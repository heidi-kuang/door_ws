#ifndef LASER_CONVERTER_H
#define LASER_CONVERTER_H

#include <ros/ros.h>
#include <laser_geometry/laser_geometry.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/transform_listener.h>

class LaserConverter {
protected:
    ros::NodeHandle n_;

    laser_geometry::LaserProjection projector_;
    tf::TransformListener listener_;

    ros::Publisher point_cloud_publisher_;
    ros::Subscriber laser_subscriber_;

public:
    LaserConverter();

    void scanCallback (const sensor_msgs::LaserScan::ConstPtr& scan_in);

};

#endif