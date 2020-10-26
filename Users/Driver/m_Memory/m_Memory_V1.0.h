/*
*****************************************************************************
 Copyright (C)
 Module         : MemoryÄ£¿é
 File Name      : m_Memory_V1.0.h
 Description    :
 others         :
 Meter Type     £º
 ----------------------------------------------------------------------------
 Modification History:
 <No.> <version >  <time>        <author>     <contents>

*****************************************************************************
*/
#ifndef  __M_MEMORY_H__
#define  __M_MEMORY_H__

#include "include.h"

/*---------------------------------------------------------------------------*
 * TYPE AND CONSTANT                            *
 *---------------------------------------------------------------------------*/
typedef enum
{
    E_CHIP_FLASH  = 0x00,  //need to be modified, defined by chip
    E_FRAM        = 0x01,  //fiexd
    E_EEPROM      = 0x02,  //fixed
    E_DATAFLASH   = 0x03,  //fixed
    E_CHIP_RAM    = 0x20,  //need to be modified, defined by chip
    E_CHIP_EEPROM = 0x05,  //need to be modified, defined by chip
    E_EXT_RTC     = 0x06,  //need to be modified, defined by RTC chip
    E_COG_LCD     = 0x07,  //need to be modified, defined 
    E_OTHER_CHIP  = 0x08,  //need to be modified, defined by users
    
    E_MEM_MAX,
}ENUM_MEM_TYPE;

#define MCU_FLASH_SIZE         0x40000
#define MCU_FLASH_START_ADDR   0x00000000

#define MCU_RAM_SIZE           0x10000
#define MCU_RAM_START_ADDR     0x20000000


#ifndef __M_MEMORY_C__
    #define __VAR_DEFINE  extern
    
#else
    #define __VAR_DEFINE  

#endif
#undef __VAR_DEFINE

/*---------------------------------------------------------------------------*
 * prototypes define                            *
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
 * external variables                           *
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
 * external routine prototypes                  *
 *---------------------------------------------------------------------------*/
extern U8 m_Memory_WriteData(U32 ulAddr, U8 *pucData, U32 ulLen);
extern U8 m_Memory_ReadData(U32 ulAddr, U8 *pucData, U32 ulLen);

#endif

/*---------------------------------------------------------------------------*/
