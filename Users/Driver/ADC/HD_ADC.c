/****************************************************************
Description: HD_ADC.c
Author: shijj
Notes: ADC����
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
        usSupValueData = HT_TBS_ValueRead(TBS_ADC1);
        usSupValueData = (U16)(0.0255 * usSupValueData + 0.05516) * 16; //3λС��
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



