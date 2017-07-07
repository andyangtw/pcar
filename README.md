# pcar

## source code download and build code please follow steps ##
1. create a new workspace on your local machine first
command example:
   source /opt/ros/indigo/setup.bash
   mkdir -p ~/pegacar_ws/src
(Reference: http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment)

2. git clone source code to your workspace
command example:
   cd ~/pegacar_ws/src
   git clone https://github.com/andyangtw/pcar_ws.git

3. build code
command example:
   cd ~/pegacar_ws/
   catkin_make


## If you want to test mapping on your machine, please follow steps ##
1. roscore
2. open new terminal
3. roslaunch loco hector_slam_pcar.launch
4. open new terminal
5. roslaunch loco rviz.launch


## If you want to test amcl localization on your machine, please follow steps ##
1. roscore
2. open new terminal
3. roslaunch loco amcl_pcar.launch
4. open new terminal
5. roslaunch loco rviz.launch
