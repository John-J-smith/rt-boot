/******************************************************************************
 Copyright (C) Aug.2，2004  R&D Institute of Reallin Co., Ltd.
 Module         : 主任务模块
 Description    : 
 Build Date     : 
 others         : 
 ------------------------------------------------------------------------------
 Modification History:
 <No.> <version >  <time>        <author>     <contents> 
  2、    
  1、    1.00     2015-01-05    yaoc     build this moudle     
******************************************************************************/

#ifdef   __cplusplus
extern   "C"
{
#endif

#ifndef  _AL_MAIN_C
#define  _AL_MAIN_C

#include "Include.h"


/**
* @brief  Clock_Init:
- PLLL input clock    : External 32K crystal
- PLLL frequency      : 26M
- AHB Clock source    : PLLL
- AHB Clock frequency : 26M (PLLL divided by 1)
- APB Clock frequency : 13M (AHB Clock divided by 2)
* @param  None
* @retval None
*/
void Clock_Init(void)
{
    SwitchTo_Fpll(SPD_MCU);
}

/*******************************************************************************
* @Description: 系统初始
* @Param      : 
* @Return     : 
* @History    : 
* <No.> <version>   <time>          <author>    <contents> 
* 1     1.0         2019-03-03      @shijj      create
*******************************************************************************/
void AL_Init(void)
{
    U8 ucCnt;
    U8 ucPowerStable;

    __disable_irq();
    
    HD_clrWDT();
    HD_System_RCC_Init();
    g_ulMCLK = HT_CMU_SysClkGet();
    HD_System_PVDConfig();
    HD_System_PMUConfig();
    HD_clrWDT();

    ucPowerStable = 0;
    for(ucCnt = 0; ucCnt < 20; ucCnt++) 
    {
        Delay_ms(10);
        ucPowerStable <<= 1;
        if(PFAL_Read() != 0)
        {
            ucPowerStable++;
        }
        if(ucPowerStable == 0xff)//检测电源稳定，提前退出
        {
            break;
        }
        g_ulMCLK = HT_CMU_SysClkGet();
        HD_clrWDT();
    }
    Clock_Init();
    g_ulMCLK = HT_CMU_SysClkGet();
    
    HD_GPIO_Init();
    HD_Flash_Init();
    Stdio_Init();
    
    //__enable_irq();
}


#ifdef   __cplusplus
}
#endif

#endif



