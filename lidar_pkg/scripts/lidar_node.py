#!/usr/bin/env python3
#coding=utf-8
import rospy
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist

count = 0

def LidarCallback(msg):
    global vel_pub
    global count
    dist = msg.ranges[180]
    rospy.loginfo("前方测距 ranges[180]:=  %f 米！", dist)
    vel_cmd = Twist()
    if count > 0:
        count -= 1
        return

    if dist < 1.5:
        vel_cmd.linear.x = 0.0
        vel_cmd.angular.z = 0.3
        count = 50
        rospy.loginfo("前方障碍物过近，停止前进！")
    else:
        vel_cmd.linear.x = 0.05
        vel_cmd.angular.z = 0.0
        rospy.loginfo("前方无障碍物，继续前进！")
    vel_pub.publish(vel_cmd)


if __name__ == '__main__':
    # 初始化ROS节点
    rospy.init_node('lidar_node')
    #创建一个接收器，订阅激光雷达数据
    lidar_sub = rospy.Subscriber('/scan', LaserScan,LidarCallback, queue_size=10)
    vel_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10) 
    rospy.spin()