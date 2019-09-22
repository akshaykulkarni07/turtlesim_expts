#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <math.h>
#include <sstream>
#include "turtlesim/Pose.h"
#include "turtlesim/TeleportAbsolute.h"
#include <string>

// global variables declaration
ros :: Publisher vel_pub;
ros :: Subscriber pose_sub;
turtlesim :: Pose current_pose;
double linear_error, angular_error;

#endif

using namespace std;

// function declarations
double degreesToRadians(double);
double radiansToDegrees(double);
double distance(double, double, double, double);
geometry_msgs :: Twist returnVelocity(double, double);
void turn(double, double);
void turnPI(double, double);
void moveToGoal(turtlesim :: Pose, double);
void moveToGoalPI(turtlesim :: Pose, double);
void poseCallback(const turtlesim :: Pose :: ConstPtr&);
