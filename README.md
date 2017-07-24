# pcar

![image](https://github.com/andyangtw/pcar_ws/blob/master/pcar_image/20170612_104811.jpg)

**hector_slam video**<br/> 
[![image](http://img.youtube.com/vi/6vYtg7prtX8/0.jpg)](http://www.youtube.com/watch?v=6vYtg7prtX8)<br/>
**amcl localization video**<br/> 
[![image](http://img.youtube.com/vi/LBaiD47eCDw/0.jpg)](https://www.youtube.com/watch?v=LBaiD47eCDw)


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

## If you want to simulate pcar navigation, please follow steps ##
1. roscore
2. open new terminal
3. roslaunch rbx1_nav pcar_sim.launch



## If you want to test mapping or localization on TX1, you should do some setting on your local machine ##
1. connect to TX1 wifi
2. Add **export ROS_MASTER_URI=http://192.168.0.100:11311** in your .bashrc 
3. Add **export ROS_IP=your IP** in your .bashrc 
4. ssh ubuntu@tegra-ubuntu

## If you want to test mapping on your tx1 with ps3, please follow steps ##
**On TX1 setting commmand**
1. roscore
2. open new terminal
3. sudo bash
4. hciconfig hci0 reset
5. roslaunch loco hector_slam_pcar_ps3.launch<br/>
**On your local machine setting commmand**
1. roslaunch loco rviz_cam.launch

## If you want to test amcl localization on your tx1 with ps3, please follow steps ##
**On TX1 setting commmand**
1. roscore
2. open new terminal
3. sudo bash
4. hciconfig hci0 reset
5. roslaunch loco amcl_pcar_ps3.launch<br/>
**On your local machine setting commmand**
1. roslaunch loco rviz_cam.launch


