#include "door_cghr/LaserConverter.h"
#include <ros/ros.h>
#include <laser_geometry/laser_geometry.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/transform_listener.h>

#define RANGES_SIZE 726


LaserConverter::LaserConverter() {
	laser_subscriber_ = n_.subscribe<sensor_msgs::LaserScan>("/scan_filtered", 100, &LaserConverter::scanCallback, this);
	point_cloud_publisher_ = n_.advertise<sensor_msgs::PointCloud>("cloud", 100);
	listener_.setExtrapolationLimit(ros::Duration(0.1));

}

void LaserConverter::scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan_in) {
	if(!listener_.waitForTransform(
    	scan_in->header.frame_id,
    	"/base_link",
    	scan_in->header.stamp + ros::Duration().fromSec(scan_in->ranges.size()*scan_in->time_increment),
    	ros::Duration(1.0))){
    	return;
	}

	sensor_msgs::PointCloud cloud;
	projector_.transformLaserScanToPointCloud("/base_link",*scan_in, cloud, listener_);

	// list all cloud points
	// for (int i = 0; i < RANGES_SIZE; i++) {
	// 	ROS_INFO_STREAM("converted cloud[" << i << "] = " << cloud.points[i]);
	// }

	// print if distance < range_max at 90 degrees in front
	const int RANGE_THRESHOLD = 3;
	if (scan_in->ranges[RANGES_SIZE / 2] < RANGE_THRESHOLD) {
    	ROS_INFO_STREAM(std::endl << "at 90 degrees, ranges[RANGES_SIZE/2] = " << scan_in->ranges[RANGES_SIZE/2] << "!!!!!");
    	ROS_INFO_STREAM("OBJECT DETECTED" << std::endl);
	} else {
    	ROS_INFO_STREAM("Nothing detected");
	}

	// print distance directly in front
	// ROS_INFO_STREAM("at 90 degrees, ranges[RANGES_SIZE/2] = " << scan_in->ranges[RANGES_SIZE/2]);

	/*
	// get the average of some small sector in front and print
	const int SECTOR_WIDTH = 20; // around 40 ranges = 14 degrees in front
	double ranges_sum = 0;
	for (int i = RANGES_SIZE / 2 - SECTOR_WIDTH; i < RANGES_SIZE / 2 + SECTOR_WIDTH; i++) {
    	// ROS_INFO_STREAM("sector: ranges[" << i << "] = " << scan_in->ranges[i] << std::endl);
    	if (scan_in->ranges[i] < scan_in->range_max) {
        	ranges_sum += scan_in->ranges[i];
    	}
   	 
	}

	// range_max is 5.6
	const int RANGE_THRESHOLD = 3;
	double ranges_avg = ranges_sum / (SECTOR_WIDTH * 2);
	if (ranges_avg < RANGE_THRESHOLD && ranges_avg > scan_in->range_min) {
    	ROS_INFO_STREAM("ranges_avg = " << ranges_avg << std::endl);
    	ROS_INFO_STREAM("OBJECT DETECTED" << std::endl);
	}

	*/

	point_cloud_publisher_.publish(cloud);
}