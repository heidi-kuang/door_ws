#include "door_cghr/LocationParser.h"
#include <ros/ros.h>

LocationParser::LocationParser(std::string fileName) {
    fileStream.open(fileName);
   
    if (fileStream.is_open()) {
        ROS_INFO_STREAM("successfully opened file");
    }
}

LocationParser::~LocationParser() {}


std::vector<move_base_msgs::MoveBaseGoal> LocationParser::getLocations() {
    std::string line;
    if (fileStream.is_open()) {
        std::getline(fileStream, line);
        

        ROS_INFO_STREAM(line);

    }


    return locations;
}