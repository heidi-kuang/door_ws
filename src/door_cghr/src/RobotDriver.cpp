#include <door_cghr/RobotDriver.h>
#include <geometry_msgs/TransformStamped.h>

// tell the action client that we want to spin a thread by default
RobotDriver::RobotDriver() : _ac("move_base", true), tfListener(buffer)
{
  // wait for the action server to come up
  while (!_ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for the move_base action server to come up");
  }
}

RobotDriver::~RobotDriver() {}

void RobotDriver::drive(){
  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.header.frame_id = "base_link";
  goal.target_pose.header.stamp = ros::Time::now();

//   difference = buffer.lookupTransform("base_footprint", landmark, ros::Time(0), ros::Duration(4.0));

  /**
   * At time 1682298364.380
        - Translation: [5.959, -1.413, 0.216]
        - Rotation: in Quaternion [0.000, 0.000, 0.709, 0.705]
                    in RPY (radian) [0.000, -0.000, 1.577]
                    in RPY (degree) [0.000, -0.000, 90.367]

  */

  goal.target_pose.pose.position.x = 5.959;
  goal.target_pose.pose.position.y = -1.413;
  goal.target_pose.pose.position.z = 0.216;

  goal.target_pose.pose.orientation.x = 0.0;
  goal.target_pose.pose.orientation.y = 0.0;
  goal.target_pose.pose.orientation.z = 0.709; 
  goal.target_pose.pose.orientation.w = 0.705;

  _ac.sendGoal(goal);

  _ac.waitForResult();

  if (_ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("Hooray, the base moved to the designated landmark");
  } else {
    ROS_INFO("The base failed to move to the designated landmark for some reason");
  }
}

