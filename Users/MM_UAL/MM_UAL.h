#ifndef _MM_UAL_H_
#define _MM_UAL_H_

#include "include.h"

#define MIN(a, b)                       (((a) < (b))? (a) : (b))
#define MAX(a, b)                       (((a) > (b))? (a) : (b))
#define DIV_CEIL(x, y)                  (((x) + (y) - 1) / (y))


/*������ʼ��*******************/
#ifndef _MM_UAL_C_
    #define __GLOBAL  extern
#else
    #define __GLOBAL  
#endif

/* ��ת�ַ���	*/
__GLOBAL void   MM_StrReverse(void *pVoidBuf, U16 uslen);
/* ����У��� */
__GLOBAL U8     MM_ChkSum(U8 * pucBuff, U16 usLen);
__GLOBAL U16    MM_ChkSum_16(U8 * pucBuff, U16 usLen);

/* �ַ����Ƚ� */
__GLOBAL U8     MM_MemCmp(U8 *pucSrc, U8 *pucDst, U8 ucLen);
/* 16����תascii */
__GLOBAL BOOL   MM_Hex2Ascii(U8 * src, U8 *dst, U16 ucLen);
/* asciiת16���� */
__GLOBAL BOOL 	MM_Ascii2Hex(U8 * src, U8 * dst, U16 ucLen);
/* �ж��Ƿ��ǿɼ��ַ� */
__GLOBAL BOOL 	MM_isVisibleChar(U8 character);
/* �ж��Ƿ��ǿɼ��ַ��� */
__GLOBAL BOOL 	MM_isVisibleString(U8 * str, U8 len);
/* �ж��Ƿ��������ַ��� */
__GLOBAL BOOL 	MM_isNumString(U8 * str, U8 len);
/* ����int��ƽ��ֵ */
__GLOBAL int    MM_getAvg(int * str, U8 cnt);
/* У��CRC16У�� */
__GLOBAL U16    MM_calcCRC( U8* ucBuf, U16 uilen, U16 uiCrc );
__GLOBAL U16    MODBUS_crc16(U8 *pucMsg, U16 usDataLen, U16 crc);
__GLOBAL U16    MODBUS_calcCycleCRC(U8 *pucBuff, U16 usLen);
/* ���������ݳ��� */
__GLOBAL int    MM_getNumLen(int num);


#undef __GLOBAL

#endif
