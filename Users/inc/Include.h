#ifndef __INCLUDE_H
#define __INCLUDE_H

#define DEBUG 0 //调试模式, 置1后开启堆栈监控,assert


#if DEBUG

#else
    #define  ASSERT_NDEBUG
#endif


typedef        unsigned char         BOOL;
typedef        signed char           S8;
typedef        unsigned char         U8;
typedef        short                 S16;
typedef        unsigned short        U16;
typedef        int                   S32;
typedef        unsigned int          U32;
typedef        unsigned long long    U64;
typedef        signed long long      S64;
typedef        float                 F32;


//typedef        S8       int8_t;
//typedef        U8       uint8_t;
//typedef        S16      int16_t;
//typedef        U16      uint16_t;
//typedef        S32      int32_t;
//typedef        U32      uint32_t;
//typedef        U64      uint64_t;
//typedef        S64      int64_t;

//AT指令错误码
typedef enum
{
    E_SUCCESS       = 0x00,
    E_SEND_FAIL     = 0x01,
    E_TIMEOUT       = 0x02, //发送回复 send ok 接收超时
    E_DISCONNECT    = 0x03,
    E_LEN_ERR       = 0x04,
    E_NO_MEM        = 0x05, //内存不足
    E_TRY_AGAIN     = 0x06, //资源暂时不可用
    E_CMD_INVALID   = 0x07, // +CME ERROR:invalid command line  GPRS IO时 会出现
    E_FTP_OPEN_FAIL = 0x08,
    E_FTP_GET_FAIL  = 0x09,
    E_FILE_CHK_ERR  = 0x0A,
    E_OVERFLOW      = 0x0B,
    E_UNKOWN_ERR    = 0xFF,
}ErrCode_t;


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "ht6xxx_lib.h"
#include "HD_System.h"
#include "ht6xxx.h"
#include "conf.h"
#include "main.h"
#include "HD_GPIO.h"
#include "HD_UART.h"
#include "HD_EEPROM.h"
#include "AL_main.h"
#include "MM_UAL.h"
#include "HD_Flash.h"
#include "flash_map.h"
#include "ota.h"
#include "v_stdio.h"
#include "m_Memory_V1.0.h"
#include "EEPROM_map.h"

#define    _TRUE        1
#define    _FALSE       0

#ifndef    _false
#define    _false        0
#endif

#ifndef    _true
#define    _true         1
#endif

#ifndef    true
#define    true       _true
#endif

#ifndef    false
#define    false      _false
#endif

#ifndef    _Enable
#define    _Enable      1
#endif

#ifndef    _Disable     
#define    _Disable     0
#endif

#ifndef    FALSE
#define    FALSE        0
#endif

#ifndef    TRUE
#define    TRUE         1
#endif

#ifndef PNULL
#define PNULL           (void *)0

#define HD_clrWDT()             {HT_FreeDog();}

#endif



#endif
