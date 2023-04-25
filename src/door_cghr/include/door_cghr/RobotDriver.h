
#ifndef ROBOT_DRIVER_H
#define ROBOT_DRIVER_H

#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>

#include <string>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class RobotDriver {
public:
    RobotDriver();
    ~RobotDriver();
    void drive();
    
protected:
    MoveBaseClient _ac;
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener tfListener;
};

#endif