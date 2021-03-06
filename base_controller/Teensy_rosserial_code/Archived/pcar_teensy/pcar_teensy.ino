/*
   rosserial Servo Control Example

   This sketch demonstrates the control of hobby R/C servos
   using ROS and the arduiono

   For the full tutorial write up, visit
   www.ros.org/wiki/rosserial_arduino_demos

   For more information on the Arduino Servo Library
Checkout :
http://www.arduino.cc/en/Reference/Servo
 */

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>
//#include <ackermann_msgs/AckermannDriveStamped.h>

#define led_pin 13
#define kill_pin 20
//#define disable_pin 21
#define esc_pin 10
#define servo_pin 9

const int defSteering = 1455 ;
const int diffSteering = 610 ;
static long offSteering = 0 ;
static double last_speed = 0.0 ;
//const int minSteering = 852 ;
//const int maxSteering = 2086 ;

const int defThrottle = 1470 ;
const int revstartThrottle = 1387 ;
const int minThrottle = 1377 ;
const int startThrottle = 1560 ;
const int maxThrottle = 1568 ;
const int turningoffset = 5;
const double maxSpeed = -0.3 ;
const double revSpeed = 0.3 ;


ros::NodeHandle  nh;

Servo servo;
Servo esc;

double x, w;
long steer, throttle;
char buf[200];
unsigned long last_received;
const unsigned long timeout = 1000; //timeout in ms before resetting steering and throttle to 0

bool disabled = 0;
bool kill = 0;


double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//std_msgs::String out_msg;
std_msgs::String out_msg;
ros::Publisher teensy("teensy", &out_msg);

std_msgs::Int32 str_msg;
ros::Publisher chatter("chatter", &str_msg); 

void cmd_vel_cb(const geometry_msgs::Twist& cmd_msg) {
	x = (-1.0) * cmd_msg.linear.x;
	w = cmd_msg.angular.z;
	last_received = millis();
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel_out", cmd_vel_cb);

void cmd_vel_offset_cb(const geometry_msgs::Twist& cmd_msg) {
	offSteering = mapf(cmd_msg.angular.z, 0.96, -0.96, diffSteering, (-1.0) * diffSteering);
	// str_msg.data = offSteering;
	// chatter.publish( &str_msg );
}

ros::Subscriber<geometry_msgs::Twist> sub1("cmd_vel_offset", cmd_vel_offset_cb);

void setup() {
	pinMode(led_pin, OUTPUT);
	pinMode(esc_pin, OUTPUT);
	pinMode(servo_pin, OUTPUT);
	// pinMode(disable_pin, INPUT);
	// pinMode(kill_pin, INPUT);
	// attachInterrupt(disable_pin, disable_ISR, CHANGE);
	// attachInterrupt(kill_pin, kill_ISR, CHANGE);
	nh.getHardware()->setBaud(115200);
	nh.initNode();
	nh.subscribe(sub);
	//nh.advertise(teensy);
	nh.advertise(chatter);
	nh.subscribe(sub1);

	servo.attach(servo_pin, defSteering - diffSteering, defSteering + diffSteering); //attach it to pin A9/23
	// esc.attach(esc_pin, minThrottle, maxThrottle); //attach it to pin A8/22
	esc.attach(esc_pin, 1000, 2000); //attach it to pin A8/22

	// just to show it's alive
	digitalWrite(led_pin, HIGH);
	delay(100);
	digitalWrite(led_pin, LOW);
	delay(100);
	digitalWrite(led_pin, HIGH);
	delay(100);
	digitalWrite(led_pin, LOW);
}

void loop() {

	unsigned long elapsed = millis() - last_received;
	int steeringAngle;
	int escCmd;

	if (elapsed > timeout) {
		//x = 0;
		//w = 0;
	}

	nh.spinOnce();
	String out;
	//out +=  "lx: " + String(x) + ", " + String(throttle) + '\t' + "az: " + String(w) + ", " + String(steer) + '\t' ;
	//out.toCharArray(buf, 200);
	//out_msg.data = buf;
	//teensy.publish( &out_msg );

	if (!disabled) {

		if (w == 0)
			steer = defSteering + offSteering;
		else
			steer = mapf(w, 0.96, -0.96, (defSteering + offSteering) - diffSteering, (defSteering + offSteering) + diffSteering); //maxes out at +/- 0.96 rads = +/- 55 degs
		// servo.attach(servo_pin, 1000, 2000);

		// servo.writeMicroseconds(steer);
		// if (abs(steer-1500) <= 10) {
		//          steer = 1500;
		//    }

		if (x > 0) {
			throttle = mapf(x, 0, revSpeed, revstartThrottle, minThrottle);
			if (w != 0)
				throttle -= turningoffset;
			str_msg.data = throttle;
			chatter.publish( &str_msg );
			//throttle = mapf(x, 0, 4.0, 1500, 1000);
			//        if ( x > 2.0) {
			//          throttle = mapf(x, 0, 4.0, 1500, 1000);
			//        }
			//
			//        else {
			//             throttle = mapf(x, 0, 2.0, 1500, 1250); //hand tuned values. default to 1500, 2000 if problems
			//
			//        }

		}

		else if (x < 0) {
			throttle = mapf(x, maxSpeed , 0, maxThrottle, startThrottle);
			if (w != 0)
				throttle += turningoffset;
			str_msg.data = throttle;
			chatter.publish( &str_msg );
			//throttle = mapf(x, -4.0 , 0, 2000, 1500);
			//      if ( x < -2.0) {
			//          throttle = mapf(x, -4.0 , 0, 2000, 1500);
			//       }
			//
			//      else {
			//          throttle = mapf(x, -2.0, 0, 1750, 1500); //hand tuned values. default to 1500, 2000 if problems
			//      }

		}

		else {
			throttle = defThrottle;
		}

		// Terry print log - B
		steeringAngle = steer;
		// Steering
		// str_msg.data = steeringAngle;
		// chatter.publish( &str_msg );
		escCmd = throttle;
		// Throttle
		// str_msg.data = throttle;
		// chatter.publish( &str_msg );
		// Adjust Steering
		//if (offSteering != 0) {
		//  str_msg.data = offSteering;
		//  chatter.publish( &str_msg );
		//}
		// Terry print log - E

		if (last_speed <= 0.0 && x > 0.0) {
			esc.writeMicroseconds(throttle);
			//str_msg.data = (int)(1000*last_speed);
			//chatter.publish( &str_msg );
			delay(100);
			esc.writeMicroseconds(defThrottle);
			//str_msg.data = (int)(1000*x);
			//chatter.publish( &str_msg );
			delay(100);
		}
		esc.writeMicroseconds(throttle);
		servo.writeMicroseconds(steer);
		last_speed = x;

		/*
		   if (elapsed > 500 && steer == 1500) {
		   servo.detach();
		   }
		 */
		digitalWrite(led_pin, LOW);
	}

	else {  //when disabled

		throttle = defThrottle;
		steer = defSteering;
		servo.writeMicroseconds(steer);
		//servo.detach();
		esc.writeMicroseconds(throttle);
		digitalWrite(led_pin, HIGH);

	}

	delay(10);
}

/*
   void disable_ISR() {

   disabled = digitalRead(disable_pin);
   w = 0;
   x = 0;
   throttle = 1500;
   steer = 1500;
   esc.writeMicroseconds(1500);
   servo.writeMicroseconds(1500);
   servo.detach();

   }
 */

