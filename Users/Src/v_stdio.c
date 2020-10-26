/**
* @file    v_stdio.h
* @author  Application Team
* @version V4.3.0
* @date    2018-09-04
* @brief   standard printf.
******************************************************************************/
#include <stdio.h>
#include "include.h"
#include "ht6xxx_uart&7816.h"

#define CONSOLE_PORT    HT_UART3    /* ´òÓ¡¶Ë¿Ú */

static void HD_UART_ITConfig(HT_UART_TypeDef *UARTx, uint8_t USART_IT, FunctionalState NewState)
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

static uint16_t HD_UART_BaudConfig(uint32_t ulBaud)
{
    uint16_t usCfg;

    usCfg = HT_CMU_SysClkGet() / (ulBaud * 2) - 1;

    return (usCfg);
}

/**
* @brief  printf init.
* @param  None
* @retval None
*/
void Stdio_Init(void)
{   
    HT_UART_TypeDef* uart = CONSOLE_PORT;

    _OPEN_REG_WRITE;

    HT_CMU->CLKCTRL1 |= UART3_EN;
    HD_System_GPIO_DIR(HT_GPIOE, Pin_5, PUPDR_UP, OUTPUT);
    HD_System_GPIO_DIR(HT_GPIOE, Pin_4, PUPDR_UP, INPUT);
    HD_System_GPIO_AF(HT_GPIOE, Pin_5, GPIO_AF_TX3, PUPDR_OD);
    HD_System_GPIO_AF(HT_GPIOE, Pin_4, GPIO_AF_RX3, PUPDR_OD);
    
	/* baudrate */
	uart->SREL = HD_UART_BaudConfig(115200);

	/* default 8N1 */
    uart->UARTCON = 0x000f;

    /* Disable the uart interrupt */
    HT_UART_ClearITPendingBit(uart, UART_UARTSTA_RXIF);
    HT_UART_ClearITPendingBit(uart, UART_UARTSTA_TXIF);
    HD_UART_ITConfig(uart, UART_IT_RXNE, DISABLE);
    HD_UART_ITConfig(uart, UART_IT_TXNE, DISABLE);
}

/**
* @brief  fputc.
* @param  None
* @retval None
*/
int fputc(int ch, FILE *f)
{
    HT_UART_TypeDef* uart = CONSOLE_PORT;
    
    uart->SBUF = ch;
	while(SET != HT_UART_ITFlagStatusGet(uart, UART_UARTSTA_TXIF));
	HT_UART_ClearITPendingBit(uart, UART_UARTSTA_TXIF);
    
    return ch;
}

#pragma optimize = none
void Delay_us(volatile uint32_t n)
{
    while (n--)
    {
        __NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();
        __NOP();__NOP();
    }
}

#pragma optimize = none
void Delay_ms(volatile uint32_t n)
{
    while (n--)
    {
        Delay_us(971);
    }
}

/*********************************** END OF FILE ******************************/
