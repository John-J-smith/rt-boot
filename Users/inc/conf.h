/****************************************************************
Description: Config.h
Author: shijj
Notes: 配置文件
*****************************************************************/
#ifndef __CONFIG_H
#define __CONFIG_H

#define __task                  //标记任务函数

//单片机flash
#define ADDR_BOOT_START     (0x0UL)
#define ADDR_BOOT_END       (0xFFFFUL) //64KB
#define BOOT_IMAGE_SIZE     (ADDR_BOOT_END - ADDR_BOOT_START)

#define ADDR_APP_START      0x10000UL
#define ADDR_APP_END        (0x7FFFFUL)//448kb
#define APP_IMAGE_SIZE      (ADDR_APP_END - ADDR_APP_START) 

#define ApplicationAddress  ADDR_APP_START


// 参数长度
#define APN_LEN                 (16)
#define PHONE_NUMBER_LEN        (20)
#define PORT_LEN                (6)
#define IP_LEN                  (16)
#define SOCK_TYPE_LEN           (7)
#define HOST_LEN                (20)
#define USER_NAME_LEN           (10)
#define PSW_LEN                 (10)
#define PATH_LEN                (20)
#define IMEI_LEN                (18)
#define BAND_LEN                (18)
#define URI_LEN                 (18)

#endif

