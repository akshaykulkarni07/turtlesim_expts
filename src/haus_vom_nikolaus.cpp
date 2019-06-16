#include "movement.h"

// global variables declaration
// ros :: Publisher vel_pub;
// ros :: Subscriber pose_sub;
// turtlesim :: Pose current_pose;

int main(int argc, char **argv)
{
     ros :: init(argc, argv, "haus_vom_nikolaus");
     ros :: NodeHandle n;
     vel_pub = n.advertise<geometry_msgs :: Twist>("/turtle1/cmd_vel", 1000);
     pose_sub = n.subscribe<turtlesim :: Pose>("/turtle1/pose", 1000, poseCallback);

     turtlesim :: Pose goal_pose;

     ros :: WallTime _start, _end;

     _start = ros :: WallTime :: now();

     // goal_pose.x = (double)5;
     // goal_pose.y = (double)1;
     // moveToGoal(goal_pose, 1e-2);
     // turn(135, 1e-4);
     // goal_pose.x = (double)1;
     // goal_pose.y = (double)5;
     // moveToGoal(goal_pose, 1e-2);
     // turn(0, 1e-4);
     // goal_pose.x = (double)5;
     // goal_pose.y = (double)5;
     // moveToGoal(goal_pose, 1e-2);
     // turn(225, 1e-4);
     // goal_pose.x = (double)1;
     // goal_pose.y = (double)1;
     // moveToGoal(goal_pose, 1e-2);
     // turn(90, 1e-4);
     // goal_pose.x = (double)1;
     // goal_pose.y = (double)5;
     // moveToGoal(goal_pose, 1e-2);
     // turn(45, 1e-4);
     // goal_pose.x = (double)3;
     // goal_pose.y = (double)7;
     // moveToGoal(goal_pose, 1e-2);
     // turn(360 - 45, 1e-4);
     // goal_pose.x = (double)5;
     // goal_pose.y = (double)5;
     // moveToGoal(goal_pose, 1e-2);
     // turn(270, 1e-4);
     // goal_pose.x = (double)5;
     // goal_pose.y = (double)1;
     // moveToGoal(goal_pose, 1e-2);

     goal_pose.x = (double)5.44444444;
     goal_pose.y = (double)1;
     moveToGoal(goal_pose, 1e-4);

     _end = ros :: WallTime :: now();

     double execution_time = (_end - _start).toNSec() * 1e-9;
     cout << "Execution Time (in sec) : " << execution_time << endl;

     return 0;
}
