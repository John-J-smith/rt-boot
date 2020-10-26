/**
  ******************************************************************************
  * @file    common.h
  * @author  Application Team
  * @version V4.3.0
  * @date    2018-09-04
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#ifndef __COMMON_H
#define __COMMON_H


#include "stdio.h"
#include "string.h"
#include "include.h"

typedef void (*pFunction)(void);

#define FLASH_SERASE_KEY   0xAA5555AA
#define CMD_STRING_SIZE    128
#define ISR_HAND_OFFSET    0x00000004
#define BootIsrAddress     0x00000004
#define PAGE_SIZE         (0x400)    /* 1024 byte */
#define ROM_PAGE_SIZE     (0x100)    /* 256 byte */
#define FLASH_SIZE        (0x80000UL)

//The size of file
#define FLASH_IMAGE_SIZE (uint32_t) (FLASH_SIZE - (ApplicationAddress - 0x0000000))

#define IS_AF(c)  ((c >= 'A') && (c <= 'F'))
#define IS_af(c)  ((c >= 'a') && (c <= 'f'))
#define IS_09(c)  ((c >= '0') && (c <= '9'))
#define ISVALIDHEX(c)  IS_AF(c) || IS_af(c) || IS_09(c)
#define ISVALIDDEC(c)  IS_09(c)
#define CONVERTDEC(c)  (c - '0')

#define CONVERTHEX_alpha(c)  (IS_AF(c) ? (c - 'A'+10) : (c - 'a'+10))
#define CONVERTHEX(c)   (IS_09(c) ? (c - '0') : CONVERTHEX_alpha(c))

#if 0
#define SerialPutString(x) Serial_PutString((uint8_t*)(x))
#else
#define SerialPutString(x)
#endif

void Int2Str(uint8_t* str,int32_t intnum);
uint32_t Str2Int(uint8_t *inputstr,int32_t *intnum);
uint32_t FLASH_PagesMask(volatile uint32_t Size);
void FLASH_DisableWriteProtectionPages(void);
void FLASH_SectorEraseUnderUnlock(uint32_t SectorAddr);
void FLASH_ProgramOneWord(uint32_t Addr, uint32_t Word);
void FLASH_Unlock(void);
void FLASH_Lock(void);

#endif  /* __COMMON_H */

