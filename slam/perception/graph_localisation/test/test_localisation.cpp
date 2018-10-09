
#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>

#include <ndt_map/ndt_conversions.h>
#include <pcl_conversions/pcl_conversions.h>
#include <tf_conversions/tf_eigen.h>
#include <Eigen/Eigen>
#include "eigen_conversions/eigen_msg.h"
#include "ndt_generic/utils.h"
#include "pcl/point_cloud.h"

#include "pcl/io/pcd_io.h"
#include "sensor_msgs/PointCloud2.h"

#include <tf/transform_broadcaster.h>
#include <fstream>
#include "message_filters/subscriber.h"
#include "tf/message_filter.h"

#include <geometry_msgs/PoseStamped.h>
#include <laser_geometry/laser_geometry.h>
#include <nav_msgs/Odometry.h>
#include <boost/circular_buffer.hpp>

#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/synchronizer.h>
#include <std_srvs/Empty.h>
#include <visualization_msgs/MarkerArray.h>

#include <ndt_map/NDTMapMsg.h>
#include <boost/foreach.hpp>

#include <time.h>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <cstdio>
#include <fstream>

using namespace std;
int main( int argc, char** argv ) {
    ros::init( argc, argv, "test_localisation" );
    ros::NodeHandle param( "~" );
    cout << "tjosan" << endl;
    ros::spin();

    return 0;
}
