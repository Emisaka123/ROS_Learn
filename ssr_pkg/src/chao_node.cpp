#include<ros/ros.h>
#include<std_msgs/String.h>
#include<qq_msgs/Carry.h>//自定义消息

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "chao_node");
    printf("你已经成功编译了一个ROS节点\n");

    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<qq_msgs::Carry>("chao_node", 10);//发布话题
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
       printf("你已经成功编译了一个ROS节点！\n");
       qq_msgs::Carry msg;
       msg.grade = "king";//自定义消息
       msg.star =50;//自定义消息
       msg.data = "Hello, ROS!";
       pub.publish(msg);
       loop_rate.sleep();
    }
    return 0;
}