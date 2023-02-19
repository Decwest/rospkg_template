#include "rospkg_template/template.h"

std::string node_name = "template_cpp_node";

Template::Template(ros::NodeHandle &nh, const int &loop_rate, const std::string &base_frame_id)
: nh_(nh), loop_rate_(loop_rate), base_frame_id_(base_frame_id), tfBuffer_(), tfListener_(tfBuffer_)
{ //constructer, define pubsub
    ROS_INFO("Creating template_cpp_node");
    ROS_INFO_STREAM("loop_rate [Hz]: " << loop_rate_);
    ROS_INFO_STREAM("base_frame_id: " << base_frame_id_);

    // TODO: topic communication

    // service communication
    service_server_ = nh_.advertiseService("template_service", &Template::templateService, this);

    // TODO: action communication

    ROS_INFO("template_cpp_node ready");
    update();

    // ros::spin();
}

bool Template::templateService(rospkg_template_msgs::SrvTemplate::Request &req, rospkg_template_msgs::SrvTemplate::Response &res)
{
    res.sum = req.a + req.b;
    ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
    ROS_INFO("sending back response: [%ld]", (long int)res.sum);
    return true;
}

void Template::update()
{ // if use topic communication
    ros::Rate r(loop_rate_);

    while (ros::ok())
    {
        geometry_msgs::TransformStamped transformStamped;
        try
        {
            transformStamped = tfBuffer_.lookupTransform("map", base_frame_id_, ros::Time(0));
        }
        catch (tf2::TransformException& ex)
        {
            ROS_WARN("%s", ex.what());
            return;
        }
        auto& trans = transformStamped.transform.translation; // Vector3
        auto& rotation = transformStamped.transform.rotation; // Quaternion
        ROS_INFO("map->%s: %f %f %f", base_frame_id_.c_str(), trans.x, trans.y, trans.z);

        ros::spinOnce();
        r.sleep();
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, node_name);

    ros::NodeHandle nh;
    ros::NodeHandle arg_n("~");

    // default value
    int looprate = 30; // Hz
    std::string base_frame_id = "base_link";

    arg_n.getParam("control_frequency", looprate);
    arg_n.getParam("base_frame_id", base_frame_id);

    Template template_node(nh, looprate, base_frame_id);
    return 0;
}
