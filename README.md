# Usage

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
rosrun turtlesim_expts movement
```
and check the output in the simulator window.
