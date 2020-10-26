/****************************************************************
Description: HD_Uart.c
Author: shijj
Notes: Uart驱动
*****************************************************************/
#define __HD_FLASH_C__
/*- 1.Include---------------------------------------------------*/
#include "Include.h"
#include "HD_Flash.h"

//wait to add......

/*- 2.Macro-----------------------------------------------------*/
#define FLASH_WP_H  IO_DF_WP_H 
#define FLASH_WP_L  IO_DF_WP_L 
#define FLASH_CS_H  IO_DF_CS_H 
#define FLASH_CS_L  IO_DF_CS_L 

/*- 3.Private variable------------------------------------------*/
//定义的buff需是2个flash page
U8 sucFlashBuff[DF_PAGE_SIZE * 2 + 2];

/*- 4.Public variable-------------------------------------------*/


/*- 5.Private function------------------------------------------*/


/*- 6.Const-----------------------------------------------------*/


/*- 7.End-------------------------------------------------------*/
/**
  * @brief  SPI send byte data.
  * @param  None
  * @retval None
  */
static U8 SPI_SendRecvByte(U8 ch)
{
    return (HT_SPI_SendByte(HT_SPI0, ch));    
}

/******************************************************************************
 Description  :  等待data flash读写忙结束
 ..............................................................................
 Modification History:
 <No.> <version >  <time>        <author>     <contents>
  2、
  1、    1.00     2011-04-23    liu shun     build this moudle
 *****************************************************************************/
static void DF_wrBusyWait(void)
{
    U16 i;
    U8 rcvData;

    for(i = 0; i < 15000; i++)
    {
        IO_DF_CS_L;
        SPI_SendRecvByte( DF_CMD_RDSR );
        rcvData = SPI_SendRecvByte( 0x00 );
        IO_DF_CS_H;
        if( rcvData == 0 )
        {
            break;
        }
    }
}
/*****************************************************************************
 Description:
 ..............................................................................
 Modification History:
 <No.> <version >  <time>        <author>     <contents>
  2、
  1、    1.00     2011-04-23    liu shun     build this moudle
 *****************************************************************************/
static void DF_WriteEnable(void)
{
    IO_DF_CS_L;
    SPI_SendRecvByte( DF_CMD_WREN );
    IO_DF_CS_H;
}
/*****************************************************************************
 Description:
 ..............................................................................
 Modification History:
 <No.> <version >  <time>        <author>     <contents>
  2、
  1、    1.00     2011-04-23    liu shun     build this moudle
 *****************************************************************************/
static void DF_WriteDisable( void )
{
    IO_DF_CS_L;
    SPI_SendRecvByte( DF_CMD_WRDI );
    IO_DF_CS_H;
}
/******************************************************************************
 Description  :  写buff中的数据到data flash，写之前要确保页已经擦除过
 Input        :
 ..............................................................................
 Modification History:
 <No.> <version >  <time>        <author>     <contents>
  2、
  1、    1.00     2011-04-23    liu shun     build this moudle
 *****************************************************************************/
static void DF_pageProgram( U32 ulAddr,U8 *buff,U16 len )
{
    U16 i;
    
    DF_wrBusyWait( );
    DF_WriteEnable( );
    IO_DF_CS_L;
    SPI_SendRecvByte(DF_CMD_PP);
    SPI_SendRecvByte((U8)(ulAddr>>16));
    SPI_SendRecvByte((U8)(ulAddr>>8));
    SPI_SendRecvByte((U8)ulAddr);

    for(i = 0; i < len; i++)
        SPI_SendRecvByte( *buff++ );

    IO_DF_CS_H;
    DF_WriteDisable( );
}
/******************************************************************************
 Description  :  擦除data flash某页
 Input        :  curPage 擦除的页号
 ..............................................................................
 Modification History:
 <No.> <version >  <time>        <author>     <contents>
  2、
  1、    1.00     2011-03-27    liu.shun     build this moudle
 *****************************************************************************/
static void DF_SECTORErase(U16 curPage)
{
	DF_wrBusyWait( );
    DF_WriteEnable( );
    IO_DF_CS_L;
    SPI_SendRecvByte( DF_CMD_SCE );
    SPI_SendRecvByte( (U8)(curPage>>8) );
    SPI_SendRecvByte( (U8)(curPage) );
    SPI_SendRecvByte( 0x00 );
    IO_DF_CS_H;
    DF_WriteDisable( );
}

/*******************************************************************************
* @Description: flash初始化
* @Param      : 
* @Return     : 
* @History    : 
* <No.> <version>   <time>          <author>    <contents> 
* 1     1.0         2019-04-15      @shijj      create
*******************************************************************************/
void HD_Flash_Init(void)
{
    SPI_InitTypeDef  SPI_InitStructure;

    HT_CMU_ClkCtrl0Config(CMU_CLKCTRL0_SPI0EN, ENABLE);            /*!< 使能SPI0模块                */

    SPI_InitStructure.SPI_CSInCtrol = DISABLE;
    SPI_InitStructure.SPI_Baudrate = SPI_BaudRatePrescaler_16;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_high;
    SPI_InitStructure.SPI_Mode = SPI_Master;
    //SPI_InitStructure.SPI_CLK = SPI_CLKSEL_PLL44M;

    HT_SPI_Init(HT_SPI0, &SPI_InitStructure);
    FLASH_WP_H;
    FLASH_CS_H;
}
/*******************************************************************************
* @Description: flash 读接口
* @Param      : 数据指针, 数据包长度
* @Return     : 协议类型
* @History    : 
* <No.> <version>   <time>          <author>    <contents> 
* 1     1.0         2019-04-15      @shijj      create
*******************************************************************************/
ErrCode_t Flash_read(U32 addr, U8 *pucBuf, U16 size)
{
    U16 i;

    if(size > MAX_UART_BUF_SIZE)
    {
        return E_OVERFLOW;
    }
    DF_wrBusyWait();
    FLASH_CS_L;

    // read data flash
    SPI_SendRecvByte(DF_CMD_READ);
    SPI_SendRecvByte((U8)(addr>>16));
    SPI_SendRecvByte((U8)(addr>>8));
    SPI_SendRecvByte((U8)addr);
    
    for(i = 0; i < size; i++)
        *pucBuf++ = SPI_SendRecvByte( 0x00 );
    
    FLASH_CS_H;
    return E_SUCCESS;
}
/*******************************************************************************
* @Description: flash 写接口
* @Param      : 数据指针, 数据包长度
* @Return     : 协议类型
* @History    : 
* <No.> <version>   <time>          <author>    <contents> 
* 1     1.0         2019-04-15      @shijj      create
*******************************************************************************/
ErrCode_t Flash_write(U32 addr, U8 *pucBuf, U16 size)
{
    U16 uiNum;
    U16 wrLen;

    if(size > MAX_UART_BUF_SIZE)
    {
        return E_OVERFLOW;
    }

    FLASH_CS_L;
    FLASH_WP_L;

    // write data flash
    while( size )
    {
        uiNum = addr % DF_SECTOR_SIZE;
        if( 0 == uiNum )
        {
            DF_SECTORErase((U16)(addr / DF_PAGE_SIZE));
            Delay_ms(96);
        }
        uiNum = addr % DF_PAGE_SIZE;
        wrLen = DF_PAGE_SIZE - uiNum;

        if( wrLen > size )
        {
            wrLen = size;
        }

        DF_pageProgram( addr, pucBuf, wrLen );
        Delay_ms(3);
        if(wrLen <= DF_PAGE_SIZE)
		{
			memcpy(sucFlashBuff + DF_PAGE_SIZE, pucBuf, wrLen);
			for(U8 ucLoopWrite = 0;ucLoopWrite < 2;ucLoopWrite++)
			{
				Flash_read(addr, sucFlashBuff, wrLen);
				if(memcmp(sucFlashBuff + DF_PAGE_SIZE, sucFlashBuff, wrLen) != 0)
				{
					DF_pageProgram(addr, sucFlashBuff + DF_PAGE_SIZE, wrLen);
					//再次写则强制延时10ms
					Delay_ms(10);
				}
				else
				{
					break;
				}
			}
		}
        
        addr += wrLen;
        pucBuf += wrLen;
        size -= wrLen;
    }
    
    FLASH_WP_H;
    FLASH_CS_H;
    return E_SUCCESS;
}

