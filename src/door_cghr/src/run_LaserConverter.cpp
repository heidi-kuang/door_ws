#include "ros/ros.h"
#include "door_cghr/LaserConverter.h"

#include <iostream>

int main(int argc, char **argv) {
    ros::init(argc, argv, "laser_converter");
    LaserConverter converter;
    ros::spin();
    return 0;
}