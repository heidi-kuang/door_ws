#include "door_cghr/RobotDriver.h"
#include <string>
#include "ros/ros.h"

#include "door_cghr/LocationParser.h"

int main(int argc, char** argv){
    ros::init(argc, argv, "robot_driver");
    ros::NodeHandle n;
    // RobotDriver robotDriver;
    // robotDriver.drive();

    LocationParser p("src/door_cghr/include/door_cghr/locations.txt");
    p.getLocations();
    ROS_INFO_STREAM("hello");

  return 0;
}