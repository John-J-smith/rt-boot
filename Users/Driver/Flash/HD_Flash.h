/****************************************************************
Description: HD_FLASH.h
Author: shijj
Notes: data flash 驱动头文件
*****************************************************************/
#ifndef __HD_FLASH_H
#define __HD_FLASH_H
/*- 1.Macro-----------------------------------------------------*/
#define DF_SECTOR_SIZE 4096
#define DF_PAGE_SIZE   256

/*Flash 操作命令*/
#define DF_CMD_WREN       0x06     //写使能
#define DF_CMD_WRDI       0x04     //写禁止
#define DF_CMD_RDID       0x9F     //读芯片ID
#define DF_CMD_RDSR       0x05     //读状态寄存器
#define DF_CMD_READ       0x03     //读数据
#define DF_CMD_FAST_READ  0x0B     //快速读数据
#define DF_CMD_PW         0x0A     //页写
#define DF_CMD_PP         0x02     //页编程
#define DF_CMD_PE         0xDB     //页擦除
#define DF_CMD_SCE        0x20     //扇区擦除
#define DF_CMD_DP         0xB9     //掉电模式
#define DF_CMD_RDP        0xAB     //掉电模式换醒


/*- 2.Type prototype--------------------------------------------*/

/*- 3.Public variable-------------------------------------------*/


/*- 4.Public function-------------------------------------------*/
#ifndef __HD_FLASH_C__
    #define __GLOBAL  extern
#else
    #define __GLOBAL
#endif

__GLOBAL    void        HD_Flash_Init(void);
__GLOBAL    ErrCode_t   Flash_read(U32 addr, U8 *pucBuf, U16 size);
__GLOBAL    ErrCode_t   Flash_write(U32 addr, U8 *pucBuf, U16 size);

#undef __GLOBAL  

/*- 5.End-------------------------------------------------------*/

#endif
