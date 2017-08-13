# pcar

![image](https://github.com/andyangtw/pcar_ws/blob/master/pcar_image/20170612_104811.jpg)


## Video ##
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
## If you want to test mapping or localization on TX1, you should do some setting on your local machine ##
1. connect to TX1 wifi
2. Add **export ROS_MASTER_URI=http://192.168.0.100:11311** in your .bashrc 
3. Add **export ROS_IP=your IP** in your .bashrc 
4. ssh ubuntu@tegra-ubuntu

## If you want to test mapping on your tx1 with ps3, please follow steps ##
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
$ roslaunch loco rviz.launch
```
## If you want to test amcl localization on your tx1 with ps3, please follow steps ##
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

## If you want to test navigation on your tx1 with ps3, please follow steps ##
**On TX1 setting commmand**
```
$ roscore
  open new terminal(Just only run once time for ps3 paired)
$ sudo bash
$ hciconfig hci0 reset
$ roslaunch loco ps3_pairing.launch
  open new terminal
$ roslaunch loco nav_pcar.launch<br/>
```
**On your local machine setting commmand**
```
$ roslaunch loco nav_rviz_pcar.launch
```

## If you want to simulate pcar navigation, please follow steps ##
```
$ roscore
$ open new terminal
$ roslaunch rbx1_nav pcar_sim.launch
```
