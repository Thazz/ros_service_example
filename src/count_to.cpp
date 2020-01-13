#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <ros_service_example/CountToAction.h>

namespace ros_service_example
{
class CountTo
{
protected:
  ros::NodeHandle nh_;
  ros::NodeHandle private_nh_;
  actionlib::SimpleActionServer<ros_service_example::CountToAction> as_;
  std::string action_name_;
  int loop_hz_;

  ros_service_example::CountToFeedback feedback_;
  ros_service_example::CountToResult result_;

public:
  CountTo(ros::NodeHandle& nh, const std::string& name)
    : nh_(nh)
    , private_nh_("~")
    , as_(nh_, name, boost::bind(&CountTo::executeCallback, this, _1), false)
    , action_name_(name)
    , loop_hz_(0)
  {
    private_nh_.param<int>("loop_hz", loop_hz_, 10);
    as_.start();
  }

  ~CountTo()
  {
  }

  void executeCallback(const ros_service_example::CountToGoalConstPtr& goal)
  {
    ROS_INFO_STREAM(action_name_ << " started");

    // helper variables
    ros::Rate r(2);
    bool success = true;

    // push_back the seeds for the fibonacci sequence
    feedback_.current_number = 0;

    // start executing the action
    for (int i = 1; i <= goal->number; i++)
    {
      // check that preempt has not been requested by the client
      if (as_.isPreemptRequested() || !ros::ok())
      {
        ROS_INFO_STREAM(action_name_ << " preempted");
        as_.setPreempted();
        success = false;
        break;
      }
      feedback_.current_number = i;
      as_.publishFeedback(feedback_);
      r.sleep();
    }

    if (success)
    {
      result_.final_number = feedback_.current_number;
      ROS_INFO_STREAM(action_name_ << " succeeded");
      // set the action state to succeeded
      as_.setSucceeded(result_);
    }
  }
};
}  // namespace ros_service_example

int main(int argc, char** argv)
{
  ros::init(argc, argv, "count_to");
  ros::NodeHandle nh;

  ros_service_example::CountTo cta(nh, "count_to");
  ros::spin();

  return 0;
}