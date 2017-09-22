# pcar

![image](https://github.com/andyangtw/pcar_ws/blob/master/pcar_image/20170612_104811.jpg)


## Demo Video ##
**hector_slam mapping video**<br/> 
[![image](http://img.youtube.com/vi/6vYtg7prtX8/0.jpg)](http://www.youtube.com/watch?v=6vYtg7prtX8)<br/>
**amcl localization video**<br/> 
[![image](http://img.youtube.com/vi/LBaiD47eCDw/0.jpg)](https://www.youtube.com/watch?v=LBaiD47eCDw)


## source code download and build code please follow steps ##
1. create a new workspace on your local machine first<br/>
```
$ source /opt/ros/indigo/setup.bash
$ mkdir -p ~/pcar_ws/src
```
(Reference: http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment)

2. git clone source code to your workspace<br/>
```
$ cd ~/pcar_ws/src
$ git clone https://github.com/andyangtw/pcar.git
```
3. build code<br/>
```
$ cd ~/pcar_ws/
$ catkin_make
```
If you finish building code, you need to source your worksapce.
please add **source ~/pcar_ws/devel/setup.bash** in your .bashrc.<br/>
and use the commands below to copy the rule for pcar usb devices.<br/>
```
$ sudo cp ~/pcar_ws/src/pcar/loco/prepare_process/98-pcar-usb-devices.rules /etc/udev/rules.d/
```
## Test mapping or navigation on TX1, you should do some setting on your local machine ##
1. connect to TX1 wifi
2. Add **export ROS_MASTER_URI=http://10.0.0.100:11311** in your .bashrc 
3. Add **export ROS_IP=your IP** in your .bashrc 
4. Add **10.0.0.100 tegra-ubuntu** in your /etc/hosts
5. ssh ubuntu@tegra-ubuntu

## Test mapping with ps3 ##
**On TX1 setting commmand**
```
$ roscore
  open new terminal(Just only run once time for ps3 paired)
$ sudo bash
$ hciconfig hci0 reset
$ roslaunch loco ps3_pairing.launch
  open new terminal
$ roslaunch loco hector_slam_pcar.launch
```
**On your local machine setting commmand**
```
$ roslaunch loco map_rviz_pcar.launch
```
## Test amcl localization with ps3 ##
**On TX1 setting commmand**
```
$ roscore
  open new terminal(Just only run once time for ps3 paired)
$ sudo bash
$ hciconfig hci0 reset
$ roslaunch loco ps3_pairing.launch
  open new terminal
$ roslaunch loco amcl_pcar.launch
```
**On your local machine setting commmand**
```
$ roslaunch loco rviz.launch
```

## Test loop navigation between any two waypoints ##  ##The two waypoints are initial pose and goal pose respectively ## ## Navigation map is in office 5F building ##
**On TX1 setting commmand**
```
$ roscore
  open new terminal
$ roslaunch loco nav_pcar.launch
```
**On your local machine setting commmand**
```
$ roslaunch loco nav_rviz_pcar.launch
```
To run navigation, you need to setting robot initial pose and goal's pose:</br> 
1. First, you need to put robot on navigation start point in map
2. Click "2D Pose Estimate" button on rviz and click robot current pose in map on rviz to set initial pose
3. Use below command to know intial pose value and set initial_pose_x,initial_pose_y,initial_pose_a parameter value in amcl_pcar.launch
```
$ rosparam get /amcl/initial_pose_x (robot's x position)
$ rosparam get /amcl/initial_pose_y (robot's y position)
$ rosparam get /amcl/initial_pose_a (robot's yaw)
```
4. Goals pose as initial pose determine method, click "2D Pose Estimate" button on rviz and click goal's pose in map
5. Using step 3 command to get goal's pose value
6. "waypoint_nav.py" is a send multiple goals python</br>
    Setting goal's pose and a intial pose point to in "waypoint_nav.py"

Finally, finish intial pose and goal's pose setting, run below command 

```
$ rosrun loco waypoint_nav.py (send navigation goals and ctrl+c key can stop navigation)
```


## Simulate pcar navigation ##
```
$ roscore
  open new terminal
$ roslaunch rbx1_nav pcar_sim.launch
```
