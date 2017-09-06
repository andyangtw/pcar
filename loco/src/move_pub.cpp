#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <math.h>

int main(int argc, char **argv)
{
const double PI = 3.14159265358979323846;

ros::init(argc, argv, "move_pub");
ros::NodeHandle n;
ros::Publisher movement_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_out", 1); //for sensors the value after , should be higher to get a more accurate result (queued)
ros::Rate rate(10); //the larger the value, the "smoother" , try value of 1 to see "jerk" movement

//move forward
ros::Time start = ros::Time::now();
while(ros::Time::now() - start < ros::Duration(3.0))
{
    geometry_msgs::Twist move;
    //velocity controls
    move.linear.x = 1.0; //speed value m/s
    move.angular.z = 0.0;
    movement_pub.publish(move);

    ros::spinOnce();
    rate.sleep();
}
ros::Time start1 = ros::Time::now();
while(ros::Time::now() - start1 < ros::Duration(1.0))
{
    geometry_msgs::Twist move;
    //velocity controls
    move.linear.x = 0.0; 
    move.angular.z = 0;
    movement_pub.publish(move);

    ros::spinOnce();
    rate.sleep();
}

return 0;
}
