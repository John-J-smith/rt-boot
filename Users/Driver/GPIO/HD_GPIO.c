/****************************************************************
Description: HD_LCD.c
Author: hx
Notes: GPIO驱动
*****************************************************************/
#define __HD_GPIO_C__
/*- 1.Include---------------------------------------------------*/
#include "Include.h"
//wait to add......
/*- 2.Private variable------------------------------------------*/


/*- 3.Public variable-------------------------------------------*/


/*****************************************************************************
Description: 读GPIO 口
Input:
Output:
Return:
******************************************************************************/
U8 HD_System_GPIO_Read(HT_GPIO_TypeDef* GPIOx,U32 GPIO_PIN)
{
    if(GPIOx->PTDAT & (1 << GPIO_PIN))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

/*****************************************************************************
Description: 读GPIO端口的输入输出状态值
Input:
Output:
Return:
******************************************************************************/
U8 HD_System_GPIO_DIR_Read(HT_GPIO_TypeDef *GPIOx, U32 GPIO_PIN)
{
    if (GPIOx->PTDIR & (1 << GPIO_PIN))
    {
        return OUTPUT;//输出
    }
    else
    {
        return INPUT;//输入
    }
}

/*******************************************************************************
* @Description: GPIO初始化
* @Param      : none
* @Return     : none
* @History    : 
* <No.> <version>   <time>          <author>    <contents> 
* 1     1.0         2019-03-19     @shijj      create
*******************************************************************************/
void HD_System_GPIO_DIR( HT_GPIO_TypeDef* GPIOx,U32 GPIO_PIN,U8 PuPd,U8 DIR)
{
    if(DIR == OUTPUT)
    {
        GPIOx->PTDIR |= (0x0001<<GPIO_PIN); 
    }
    else
    {
        GPIOx->PTDIR &= ~(0x0001<<GPIO_PIN); 
    }
    if(PuPd == PUPDR_UP)
    {
        GPIOx->PTUP &= ~(0x0001<<GPIO_PIN);
    }
    else
    {
        GPIOx->PTUP |= (0x0001<<GPIO_PIN);
    }
}

/*******************************************************************************
* @Description: GPIO初始化
* @Param      : none
* @Return     : none
* @History    : 
* <No.> <version>   <time>          <author>    <contents> 
* 1     1.0         2019-03-19     @shijj      create
*******************************************************************************/
void HD_GPIO_Init(void)
{
    //模块控制
    IO_RST_IOT_OUTPUT;
    IO_NB_PWR_L;IO_NB_PWR_OUTPUT;IO_NB_PWR_L;

    //LED 一共12颗，其中1颗由模组控制
    IO_LED_RUN_H;IO_LED_RUN_OUTPUT;IO_LED_RUN_H;
    IO_LED_RX_H;IO_LED_RX_OUTPUT;IO_LED_RX_H;
    IO_LED_TX_H;IO_LED_TX_OUTPUT;IO_LED_TX_H;
    
    IO_RELAYA_LED_H;IO_RELAYA_LED_OUTPUT;IO_RELAYA_LED_H;
    IO_RELAYB_LED_H;IO_RELAYB_LED_OUTPUT;IO_RELAYB_LED_H;
    IO_RELAYC_LED_H;IO_RELAYC_LED_OUTPUT;IO_RELAYC_LED_H;
    
    IO_SIG1_LED_H;IO_SIG1_LED_OUTPUT;IO_SIG1_LED_H;
    IO_SIG2_LED_H;IO_SIG2_LED_OUTPUT;IO_SIG2_LED_H;
    IO_SIG3_LED_H;IO_SIG3_LED_OUTPUT;IO_SIG3_LED_H;
    IO_SIG4_LED_H;IO_SIG4_LED_OUTPUT;IO_SIG4_LED_H;
    
    IO_485_LED_H;IO_485_LED_OUTPUT;IO_485_LED_H;

    //485
    IO_RS485_1_DIR_OUTPUT;
    RS485_1_INPUT;//485初始化为输入模式
    IO_RS485_2_DIR_OUTPUT;
    RS485_2_INPUT;//485初始化为输入模式

    /*spi*/
    IO_DF_CS_OUTPUT;
    IO_DF_CLK_OUTPUT;
    HD_System_GPIO_AF(IO_DF_CLK_PORT, IO_DF_CLK_PIN, GPIO_AF_SPI0_CLK, PUPDR_OD);
    IO_DF_SDI_INPUT;
    HD_System_GPIO_AF(IO_DF_SDI_PORT, IO_DF_SDI_PIN, GPIO_AF_SPI0_SDI, PUPDR_OD);
    IO_DF_SDO_OUTPUT;
    HD_System_GPIO_AF(IO_DF_SDO_PORT, IO_DF_SDO_PIN, GPIO_AF_SPI0_SDO, PUPDR_OD);
    IO_DF_WP_OUTPUT;

    /*i2c*/
    IO_I2C_SCL_H;IO_I2C_SCL_OUTPUT;IO_I2C_SCL_H;
    IO_I2C_SDA_H;IO_I2C_SDA_OUTPUT;IO_I2C_SDA_H;
    IO_EE_WP_H;IO_EE_WP_OUTPUT;IO_EE_WP_H;

    /*Super capacity*/
    IO_SUP_DT_INPUT;
    HD_System_GPIO_AF(IO_SUP_DT_PORT, IO_SUP_DT_PIN, GPIO_AF_ADCIN1, PUPDR_OD);

    /*Relay*/
    IO_RELAY_A_L;IO_RELAY_A_OUTPUT;IO_RELAY_A_L;
    IO_RELAY_B_L;IO_RELAY_B_OUTPUT;IO_RELAY_B_L;

    /* relay feedback */
    IO_RELAY_A_DT_INPUT;
    IO_RELAY_B_DT_INPUT;
    IO_RELAY_C_DT_INPUT;

    /*Key*/
    IO_KEY_DT_INPUT;
    IO_OPEN_T_INPUT;
}
/*******************************************************************************
* @Description: NB模块复位
* @Param      : none
* @Return     : none
* @History    : 
* <No.> <version>   <time>          <author>    <contents> 
* 1     1.0         2019-03-19     @shijj      create
*******************************************************************************/
void HD_Module_Reset(void)
{

}
/*****************************************************************************
Description:GPIO 外设功能配置
Input:
Output:
Return:
******************************************************************************/
void HD_System_GPIO_AF(HT_GPIO_TypeDef* GPIOx, U32 GPIO_PIN, U8 ucGPIOAF, U8 PuPd)
{
    if(PuPd == PUPDR_UP)
    {
        GPIOx->PTUP &= ~(0x0001<<GPIO_PIN);
    }
    else
    {
        GPIOx->PTUP |= (0x0001<<GPIO_PIN);
    }

    GPIOx->IOCFG |= (0x0001<<GPIO_PIN);

    if(ucGPIOAF == 0x02)
    {
        GPIOx->AFCFG &= ~(0x0001<<GPIO_PIN);
    }
    else
    {
        GPIOx->AFCFG |= (0x0001<<GPIO_PIN);
    }
}

/*- 4.Private function------------------------------------------*/


/*- 5.Const-----------------------------------------------------*/


/*- 6.End-------------------------------------------------------*/

