/*
*****************************************************************************
 Copyright (C)
 Module         : MEMORY
 File Name      : m_Memory_V1.0.c
 Description    : 
 others         :
 Meter Type     ：
 ----------------------------------------------------------------------------
 Modification History:
 <No.> <version >  <time>        <author>     <contents>

******************************************************************************
*/
#define   __M_MEMORY_C__

/****************************************************************************/
/* 输入头文件 */

#ifndef   Debug_M_MEMORY_err
#define   Debug_M_MEMORY_err(n)
#endif

#include  "m_Memory_V1.0.h"
#include  "HD_EEPROM.h"
#include  "HD_Flash.h"

/*****************************************************************************
 * prototypes define  *
 ****************************************************************************/

/*****************************************************************************
        TYPE AND CONSTANT
*****************************************************************************/

/********************************************************************************
Function name:  
Description:    
Input:          
Output:      
Return: 
Nites:  
.................................................................................
Modification History:
 <No.> <version>      <time>         <author>      <contents>
 2、
 1、   
********************************************************************************/
U8 m_Memory_ReadData(U32 ulAddr, U8 *pucData, U32 ulLen)
{
    U8 ucMemType;
    U8 ucRtnValue;

    ucRtnValue = true;
    ucMemType = (U8)((ulAddr & 0xff000000) >> 24);
    switch(ucMemType)
    {
        case E_CHIP_FLASH:
        case E_CHIP_RAM:
        case E_CHIP_EEPROM:
        {
            if(ucMemType == E_CHIP_FLASH)
            {
                if(((ulAddr + ulLen) <= (MCU_FLASH_START_ADDR + MCU_FLASH_SIZE)) && (ulLen != 0))
                {
                    memcpy(pucData, (U8 *)ulAddr, ulLen);
                }
                else
                {
                    ucRtnValue = false;
                }
            }
            else if(ucMemType == E_CHIP_RAM)
            {
                if(((ulAddr + ulLen) <= (MCU_RAM_START_ADDR + MCU_RAM_SIZE)) && (ulLen != 0))
                {
                    memcpy(pucData, (U8 *)ulAddr, ulLen);
                }
                else
                {
                    ucRtnValue = false;
                }
            }
            else
            {
                ucRtnValue = false;
            }
            memcpy(pucData, (U8 *)ulAddr, ulLen);
        }break;
        case E_FRAM:
        case E_EEPROM:
        case E_EXT_RTC:
        case E_COG_LCD:
        {
            I2C_readData(0xa0, (U16)ulAddr, pucData, ulLen);
        }break;
        case E_DATAFLASH:
        {
            Flash_read(ulAddr, pucData, ulLen);
        }break;
        case E_OTHER_CHIP:
        {
            
        }break;
        default:
        {
            ucRtnValue = false;
        }break;
    }

    return (ucRtnValue);
}

/********************************************************************************
Function name:  
Description:    
Input:          
Output:      
Return: 
Nites:  
.................................................................................
Modification History:
 <No.> <version>      <time>         <author>      <contents>
 2、
 1、   
********************************************************************************/
U8 m_Memory_WriteData(U32 ulAddr, U8 *pucData, U32 ulLen)
{
    U8 ucMemType;
    U8 ucRtnValue;

    ucRtnValue = true;
    ucMemType = (U8)((ulAddr & 0xff000000) >> 24);
    switch(ucMemType)
    {
        case E_CHIP_FLASH:
        case E_CHIP_EEPROM:
        {
            
        }break;
        case E_CHIP_RAM:
        {
            memcpy((U8 *)ulAddr, pucData, ulLen);
        }break;
        case E_FRAM:
        case E_COG_LCD:
        case E_EEPROM:
        case E_EXT_RTC:
        {
            I2C_writeData(0xa0, (U16)ulAddr, pucData, ulLen);
        }break;
        case E_DATAFLASH:
        {
            Flash_write(ulAddr, pucData, ulLen);
        }break;
        case E_OTHER_CHIP:
        {
            
        }break;
        default:
        {
            ucRtnValue = false;
        }break;
    }

    return (ucRtnValue);
} 

