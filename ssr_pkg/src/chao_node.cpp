#include<ros/ros.h>
#include<std_msgs/String.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "chao_node");
    printf("你已经成功编译了一个ROS节点\n");

    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::String>("chao_node", 10);
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
       printf("你已经成功编译了一个ROS节点！\n");
       std_msgs::String msg;
       msg.data = "Hello, ROS!";
       pub.publish(msg);
       loop_rate.sleep();
    }
    return 0;
}