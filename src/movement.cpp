#include "movement.h"

// called whenever there is a new message on the pose topic of turtle
void poseCallback(const turtlesim :: Pose :: ConstPtr& pose)
{
     current_pose.x = pose -> x;
     current_pose.y = pose -> y;
     current_pose.theta = pose -> theta;
     current_pose.linear_velocity = pose -> linear_velocity;
     current_pose.angular_velocity = pose -> angular_velocity;
     cout << "Current Pose : " << current_pose.x << " " << current_pose.y << " " << radiansToDegrees(current_pose.theta) << endl;
     cout << "Linear Velocity : " << current_pose.linear_velocity << endl;
     cout << "Angular Velocity : " << current_pose.angular_velocity << endl;
     return;
}

// int main(int argc, char **argv)
// {
//      ros :: init(argc, argv, "movement");
//      ros :: NodeHandle n;
//      // subscribe to turtle's pose topic
//      pose_sub = n.subscribe<turtlesim :: Pose>("/turtle1/pose", 1000, poseCallback);
//      // publisher for velocity of turtle
//      vel_pub = n.advertise<geometry_msgs :: Twist>("/turtle1/cmd_vel", 1000);
//      // loop.sleep() will produce a delay of 0.1 sec i.e. 10Hz frequency
//      ros :: Rate loop_rate(10);
//
//      turtlesim :: Pose goal_pose;
//      goal_pose.x = (double)4;
//      goal_pose.y = (double)1;
//      moveToGoal(goal_pose, 1e-2);
//      turn(310, 1e-4);
//      return 0;
// }

// returns angle (in degrees) converted to radians
double degreesToRadians(double theta)
{
     return(theta * (M_PI / 180));
}

// returns angle (in radians) converted to degrees
double radiansToDegrees(double theta)
{
     return(theta * (180 / M_PI));
}

// returns distance between 2 points (x, y) and (x2, y2) in the Cartesian plane
double distance(double x, double y, double x2, double y2)
{
     return sqrt(pow(x - x2, 2) + pow(y - y2, 2));
}

// move to desired position using proportional controller
void moveToGoal(turtlesim :: Pose goal_pose, double tolerance)
{
     ros :: Rate loop_rate(10);
     while (ros :: ok() && distance(current_pose.x, current_pose.y, goal_pose.x, goal_pose.y) > tolerance)
     {
          double speed = distance(current_pose.x, current_pose.y, goal_pose.x, goal_pose.y);
          double angular_speed = 16 * (atan2(goal_pose.y - current_pose.y, goal_pose.x - current_pose.x) - current_pose.theta);
          geometry_msgs :: Twist vel = returnVelocity(speed, angular_speed);
          vel_pub.publish(vel);
          loop_rate.sleep();
          ros :: spinOnce();
     }
     cout << "Reached goal position" << endl;
     return;
}

// move to desired position using PI controller
void moveToGoalPI(turtlesim :: Pose goal_pose, double tolerance)
{
     ros :: Rate loop_rate(10);
     // 0.1 is used as time interval since ROS loop rate is 10 Hz
     double dt = 0.1;
     double kp = 16;
     double ki = 1e-2;
     // double ki = 0;
     double linear_error = 0;
     double angular_error = 0;
     while (ros :: ok() && distance(current_pose.x, current_pose.y, goal_pose.x, goal_pose.y) > tolerance)
     {
          double dist = distance(current_pose.x, current_pose.y, goal_pose.x, goal_pose.y);
          linear_error += (dist * dt);
          double speed = dist + (ki * linear_error);
          double ang = atan2(goal_pose.y - current_pose.y, goal_pose.x - current_pose.x) - current_pose.theta;
          // double ang = atan2(goal_pose.y - current_pose.y, goal_pose.x - current_pose.x);
          // double ang = current_pose.theta - degreesToRadians(goal_pose.theta);
          angular_error += (ang * dt);
          cout << "Linear Error Total " << linear_error << " Angular Error Total " << angular_error << endl;
          double angular_speed = kp * ang + ((1 / 100) * angular_error);
          cout << "Angular Speed " << angular_speed << endl;
          geometry_msgs :: Twist vel = returnVelocity(speed, angular_speed);
          vel_pub.publish(vel);
          loop_rate.sleep();
          ros :: spinOnce();
     }
     cout << "Reached goal position" << endl;
     return;
}

// returns a Twist variable with desired velocity parameters
geometry_msgs :: Twist returnVelocity(double speed, double angular_speed)
{
     geometry_msgs :: Twist vel;
     vel.linear.x = speed;
     vel.linear.y = 0;
     vel.linear.z = 0;
     vel.angular.x = 0;
     vel.angular.y = 0;
     vel.angular.z = angular_speed;
     return vel;
}

// turtle rotates to goal angle using proportional controller
void turn(double angle, double tolerance)
{
     ros :: Rate loop_rate(10);
     double kp = 4.0;
     double angle_rad = degreesToRadians(angle);
     while (ros :: ok() && abs(angle_rad - current_pose.theta) > tolerance)
     {
          geometry_msgs :: Twist vel = returnVelocity(0, kp * (angle_rad - current_pose.theta));
          vel_pub.publish(vel);
          ros :: spinOnce();
          loop_rate.sleep();
     }
     cout << "reached goal angle" << endl;
     return;
}

// turtle rotates to goal angle using PI controller
void turnPI(double angle, double tolerance)
{
     ros :: Rate loop_rate(10);
     double kp = 4;
     double ki = 1e-4;
     // double ki = 0;
     double angular_error = 0;
     double angle_rad = degreesToRadians(angle);
     while (ros :: ok() && abs(angle_rad - current_pose.theta) > tolerance)
     {
          double prop_err = angle_rad - current_pose.theta;
          // integral error has to be multiplied with dt = 0.1 seconds
          // as that is the ROS rate
          angular_error += prop_err * 0.1;
          geometry_msgs :: Twist vel = returnVelocity(0, kp * prop_err + ki * angular_error);
          vel_pub.publish(vel);
          ros :: spinOnce();
          loop_rate.sleep();
     }
     cout << "reached goal angle" << endl;
     return;
}
