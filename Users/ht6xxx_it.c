/*
*********************************************************************************************************
*                                          HT60XX
*                                       HT60XX����
*
*                             Copyright 2013, Hi-Trend Tech, Corp.
*                                    All Rights Reserved
*
*
* Project      : HT60xx
* File         : ht60xx_it.c
* By           : Hitrendtech_SocTeam
* Version      : V1.0.4
* Description  :
*********************************************************************************************************
*/

#define  __HT60XX_IT_C

#include "ht6xxx_lib.h"
#include "ht6xxx_it.h"
#include "Include.h"
#include "common.h"

// LEDs
#define LED_RUN_ON          do { IO_LED_RUN_OUTPUT; IO_LED_RUN_L; } while(0)
#define LED_RUN_OFF         do { IO_LED_RUN_OUTPUT; IO_LED_RUN_H; } while(0)

#define LED_UPLINK_ON       do { IO_LED_TX_OUTPUT; IO_LED_TX_L; } while(0) //RED
#define LED_UPLINK_OFF      do { IO_LED_TX_OUTPUT; IO_LED_TX_H; } while(0)

#define LED_DOWNLINK_ON     do { IO_LED_RX_OUTPUT; IO_LED_RX_L; } while(0) //GREEN
#define LED_DOWNLINK_OFF    do { IO_LED_RX_OUTPUT; IO_LED_RX_H; } while(0)
/*
*********************************************************************************************************
*                                            ���غ�/�ṹ��
*********************************************************************************************************
*/
#define RX_Head1    0xAA
#define RX_Head2    0x55
#define RX_Over     0x16

/*
*********************************************************************************************************
*                                            ���ر���
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           ���غ�������
*********************************************************************************************************
*/




/*
*********************************************************************************************************
*                                        NMI INTERRUPT HANDLER #16-14
*
*********************************************************************************************************
*/
__stackless void NMI_Handler(void)
{
    if (SET == HT_CMU_StopFlagGet(CMU_CLKSTA_LFFLAG))
    {
        
    }
    
    if (SET == HT_CMU_StopFlagGet(CMU_CLKSTA_HRCFLAG))
    {
        
    }
    
    if (SET == HT_CMU_StopFlagGet(CMU_CLKSTA_PLLFLAG))
    {
        
    }
}

/*
*********************************************************************************************************
*                                        HARDFAULT INTERRUPT HANDLER #16-13
*
*********************************************************************************************************
*/
__stackless void HardFault_Handler(void)
{
    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 0xc;
    
    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                        SVC INTERRUPT HANDLER #16-5
*
*********************************************************************************************************
*/
__stackless void SVC_Handler(void)
{
    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 0x2c;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                        PENDSV INTERRUPT HANDLER #16-2
*
*********************************************************************************************************
*/
__stackless void PendSV_Handler( void )
{
    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 0x38;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}
/*
*********************************************************************************************************
*                                        SYSTICK INTERRUPT HANDLER #16-1
*
*********************************************************************************************************
*/
__stackless void SysTick_Handler(void)
{
    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 0x3c;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                        PMU INTERRUPT HANDLER #16+0
*
*********************************************************************************************************
*/

__stackless void PMU_IRQHandler()
{
#if 0
    if(SET == HT_PMU_ITFlagStatusGet(PMU_PMUIF_VCCIF))           /*!< Vcc����ж���λ            */
    {
        
        HT_PMU_ClearITPendingBit(PMU_PMUIF_VCCIF);               /*!< ����жϱ�־               */
    }
    
    if(SET == HT_PMU_ITFlagStatusGet(PMU_PMUIF_BORIF))           /*!< Bor����ж���λ            */
    {
        
        HT_PMU_ClearITPendingBit(PMU_PMUIF_BORIF);               /*!< ����жϱ�־               */
    }
    
    if(SET == HT_PMU_ITFlagStatusGet(PMU_PMUIF_LVD0IF))           /*!< Lvdin����ж���λ          */
    {
        
        HT_PMU_ClearITPendingBit(PMU_PMUIF_LVD0IF);               /*!< ����жϱ�־               */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 64;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}


/*
*********************************************************************************************************
*                                  3DES/AES INTERRUPT HANDLER  #16+1
*
*********************************************************************************************************
*/
#if defined HT6x1x
__stackless void TDES_IRQHandler()                      /*!< 3DES               */
{
    
}
#else
__stackless void AES_IRQHandler()                       /*!< AES                */
{
    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 68;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}
#endif

/*
*********************************************************************************************************
*                                   EXTI0 INTERRUPT HANDLER  #16+2
*
*********************************************************************************************************
*/

__stackless void EXTI0_IRQHandler()
{
#if 0
    if(SET == HT_EXTIRise_ITFlagStatusGet(INT_EXTIF_RIF_INT0))         /*!< INT0�������ж�           */
    {
        HT_EXTIRise_ClearITPendingBit(INT_EXTIF_RIF_INT0);             /*!< ����жϱ�־             */
    }
    
    if(SET == HT_EXTIFall_ITFlagStatusGet(INT_EXTIF_FIF_INT0))         /*!< INT0�½����ж�           */
    {
        HT_EXTIFall_ClearITPendingBit(INT_EXTIF_FIF_INT0);             /*!< ����жϱ�־             */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 72;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                   EXTI1 INTERRUPT HANDLER  #16+3
*
*********************************************************************************************************
*/

__stackless void EXTI1_IRQHandler()
{
#if 0
    if(SET == HT_EXTIRise_ITFlagStatusGet(INT_EXTIF_RIF_INT1))         /*!< INT1�������ж�           */
    {
        
        HT_EXTIRise_ClearITPendingBit(INT_EXTIF_RIF_INT1);             /*!< ����жϱ�־             */
    }
    
    if(SET == HT_EXTIFall_ITFlagStatusGet(INT_EXTIF_FIF_INT1))         /*!< INT1�½����ж�           */
    {
        
        HT_EXTIFall_ClearITPendingBit(INT_EXTIF_FIF_INT1);             /*!< ����жϱ�־             */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 76;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                   EXTI2 INTERRUPT HANDLER  #16+4
*
*********************************************************************************************************
*/

__stackless void EXTI2_IRQHandler()
{
#if 0
    if(SET == HT_EXTIRise_ITFlagStatusGet(INT_EXTIF_RIF_INT2))         /*!< INT2�������ж�           */
    {
        
        HT_EXTIRise_ClearITPendingBit(INT_EXTIF_RIF_INT2);             /*!< ����жϱ�־             */
    }
    
    if(SET == HT_EXTIFall_ITFlagStatusGet(INT_EXTIF_FIF_INT2))         /*!< INT2�½����ж�           */
    {
        
        HT_EXTIFall_ClearITPendingBit(INT_EXTIF_FIF_INT2);             /*!< ����жϱ�־             */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 80;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                   EXTI3 INTERRUPT HANDLER  #16+5
*
*********************************************************************************************************
*/

__stackless void EXTI3_IRQHandler()
{
#if 0
    if(SET == HT_EXTIRise_ITFlagStatusGet(INT_EXTIF_RIF_INT3))         /*!< INT3�������ж�           */
    {
        
        HT_EXTIRise_ClearITPendingBit(INT_EXTIF_RIF_INT3);             /*!< ����жϱ�־             */
    }
    
    if(SET == HT_EXTIFall_ITFlagStatusGet(INT_EXTIF_FIF_INT3))         /*!< INT3�½����ж�           */
    {
        
        HT_EXTIFall_ClearITPendingBit(INT_EXTIF_FIF_INT3);             /*!< ����жϱ�־             */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 84;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                   EXTI4 INTERRUPT HANDLER  #16+6
*
*********************************************************************************************************
*/

__stackless void EXTI4_IRQHandler()
{
#if 0
    if(SET == HT_EXTIRise_ITFlagStatusGet(INT_EXTIF_RIF_INT4))         /*!< INT4�������ж�           */
    {
        
        HT_EXTIRise_ClearITPendingBit(INT_EXTIF_RIF_INT4);             /*!< ����жϱ�־             */
    }
    
    if(SET == HT_EXTIFall_ITFlagStatusGet(INT_EXTIF_FIF_INT4))         /*!< INT4�½����ж�           */
    {
        
        HT_EXTIFall_ClearITPendingBit(INT_EXTIF_FIF_INT4);             /*!< ����жϱ�־             */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 88;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                   EXTI5 INTERRUPT HANDLER  #16+7
*
*********************************************************************************************************
*/

__stackless void EXTI5_IRQHandler()
{
#if 0
    if(SET == HT_EXTIRise_ITFlagStatusGet(INT_EXTIF_RIF_INT5))         /*!< INT5�������ж�           */
    {
        
        HT_EXTIRise_ClearITPendingBit(INT_EXTIF_RIF_INT5);             /*!< ����жϱ�־             */
    }
    
    if(SET == HT_EXTIFall_ITFlagStatusGet(INT_EXTIF_FIF_INT5))         /*!< INT5�½����ж�           */
    {
        
        HT_EXTIFall_ClearITPendingBit(INT_EXTIF_FIF_INT5);             /*!< ����жϱ�־             */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 92;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                   EXTI6 INTERRUPT HANDLER  #16+8
*
*********************************************************************************************************
*/

__stackless void EXTI6_IRQHandler()
{
#if 0
    if(SET == HT_EXTIRise_ITFlagStatusGet(INT_EXTIF_RIF_INT6))         /*!< INT6�������ж�           */
    {
        
        HT_EXTIRise_ClearITPendingBit(INT_EXTIF_RIF_INT6);             /*!< ����жϱ�־             */
    }
    
    if(SET == HT_EXTIFall_ITFlagStatusGet(INT_EXTIF_FIF_INT6))         /*!< INT6�½����ж�           */
    {
        
        HT_EXTIFall_ClearITPendingBit(INT_EXTIF_FIF_INT6);             /*!< ����жϱ�־             */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 96;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}


/*
*********************************************************************************************************
*                                   UART0 INTERRUPT HANDLER  #16+9
*
*********************************************************************************************************
*/

__stackless void UART0_IRQHandler()
{
#if 0
    if(SET == HT_UART_ITFlagStatusGet(HT_UART0, UART_UARTSTA_TXIF))         /*!< UART0�����ж�         */
    {
        
        HT_UART_ClearITPendingBit(HT_UART0, UART_UARTSTA_TXIF);             /*!< ����жϱ�־          */
        
    }
    
    if(SET == HT_UART_ITFlagStatusGet(HT_UART0, UART_UARTSTA_RXIF))         /*!< UART0�����ж�         */
    {
        
        HT_UART_ClearITPendingBit(HT_UART0, UART_UARTSTA_RXIF);             /*!< ����жϱ�־          */
        
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 100;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                   UART1 INTERRUPT HANDLER  #16+10
*
*********************************************************************************************************
*/

__stackless void UART1_IRQHandler()
{
#if 0
    if(SET == HT_UART_ITFlagStatusGet(HT_UART1, UART_UARTSTA_RXIF))         /*!< UART1�����ж�         */
    {
        
        HT_UART_ClearITPendingBit(HT_UART1, UART_UARTSTA_RXIF);             /*!< ����жϱ�־          */
        
    }
    
	if(SET == HT_UART_ITFlagStatusGet(HT_UART1, UART_UARTSTA_TXIF))         /*!< UART1�����ж�         */
    {
        
        HT_UART_ClearITPendingBit(HT_UART1, UART_UARTSTA_TXIF);             /*!< ����жϱ�־          */
        
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 104;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                   UART2 INTERRUPT HANDLER  #16+11
*
*********************************************************************************************************
*/

__stackless void UART2_IRQHandler()
{
#if 0
    if(SET == HT_UART_ITFlagStatusGet(HT_UART2, UART_UARTSTA_TXIF))         /*!< UART2�����ж�         */
    {
        
        HT_UART_ClearITPendingBit(HT_UART2, UART_UARTSTA_TXIF);             /*!< ����жϱ�־          */
        
    }
    
    if(SET == HT_UART_ITFlagStatusGet(HT_UART2, UART_UARTSTA_RXIF))         /*!< UART2�����ж�         */
    {
        
        HT_UART_ClearITPendingBit(HT_UART2, UART_UARTSTA_RXIF);             /*!< ����жϱ�־          */
        
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 108;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

__stackless void UART3_IRQHandler()
{
#if 0
    uint32_t address;
    void (*pFunction)(void);
    
    if(g_bAppRun)
    {
        HT_Flash_WordRead(&address, ApplicationAddress + 4 * 28, 1);
        
        pFunction = (void (*)(void))address;
        pFunction();
    }
    else
    {
        if(SET == HT_UART_ITFlagStatusGet(HT_UART3, UART_UARTSTA_TXIF))    /*!< UART3�����ж�         */
        {
            HT_UART_ClearITPendingBit(HT_UART3, UART_UARTSTA_TXIF);
            uart_snd_flg = 1;
        }
        
        if(HT_UART_ITFlagStatusGet(HT_UART3, UART_UARTSTA_RXIF))            /*!< UART3�����ж�         */
        {
            HT_UART_ClearITPendingBit(HT_UART3, UART_UARTSTA_RXIF);
            key_val = (HT_UART3->SBUF);
            uart_rcv_flg = 1;
        }
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 112;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                   UART4 INTERRUPT HANDLER  #16+13
*
*********************************************************************************************************
*/

__stackless void UART4_IRQHandler()
{
#if 0
    if(SET == HT_UART_ITFlagStatusGet(HT_UART4, UART_UARTSTA_TXIF))            /*!< UART4�����ж�         */
    {
        
        HT_UART_ClearITPendingBit(HT_UART4, UART_UARTSTA_TXIF);                /*!< ����жϱ�־          */
        
    }
    
    if(SET == HT_UART_ITFlagStatusGet(HT_UART4, UART_UARTSTA_RXIF))            /*!< UART4�����ж�         */
    {
        
        HT_UART_ClearITPendingBit(HT_UART4, UART_UARTSTA_RXIF);                /*!< ����жϱ�־          */
        
    }
    
    if(SET == HT_ISO7816_ITFlagStatusGet(HT_ISO7816_0, UART_ISO7816STA_TXIF))  /*!< 7816�����ж�          */
    {
        
        HT_ISO7816_ClearITPendingBit(HT_ISO7816_0, UART_ISO7816STA_TXIF);      /*!< ����жϱ�־          */
    }
    
    if(SET == HT_ISO7816_ITFlagStatusGet(HT_ISO7816_0, UART_ISO7816STA_RXIF))  /*!< 7816�����ж�          */
    {
        
        HT_ISO7816_ClearITPendingBit(HT_ISO7816_0, UART_ISO7816STA_RXIF);      /*!< ����жϱ�־          */
    }
    
    if(SET == HT_ISO7816_ITFlagStatusGet(HT_ISO7816_0, UART_ISO7816STA_PRDIF)) /*!< 7816���������жϱ�־  */
    {
        
        HT_ISO7816_ClearITPendingBit(HT_ISO7816_0, UART_ISO7816STA_PRDIF);     /*!< ����жϱ�־          */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 116;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                   UART5 INTERRUPT HANDLER  #16+14
*
*********************************************************************************************************
*/

__stackless void UART5_IRQHandler()
{
#if 0
	if(SET == HT_UART_ITFlagStatusGet(HT_UART5, UART_UARTSTA_RXIF))         /*!< UART5�����ж�         */
    {
        
        HT_UART_ClearITPendingBit(HT_UART5, UART_UARTSTA_RXIF);             /*!< ����жϱ�־          */
        
    }
    if(SET == HT_UART_ITFlagStatusGet(HT_UART5, UART_UARTSTA_TXIF))         /*!< UART5�����ж�         */
    {
        
        HT_UART_ClearITPendingBit(HT_UART5, UART_UARTSTA_TXIF);             /*!< ����жϱ�־          */
        
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 120;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                   TIMER_0 INTERRUPT HANDLER  #16+15
*
*********************************************************************************************************
*/

__stackless void TIMER_0_IRQHandler()
{
#if 0
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR0, TMR_TMRIF_PRDIF))                /*!< �����ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR0, TMR_TMRIF_PRDIF);                    /*!< ����жϱ�־          */
    }
    
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR0, TMR_TMRIF_CAPIF))                /*!< �����ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR0, TMR_TMRIF_CAPIF);                    /*!< ����жϱ�־          */
    }
    
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR0, TMR_TMRIF_CMPIF))                /*!< �Ƚ��ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR0, TMR_TMRIF_CMPIF);                    /*!< ����жϱ�־          */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 124;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                   TIMER_1 INTERRUPT HANDLER  #16+16
*                                   �жϴ�����100us
*********************************************************************************************************
*/

__stackless void TIMER_1_IRQHandler()
{
#if 0
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR1, TMR_TMRIF_PRDIF))                /*!< �����ж�           */
    {
        HT_TMR_ClearITPendingBit(HT_TMR1, TMR_TMRIF_PRDIF);                    /*!< ����жϱ�־       */
        
        
    }
    
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR1, TMR_TMRIF_CAPIF))                /*!< �����ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR1, TMR_TMRIF_CAPIF);                    /*!< ����жϱ�־          */
    }
    
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR1, TMR_TMRIF_CMPIF))                /*!< �Ƚ��ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR1, TMR_TMRIF_CMPIF);                    /*!< ����жϱ�־          */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 128;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                   TIMER_2 INTERRUPT HANDLER  #16+17
*
*********************************************************************************************************
*/

__stackless void TIMER_2_IRQHandler()
{
#if 0
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR2, TMR_TMRIF_PRDIF))                /*!< �����ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR2, TMR_TMRIF_PRDIF);                    /*!< ����жϱ�־          */
    }
    
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR2, TMR_TMRIF_CAPIF))                /*!< �����ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR2, TMR_TMRIF_CAPIF);                    /*!< ����жϱ�־          */
    }
    
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR2, TMR_TMRIF_CMPIF))                /*!< �Ƚ��ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR2, TMR_TMRIF_CMPIF);                    /*!< ����жϱ�־          */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 132;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                   TIMER_3 INTERRUPT HANDLER  #16+18
*                                   �жϴ����� 1ms
*********************************************************************************************************
*/

__stackless void TIMER_3_IRQHandler()
{
#if 0
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR3, TMR_TMRIF_PRDIF))                /*!< �����ж�           */
    {
        HT_TMR_ClearITPendingBit(HT_TMR3, TMR_TMRIF_PRDIF);                    /*!< ����жϱ�־       */
        
        
    }
    
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR3, TMR_TMRIF_CAPIF))                /*!< �����ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR3, TMR_TMRIF_CAPIF);                    /*!< ����жϱ�־       */
    }
    
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR3, TMR_TMRIF_CMPIF))                /*!< �Ƚ��ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR3, TMR_TMRIF_CMPIF);                    /*!< ����жϱ�־       */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 136;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                     TBS INTERRUPT HANDLER  #16+19
*
*********************************************************************************************************
*/

__stackless void TBS_IRQHandler()
{
#if 0
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_TMPIF))                 /*!< �¶Ȳ����ж�          */
    {
        
        HT_TBS_ClearITPendingBit(TBS_TBSIF_TMPIF);                     /*!< ����жϱ�־          */
    }
    
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_VBATIF))                /*!< ��ز����ж�          */
    {
        
        HT_TBS_ClearITPendingBit(TBS_TBSIF_VBATIF);                    /*!< ����жϱ�־          */
    }
    
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC0IF))                /*!< ADC0�����ж�          */
    {
        
        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC0IF);                    /*!< ����жϱ�־          */
    }
    
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC1IF))                /*!< ADC1�����ж�          */
    {
        
        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC1IF);                    /*!< ����жϱ�־          */
    }
    
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_VBATCMPIF))             /*!< ��ص�ѹ�Ƚ��ж�      */
    {
        
        HT_TBS_ClearITPendingBit(TBS_TBSIF_VBATCMPIF);                 /*!< ����жϱ�־          */
    }
    
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_VCCIF))                 /*!< ��Դ�����ж�          */
    {
        
        HT_TBS_ClearITPendingBit(TBS_TBSIF_VCCIF);                     /*!< ����жϱ�־          */
    }
    
#if defined  HT501x  ||  defined  HT502x
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC2IF))                /*!< ADC2�����ж�          */
    {
        
        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC2IF);                    /*!< ����жϱ�־          */
    }
#endif
    
#if defined  HT501x
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_VREFIF))                /*!< VREF�����ж�          */
    {
        
        HT_TBS_ClearITPendingBit(TBS_TBSIF_VREFIF);                    /*!< ����жϱ�־          */
    }
#endif
    
#if defined  HT6x2x  ||  defined  HT6x3x
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC3IF))                /*!< ADC3�����ж�          */
    {
        
        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC3IF);                    /*!< ����жϱ�־          */
    }
    
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC4IF))                /*!< ADC4�����ж�          */
    {
        
        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC4IF);                    /*!< ����жϱ�־          */
    }
    
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC5IF))                /*!< ADC5�����ж�          */
    {
        
        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC5IF);                    /*!< ����жϱ�־          */
    }
#endif
    
#if defined  HT6x2x  ||  defined  HT6x3x  ||  defined  HT501x  ||  defined  HT502x
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC0CMPIF))             /*!< ADC0CMP�����ж�       */
    {
        
        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC0CMPIF);                 /*!< ����жϱ�־          */
    }
#endif
    
#if defined  HT501x  ||  defined  HT502x
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC1CMPIF))             /*!< ADC1CMP�����ж�       */
    {
        
        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC1CMPIF);                 /*!< ����жϱ�־          */
    }
#endif
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 140;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                    RTC INTERRUPT HANDLER  #16+20
*
*********************************************************************************************************
*/

__stackless void RTC_IRQHandler()
{
#if 0
    uint8_t Flag = HT_RTC->RTCIF;
    HT_RTC->RTCIF = 0;                                             /*!< ����жϱ�־          */
    
    if(Flag & RTC_RTCIF_SECIF)                                     /*!< ���ж�                */
    {
        
    }
    
    if(Flag & RTC_RTCIF_MINIF)                                     /*!< ���ж�                */
    {
        
    }
    
    if(Flag & RTC_RTCIF_HRIF)                                      /*!< Сʱ�ж�              */
    {
        
    }
    
    if(Flag & RTC_RTCIF_DAYIF)                                     /*!< ���ж�                */
    {
        
    }
    
    if(Flag & RTC_RTCIF_MTHIF)                                     /*!< ���ж�                */
    {
        
    }
    
    if(Flag & RTC_RTCIF_RTC1IF)                                    /*!< RTC��ʱ��1�ж�        */
    {
        
    }
    
    if(Flag & RTC_RTCIF_RTC2IF)                                    /*!< RTC��ʱ��2�ж�        */
    {
        
    }
    
    if(Flag & RTC_RTCIF_ALMIF)                                     /*!< �����ж�              */
    {
        
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 144;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                    I2C INTERRUPT HANDLER  #16+21
*
*********************************************************************************************************
*/

__stackless void I2C_IRQHandler()
{
    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 148;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                    SPI0 INTERRUPT HANDLER  #16+22
*
*********************************************************************************************************
*/

__stackless void SPI0_IRQHandler()
{
#if 0
    if(SET == HT_SPI_ITFlagStatusGet(HT_SPI0,SPI_SPISTA_MODF))                 /*!< SPI0ģʽ���ϱ�־λ     */
    {
        
        HT_SPI_ClearITPendingBit(HT_SPI0, SPI_SPISTA_MODF);                    /*!< ����жϱ�־          */
    }
    
    if(SET == HT_SPI_ITFlagStatusGet(HT_SPI0, SPI_SPISTA_SPIF))                /*!< SPI0���ݴ�����ɱ�־λ*/
    {
        
        HT_SPI_ClearITPendingBit(HT_SPI0, SPI_SPISTA_SPIF);                    /*!< ����жϱ�־          */
    }
#endif
    
    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 152;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}

/*
*********************************************************************************************************
*                                  WDT/SPI1 INTERRUPT HANDLER  #16+23
*
*********************************************************************************************************
*/
#if defined  HT6x1x
__stackless void WDT_IRQHandler()
{
    
}
#elif defined HT6x2x  ||  defined  HT6x3x
__stackless void SPI1_IRQHandler()
{
#if 0
    if(SET == HT_SPI_ITFlagStatusGet(HT_SPI1,SPI_SPISTA_MODF))                 /*!< SPI1ģʽ���ϱ�־λ     */
    {
        
        HT_SPI_ClearITPendingBit(HT_SPI1, SPI_SPISTA_MODF);                    /*!< ����жϱ�־          */
    }
    
    if(SET == HT_SPI_ITFlagStatusGet(HT_SPI1, SPI_SPISTA_SPIF))                /*!< SPI1���ݴ�����ɱ�־λ*/
    {
        
        HT_SPI_ClearITPendingBit(HT_SPI1, SPI_SPISTA_SPIF);                    /*!< ����жϱ�־          */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 156;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}
#endif

/*
*********************************************************************************************************
*                                 FREQ TEST INTERRUPT HANDLER  #16+24
*
*********************************************************************************************************
*/
#if defined  HT6x2x  ||  defined  HT6x3x
__stackless void SelfTestF_IRQHandler(void)
{
    
}
#endif

/*
*********************************************************************************************************
*                               TIMER_4/EMU INTERRUPT HANDLER  #16+25
*
*********************************************************************************************************
*/
#if defined  HT6x2x  ||  defined  HT6x3x
__stackless void TIMER_4_IRQHandler(void)
{
#if 0
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR4, TMR_TMRIF_PRDIF))                /*!< �����ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR4, TMR_TMRIF_PRDIF);                    /*!< ����жϱ�־       */
    }
    
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR4, TMR_TMRIF_CAPIF))                /*!< �����ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR4, TMR_TMRIF_CAPIF);                    /*!< ����жϱ�־       */
    }
    
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR4, TMR_TMRIF_CMPIF))                /*!< �Ƚ��ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR4, TMR_TMRIF_CMPIF);                    /*!< ����жϱ�־       */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 164;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}
#elif defined HT501x
__stackless void EMU_IRQHandler(void)
{
    
}
#endif

/*
*********************************************************************************************************
*                               TIMER_5/DMA INTERRUPT HANDLER  #16+26
*
*********************************************************************************************************
*/

#if defined  HT6x2x  ||  defined  HT6x3x
__stackless void TIMER_5_IRQHandler(void)
{
#if 0
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR5, TMR_TMRIF_PRDIF))                /*!< �����ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR5, TMR_TMRIF_PRDIF);                    /*!< ����жϱ�־       */
    }
    
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR5, TMR_TMRIF_CAPIF))                /*!< �����ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR5, TMR_TMRIF_CAPIF);                    /*!< ����жϱ�־       */
    }
    
    if(SET == HT_TMR_ITFlagStatusGet(HT_TMR5, TMR_TMRIF_CMPIF))                /*!< �Ƚ��ж�           */
    {
        
        HT_TMR_ClearITPendingBit(HT_TMR5, TMR_TMRIF_CMPIF);                    /*!< ����жϱ�־       */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 168;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}
#elif defined HT501x
__stackless void DMA_IRQHandler(void)
{
    
}
#endif

/*
*********************************************************************************************************
*                               UART6/KEY INTERRUPT HANDLER  #16+27
*
*********************************************************************************************************
*/
#if defined  HT6x2x  ||  defined  HT6x3x
__stackless void UART6_IRQHandler(void)
{
#if 0
	if(SET == HT_UART_ITFlagStatusGet(HT_UART6, UART_UARTSTA_RXIF))         /*!< UART0�����ж�         */
    {
        
        HT_UART_ClearITPendingBit(HT_UART6, UART_UARTSTA_RXIF);             /*!< ����жϱ�־          */
        
    }
    
    if(SET == HT_UART_ITFlagStatusGet(HT_UART6, UART_UARTSTA_TXIF))         /*!< UART0�����ж�         */
    {
        
        HT_UART_ClearITPendingBit(HT_UART6, UART_UARTSTA_TXIF);             /*!< ����жϱ�־          */
        
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 172;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}
#elif defined HT501x
__stackless void KEY_IRQHandler(void)
{
    
}
#endif

/*
*********************************************************************************************************
*                                 EXTI7 INTERRUPT HANDLER  #16+28
*
*********************************************************************************************************
*/
#if defined  HT6x2x
__stackless void EXTI7_IRQHandler(void)
{
    if(SET == HT_EXTIRise_ITFlagStatusGet(INT_EXTIF2_RIF_INT7))         /*!< INT7�������ж�           */
    {
        
        HT_EXTIRise_ClearITPendingBit(INT_EXTIF2_RIF_INT7);             /*!< ����жϱ�־             */
    }
    
    if(SET == HT_EXTIFall_ITFlagStatusGet(INT_EXTIF2_FIF_INT7))         /*!< INT7�½����ж�           */
    {
        
        HT_EXTIFall_ClearITPendingBit(INT_EXTIF2_FIF_INT7);             /*!< ����жϱ�־             */
    }
}
#elif  defined  HT6x3x
__stackless void EXTI7_IRQHandler(void)
{
#if 0
    if(SET == HT_EXTIRise_ITFlagStatusGet(INT_EXTIF2_RIF_INT7))         /*!< INT7�������ж�           */
    {
        
        HT_EXTIRise_ClearITPendingBit(INT_EXTIF2_RIF_INT7);             /*!< ����жϱ�־             */
    }
    
    if(SET == HT_EXTIFall_ITFlagStatusGet(INT_EXTIF2_FIF_INT7))         /*!< INT7�½����ж�           */
    {
        
        HT_EXTIFall_ClearITPendingBit(INT_EXTIF2_FIF_INT7);             /*!< ����жϱ�־             */
    }
    
    
    if(SET == HT_EXTIRise_ITFlagStatusGet(INT_EXTIF2_RIF_INT8))         /*!< INT8�������ж�           */
    {
        
        HT_EXTIRise_ClearITPendingBit(INT_EXTIF2_RIF_INT8);             /*!< ����жϱ�־             */
    }
    
    if(SET == HT_EXTIFall_ITFlagStatusGet(INT_EXTIF2_FIF_INT8))         /*!< INT8�½����ж�           */
    {
        
        HT_EXTIFall_ClearITPendingBit(INT_EXTIF2_FIF_INT8);             /*!< ����жϱ�־             */
        
    }
    
    
    if(SET == HT_EXTIRise_ITFlagStatusGet(INT_EXTIF2_RIF_INT9))         /*!< INT9�������ж�           */
    {
        
        HT_EXTIRise_ClearITPendingBit(INT_EXTIF2_RIF_INT9);             /*!< ����жϱ�־             */
    }
    
    if(SET == HT_EXTIFall_ITFlagStatusGet(INT_EXTIF2_FIF_INT9))         /*!< INT9�½����ж�           */
    {
        
        HT_EXTIFall_ClearITPendingBit(INT_EXTIF2_FIF_INT9);             /*!< ����жϱ�־             */
        
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 176;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}
#endif
/*
*********************************************************************************************************
*                                 EXTI8 INTERRUPT HANDLER  #16+29
*
*********************************************************************************************************
*/
#if defined  HT6x2x
__stackless void EXTI8_IRQHandler(void)
{
    if(SET == HT_EXTIRise_ITFlagStatusGet(INT_EXTIF2_RIF_INT8))         /*!< INT8�������ж�           */
    {
        
        HT_EXTIRise_ClearITPendingBit(INT_EXTIF2_RIF_INT8);             /*!< ����жϱ�־             */
    }
    
    if(SET == HT_EXTIFall_ITFlagStatusGet(INT_EXTIF2_FIF_INT8))         /*!< INT8�½����ж�           */
    {
        
        HT_EXTIFall_ClearITPendingBit(INT_EXTIF2_FIF_INT8);             /*!< ����жϱ�־             */
    }
}
#endif

/*
*********************************************************************************************************
*                                 EXTI9/SPI INTERRUPT HANDLER  #16+30
*
*********************************************************************************************************
*/
#if defined  HT6x2x
__stackless void EXTI9_IRQHandler(void)
{
    if(SET == HT_EXTIRise_ITFlagStatusGet(INT_EXTIF2_RIF_INT9))         /*!< INT9�������ж�           */
    {
        
        HT_EXTIRise_ClearITPendingBit(INT_EXTIF2_RIF_INT9);             /*!< ����жϱ�־             */
    }
    
    if(SET == HT_EXTIFall_ITFlagStatusGet(INT_EXTIF2_FIF_INT9))         /*!< INT9�½����ж�           */
    {
        
        HT_EXTIFall_ClearITPendingBit(INT_EXTIF2_FIF_INT9);             /*!< ����жϱ�־             */
    }
}
#elif  defined  HT6x3x
__stackless void SPI2_IRQHandler()
{
#if 0
    if(SET == HT_SPI_ITFlagStatusGet(HT_SPI2,SPI_SPISTA_MODF))          /*!< SPI1ģʽ���ϱ�־λ     */
    {
        
        HT_SPI_ClearITPendingBit(HT_SPI2, SPI_SPISTA_MODF);             /*!< ����жϱ�־          */
    }
    
    if(SET == HT_SPI_ITFlagStatusGet(HT_SPI2, SPI_SPISTA_SPIF))         /*!< SPI1���ݴ�����ɱ�־λ*/
    {
        
        HT_SPI_ClearITPendingBit(HT_SPI2, SPI_SPISTA_SPIF);             /*!< ����жϱ�־          */
    }
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 180;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}
#endif
/*
*********************************************************************************************************
*                                 DMA INTERRUPT HANDLER  #16+31
*
*********************************************************************************************************
*/
#if defined  HT6x2x  ||  defined  HT6x3x
__stackless void DMA_IRQHandler(void)
{
#if 0
    HT_DMA_ClearITPendingBit(DMA_DMAIF_TCIF1);
    DMA_Cmd(HT_DMA_Channel1, DISABLE);
    DMA_Cmd(HT_DMA_Channel0, DISABLE);
#endif

    uint32_t appVectors = ApplicationAddress;
    uint32_t offset = 184;

    __asm volatile
    (
    "   add r0, %0, %1              \n" 
    "   ldr r0, [r0]                \n"
    "   bx  r0                      \n"
    :   "+r"(appVectors), "+r"(offset)
    );
}
#endif




