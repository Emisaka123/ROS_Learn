#include<ros/ros.h>
#include<std_msgs/String.h>
#include<qq_msgs/Carry.h>//自定义消息

void chao_callback( qq_msgs::Carry msg)
{
  ROS_WARN(msg.grade.c_str());
  ROS_WARN("star: %d星", msg.star);
  ROS_INFO(msg.data.c_str());
}

void yao_callback(std_msgs::String msg)
{
  ROS_WARN(msg.data.c_str());
}
int main(int argc, char **argv)
{
  setlocale(LC_ALL,"");//设置中文显示
  ros::init(argc, argv, "ma_node");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("chao_node", 10,chao_callback);
  ros::Subscriber sub1 = nh.subscribe("yao_node", 10,yao_callback);
  while(ros::ok())
  {
    ros::spinOnce();//功能：处理回调函数
  }
     return 0;
}