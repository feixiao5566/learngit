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
 *Description:  //用于主要说明此程序文件完成的主要功能
                //与其他模块或函数的接口、输出值、取值范围、
                //含义及参数间的控制、顺序、独立及依赖关系
 *Others:  //其他内容说明
 *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
     1.…………
     2.…………
 *History:  //修改历史记录列表，每条修改记录应包含修改日期、修改者及修改内容简介
     1.Date:2015-05-06
       Author:Tian Bo
       Modification:Jiuray RFID reader api
     2.Date:2015-5-11
       Author:feixiao
       Modification:新增字符串处理函数
**********************************************************************************/
#ifndef UHF_RFID_API_H
#define UHF_RFID_API_H
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/select.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <boost/property_tree/ini_parser.hpp>


class UhfRfidReader
{
public:
  UhfRfidReader();
  ~UhfRfidReader();
  void uhfReaderConnect();//读接口
  int uhfInit();
  unsigned char epcbuf24[25];//接口，读到的标签的16进制会转成24个字符存入
  int mybuff[25];//便签值 
  unsigned char itagid[13];
  //const char CMD_SINGLE[7] = {0xAA,0x00,0x22,0x00,0x00,0x22,0x8e};//single
  char CMD_SINGLE[7];//single
  unsigned  char g_testarry[25][28];
private:
  typedef
  enum
  {
      SERIAL_8N1 = 0,
      SERIAL_7E1 = 1,
      SERIAL_7O1 = 2,
      SERIAL_7S1 = 3
  }serial_format;

  struct  timeval timeout;
  fd_set  set_input;
  int fd;
  int ret_select;
  int bytes;
  int write_num;
  int read_num;
  unsigned char buff[25];
  const char * serial_port[1];
  unsigned char* buffer_read();//字串处理函数
  int itoa16(unsigned char* buff);
  int serial_open(int port);
  void serial_format_set(int fd, serial_format format);
  void serial_speed_set(int fd, int baudrate);
  void serial_etc_config(int fd);
  void serial_config(int fd, int baudrate, serial_format format);
};


#endif











