#include<ros/ros.h>
#include<nav_msgs/OccupancyGrid.h>


int main(int argc, char **argv){
    ros::init(argc, argv, "map_pub_node");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<nav_msgs::OccupancyGrid>("/map", 10);
    ros::Rate loop_rate(1); // 1 Hz
    while(ros::ok()){
      nav_msgs::OccupancyGrid msg;
      msg.header.frame_id = "map";
      msg.header.stamp = ros::Time::now();
      msg.info.origin.position.x = 0.0;
      msg.info.origin.position.y = 0.0;
      msg.info.resolution = 1.0;
      msg.info.width = 4;
      msg.info.height = 2;

      msg.data.resize(4*2);
      msg.data[0] = 100;
      msg.data[1] = 100;
      msg.data[3] = -1;
      pub.publish(msg);
      loop_rate.sleep();
    }
     return 0;
 }