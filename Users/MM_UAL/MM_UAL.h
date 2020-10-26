#ifndef _MM_UAL_H_
#define _MM_UAL_H_

#include "include.h"

#define MIN(a, b)                       (((a) < (b))? (a) : (b))
#define MAX(a, b)                       (((a) > (b))? (a) : (b))
#define DIV_CEIL(x, y)                  (((x) + (y) - 1) / (y))


/*函数初始化*******************/
#ifndef _MM_UAL_C_
    #define __GLOBAL  extern
#else
    #define __GLOBAL  
#endif

/* 翻转字符串	*/
__GLOBAL void   MM_StrReverse(void *pVoidBuf, U16 uslen);
/* 计算校验和 */
__GLOBAL U8     MM_ChkSum(U8 * pucBuff, U16 usLen);
__GLOBAL U16    MM_ChkSum_16(U8 * pucBuff, U16 usLen);

/* 字符串比较 */
__GLOBAL U8     MM_MemCmp(U8 *pucSrc, U8 *pucDst, U8 ucLen);
/* 16进制转ascii */
__GLOBAL BOOL   MM_Hex2Ascii(U8 * src, U8 *dst, U16 ucLen);
/* ascii转16进制 */
__GLOBAL BOOL 	MM_Ascii2Hex(U8 * src, U8 * dst, U16 ucLen);
/* 判断是否是可见字符 */
__GLOBAL BOOL 	MM_isVisibleChar(U8 character);
/* 判断是否是可见字符串 */
__GLOBAL BOOL 	MM_isVisibleString(U8 * str, U8 len);
/* 判断是否是数字字符串 */
__GLOBAL BOOL 	MM_isNumString(U8 * str, U8 len);
/* 计算int型平均值 */
__GLOBAL int    MM_getAvg(int * str, U8 cnt);
/* 校验CRC16校验 */
__GLOBAL U16    MM_calcCRC( U8* ucBuf, U16 uilen, U16 uiCrc );
__GLOBAL U16    MODBUS_crc16(U8 *pucMsg, U16 usDataLen, U16 crc);
__GLOBAL U16    MODBUS_calcCycleCRC(U8 *pucBuff, U16 usLen);
/* 求整型数据长度 */
__GLOBAL int    MM_getNumLen(int num);


#undef __GLOBAL

#endif
