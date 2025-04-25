#!/usr/bin/env python3
#coding=utf-8
import rospy
from std_msgs.msg import String

def chao_callback(msg):
    rospy.loginfo(msg.data)

def yao_callback(msg):
    rospy.logwarn(msg.data)


if __name__== "__main__":
  rospy.init_node('ma_node')
  
  sub = rospy.Subscriber('chao_node', String, chao_callback, queue_size=10)
  sub2 = rospy.Subscriber('yao_node', String, yao_callback, queue_size=10)
  rospy.spin()