/**
  ******************************************************************************
  * @file    AL_main.h 
  * @author  shijj
  * @version V1.0.0
  * @date    2019-03-06
  * @brief   Ӧ�ò�.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#ifndef __AL_MAIN_H__
#define __AL_MAIN_H__

/* Includes ------------------------------------------------------------------*/
#include "Include.h"

/* Macros --------------------------------------------------------------------*/


#if DEBUG                           
//��ӡ������Ϣ
#define print(pucBuf, usLen)       debug(pucBuf, usLen)
#else
#define print(pucBuf, usLen) 
#endif

//��ӡ������Ϣ
#define print_log(pucBuf, usLen)    do{ \
                                        if(getDebug())  \
                                            UART_write(E_UART_DEBUG, pucBuf, usLen); \
                                    }while(0)

/* Exported Functions ------------------------------------------------------- */
#ifndef _AL_MAIN_C
    #define __GLOBAL  extern
#else
    #define __GLOBAL
#endif

//functions
__GLOBAL        void                AL_Init(void);
__GLOBAL        void                AL_PowerDown_Dtc(void);

#undef __GLOBAL  

#endif

/******** (C) Copyright R&D Institute of Reallin Co., Ltd. *****END OF FILE****/

