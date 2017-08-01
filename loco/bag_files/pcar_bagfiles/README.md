# pcar bagfile

**csmfail.bag** <br/>
amcl localization with csm issue bag file.<br/>
**nav_ekf.bag** <br/>
navigation bag file.<br/>


## If you want to test amcl with csm fail case using bagfile on your machine, please follow steps ##
**Modify launch**<br/>
1. cd ~/pcar_ws/src/pcar/loco/launch/core
2. vim odometry_pcar.launch
3. Change "hector" default true --> false<br/>
   Change "csm" default false --> true<br/>
4. vim robot_tf.launch  
5. Change 3.14159 --> 0<br/>
6. cd ~/pcar_ws/src/pcar/loco/launch/amcl
7. vim amcl_pcar.launch
8. Setting intialpose<br/>
      initial_pose_x: -9.624<br/>
      initial_pose_y: -4.781<br/>
      initial_pose_a: -1.826<br/>

**command** <br/>
1. roscore
2. open new terminal
3. rosparam set use_sim_time true
4. rosparam get use_sim_time
5. cd ~/pcar_ws/src/pcar/loco/bag_files/pcar_bagfiles 
6. rosbag play csmfail.bag --clock
7. open new terminal
8. roslaunch loco amcl_pcar.launch
9. roslaunch loco rviz.launch<br/>
**If you want to tunning parameter using reconfigure ui,please run below command** <br/>
10. rosrun rqt_reconfigure rqt_reconfigure

## If you want to test amcl with csm fail case using bagfile on your machine, please follow steps ##
1. roscore
2. open new terminal
3. rosparam set use_sim_time true
4. rosparam get use_sim_time
5. cd ~/pcar_ws/src/pcar/loco/bag_files/pcar_bagfiles 
6. rosbag play nav_ekf.bag --clock
7. open new terminal
8. roslaunch loco nav.launch
9. roslaunch loco rviz.launch
**If you want to tunning parameter using reconfigure ui,please run below command** <br/>
10. rosrun rqt_reconfigure rqt_reconfigure


