/******************************************************************************
 Copyright (C) Aug.2，2004  R&D Institute of Reallin Co., Ltd.
 Module         : 存储器定义头文件..
 File Name      : EEPROM.h
 Description    :
 Author         : liu shun
 Build Date     :
 others         :
         EEPROM : 24LC512
       地址空间 ：0x0000~0xFFFF
 ------------------------------------------------------------------------------
 Modification History:
 <No.> <version >  <time>        <author>     <contents>
  3、
  2、    1.10     2008-01-07    liu shun     modified this moudle
  1、    1.00     2007-06-20    liu shun     build this moudle
******************************************************************************/
/* 1 ------------------------------------------------------------------------
 宏常数值定义
-------------------------------------------------------------------------- */
/* 1 end------------------------------------------------------------------ */

/* 2 ------------------------------------------------------------------------
 eeprom_a地址定义
-------------------------------------------------------------------------- */
#ifndef    _EEPROM_H
#define    _EEPROM_H

#define  OP_EEPROM				2
#define  OP_FM					1
#define  OP_ON_CHIP_FLASH		0
#define  OP_DATA_FLASH			3
#define  OP_ALL_MEM				4

typedef enum
{
    EEPROM_HEAD_ADDR = (OP_EEPROM << 24),
    FRAM_HEAD_ADDR = (OP_FM << 24),
    MCUROM_HEAD_ADDR = (OP_ON_CHIP_FLASH << 24),
    DF_HEAD_ADDR = (OP_DATA_FLASH << 24),
} ENUM_MEMORY_HEAD; /*存储器地址分类*/

/******************************************************************************
*                                 第0-1页                                   *
******************************************************************************/
#define METER_INFO_EE                           (EEPROM_HEAD_ADDR + 0x80*0)
#define METER_LOG_DEC_NAME_LEN                  (METER_INFO_EE) //1byte
#define METER_LOG_DEC_NAME                      (METER_LOG_DEC_NAME_LEN + 1) //max 20 bytes
#define METER_SERIAL_NUM_EE                     (METER_LOG_DEC_NAME + 20)
#define ADDR_METER_MODEL                        (METER_SERIAL_NUM_EE + 20)
#define ADDR_SEC_ITEM_NUM                       (ADDR_METER_MODEL + 8)
#define METER_FW_VERSION_EE                     (ADDR_SEC_ITEM_NUM + 9)
#define ADDR_MODULE_SN_EE                       (METER_FW_VERSION_EE + 20)
#define ADDR_NORMINAL_VOLTAGE_EE                (ADDR_MODULE_SN_EE + 20)
#define ADDR_NORMINAL_CURRENT_EE                (ADDR_NORMINAL_VOLTAGE_EE + 4)
#define ADDR_MAX_CURRENT_EE                     (ADDR_NORMINAL_CURRENT_EE + 4)
#define ADDR_HARD_VARSION_EE                    (ADDR_MAX_CURRENT_EE + 4)//32字节
#define ADDR_MODULE_TYPE                        (ADDR_HARD_VARSION_EE + 32)//8字节
#define ADDR_Manfactory_EE                      (ADDR_MODULE_TYPE + 8)//预留16字节

/******************************************************************************
*                                 第2页         	*密码
******************************************************************************/
#define SECT_2EE                                (EEPROM_HEAD_ADDR + 0x80*2)
/* Security setup for Association ........................................... */
#define SECURITY_SETUP_SECT                     SECT_2EE
#define ClientSecurityTitle_EE                  (SECURITY_SETUP_SECT)          /*  8 字节  */
#define SecretForLLS_LEN_EE                     (ClientSecurityTitle_EE + 8)   /*  1 字节  */
#define SecretForLLS_EE                         (SecretForLLS_LEN_EE + 1)      /*  16 字节  */
#define SecurityPolicy_EE                       (SecretForLLS_EE + 16)         /*  1 字节  */
#define SecuritySuit_EE                         (SecurityPolicy_EE + 1)        /*  1 字节  */
#define UnicastEncryptionKey_EE                 (SecuritySuit_EE + 1)          /*  16 字节  */
#define BroadcastEncryptionKey_EE               (UnicastEncryptionKey_EE + 16)  /*  16 字节  */
#define AuthenticationKey_EE                    (BroadcastEncryptionKey_EE + 16)/*  16 字节  */
#define MasterKey_EE                            (AuthenticationKey_EE + 16)    /*  16 字节  */
#define DataTransPortSecurityMode_EE            (MasterKey_EE + 16)            /*  1 字节  */
#define AuthMechnism_EE                         (DataTransPortSecurityMode_EE + 1)  /*  1 字节 目前只支持1和5 */


/******************************************************************************
*                                 第3页         	*掉电保存数据
******************************************************************************/
#define ADDR_POWER_DOWN_INFO                    (EEPROM_HEAD_ADDR + 0x80*3)
#define ADDR_STATUS_WORD                        (ADDR_POWER_DOWN_INFO)
#define ADDR_AA_IC_EE                           (ADDR_STATUS_WORD + sizeof(UN_Err_Byte))
#define ADDR_ECCU_REG_PUSH                      (ADDR_AA_IC_EE + sizeof(ST_EACH_CHNL_IC))
#define ADDR_ContactorStatus_EE                 (ADDR_ECCU_REG_PUSH + sizeof(UN_Err_Byte))
#define ADDR_POWER_DOWN_TIME_EE                 (ADDR_ContactorStatus_EE + 1)//12字节



/******************************************************************************
*                                 第4页    继电器参数和状态相关                     *
******************************************************************************/
#define ADDR_ContactorControlMode_EE                (EEPROM_HEAD_ADDR + 0x80*4)
#define ADDR_STATE_OUT_RELAY_SIGNAL                 (ADDR_ContactorControlMode_EE + 1) /*  1 字节  */
#define ADDR_SELECT_IN_SIGNAL                 		(ADDR_STATE_OUT_RELAY_SIGNAL + 1) /*  1 字节  */
#define ADDR_CURRENT_OVER_RECOVER_SETTING_TIMES    	(ADDR_SELECT_IN_SIGNAL + 1) /*  2 字节  */
#define ADDR_CURRENT_OVER_RECOVER_OPERATE_TIMES    	(ADDR_CURRENT_OVER_RECOVER_SETTING_TIMES + 2) /*  2 字节  */
#define ADDR_CURRENT_OVER_RELEASE_SETTING_TIMES   	(ADDR_CURRENT_OVER_RECOVER_OPERATE_TIMES + 2) /*  2 字节  */
#define ADDR_RELAT_CTRL_SET_TIME                    (ADDR_CURRENT_OVER_RELEASE_SETTING_TIMES + 2)//2字节 单位 100us
#define ADDR_RELAT_REALEASE_SET_TIME                (ADDR_RELAT_CTRL_SET_TIME + 2)//2字节 单位 100us
#define ADDR_RELAT_NEXT_CTRL_SET_TIME               (ADDR_RELAT_REALEASE_SET_TIME + 2)//2字节 单位 100us
#define ADDR_RELAYCTRL_EE                			(ADDR_RELAT_NEXT_CTRL_SET_TIME + 2)  /*  1 字节  */
#define ADDR_RELAYOPENREASON_EE                		(ADDR_RELAYCTRL_EE + 1)  /*  2 字节  */
#define ADDR_RELAYSTATUS_EE                			(ADDR_RELAYOPENREASON_EE + 2)  /*  2 字节  */
#define ADDR_RELAYFLAG_EE                			(ADDR_RELAYSTATUS_EE + 2)  /*  2 字节  */
#define ADDR_PLY2STATE                        		(ADDR_RELAYFLAG_EE + 2) /*  1 字节  */
#define ADDR_PLY2pluseTimeCfg                       (ADDR_PLY2STATE + 1) /*继电器控制时间，1字节*/
#define ADDR_PLY2RepeatCNT                          (ADDR_PLY2pluseTimeCfg + 1)// 1字节


/********************************************************************************
*                                 第5页   主站类型等参数，这一页不允许调整位置                                *
*********************************************************************************/
#define ADDR_HES_Type                           (EEPROM_HEAD_ADDR + 0x80*5)//占用4个字节
#define ADDR_Temperature_Option                 (ADDR_HES_Type + 4)// 1个字节
#define ADDR_NariHES_LoginFLAG_EE               (ADDR_Temperature_Option + 1)// 4个字节
#define ADDR_STO1_EE                            (ADDR_NariHES_LoginFLAG_EE + 4)// 8个字节


/******************************************************************************
*                                 第6页    	class41   TCP-UDP setup
******************************************************************************/
#define          SECT_6EE                         	(EEPROM_HEAD_ADDR + 0x80*6)
#define          ADDR_TCPUDP_SET                        SECT_6EE
#define          ADDR_TCPUDP_PORT                       ADDR_TCPUDP_SET
#define          ADDR_IP_Reference_LEN                  (ADDR_TCPUDP_PORT + 2)
#define          ADDR_IP_Reference                      (ADDR_IP_Reference_LEN + 1)//预留64字节
#define          ADDR_MSS                               (ADDR_IP_Reference + 64)
#define          ADDR_NB_SIM_CONN                       (ADDR_MSS + 2)//1字节
#define          ADDR_TCP_UDP_INACTIVITY_TIME_OUT       (ADDR_NB_SIM_CONN + 1)//2字节


/******************************************************************************
*                                 第7页-9页    	class42  IPv4 setup
******************************************************************************/
#define          SECT_7EE                         	(EEPROM_HEAD_ADDR + 0x80*7)
#define          ADDR_IPV4_SET                          SECT_7EE
#define          ADDR_IPV4_DL_REFERENCE_LEN             ADDR_IPV4_SET
#define          ADDR_IPV4_DL_REFERENCE                 (ADDR_IPV4_DL_REFERENCE_LEN + 1)//预留64字节
#define          ADDR_IPV4_Addr                         (ADDR_IPV4_DL_REFERENCE + 64)//4个字节
#define          ADDR_MUL_IPV4_Addr_NUM                 (ADDR_IPV4_Addr + 4)
#define          ADDR_MUL_IPV4_Addr                     (ADDR_MUL_IPV4_Addr_NUM + 1)//预留5个Array，共20字节
#define          ADDR_IPV4_OPTION_NUM                   (ADDR_MUL_IPV4_Addr + 20)
#define          ADDR_IPV4_OPTION                       (ADDR_IPV4_OPTION_NUM + 1)//预留5个Array，共170字节(1 + 1 + 32) * 5
#define          ADDR_SUBNET_MASK                       (ADDR_IPV4_OPTION + 170)//4个字节
#define          ADDR_Gateway_IP_Addr                   (ADDR_SUBNET_MASK + 4)//4个字节
#define          ADDR_USE_DHCP_Flag                     (ADDR_Gateway_IP_Addr + 4)//1个字节
#define          ADDR_IPV4_PRIMARY_DNS_Addr             (ADDR_USE_DHCP_Flag + 1)//4个字节
#define          ADDR_IPV4_SECONDARY_DNS_Addr           (ADDR_IPV4_PRIMARY_DNS_Addr + 4)//4个字节



/******************************************************************************
*								  第10 - 14页 	class44  PPP setup
******************************************************************************/
#define          SECT_10EE                         	(EEPROM_HEAD_ADDR + 0x80*10)
#define          ADDR_PPP_SET                           SECT_10EE
#define          ADDR_PHY_REFERENCE_LEN                 ADDR_PPP_SET
#define          ADDR_PHY_REFERENCE                     (ADDR_PHY_REFERENCE_LEN + 1)//预留64字节
#define          ADDR_LCP_OPTION_NUM                    (ADDR_PHY_REFERENCE + 64)//1字节
#define          ADDR_LCP_OPTION_TYPE                   (ADDR_LCP_OPTION_NUM + 1)//4字节 2 * (格式(1字节) +       octring个数(1字节))
#define          ADDR_LCP_OPTION                        (ADDR_LCP_OPTION_TYPE + 4)//预留140字节 只支持2个array
#define          ADDR_IPCP_OPTION_NUM                   (ADDR_LCP_OPTION + 140)//1字节
#define          ADDR_IPCP_OPTION_TYPE                  (ADDR_IPCP_OPTION_NUM + 1)//4字节 2 * (格式(1字节) + array个数(1字节))
#define          ADDR_IPCP_OPTION                       (ADDR_IPCP_OPTION_TYPE + 4)//预留180字节 只支持2个array
#define          ADDR_PPP_AUTHENATION_TYPE              (ADDR_IPCP_OPTION + 180)//1字节
#define          ADDR_PPP_STRUCT_TYPE                   (ADDR_PPP_AUTHENATION_TYPE + 1)//1字节
#define          ADDR_PPP_AUTHE_NAME_LEN                (ADDR_PPP_STRUCT_TYPE + 1)//1字节
#define          ADDR_PPP_AUTHE_PASSWORD_LEN            (ADDR_PPP_AUTHE_NAME_LEN + 1)//1字节
#define          ADDR_PPP_AUTHE_NAME                    (ADDR_PPP_AUTHE_PASSWORD_LEN + 1)//共预留64字节


/******************************************************************************
*								  第15页 	class45  GPRS modem setup
******************************************************************************/
#define          SECT_15EE                         	(EEPROM_HEAD_ADDR + 0x80*15)
#define          ADDR_GPRS_modem_SET                    SECT_15EE
#define          ADDR_APN_LEN                           ADDR_GPRS_modem_SET
#define          ADDR_APN_OCTRING                       (ADDR_APN_LEN + 1)
#define          ADDR_PIN_CODE                          (ADDR_APN_OCTRING + 32)
#define          ADDR_QOS_SERVICE                       (ADDR_PIN_CODE + 2)//10个字节



/******************************************************************************
*								  第16 - 22页 	class48  IPv6 setup
******************************************************************************/
#define          SECT_16EE                         	(EEPROM_HEAD_ADDR + 0x80*16)
#define          ADDR_IPV6_SET                          SECT_16EE
#define          ADDR_IPV6_DL_REFERENCE_LEN             ADDR_IPV6_SET
#define          ADDR_IPV6_DL_REFERENCE                 (ADDR_IPV6_DL_REFERENCE_LEN + 1)//预留64字节
#define          ADDR_CONFIG_MODE                       (ADDR_IPV6_DL_REFERENCE + 64)
#define          ADDR_UNICAST_IPV6Addr_NUM              (ADDR_CONFIG_MODE + 1)
#define          ADDR_UNICAST_IPV6Addr_OCT_LEN          (ADDR_UNICAST_IPV6Addr_NUM + 1)//5个字节
#define          ADDR_UNICAST_IPV6Addr                  (ADDR_UNICAST_IPV6Addr_OCT_LEN + 5)//预留3个array，共150字节
#define          ADDR_MUL_UNICAST_IPV6Addr_NUM          (ADDR_UNICAST_IPV6Addr + 150)
#define          ADDR_MUL_UNICAST_IPV6Addr_OCT_LEN      (ADDR_MUL_UNICAST_IPV6Addr_NUM + 1)
#define          ADDR_MUL_UNICAST_IPV6Addr              (ADDR_MUL_UNICAST_IPV6Addr_OCT_LEN + 5)//预留3个array，共150字节
#define          ADDR_GATEWAY_IPV6Addr_NUM              (ADDR_MUL_UNICAST_IPV6Addr + 150)
#define          ADDR_GATEWAY_IPV6Addr_OCT_LEN          (ADDR_GATEWAY_IPV6Addr_NUM + 1)
#define          ADDR_GATEWAY_IPV6Addr                  (ADDR_GATEWAY_IPV6Addr_OCT_LEN + 5)//预留3个array，共150字节
#define          ADDR_IPV6_PRIMARY_DNS_Addr_LEN         (ADDR_GATEWAY_IPV6Addr + 150)//1个字节
#define          ADDR_IPV6_PRIMARY_DNS_Addr             (ADDR_IPV6_PRIMARY_DNS_Addr_LEN + 1)//50个字节
#define          ADDR_IPV6_SECONDARY_DNS_Addr_LEN       (ADDR_IPV6_PRIMARY_DNS_Addr + 50)//1个字节
#define          ADDR_IPV6_SECONDARY_DNS_Addr           (ADDR_IPV6_SECONDARY_DNS_Addr_LEN + 1)//50个字节
#define          ADDR_TRAFFIC_CLASS                     (ADDR_IPV6_SECONDARY_DNS_Addr + 50)//1个字节
#define          ADDR_NEIGHBOR_NUM                      (ADDR_TRAFFIC_CLASS + 1)//1个字节
#define          ADDR_NEIGHBOR_discover                 (ADDR_NEIGHBOR_NUM + 1)//预留8个array，共56字节



/******************************************************************************
*                                 第23-36页   6.5和7.0规约指针              *
******************************************************************************/
#define EVN_PWR_FAIL_PROFILE_PARA_EE                    (EEPROM_HEAD_ADDR + 0x80*23)
#define EVN_PWR_FAIL_READ_CTRL_EE                       (EVN_PWR_FAIL_PROFILE_PARA_EE)//10bytes
#define EVN_PWR_FAIL_Capture_Period_EE                  (EVN_PWR_FAIL_PROFILE_PARA_EE + 10)//4bytes
#define EVN_PWR_FAIL_entries_in_use_EE                  (EVN_PWR_FAIL_PROFILE_PARA_EE + 14)//4bytes
#define EVN_PWR_FAIL_profile_entries_EE                 (EVN_PWR_FAIL_PROFILE_PARA_EE + 18)//4bytes
#define EVN_PWR_FAIL_Capture_Num_EE                     (EVN_PWR_FAIL_PROFILE_PARA_EE + 22)//1bytes
#define EVN_PWR_FAIL_Capture_Obj_EE                     (EVN_PWR_FAIL_PROFILE_PARA_EE + 23)

#define EVN_PWR_ON_PROFILE_PARA_EE                      (EEPROM_HEAD_ADDR + 0x80*24)
#define EVN_PWR_ON_READ_CTRL_EE                         (EVN_PWR_ON_PROFILE_PARA_EE)//10bytes
#define EVN_PWR_ON_Capture_Period_EE                    (EVN_PWR_ON_PROFILE_PARA_EE + 10)//4bytes
#define EVN_PWR_ON_entries_in_use_EE                    (EVN_PWR_ON_PROFILE_PARA_EE + 14)//4bytes
#define EVN_PWR_ON_profile_entries_EE                   (EVN_PWR_ON_PROFILE_PARA_EE + 18)//4bytes
#define EVN_PWR_ON_Capture_Num_EE                       (EVN_PWR_ON_PROFILE_PARA_EE + 22)//1bytes
#define EVN_PWR_ON_Capture_Obj_EE                       (EVN_PWR_ON_PROFILE_PARA_EE + 23)

#define EVN_SYNC_B_PROFILE_PARA_EE                      (EEPROM_HEAD_ADDR + 0x80*25)
#define EVN_SYNC_B_READ_CTRL_EE                         (EVN_SYNC_B_PROFILE_PARA_EE)//10bytes
#define EVN_SYNC_B_Capture_Period_EE                    (EVN_SYNC_B_PROFILE_PARA_EE + 10)//4bytes
#define EVN_SYNC_B_entries_in_use_EE                    (EVN_SYNC_B_PROFILE_PARA_EE + 14)//4bytes
#define EVN_SYNC_B_profile_entries_EE                   (EVN_SYNC_B_PROFILE_PARA_EE + 18)//4bytes
#define EVN_SYNC_B_Capture_Num_EE                       (EVN_SYNC_B_PROFILE_PARA_EE + 22)//1bytes
#define EVN_SYNC_B_Capture_Obj_EE                       (EVN_SYNC_B_PROFILE_PARA_EE + 23)

#define EVN_SYNC_A_PROFILE_PARA_EE                      (EEPROM_HEAD_ADDR + 0x80*26)
#define EVN_SYNC_A_READ_CTRL_EE                         (EVN_SYNC_A_PROFILE_PARA_EE)//10bytes
#define EVN_SYNC_A_Capture_Period_EE                    (EVN_SYNC_A_PROFILE_PARA_EE + 10)//4bytes
#define EVN_SYNC_A_entries_in_use_EE                    (EVN_SYNC_A_PROFILE_PARA_EE + 14)//4bytes
#define EVN_SYNC_A_profile_entries_EE                   (EVN_SYNC_A_PROFILE_PARA_EE + 18)//4bytes
#define EVN_SYNC_A_Capture_Num_EE                       (EVN_SYNC_A_PROFILE_PARA_EE + 22)//1bytes
#define EVN_SYNC_A_Capture_Obj_EE                       (EVN_SYNC_A_PROFILE_PARA_EE + 23)

#define EVN_EOB_RST_PROFILE_PARA_EE                     (EEPROM_HEAD_ADDR + 0x80*27)
#define EVN_EOB_RST_READ_CTRL_EE                        (EVN_EOB_RST_PROFILE_PARA_EE)//10bytes
#define EVN_EOB_RST_Capture_Period_EE                   (EVN_EOB_RST_PROFILE_PARA_EE + 10)//4bytes
#define EVN_EOB_RST_entries_in_use_EE                   (EVN_EOB_RST_PROFILE_PARA_EE + 14)//4bytes
#define EVN_EOB_RST_profile_entries_EE                  (EVN_EOB_RST_PROFILE_PARA_EE + 18)//4bytes
#define EVN_EOB_RST_Capture_Num_EE                      (EVN_EOB_RST_PROFILE_PARA_EE + 22)//1bytes
#define EVN_EOB_RST_Capture_Obj_EE                      (EVN_EOB_RST_PROFILE_PARA_EE + 23)

#define EVN_EOB_M_PROFILE_PARA_EE                       (EEPROM_HEAD_ADDR + 0x80*28)
#define EVN_EOB_M_READ_CTRL_EE                          (EVN_EOB_M_PROFILE_PARA_EE)//10bytes
#define EVN_EOB_M_Capture_Period_EE                     (EVN_EOB_M_PROFILE_PARA_EE + 10)//4bytes
#define EVN_EOB_M_entries_in_use_EE                     (EVN_EOB_M_PROFILE_PARA_EE + 14)//4bytes
#define EVN_EOB_M_profile_entries_EE                    (EVN_EOB_M_PROFILE_PARA_EE + 18)//4bytes
#define EVN_EOB_M_Capture_Num_EE                        (EVN_EOB_M_PROFILE_PARA_EE + 22)//1bytes
#define EVN_EOB_M_Capture_Obj_EE                        (EVN_EOB_M_PROFILE_PARA_EE + 23)

#define EVN_AUTO_PROFILE_PARA_EE                        (EEPROM_HEAD_ADDR + 0x80*29)
#define EVN_AUTO_READ_CTRL_EE                           (EVN_AUTO_PROFILE_PARA_EE)//10bytes
#define EVN_AUTO_Capture_Period_EE                      (EVN_AUTO_PROFILE_PARA_EE + 10)//4bytes
#define EVN_AUTO_entries_in_use_EE                      (EVN_AUTO_PROFILE_PARA_EE + 14)//4bytes
#define EVN_AUTO_profile_entries_EE                     (EVN_AUTO_PROFILE_PARA_EE + 18)//4bytes
#define EVN_AUTO_Capture_Num_EE                         (EVN_AUTO_PROFILE_PARA_EE + 22)//1bytes
#define EVN_AUTO_Capture_Obj_EE                         (EVN_AUTO_PROFILE_PARA_EE + 23)

#define EVN_ERR1_PROFILE_PARA_EE                        (EEPROM_HEAD_ADDR + 0x80*30)
#define EVN_ERR1_READ_CTRL_EE                           (EVN_ERR1_PROFILE_PARA_EE)//10bytes
#define EVN_ERR1_Capture_Period_EE                      (EVN_ERR1_PROFILE_PARA_EE + 10)//4bytes
#define EVN_ERR1_entries_in_use_EE                      (EVN_ERR1_PROFILE_PARA_EE + 14)//4bytes
#define EVN_ERR1_profile_entries_EE                     (EVN_ERR1_PROFILE_PARA_EE + 18)//4bytes
#define EVN_ERR1_Capture_Num_EE                         (EVN_ERR1_PROFILE_PARA_EE + 22)//1bytes
#define EVN_ERR1_Capture_Obj_EE                         (EVN_ERR1_PROFILE_PARA_EE + 23)

#define EVN_ERR2_PROFILE_PARA_EE                        (EEPROM_HEAD_ADDR + 0x80*31)
#define EVN_ERR2_READ_CTRL_EE                           (EVN_ERR2_PROFILE_PARA_EE)//10bytes
#define EVN_ERR2_Capture_Period_EE                      (EVN_ERR2_PROFILE_PARA_EE + 10)//4bytes
#define EVN_ERR2_entries_in_use_EE                      (EVN_ERR2_PROFILE_PARA_EE + 14)//4bytes
#define EVN_ERR2_profile_entries_EE                     (EVN_ERR2_PROFILE_PARA_EE + 18)//4bytes
#define EVN_ERR2_Capture_Num_EE                         (EVN_ERR2_PROFILE_PARA_EE + 22)//1bytes
#define EVN_ERR2_Capture_Obj_EE                         (EVN_ERR2_PROFILE_PARA_EE + 23)

#define EVN_ERR3_PROFILE_PARA_EE                        (EEPROM_HEAD_ADDR + 0x80*32)
#define EVN_ERR3_READ_CTRL_EE                           (EVN_ERR3_PROFILE_PARA_EE)//10bytes
#define EVN_ERR3_Capture_Period_EE                      (EVN_ERR3_PROFILE_PARA_EE + 10)//4bytes
#define EVN_ERR3_entries_in_use_EE                      (EVN_ERR3_PROFILE_PARA_EE + 14)//4bytes
#define EVN_ERR3_profile_entries_EE                     (EVN_ERR3_PROFILE_PARA_EE + 18)//4bytes
#define EVN_ERR3_Capture_Num_EE                         (EVN_ERR3_PROFILE_PARA_EE + 22)//1bytes
#define EVN_ERR3_Capture_Obj_EE                         (EVN_ERR3_PROFILE_PARA_EE + 23)

#define EVN_ERR5_PROFILE_PARA_EE                        (EEPROM_HEAD_ADDR + 0x80*33)
#define EVN_ERR5_READ_CTRL_EE                           (EVN_ERR5_PROFILE_PARA_EE)//10bytes
#define EVN_ERR5_Capture_Period_EE                      (EVN_ERR5_PROFILE_PARA_EE + 10)//4bytes
#define EVN_ERR5_entries_in_use_EE                      (EVN_ERR5_PROFILE_PARA_EE + 14)//4bytes
#define EVN_ERR5_profile_entries_EE                     (EVN_ERR5_PROFILE_PARA_EE + 18)//4bytes
#define EVN_ERR5_Capture_Num_EE                         (EVN_ERR5_PROFILE_PARA_EE + 22)//1bytes
#define EVN_ERR5_Capture_Obj_EE                         (EVN_ERR5_PROFILE_PARA_EE + 23)

#define EVN_ERR4_PROFILE_PARA_EE                        (EEPROM_HEAD_ADDR + 0x80*34)
#define EVN_ERR4_READ_CTRL_EE                           (EVN_ERR4_PROFILE_PARA_EE)//10bytes
#define EVN_ERR4_Capture_Period_EE                      (EVN_ERR4_PROFILE_PARA_EE + 10)//4bytes
#define EVN_ERR4_entries_in_use_EE                      (EVN_ERR4_PROFILE_PARA_EE + 14)//4bytes
#define EVN_ERR4_profile_entries_EE                     (EVN_ERR4_PROFILE_PARA_EE + 18)//4bytes
#define EVN_ERR4_Capture_Num_EE                         (EVN_ERR4_PROFILE_PARA_EE + 22)//1bytes
#define EVN_ERR4_Capture_Obj_EE                         (EVN_ERR4_PROFILE_PARA_EE + 23)

#define EVN_PSW_CHG_PROFILE_PARA_EE                     (EEPROM_HEAD_ADDR + 0x80*35)
#define EVN_PSW_CHG_READ_CTRL_EE                        (EVN_PSW_CHG_PROFILE_PARA_EE)//10bytes
#define EVN_PSW_CHG_Capture_Period_EE                   (EVN_PSW_CHG_PROFILE_PARA_EE + 10)//4bytes
#define EVN_PSW_CHG_entries_in_use_EE                   (EVN_PSW_CHG_PROFILE_PARA_EE + 14)//4bytes
#define EVN_PSW_CHG_profile_entries_EE                  (EVN_PSW_CHG_PROFILE_PARA_EE + 18)//4bytes
#define EVN_PSW_CHG_Capture_Num_EE                      (EVN_PSW_CHG_PROFILE_PARA_EE + 22)//1bytes
#define EVN_PSW_CHG_Capture_Obj_EE                      (EVN_PSW_CHG_PROFILE_PARA_EE + 23)

#define EVN_CFG_CHG_PROFILE_PARA_EE                     (EEPROM_HEAD_ADDR + 0x80*36)
#define EVN_CFG_CHG_READ_CTRL_EE                        (EVN_CFG_CHG_PROFILE_PARA_EE)//10bytes
#define EVN_CFG_CHG_Capture_Period_EE                   (EVN_CFG_CHG_PROFILE_PARA_EE + 10)//4bytes
#define EVN_CFG_CHG_entries_in_use_EE                   (EVN_CFG_CHG_PROFILE_PARA_EE + 14)//4bytes
#define EVN_CFG_CHG_profile_entries_EE                  (EVN_CFG_CHG_PROFILE_PARA_EE + 18)//4bytes
#define EVN_CFG_CHG_Capture_Num_EE                      (EVN_CFG_CHG_PROFILE_PARA_EE + 22)//1bytes
#define EVN_CFG_CHG_Capture_Obj_EE                      (EVN_CFG_CHG_PROFILE_PARA_EE + 23)

/******************************************************************************
*                                 第37-44页   暂时空余                                 *
******************************************************************************/



/******************************************************************************
*                                 第45 页     事件无效通道                 *
******************************************************************************/
#define         SECT_45EE                          (EEPROM_HEAD_ADDR + 0x80*45)
#define 		ADDR_LOG_NULL_FLAG                 SECT_45EE //目前只有AEC表才使用



/******************************************************************************
*                                 第46 页     push filter  和事件指针                 *
******************************************************************************/
#define         SECT_46EE                          (EEPROM_HEAD_ADDR + 0x80*46)
#define         EE_push_filter    			       SECT_46EE
#define         EE_ERROR_REG1_FILTER               (EE_push_filter)
#define         EE_ERROR_REG2_FILTER               (EE_ERROR_REG1_FILTER + 1)
#define         EE_ERROR_REG3_FILTER               (EE_ERROR_REG2_FILTER + 1)
#define         EE_ERROR_REG4_FILTER               (EE_ERROR_REG3_FILTER + 1)
#define         EE_ERROR_REG5_FILTER               (EE_ERROR_REG4_FILTER + 1)
#define         EE_ERROR_REG6_FILTER               (EE_ERROR_REG5_FILTER + 1)//预留
#define         EE_ERROR_REG7_FILTER               (EE_ERROR_REG6_FILTER + 1)//预留
#define         EE_ERROR_REG8_FILTER               (EE_ERROR_REG7_FILTER + 1)//预留
#define         EE_ECCU_REG_FILTER                 (EE_ERROR_REG8_FILTER + 1)
#define         ADDR_ERROR_REGISTER                (EE_ECCU_REG_FILTER + 1)//8个字节，预留了3个字节
#define         ADDR_ERROR_REGISTER_PUSH           (ADDR_ERROR_REGISTER + 8)//8个字节，预留了3个字节
#define         ADDR_LOG_CTRL                      (ADDR_ERROR_REGISTER_PUSH + 8)



/******************************************************************************
*                                 第47 - 48 页     push_script                   *
******************************************************************************/
#define         SECT_47EE                          (EEPROM_HEAD_ADDR + 0x80*47)
#define         EE_push_script_num    			   SECT_47EE
#define         EE_push_script                     (EE_push_script_num + 2)

/******************************************************************************
*                                 第49页        Clock Daylight Saving Cfg
******************************************************************************/
#define         ADDR_CLOCK_TIME_ZONE                    (EEPROM_HEAD_ADDR + 0x80*49) /*2bytes*/
#define         ADDR_CLOCK_Daylight_Saving_Begin        (ADDR_CLOCK_TIME_ZONE + 2)
#define         ADDR_CLOCK_Daylight_Saving_End          (ADDR_CLOCK_Daylight_Saving_Begin + 12)
#define         ADDR_CLOCK_Daylight_Saving_Deviation    (ADDR_CLOCK_Daylight_Saving_End + 12)
#define         ADDR_CLOCK_Daylight_Saving_Enable       (ADDR_CLOCK_Daylight_Saving_Deviation + 1)

/******************************************************************************
*                                 第50 - 51页       GPRS参数              *
******************************************************************************/
#define         SECT_50EE                          (EEPROM_HEAD_ADDR + 0x80*50)
#define         ADDR_GPRS_PARA_EE                  SECT_50EE                                //158字节
#define         ADDR_GPRS_CTRL                     (ADDR_GPRS_PARA_EE + sizeof(ST_GPRS_PARA)) //2字节
#define         ADDR_EVENTOCCURED_EE               (ADDR_GPRS_CTRL + sizeof(ST_GPRS_CTRL))    //1字节
#define         ADDR_PFTIMETEMP_EE                 (ADDR_EVENTOCCURED_EE + 1)                 //1字节
#define         ADDR_IP_TYPE_EE                    (ADDR_PFTIMETEMP_EE + 1)                   //2字节 1字节数值 + 1字节校验
#define         ADDR_simcard_IMSI_EE               (ADDR_IP_TYPE_EE + 2)                      //31字节 1字节长度 + 30字节有效数据
#define         ADDR_simcard_ICCID_EE              (ADDR_simcard_IMSI_EE + 31)                //31字节 1字节长度 + 30字节有效数据
#define         ADDR_Modem_IMEI_EE                 (ADDR_simcard_ICCID_EE + 31)               //31字节 1字节长度 + 30字节有效数据


/******************************************************************************
*                                 第52 - 57页       NB/4G/GPRS其他参数              *
******************************************************************************/
#define         SECT_52EE                          (EEPROM_HEAD_ADDR + 0x80*52)

#define         ADDR_ALIVE_INTERVAL_EE              SECT_52EE //10字节，实际使用5个字节+2个字节校验和，已预留了3个字节
#define         ADDR_NETWORK_MODE_EE                (ADDR_ALIVE_INTERVAL_EE + 10) //4字节，2个字节+2个字节校验和
#define         ADDR_R13_R14_SWITCH_EE              (ADDR_NETWORK_MODE_EE + 4) //4字节，2个字节+2个字节校验和
#define         ADDR_FOTA_ADDRESS_LEN_EE            (ADDR_R13_R14_SWITCH_EE + 4) //1字节
#define         ADDR_FOTA_ADDRESS_EE                (ADDR_FOTA_ADDRESS_LEN_EE + 1) //120字节  针对FTP，需要满足格式：IP;Port;Path;Username;Password， 举例：2a02:ce0:12:4:50dd:8fa9:b59:e9c;21;N25_T10_to_T11.pack;admin;public
#define         ADDR_AUTO_CONNECT_MODE_EE           (ADDR_FOTA_ADDRESS_EE + 120) //1字节
#define         ADDR_AUTO_REPETITIONS_EE            (ADDR_AUTO_CONNECT_MODE_EE + 1) //1字节
#define         ADDR_AUTO_REPET_DELAY_EE            (ADDR_AUTO_REPETITIONS_EE + 1) //2字节
#define         ADDR_CALLING_WINDOW_ARRAY_NUM_EE    (ADDR_AUTO_REPET_DELAY_EE + 2) //1字节
#define         ADDR_CALLING_WINDOW_EE              (ADDR_CALLING_WINDOW_ARRAY_NUM_EE + 1) //120 = 24 * 5字节
#define         ADDR_DEST_LIST_ARRAY_NUM_EE         (ADDR_CALLING_WINDOW_EE + 120) //1字节
#define         ADDR_DEST_LIST_OCT_LEN_EE           (ADDR_DEST_LIST_ARRAY_NUM_EE + 1) //5字节 //最多支持5个array
#define         ADDR_DEST_LIST_EE                   (ADDR_DEST_LIST_OCT_LEN_EE + 5) //400字节 //1个数组最多80字节

/******************************************************************************
*                                 第58页                                   *
******************************************************************************/
#define ADDR_EESELFTEST_EE                           (EEPROM_HEAD_ADDR + 0x80*58)



/******************************************************************************
*                                 第59-61页                                   *
******************************************************************************/
#define IMAGE_INFO_EE                           (EEPROM_HEAD_ADDR + 0x80*59)
#define ImageBlocksStatus                       (IMAGE_INFO_EE)       //512*(256*8)=1024KB
#define ImageIdentification                     (IMAGE_INFO_EE + 256) //20bytes
#define ImageSignature                          (IMAGE_INFO_EE + 276) //2bytes
#define ImageTransferStatus_EE                  (IMAGE_INFO_EE + 278) //1byte
#define ImageRecordStatus                       (IMAGE_INFO_EE + 279) //1byte
#define ADDR_UPGRADE_FLAG                       (IMAGE_INFO_EE + 280) //4byte
#define NULL_ImageTransInfo_EE                  (IMAGE_INFO_EE + 281) /*此地址与ADDR_UPGRADE_FLAG重叠，此地址停用，重新定义在第63页*/
#define NULL_ImageType_EE                       (IMAGE_INFO_EE + 310) /*此地址与ADDR_UPGRADE_FLAG重叠，此地址停用，重新定义在第63页*/
#define ADDR_NEWIMAGE_SIZE                      (IMAGE_INFO_EE + 311) //4bytes，size of newimage which verified successfully
#define ADDR_OLDIMAGE_SIZE                      (IMAGE_INFO_EE + 315) //4bytes，size of image after upgrade

/******************************************************************************
*                                 第62页    通信规约是否填null的标记         *
******************************************************************************/
#define ADDR_CHANNEL_NULL_CONFIG                (EEPROM_HEAD_ADDR + 0x80*62)//通信规约的处理方式，没有的通道是否填充为null，
#define ADDR_LP_NULL_FLAG                       (ADDR_CHANNEL_NULL_CONFIG)
#define ADDR_DAILY_PROFILE_NULL_FLAG            (ADDR_LP_NULL_FLAG + 4)
#define ADDR_DMD_PROFILE_NULL_FLAG              (ADDR_DAILY_PROFILE_NULL_FLAG + 16)
#define ADDR_CUM_DMD_PROFILE_NULL_FLAG          (ADDR_DMD_PROFILE_NULL_FLAG + 16)
#define ADDR_MON_PROFILE_NULL_FLAG              (ADDR_CUM_DMD_PROFILE_NULL_FLAG + 16)//AEC表占用64字节，其他表占用16字节



/********************************************************************************
*                                 第63页                                  *
*********************************************************************************/
#define ImageTransInfo_EE                       (EEPROM_HEAD_ADDR + 0x80*63) //
#define ImageType_EE                            (ImageTransInfo_EE + 29) //升级类型



/******************************************************************************
*                                 第64 - 65页                                   *
******************************************************************************/
#define LP_CAPTURE_MAX_SIZE                     16
#define PROFILE_PARA_EE                         (EEPROM_HEAD_ADDR + 0x80*64)
#define LP_READ_CTRL_EE                         (PROFILE_PARA_EE)//10bytes
#define LP_Capture_Period_EE                    (PROFILE_PARA_EE + 10)//4bytes
#define LP_entries_in_use_EE                    (PROFILE_PARA_EE + 14)//4bytes
#define LP_profile_entries_EE                   (PROFILE_PARA_EE + 18)//4bytes
#define LP_Capture_Num_EE                       (PROFILE_PARA_EE + 22)//1bytes
#define LP_Capture_Obj_EE                       (PROFILE_PARA_EE + 23)

/******************************************************************************
*                                 第66页                                   *
******************************************************************************/
#define MONTH_CAPTURE_MAX_SIZE                  64
#define MONTH_PROFILE_PARA_EE                   (EEPROM_HEAD_ADDR + 0x80*66)
#define MONTH_Capture_Period_EE                 (MONTH_PROFILE_PARA_EE)//4bytes
#define MONTH_entries_in_use_EE                 (MONTH_PROFILE_PARA_EE + 4)//4bytes
#define MONTH_profile_entries_EE                (MONTH_PROFILE_PARA_EE + 8)//4bytes
#define MONTH_READ_CTRL_EE                      (MONTH_PROFILE_PARA_EE + 12)//10bytes
#define MONTH_Capture_Num_EE                    (MONTH_PROFILE_PARA_EE + 22)//1bytes
#define MONTH_Capture_Obj_EE                    (MONTH_PROFILE_PARA_EE + 23)

/******************************************************************************
*                                 第72页                                   *
******************************************************************************/
#define DAILY_CAPTURE_MAX_SIZE                  128
#define DAILY_PROFILE_PARA_EE                   (EEPROM_HEAD_ADDR + 0x80*72)
#define DAILY_Capture_Period_EE                 (DAILY_PROFILE_PARA_EE)//4bytes
#define DAILY_entries_in_use_EE                 (DAILY_PROFILE_PARA_EE + 4)//4bytes
#define DAILY_profile_entries_EE                (DAILY_PROFILE_PARA_EE + 8)//4bytes
#define DAILY_READ_CTRL_EE                      (DAILY_PROFILE_PARA_EE + 12)//10bytes
#define DAILY_Capture_Num_EE                    (DAILY_PROFILE_PARA_EE + 22)//1btyes
#define DAILY_Capture_Obj_EE                    (DAILY_PROFILE_PARA_EE + 23)

/******************************************************************************
*                                 第84页                                   *
******************************************************************************/
#define MAX_DMD_CAPTURE_MAX_SIZE                128
#define MAX_DMD_PROFILE_PARA_EE                 (EEPROM_HEAD_ADDR + 0x80*84)
#define MAX_DMD_Capture_Period_EE               (MAX_DMD_PROFILE_PARA_EE)//4bytes
#define MAX_DMD_entries_in_use_EE               (MAX_DMD_PROFILE_PARA_EE + 4)//4bytes
#define MAX_DMD_profile_entries_EE              (MAX_DMD_PROFILE_PARA_EE + 8)//4bytes
#define MAX_DMD_READ_CTRL_EE                    (MAX_DMD_PROFILE_PARA_EE + 12)//10bytes
#define MAX_DMD_Capture_Num_EE                  (MAX_DMD_PROFILE_PARA_EE + 22)//1bytes
#define MAX_DMD_Capture_Obj_EE                  (MAX_DMD_PROFILE_PARA_EE + 23)

/******************************************************************************
*                                 第96页                                   *
******************************************************************************/
#define CUM_MAX_DMD_CAPTURE_MAX_SIZE            128
#define CUM_MAX_DMD_PROFILE_PARA_EE             (EEPROM_HEAD_ADDR + 0x80*96)
#define CUM_MAX_DMD_Capture_Period_EE           (CUM_MAX_DMD_PROFILE_PARA_EE)//4bytes
#define CUM_MAX_DMD_entries_in_use_EE           (CUM_MAX_DMD_PROFILE_PARA_EE + 4)//4bytes
#define CUM_MAX_DMD_profile_entries_EE          (CUM_MAX_DMD_PROFILE_PARA_EE + 8)//4bytes
#define CUM_MAX_DMD_READ_CTRL_EE                (CUM_MAX_DMD_PROFILE_PARA_EE + 12)//4bytes
#define CUM_MAX_DMD_Capture_Num_EE              (CUM_MAX_DMD_PROFILE_PARA_EE + 22)
#define CUM_MAX_DMD_Capture_Obj_EE              (CUM_MAX_DMD_PROFILE_PARA_EE + 23)

/******************************************************************************
*                                 第108页                                   *
******************************************************************************/
#define CLASS_REG_UNIT_SCALE_PRAR_EE            (EEPROM_HEAD_ADDR + 0x80*108)
#define VOLTAGE_UNIT_SCALE_EE                   (CLASS_REG_UNIT_SCALE_PRAR_EE)
#define CURRENT_UNIT_SCALE_EE                   (CLASS_REG_UNIT_SCALE_PRAR_EE + 2)
#define POWER_UNIT_SCALE_EE                     (CLASS_REG_UNIT_SCALE_PRAR_EE + 4)
#define ENERGY_UNIT_SCALE_EE                    (CLASS_REG_UNIT_SCALE_PRAR_EE + 6)
#define DEMAND_UNIT_SCALE_EE                    (CLASS_REG_UNIT_SCALE_PRAR_EE + 8)
#define POWER_FACTOR_UNIT_SCALE_EE              (CLASS_REG_UNIT_SCALE_PRAR_EE + 10)
#define CUM_DEMAND_UNIT_SCALE_EE                (CLASS_REG_UNIT_SCALE_PRAR_EE + 12)

/******************************************************************************
*                                 第109-111页      已预留了1页                             *
******************************************************************************/
#define ADDR_GPRS_PARAM                         (EEPROM_HEAD_ADDR + 0x80*109)



/******************************************************************************
*                                 第112-113页       FTP升级状态和模块push data被清除标志相关参数              *
******************************************************************************/
#define         SECT_112EE                          (EEPROM_HEAD_ADDR + 0x80*112)
#define         ADDR_FTP_UPGRADE_STATUS              SECT_112EE                     //5字节
#define         ADDR_FTP_UPGRADE_PARA_NUM           (ADDR_FTP_UPGRADE_STATUS + 5) //1字节
#define         ADDR_FTP_UPGRADE_IP_LEN             (ADDR_FTP_UPGRADE_PARA_NUM + 1) //1字节
#define         ADDR_FTP_FILE_NAME_LEN              (ADDR_FTP_UPGRADE_IP_LEN + 1) //1字节
#define         ADDR_FTP_USERNAME_LEN               (ADDR_FTP_FILE_NAME_LEN + 1) //1字节
#define         ADDR_FTP_PASSWORD_LEN               (ADDR_FTP_USERNAME_LEN + 1) //1字节
#define         ADDR_FTP_UPGRADE_PARA               (ADDR_FTP_PASSWORD_LEN + 1) //167字节
#define         ADDR_LOSS_COV_LEN                   (ADDR_FTP_UPGRADE_PARA + 167)//4字节
#define         ADDR_LOSS_COV_BACKOFF_MAX_CNT       (ADDR_LOSS_COV_LEN + 4)//1字节

/******************************************************************************
*                                 第114页                                   *
******************************************************************************/
#define Image_Check_St                          (EEPROM_HEAD_ADDR + 0x80*114)//1个字节
#define ADDR_Upgrade_Fail_Reason                (Image_Check_St + 1)  /*  升级后错误原因 1 字节 */


/******************************************************************************
*                                 第115-116页                                   *
******************************************************************************/
#define LP_CATPURE_INFO                         (EEPROM_HEAD_ADDR + 0x80*115)
#define LP_Capture_Num_ForV8_EE                 (PROFILE_PARA_EE + 22)//10bytes
#define LP_Capture_Obj_ForV8_EE                 (PROFILE_PARA_EE + 23)

/******************************************************************************
*                                 第117-119页      升级相关的            *
******************************************************************************/
#define IMAGE_INFO_FOR_METER_EE                 (EEPROM_HEAD_ADDR + 0x80*117)
#define METER_BLOCK_SIZE                        (IMAGE_INFO_FOR_METER_EE)
#define METER_BLOCKS_STATUS_SIZE                (IMAGE_INFO_FOR_METER_EE + 4)
#define METER_BLOCKS_STATUS                     (IMAGE_INFO_FOR_METER_EE + 6)
#define METER_FIRST_NOT_TRANS_NUM               (IMAGE_INFO_FOR_METER_EE + 256)
#define METER_TRANS_EN                          (IMAGE_INFO_FOR_METER_EE + 260)
#define METER_TRANS_STATUS                      (IMAGE_INFO_FOR_METER_EE + 261)
#define METER_ACT_INFO                          (IMAGE_INFO_FOR_METER_EE + 262)



/******************************************************************************
*                                 第120 - 122页     空余                              *
******************************************************************************/






/******************************************************************************
*                                 第123页     NB相关                              *
******************************************************************************/
#define         SECT_123EE                          (EEPROM_HEAD_ADDR + 0x80*123)
#define         ADDR_TIMESTAMP                      SECT_123EE//4字节
#define         ADDR_LastPushCellID                 ADDR_TIMESTAMP + 64//4字节

/******************************************************************************
*                                 第124 - 125页    	*HLS invloke counter相关的
******************************************************************************/
#define         SECT_124EE                          (EEPROM_HEAD_ADDR + 0x80*124)
#define         ADDR_Power_On_Logon_Mode           		 SECT_124EE
#define         ADDR_Event_Report_Mode             		 (ADDR_Power_On_Logon_Mode + 1)
#define         ADDR_DataTransport_Security_LOCK_Mode    (ADDR_Event_Report_Mode + 1)//密码错误是否闭锁


/******************************************************************************
*                                 第126页       存储工厂模式     *
******************************************************************************/
#define         SECT_126EE                          (EEPROM_HEAD_ADDR + 0x80*126)
#define         ADDR_32kXTALlosed                    SECT_126EE  /*晶振历史状态字，1字节*/
#define         ADDR_Enter_Fact_Mode                 (ADDR_32kXTALlosed + 1)  //4字节



/******************************************************************************
*                                 第127页                                   *
******************************************************************************/
#define         ADDR_Binding_Meter_Information_EE            (EEPROM_HEAD_ADDR + 0x80*127)
#define         ADDR_Binding_Array_Num_EE                    (ADDR_Binding_Meter_Information_EE)
#define         ADDR_Binding_Client_ID_EE                    (ADDR_Binding_Array_Num_EE + 1)
#define         ADDR_Binding_HDLC_Addr_Len_EE                (ADDR_Binding_Client_ID_EE + 5)
#define         ADDR_Binding_HDLC_Addr_EE                    (ADDR_Binding_HDLC_Addr_Len_EE + 5)
#define         ADDR_Binding_PASSWORD_Len_EE                 (ADDR_Binding_HDLC_Addr_EE + 20)
#define         ADDR_Binding_PASSWORD_EE                     (ADDR_Binding_PASSWORD_Len_EE + 5)//每个密码占用16字节


/******************************************************************************
*                                 第128-129页                                       *
******************************************************************************/
#define         SECT_128EE                         (EEPROM_HEAD_ADDR + 0x80 * 128)
#define         ADDR_LP1_Profile_EE                SECT_128EE
#define         ADDR_LP1_Capture_Objects_EE        (ADDR_LP1_Profile_EE + 0)   /*  196字节 预留16个通道的地址空间  */
#define         ADDR_LP1_Sort_Method_EE            (ADDR_LP1_Profile_EE + 196)  /*  1字节  */
#define         ADDR_LP1_Sort_Object_EE            (ADDR_LP1_Profile_EE + 197) /*  1字节  */
#define         ADDR_LP1_Capture_Period_EE         (ADDR_LP1_Profile_EE + 198) /*  4字节  */
#define         ADDR_LP1_Entries_In_Use_EE         (ADDR_LP1_Profile_EE + 202) /*  2字节  */
#define         ADDR_LP1_Profile_Entries_EE        (ADDR_LP1_Profile_EE + 204) /*  2字节  */
#define         ADDR_LP1_Current_Point_EE          (ADDR_LP1_Profile_EE + 206) /*  2字节  */
#define         ADDR_LP1_Max_Num_EE                (ADDR_LP1_Profile_EE + 208) /*  2字节  */
#define         ADDR_LP1_One_Len_EE                (ADDR_LP1_Profile_EE + 210) /*  1字节  */
#define         ADDR_LP1_Objects_Num_EE            (ADDR_LP1_Profile_EE + 211) /*  1字节  */
#define         ADDR_LP1_Objects_Transform_EE      (ADDR_LP1_Profile_EE + 212) /*  20字节  */
#define         ADDR_LP1_Repair_Inf_EE             (ADDR_LP1_Profile_EE + 232)  /*  3字节*/


/******************************************************************************
*                                 第130页 ---第131   	*net quality 负荷曲线参数
******************************************************************************/
#define         SECT_130EE                     	  	  (EEPROM_HEAD_ADDR + 0x80*130)
#define         ADDR_NET_LP_Profile_EE         		  SECT_130EE
#define         ADDR_NET_LP_Capture_Objects_EE        (ADDR_NET_LP_Profile_EE + 0)   /*  220字节 预留20个通道的地址空间  */
#define         ADDR_NET_LP_Sort_Method_EE            (ADDR_NET_LP_Profile_EE + 220) /*  1字节  */
#define         ADDR_NET_LP_Sort_Object_EE            (ADDR_NET_LP_Profile_EE + 221) /*  1字节  */
#define         ADDR_NET_LP_Capture_Period_EE         (ADDR_NET_LP_Profile_EE + 222) /*  4字节  */
#define         ADDR_NET_LP_Entries_In_Use_EE         (ADDR_NET_LP_Profile_EE + 226) /*  2字节  */
#define         ADDR_NET_LP_Profile_Entries_EE        (ADDR_NET_LP_Profile_EE + 228) /*  2字节  */
#define         ADDR_NET_LP_Current_Point_EE          (ADDR_NET_LP_Profile_EE + 230) /*  2字节  */
#define         ADDR_NET_LP_Max_Num_EE                (ADDR_NET_LP_Profile_EE + 232) /*  2字节  */
#define         ADDR_NET_LP_One_Len_EE                (ADDR_NET_LP_Profile_EE + 234) /*  1字节  */
#define         ADDR_NET_LP_Objects_Num_EE            (ADDR_NET_LP_Profile_EE + 235) /*  1字节  */
#define         ADDR_NET_LP_Objects_Transform_EE      (ADDR_NET_LP_Profile_EE + 236) /*  20字节  */
#define         ADDR_NET_LP_Repair_Inf_EE             (ADDR_NET_LP_Profile_EE + 256)  /*  3字节*/


/******************************************************************************
*                                 第132 - 133页          瞬时电压电流等负荷曲线             *
******************************************************************************/
#define         SECT_132EE                     	  	      (EEPROM_HEAD_ADDR + 0x80*132)
#define         ADDR_INSTANT_LP_Profile_EE                SECT_132EE
#define         ADDR_INSTANT_LP_Capture_Objects_EE        (ADDR_INSTANT_LP_Profile_EE + 0)   /*  220字节 预留20个通道的地址空间  */
#define         ADDR_INSTANT_LP_Sort_Method_EE            (ADDR_INSTANT_LP_Profile_EE + 220) /*  1字节  */
#define         ADDR_INSTANT_LP_Sort_Object_EE            (ADDR_INSTANT_LP_Profile_EE + 221) /*  1字节  */
#define         ADDR_INSTANT_LP_Capture_Period_EE         (ADDR_INSTANT_LP_Profile_EE + 222) /*  4字节  */
#define         ADDR_INSTANT_LP_Entries_In_Use_EE         (ADDR_INSTANT_LP_Profile_EE + 226) /*  2字节  */
#define         ADDR_INSTANT_LP_Profile_Entries_EE        (ADDR_INSTANT_LP_Profile_EE + 228) /*  2字节  */
#define         ADDR_INSTANT_LP_Current_Point_EE          (ADDR_INSTANT_LP_Profile_EE + 230) /*  2字节  */
#define         ADDR_INSTANT_LP_Max_Num_EE                (ADDR_INSTANT_LP_Profile_EE + 232) /*  2字节  */
#define         ADDR_INSTANT_LP_One_Len_EE                (ADDR_INSTANT_LP_Profile_EE + 234) /*  1字节  */
#define         ADDR_INSTANT_LP_Objects_Num_EE            (ADDR_INSTANT_LP_Profile_EE + 235) /*  1字节  */
#define         ADDR_INSTANT_LP_Objects_Transform_EE      (ADDR_INSTANT_LP_Profile_EE + 236) /*  20字节  */
#define         ADDR_INSTANT_LP_Repair_Inf_EE             (ADDR_INSTANT_LP_Profile_EE + 256)  /*  3字节*/



/******************************************************************************
						          第134 - 167页  通道配置

******************************************************************************/
#define          SECT_134EE                          	(EEPROM_HEAD_ADDR + 0x80*134)
#define          ADDR_TIME_ENGRY_CONFIG               	SECT_134EE
#define          ADDR_CHANNLE_CAPTURE_NUM             	ADDR_TIME_ENGRY_CONFIG
#define          ADDR_ENERGY_PROFILE_CAPTURE_ITEM     	(ADDR_CHANNLE_CAPTURE_NUM + 4)   /*最大40个通道*/
#define          ADDR_DALIY_ENG_PROFILE_CAPTURE_ITEM  	(ADDR_ENERGY_PROFILE_CAPTURE_ITEM + 40 * 11)/*最大126个通道*/
#define          ADDR_MAXDMEAND_PROFILE_CAPTURE_ITEM  	(ADDR_DALIY_ENG_PROFILE_CAPTURE_ITEM + 126 * 11)/*最大107个通道*/
#define          ADDR_CUM_DEMAND_PROFILE_CAPTURE_IETM 	(ADDR_MAXDMEAND_PROFILE_CAPTURE_ITEM + 107 * 11)/*最大106个通道*/



/******************************************************************************
						          第168页  平均值负荷曲线周期和事件相关参数

******************************************************************************/
#define          SECT_168EE                          	(EEPROM_HEAD_ADDR + 0x80*168)
#define          ADDR_AVERAGE_VOL_CURR_INTERVAL         SECT_168EE//1个字节
#define          ADDR_CUR_OVER_THRESHOLD            	(ADDR_AVERAGE_VOL_CURR_INTERVAL + 1)//2个字节
#define          ADDR_CUR_OVER_DURATION             	(ADDR_CUR_OVER_THRESHOLD + 2)//1个字节
#define          ADDR_TEMPERATURE_OVER_THRESHOLD      	(ADDR_CUR_OVER_DURATION + 1)//2个字节
#define          ADDR_TEMPERATURE_OVER_DURATION      	(ADDR_TEMPERATURE_OVER_THRESHOLD + 2)//2个字节
#define          ADDR_TEMPERATURE_UNDER_DURATION      	(ADDR_TEMPERATURE_OVER_DURATION + 2) /*  1 字节  */
#define          ADDR_RELAY_OFF_TEMP_OVER_DURATION      (ADDR_TEMPERATURE_UNDER_DURATION + 1)//过温度门限而需要继电器拉闸时间 2个字节，单位是分钟
#define          ADDR_MAGNETIC_DURATION         		(ADDR_RELAY_OFF_TEMP_OVER_DURATION + 2)//4个字节





/******************************************************************************
						          第169 - 170页  平均值负荷曲线周期

******************************************************************************/
#define         SECT_169EE                         (EEPROM_HEAD_ADDR + 0x80*169)
#define         ADDR_BILLING_MON_DATA               SECT_169EE
#define         ADDR_BILLING_DAY_DATA_CTRL         (ADDR_BILLING_MON_DATA + 4)
#define         ADDR_485_1_ENERGY_PROFILE_RD_EE    (ADDR_BILLING_DAY_DATA_CTRL + 4)



/******************************************************************************
*                                 第171 - 249页    	*event 预留5页的存储空间
******************************************************************************/
#define         LOG_MAX_NUM                         30
#define         SECT_171EE                          (EEPROM_HEAD_ADDR + 0x80*171)

#define         ADDR_PowerFailure_Buffer_EE         SECT_171EE
#define         ADDR_PowerRestore_Buffer_EE         ADDR_PowerFailure_Buffer_EE + LOG_MAX_NUM * 20 + 1
#define         ADDR_TIME_BEFORE_CHANGE_Buffer_EE   ADDR_PowerRestore_Buffer_EE + LOG_MAX_NUM * 20 + 1
#define         ADDR_TIME_AFTER_CHANGE_Buffer_EE    ADDR_TIME_BEFORE_CHANGE_Buffer_EE + LOG_MAX_NUM * 14 + 1
#define         ADDR_EOB_RESET_Buffer_EE            ADDR_TIME_AFTER_CHANGE_Buffer_EE + LOG_MAX_NUM * 14 + 1
#define         ADDR_MANUAL_RESET_Buffer_EE         ADDR_EOB_RESET_Buffer_EE + LOG_MAX_NUM * 14 + 1
#define         ADDR_AUTO_RESET_Buffer_EE           ADDR_MANUAL_RESET_Buffer_EE + LOG_MAX_NUM * 14 + 1
#define         ADDR_CONFI_CHANGE_Buffer_EE         ADDR_AUTO_RESET_Buffer_EE + LOG_MAX_NUM * 14 + 1
#define         ADDR_COMM_PORT_Buffer_EE            ADDR_CONFI_CHANGE_Buffer_EE + LOG_MAX_NUM * 14 + 1
#define         ADDR_BATT_MEMORY_Buffer_EE          ADDR_COMM_PORT_Buffer_EE + LOG_MAX_NUM * 15 + 1
#define         ADDR_POWERLINE_CUT_Buffer_EE        ADDR_BATT_MEMORY_Buffer_EE + LOG_MAX_NUM * 13 + 1
#define         ADDR_TAMPER1_Buffer_EE              ADDR_POWERLINE_CUT_Buffer_EE + LOG_MAX_NUM * 19 + 1
#define         ADDR_TAMPER2_Buffer_EE              ADDR_TAMPER1_Buffer_EE + LOG_MAX_NUM * 21 + 1
#define         ADDR_CURR_VOL_LIMIT_Buffer_EE       ADDR_TAMPER2_Buffer_EE + LOG_MAX_NUM * 19 + 1
#define         ADDR_OUT_RELAY_Buffer_EE            ADDR_CURR_VOL_LIMIT_Buffer_EE + LOG_MAX_NUM * 13 + 1
#define         ADDR_PASSWORD_CHANGE_Buffer_EE      ADDR_OUT_RELAY_Buffer_EE + LOG_MAX_NUM * 17 + 1
#define         ADDR_ECCU_ALARM_Buffer_EE           ADDR_PASSWORD_CHANGE_Buffer_EE + LOG_MAX_NUM * 17 + 1
#define         ADDR_UPGRADE_BEGIN_Buffer_EE  		ADDR_ECCU_ALARM_Buffer_EE + LOG_MAX_NUM * 13 + 1
#define         ADDR_UPGRADE_END_Buffer_EE  		ADDR_UPGRADE_BEGIN_Buffer_EE + LOG_MAX_NUM * 12 + 1
#define         ADDR_UPGRADE_FAILURE_Buffer_EE  	ADDR_UPGRADE_END_Buffer_EE + LOG_MAX_NUM * 12 + 1


/******************************************************************************
*                                 第250页-277页        Push setup
******************************************************************************/

#define          PUSH_OBJECT_OFFSET                      0x80*4
#define          PUSH_OBJECT_NUM                        7  //7个push
#define          PUSH_RATAIN_NUM                        4   //PUSH的event保留条数
#define          PUSH_COMMAND_RATAIN_NUM                3    //PUSH命令的event保留条数

#define          SECT_250EE                              (EEPROM_HEAD_ADDR + 0x80*250)
#define          ADDR_PUSH1_OBJ_NUM                      SECT_250EE
#define          ADDR_PUSH1_OBJLIST                      (ADDR_PUSH1_OBJ_NUM + 1)
#define          ADDR_PUSH1_DesLen             			 (ADDR_PUSH1_OBJLIST + 55)
#define          ADDR_PUSH1_SendDesAndMethod             (ADDR_PUSH1_DesLen + 1)
#define          ADDR_PUSH1_RandValue                    (ADDR_PUSH1_SendDesAndMethod + 60)
#define          ADDR_PUSH1_NUM_Retry                    (ADDR_PUSH1_RandValue + 2)
#define          ADDR_PUSH1_Repetition_Delay             (ADDR_PUSH1_NUM_Retry + 1)
#define          ADDR_PUSH1_CUMMUNICATE_WINDOW_NUM       (ADDR_PUSH1_Repetition_Delay + 2)
#define          ADDR_PUSH1_CUMMUNICTAE_WINDOW           (ADDR_PUSH1_CUMMUNICATE_WINDOW_NUM + 1)

#define          SECT_254EE                              (EEPROM_HEAD_ADDR + 0x80*254)
#define          ADDR_PUSH2_OBJ_NUM                      SECT_254EE
#define          ADDR_PUSH2_OBJLIST                      (ADDR_PUSH2_OBJ_NUM + 1)
#define          ADDR_PUSH2_DesLen             			 (ADDR_PUSH2_OBJLIST + 55)
#define          ADDR_PUSH2_SendDesAndMethod             (ADDR_PUSH2_DesLen + 1)
#define          ADDR_PUSH2_RandValue                    (ADDR_PUSH2_SendDesAndMethod + 60)
#define          ADDR_PUSH2_NUM_Retry                    (ADDR_PUSH2_RandValue + 2)
#define          ADDR_PUSH2_Repetition_Delay             (ADDR_PUSH2_NUM_Retry + 1)
#define          ADDR_PUSH2_CUMMUNICATE_WINDOW_NUM       (ADDR_PUSH2_Repetition_Delay + 2)
#define          ADDR_PUSH2_CUMMUNICTAE_WINDOW           (ADDR_PUSH2_CUMMUNICATE_WINDOW_NUM + 1)
#define          ADDR_PUSH2_REGISTER1_PT                 (ADDR_PUSH2_CUMMUNICTAE_WINDOW + 10 * 24)
#define          ADDR_PUSH2_REGISTER1_NUM                (ADDR_PUSH2_REGISTER1_PT + 2)
#define          ADDR_PUSH2_REGISTER1_STACK              (ADDR_PUSH2_REGISTER1_NUM + 1)
#define          ADDR_PUSH2_REGISTER1_COMMAND_PT      	 (ADDR_PUSH2_REGISTER1_STACK + PUSH_RATAIN_NUM * 13)
#define          ADDR_PUSH2_REGISTER1_COMMAND_NUM  	     (ADDR_PUSH2_REGISTER1_COMMAND_PT + 2)
#define          ADDR_PUSH2_REGISTER1_COMMAND_STACK      (ADDR_PUSH2_REGISTER1_COMMAND_NUM + 1)


#define          SECT_258EE                              (EEPROM_HEAD_ADDR + 0x80*258)
#define          ADDR_PUSH3_OBJ_NUM                      SECT_258EE
#define          ADDR_PUSH3_OBJLIST                      (ADDR_PUSH3_OBJ_NUM + 1)
#define          ADDR_PUSH3_DesLen                       (ADDR_PUSH3_OBJLIST + 55)
#define          ADDR_PUSH3_SendDesAndMethod             (ADDR_PUSH3_DesLen + 1)
#define          ADDR_PUSH3_RandValue                    (ADDR_PUSH3_SendDesAndMethod + 60)
#define          ADDR_PUSH3_NUM_Retry                    (ADDR_PUSH3_RandValue + 2)
#define          ADDR_PUSH3_Repetition_Delay             (ADDR_PUSH3_NUM_Retry + 1)
#define          ADDR_PUSH3_CUMMUNICATE_WINDOW_NUM       (ADDR_PUSH3_Repetition_Delay + 2)
#define          ADDR_PUSH3_CUMMUNICTAE_WINDOW           (ADDR_PUSH3_CUMMUNICATE_WINDOW_NUM + 1)
#define          ADDR_PUSH3_REGISTER2_PT                 (ADDR_PUSH3_CUMMUNICTAE_WINDOW + 10 * 24)
#define          ADDR_PUSH3_REGISTER2_NUM                (ADDR_PUSH3_REGISTER2_PT + 2)
#define          ADDR_PUSH3_REGISTER2_STACK              (ADDR_PUSH3_REGISTER2_NUM + 1)
#define          ADDR_PUSH3_REGISTER2_COMMAND_PT      	 (ADDR_PUSH3_REGISTER2_STACK + PUSH_RATAIN_NUM * 13)
#define          ADDR_PUSH3_REGISTER2_COMMAND_NUM  	     (ADDR_PUSH3_REGISTER2_COMMAND_PT + 2)
#define          ADDR_PUSH3_REGISTER2_COMMAND_STACK      (ADDR_PUSH3_REGISTER2_COMMAND_NUM + 1)


#define          SECT_262EE                              (EEPROM_HEAD_ADDR + 0x80*262)
#define          ADDR_PUSH4_OBJ_NUM                      SECT_262EE
#define          ADDR_PUSH4_OBJLIST                      (ADDR_PUSH4_OBJ_NUM + 1)
#define          ADDR_PUSH4_DesLen                       (ADDR_PUSH4_OBJLIST + 55)
#define          ADDR_PUSH4_SendDesAndMethod             (ADDR_PUSH4_DesLen + 1)
#define          ADDR_PUSH4_RandValue                    (ADDR_PUSH4_SendDesAndMethod + 60)
#define          ADDR_PUSH4_NUM_Retry                    (ADDR_PUSH4_RandValue + 2)
#define          ADDR_PUSH4_Repetition_Delay             (ADDR_PUSH4_NUM_Retry + 1)
#define          ADDR_PUSH4_CUMMUNICATE_WINDOW_NUM       (ADDR_PUSH4_Repetition_Delay + 2)
#define          ADDR_PUSH4_CUMMUNICTAE_WINDOW           (ADDR_PUSH4_CUMMUNICATE_WINDOW_NUM + 1)
#define          ADDR_PUSH4_REGISTER3_PT                 (ADDR_PUSH4_CUMMUNICTAE_WINDOW + 10 * 24)
#define          ADDR_PUSH4_REGISTER3_NUM                (ADDR_PUSH4_REGISTER3_PT + 2)
#define          ADDR_PUSH4_REGISTER3_STACK              (ADDR_PUSH4_REGISTER3_NUM + 1)
#define          ADDR_PUSH4_REGISTER3_COMMAND_PT      	 (ADDR_PUSH4_REGISTER3_STACK + PUSH_RATAIN_NUM * 13)
#define          ADDR_PUSH4_REGISTER3_COMMAND_NUM  	     (ADDR_PUSH4_REGISTER3_COMMAND_PT + 2)
#define          ADDR_PUSH4_REGISTER3_COMMAND_STACK      (ADDR_PUSH4_REGISTER3_COMMAND_NUM + 1)


#define          SECT_266EE                              (EEPROM_HEAD_ADDR + 0x80*266)
#define          ADDR_PUSH5_OBJ_NUM                      SECT_266EE
#define          ADDR_PUSH5_OBJLIST                      (ADDR_PUSH5_OBJ_NUM + 1)
#define          ADDR_PUSH5_DesLen             			 (ADDR_PUSH5_OBJLIST + 55)
#define          ADDR_PUSH5_SendDesAndMethod             (ADDR_PUSH5_DesLen + 1)
#define          ADDR_PUSH5_RandValue                    (ADDR_PUSH5_SendDesAndMethod + 60)
#define          ADDR_PUSH5_NUM_Retry                    (ADDR_PUSH5_RandValue + 2)
#define          ADDR_PUSH5_Repetition_Delay             (ADDR_PUSH5_NUM_Retry + 1)
#define          ADDR_PUSH5_CUMMUNICATE_WINDOW_NUM       (ADDR_PUSH5_Repetition_Delay + 2)
#define          ADDR_PUSH5_CUMMUNICTAE_WINDOW           (ADDR_PUSH5_CUMMUNICATE_WINDOW_NUM + 1)
#define          ADDR_PUSH5_REGISTER4_PT                 (ADDR_PUSH5_CUMMUNICTAE_WINDOW + 10 * 24)
#define          ADDR_PUSH5_REGISTER4_NUM                (ADDR_PUSH5_REGISTER4_PT + 2)
#define          ADDR_PUSH5_REGISTER4_STACK              (ADDR_PUSH5_REGISTER4_NUM + 1)
#define          ADDR_PUSH5_REGISTER4_COMMAND_PT      	 (ADDR_PUSH5_REGISTER4_STACK + PUSH_RATAIN_NUM * 13)
#define          ADDR_PUSH5_REGISTER4_COMMAND_NUM  	     (ADDR_PUSH5_REGISTER4_COMMAND_PT + 2)
#define          ADDR_PUSH5_REGISTER4_COMMAND_STACK      (ADDR_PUSH5_REGISTER4_COMMAND_NUM + 1)


#define          SECT_270EE                              (EEPROM_HEAD_ADDR + 0x80*270)
#define          ADDR_PUSH6_OBJ_NUM                      SECT_270EE
#define          ADDR_PUSH6_OBJLIST                      (ADDR_PUSH6_OBJ_NUM + 1)
#define          ADDR_PUSH6_DesLen                       (ADDR_PUSH6_OBJLIST + 55)
#define          ADDR_PUSH6_SendDesAndMethod             (ADDR_PUSH6_DesLen + 1)
#define          ADDR_PUSH6_RandValue                    (ADDR_PUSH6_SendDesAndMethod + 60)
#define          ADDR_PUSH6_NUM_Retry                    (ADDR_PUSH6_RandValue + 2)
#define          ADDR_PUSH6_Repetition_Delay             (ADDR_PUSH6_NUM_Retry + 1)
#define          ADDR_PUSH6_CUMMUNICATE_WINDOW_NUM       (ADDR_PUSH6_Repetition_Delay + 2)
#define          ADDR_PUSH6_CUMMUNICTAE_WINDOW           (ADDR_PUSH6_CUMMUNICATE_WINDOW_NUM + 1)
#define          ADDR_PUSH6_REGISTER5_PT                 (ADDR_PUSH6_CUMMUNICTAE_WINDOW + 10 * 24)
#define          ADDR_PUSH6_REGISTER5_NUM                (ADDR_PUSH6_REGISTER5_PT + 2)
#define          ADDR_PUSH6_REGISTER5_STACK              (ADDR_PUSH6_REGISTER5_NUM + 1)
#define          ADDR_PUSH6_REGISTER5_COMMAND_PT      	 (ADDR_PUSH6_REGISTER5_STACK + PUSH_RATAIN_NUM * 13)
#define          ADDR_PUSH6_REGISTER5_COMMAND_NUM  	     (ADDR_PUSH6_REGISTER5_COMMAND_PT + 2)
#define          ADDR_PUSH6_REGISTER5_COMMAND_STACK      (ADDR_PUSH6_REGISTER5_COMMAND_NUM + 1)


#define          SECT_274EE                              (EEPROM_HEAD_ADDR + 0x80*274)
#define          ADDR_PUSH11_OBJ_NUM                      SECT_274EE
#define          ADDR_PUSH11_OBJLIST                     (ADDR_PUSH11_OBJ_NUM + 1)
#define          ADDR_PUSH11_DesLen                      (ADDR_PUSH11_OBJLIST + 55)
#define          ADDR_PUSH11_SendDesAndMethod            (ADDR_PUSH11_DesLen + 1)
#define          ADDR_PUSH11_RandValue                   (ADDR_PUSH11_SendDesAndMethod + 60)
#define          ADDR_PUSH11_NUM_Retry                   (ADDR_PUSH11_RandValue + 2)
#define          ADDR_PUSH11_Repetition_Delay            (ADDR_PUSH11_NUM_Retry + 1)
#define          ADDR_PUSH11_CUMMUNICATE_WINDOW_NUM      (ADDR_PUSH11_Repetition_Delay + 2)
#define          ADDR_PUSH11_CUMMUNICTAE_WINDOW          (ADDR_PUSH11_CUMMUNICATE_WINDOW_NUM + 1)
#define          ADDR_PUSH11_REGISTER6_PT                (ADDR_PUSH11_CUMMUNICTAE_WINDOW + 10 * 24)
#define          ADDR_PUSH11_REGISTER6_NUM               (ADDR_PUSH11_REGISTER6_PT + 2)
#define          ADDR_PUSH11_REGISTER6_STACK             (ADDR_PUSH11_REGISTER6_NUM + 1)
#define          ADDR_PUSH11_REGISTER6_COMMAND_PT      	 (ADDR_PUSH11_REGISTER6_STACK + PUSH_RATAIN_NUM * 13)
#define          ADDR_PUSH11_REGISTER6_COMMAND_NUM  	 (ADDR_PUSH11_REGISTER6_COMMAND_PT + 2)
#define          ADDR_PUSH11_REGISTER6_COMMAND_STACK     (ADDR_PUSH11_REGISTER6_COMMAND_NUM + 1)

/******************************************************************************
*                                 第278-287页
******************************************************************************/
#define         EVN_POWER_LINE_TEMP_BUFF_EE              (EEPROM_HEAD_ADDR + 0x80*278)//19Bytes * 30 = 570Bytes, 5pages
#define         ADDR_CUR_VOL_LIMIT_TEMP_BUFF_EE          (EEPROM_HEAD_ADDR + 0x80*283)//19Bytes * 30 = 570Bytes, 5pages
#define         ADDR_TAMPER1_TEMP_BUFF_EE                (EEPROM_HEAD_ADDR + 0x80*288)//21Bytes * 30 = 630Bytes, 5pages

/******************************************************************************
*                                 第293页
******************************************************************************/
#define         ADDR_AEC_MONTH_CAPTURE_EE                (EEPROM_HEAD_ADDR + 0x80*293)
#endif

/* 4 end------------------------------------------------------------------ */

/*************************** under blank *************************************/
