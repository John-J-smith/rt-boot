/******************************************************************************
 Copyright (C) Aug.2,2004  R&D Institute of Reallin Co., Ltd.
 Module         : 通用模块
 Description    : 
 Build Date     : 
 others         : 
 ------------------------------------------------------------------------------
 Modification History:
 <No.> <version >  <time>        <author>     <contents> 
  1.    1.00     2018-07-17		shijj			create
******************************************************************************/

#define _MM_UAL_C_
#include "MM_UAL.h"
/*******************************************************************************
@ Function Name  : U8 MM_StrReverse(U8 * src, U16 ucLen)
@ Description    : 
@ Input          : None.
@ Return         : None.
@ History		 : 
<No.>	<version >	<time>			<author>     <contents> 
1.		1.0			2017-12-07		shijj		 create
*******************************************************************************/
void MM_StrReverse(void *pVoidBuf, U16 uslen)
{
    U8 ucData;
    U8 *pucBuf;
    
    pucBuf = (U8*)pVoidBuf + uslen;
    uslen >>= 1;
    while (uslen--)
    {
        pucBuf   = pucBuf - 1;
        ucData   = *(pucBuf);
        *pucBuf  = *(U8*)pVoidBuf;
        *(U8*)pVoidBuf = ucData;
        pVoidBuf = (U8*)pVoidBuf + 1;
    }
}
/*******************************************************************************
@ Function Name  : U8 MM_ChkSum(U8 * pucSntBuff, U16 usLen)
@ Description    : 计算校验和
@ Input          : 
@ Return         : 帧长度
@ History		 : 
<No.>	<version >	<time>			<author>     <contents> 
1.		1.0			2018-03-08		shijj		create
*******************************************************************************/
U8 MM_ChkSum(U8 * pucBuff, U16 usLen)
{
    U8  ucChkSum = 0;
    
    for(U16 i = 0; i < usLen; i++)
    {
        ucChkSum += pucBuff[i];
    }
    
    return ucChkSum;
}
/*******************************************************************************
@ Function Name  : U16 MM_ChkSum_16(U8 * pucSntBuff, U16 usLen)
@ Description    : 计算校验和
@ Input          : 
@ Return         : 帧长度
@ History		 : 
<No.>	<version >	<time>			<author>     <contents> 
1.		1.0			2018-03-08		shijj		create
*******************************************************************************/
U16 MM_ChkSum_16(U8 * pucBuff, U16 usLen)
{
    U16  usChkSum = 0;
    
    for(U16 i = 0; i < usLen; i++)
    {
        usChkSum += pucBuff[i];
    }
    
    return usChkSum;
}

/*******************************************************************************
* Function Name  : U8 MM_MemCmp(U8 *pucSrc, U8 *pucDst, U8 ucLen)
* Description    : 字符串比较
* Input          : None.
* Return         : 相同返回TRUE
* History		 : 
<No.>	<version >	<time>			<author>     <contents> 
1.		1.0			2018-03-08		shijj		create
*******************************************************************************/
U8 MM_MemCmp(U8 *pucSrc, U8 *pucDst, U8 ucLen)
{
	if(pucSrc == NULL || pucDst == NULL || ucLen == 0)
	{
		return FALSE;
	}
    for(U8 i = 0; i < ucLen; i++)
    {
        if(pucSrc[i] != pucDst[i])
        {
            return FALSE;
        }
    }
    return TRUE;
}
/*******************************************************************************
* Function Name  : U8 MM_MemCpy(U8 *pucSrc, U8 *pucDst, U16 ucLen)
* Description    : 内存拷贝
* Input          : None.
* Return         : 
* History		 : 
<No.>	<version >	<time>			<author>     <contents> 
1.		1.0			2018-03-08		shijj		create
*******************************************************************************/
U8 MM_MemCpy(U8 *pucSrc, U8 *pucDst, U16 ucLen)
{
    if(ucLen == 0)
    {
        return FALSE;
    }
    for(U16 i = 0; i < ucLen; i++)
    {
        pucDst[i] = pucSrc[i];
    }
    return TRUE;
}
/*******************************************************************************
* Description    : 16进制转ascii码, 0xAA-->'A','A'
* Input          : hex, ascii, hex的长度
* Return         : 2n字节ascii码
* History		 : 
<No.>	<version >	<time>			<author>     <contents> 
1.		1.0			2018-03-08		shijj		create
*******************************************************************************/
BOOL MM_Hex2Ascii(U8 * src, U8 * dst, U16 ucLen)
{
    if(0 == ucLen)
    {
        return FALSE;
    }
    for(U16 i = 0; i < ucLen; i++)
    {
        if((src[i] & 0x0F) < 10)
        {
            dst[2*i+1] = (src[i] & 0x0F) + '0'; 
        }
        else
        {
            dst[2*i+1] = (src[i] & 0x0F) + 'A' - 10;
        }

        if(((src[i] & 0xF0) >> 4) < 10)
        {
            dst[2*i] = ((src[i] & 0xF0) >> 4) + '0'; 
        }
        else
        {
            dst[2*i] = ((src[i] & 0xF0) >> 4) + 'A' - 10;
        }
    }
    return TRUE;
}
/*******************************************************************************
* Description    : 16进制ascii码转16进制,'A','A'->0xAA
* Input          : ascii, hex, hex的len,
* Return         : len字节hex码
* History		 : 
<No.>	<version >	<time>			<author>     <contents> 
1.		1.0			2018-09-19		shijj		create
*******************************************************************************/
BOOL MM_Ascii2Hex(U8 * src, U8 * dst, U16 ucLen)
{
	//U8 ucDst_Bk[20];
	//memcpy(ucDst_Bk, dst, ucLen);
    if(0 == ucLen)
    {
        return FALSE;
    }
    for(U16 i = 0; i < ucLen; i++)
    {
        if(src[2*i] >= '0' && src[2*i] <= '9')
		{
			src[2*i] -= '0';
		}
		else if(src[2*i] >= 'a' && src[2*i] <= 'f')
		{
			src[2*i] -= ('a'-10);
		}
		else if(src[2*i] >= 'A' && src[2*i] <= 'F')
		{
			src[2*i] -= ('A'-10);
		}
		
		if(src[2*i+1] >= '0' && src[2*i+1] <= '9')
		{
			src[2*i+1] -= '0';
		}
		else if(src[2*i+1] >= 'a' && src[2*i+1] <= 'f')
		{
			src[2*i+1] -= ('a'-10);
		}
		else if(src[2*i+1] >= 'A' && src[2*i+1] <= 'F')
		{
			src[2*i+1] -= ('A'-10);
		}
		else
		{
			//memcpy(dst, ucDst_Bk, ucLen);//失败则恢复数据
			return FALSE;
		}
		dst[i] = (src[2*i] << 4) | src[2*i+1];
    }
    return TRUE;
}
/*******************************************************************************
* Function Name  : BOOL MM_isVisibleChar(U8 character)
* Description    : 判断是否是可见字符
* Input          : character
* Return         : true / false
* History		 : 
<No.>	<version >	<time>			<author>     <contents> 
1.		1.0			2018-10-24		shijj		create
*******************************************************************************/
BOOL MM_isVisibleChar(U8 character)
{
	/*
	if(character >= 'a' && character <= 'z')
	{
		return TRUE;
	}
	else if(character >= 'A' && character <= 'Z')
	{
		return TRUE;
	}
	else if(character >= '0' && character <= '9')
	{
		return TRUE;
	}
	*/
	if((character >= ' ') && (character <= '~'))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/*******************************************************************************
* Function Name  : BOOL MM_isVisibleString(U8 * str, U8 len)
* Description    : 判断是否是可见字符串
* Input          : str[in]， len[in]
* Return         : true / false
* History		 : 
<No.>	<version >	<time>			<author>     <contents> 
1.		1.0			2018-11-12		shijj		create
*******************************************************************************/
BOOL MM_isVisibleString(U8 * str, U8 len)
{
	for(U8 i = 0; i < len; i++)
	{
		if(FALSE == MM_isVisibleChar(str[i]))
		{
			return FALSE;
		}
	}

	return TRUE;
}
/*******************************************************************************
* Function Name  : BOOL MM_isNumString(U8 * str, U8 len)
* Description    : 判断是否是可见数字字符串
* Input          : str[in]， len[in]
* Return         : true / false
* History		 : 
<No.>	<version >	<time>			<author>     <contents> 
1.		1.0			2018-11-19		shijj		create
*******************************************************************************/
BOOL MM_isNumString(U8 * str, U8 len)
{
	for(U8 i = 0; i < len; i++)
	{
		if((str[i] < '0') || (str[i] > '9'))
		{
			return FALSE;
		}
	}

	return TRUE;
}
/*******************************************************************************
* Description    : 计算平均值
* Input          : str[in]， cnt[in]
* Return         : average
* History		 : 
<No.>	<version >	<time>			<author>     <contents> 
1.		1.0			2019-03-25		shijj		create
*******************************************************************************/
int MM_getAvg(int * str, U8 cnt)
{
    int sum = 0;
    
	for(U8 i = 0; i < cnt; i++)
	{
		sum += str[i];
	}

	return (sum / cnt);
}
/******************************************************************************
 Description  : 初始化固件校验
 ..............................................................................
 Modification History:                                                         
 <No.> <version >  <time>        <author>     <contents>                       
  2、    
  1、    1.00     2011-11-23    liu shun     build this moudle                
 *****************************************************************************/
//CRC table
const U16 dlms_FCSTAB[256] = 
{
    0x0000, 0x1189, 0x2312, 0x329B, 0x4624, 0x57AD, 0x6536, 0x74BF,
    0x8C48, 0x9DC1, 0xAF5A, 0xBED3, 0xCA6C, 0xDBE5, 0xE97E, 0xF8F7,
    0x1081, 0x0108, 0x3393, 0x221A, 0x56A5, 0x472C, 0x75B7, 0x643E,
    0x9CC9, 0x8D40, 0xBFDB, 0xAE52, 0xDAED, 0xCB64, 0xF9FF, 0xE876,
    0x2102, 0x308B, 0x0210, 0x1399, 0x6726, 0x76AF, 0x4434, 0x55BD,
    0xAD4A, 0xBCC3, 0x8E58, 0x9FD1, 0xEB6E, 0xFAE7, 0xC87C, 0xD9F5,
    0x3183, 0x200A, 0x1291, 0x0318, 0x77A7, 0x662E, 0x54B5, 0x453C,
    0xBDCB, 0xAC42, 0x9ED9, 0x8F50, 0xFBEF, 0xEA66, 0xD8FD, 0xC974,
    0x4204, 0x538D, 0x6116, 0x709F, 0x0420, 0x15A9, 0x2732, 0x36BB,
    0xCE4C, 0xDFC5, 0xED5E, 0xFCD7, 0x8868, 0x99E1, 0xAB7A, 0xBAF3,
    0x5285, 0x430C, 0x7197, 0x601E, 0x14A1, 0x0528, 0x37B3, 0x263A,
    0xDECD, 0xCF44, 0xFDDF, 0xEC56, 0x98E9, 0x8960, 0xBBFB, 0xAA72,
    0x6306, 0x728F, 0x4014, 0x519D, 0x2522, 0x34AB, 0x0630, 0x17B9,
    0xEF4E, 0xFEC7, 0xCC5C, 0xDDD5, 0xA96A, 0xB8E3, 0x8A78, 0x9BF1,
    0x7387, 0x620E, 0x5095, 0x411C, 0x35A3, 0x242A, 0x16B1, 0x0738,
    0xFFCF, 0xEE46, 0xDCDD, 0xCD54, 0xB9EB, 0xA862, 0x9AF9, 0x8B70,
    0x8408, 0x9581, 0xA71A, 0xB693, 0xC22C, 0xD3A5, 0xE13E, 0xF0B7,
    0x0840, 0x19C9, 0x2B52, 0x3ADB, 0x4E64, 0x5FED, 0x6D76, 0x7CFF,
    0x9489, 0x8500, 0xB79B, 0xA612, 0xD2AD, 0xC324, 0xF1BF, 0xE036,
    0x18C1, 0x0948, 0x3BD3, 0x2A5A, 0x5EE5, 0x4F6C, 0x7DF7, 0x6C7E,
    0xA50A, 0xB483, 0x8618, 0x9791, 0xE32E, 0xF2A7, 0xC03C, 0xD1B5,
    0x2942, 0x38CB, 0x0A50, 0x1BD9, 0x6F66, 0x7EEF, 0x4C74, 0x5DFD,
    0xB58B, 0xA402, 0x9699, 0x8710, 0xF3AF, 0xE226, 0xD0BD, 0xC134,
    0x39C3, 0x284A, 0x1AD1, 0x0B58, 0x7FE7, 0x6E6E, 0x5CF5, 0x4D7C,
    0xC60C, 0xD785, 0xE51E, 0xF497, 0x8028, 0x91A1, 0xA33A, 0xB2B3,
    0x4A44, 0x5BCD, 0x6956, 0x78DF, 0x0C60, 0x1DE9, 0x2F72, 0x3EFB,
    0xD68D, 0xC704, 0xF59F, 0xE416, 0x90A9, 0x8120, 0xB3BB, 0xA232,
    0x5AC5, 0x4B4C, 0x79D7, 0x685E, 0x1CE1, 0x0D68, 0x3FF3, 0x2E7A,
    0xE70E, 0xF687, 0xC41C, 0xD595, 0xA12A, 0xB0A3, 0x8238, 0x93B1,
    0x6B46, 0x7ACF, 0x4854, 0x59DD, 0x2D62, 0x3CEB, 0x0E70, 0x1FF9,
    0xF78F, 0xE606, 0xD49D, 0xC514, 0xB1AB, 0xA022, 0x92B9, 0x8330,
    0x7BC7, 0x6A4E, 0x58D5, 0x495C, 0x3DE3, 0x2C6A, 0x1EF1, 0x0F78
};

U16 MM_calcCRC( U8* ucBuf, U16 uilen, U16 uiCrc )
{
    uiCrc ^= 0xffff;
    while( uilen-- )
    {
        uiCrc = (uiCrc >> 8) ^ dlms_FCSTAB[(uiCrc ^ *ucBuf++) & 0xff];
    }
    uiCrc ^= 0xffff;
    return( uiCrc );
}


/* CRC 高位字节值表 */ 
const unsigned char auchCRCHi[] = { 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40 
};

/* CRC低位字节值表*/ 
const unsigned char auchCRCLo[] = { 
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 
0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 
0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 
0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 
0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 
0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 
0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 
0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 
0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 
0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 
0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 
0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 
0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 
0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 
0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 
0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 
0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C, 
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 
0x43, 0x83, 0x41, 0x81, 0x80, 0x40 
};

/****************************************************************************
Description  : MODBUS CRC校验
Others          : MODBUS通讯组帧时调用
...............................................................................
...........................................................................
Modification History:                                                                                                             
<No.> <version >  <time>                <author>         <contents>                                       
2、    
1、    1.00     2012-11-11         zhangll         build this moudle                            
*****************************************************************************/
U16 MODBUS_crc16(U8 *pucMsg, U16 usDataLen, U16 crc) 
{ 
    //U8 ucCRCHi = 0xFF; /* 高CRC字节初始化 */ 
    //U8 ucCRCLo = 0xFF; /* 低CRC 字节初始化 */ 
    U8 ucCRCHi = (crc >> 8) & 0xFF; /* 高CRC字节初始化 */ 
    U8 ucCRCLo = (crc & 0xFF); /* 低CRC 字节初始化 */ 
    U32 ulIndex; /* CRC循环中的索引 */ 
    while(usDataLen--) /* 传输消息缓冲区 */ 
    {
        ulIndex = ucCRCHi ^ *pucMsg++; /* 计算CRC */ 
        ucCRCHi = ucCRCLo ^ auchCRCHi[ulIndex]; 
        ucCRCLo = auchCRCLo[ulIndex]; 
    } 
    return (ucCRCHi << 8 | ucCRCLo); 
}

/******************************************************************************
 Description:
 Input:
 Output:
 Return:
*******************************************************************************/
U16 MODBUS_calcCycleCRC(U8 *pucBuff, U16 usLen)
{
    U8 ucCRCHi = 0xFF; /* 高CRC字节初始化 */ 
    U8 ucCRCLo = 0xFF; /* 低CRC 字节初始化 */ 
    U32 ulIndex; /* CRC循环中的索引 */
    U16 usCnt;

    for(usCnt = 0; usCnt < usLen; usCnt++)
    {
        ulIndex = ucCRCHi ^ pucBuff[usCnt]; /* 计算CRC */ 
        ucCRCHi = ucCRCLo ^ auchCRCHi[ulIndex]; 
        ucCRCLo = auchCRCLo[ulIndex]; 
    }
    return (ucCRCHi << 8 | ucCRCLo); 
}
/*******************************************************************************
* Description    : 求int型数据位数
* Input          : 
* Return         : average
* History		 : 
<No.>	<version >	<time>			<author>     <contents> 
1.		1.0			2019-05-24		shijj		create
*******************************************************************************/
int MM_getNumLen(int num)
{
    int cnt = 0;

    if(num < 0)
    {
        num = -num;
        cnt++;
    }

    while(num)
    {
        cnt++;
        num /= 10;
    }

    return cnt;
}



