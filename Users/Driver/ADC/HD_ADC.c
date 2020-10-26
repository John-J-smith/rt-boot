/****************************************************************
Description: HD_ADC.c
Author: shijj
Notes: ADC驱动
*****************************************************************/
#define __HD_ADC_C__
/*- 1.Include---------------------------------------------------*/
#include "Include.h"
#include "HD_ADC.h"

//wait to add......

/*- 2.Macro-----------------------------------------------------*/


/*- 3.Private variable------------------------------------------*/
U16  usSupValueData; 

/*private functions defined in this file:------------------------------------*/
/*
*********************************************************************************************************
*                                     TBS INTERRUPT HANDLER  #16+19
*
*********************************************************************************************************
*/

void TBS_IRQHandler()
{

    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_TMPIF))                 /*!< 温度测量中断          */
    {

        HT_TBS_ClearITPendingBit(TBS_TBSIF_TMPIF);                     /*!< 清除中断标志          */
    }

    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_VBATIF))                /*!< 电池测量中断          */
    {

        HT_TBS_ClearITPendingBit(TBS_TBSIF_VBATIF);                    /*!< 清除中断标志          */
    }

    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC0IF))                /*!< ADC0测量中断          */
    {

        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC0IF);                    /*!< 清除中断标志          */
    }

    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC1IF))                /*!< ADC1测量中断          */
    {
        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC1IF);                    /*!< 清除中断标志          */
        usSupValueData = HT_TBS_ValueRead(TBS_ADC1);
        usSupValueData = (U16)(0.0255 * usSupValueData + 0.05516) * 16; //3位小数
    }

    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_VBATCMPIF))             /*!< 电池电压比较中断      */
    {

        HT_TBS_ClearITPendingBit(TBS_TBSIF_VBATCMPIF);                 /*!< 清除中断标志          */
    }

    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_VCCIF))                 /*!< 电源测量中断          */
    {

        HT_TBS_ClearITPendingBit(TBS_TBSIF_VCCIF);                     /*!< 清除中断标志          */
    }
    
#if defined  HT501x  ||  defined  HT502x
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC2IF))                /*!< ADC2测量中断          */
    {

        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC2IF);                    /*!< 清除中断标志          */
    }
#endif

#if defined  HT501x
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_VREFIF))                /*!< VREF测量中断          */
    {

        HT_TBS_ClearITPendingBit(TBS_TBSIF_VREFIF);                    /*!< 清除中断标志          */
    }
#endif

#if defined  HT6x2x  ||  defined  HT6x3x
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC3IF))                /*!< ADC3测量中断          */
    {

        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC3IF);                    /*!< 清除中断标志          */
    }

    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC4IF))                /*!< ADC4测量中断          */
    {

        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC4IF);                    /*!< 清除中断标志          */
    }

    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC5IF))                /*!< ADC5测量中断          */
    {

        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC5IF);                    /*!< 清除中断标志          */
    }
#endif

#if defined  HT6x2x  ||  defined  HT6x3x  ||  defined  HT501x  ||  defined  HT502x
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC0CMPIF))             /*!< ADC0CMP测量中断       */
    {

        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC0CMPIF);                 /*!< 清除中断标志          */
    }
#endif

#if defined  HT501x  ||  defined  HT502x
    if(SET == HT_TBS_ITFlagStatusGet(TBS_TBSIF_ADC1CMPIF))             /*!< ADC1CMP测量中断       */
    {

        HT_TBS_ClearITPendingBit(TBS_TBSIF_ADC1CMPIF);                 /*!< 清除中断标志          */
    }
#endif

}

void HD_ADC_Init(void)
{
    HT_TBSConfig(TBS_TBSCON_ADC1En, ENABLE);

    HT_TBS_ClkSelConfig(TBS_CLKSEL_PLLDIV);

    HT_TBS_ITConfig(TBS_TBSIE_ADC1IE, ENABLE);

    HT_TBS_PeriodSet(ADC1PRD, TBS_TBSPRD_ADC1PRD_2S);

    NVIC_SetPriority(TBS_IRQn, 3);  
    NVIC_EnableIRQ(TBS_IRQn);
}



