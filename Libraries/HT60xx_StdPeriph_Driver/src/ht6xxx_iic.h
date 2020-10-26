/*
**********************************************************************************************************
*                                              HT6XXX
*                                          Library Function
*
*                                   Copyright 2013, Hi-Trend Tech, Corp.
*                                        All Rights Reserved
*                                         
*
* Project      : HT6xxx
* File         : ht6xxx_iic.h
* By           : SocTeam
* Version      : CurrentVersion
* Description  : 
**********************************************************************************************************
*/

#ifndef __HT6XXX_IIC_H__
#define __HT6XXX_IIC_H__

#ifdef __cplusplus
extern "C" {
#endif 
    
#include "ht6xxx.h"
    
/*
*********************************************************************************************************
*                                           ȫ�ֺ�/�ṹ��
*********************************************************************************************************
*/

typedef void  (*IIC_IRQ_DEF)(void);


    
/*
*********************************************************************************************************
*                                             ȫ�ֱ���
*********************************************************************************************************
*/

extern IIC_IRQ_DEF    I2C_IRQHandlerSelect; 

/*
*********************************************************************************************************
*                                           ȫ�ֺ�������
*********************************************************************************************************
*/

void HT_IIC_Init(void);
void  EEPROM_Write(unsigned char  deviceAddr, unsigned short int wordAddr, unsigned char  wordNum,  unsigned char* pword);
void  EEPROM_Read(unsigned char  deviceAddr, unsigned short int wordAddr, unsigned char  wordNum,  unsigned char* pword);




#ifdef __cplusplus
}
#endif

#endif /* __HT6XXX_IIC_H__ */ 
