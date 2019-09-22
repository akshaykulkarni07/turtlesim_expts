# Turtlesim Experiments
This repository contains some experiments with Turtlesim which implement the classical PID controllers for A to B motion and for pure turning in a differential drive mobile robot, and also one pattern (called Haus Vom Nikolaus) is generated using these controllers.

### Functions Implemented

- `moveToGoalPI` - Implementation of PI controller to move turtle to desired position. Note that it is only for the `x` and `y` of the turtle, and not the `theta`.
- `turnPI` - Implementation of PI controller to turn the turtle (about itself i.e. about `z` axis). 

### TODO
- [x] Implement Proportional controller
- [x] Implement PI controller
- [ ] Implement PID controller
- [ ] Tune all controllers

### Usage

Ensure that ROS and the ROS turtlesim package is installed in your machine.

Then, in a new terminal window, start the ROS master server :
```
roscore
```

Open another terminal and start the turtlesim simulator,
```
rosrun turtlesim turtlesim_node
```

Put the repository in your catkin workspace's src folder, and do this in another terminal (assuming workspace name is `catkin_ws`):
```
cd ~/catkin_ws
catkin_make
source ./devel/setup.bash
```
(You can edit the source code to modify the destination coordinates or orientation, but you need to repeat the catkin_make steps after editing any code)
Then, you can run the C++ code using 
```
rosrun turtlesim_expts haus_vom_nikolaus
```
and check the output in the simulator window.

You can also write generate your own pattern by writing a script using the functions from `movement.cpp` like `moveToGoal` or `turn` 
