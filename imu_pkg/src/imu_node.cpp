#include<ros/ros.h>
#include<sensor_msgs/Imu.h>
#include<tf/tf.h>
#include<geometry_msgs/Twist.h>

ros::Publisher vel_pub;

void IMUCallback(sensor_msgs::Imu msg)
{
  if(msg.orientation_covariance[0]<0)
  {
    ROS_INFO("IMU数据不可用");
    return;
  }
  tf::Quaternion quaternion(
    msg.orientation.x, 
    msg.orientation.y,
    msg.orientation.z,
    msg.orientation.w
    );
    double roll, pitch, yaw;
    tf::Matrix3x3(quaternion).getRPY(roll, pitch, yaw);
    roll = roll * 180 / M_PI;
    pitch = pitch * 180 / M_PI;
    yaw = yaw * 180 / M_PI;
    ROS_INFO("滚转角: %.0f, 俯仰角: %.0f, 朝向: %.0f", roll, pitch, yaw);

    double target_yaw = 90; // 目标偏航角
    double diff_angle = target_yaw - yaw; // 计算偏航角差
    geometry_msgs::Twist vel_cmd;
    vel_cmd.angular.z = diff_angle*0.01;
    vel_cmd.linear.x=0.1;// 设置线速度
    vel_pub.publish(vel_cmd);  // 发布速度指令
  }
int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");//设置中文显示
    ros::init(argc, argv, "imu_node");//初始化节点
    ros::NodeHandle nh;//创建节点句柄
    ros::Subscriber imu_sub = nh.subscribe("/imu/data", 10, IMUCallback);//订阅IMU数据 {
    vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);//发布速度指令
    ros::spin();//循环等待回调函数
    return 0;
}