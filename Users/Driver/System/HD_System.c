/******************************************************************************
 Copyright (C) Aug.2��2004  R&D Institute of Reallin Co., Ltd.
 Module         : ϵͳ������������ģ��
 Description    :
 Build Date     :
 others         :
 ------------------------------------------------------------------------------
 Modification History:
 <No.> <version >  <time>        <author>     <contents>
  2��
  1��    1.00     2015-01-05    yaoc     build this moudle     
******************************************************************************/
#define __HD_SYSTEM_C__
#include  "Include.h"

//wait to add......
/*- 2.Macro-----------------------------------------------------*/


/*- 3.Private variable------------------------------------------*/


/*- 4.Public variable-------------------------------------------*/
U32 g_ulMCLK;/*ϵͳʱ��Ƶ��*/


/*- 5.Private function------------------------------------------*/


/*- 6.Const-----------------------------------------------------*/


/*- 7.End-------------------------------------------------------*/

/*******************************************************************************
 ����������  �л���LRCʱ��
 ���������
 ���ز�����
 ����˵����  32KHz
 *******************************************************************************/
/*
void SwitchTo_Flrc(void)
{
	if ((HT_CMU->SYSCLKCFG != 0x0000)
	 || (HT_CMU->LRCADJ    != 0x00B5)
	 || (HT_CMU->SYSCLKDIV != 0x0000))
	{
		_OPEN_REG_WRITE;
		HT_CMU->LRCADJ    = 0x00B5;			 //���32768Hz
		HT_CMU->SYSCLKDIV = 0x0000;			 //Fcpu = Fsys
 // 	 Delay_mSec(2);
		HT_CMU->SYSCLKCFG = 0x0080;			 //Fsys = Flrc
		__NOP();
		HT_CMU->SYSCLKCFG = 0x0000;			 //Fsys = Flrc
		 
		HT_CMU->CLKCTRL0 &= ~0x0030;			 //�ر�PLL,HRC
		_CLOSE_REG_WRITE;
	}
}*/
/*******************************************************************************
����������	�л���HRCʱ��
���������
���ز�����
����˵����	11MHz
			����ʱ��Ҫ��ʱ500us
*******************************************************************************/
void SwitchTo_Fhrc(void)
{
	U32	adj0, adj1;
	
	adj0 = *(U32*)0x40140;
	adj1 = *(U32*)0x40144;
	adj1 = ~ adj1;

	if (adj0 != adj1)			//δУ׼
	{
		adj0 = 0x0040;
	}
	adj0 &= 0x007F;
	
	if ((HT_CMU->SYSCLKCFG != 0x0002)
	|| (HT_CMU->HRCADJ    != adj0)
	|| (HT_CMU->HRCDIV    != 0x0000)
	|| !(HT_CMU->CLKCTRL0 & 0x0020)
#if	(SPD_MCU == SPD_22000K)
	|| (HT_CMU->SYSCLKDIV != 0x0000))
#else
	|| (HT_CMU->SYSCLKDIV != SPD_MCU-1))
#endif
	{
		_OPEN_REG_WRITE;
		HT_CMU->HRCADJ    = adj0;				//���11MHz
		HT_CMU->HRCDIV    = 0x0000;				//Fhrc' = Fhrc = 11MHz
		HT_CMU->CLKCTRL0 |= 0x0020;				//ʹ��HRC
#if	(SPD_MCU == SPD_22000K)
		HT_CMU->SYSCLKDIV = 0x0000;				//Fcpu  = Fsys = 11MHz
#else
		HT_CMU->SYSCLKDIV = SPD_MCU-1;			//Fcpu  = Fsys = 11MHz
#endif
		HT_CMU->SYSCLKCFG = 0x0082;				//Fsys = Fhrc'
		__NOP();
		HT_CMU->SYSCLKCFG = 0x0002;				//Fsys = Fhrc'
		_CLOSE_REG_WRITE;
	}
}
/*******************************************************************************
����������	�л���PLLʱ��
���������
���ز�����
����˵����	22MHz
			����ʱ��Ҫ��ʱ2ms,��֮ǰû�п���Flf(Fosc)������ʱ500ms
*******************************************************************************/
void SwitchTo_Fpll(U8 ucClk)
{
	if ((HT_CMU->SYSCLKCFG != 0x0003)
	|| !(HT_CMU->CLKCTRL0 & 0x0010)				//ʹ��PLL
	|| (HT_CMU->SYSCLKDIV != ucClk))
	{
		_OPEN_REG_WRITE;
		HT_CMU->CLKCTRL0 |= 0x0010;				//ʹ��PLL
		while(!(HT_CMU->CLKSTA & 0x0020));/*�ȴ�PLL�����ȶ�*/
		HT_CMU->SYSCLKDIV = ucClk;			    //Fcpu = Fsys/2 = Fpll/2 = 11.010048MHz
		HT_CMU->SYSCLKCFG = 0x0083;				//Fsys = Fpll
		__NOP();
		HT_CMU->SYSCLKCFG = 0x0003;				//Fsys = Fpll
		_CLOSE_REG_WRITE;
	}
}
/*****************************************************************************
Description:
Input:
Output:
Return:
******************************************************************************/
void HD_CfgClk_CloseHRC(void)
{

}

/*****************************************************************************
Description:
Input:
Output:
Return:
******************************************************************************/
void HD_CfgClk_RunOSC(void)
{

}

/*****************************************************************************
Description:
Input:
Output:
Return:
******************************************************************************/
void HD_CfgClk_ClosePLL(void)
{

}

/*****************************************************************************
Description:
Input:
Output:
Return:
******************************************************************************/
void HD_CfgClk_RunHRC(void)
{

}

/*****************************************************************************
Description:
Input:
Output:
Return:
******************************************************************************/
void HD_System_PVDConfig(void)
{
    _OPEN_REG_WRITE;
    HT_PMU->PMUCON = 0x0007; //����LVDIN0_DETģ��,����BOR_DETģ��
    HD_System_GPIO_AF(HT_GPIOE, IO_POWER_FAIL_DT_PIN, GPIO_AF_LVDIN0, PUPDR_OD);
}

/*****************************************************************************
Description:��λ������������û�����õ�PMU�Ĵ���
Input:
Output:
Return:
******************************************************************************/
void HD_System_PMUConfig(void)
{
    HT_PMU->VDETCFG = 0x000D;//VSYS_LVL   3.0V, BOR_LVL   2.2V
    HT_PMU->VDETPCFG = 0x003C;/*Hold,Sleepģʽ��,VSYS_DET,BOR_DET,LVDIN_DET��ʱ���ʱ���趨:ʱ��560us,����268ms*/
    HT_PMU->WAKEIF = 0x0000;
    HT_PMU->PMUIE = 0x0000;
    HT_PMU->PMUIF = 0x0000;
}
/*****************************************************************************
Description:
Input:
Output:
Return:
******************************************************************************/
void HD_System_PVD_INTCfg(U8 ucEnable)
{
	if(ucEnable == TRUE)
    {
        HT_PMU->PMUIE |= 0x08; 
    }
    else
    {
        HT_PMU->PMUIE &= ~0x08; 
    }
}

/*****************************************************************************
Description:
Input:
Output:
Return:
******************************************************************************/
U8 HD_System_IsPVDIntStatus(void)
{
 	if(HT_PMU->PMUIF & 0x08)
    {
        return _true;
    }
    else
    {
        return _false;
    }   
}

/*********************************************************************************  
Function name: void HD_System_RCC_Init(void)
Description:   ��������
Input:  
Return:  
Notes: �е�ģʽ��ʱ�ӳ�ʼ��
Modification History:
<No.> <version >  <time>        <author>     <contents>

**********************************************************************************/
void HD_System_RCC_Init(void)
{
	/*Bit15-EMU-colse,  Bit14-AES-colse,    Bit13-1P5LBOR-colse, Bit12-CLKOUT-colse,
    Bit11-KEY-colse,  Bit10-OSC-enable,   Bit9-HRC_DET-colse,  Bit8-PLL_DET-colse,
    Bit7-LF_DET-colse,Bit6-PLL_LOCK-colse,Bit5-HRC_EN-enable,  Bit4-PLL_EN-colse,
    Bit3-I2C-colse,   Bit2-SPI-colse,     Bit1-LCD-colse,      Bit0-XXX-colse*/
    _OPEN_REG_WRITE;//Boot�����Ѵ���
    HT_CMU->CLKCTRL0 = 0x0420;
    /*��������ʱ������:UART,Timer,RTC..*/
    _OPEN_REG_WRITE;
    HT_CMU->CLKCTRL1 = 0x0000;
    /*Ĭ��ֵ*/
    _OPEN_REG_WRITE;
    HT_CMU->LRCADJ = 0x0009;
    /*Ĭ��ֵ*/
    _OPEN_REG_WRITE;
    HT_CMU->HRCADJ = 0x0040;

	//SwitchTo_Flrc();
}
/*********************************************************************************  
Function name: void System_RCC_PD_Init(void)
Description:   ��������
Input:  
Return:  
Notes: ͣ��ģʽ��ʱ�ӳ�ʼ��
Modification History:
<No.> <version >  <time>        <author>     <contents>
    1��    1.00     2014-02-10   yaoc             Creat
**********************************************************************************/
void HD_System_RCC_PD_Init(void)
{
	HT_PMU->PMUIE = 0x01;
    HT_PMU->PMUIF = 0;
    HT_PMU->VDETPCFG = 0x1C;//BOR�������268ms,���ʱ��560us.
    /*ϵͳ���� */
    _OPEN_REG_WRITE;
    HT_CMU->SYSCLKCFG = 0x81;              //OSC as Fsys 
    HT_CMU->SYSCLKDIV = 0x00; 	 
    HD_clrWDT();
    _OPEN_REG_WRITE;
    HT_CMU->CLKCTRL0 = 0xA400;             //close HRC...
    //HT_PMU->PMUCON = 0x0002;
    _OPEN_REG_WRITE;
    HT_CMU->CLKCTRL1 = 0;
    //TPS config-----------------------------------------
    //HT_TBS->TBSCON = 0x0101;//Chop����  2��ƽ�����   osr=64  
    //HT_TBS->TBSIE = 0x00;
    //HT_TBS->TBSPRD = 0x00;//1s��1��
    HT_TBS->TBSCON = 0x6541;//�¶Ȳ����򿪣�reserved��ֵ�����ֲ�Ҫ�󱣳�Ĭ��ֵ
    HT_TBS->TBSIE = 0x00;
    HT_TBS->TBSPRD = 0x04;//8s��1��
    //�رյ�ƵRC�Թرտ��Ź�
    //_OPEN_REG_WRITE;
    //HT_RTC->CTRLBYFLASH&=0xfffd;
    //HT_RTC->LRCCOMAND=0x5555;
    //HT_RTC->LRCCOMAND=0xAAAA;
}
/*********************************************************************************  
Function name: void HD_System_NVIC_Init(void)
Description:   ��������
Input:  
Return:  
Notes: �е�ģʽ���жϳ�ʼ��
Modification History:
<No.> <version >  <time>        <author>     <contents>
    1��    1.00     2014-02-10   yaoc             Creat
**********************************************************************************/
void HD_System_NVIC_Init(void)
{
    /*Timer1 �ж�*/
    NVIC_SetPriority(TIMER_1_IRQn, 0x00);
    NVIC_EnableIRQ(TIMER_1_IRQn);
    /*Timer3 �ж�*/
    NVIC_SetPriority(TIMER_3_IRQn, 0x01);
    NVIC_EnableIRQ(TIMER_3_IRQn);
	/*Uart 0 �ж�*/
    NVIC_SetPriority(UART0_IRQn, 0x02);  
    NVIC_EnableIRQ(UART0_IRQn);
	/*Uart 1 �ж�*/
    NVIC_SetPriority(UART1_IRQn, 0x02);  
    NVIC_EnableIRQ(UART1_IRQn);
	/*Uart 2 �ж� PLCͨ�� 115200������*/
    NVIC_SetPriority(UART2_IRQn, 0x00);  
    NVIC_EnableIRQ(UART2_IRQn);
	/*Uart 3 �ж�*/
    NVIC_SetPriority(UART3_IRQn, 0x02);  
    NVIC_EnableIRQ(UART3_IRQn);
	/*Uart 4 �ж�*/
    NVIC_SetPriority(UART4_IRQn, 0x02);  
    NVIC_EnableIRQ(UART4_IRQn);
    /*Uart 5 �ж�*/
    NVIC_SetPriority(UART5_IRQn, 0x02);  
    NVIC_EnableIRQ(UART5_IRQn);  
	/*Uart 6 �ж�*/
    NVIC_SetPriority(UART6_IRQn, 0x02);  
    NVIC_EnableIRQ(UART6_IRQn); 
    /*RTC �ж�*/  
    NVIC_SetPriority(RTC_IRQn, 0x03);    
    NVIC_EnableIRQ(RTC_IRQn); 	
    /*INT 0 */
    NVIC_SetPriority(EXTI0_IRQn, 0x03);      
    NVIC_EnableIRQ(EXTI0_IRQn);
	/*INT 2 */
    NVIC_SetPriority(EXTI2_IRQn, 0x03);      
    NVIC_DisableIRQ(EXTI2_IRQn);
	/*INT 3 */
    NVIC_SetPriority(EXTI3_IRQn, 0x03);      
    NVIC_DisableIRQ(EXTI3_IRQn);
	/*INT 8 */
   	NVIC_SetPriority(EXTI8_IRQn, 0x03);      
   	NVIC_EnableIRQ(EXTI8_IRQn);
   	/*INT 9 */
   	NVIC_SetPriority(EXTI9_IRQn, 0x03);      
   	NVIC_EnableIRQ(EXTI9_IRQn);
}
/*********************************************************************************  
Function name: void HD_System_NVIC_PD_Init(void)
Description:   ��������
Input:  
Return:  
Notes: ͣ��ģʽ���жϳ�ʼ��
Modification History:
<No.> <version >  <time>        <author>     <contents>
    1��    1.00     2014-02-10   yaoc             Creat
**********************************************************************************/

void HD_System_NVIC_PD_Init(void)
{
	/*Timer1 �ж�*/
    NVIC_SetPriority(TIMER_1_IRQn, 0x00);
    NVIC_DisableIRQ(TIMER_1_IRQn);
	/*Timer2 �ж�*/
    NVIC_SetPriority(TIMER_2_IRQn, 0x00);
    NVIC_DisableIRQ(TIMER_2_IRQn);
    /*Timer3 �ж�*/
    NVIC_SetPriority(TIMER_3_IRQn, 0x01);
    NVIC_DisableIRQ(TIMER_3_IRQn);
	/*Uart 0 �ж�*/
    NVIC_SetPriority(UART0_IRQn, 0x02);  
    NVIC_DisableIRQ(UART0_IRQn);
	/*Uart 1 �ж�*/
    NVIC_SetPriority(UART1_IRQn, 0x02);  
    NVIC_DisableIRQ(UART1_IRQn);
	/*Uart 2 �ж� PLCͨ�� 115200������*/
    NVIC_SetPriority(UART2_IRQn, 0x00);  
    NVIC_DisableIRQ(UART2_IRQn);
	/*Uart 3 �ж�*/
    NVIC_SetPriority(UART3_IRQn, 0x02);  
    NVIC_DisableIRQ(UART3_IRQn);
	/*Uart 4 �ж�*/
    NVIC_SetPriority(UART4_IRQn, 0x02);  
    NVIC_DisableIRQ(UART4_IRQn);
    /*Uart 5 �ж�*/
    NVIC_SetPriority(UART5_IRQn, 0x02);  
    NVIC_DisableIRQ(UART5_IRQn);  
	/*Uart 6 �ж�*/
    NVIC_SetPriority(UART6_IRQn, 0x02);  
    NVIC_DisableIRQ(UART6_IRQn); 
    /*RTC �ж�*/  
    NVIC_SetPriority(RTC_IRQn, 0x03);    
    NVIC_EnableIRQ(RTC_IRQn); 	
    /*INT 0 */
    NVIC_SetPriority(EXTI0_IRQn, 0x03);      
    NVIC_DisableIRQ(EXTI0_IRQn);
	/*INT 2 */
    NVIC_SetPriority(EXTI2_IRQn, 0x03);      
    NVIC_EnableIRQ(EXTI2_IRQn);
	/*INT 3 */
    NVIC_SetPriority(EXTI3_IRQn, 0x03);      
    NVIC_EnableIRQ(EXTI3_IRQn);
	/*INT 8 */
   	NVIC_SetPriority(EXTI8_IRQn, 0x03);      
   	NVIC_DisableIRQ(EXTI8_IRQn);
   	/*INT 9 */
   	NVIC_SetPriority(EXTI9_IRQn, 0x03);      
   	NVIC_DisableIRQ(EXTI9_IRQn);
}

/*********************************************************************************  
Function name:  void HD_System_ADC_Init(void)
Description:   ��������
Input:  
Return:  
Notes: �ⲿ�ж�ʹ��
Modification History:
<No.> <version >  <time>        <author>     <contents>
    1��    1.00     2014-02-10   yaoc             Creat
**********************************************************************************/

void HD_System_ADC_Init(void)
{
    /* Enable CLOCK */
    _OPEN_REG_WRITE;
    HT_TBS->TBSCON |= 0x23;  /*ʹ��PLL 16��Ƶʱ��Դ(֧�ֿ����л�)���¶ȼ�� VBAT ��ص�ѹ���*/
}
/*********************************************************************************  
  Function name:  void HD_CfgCLK_FOSC_32K( void )
  Description:����ģ��
  Input:   
  Return:  
  Notes:   ����Ӳ��ʱ��Ϊ32k ,ʹ��OSC ʱ��,MCLK = 32.768KHZ 
  Modification History:
  <No.> <version >  <time>        <author>     <contents>
   1��    1.00     2014-02-20       yaoc        Creat
**********************************************************************************/
void HD_CfgCLK_FOSC_32K(U8 ucLcdState)
{
    /* Enable LSE*/
    _OPEN_REG_WRITE;
    HT_CMU->SYSCLKCFG = 0x81;  /*ѡ��OSC*/
    HT_CMU->SYSCLKDIV = 0x00;  
    _OPEN_REG_WRITE;
    HT_CMU->CLKCTRL0 &= ~PLL_EN;/*PLL ʱ�Ӳ�ʹ��*/	
    _OPEN_REG_WRITE;
    HT_CMU->CLKCTRL0 &= ~LCD_EN;/*PLL ʱ��ʹ��*/
}

/*********************************************************************************  
  Function name:  void HD_CfgCLK_MSI_614K( void )
  Description:����ģ��
  Input:   
  Return:  
  Notes:   ����Ӳ��ʱ��Ϊ614k ,ʹ��PLL ʱ��,MCLK = 1/32PLL 
  Modification History:
  <No.> <version >  <time>        <author>     <contents>
   1��    1.00     2014-02-20       yaoc        Creat
**********************************************************************************/
void HD_CfgCLK_PLL_614K(void)
{

}
/*********************************************************************************  
   Function name:  void HD_CfgCLK_PLL_1M376( void )
   Description:����ģ��
   Input:	
   Return:	
   Notes:	����Ӳ��ʱ��Ϊ1.376M ,ʹ��PLL ʱ��,,MCLK = 1/16PLL 
   Modification History:
   <No.> <version >  <time> 	   <author> 	<contents>
	1��    1.00 	2014-02-20		 yaoc		 Creat
**********************************************************************************/
void HD_CfgCLK_PLL_1M376(void)
{
	/* Enable HSE */
	_OPEN_REG_WRITE;
	HT_CMU->CLKCTRL0 |= PLL_EN;/*PLL ʱ��ʹ��*/
	while(!(HT_CMU->CLKSTA & 0x0020));/*�ȴ�PLL�����ȶ�*/
	HT_CMU->SYSCLKCFG = 0x83;	/*ѡ��PLL*/
	HT_CMU->SYSCLKDIV = 0x04;	/*PLL ���1.376MHZ,MCLK = PLL/16*/
	//g_ulMCLK = 1376256;
 
	_OPEN_REG_WRITE;
	HT_CMU->CLKCTRL0 &= 0xFFDF;			//close HRC
}

 /*********************************************************************************  
   Function name:  void HD_CfgCLK_PLL_22M( void )
   Description:����ģ��
   Input:   
   Return:  
   Notes:   ����Ӳ��ʱ��Ϊ22M
   Modification History:
   <No.> <version >  <time>        <author>     <contents>
    1��    1.00     2014-02-20       yaoc        Creat
 **********************************************************************************/
void HD_CfgCLK_PLL_22M(void)
{
    //��ʹ��hrc��ʹ���ڲ���PLLʱ��
    //SwitchTo_Fhrc();
    SwitchTo_Fpll(SPD_MCU);
}

 
