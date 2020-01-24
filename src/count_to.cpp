/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2019, Gregor Seljak
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <ros_service_example/CountToAction.h>
#include <string>

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

  ~CountTo() = default;

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

  int b;

  return 0;
}
