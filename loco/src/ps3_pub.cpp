#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <math.h>

int main(int argc, char **argv)
{
const double PI = 3.14159265358979323846;

ros::init(argc, argv, "ps3_pub");
ros::NodeHandle n;
ros::Publisher ps3movement_pub = n.advertise<sensor_msgs::Joy>("joy", 1); //for sensors the value after , should be higher to get a more accurate result (queued)
ros::Rate rate(10); //the larger the value, the "smoother" , try value of 1 to see "jerk" movement

ros::Time start = ros::Time::now();
while(ros::Time::now() - start < ros::Duration(3.0))
{

    sensor_msgs::Joy move;
    
    for (int i=0; i<20; i++)
    {
       if (i==3)
       {
          move.axes.push_back(1.0);
       }
       else
       move.axes.push_back(0.0);
    }
    

    for (int i=0; i<17; i++)
    {
       if (i==10)
       {
          move.buttons.push_back(1);
       }
       else
       move.buttons.push_back(0);
    }
    
    ps3movement_pub.publish(move);

    ros::spinOnce();
    rate.sleep();
}

ros::Time start1 = ros::Time::now();
while(ros::Time::now() - start1 < ros::Duration(1.0))
{
    sensor_msgs::Joy move;     

    for (int i=0; i<17; i++)
    {
       move.buttons.push_back(0);
    }
    
    ps3movement_pub.publish(move);

    ros::spinOnce();
    rate.sleep();
}

return 0;
}
