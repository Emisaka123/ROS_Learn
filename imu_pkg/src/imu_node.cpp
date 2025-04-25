#include<ros/ros.h>
#include<sensor_msgs/Imu.h>
#include<tf/tf.h>

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
    ROS_INFO("滚转角: %f, 俯仰角: %f, 偏航角: %f", roll, pitch, yaw);

}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");//设置中文显示
    ros::init(argc, argv, "imu_node");//初始化节点
    ros::NodeHandle nh;//创建节点句柄
    ros::Subscriber imu_sub = nh.subscribe("/imu/data", 10, IMUCallback);//订阅IMU数据 {
        // 打印IMU数据
    ros::spin();//循环等待回调函数
    return 0;
}