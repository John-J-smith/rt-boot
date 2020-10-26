�?/*
;*********************************************************************************************************
;*                                             HT6X3X
;*                                         Library Function
;*
;*                                  Copyright 2013, Hi-Trend Tech, Corp.
;*                                       All Rights Reserved
;*
;*
;* Project      : HT6xxx
;* File         : startup_ht6x3x.s
;* By           : SocTeam
;* Version      : CurrentVersion1_2_20171108
;* Description  :
;*********************************************************************************************************
;*/

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .password:CODE
        DCD     0xE7FFFFA2

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler             ; Reset Handler
        DCD     NMI_Handler               ; NMI Handler
        DCD     HardFault_Handler         ; Hard Fault Handler
        DCD     0                         ; MPU Fault Handler
        DCD     0                         ; Bus Fault Handler
        DCD     0                         ; Usage Fault Handler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     SVC_Handler               ; SVCall Handler
        DCD     0                         ; Debug Monitor Handler
        DCD     0                         ; Reserved
        DCD     PendSV_Handler            ; PendSV Handler
        DCD     SysTick_Handler           ; SysTick Handler

        ; External Interrupts
        DCD     PMU_IRQHandler            ; 16+ 0: PMU
        DCD     AES_IRQHandler            ; 16+ 1: AES
        DCD     EXTI0_IRQHandler          ; 16+ 2: EXTI0
        DCD     EXTI1_IRQHandler          ; 16+ 3: EXTI1
        DCD     EXTI2_IRQHandler          ; 16+ 4: EXTI2
        DCD     EXTI3_IRQHandler          ; 16+ 5: EXTI3
        DCD     EXTI4_IRQHandler          ; 16+ 6: EXTI4
        DCD     EXTI5_IRQHandler          ; 16+ 7: EXTI5
        DCD     EXTI6_IRQHandler          ; 16+ 8: EXTI6
        DCD     UART0_IRQHandler          ; 16+ 9: UART0
        DCD     UART1_IRQHandler          ; 16+10: UART1
        DCD     UART2_IRQHandler          ; 16+11: UART2
        DCD     UART3_IRQHandler          ; 16+12: UART3
        DCD     UART4_IRQHandler          ; 16+13: UART4
        DCD     UART5_IRQHandler          ; 16+14: UART5
        DCD     TIMER_0_IRQHandler        ; 16+15: Timer0
        DCD     TIMER_1_IRQHandler        ; 16+16: Timer1
        DCD     TIMER_2_IRQHandler        ; 16+17: Timer2
        DCD     TIMER_3_IRQHandler        ; 16+18: Timer3
        DCD     TBS_IRQHandler            ; 16+19: TBS
        DCD     RTC_IRQHandler            ; 16+20: RTC
        DCD     I2C_IRQHandler            ; 16+21: I2C
        DCD     SPI0_IRQHandler           ; 16+22: SPI0
        DCD     SPI1_IRQHandler           ; 16+23: SPI1
        DCD     SelfTestFreq_IRQHandler   ; 16+24: FreqTest
        DCD     TIMER_4_IRQHandler        ; 16+25: Timer4
        DCD     TIMER_5_IRQHandler        ; 16+26: Timer5
        DCD     UART6_IRQHandler          ; 16+27: UART6
        DCD     EXTI7_IRQHandler          ; 16+28: EXTI7、EXTI8、EXTI9
        DCD     Reserved_IRQHandler       ; 16+29: Reserved
        DCD     SPI2_IRQHandler           ; 16+30: SPI2
        DCD     DMA_IRQHandler            ; 16+31: DMA


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
HardFault_Handler
        ldr     r0, =0x0001000c
        ldr     r0, [r0]
        bx      r0

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
SVC_Handler
        ldr     r0, =0x0001002c
        ldr     r0, [r0]
        bx      r0

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
PendSV_Handler
        ldr     r0, =0x00010038
        ldr     r0, [r0]
        bx      r0

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
SysTick_Handler
        ldr     r0, =0x0001003c
        ldr     r0, [r0]
        bx      r0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        PUBWEAK PMU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PMU_IRQHandler
        ldr     r0, =0x00010040
        ldr     r0, [r0]
        bx      r0

        PUBWEAK AES_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
AES_IRQHandler
        ldr     r0, =0x00010044
        ldr     r0, [r0]
        bx      r0

        PUBWEAK EXTI0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EXTI0_IRQHandler
        ldr     r0, =0x00010048
        ldr     r0, [r0]
        bx      r0

        PUBWEAK EXTI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EXTI1_IRQHandler
        ldr     r0, =0x0001004c
        ldr     r0, [r0]
        bx      r0

        PUBWEAK EXTI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EXTI2_IRQHandler
        ldr     r0, =0x00010050
        ldr     r0, [r0]
        bx      r0

        PUBWEAK EXTI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EXTI3_IRQHandler
        ldr     r0, =0x00010054
        ldr     r0, [r0]
        bx      r0

        PUBWEAK EXTI4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EXTI4_IRQHandler
        ldr     r0, =0x00010058
        ldr     r0, [r0]
        bx      r0

        PUBWEAK EXTI5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EXTI5_IRQHandler
        ldr     r0, =0x0001005c
        ldr     r0, [r0]
        bx      r0

        PUBWEAK EXTI6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EXTI6_IRQHandler
        ldr     r0, =0x00010060
        ldr     r0, [r0]
        bx      r0

        PUBWEAK UART0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UART0_IRQHandler
        ldr     r0, =0x00010064
        ldr     r0, [r0]
        bx      r0

        PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UART1_IRQHandler
        ldr     r0, =0x00010068
        ldr     r0, [r0]
        bx      r0

        PUBWEAK UART2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UART2_IRQHandler
        ldr     r0, =0x0001006c
        ldr     r0, [r0]
        bx      r0

        PUBWEAK UART3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UART3_IRQHandler
        ldr     r0, =0x00010070
        ldr     r0, [r0]
        bx      r0

        PUBWEAK UART4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UART4_IRQHandler
        ldr     r0, =0x00010074
        ldr     r0, [r0]
        bx      r0

        PUBWEAK UART5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UART5_IRQHandler
        ldr     r0, =0x00010078
        ldr     r0, [r0]
        bx      r0

        PUBWEAK TIMER_0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIMER_0_IRQHandler
        ldr     r0, =0x0001007c
        ldr     r0, [r0]
        bx      r0

        PUBWEAK TIMER_1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIMER_1_IRQHandler
        ldr     r0, =0x00010080
        ldr     r0, [r0]
        bx      r0

        PUBWEAK TIMER_2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIMER_2_IRQHandler
        ldr     r0, =0x00010084
        ldr     r0, [r0]
        bx      r0

        PUBWEAK TIMER_3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIMER_3_IRQHandler
        ldr     r0, =0x00010088
        ldr     r0, [r0]
        bx      r0

        PUBWEAK TBS_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TBS_IRQHandler
        ldr     r0, =0x0001008c
        ldr     r0, [r0]
        bx      r0

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
RTC_IRQHandler
        ldr     r0, =0x00010090
        ldr     r0, [r0]
        bx      r0

        PUBWEAK I2C_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I2C_IRQHandler
        ldr     r0, =0x00010094
        ldr     r0, [r0]
        bx      r0

        PUBWEAK SPI0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI0_IRQHandler
        ldr     r0, =0x00010098
        ldr     r0, [r0]
        bx      r0

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI1_IRQHandler
        ldr     r0, =0x0001009c
        ldr     r0, [r0]
        bx      r0

        PUBWEAK SelfTestFreq_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SelfTestFreq_IRQHandler
        B SelfTestFreq_IRQHandler

        PUBWEAK TIMER_4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIMER_4_IRQHandler
        ldr     r0, =0x000100a4
        ldr     r0, [r0]
        bx      r0

        PUBWEAK TIMER_5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIMER_5_IRQHandler
        ldr     r0, =0x000100a8
        ldr     r0, [r0]
        bx      r0

        PUBWEAK UART6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UART6_IRQHandler
        ldr     r0, =0x000100ac
        ldr     r0, [r0]
        bx      r0

        PUBWEAK EXTI7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EXTI7_IRQHandler
        ldr     r0, =0x000100b0
        ldr     r0, [r0]
        bx      r0

        PUBWEAK Reserved_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved_IRQHandler
        B Reserved_IRQHandler
        ldr     r0, =0x000100b4
        ldr     r0, [r0]
        bx      r0
        
        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI2_IRQHandler
        ldr     r0, =0x000100b8
        ldr     r0, [r0]
        bx      r0

        PUBWEAK DMA_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_IRQHandler
        ldr     r0, =0x000100bc
        ldr     r0, [r0]
        bx      r0
    
        END
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
