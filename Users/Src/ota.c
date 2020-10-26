/****************************************************************
Description: ota.c
Author: shijj
Notes:
*****************************************************************/
#define _OTA_C_
/*- 1.Include---------------------------------------------------*/
#include "ota.h"
#include "common.h"
#include "easyflash.h"
#include "fal.h"

#define BUFF_SIZE 512
/*- 2.Private variable------------------------------------------*/

/*- 3.Public variable-------------------------------------------*/
extern void AL_PowerDown_Dtc(void);

/*- 4.Private function------------------------------------------*/

BOOL Boot_getFotaFlg(void)
{
    char flag = 0xff;

    ef_get_env_blob("iap_need_copy_app", &flag, 1, NULL);
    if(flag == '1')
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

U8 Boot_CheckFirmware(void)
{
#define download_partition_name "download"
    U8 gucTempRxData[BUFF_SIZE];
    const struct fal_partition *part = NULL;
    char flen_buf[32];
    U32 flen = 0;
    U32 ulAddr = 0;
    U16 crc16 = 0;
    U16 usExpectCrc16 = 0;

    if(ef_get_env_blob("iap_copy_app_size", flen_buf, sizeof(flen_buf), NULL) > 0)
    {
        sscanf(flen_buf, "%u", &flen);
    }

    part = fal_partition_find(download_partition_name);
    if (part == NULL)
    {
        LOG("download partition not foundr\n");
        return FALSE;
    }

    if(flen == 0 || flen > part->len)
    {
        LOG("flen err %u\r\n", flen);
        return FALSE;
    }

    // 计算外部flash的固件CRC校验
    for(U32 i = 0; i < (flen / BUFF_SIZE); i++)
    {
        IO_LED_RUN_TOGG;
        IO_LED_TX_TOGG;
        IO_LED_RX_TOGG;
        AL_PowerDown_Dtc();
        HD_clrWDT();
        fal_partition_read(part, ulAddr, gucTempRxData, BUFF_SIZE);
        if(i == (flen / BUFF_SIZE) - 1)
        {
            memcpy((U8 *)&usExpectCrc16, gucTempRxData + BUFF_SIZE - 2, 2);
            crc16 = MM_calcCRC(gucTempRxData, BUFF_SIZE - 2, crc16);
        }
        else
        {
            crc16 = MM_calcCRC(gucTempRxData, BUFF_SIZE, crc16);
        }
        ulAddr += BUFF_SIZE;
    }
    // 比较CRC
    if(usExpectCrc16 != crc16)
    {
        ef_set_env("iap_sta", "crc_err");
        return FALSE;
    }

    return TRUE;
}

BOOL Boot_UpdateFirmware(void)
{
#define download_partition_name "download"
#define app_partition_name      "app"
    U8 gucTempRxData[BUFF_SIZE];
    const struct fal_partition *download_part = NULL;
    const struct fal_partition *app_part = NULL;
    char flen_buf[32];
    U32 flen = 0;
    U32 offset = 0;

    if(ef_get_env_blob("iap_copy_app_size", flen_buf, sizeof(flen_buf), NULL) > 0)
    {
        sscanf(flen_buf, "%u", &flen);
    }

    download_part = fal_partition_find(download_partition_name);
    if (download_part == NULL)
    {
        LOG("download partition not foundr\n");
        return FALSE;
    }

    app_part = fal_partition_find(app_partition_name);
    if (app_part == NULL)
    {
        LOG("app partition not foundr\n");
        return FALSE;
    }

    if(flen == 0 || flen > app_part->len)
    {
        LOG("flen > app size\r\n");
        return FALSE;
    }

    fal_partition_erase_all(app_part);

    for ( U32 i = 0; i < ( flen / BUFF_SIZE ); i++ )
    {
        IO_LED_RUN_TOGG;
        IO_LED_TX_TOGG;
        IO_LED_RX_TOGG;
        HD_clrWDT();
        AL_PowerDown_Dtc();
        fal_partition_read(download_part, offset, gucTempRxData, BUFF_SIZE);
        fal_partition_write(app_part, offset, gucTempRxData, BUFF_SIZE);
        offset += BUFF_SIZE;
    }
	//Memory_WriteData(ADDR_OLDIMAGE_SIZE, (U8 *)&ulNewimageSize, 4);/*write the size of image*/
    ef_set_env("iap_sta", "success");

    return TRUE;
}

/*- 5.public functions------------------------------------------*/


/*- 6.End-------------------------------------------------------*/



