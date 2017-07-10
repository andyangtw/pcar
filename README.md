# pcar

![image](https://github.com/andyangtw/pcar_ws/blob/master/pcar_image/20170612_104811.jpg)

**hector_slam video**<br/> 
[![image](http://img.youtube.com/vi/6vYtg7prtX8/0.jpg)](http://www.youtube.com/watch?v=6vYtg7prtX8)<br/>
**amcl localization video**<br/> 
[![image](http://img.youtube.com/vi/GngFAX3XQzk/0.jpg)](http://www.youtube.com/watch?v=GngFAX3XQzk)


## source code download and build code please follow steps ##
1. create a new workspace on your local machine first<br/>
**command example:**<br/>
   source /opt/ros/indigo/setup.bash<br/>
   mkdir -p ~/pcar_ws/src<br/>
(Reference: http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment)

2. git clone source code to your workspace<br/>
**command example:**<br/>
   cd ~/pcar_ws/src<br/>
   git clone https://github.com/andyangtw/pcar.git

3. build code<br/>
**command example:**<br/>
   cd ~/pcar_ws/<br/>
   catkin_make

If you finish building code, you need to source your worksapce.
please add **source ~/pcar_ws/devel/setup.bash** in your .bashrc.

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


## If you want to test amcl localization with bagfile on your machine, please follow steps ##
1. roscore
2. open new terminal
3. roslaunch loco amcl_pcar_bag.launch
4. open new terminal
5. roslaunch loco rviz.launch
