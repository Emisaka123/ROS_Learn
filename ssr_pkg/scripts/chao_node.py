#!/usr/bin/env python3
#coding=utf-8
import rospy
from std_msgs.msg import String

if __name__== "__main__":
  rospy.init_node('chao_node')
  rospy.logwarn("This is a warning message")

  pub = rospy.Publisher('chao_node', String, queue_size=10)

  rate = rospy.Rate(10) # 10hz

  while not rospy.is_shutdown():
    rospy.loginfo("This is an info message")
    msg = String()
    msg.data = "Hello, world!"
    pub.publish(msg)
    rate.sleep()