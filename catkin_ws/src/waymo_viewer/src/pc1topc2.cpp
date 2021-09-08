#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <pluginlib/class_list_macros.h>

namespace waymo_viewer
{
class pc1topc2 : public nodelet::Nodelet
{
public:
    virtual void onInit();
    void cloud_cb(const sensor_msgs::PointCloudConstPtr& cloud_msg);
private:
    ros::NodeHandle nh_;
    ros::Publisher pub_;
    ros::Subscriber sub_;
};

void pc1topc2::onInit()
{
    // Initialize ROS
    NODELET_INFO("pc1_to_pc2");
    //ros::init (argc, argv, "pc1_to_pc2");
    nh_ = getNodeHandle();

    // Create a ROS subscriber for the input point cloud
    sub_ = nh_.subscribe ("/lidar_pointcloud/top", 1, &pc1topc2::cloud_cb, this);
    // Create a ROS publisher for the output point cloud
    //pub_ = nh_.advertise<sensor_msgs::PointCloud2> ("/sensing/lidar/top/rectified/pointcloud", 1);
    pub_ = nh_.advertise<sensor_msgs::PointCloud2> ("/test", 1);
}

void pc1topc2::cloud_cb (const sensor_msgs::PointCloudConstPtr& cloud_msg)
{
    sensor_msgs::PointCloud cloud1;
    sensor_msgs::PointCloud2 cloud2;
    sensor_msgs::convertPointCloudToPointCloud2(*cloud_msg, cloud2);
     
    // Publish the data
    pub_.publish (cloud2);
}
}
PLUGINLIB_EXPORT_CLASS(waymo_viewer::pc1topc2, nodelet::Nodelet);

