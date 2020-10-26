/****************************************************************
Description: HD_Uart.c
Author: shijj
Notes: Uart驱动
*****************************************************************/
#define __HD_UART_C__
/*- 1.Include---------------------------------------------------*/
#include "Include.h"

//wait to add......
/*- 2.Macro-----------------------------------------------------*/

/*- 3.Private variable------------------------------------------*/
const       U32                 pulBaudRand[E_BAUD_MAX] = {300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800};


/*- 4.Public variable-------------------------------------------*/


/*- 5.Private function------------------------------------------*/


/*- 6.Const-----------------------------------------------------*/


/*- 7.End-------------------------------------------------------*/


/*********************************************************************************  
Function name: void HD_UART_ITConfig(HT_UART_TypeDef *UARTx,FunctionalState NewState)
Description:  串口中断使能
Input:  
Return:  
Notes:   
Modification History:
<No.> <version >  <time>        <author>     <contents>
    1、    1.00     2014-02-10   yaoc             Creat
**********************************************************************************/
void HD_UART_ITConfig(HT_UART_TypeDef *UARTx,U8 USART_IT,FunctionalState NewState)
{
    if(USART_IT == UART_IT_RXNE)
    {
        if(NewState == ENABLE)
        {
            UARTx->UARTCON |= 0x08;
            UARTx->UARTCON |= 0x02;
        }
        else
        {
            UARTx->UARTCON &= ~0x08;
            UARTx->UARTCON &= ~0x02;
        }
    }
    if(USART_IT == UART_IT_TXNE)
    {
        if(NewState == ENABLE)
        {
            UARTx->UARTCON |= 0x04;
            UARTx->UARTCON |= 0x01;
        }
        else
        {
            UARTx->UARTCON &= ~0x04;
            UARTx->UARTCON &= ~0x01;
        }
    }
}

/*******************************************************************************
* @Description: 初始化UART相关的内存
* @Param      : none
* @Return     : none
* @History    : 
* <No.> <version>   <time>          <author>    <contents> 
* 1     1.0         2019-03-02      @shijj      create
*******************************************************************************/
void HD_UART_Var_Init(void)
{
    //HD_UART_Init(E_UART_NBIOT, E_BAUD_9600, E_UART_8N1);
    //HD_UART_Init(E_UART_RS485, E_BAUD_9600, E_UART_8N1);
    HD_UART_Init(E_UART_DEBUG, E_BAUD_115200, E_UART_8N1);
}

/*******************************************************************************
* @Description: UART 中断使能
* @Param      : none
* @Return     : none
* @History    : 
* <No.> <version>   <time>          <author>    <contents> 
* 1     1.0         2019-03-02      @shijj      create
*******************************************************************************/
void UART_interrupt_conf(U8 chnl, U32 INTMask, U8 NewState)
{
    switch(chnl)
    {
        case E_UART_NBIOT: HD_UART_ITConfig(HT_UART0, INTMask, (FunctionalState)NewState); break;
        case E_UART_RS485: HD_UART_ITConfig(HT_UART1, INTMask, (FunctionalState)NewState); break;
        case E_UART_DEBUG: HD_UART_ITConfig(HT_UART3, INTMask, (FunctionalState)NewState); break;
        default: break;
    }
}

/*****************************************************************
Function name: HD_UART_Stt_Send
Description: 串口发送数据
Input: pucBuff: 数据地址
       usLen: 数据长度
Return: void                                        
Notes:
 -----------------------------------------------------------------
 Modification History:
 <No.> <version>      <time>       <author>      <contents>
 2、
 1、   1.00          2017-3-9         hx       build this module
*****************************************************************/
void HD_UART_SendData(U8 ucChnl, U8 ucData)
{
    switch(ucChnl)
    {
        case E_UART_NBIOT:
        {
            HT_UART0->SBUF = ucData;
        }break;
        case E_UART_RS485:
        {
            HT_UART1->SBUF = ucData;
        }break;
        case E_UART_DEBUG:
        {
            HT_UART3->SBUF = ucData;
        }break;
        default:
        break;
    }
}
/*****************************************************************
Function name: HD_UART_BaudConfig
Description: 波特率配置
Input: usBaud:波特率
Return: void                                        
Notes:
 -----------------------------------------------------------------
 Modification History:
 <No.> <version>      <time>       <author>      <contents>
 2、
 1、   1.00          2017-3-9         hx       build this module
*****************************************************************/
U16 HD_UART_BaudConfig(U32 ulBaud)
{
    U16 usCfg;

    usCfg = g_ulMCLK / (ulBaud * 2) - 1;

    return (usCfg);
}

/*****************************************************************
Function name: HD_UART_Set
Description: 串口配置
Input:  ucChnl:通道
        usBaud:波特率
        ucType:帧格式
Return: void                                        
Notes:
-----------------------------------------------------------------
Modification History:
<No.> <version>      <time>       <author>      <contents>
2、
1、   1.00          2017-3-9         hx       build this module
*****************************************************************/
void HD_UART_Init(U8 ucChnl, U8 ucBaud, U8 ucType)
{
    U8 ucUartCfg;

    _OPEN_REG_WRITE;
    switch(ucType)
    {
        case E_UART_7E1:
        {
            ucUartCfg = 0x00df;
        }break;
        case E_UART_8N1:
        {
            ucUartCfg = 0x000f;
        }break;
        case E_UART_8E1:
        {
            ucUartCfg = 0x005f;
        }break;
        case E_UART_8O1:
        {
            ucUartCfg = 0x003F;
        }break;
        default:
        {
            
        }break;
    }

    switch(ucChnl)
    {
        case E_UART_NBIOT: //UART1
        {
            IO_RX_NB_INPUT;
            IO_TX_NB_OUTPUT;
            HT_CMU->CLKCTRL1 |= UART0_EN;
            HT_UART0->UARTCON = ucUartCfg;
            HT_UART0->SREL = HD_UART_BaudConfig(pulBaudRand[ucBaud]);
            HD_System_GPIO_AF(IO_TX_NB_PORT, IO_TX_NB_PIN, GPIO_AF_TX0, PUPDR_OD);
            HD_System_GPIO_AF(IO_RX_NB_PORT, IO_RX_NB_PIN, GPIO_AF_RX0, PUPDR_OD);
            if(ucBaud >= E_BAUD_38400)
            {
                NVIC_SetPriority(UART0_IRQn, 0x00);  
                NVIC_EnableIRQ(UART0_IRQn);
            }
            else
            {
                NVIC_SetPriority(UART0_IRQn, 0x02);  
                NVIC_EnableIRQ(UART0_IRQn);
            }
            /* Enable UART transmit doen/receive interrupt */
            HD_UART_ITConfig(HT_UART0, UART_IT_RXNE, ENABLE);
            HD_UART_ITConfig(HT_UART0, UART_IT_TXNE, DISABLE);
        }break;
        case E_UART_RS485: //UART0
        {
            IO_RS485_1_RX_INPUT;
            IO_RS485_1_TX_OUTPUT;
            HT_CMU->CLKCTRL1 |= UART1_EN;
            HT_UART1->UARTCON = ucUartCfg;
            HT_UART1->SREL = HD_UART_BaudConfig(pulBaudRand[ucBaud]);
            HD_System_GPIO_AF(IO_RS485_1_TX_PORT, IO_RS485_1_TX_PIN, GPIO_AF_TX1, PUPDR_OD);
            HD_System_GPIO_AF(IO_RS485_1_RX_PORT, IO_RS485_1_RX_PIN, GPIO_AF_RX1, PUPDR_OD);
            if(ucBaud >= E_BAUD_38400)
            {
                NVIC_SetPriority(UART1_IRQn, 0x00);  
                NVIC_EnableIRQ(UART1_IRQn);
            }
            else
            {
                NVIC_SetPriority(UART1_IRQn, 0x02);  
                NVIC_EnableIRQ(UART1_IRQn);
            }
            /* Enable UART transmit doen/receive interrupt */
            HD_UART_ITConfig(HT_UART1, UART_IT_RXNE, ENABLE);
            HD_UART_ITConfig(HT_UART1, UART_IT_TXNE, DISABLE);

        }break;
        case E_UART_DEBUG: //UART2
        {
            IO_RS485_2_RX_INPUT;
            IO_RS485_2_TX_OUTPUT;
            HT_CMU->CLKCTRL1 |= UART3_EN;
            HT_UART3->UARTCON = ucUartCfg;
            HT_UART3->SREL = HD_UART_BaudConfig(pulBaudRand[ucBaud]);
            HD_System_GPIO_AF(IO_RS485_2_TX_PORT, IO_RS485_2_TX_PIN, GPIO_AF_TX3, PUPDR_OD);
            HD_System_GPIO_AF(IO_RS485_2_RX_PORT, IO_RS485_2_RX_PIN, GPIO_AF_RX3, PUPDR_OD);
            if(ucBaud >= E_BAUD_38400)
            {
                NVIC_SetPriority(UART3_IRQn, 0x00);  
                NVIC_EnableIRQ(UART3_IRQn);
            }
            else
            {
                NVIC_SetPriority(UART3_IRQn, 0x02);  
                NVIC_EnableIRQ(UART3_IRQn);
            }
            /* Enable UART transmit doen/receive interrupt */
            HD_UART_ITConfig(HT_UART3, UART_IT_RXNE, ENABLE);
            HD_UART_ITConfig(HT_UART3, UART_IT_TXNE, ENABLE);
        }break;
        default:
        break;
    }
}

