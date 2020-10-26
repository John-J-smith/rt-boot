/****************************************************************
Description: FTP.h
Author: shijj
Notes: FTP_OTA头文件
*****************************************************************/
#ifndef _OTA_H_
#define _OTA_H_

#include "include.h"


/*- 1.Macro-----------------------------------------------------*/

//升级标志
#define FOTA_IDLE               (0xFFFFFFFF)
#define FOTA_DOWNLOAD_COMPLETE  (0x01010101)
#define FOTA_START_INSTALL      (0x55AAAA55)
#define FOTA_SUCCESS            (0x00000000)
#define FOTA_FAILED             (0x11223344)

#define FOTA_JUMP_TO_BS             (0xC33CC33C)
#define FOTA_BS_CHK_BAG_ERR         (0x55555555)
#define FOTA_BS_CHK_OLD_ERR         (0x66666666)
#define FOTA_BS_COPY_ERR            (0x77777777)
#define FOTA_BS_DECOMPRESS_ERR      (0x88888888)
#define FOTA_BS_DECOMPRESS_CHK_ERR  (0x99999999)
#define FOTA_BS_CHK_NEW_ERR         (0xAAAAAAAA)


/*- 3.Public variable-------------------------------------------*/



/*- 4.Public function-------------------------------------------*/
#ifndef _OTA_C_
    #define __GLOBAL  extern
#else
    #define __GLOBAL
#endif

__GLOBAL    BOOL    Boot_getFotaFlg(void);
__GLOBAL    BOOL    Boot_UpdateFirmware(void);
__GLOBAL    U8      Boot_CheckFirmware(void);


#undef __GLOBAL

/*- 5.End-------------------------------------------------------*/

#endif


