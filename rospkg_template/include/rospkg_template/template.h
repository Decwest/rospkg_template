#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float64.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include "rospkg_template_msgs/SrvTemplate.h"

#include <cmath>
#include <string>

class Template
{
public:
    Template(ros::NodeHandle &nh, const int &loop_rate, const std::string &base_frame_id);
    ~Template(){};

private:
    //Handlers
    ros::NodeHandle nh_;

    // TODO: topic communication

    // service communication
    ros::ServiceServer service_server_;

    // TODO: action communication

    // tf::TransformBroadcaster broadcaster;
    // tf::TransformListener listerner;

    //Configurations
    int loop_rate_;
    std::string base_frame_id_;

    //variables
    double temp_variable = 0.0;

    //Methods
    void update();
    bool templateService(rospkg_template_msgs::SrvTemplate::Request &req, rospkg_template_msgs::SrvTemplate::Response &res);
};

#endif