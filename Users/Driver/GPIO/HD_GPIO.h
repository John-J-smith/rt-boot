/****************************************************************
Description: HD_GPIO.h
Author: hx
Notes: GPIO驱动头文件
*****************************************************************/
#ifndef __HD_GPIO_H
#define __HD_GPIO_H
/*- 1.Macro-----------------------------------------------------*/

#define  Pin_0                    0
#define  Pin_1                    1
#define  Pin_2                    2
#define  Pin_3                    3
#define  Pin_4                    4
#define  Pin_5                    5
#define  Pin_6                    6
#define  Pin_7                    7
#define  Pin_8                    8
#define  Pin_9                    9
#define  Pin_10                   10
#define  Pin_11                   11
#define  Pin_12                   12
#define  Pin_13                   13
#define  Pin_14                   14
#define  Pin_15                   15


#define  PUPDR_UP    1 //推挽
#define  PUPDR_OD    0 //开漏
#define  AIN         2

#define  OUTPUT      1
#define  INPUT       0 

#define  HD_System_GPIO_DATA(GPIOx,GPIO_PIN,ON) if(ON)GPIOx->PTSET |= (1<<GPIO_PIN);else GPIOx->PTCLR |= (1<<GPIO_PIN);

/*- GPIO A------------------------------------------*/
#define  IO_RELAY_POWER_CT_PORT         HT_GPIOA
#define  IO_RELAY_POWER_CT_PIN          Pin_4
#define  IO_RELAY_POWER_CT_INPUT        HD_System_GPIO_DIR(IO_RELAY_POWER_CT_PORT, IO_RELAY_POWER_CT_PIN, PUPDR_UP, INPUT)
#define  IO_RELAY_POWER_CT_OUTPUT       HD_System_GPIO_DIR(IO_RELAY_POWER_CT_PORT, IO_RELAY_POWER_CT_PIN, PUPDR_UP, OUTPUT)
#define  IO_RELAY_POWER_CT_H            HD_System_GPIO_DATA(IO_RELAY_POWER_CT_PORT, IO_RELAY_POWER_CT_PIN, 1)
#define  IO_RELAY_POWER_CT_L            HD_System_GPIO_DATA(IO_RELAY_POWER_CT_PORT, IO_RELAY_POWER_CT_PIN, 0)
#define  IO_RELAY_POWER_CT_PV           HD_System_GPIO_Read(IO_RELAY_POWER_CT_PORT, IO_RELAY_POWER_CT_PIN)

#define  IO_DF_WP_PORT                  HT_GPIOA
#define  IO_DF_WP_PIN                   Pin_5
#define  IO_DF_WP_INPUT                 HD_System_GPIO_DIR(IO_DF_WP_PORT, IO_DF_WP_PIN, PUPDR_UP, INPUT)
#define  IO_DF_WP_OUTPUT                HD_System_GPIO_DIR(IO_DF_WP_PORT, IO_DF_WP_PIN, PUPDR_UP, OUTPUT)
#define  IO_DF_WP_H                     HD_System_GPIO_DATA(IO_DF_WP_PORT, IO_DF_WP_PIN, 1)
#define  IO_DF_WP_L                     HD_System_GPIO_DATA(IO_DF_WP_PORT, IO_DF_WP_PIN, 0)
#define  IO_DF_WP_PV                    HD_System_GPIO_Read(IO_DF_WP_PORT, IO_DF_WP_PIN)

#define  IO_KEY_DT_PORT                 HT_GPIOA
#define  IO_KEY_DT_PIN                  Pin_7
#define  IO_KEY_DT_INPUT                HD_System_GPIO_DIR(IO_KEY_DT_PORT, IO_KEY_DT_PIN, PUPDR_UP, INPUT)
#define  IO_KEY_DT_OUTPUT               HD_System_GPIO_DIR(IO_KEY_DT_PORT, IO_KEY_DT_PIN, PUPDR_UP, OUTPUT)
#define  IO_KEY_DT_H                    HD_System_GPIO_DATA(IO_KEY_DT_PORT, IO_KEY_DT_PIN, 1)
#define  IO_KEY_DT_L                    HD_System_GPIO_DATA(IO_KEY_DT_PORT, IO_KEY_DT_PIN, 0)
#define  IO_KEY_DT_PV                   HD_System_GPIO_Read(IO_KEY_DT_PORT, IO_KEY_DT_PIN)

#define  IO_SUP_DT_PORT                 HT_GPIOA
#define  IO_SUP_DT_PIN                  Pin_13
#define  IO_SUP_DT_INPUT                HD_System_GPIO_DIR(IO_SUP_DT_PORT, IO_SUP_DT_PIN, PUPDR_UP, INPUT)
#define  IO_SUP_DT_OUTPUT               HD_System_GPIO_DIR(IO_SUP_DT_PORT, IO_SUP_DT_PIN, PUPDR_UP, OUTPUT)
#define  IO_SUP_DT_H                    HD_System_GPIO_DATA(IO_SUP_DT_PORT, IO_SUP_DT_PIN, 1)
#define  IO_SUP_DT_L                    HD_System_GPIO_DATA(IO_SUP_DT_PORT, IO_SUP_DT_PIN, 0)
#define  IO_SUP_DT_PV                   HD_System_GPIO_Read(IO_SUP_DT_PORT, IO_SUP_DT_PIN)

#define  IO_RELAYA_LED_PORT             HT_GPIOA
#define  IO_RELAYA_LED_PIN              Pin_8
#define  IO_RELAYA_LED_INPUT            HD_System_GPIO_DIR(IO_RELAYA_LED_PORT, IO_RELAYA_LED_PIN, PUPDR_UP, INPUT)
#define  IO_RELAYA_LED_OUTPUT           HD_System_GPIO_DIR(IO_RELAYA_LED_PORT, IO_RELAYA_LED_PIN, PUPDR_UP, OUTPUT)
#define  IO_RELAYA_LED_H                HD_System_GPIO_DATA(IO_RELAYA_LED_PORT, IO_RELAYA_LED_PIN, 1)
#define  IO_RELAYA_LED_L                HD_System_GPIO_DATA(IO_RELAYA_LED_PORT, IO_RELAYA_LED_PIN, 0)
#define  IO_RELAYA_LED_PV               HD_System_GPIO_Read(IO_RELAYA_LED_PORT, IO_RELAYA_LED_PIN)


/*- GPIO B------------------------------------------*/


#define  IO_RELAYB_LED_PORT             HT_GPIOB
#define  IO_RELAYB_LED_PIN              Pin_4
#define  IO_RELAYB_LED_INPUT            HD_System_GPIO_DIR(IO_RELAYB_LED_PORT, IO_RELAYB_LED_PIN, PUPDR_UP, INPUT)
#define  IO_RELAYB_LED_OUTPUT           HD_System_GPIO_DIR(IO_RELAYB_LED_PORT, IO_RELAYB_LED_PIN, PUPDR_UP, OUTPUT)
#define  IO_RELAYB_LED_H                HD_System_GPIO_DATA(IO_RELAYB_LED_PORT, IO_RELAYB_LED_PIN, 1)
#define  IO_RELAYB_LED_L                HD_System_GPIO_DATA(IO_RELAYB_LED_PORT, IO_RELAYB_LED_PIN, 0)
#define  IO_RELAYB_LED_PV               HD_System_GPIO_Read(IO_RELAYB_LED_PORT, IO_RELAYB_LED_PIN)

#define  IO_RELAYC_LED_PORT             HT_GPIOB
#define  IO_RELAYC_LED_PIN              Pin_5
#define  IO_RELAYC_LED_INPUT            HD_System_GPIO_DIR(IO_RELAYC_LED_PORT, IO_RELAYC_LED_PIN, PUPDR_UP, INPUT)
#define  IO_RELAYC_LED_OUTPUT           HD_System_GPIO_DIR(IO_RELAYC_LED_PORT, IO_RELAYC_LED_PIN, PUPDR_UP, OUTPUT)
#define  IO_RELAYC_LED_H                HD_System_GPIO_DATA(IO_RELAYC_LED_PORT, IO_RELAYC_LED_PIN, 1)
#define  IO_RELAYC_LED_L                HD_System_GPIO_DATA(IO_RELAYC_LED_PORT, IO_RELAYC_LED_PIN, 0)
#define  IO_RELAYC_LED_PV               HD_System_GPIO_Read(IO_RELAYC_LED_PORT, IO_RELAYC_LED_PIN)

#define  IO_LED_RUN_PORT                HT_GPIOB
#define  IO_LED_RUN_PIN                 Pin_9
#define  IO_LED_RUN_INPUT               HD_System_GPIO_DIR(IO_LED_RUN_PORT, IO_LED_RUN_PIN, PUPDR_UP, INPUT)
#define  IO_LED_RUN_OUTPUT              HD_System_GPIO_DIR(IO_LED_RUN_PORT, IO_LED_RUN_PIN, PUPDR_UP, OUTPUT)
#define  IO_LED_RUN_H                   HD_System_GPIO_DATA(IO_LED_RUN_PORT, IO_LED_RUN_PIN, 1)
#define  IO_LED_RUN_L                   HD_System_GPIO_DATA(IO_LED_RUN_PORT, IO_LED_RUN_PIN, 0)
#define  IO_LED_RUN_PV                  HD_System_GPIO_Read(IO_LED_RUN_PORT, IO_LED_RUN_PIN)
#define  IO_LED_RUN_TOGG                do{ if(IO_LED_RUN_PV){IO_LED_RUN_L;} else{IO_LED_RUN_H;} }while(0)

#define  IO_LED_TX_PORT                 HT_GPIOB
#define  IO_LED_TX_PIN                  Pin_8
#define  IO_LED_TX_INPUT                HD_System_GPIO_DIR(IO_LED_TX_PORT, IO_LED_TX_PIN, PUPDR_UP, INPUT)
#define  IO_LED_TX_OUTPUT               HD_System_GPIO_DIR(IO_LED_TX_PORT, IO_LED_TX_PIN, PUPDR_UP, OUTPUT)
#define  IO_LED_TX_H                    HD_System_GPIO_DATA(IO_LED_TX_PORT, IO_LED_TX_PIN, 1)
#define  IO_LED_TX_L                    HD_System_GPIO_DATA(IO_LED_TX_PORT, IO_LED_TX_PIN, 0)
#define  IO_LED_TX_PV                   HD_System_GPIO_Read(IO_LED_TX_PORT, IO_LED_TX_PIN)
#define  IO_LED_TX_TOGG                 do{ if(IO_LED_TX_PV){IO_LED_TX_L;} else{IO_LED_TX_H;} }while(0)

#define  IO_LED_RX_PORT                 HT_GPIOB
#define  IO_LED_RX_PIN                  Pin_7
#define  IO_LED_RX_INPUT                HD_System_GPIO_DIR(IO_LED_RX_PORT, IO_LED_RX_PIN, PUPDR_UP, INPUT)
#define  IO_LED_RX_OUTPUT               HD_System_GPIO_DIR(IO_LED_RX_PORT, IO_LED_RX_PIN, PUPDR_UP, OUTPUT)
#define  IO_LED_RX_H                    HD_System_GPIO_DATA(IO_LED_RX_PORT, IO_LED_RX_PIN, 1)
#define  IO_LED_RX_L                    HD_System_GPIO_DATA(IO_LED_RX_PORT, IO_LED_RX_PIN, 0)
#define  IO_LED_RX_PV                   HD_System_GPIO_Read(IO_LED_RX_PORT, IO_LED_RX_PIN)
#define  IO_LED_RX_TOGG                 do{ if(IO_LED_RX_PV){IO_LED_RX_L;} else{IO_LED_RX_H;} }while(0)

#define  IO_485_LED_PORT                HT_GPIOB
#define  IO_485_LED_PIN                 Pin_10
#define  IO_485_LED_INPUT               HD_System_GPIO_DIR(IO_485_LED_PORT, IO_485_LED_PIN, PUPDR_UP, INPUT)
#define  IO_485_LED_OUTPUT              HD_System_GPIO_DIR(IO_485_LED_PORT, IO_485_LED_PIN, PUPDR_UP, OUTPUT)
#define  IO_485_LED_H                   HD_System_GPIO_DATA(IO_485_LED_PORT, IO_485_LED_PIN, 1)
#define  IO_485_LED_L                   HD_System_GPIO_DATA(IO_485_LED_PORT, IO_485_LED_PIN, 0)
#define  IO_485_LED_PV                  HD_System_GPIO_Read(IO_485_LED_PORT, IO_485_LED_PIN)

#define  IO_OPEN_T_PORT                 HT_GPIOB
#define  IO_OPEN_T_PIN                  Pin_6
#define  IO_OPEN_T_INPUT                HD_System_GPIO_DIR(IO_OPEN_T_PORT, IO_OPEN_T_PIN, PUPDR_UP, INPUT)
#define  IO_OPEN_T_OUTPUT               HD_System_GPIO_DIR(IO_OPEN_T_PORT, IO_OPEN_T_PIN, PUPDR_UP, OUTPUT)
#define  IO_OPEN_T_H                    HD_System_GPIO_DATA(IO_OPEN_T_PORT, IO_OPEN_T_PIN, 1)
#define  IO_OPEN_T_L                    HD_System_GPIO_DATA(IO_OPEN_T_PORT, IO_OPEN_T_PIN, 0)
#define  IO_OPEN_T_PV                   HD_System_GPIO_Read(IO_OPEN_T_PORT, IO_OPEN_T_PIN)

#define  IO_RS485_2_DIR_PORT            HT_GPIOB
#define  IO_RS485_2_DIR_PIN             Pin_11
#define  IO_RS485_2_DIR_INPUT           HD_System_GPIO_DIR(IO_RS485_2_DIR_PORT, IO_RS485_2_DIR_PIN, PUPDR_UP, INPUT)
#define  IO_RS485_2_DIR_OUTPUT          HD_System_GPIO_DIR(IO_RS485_2_DIR_PORT, IO_RS485_2_DIR_PIN, PUPDR_UP, OUTPUT)
#define  IO_RS485_2_DIR_H               HD_System_GPIO_DATA(IO_RS485_2_DIR_PORT, IO_RS485_2_DIR_PIN, 1)
#define  IO_RS485_2_DIR_L               HD_System_GPIO_DATA(IO_RS485_2_DIR_PORT, IO_RS485_2_DIR_PIN, 0)

#define  IO_SIG4_LED_PORT               HT_GPIOB
#define  IO_SIG4_LED_PIN                Pin_12
#define  IO_SIG4_LED_INPUT              HD_System_GPIO_DIR(IO_SIG4_LED_PORT, IO_SIG4_LED_PIN, PUPDR_UP, INPUT)
#define  IO_SIG4_LED_OUTPUT             HD_System_GPIO_DIR(IO_SIG4_LED_PORT, IO_SIG4_LED_PIN, PUPDR_UP, OUTPUT)
#define  IO_SIG4_LED_H                  HD_System_GPIO_DATA(IO_SIG4_LED_PORT, IO_SIG4_LED_PIN, 1)
#define  IO_SIG4_LED_L                  HD_System_GPIO_DATA(IO_SIG4_LED_PORT, IO_SIG4_LED_PIN, 0)

#define  IO_SIG3_LED_PORT               HT_GPIOB
#define  IO_SIG3_LED_PIN                Pin_14
#define  IO_SIG3_LED_INPUT              HD_System_GPIO_DIR(IO_SIG3_LED_PORT, IO_SIG3_LED_PIN, PUPDR_UP, INPUT)
#define  IO_SIG3_LED_OUTPUT             HD_System_GPIO_DIR(IO_SIG3_LED_PORT, IO_SIG3_LED_PIN, PUPDR_UP, OUTPUT)
#define  IO_SIG3_LED_H                  HD_System_GPIO_DATA(IO_SIG3_LED_PORT, IO_SIG3_LED_PIN, 1)
#define  IO_SIG3_LED_L                  HD_System_GPIO_DATA(IO_SIG3_LED_PORT, IO_SIG3_LED_PIN, 0)


/*- GPIO C------------------------------------------*/
#define  IO_RS485_1_TX_PORT             HT_GPIOC
#define  IO_RS485_1_TX_PIN              Pin_0
#define  IO_RS485_1_TX_INPUT            HD_System_GPIO_DIR(IO_RS485_1_TX_PORT, IO_RS485_1_TX_PIN, PUPDR_UP, INPUT)
#define  IO_RS485_1_TX_OUTPUT           HD_System_GPIO_DIR(IO_RS485_1_TX_PORT, IO_RS485_1_TX_PIN, PUPDR_UP, OUTPUT)
#define  IO_RS485_1_TX_H                HD_System_GPIO_DATA(IO_RS485_1_TX_PORT, IO_RS485_1_TX_PIN, 1)
#define  IO_RS485_1_TX_L                HD_System_GPIO_DATA(IO_RS485_1_TX_PORT, IO_RS485_1_TX_PIN, 0)
#define  IO_RS485_1_TX_PV               HD_System_GPIO_Read(IO_RS485_1_TX_PORT, IO_RS485_1_TX_PIN)

#define  IO_RS485_1_RX_PORT             HT_GPIOC
#define  IO_RS485_1_RX_PIN              Pin_1
#define  IO_RS485_1_RX_INPUT            HD_System_GPIO_DIR(IO_RS485_1_RX_PORT, IO_RS485_1_RX_PIN, PUPDR_UP, INPUT)
#define  IO_RS485_1_RX_OUTPUT           HD_System_GPIO_DIR(IO_RS485_1_RX_PORT, IO_RS485_1_RX_PIN, PUPDR_UP, OUTPUT)
#define  IO_RS485_1_RX_H                HD_System_GPIO_DATA(IO_RS485_1_RX_PORT, IO_RS485_1_RX_PIN, 1)
#define  IO_RS485_1_RX_L                HD_System_GPIO_DATA(IO_RS485_1_RX_PORT, IO_RS485_1_RX_PIN, 0)
#define  IO_RS485_1_RX_PV               HD_System_GPIO_Read(IO_RS485_1_RX_PORT, IO_RS485_1_RX_PIN)

#define  IO_RX_NB_PORT                  HT_GPIOC
#define  IO_RX_NB_PIN                   Pin_2
#define  IO_RX_NB_INPUT                 HD_System_GPIO_DIR(IO_RX_NB_PORT, IO_RX_NB_PIN, PUPDR_UP, INPUT)
#define  IO_RX_NB_OUTPUT                HD_System_GPIO_DIR(IO_RX_NB_PORT, IO_RX_NB_PIN, PUPDR_UP, OUTPUT)
#define  IO_RX_NB_H                     HD_System_GPIO_DATA(IO_RX_NB_PORT, IO_RX_NB_PIN, 1)
#define  IO_RX_NB_L                     HD_System_GPIO_DATA(IO_RX_NB_PORT, IO_RX_NB_PIN, 0)
#define  IO_RX_NB_PV                    HD_System_GPIO_Read(IO_RX_NB_PORT, IO_RX_NB_PIN)

#define  IO_TX_NB_PORT                  HT_GPIOC
#define  IO_TX_NB_PIN                   Pin_3
#define  IO_TX_NB_INPUT                 HD_System_GPIO_DIR(IO_TX_NB_PORT, IO_TX_NB_PIN, PUPDR_UP, INPUT)
#define  IO_TX_NB_OUTPUT                HD_System_GPIO_DIR(IO_TX_NB_PORT, IO_TX_NB_PIN, PUPDR_UP, OUTPUT)
#define  IO_TX_NB_H                     HD_System_GPIO_DATA(IO_TX_NB_PORT, IO_TX_NB_PIN, 1)
#define  IO_TX_NB_L                     HD_System_GPIO_DATA(IO_TX_NB_PORT, IO_TX_NB_PIN, 0)
#define  IO_TX_NB_PV                    HD_System_GPIO_Read(IO_TX_NB_PORT, IO_TX_NB_PIN)

#define  IO_DF_SDO_PORT                 HT_GPIOC
#define  IO_DF_SDO_PIN                  Pin_4
#define  IO_DF_SDO_INPUT                HD_System_GPIO_DIR(IO_DF_SDO_PORT, IO_DF_SDO_PIN, PUPDR_UP, INPUT)
#define  IO_DF_SDO_OUTPUT               HD_System_GPIO_DIR(IO_DF_SDO_PORT, IO_DF_SDO_PIN, PUPDR_UP, OUTPUT)
#define  IO_DF_SDO_H                    HD_System_GPIO_DATA(IO_DF_SDO_PORT, IO_DF_SDO_PIN, 1)
#define  IO_DF_SDO_L                    HD_System_GPIO_DATA(IO_DF_SDO_PORT, IO_DF_SDO_PIN, 0)
#define  IO_DF_SDO_PV                   HD_System_GPIO_Read(IO_DF_SDO_PORT, IO_DF_SDO_PIN)

#define  IO_DF_SDI_PORT                 HT_GPIOC
#define  IO_DF_SDI_PIN                  Pin_5
#define  IO_DF_SDI_INPUT                HD_System_GPIO_DIR(IO_DF_SDI_PORT, IO_DF_SDI_PIN, PUPDR_UP, INPUT)
#define  IO_DF_SDI_OUTPUT               HD_System_GPIO_DIR(IO_DF_SDI_PORT, IO_DF_SDI_PIN, PUPDR_UP, OUTPUT)
#define  IO_DF_SDI_H                    HD_System_GPIO_DATA(IO_DF_SDI_PORT, IO_DF_SDI_PIN, 1)
#define  IO_DF_SDI_L                    HD_System_GPIO_DATA(IO_DF_SDI_PORT, IO_DF_SDI_PIN, 0)
#define  IO_DF_SDI_PV                   HD_System_GPIO_Read(IO_DF_SDI_PORT, IO_DF_SDI_PIN)

#define  IO_DF_CLK_PORT                 HT_GPIOC
#define  IO_DF_CLK_PIN                  Pin_6
#define  IO_DF_CLK_INPUT                HD_System_GPIO_DIR(IO_DF_CLK_PORT, IO_DF_CLK_PIN, PUPDR_UP, INPUT)
#define  IO_DF_CLK_OUTPUT               HD_System_GPIO_DIR(IO_DF_CLK_PORT, IO_DF_CLK_PIN, PUPDR_UP, OUTPUT)
#define  IO_DF_CLK_H                    HD_System_GPIO_DATA(IO_DF_CLK_PORT, IO_DF_CLK_PIN, 1)
#define  IO_DF_CLK_L                    HD_System_GPIO_DATA(IO_DF_CLK_PORT, IO_DF_CLK_PIN, 0)
#define  IO_DF_CLK_PV                   HD_System_GPIO_Read(IO_DF_CLK_PORT, IO_DF_CLK_PIN)

#define  IO_DF_CS_PORT                  HT_GPIOC
#define  IO_DF_CS_PIN                   Pin_7
#define  IO_DF_CS_INPUT                 HD_System_GPIO_DIR(IO_DF_CS_PORT, IO_DF_CS_PIN, PUPDR_UP, INPUT)
#define  IO_DF_CS_OUTPUT                HD_System_GPIO_DIR(IO_DF_CS_PORT, IO_DF_CS_PIN, PUPDR_UP, OUTPUT)
#define  IO_DF_CS_H                     HD_System_GPIO_DATA(IO_DF_CS_PORT, IO_DF_CS_PIN, 1)
#define  IO_DF_CS_L                     HD_System_GPIO_DATA(IO_DF_CS_PORT, IO_DF_CS_PIN, 0)
#define  IO_DF_CS_PV                    HD_System_GPIO_Read(IO_DF_CS_PORT, IO_DF_CS_PIN)

#define  IO_RS485_1_DIR_PORT            HT_GPIOC
#define  IO_RS485_1_DIR_PIN             Pin_8
#define  IO_RS485_1_DIR_INPUT           HD_System_GPIO_DIR(IO_RS485_1_DIR_PORT, IO_RS485_1_DIR_PIN, PUPDR_UP, INPUT)
#define  IO_RS485_1_DIR_OUTPUT          HD_System_GPIO_DIR(IO_RS485_1_DIR_PORT, IO_RS485_1_DIR_PIN, PUPDR_UP, OUTPUT)
#define  IO_RS485_1_DIR_H               HD_System_GPIO_DATA(IO_RS485_1_DIR_PORT, IO_RS485_1_DIR_PIN, 1)
#define  IO_RS485_1_DIR_L               HD_System_GPIO_DATA(IO_RS485_1_DIR_PORT, IO_RS485_1_DIR_PIN, 0)

#define  IO_NB_PWR_PORT                 HT_GPIOC
#define  IO_NB_PWR_PIN                  Pin_9
#define  IO_NB_PWR_INPUT                HD_System_GPIO_DIR(IO_NB_PWR_PORT, IO_NB_PWR_PIN, PUPDR_UP, INPUT)
#define  IO_NB_PWR_OUTPUT               HD_System_GPIO_DIR(IO_NB_PWR_PORT, IO_NB_PWR_PIN, PUPDR_UP, OUTPUT)
#define  IO_NB_PWR_H                    HD_System_GPIO_DATA(IO_NB_PWR_PORT, IO_NB_PWR_PIN, 1)
#define  IO_NB_PWR_L                    HD_System_GPIO_DATA(IO_NB_PWR_PORT, IO_NB_PWR_PIN, 0)

#define  IO_RST_IOT_PORT                HT_GPIOC
#define  IO_RST_IOT_PIN                 Pin_10
#define  IO_RST_IOT_INPUT               HD_System_GPIO_DIR(IO_RST_IOT_PORT, IO_RST_IOT_PIN, PUPDR_UP, INPUT)
#define  IO_RST_IOT_OUTPUT              HD_System_GPIO_DIR(IO_RST_IOT_PORT, IO_RST_IOT_PIN, PUPDR_UP, OUTPUT)
#define  IO_RST_IOT_H                   HD_System_GPIO_DATA(IO_RST_IOT_PORT, IO_RST_IOT_PIN, 1)
#define  IO_RST_IOT_L                   HD_System_GPIO_DATA(IO_RST_IOT_PORT, IO_RST_IOT_PIN, 0)
#define  IO_RST_IOT_PV                  HD_System_GPIO_Read(IO_RST_IOT_PORT, IO_RST_IOT_PIN)

#define  IO_SIG1_LED_PORT               HT_GPIOC
#define  IO_SIG1_LED_PIN                Pin_12
#define  IO_SIG1_LED_INPUT              HD_System_GPIO_DIR(IO_SIG1_LED_PORT, IO_SIG1_LED_PIN, PUPDR_UP, INPUT)
#define  IO_SIG1_LED_OUTPUT             HD_System_GPIO_DIR(IO_SIG1_LED_PORT, IO_SIG1_LED_PIN, PUPDR_UP, OUTPUT)
#define  IO_SIG1_LED_H                  HD_System_GPIO_DATA(IO_SIG1_LED_PORT, IO_SIG1_LED_PIN, 1)
#define  IO_SIG1_LED_L                  HD_System_GPIO_DATA(IO_SIG1_LED_PORT, IO_SIG1_LED_PIN, 0)
#define  IO_SIG1_LED_PV                 HD_System_GPIO_Read(IO_SIG1_LED_PORT, IO_SIG1_LED_PIN)

#define  IO_SIG2_LED_PORT               HT_GPIOC
#define  IO_SIG2_LED_PIN                Pin_11
#define  IO_SIG2_LED_INPUT              HD_System_GPIO_DIR(IO_SIG2_LED_PORT, IO_SIG2_LED_PIN, PUPDR_UP, INPUT)
#define  IO_SIG2_LED_OUTPUT             HD_System_GPIO_DIR(IO_SIG2_LED_PORT, IO_SIG2_LED_PIN, PUPDR_UP, OUTPUT)
#define  IO_SIG2_LED_H                  HD_System_GPIO_DATA(IO_SIG2_LED_PORT, IO_SIG2_LED_PIN, 1)
#define  IO_SIG2_LED_L                  HD_System_GPIO_DATA(IO_SIG2_LED_PORT, IO_SIG2_LED_PIN, 0)
#define  IO_SIG2_LED_PV                 HD_System_GPIO_Read(IO_SIG2_LED_PORT, IO_SIG2_LED_PIN)

#define  IO_I2C_SCL_PORT                HT_GPIOC
#define  IO_I2C_SCL_PIN                 Pin_13
#define  IO_I2C_SCL_INPUT               HD_System_GPIO_DIR(IO_I2C_SCL_PORT, IO_I2C_SCL_PIN, PUPDR_UP, INPUT)
#define  IO_I2C_SCL_OUTPUT              HD_System_GPIO_DIR(IO_I2C_SCL_PORT, IO_I2C_SCL_PIN, PUPDR_UP, OUTPUT)
#define  IO_I2C_SCL_H                   HD_System_GPIO_DATA(IO_I2C_SCL_PORT, IO_I2C_SCL_PIN, 1)
#define  IO_I2C_SCL_L                   HD_System_GPIO_DATA(IO_I2C_SCL_PORT, IO_I2C_SCL_PIN, 0)
#define  IO_I2C_SCL_PV                  HD_System_GPIO_Read(IO_I2C_SCL_PORT, IO_I2C_SCL_PIN)

#define  IO_I2C_SDA_PORT                HT_GPIOC
#define  IO_I2C_SDA_PIN                 Pin_14
#define  IO_I2C_SDA_INPUT               HD_System_GPIO_DIR(IO_I2C_SDA_PORT, IO_I2C_SDA_PIN, PUPDR_UP, INPUT)
#define  IO_I2C_SDA_OUTPUT              HD_System_GPIO_DIR(IO_I2C_SDA_PORT, IO_I2C_SDA_PIN, PUPDR_UP, OUTPUT)
#define  IO_I2C_SDA_H                   HD_System_GPIO_DATA(IO_I2C_SDA_PORT, IO_I2C_SDA_PIN, 1)
#define  IO_I2C_SDA_L                   HD_System_GPIO_DATA(IO_I2C_SDA_PORT, IO_I2C_SDA_PIN, 0)
#define  IO_I2C_SDA_PV                  HD_System_GPIO_Read(IO_I2C_SDA_PORT, IO_I2C_SDA_PIN)

/*- GPIO D------------------------------------------*/
#define  IO_RELAY_C_DT_PORT             HT_GPIOD
#define  IO_RELAY_C_DT_PIN              Pin_11
#define  IO_RELAY_C_DT_INPUT            HD_System_GPIO_DIR(IO_RELAY_C_DT_PORT, IO_RELAY_C_DT_PIN, PUPDR_UP, INPUT)
#define  IO_RELAY_C_DT_OUTPUT           HD_System_GPIO_DIR(IO_RELAY_C_DT_PORT, IO_RELAY_C_DT_PIN, PUPDR_UP, OUTPUT)
#define  IO_RELAY_C_DT_H                HD_System_GPIO_DATA(IO_RELAY_C_DT_PORT, IO_RELAY_C_DT_PIN, 1)
#define  IO_RELAY_C_DT_L                HD_System_GPIO_DATA(IO_RELAY_C_DT_PORT, IO_RELAY_C_DT_PIN, 0)
#define  IO_RELAY_C_DT_PV               HD_System_GPIO_Read(IO_RELAY_C_DT_PORT, IO_RELAY_C_DT_PIN)

#define  IO_RELAY_B_DT_PORT             HT_GPIOD
#define  IO_RELAY_B_DT_PIN              Pin_12
#define  IO_RELAY_B_DT_INPUT            HD_System_GPIO_DIR(IO_RELAY_B_DT_PORT, IO_RELAY_B_DT_PIN, PUPDR_UP, INPUT)
#define  IO_RELAY_B_DT_OUTPUT           HD_System_GPIO_DIR(IO_RELAY_B_DT_PORT, IO_RELAY_B_DT_PIN, PUPDR_UP, OUTPUT)
#define  IO_RELAY_B_DT_H                HD_System_GPIO_DATA(IO_RELAY_B_DT_PORT, IO_RELAY_B_DT_PIN, 1)
#define  IO_RELAY_B_DT_L                HD_System_GPIO_DATA(IO_RELAY_B_DT_PORT, IO_RELAY_B_DT_PIN, 0)
#define  IO_RELAY_B_DT_PV               HD_System_GPIO_Read(IO_RELAY_B_DT_PORT, IO_RELAY_B_DT_PIN)

#define  IO_RELAY_A_DT_PORT             HT_GPIOD
#define  IO_RELAY_A_DT_PIN              Pin_13
#define  IO_RELAY_A_DT_INPUT            HD_System_GPIO_DIR(IO_RELAY_A_DT_PORT, IO_RELAY_A_DT_PIN, PUPDR_UP, INPUT)
#define  IO_RELAY_A_DT_OUTPUT           HD_System_GPIO_DIR(IO_RELAY_A_DT_PORT, IO_RELAY_A_DT_PIN, PUPDR_UP, OUTPUT)
#define  IO_RELAY_A_DT_H                HD_System_GPIO_DATA(IO_RELAY_A_DT_PORT, IO_RELAY_A_DT_PIN, 1)
#define  IO_RELAY_A_DT_L                HD_System_GPIO_DATA(IO_RELAY_A_DT_PORT, IO_RELAY_A_DT_PIN, 0)
#define  IO_RELAY_A_DT_PV               HD_System_GPIO_Read(IO_RELAY_A_DT_PORT, IO_RELAY_A_DT_PIN)

#define  IO_RELAY_A_PORT                HT_GPIOD
#define  IO_RELAY_A_PIN                 Pin_15
#define  IO_RELAY_A_INPUT               HD_System_GPIO_DIR(IO_RELAY_A_PORT, IO_RELAY_A_PIN, PUPDR_UP, INPUT)
#define  IO_RELAY_A_OUTPUT              HD_System_GPIO_DIR(IO_RELAY_A_PORT, IO_RELAY_A_PIN, PUPDR_UP, OUTPUT)
#define  IO_RELAY_A_H                   HD_System_GPIO_DATA(IO_RELAY_A_PORT, IO_RELAY_A_PIN, 1)
#define  IO_RELAY_A_L                   HD_System_GPIO_DATA(IO_RELAY_A_PORT, IO_RELAY_A_PIN, 0)

#define  IO_RELAY_B_PORT                HT_GPIOD
#define  IO_RELAY_B_PIN                 Pin_14
#define  IO_RELAY_B_INPUT               HD_System_GPIO_DIR(IO_RELAY_B_PORT, IO_RELAY_B_PIN, PUPDR_UP, INPUT)
#define  IO_RELAY_B_OUTPUT              HD_System_GPIO_DIR(IO_RELAY_B_PORT, IO_RELAY_B_PIN, PUPDR_UP, OUTPUT)
#define  IO_RELAY_B_H                   HD_System_GPIO_DATA(IO_RELAY_B_PORT, IO_RELAY_B_PIN, 1)
#define  IO_RELAY_B_L                   HD_System_GPIO_DATA(IO_RELAY_B_PORT, IO_RELAY_B_PIN, 0)

/*- GPIO E------------------------------------------*/
#define  IO_EE_WP_PORT                  HT_GPIOE
#define  IO_EE_WP_PIN                   Pin_3
#define  IO_EE_WP_INPUT                 HD_System_GPIO_DIR(IO_EE_WP_PORT, IO_EE_WP_PIN, PUPDR_UP, INPUT)
#define  IO_EE_WP_OUTPUT                HD_System_GPIO_DIR(IO_EE_WP_PORT, IO_EE_WP_PIN, PUPDR_UP, OUTPUT)
#define  IO_EE_WP_H                     HD_System_GPIO_DATA(IO_EE_WP_PORT, IO_EE_WP_PIN, 1)
#define  IO_EE_WP_L                     HD_System_GPIO_DATA(IO_EE_WP_PORT, IO_EE_WP_PIN, 0)

#define  IO_RS485_2_RX_PORT             HT_GPIOE
#define  IO_RS485_2_RX_PIN              Pin_4
#define  IO_RS485_2_RX_INPUT            HD_System_GPIO_DIR(IO_RS485_2_RX_PORT, IO_RS485_2_RX_PIN, PUPDR_UP, INPUT)
#define  IO_RS485_2_RX_OUTPUT           HD_System_GPIO_DIR(IO_RS485_2_RX_PORT, IO_RS485_2_RX_PIN, PUPDR_UP, OUTPUT)
#define  IO_RS485_2_RX_H                HD_System_GPIO_DATA(IO_RS485_2_RX_PORT, IO_RS485_2_RX_PIN, 1)
#define  IO_RS485_2_RX_L                HD_System_GPIO_DATA(IO_RS485_2_RX_PORT, IO_RS485_2_RX_PIN, 0)

#define  IO_RS485_2_TX_PORT             HT_GPIOE
#define  IO_RS485_2_TX_PIN              Pin_5
#define  IO_RS485_2_TX_INPUT            HD_System_GPIO_DIR(IO_RS485_2_TX_PORT, IO_RS485_2_TX_PIN, PUPDR_UP, INPUT)
#define  IO_RS485_2_TX_OUTPUT           HD_System_GPIO_DIR(IO_RS485_2_TX_PORT, IO_RS485_2_TX_PIN, PUPDR_UP, OUTPUT)
#define  IO_RS485_2_TX_H                HD_System_GPIO_DATA(IO_RS485_2_TX_PORT, IO_RS485_2_TX_PIN, 1)
#define  IO_RS485_2_TX_L                HD_System_GPIO_DATA(IO_RS485_2_TX_PORT, IO_RS485_2_TX_PIN, 0)

#define  IO_POWER_FAIL_DT_PORT          HT_GPIOE
#define  IO_POWER_FAIL_DT_PIN           Pin_7
#define  IO_POWER_FAIL_DT_INPUT         HD_System_GPIO_DIR(IO_POWER_FAIL_DT_PORT, IO_POWER_FAIL_DT_PIN, INPUT)
#define  IO_POWER_FAIL_DT_OUTPUT        HD_System_GPIO_DIR(IO_POWER_FAIL_DT_PORT, IO_POWER_FAIL_DT_PIN, OUTPUT)
#define  IO_POWER_FAIL_DT_H             HD_System_GPIO_DATA(IO_POWER_FAIL_DT_PORT, IO_POWER_FAIL_DT_PIN, 1)
#define  IO_POWER_FAIL_DT_L             HD_System_GPIO_DATA(IO_POWER_FAIL_DT_PORT, IO_POWER_FAIL_DT_PIN, 0)
#define  IO_POWER_FAIL_DT_PV            HD_System_GPIO_Read(IO_POWER_FAIL_DT_PORT, IO_POWER_FAIL_DT_PIN)


/*- 2.Type prototype--------------------------------------------*/


/*- 3.Public variable-------------------------------------------*/


/*- 4.Public function-------------------------------------------*/
#ifndef _GPRS_C_
    #define __GLOBAL  extern
#else
    #define __GLOBAL
#endif

__GLOBAL    void        HD_GPIO_Init(void);
/* GPRS模块上电 */
__GLOBAL    void        HD_Module_Reset(void);
__GLOBAL    void        HD_Module_PwrOff(void);
__GLOBAL    void        HD_System_GPIO_AF(HT_GPIO_TypeDef* GPIOx, U32 GPIO_PIN, U8 ucGPIOAF, U8 PuPd);
__GLOBAL    void        HD_System_GPIO_DIR( HT_GPIO_TypeDef* GPIOx,U32 GPIO_PIN,U8 PuPd,U8 DIR);
__GLOBAL    U8          HD_System_GPIO_Read(HT_GPIO_TypeDef* GPIOx,U32 GPIO_PIN);

#undef __GLOBAL  


/*- 5.End-------------------------------------------------------*/

#endif
