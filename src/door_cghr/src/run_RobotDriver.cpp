#include "door_cghr/RobotDriver.h"
#include <string>
#include "ros/ros.h"

int main(int argc, char** argv){
    ros::init(argc, argv, "robot_driver");
    ros::NodeHandle n;
    RobotDriver robotDriver;
    robotDriver.drive();

  return 0;
}