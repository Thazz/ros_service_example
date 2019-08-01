#include <ros/ros.h>
#include <smartgv_chatter/AddNumbers.h>
#include <cstdlib>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "add_numbers_client");

  ros::NodeHandle nh;
  ros::ServiceClient client = nh.serviceClient<smartgv_chatter::AddNumbers>("/ihs/smartgv_chatter/add_numbers");
  smartgv_chatter::AddNumbers srv;

  std::vector<double> input{ 1, 2, 3, 4, 5 };
  srv.request.numbers = input;

  if (client.call(srv))
  {
    ROS_INFO_STREAM("Sum: " << srv.response.sum);
  }
  else
  {
    ROS_ERROR("Failed to call service add_numbers");
    return 1;
  }

  return 0;
}