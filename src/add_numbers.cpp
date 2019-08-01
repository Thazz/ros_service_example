#include <ros/ros.h>
#include <ros_service_example/AddNumbers.h>

bool add(ros_service_example::AddNumbers::Request& req, ros_service_example::AddNumbers::Response& res)
{
  double sum = 0;
  for (auto num : req.numbers)
  {
    sum += num;
  }
  res.sum = sum;

  ROS_INFO_STREAM("Sum: " << sum);
  return true;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "add_numbers");
  ros::NodeHandle nh;

  ros::ServiceServer service = nh.advertiseService("add_numbers", add);
  ROS_INFO("Ready");
  ros::spin();

  return 0;
}