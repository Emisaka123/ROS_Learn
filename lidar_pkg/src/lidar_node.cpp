#include<ros/ros.h>
#include<sensor_msgs/LaserScan.h>
void LidarCallback(const sensor_msgs::LaserScan msg)
{

    float fMidDist = msg.ranges[180];//获取前方180度的测距值
    ROS_INFO("前方测距 ranges[180]: %f 米", fMidDist);//打印前方测距值
}
int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");//设置中文显示
    ros::init(argc, argv, "lidar_node");//初始化节点
    ros::NodeHandle nh;//创建节点句柄
    ros::Subscriber lidar_sub = nh.subscribe("/scan", 10, &LidarCallback);//订阅激光雷达数据
    ros::spin();//循环等待回调函数
    return 0;
}