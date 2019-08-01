#include <ros/ros.h>
#include <ros_service_example/ReverseString.h>
#include <algorithm>

bool reverseString(ros_service_example::ReverseString::Request& req, ros_service_example::ReverseString::Response& res)
{
  std::string tmp = req.in;
  std::reverse(tmp.begin(), tmp.end());
  res.out = tmp;

  ROS_INFO_STREAM("Revesed string: " << tmp);
  return true;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "add_numbers");
  ros::NodeHandle nh;

  ros::ServiceServer service = nh.advertiseService("reverse_string", reverseString);
  ROS_INFO("Ready");
  ros::spin();

  return 0;
}