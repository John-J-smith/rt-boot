/****************************************************************
Description: HD_ADC.h
Author: shijj
Notes: ADC 驱动头文件
*****************************************************************/
#ifndef __HD_ADC_H
#define __HD_ADC_H
/*- 1.Macro-----------------------------------------------------*/

/*- 2.Type prototype--------------------------------------------*/

/*- 3.Public variable-------------------------------------------*/


/*- 4.Public function-------------------------------------------*/
#ifndef __HD_ADC_C__
    #define __GLOBAL  extern
#else
    #define __GLOBAL
#endif

__GLOBAL void HD_ADC_Init(void);

#undef __GLOBAL  

/*- 5.End-------------------------------------------------------*/

#endif
