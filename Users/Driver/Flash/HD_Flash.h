/****************************************************************
Description: HD_FLASH.h
Author: shijj
Notes: data flash ����ͷ�ļ�
*****************************************************************/
#ifndef __HD_FLASH_H
#define __HD_FLASH_H
/*- 1.Macro-----------------------------------------------------*/
#define DF_SECTOR_SIZE 4096
#define DF_PAGE_SIZE   256

/*Flash ��������*/
#define DF_CMD_WREN       0x06     //дʹ��
#define DF_CMD_WRDI       0x04     //д��ֹ
#define DF_CMD_RDID       0x9F     //��оƬID
#define DF_CMD_RDSR       0x05     //��״̬�Ĵ���
#define DF_CMD_READ       0x03     //������
#define DF_CMD_FAST_READ  0x0B     //���ٶ�����
#define DF_CMD_PW         0x0A     //ҳд
#define DF_CMD_PP         0x02     //ҳ���
#define DF_CMD_PE         0xDB     //ҳ����
#define DF_CMD_SCE        0x20     //��������
#define DF_CMD_DP         0xB9     //����ģʽ
#define DF_CMD_RDP        0xAB     //����ģʽ����


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
