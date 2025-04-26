#include<ros/ros.h>
#include<sensor_msgs/LaserScan.h>
#include<geometry_msgs/Twist.h>//引入几何消息库
ros::Publisher vel_pub;//定义速度指令发布器
int nCount = 0;//定义计数器
void LidarCallback(const sensor_msgs::LaserScan msg)
{

    float fMidDist = msg.ranges[180];//获取前方180度的测距值
    ROS_INFO("前方测距 ranges[180]: %f 米", fMidDist);//打印前方测距值
   
    if (nCount > 0)//如果计数器大于0
    {
        nCount--;//计数器减1
       return;//返回
    }
    

    geometry_msgs::Twist vel_cmd;//定义速度指令
    if(fMidDist < 1.5)//如果前方距离小于0.5米
    {
        vel_cmd.linear.x = 0.0;//停止前进
        vel_cmd.angular.z = 0.3;//向右转
        ROS_INFO("前方障碍物，停止前进，向右转");//打印信息
        nCount=50;
    }
    else 
    {
        vel_cmd.linear.x = 0.5;//前进
        vel_cmd.angular.z = 0.0;//不转向
        ROS_INFO("前方无障碍物，继续前进");//打印信息
    }
    vel_pub.publish(vel_cmd);//发布速度指令
}


int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");//设置中文显示
    ros::init(argc, argv, "lidar_node");//初始化节点
    ros::NodeHandle nh;//创建节点句柄
    ros::Subscriber lidar_sub = nh.subscribe("/scan", 10, &LidarCallback);//订阅激光雷达数据
    vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);//发布速度指令
    ros::spin();//循环等待回调函数
    return 0;
}