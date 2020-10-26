#ifndef _FLASH_MAP_H_
#define _FLASH_MAP_H_

#include "HD_Flash.h"

#define ADDR_FLASH_START                    ((U32)0x03000000 + DF_PAGE_SIZE * 0)

/********************************************************************************
|                              DATA FLASH self test                             |
********************************************************************************/
#define ADDR_FLASH_SELF_TEST                (ADDR_FLASH_START + DF_SECTOR_SIZE * 000)

/********************************************************************************
|                              firmware 1                                       |
********************************************************************************/
#define ADDR_FIRMWARE_NEW_START             (ADDR_FLASH_START + DF_SECTOR_SIZE * 001)
#define ADDR_FIRMWARE_NEW_END               (ADDR_FLASH_START + DF_SECTOR_SIZE * 113) //固件大小最大448KB

/********************************************************************************
|                                for BS                                         |
********************************************************************************/
#define BS_BAG_START_ADDR                   (ADDR_FLASH_START + DF_SECTOR_SIZE * 113)
#define BS_BAG_END_ADDR                     (ADDR_FLASH_START + DF_SECTOR_SIZE * 130) //68kB
#define BS_BAG_SIZE                         (BS_BAG_END_ADDR - BS_BAG_START_ADDR)

#define BS_PATCH_START_ADDR                 (ADDR_FLASH_START + DF_SECTOR_SIZE * 130)
#define BS_PATCH_END_ADDR                   (ADDR_FLASH_START + DF_SECTOR_SIZE * 252) //488KB

#define BS_OLDIMAGE_ADDR                    APP_ROM_START/*chenj-fw. 直接从ROM中读取，不再拷贝*/
#define BS_NEWIMAGE_ADDR                    ADDR_FIRMWARE_NEW_START

/********************************************************************************
|                              module firmware                                  |
*********************************************************************************/
#define ADDR_MODEM_FIRMWARE_START           ADDR_FIRMWARE_NEW_START /*与模块升级共用*/
#define ADDR_MODEM_FIRMWARE_END             (ADDR_FLASH_START + DF_SECTOR_SIZE * 252) //共1004KB


/*以下共占用1040KB*/
/********************************************************************************
|                             Load profile record                               |
*********************************************************************************/
#define ADDR_LP_READ_BUFF_START             (ADDR_FLASH_START + DF_SECTOR_SIZE * 252)
#define ADDR_LP_READ_BUFF_END               (ADDR_LP_READ_BUFF_START + DF_SECTOR_SIZE * 190)

/********************************************************************************
|                             Month record                                      |
*********************************************************************************/
#define ADDR_Month_Read_Buff_Start          (ADDR_FLASH_START + DF_SECTOR_SIZE * 442)
#define ADDR_Month_Read_Buff_End            (ADDR_Month_Read_Buff_Start + DF_SECTOR_SIZE * 10)

/********************************************************************************
|                             daily record                                      |
*********************************************************************************/
#define ADDR_Daily_Read_Buff_Start          (ADDR_FLASH_START + DF_SECTOR_SIZE * 452)
#define ADDR_Daily_Read_Buff_End            (ADDR_Daily_Read_Buff_Start + DF_SECTOR_SIZE * 10)

#define ADDR_Daily_Read_Buff_Tmp_Start      (ADDR_FLASH_START + DF_SECTOR_SIZE * 462)
#define ADDR_Daily_Read_Buff_Tmp_End        (ADDR_Daily_Read_Buff_Tmp_Start + DF_SECTOR_SIZE * 5)

#define ADDR_MAX_DMD_Read_Buff_Tmp_Start    (ADDR_FLASH_START + DF_SECTOR_SIZE * 467)
#define ADDR_MAX_DMD_Read_Buff_Tmp_End      (ADDR_MAX_DMD_Read_Buff_Tmp_Start + DF_SECTOR_SIZE * 5)

/********************************************************************************
|                             maximum demand record                             |
*********************************************************************************/
#define ADDR_MAX_DMD_Read_Buff_Start        (ADDR_FLASH_START + DF_SECTOR_SIZE * 472)
#define ADDR_MAX_DMD_Read_Buff_End          (ADDR_MAX_DMD_Read_Buff_Start + DF_SECTOR_SIZE * 10)

#define ADDR_Month_Read_Buff_Tmp_Start      (ADDR_FLASH_START + DF_SECTOR_SIZE * 482)
#define ADDR_Month_Read_Buff_Tmp_End        (ADDR_Month_Read_Buff_Tmp_Start + DF_SECTOR_SIZE * 10)

/********************************************************************************
|                             cum maximum demand record                         |
*********************************************************************************/
#define ADDR_CUM_MAX_DMD_Read_Buff_Start    (ADDR_FLASH_START + DF_SECTOR_SIZE * 492)
#define ADDR_CUM_MAX_DMD_Read_Buff_End      (ADDR_CUM_MAX_DMD_Read_Buff_Start + DF_SECTOR_SIZE * 10)

#define ADDR_CUM_MAX_DMD_Read_Buff_Tmp_Start (ADDR_FLASH_START + DF_SECTOR_SIZE * 502)
#define ADDR_CUM_MAX_DMD_Read_Buff_Tmp_End  (ADDR_CUM_MAX_DMD_Read_Buff_Tmp_Start + DF_SECTOR_SIZE * 5)


#endif
