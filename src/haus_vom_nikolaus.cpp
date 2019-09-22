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
     ros :: ServiceClient client = n.serviceClient<turtlesim :: TeleportAbsolute>("/turtle1/teleport_absolute");

     turtlesim :: TeleportAbsolute srv;
     turtlesim :: Pose goal_pose;

     srv.request.x = 1;
     srv.request.y = 1;
     srv.request.theta = 0;

     ros :: WallTime _start, _end;
     _start = ros :: WallTime :: now();

     if (client.call(srv))
     {
          ROS_INFO("Teleporting to 1, 1, 0");
     }
     else
     {
          ROS_ERROR("Failed to call service");
          return 1;
     }

     goal_pose.x = (double)5;
     goal_pose.y = (double)1;
     moveToGoalPI(goal_pose, 1e-2);
     turnPI(135, 1e-2);
     goal_pose.x = (double)1;
     goal_pose.y = (double)5;
     moveToGoalPI(goal_pose, 1e-2);
     turnPI(0, 1e-2);
     goal_pose.x = (double)5;
     goal_pose.y = (double)5;
     moveToGoalPI(goal_pose, 1e-2);
     turnPI(-135, 1e-2);
     goal_pose.x = (double)1;
     goal_pose.y = (double)1;
     moveToGoalPI(goal_pose, 1e-2);
     turnPI(90, 1e-2);
     goal_pose.x = (double)1;
     goal_pose.y = (double)5;
     moveToGoalPI(goal_pose, 1e-2);
     turnPI(45, 1e-2);
     goal_pose.x = (double)3;
     goal_pose.y = (double)7;
     moveToGoalPI(goal_pose, 1e-2);
     turnPI(-45, 1e-2);
     goal_pose.x = (double)5;
     goal_pose.y = (double)5;
     moveToGoalPI(goal_pose, 1e-2);
     turnPI(-90, 1e-2);
     goal_pose.x = (double)5;
     goal_pose.y = (double)1;
     moveToGoalPI(goal_pose, 1e-2);

     _end = ros :: WallTime :: now();

     double execution_time = (_end - _start).toNSec() * 1e-9;
     cout << "Execution Time (in sec) : " << execution_time << endl;

     return 0;
}
