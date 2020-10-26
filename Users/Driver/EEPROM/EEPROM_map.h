/******************************************************************************
 Copyright (C) Aug.2��2004  R&D Institute of Reallin Co., Ltd.
 Module         : �洢������ͷ�ļ�..
 File Name      : EEPROM.h
 Description    :
 Author         : liu shun
 Build Date     :
 others         :
         EEPROM : 24LC512
       ��ַ�ռ� ��0x0000~0xFFFF
 ------------------------------------------------------------------------------
 Modification History:
 <No.> <version >  <time>        <author>     <contents>
  3��
  2��    1.10     2008-01-07    liu shun     modified this moudle
  1��    1.00     2007-06-20    liu shun     build this moudle
******************************************************************************/
/* 1 ------------------------------------------------------------------------
 �곣��ֵ����
-------------------------------------------------------------------------- */
/* 1 end------------------------------------------------------------------ */

/* 2 ------------------------------------------------------------------------
 eeprom_a��ַ����
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
} ENUM_MEMORY_HEAD; /*�洢����ַ����*/

/******************************************************************************
*                                 ��0-1ҳ                                   *
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
#define ADDR_HARD_VARSION_EE                    (ADDR_MAX_CURRENT_EE + 4)//32�ֽ�
#define ADDR_MODULE_TYPE                        (ADDR_HARD_VARSION_EE + 32)//8�ֽ�
#define ADDR_Manfactory_EE                      (ADDR_MODULE_TYPE + 8)//Ԥ��16�ֽ�

/******************************************************************************
*                                 ��2ҳ         	*����
******************************************************************************/
#define SECT_2EE                                (EEPROM_HEAD_ADDR + 0x80*2)
/* Security setup for Association ........................................... */
#define SECURITY_SETUP_SECT                     SECT_2EE
#define ClientSecurityTitle_EE                  (SECURITY_SETUP_SECT)          /*  8 �ֽ�  */
#define SecretForLLS_LEN_EE                     (ClientSecurityTitle_EE + 8)   /*  1 �ֽ�  */
#define SecretForLLS_EE                         (SecretForLLS_LEN_EE + 1)      /*  16 �ֽ�  */
#define SecurityPolicy_EE                       (SecretForLLS_EE + 16)         /*  1 �ֽ�  */
#define SecuritySuit_EE                         (SecurityPolicy_EE + 1)        /*  1 �ֽ�  */
#define UnicastEncryptionKey_EE                 (SecuritySuit_EE + 1)          /*  16 �ֽ�  */
#define BroadcastEncryptionKey_EE               (UnicastEncryptionKey_EE + 16)  /*  16 �ֽ�  */
#define AuthenticationKey_EE                    (BroadcastEncryptionKey_EE + 16)/*  16 �ֽ�  */
#define MasterKey_EE                            (AuthenticationKey_EE + 16)    /*  16 �ֽ�  */
#define DataTransPortSecurityMode_EE            (MasterKey_EE + 16)            /*  1 �ֽ�  */
#define AuthMechnism_EE                         (DataTransPortSecurityMode_EE + 1)  /*  1 �ֽ� Ŀǰֻ֧��1��5 */


/******************************************************************************
*                                 ��3ҳ         	*���籣������
******************************************************************************/
#define ADDR_POWER_DOWN_INFO                    (EEPROM_HEAD_ADDR + 0x80*3)
#define ADDR_STATUS_WORD                        (ADDR_POWER_DOWN_INFO)
#define ADDR_AA_IC_EE                           (ADDR_STATUS_WORD + sizeof(UN_Err_Byte))
#define ADDR_ECCU_REG_PUSH                      (ADDR_AA_IC_EE + sizeof(ST_EACH_CHNL_IC))
#define ADDR_ContactorStatus_EE                 (ADDR_ECCU_REG_PUSH + sizeof(UN_Err_Byte))
#define ADDR_POWER_DOWN_TIME_EE                 (ADDR_ContactorStatus_EE + 1)//12�ֽ�



/******************************************************************************
*                                 ��4ҳ    �̵���������״̬���                     *
******************************************************************************/
#define ADDR_ContactorControlMode_EE                (EEPROM_HEAD_ADDR + 0x80*4)
#define ADDR_STATE_OUT_RELAY_SIGNAL                 (ADDR_ContactorControlMode_EE + 1) /*  1 �ֽ�  */
#define ADDR_SELECT_IN_SIGNAL                 		(ADDR_STATE_OUT_RELAY_SIGNAL + 1) /*  1 �ֽ�  */
#define ADDR_CURRENT_OVER_RECOVER_SETTING_TIMES    	(ADDR_SELECT_IN_SIGNAL + 1) /*  2 �ֽ�  */
#define ADDR_CURRENT_OVER_RECOVER_OPERATE_TIMES    	(ADDR_CURRENT_OVER_RECOVER_SETTING_TIMES + 2) /*  2 �ֽ�  */
#define ADDR_CURRENT_OVER_RELEASE_SETTING_TIMES   	(ADDR_CURRENT_OVER_RECOVER_OPERATE_TIMES + 2) /*  2 �ֽ�  */
#define ADDR_RELAT_CTRL_SET_TIME                    (ADDR_CURRENT_OVER_RELEASE_SETTING_TIMES + 2)//2�ֽ� ��λ 100us
#define ADDR_RELAT_REALEASE_SET_TIME                (ADDR_RELAT_CTRL_SET_TIME + 2)//2�ֽ� ��λ 100us
#define ADDR_RELAT_NEXT_CTRL_SET_TIME               (ADDR_RELAT_REALEASE_SET_TIME + 2)//2�ֽ� ��λ 100us
#define ADDR_RELAYCTRL_EE                			(ADDR_RELAT_NEXT_CTRL_SET_TIME + 2)  /*  1 �ֽ�  */
#define ADDR_RELAYOPENREASON_EE                		(ADDR_RELAYCTRL_EE + 1)  /*  2 �ֽ�  */
#define ADDR_RELAYSTATUS_EE                			(ADDR_RELAYOPENREASON_EE + 2)  /*  2 �ֽ�  */
#define ADDR_RELAYFLAG_EE                			(ADDR_RELAYSTATUS_EE + 2)  /*  2 �ֽ�  */
#define ADDR_PLY2STATE                        		(ADDR_RELAYFLAG_EE + 2) /*  1 �ֽ�  */
#define ADDR_PLY2pluseTimeCfg                       (ADDR_PLY2STATE + 1) /*�̵�������ʱ�䣬1�ֽ�*/
#define ADDR_PLY2RepeatCNT                          (ADDR_PLY2pluseTimeCfg + 1)// 1�ֽ�


/********************************************************************************
*                                 ��5ҳ   ��վ���͵Ȳ�������һҳ���������λ��                                *
*********************************************************************************/
#define ADDR_HES_Type                           (EEPROM_HEAD_ADDR + 0x80*5)//ռ��4���ֽ�
#define ADDR_Temperature_Option                 (ADDR_HES_Type + 4)// 1���ֽ�
#define ADDR_NariHES_LoginFLAG_EE               (ADDR_Temperature_Option + 1)// 4���ֽ�
#define ADDR_STO1_EE                            (ADDR_NariHES_LoginFLAG_EE + 4)// 8���ֽ�


/******************************************************************************
*                                 ��6ҳ    	class41   TCP-UDP setup
******************************************************************************/
#define          SECT_6EE                         	(EEPROM_HEAD_ADDR + 0x80*6)
#define          ADDR_TCPUDP_SET                        SECT_6EE
#define          ADDR_TCPUDP_PORT                       ADDR_TCPUDP_SET
#define          ADDR_IP_Reference_LEN                  (ADDR_TCPUDP_PORT + 2)
#define          ADDR_IP_Reference                      (ADDR_IP_Reference_LEN + 1)//Ԥ��64�ֽ�
#define          ADDR_MSS                               (ADDR_IP_Reference + 64)
#define          ADDR_NB_SIM_CONN                       (ADDR_MSS + 2)//1�ֽ�
#define          ADDR_TCP_UDP_INACTIVITY_TIME_OUT       (ADDR_NB_SIM_CONN + 1)//2�ֽ�


/******************************************************************************
*                                 ��7ҳ-9ҳ    	class42  IPv4 setup
******************************************************************************/
#define          SECT_7EE                         	(EEPROM_HEAD_ADDR + 0x80*7)
#define          ADDR_IPV4_SET                          SECT_7EE
#define          ADDR_IPV4_DL_REFERENCE_LEN             ADDR_IPV4_SET
#define          ADDR_IPV4_DL_REFERENCE                 (ADDR_IPV4_DL_REFERENCE_LEN + 1)//Ԥ��64�ֽ�
#define          ADDR_IPV4_Addr                         (ADDR_IPV4_DL_REFERENCE + 64)//4���ֽ�
#define          ADDR_MUL_IPV4_Addr_NUM                 (ADDR_IPV4_Addr + 4)
#define          ADDR_MUL_IPV4_Addr                     (ADDR_MUL_IPV4_Addr_NUM + 1)//Ԥ��5��Array����20�ֽ�
#define          ADDR_IPV4_OPTION_NUM                   (ADDR_MUL_IPV4_Addr + 20)
#define          ADDR_IPV4_OPTION                       (ADDR_IPV4_OPTION_NUM + 1)//Ԥ��5��Array����170�ֽ�(1 + 1 + 32) * 5
#define          ADDR_SUBNET_MASK                       (ADDR_IPV4_OPTION + 170)//4���ֽ�
#define          ADDR_Gateway_IP_Addr                   (ADDR_SUBNET_MASK + 4)//4���ֽ�
#define          ADDR_USE_DHCP_Flag                     (ADDR_Gateway_IP_Addr + 4)//1���ֽ�
#define          ADDR_IPV4_PRIMARY_DNS_Addr             (ADDR_USE_DHCP_Flag + 1)//4���ֽ�
#define          ADDR_IPV4_SECONDARY_DNS_Addr           (ADDR_IPV4_PRIMARY_DNS_Addr + 4)//4���ֽ�



/******************************************************************************
*								  ��10 - 14ҳ 	class44  PPP setup
******************************************************************************/
#define          SECT_10EE                         	(EEPROM_HEAD_ADDR + 0x80*10)
#define          ADDR_PPP_SET                           SECT_10EE
#define          ADDR_PHY_REFERENCE_LEN                 ADDR_PPP_SET
#define          ADDR_PHY_REFERENCE                     (ADDR_PHY_REFERENCE_LEN + 1)//Ԥ��64�ֽ�
#define          ADDR_LCP_OPTION_NUM                    (ADDR_PHY_REFERENCE + 64)//1�ֽ�
#define          ADDR_LCP_OPTION_TYPE                   (ADDR_LCP_OPTION_NUM + 1)//4�ֽ� 2 * (��ʽ(1�ֽ�) +       octring����(1�ֽ�))
#define          ADDR_LCP_OPTION                        (ADDR_LCP_OPTION_TYPE + 4)//Ԥ��140�ֽ� ֻ֧��2��array
#define          ADDR_IPCP_OPTION_NUM                   (ADDR_LCP_OPTION + 140)//1�ֽ�
#define          ADDR_IPCP_OPTION_TYPE                  (ADDR_IPCP_OPTION_NUM + 1)//4�ֽ� 2 * (��ʽ(1�ֽ�) + array����(1�ֽ�))
#define          ADDR_IPCP_OPTION                       (ADDR_IPCP_OPTION_TYPE + 4)//Ԥ��180�ֽ� ֻ֧��2��array
#define          ADDR_PPP_AUTHENATION_TYPE              (ADDR_IPCP_OPTION + 180)//1�ֽ�
#define          ADDR_PPP_STRUCT_TYPE                   (ADDR_PPP_AUTHENATION_TYPE + 1)//1�ֽ�
#define          ADDR_PPP_AUTHE_NAME_LEN                (ADDR_PPP_STRUCT_TYPE + 1)//1�ֽ�
#define          ADDR_PPP_AUTHE_PASSWORD_LEN            (ADDR_PPP_AUTHE_NAME_LEN + 1)//1�ֽ�
#define          ADDR_PPP_AUTHE_NAME                    (ADDR_PPP_AUTHE_PASSWORD_LEN + 1)//��Ԥ��64�ֽ�


/******************************************************************************
*								  ��15ҳ 	class45  GPRS modem setup
******************************************************************************/
#define          SECT_15EE                         	(EEPROM_HEAD_ADDR + 0x80*15)
#define          ADDR_GPRS_modem_SET                    SECT_15EE
#define          ADDR_APN_LEN                           ADDR_GPRS_modem_SET
#define          ADDR_APN_OCTRING                       (ADDR_APN_LEN + 1)
#define          ADDR_PIN_CODE                          (ADDR_APN_OCTRING + 32)
#define          ADDR_QOS_SERVICE                       (ADDR_PIN_CODE + 2)//10���ֽ�



/******************************************************************************
*								  ��16 - 22ҳ 	class48  IPv6 setup
******************************************************************************/
#define          SECT_16EE                         	(EEPROM_HEAD_ADDR + 0x80*16)
#define          ADDR_IPV6_SET                          SECT_16EE
#define          ADDR_IPV6_DL_REFERENCE_LEN             ADDR_IPV6_SET
#define          ADDR_IPV6_DL_REFERENCE                 (ADDR_IPV6_DL_REFERENCE_LEN + 1)//Ԥ��64�ֽ�
#define          ADDR_CONFIG_MODE                       (ADDR_IPV6_DL_REFERENCE + 64)
#define          ADDR_UNICAST_IPV6Addr_NUM              (ADDR_CONFIG_MODE + 1)
#define          ADDR_UNICAST_IPV6Addr_OCT_LEN          (ADDR_UNICAST_IPV6Addr_NUM + 1)//5���ֽ�
#define          ADDR_UNICAST_IPV6Addr                  (ADDR_UNICAST_IPV6Addr_OCT_LEN + 5)//Ԥ��3��array����150�ֽ�
#define          ADDR_MUL_UNICAST_IPV6Addr_NUM          (ADDR_UNICAST_IPV6Addr + 150)
#define          ADDR_MUL_UNICAST_IPV6Addr_OCT_LEN      (ADDR_MUL_UNICAST_IPV6Addr_NUM + 1)
#define          ADDR_MUL_UNICAST_IPV6Addr              (ADDR_MUL_UNICAST_IPV6Addr_OCT_LEN + 5)//Ԥ��3��array����150�ֽ�
#define          ADDR_GATEWAY_IPV6Addr_NUM              (ADDR_MUL_UNICAST_IPV6Addr + 150)
#define          ADDR_GATEWAY_IPV6Addr_OCT_LEN          (ADDR_GATEWAY_IPV6Addr_NUM + 1)
#define          ADDR_GATEWAY_IPV6Addr                  (ADDR_GATEWAY_IPV6Addr_OCT_LEN + 5)//Ԥ��3��array����150�ֽ�
#define          ADDR_IPV6_PRIMARY_DNS_Addr_LEN         (ADDR_GATEWAY_IPV6Addr + 150)//1���ֽ�
#define          ADDR_IPV6_PRIMARY_DNS_Addr             (ADDR_IPV6_PRIMARY_DNS_Addr_LEN + 1)//50���ֽ�
#define          ADDR_IPV6_SECONDARY_DNS_Addr_LEN       (ADDR_IPV6_PRIMARY_DNS_Addr + 50)//1���ֽ�
#define          ADDR_IPV6_SECONDARY_DNS_Addr           (ADDR_IPV6_SECONDARY_DNS_Addr_LEN + 1)//50���ֽ�
#define          ADDR_TRAFFIC_CLASS                     (ADDR_IPV6_SECONDARY_DNS_Addr + 50)//1���ֽ�
#define          ADDR_NEIGHBOR_NUM                      (ADDR_TRAFFIC_CLASS + 1)//1���ֽ�
#define          ADDR_NEIGHBOR_discover                 (ADDR_NEIGHBOR_NUM + 1)//Ԥ��8��array����56�ֽ�



/******************************************************************************
*                                 ��23-36ҳ   6.5��7.0��Լָ��              *
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
*                                 ��37-44ҳ   ��ʱ����                                 *
******************************************************************************/



/******************************************************************************
*                                 ��45 ҳ     �¼���Чͨ��                 *
******************************************************************************/
#define         SECT_45EE                          (EEPROM_HEAD_ADDR + 0x80*45)
#define 		ADDR_LOG_NULL_FLAG                 SECT_45EE //Ŀǰֻ��AEC���ʹ��



/******************************************************************************
*                                 ��46 ҳ     push filter  ���¼�ָ��                 *
******************************************************************************/
#define         SECT_46EE                          (EEPROM_HEAD_ADDR + 0x80*46)
#define         EE_push_filter    			       SECT_46EE
#define         EE_ERROR_REG1_FILTER               (EE_push_filter)
#define         EE_ERROR_REG2_FILTER               (EE_ERROR_REG1_FILTER + 1)
#define         EE_ERROR_REG3_FILTER               (EE_ERROR_REG2_FILTER + 1)
#define         EE_ERROR_REG4_FILTER               (EE_ERROR_REG3_FILTER + 1)
#define         EE_ERROR_REG5_FILTER               (EE_ERROR_REG4_FILTER + 1)
#define         EE_ERROR_REG6_FILTER               (EE_ERROR_REG5_FILTER + 1)//Ԥ��
#define         EE_ERROR_REG7_FILTER               (EE_ERROR_REG6_FILTER + 1)//Ԥ��
#define         EE_ERROR_REG8_FILTER               (EE_ERROR_REG7_FILTER + 1)//Ԥ��
#define         EE_ECCU_REG_FILTER                 (EE_ERROR_REG8_FILTER + 1)
#define         ADDR_ERROR_REGISTER                (EE_ECCU_REG_FILTER + 1)//8���ֽڣ�Ԥ����3���ֽ�
#define         ADDR_ERROR_REGISTER_PUSH           (ADDR_ERROR_REGISTER + 8)//8���ֽڣ�Ԥ����3���ֽ�
#define         ADDR_LOG_CTRL                      (ADDR_ERROR_REGISTER_PUSH + 8)



/******************************************************************************
*                                 ��47 - 48 ҳ     push_script                   *
******************************************************************************/
#define         SECT_47EE                          (EEPROM_HEAD_ADDR + 0x80*47)
#define         EE_push_script_num    			   SECT_47EE
#define         EE_push_script                     (EE_push_script_num + 2)

/******************************************************************************
*                                 ��49ҳ        Clock Daylight Saving Cfg
******************************************************************************/
#define         ADDR_CLOCK_TIME_ZONE                    (EEPROM_HEAD_ADDR + 0x80*49) /*2bytes*/
#define         ADDR_CLOCK_Daylight_Saving_Begin        (ADDR_CLOCK_TIME_ZONE + 2)
#define         ADDR_CLOCK_Daylight_Saving_End          (ADDR_CLOCK_Daylight_Saving_Begin + 12)
#define         ADDR_CLOCK_Daylight_Saving_Deviation    (ADDR_CLOCK_Daylight_Saving_End + 12)
#define         ADDR_CLOCK_Daylight_Saving_Enable       (ADDR_CLOCK_Daylight_Saving_Deviation + 1)

/******************************************************************************
*                                 ��50 - 51ҳ       GPRS����              *
******************************************************************************/
#define         SECT_50EE                          (EEPROM_HEAD_ADDR + 0x80*50)
#define         ADDR_GPRS_PARA_EE                  SECT_50EE                                //158�ֽ�
#define         ADDR_GPRS_CTRL                     (ADDR_GPRS_PARA_EE + sizeof(ST_GPRS_PARA)) //2�ֽ�
#define         ADDR_EVENTOCCURED_EE               (ADDR_GPRS_CTRL + sizeof(ST_GPRS_CTRL))    //1�ֽ�
#define         ADDR_PFTIMETEMP_EE                 (ADDR_EVENTOCCURED_EE + 1)                 //1�ֽ�
#define         ADDR_IP_TYPE_EE                    (ADDR_PFTIMETEMP_EE + 1)                   //2�ֽ� 1�ֽ���ֵ + 1�ֽ�У��
#define         ADDR_simcard_IMSI_EE               (ADDR_IP_TYPE_EE + 2)                      //31�ֽ� 1�ֽڳ��� + 30�ֽ���Ч����
#define         ADDR_simcard_ICCID_EE              (ADDR_simcard_IMSI_EE + 31)                //31�ֽ� 1�ֽڳ��� + 30�ֽ���Ч����
#define         ADDR_Modem_IMEI_EE                 (ADDR_simcard_ICCID_EE + 31)               //31�ֽ� 1�ֽڳ��� + 30�ֽ���Ч����


/******************************************************************************
*                                 ��52 - 57ҳ       NB/4G/GPRS��������              *
******************************************************************************/
#define         SECT_52EE                          (EEPROM_HEAD_ADDR + 0x80*52)

#define         ADDR_ALIVE_INTERVAL_EE              SECT_52EE //10�ֽڣ�ʵ��ʹ��5���ֽ�+2���ֽ�У��ͣ���Ԥ����3���ֽ�
#define         ADDR_NETWORK_MODE_EE                (ADDR_ALIVE_INTERVAL_EE + 10) //4�ֽڣ�2���ֽ�+2���ֽ�У���
#define         ADDR_R13_R14_SWITCH_EE              (ADDR_NETWORK_MODE_EE + 4) //4�ֽڣ�2���ֽ�+2���ֽ�У���
#define         ADDR_FOTA_ADDRESS_LEN_EE            (ADDR_R13_R14_SWITCH_EE + 4) //1�ֽ�
#define         ADDR_FOTA_ADDRESS_EE                (ADDR_FOTA_ADDRESS_LEN_EE + 1) //120�ֽ�  ���FTP����Ҫ�����ʽ��IP;Port;Path;Username;Password�� ������2a02:ce0:12:4:50dd:8fa9:b59:e9c;21;N25_T10_to_T11.pack;admin;public
#define         ADDR_AUTO_CONNECT_MODE_EE           (ADDR_FOTA_ADDRESS_EE + 120) //1�ֽ�
#define         ADDR_AUTO_REPETITIONS_EE            (ADDR_AUTO_CONNECT_MODE_EE + 1) //1�ֽ�
#define         ADDR_AUTO_REPET_DELAY_EE            (ADDR_AUTO_REPETITIONS_EE + 1) //2�ֽ�
#define         ADDR_CALLING_WINDOW_ARRAY_NUM_EE    (ADDR_AUTO_REPET_DELAY_EE + 2) //1�ֽ�
#define         ADDR_CALLING_WINDOW_EE              (ADDR_CALLING_WINDOW_ARRAY_NUM_EE + 1) //120 = 24 * 5�ֽ�
#define         ADDR_DEST_LIST_ARRAY_NUM_EE         (ADDR_CALLING_WINDOW_EE + 120) //1�ֽ�
#define         ADDR_DEST_LIST_OCT_LEN_EE           (ADDR_DEST_LIST_ARRAY_NUM_EE + 1) //5�ֽ� //���֧��5��array
#define         ADDR_DEST_LIST_EE                   (ADDR_DEST_LIST_OCT_LEN_EE + 5) //400�ֽ� //1���������80�ֽ�

/******************************************************************************
*                                 ��58ҳ                                   *
******************************************************************************/
#define ADDR_EESELFTEST_EE                           (EEPROM_HEAD_ADDR + 0x80*58)



/******************************************************************************
*                                 ��59-61ҳ                                   *
******************************************************************************/
#define IMAGE_INFO_EE                           (EEPROM_HEAD_ADDR + 0x80*59)
#define ImageBlocksStatus                       (IMAGE_INFO_EE)       //512*(256*8)=1024KB
#define ImageIdentification                     (IMAGE_INFO_EE + 256) //20bytes
#define ImageSignature                          (IMAGE_INFO_EE + 276) //2bytes
#define ImageTransferStatus_EE                  (IMAGE_INFO_EE + 278) //1byte
#define ImageRecordStatus                       (IMAGE_INFO_EE + 279) //1byte
#define ADDR_UPGRADE_FLAG                       (IMAGE_INFO_EE + 280) //4byte
#define NULL_ImageTransInfo_EE                  (IMAGE_INFO_EE + 281) /*�˵�ַ��ADDR_UPGRADE_FLAG�ص����˵�ַͣ�ã����¶����ڵ�63ҳ*/
#define NULL_ImageType_EE                       (IMAGE_INFO_EE + 310) /*�˵�ַ��ADDR_UPGRADE_FLAG�ص����˵�ַͣ�ã����¶����ڵ�63ҳ*/
#define ADDR_NEWIMAGE_SIZE                      (IMAGE_INFO_EE + 311) //4bytes��size of newimage which verified successfully
#define ADDR_OLDIMAGE_SIZE                      (IMAGE_INFO_EE + 315) //4bytes��size of image after upgrade

/******************************************************************************
*                                 ��62ҳ    ͨ�Ź�Լ�Ƿ���null�ı��         *
******************************************************************************/
#define ADDR_CHANNEL_NULL_CONFIG                (EEPROM_HEAD_ADDR + 0x80*62)//ͨ�Ź�Լ�Ĵ���ʽ��û�е�ͨ���Ƿ����Ϊnull��
#define ADDR_LP_NULL_FLAG                       (ADDR_CHANNEL_NULL_CONFIG)
#define ADDR_DAILY_PROFILE_NULL_FLAG            (ADDR_LP_NULL_FLAG + 4)
#define ADDR_DMD_PROFILE_NULL_FLAG              (ADDR_DAILY_PROFILE_NULL_FLAG + 16)
#define ADDR_CUM_DMD_PROFILE_NULL_FLAG          (ADDR_DMD_PROFILE_NULL_FLAG + 16)
#define ADDR_MON_PROFILE_NULL_FLAG              (ADDR_CUM_DMD_PROFILE_NULL_FLAG + 16)//AEC��ռ��64�ֽڣ�������ռ��16�ֽ�



/********************************************************************************
*                                 ��63ҳ                                  *
*********************************************************************************/
#define ImageTransInfo_EE                       (EEPROM_HEAD_ADDR + 0x80*63) //
#define ImageType_EE                            (ImageTransInfo_EE + 29) //��������



/******************************************************************************
*                                 ��64 - 65ҳ                                   *
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
*                                 ��66ҳ                                   *
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
*                                 ��72ҳ                                   *
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
*                                 ��84ҳ                                   *
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
*                                 ��96ҳ                                   *
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
*                                 ��108ҳ                                   *
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
*                                 ��109-111ҳ      ��Ԥ����1ҳ                             *
******************************************************************************/
#define ADDR_GPRS_PARAM                         (EEPROM_HEAD_ADDR + 0x80*109)



/******************************************************************************
*                                 ��112-113ҳ       FTP����״̬��ģ��push data�������־��ز���              *
******************************************************************************/
#define         SECT_112EE                          (EEPROM_HEAD_ADDR + 0x80*112)
#define         ADDR_FTP_UPGRADE_STATUS              SECT_112EE                     //5�ֽ�
#define         ADDR_FTP_UPGRADE_PARA_NUM           (ADDR_FTP_UPGRADE_STATUS + 5) //1�ֽ�
#define         ADDR_FTP_UPGRADE_IP_LEN             (ADDR_FTP_UPGRADE_PARA_NUM + 1) //1�ֽ�
#define         ADDR_FTP_FILE_NAME_LEN              (ADDR_FTP_UPGRADE_IP_LEN + 1) //1�ֽ�
#define         ADDR_FTP_USERNAME_LEN               (ADDR_FTP_FILE_NAME_LEN + 1) //1�ֽ�
#define         ADDR_FTP_PASSWORD_LEN               (ADDR_FTP_USERNAME_LEN + 1) //1�ֽ�
#define         ADDR_FTP_UPGRADE_PARA               (ADDR_FTP_PASSWORD_LEN + 1) //167�ֽ�
#define         ADDR_LOSS_COV_LEN                   (ADDR_FTP_UPGRADE_PARA + 167)//4�ֽ�
#define         ADDR_LOSS_COV_BACKOFF_MAX_CNT       (ADDR_LOSS_COV_LEN + 4)//1�ֽ�

/******************************************************************************
*                                 ��114ҳ                                   *
******************************************************************************/
#define Image_Check_St                          (EEPROM_HEAD_ADDR + 0x80*114)//1���ֽ�
#define ADDR_Upgrade_Fail_Reason                (Image_Check_St + 1)  /*  ���������ԭ�� 1 �ֽ� */


/******************************************************************************
*                                 ��115-116ҳ                                   *
******************************************************************************/
#define LP_CATPURE_INFO                         (EEPROM_HEAD_ADDR + 0x80*115)
#define LP_Capture_Num_ForV8_EE                 (PROFILE_PARA_EE + 22)//10bytes
#define LP_Capture_Obj_ForV8_EE                 (PROFILE_PARA_EE + 23)

/******************************************************************************
*                                 ��117-119ҳ      ������ص�            *
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
*                                 ��120 - 122ҳ     ����                              *
******************************************************************************/






/******************************************************************************
*                                 ��123ҳ     NB���                              *
******************************************************************************/
#define         SECT_123EE                          (EEPROM_HEAD_ADDR + 0x80*123)
#define         ADDR_TIMESTAMP                      SECT_123EE//4�ֽ�
#define         ADDR_LastPushCellID                 ADDR_TIMESTAMP + 64//4�ֽ�

/******************************************************************************
*                                 ��124 - 125ҳ    	*HLS invloke counter��ص�
******************************************************************************/
#define         SECT_124EE                          (EEPROM_HEAD_ADDR + 0x80*124)
#define         ADDR_Power_On_Logon_Mode           		 SECT_124EE
#define         ADDR_Event_Report_Mode             		 (ADDR_Power_On_Logon_Mode + 1)
#define         ADDR_DataTransport_Security_LOCK_Mode    (ADDR_Event_Report_Mode + 1)//��������Ƿ����


/******************************************************************************
*                                 ��126ҳ       �洢����ģʽ     *
******************************************************************************/
#define         SECT_126EE                          (EEPROM_HEAD_ADDR + 0x80*126)
#define         ADDR_32kXTALlosed                    SECT_126EE  /*������ʷ״̬�֣�1�ֽ�*/
#define         ADDR_Enter_Fact_Mode                 (ADDR_32kXTALlosed + 1)  //4�ֽ�



/******************************************************************************
*                                 ��127ҳ                                   *
******************************************************************************/
#define         ADDR_Binding_Meter_Information_EE            (EEPROM_HEAD_ADDR + 0x80*127)
#define         ADDR_Binding_Array_Num_EE                    (ADDR_Binding_Meter_Information_EE)
#define         ADDR_Binding_Client_ID_EE                    (ADDR_Binding_Array_Num_EE + 1)
#define         ADDR_Binding_HDLC_Addr_Len_EE                (ADDR_Binding_Client_ID_EE + 5)
#define         ADDR_Binding_HDLC_Addr_EE                    (ADDR_Binding_HDLC_Addr_Len_EE + 5)
#define         ADDR_Binding_PASSWORD_Len_EE                 (ADDR_Binding_HDLC_Addr_EE + 20)
#define         ADDR_Binding_PASSWORD_EE                     (ADDR_Binding_PASSWORD_Len_EE + 5)//ÿ������ռ��16�ֽ�


/******************************************************************************
*                                 ��128-129ҳ                                       *
******************************************************************************/
#define         SECT_128EE                         (EEPROM_HEAD_ADDR + 0x80 * 128)
#define         ADDR_LP1_Profile_EE                SECT_128EE
#define         ADDR_LP1_Capture_Objects_EE        (ADDR_LP1_Profile_EE + 0)   /*  196�ֽ� Ԥ��16��ͨ���ĵ�ַ�ռ�  */
#define         ADDR_LP1_Sort_Method_EE            (ADDR_LP1_Profile_EE + 196)  /*  1�ֽ�  */
#define         ADDR_LP1_Sort_Object_EE            (ADDR_LP1_Profile_EE + 197) /*  1�ֽ�  */
#define         ADDR_LP1_Capture_Period_EE         (ADDR_LP1_Profile_EE + 198) /*  4�ֽ�  */
#define         ADDR_LP1_Entries_In_Use_EE         (ADDR_LP1_Profile_EE + 202) /*  2�ֽ�  */
#define         ADDR_LP1_Profile_Entries_EE        (ADDR_LP1_Profile_EE + 204) /*  2�ֽ�  */
#define         ADDR_LP1_Current_Point_EE          (ADDR_LP1_Profile_EE + 206) /*  2�ֽ�  */
#define         ADDR_LP1_Max_Num_EE                (ADDR_LP1_Profile_EE + 208) /*  2�ֽ�  */
#define         ADDR_LP1_One_Len_EE                (ADDR_LP1_Profile_EE + 210) /*  1�ֽ�  */
#define         ADDR_LP1_Objects_Num_EE            (ADDR_LP1_Profile_EE + 211) /*  1�ֽ�  */
#define         ADDR_LP1_Objects_Transform_EE      (ADDR_LP1_Profile_EE + 212) /*  20�ֽ�  */
#define         ADDR_LP1_Repair_Inf_EE             (ADDR_LP1_Profile_EE + 232)  /*  3�ֽ�*/


/******************************************************************************
*                                 ��130ҳ ---��131   	*net quality �������߲���
******************************************************************************/
#define         SECT_130EE                     	  	  (EEPROM_HEAD_ADDR + 0x80*130)
#define         ADDR_NET_LP_Profile_EE         		  SECT_130EE
#define         ADDR_NET_LP_Capture_Objects_EE        (ADDR_NET_LP_Profile_EE + 0)   /*  220�ֽ� Ԥ��20��ͨ���ĵ�ַ�ռ�  */
#define         ADDR_NET_LP_Sort_Method_EE            (ADDR_NET_LP_Profile_EE + 220) /*  1�ֽ�  */
#define         ADDR_NET_LP_Sort_Object_EE            (ADDR_NET_LP_Profile_EE + 221) /*  1�ֽ�  */
#define         ADDR_NET_LP_Capture_Period_EE         (ADDR_NET_LP_Profile_EE + 222) /*  4�ֽ�  */
#define         ADDR_NET_LP_Entries_In_Use_EE         (ADDR_NET_LP_Profile_EE + 226) /*  2�ֽ�  */
#define         ADDR_NET_LP_Profile_Entries_EE        (ADDR_NET_LP_Profile_EE + 228) /*  2�ֽ�  */
#define         ADDR_NET_LP_Current_Point_EE          (ADDR_NET_LP_Profile_EE + 230) /*  2�ֽ�  */
#define         ADDR_NET_LP_Max_Num_EE                (ADDR_NET_LP_Profile_EE + 232) /*  2�ֽ�  */
#define         ADDR_NET_LP_One_Len_EE                (ADDR_NET_LP_Profile_EE + 234) /*  1�ֽ�  */
#define         ADDR_NET_LP_Objects_Num_EE            (ADDR_NET_LP_Profile_EE + 235) /*  1�ֽ�  */
#define         ADDR_NET_LP_Objects_Transform_EE      (ADDR_NET_LP_Profile_EE + 236) /*  20�ֽ�  */
#define         ADDR_NET_LP_Repair_Inf_EE             (ADDR_NET_LP_Profile_EE + 256)  /*  3�ֽ�*/


/******************************************************************************
*                                 ��132 - 133ҳ          ˲ʱ��ѹ�����ȸ�������             *
******************************************************************************/
#define         SECT_132EE                     	  	      (EEPROM_HEAD_ADDR + 0x80*132)
#define         ADDR_INSTANT_LP_Profile_EE                SECT_132EE
#define         ADDR_INSTANT_LP_Capture_Objects_EE        (ADDR_INSTANT_LP_Profile_EE + 0)   /*  220�ֽ� Ԥ��20��ͨ���ĵ�ַ�ռ�  */
#define         ADDR_INSTANT_LP_Sort_Method_EE            (ADDR_INSTANT_LP_Profile_EE + 220) /*  1�ֽ�  */
#define         ADDR_INSTANT_LP_Sort_Object_EE            (ADDR_INSTANT_LP_Profile_EE + 221) /*  1�ֽ�  */
#define         ADDR_INSTANT_LP_Capture_Period_EE         (ADDR_INSTANT_LP_Profile_EE + 222) /*  4�ֽ�  */
#define         ADDR_INSTANT_LP_Entries_In_Use_EE         (ADDR_INSTANT_LP_Profile_EE + 226) /*  2�ֽ�  */
#define         ADDR_INSTANT_LP_Profile_Entries_EE        (ADDR_INSTANT_LP_Profile_EE + 228) /*  2�ֽ�  */
#define         ADDR_INSTANT_LP_Current_Point_EE          (ADDR_INSTANT_LP_Profile_EE + 230) /*  2�ֽ�  */
#define         ADDR_INSTANT_LP_Max_Num_EE                (ADDR_INSTANT_LP_Profile_EE + 232) /*  2�ֽ�  */
#define         ADDR_INSTANT_LP_One_Len_EE                (ADDR_INSTANT_LP_Profile_EE + 234) /*  1�ֽ�  */
#define         ADDR_INSTANT_LP_Objects_Num_EE            (ADDR_INSTANT_LP_Profile_EE + 235) /*  1�ֽ�  */
#define         ADDR_INSTANT_LP_Objects_Transform_EE      (ADDR_INSTANT_LP_Profile_EE + 236) /*  20�ֽ�  */
#define         ADDR_INSTANT_LP_Repair_Inf_EE             (ADDR_INSTANT_LP_Profile_EE + 256)  /*  3�ֽ�*/



/******************************************************************************
						          ��134 - 167ҳ  ͨ������

******************************************************************************/
#define          SECT_134EE                          	(EEPROM_HEAD_ADDR + 0x80*134)
#define          ADDR_TIME_ENGRY_CONFIG               	SECT_134EE
#define          ADDR_CHANNLE_CAPTURE_NUM             	ADDR_TIME_ENGRY_CONFIG
#define          ADDR_ENERGY_PROFILE_CAPTURE_ITEM     	(ADDR_CHANNLE_CAPTURE_NUM + 4)   /*���40��ͨ��*/
#define          ADDR_DALIY_ENG_PROFILE_CAPTURE_ITEM  	(ADDR_ENERGY_PROFILE_CAPTURE_ITEM + 40 * 11)/*���126��ͨ��*/
#define          ADDR_MAXDMEAND_PROFILE_CAPTURE_ITEM  	(ADDR_DALIY_ENG_PROFILE_CAPTURE_ITEM + 126 * 11)/*���107��ͨ��*/
#define          ADDR_CUM_DEMAND_PROFILE_CAPTURE_IETM 	(ADDR_MAXDMEAND_PROFILE_CAPTURE_ITEM + 107 * 11)/*���106��ͨ��*/



/******************************************************************************
						          ��168ҳ  ƽ��ֵ�����������ں��¼���ز���

******************************************************************************/
#define          SECT_168EE                          	(EEPROM_HEAD_ADDR + 0x80*168)
#define          ADDR_AVERAGE_VOL_CURR_INTERVAL         SECT_168EE//1���ֽ�
#define          ADDR_CUR_OVER_THRESHOLD            	(ADDR_AVERAGE_VOL_CURR_INTERVAL + 1)//2���ֽ�
#define          ADDR_CUR_OVER_DURATION             	(ADDR_CUR_OVER_THRESHOLD + 2)//1���ֽ�
#define          ADDR_TEMPERATURE_OVER_THRESHOLD      	(ADDR_CUR_OVER_DURATION + 1)//2���ֽ�
#define          ADDR_TEMPERATURE_OVER_DURATION      	(ADDR_TEMPERATURE_OVER_THRESHOLD + 2)//2���ֽ�
#define          ADDR_TEMPERATURE_UNDER_DURATION      	(ADDR_TEMPERATURE_OVER_DURATION + 2) /*  1 �ֽ�  */
#define          ADDR_RELAY_OFF_TEMP_OVER_DURATION      (ADDR_TEMPERATURE_UNDER_DURATION + 1)//���¶����޶���Ҫ�̵�����բʱ�� 2���ֽڣ���λ�Ƿ���
#define          ADDR_MAGNETIC_DURATION         		(ADDR_RELAY_OFF_TEMP_OVER_DURATION + 2)//4���ֽ�





/******************************************************************************
						          ��169 - 170ҳ  ƽ��ֵ������������

******************************************************************************/
#define         SECT_169EE                         (EEPROM_HEAD_ADDR + 0x80*169)
#define         ADDR_BILLING_MON_DATA               SECT_169EE
#define         ADDR_BILLING_DAY_DATA_CTRL         (ADDR_BILLING_MON_DATA + 4)
#define         ADDR_485_1_ENERGY_PROFILE_RD_EE    (ADDR_BILLING_DAY_DATA_CTRL + 4)



/******************************************************************************
*                                 ��171 - 249ҳ    	*event Ԥ��5ҳ�Ĵ洢�ռ�
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
*                                 ��250ҳ-277ҳ        Push setup
******************************************************************************/

#define          PUSH_OBJECT_OFFSET                      0x80*4
#define          PUSH_OBJECT_NUM                        7  //7��push
#define          PUSH_RATAIN_NUM                        4   //PUSH��event��������
#define          PUSH_COMMAND_RATAIN_NUM                3    //PUSH�����event��������

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
*                                 ��278-287ҳ
******************************************************************************/
#define         EVN_POWER_LINE_TEMP_BUFF_EE              (EEPROM_HEAD_ADDR + 0x80*278)//19Bytes * 30 = 570Bytes, 5pages
#define         ADDR_CUR_VOL_LIMIT_TEMP_BUFF_EE          (EEPROM_HEAD_ADDR + 0x80*283)//19Bytes * 30 = 570Bytes, 5pages
#define         ADDR_TAMPER1_TEMP_BUFF_EE                (EEPROM_HEAD_ADDR + 0x80*288)//21Bytes * 30 = 630Bytes, 5pages

/******************************************************************************
*                                 ��293ҳ
******************************************************************************/
#define         ADDR_AEC_MONTH_CAPTURE_EE                (EEPROM_HEAD_ADDR + 0x80*293)
#endif

/* 4 end------------------------------------------------------------------ */

/*************************** under blank *************************************/
