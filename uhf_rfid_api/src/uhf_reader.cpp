/*********************************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2015, Tasbot, Inc.
 *  All rights reserved.
 *
 *FileName:  uhf_inventory_single_tag.cpp
 *Author:  feixiao5566 feixiao5566@126.com
 *Version:  0.3
 *Date:  2015-06-01
 *Description:  //收到18次数据，停止5s发送STOPSTOPSTOP模拟机器人停止前进
                //与其他模块或函数的接口、输出值、取值范围、
                //含义及参数间的控制、顺序、独立及依赖关系
 *Others:  此文件仅为接收话题的测试文件
 *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
     1.…………
     2.…………
 *History:  //修改历史记录列表，每条修改记录应包含修改日期、修改者及修改内容简介
     1.Date:2015-5-13
       Author:feixiao
       Modification:接收话题消息，
     2.Date:2015-5-22
       Author:feixiao
       Modification:delete something unnecessary
**********************************************************************************/
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "uhf_rfid_api/UhfRfid.h"

int i = 0;
void chatterCallback(const uhf_rfid_api::UhfRfid::ConstPtr& msg)
{
  ros::Rate rate(1);// sleep 1s
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}
int main(int argc, char **argv)
{
  int i = 0;
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("messageepc", 1000, chatterCallback);
  ros::spin();
  return 0;
}
