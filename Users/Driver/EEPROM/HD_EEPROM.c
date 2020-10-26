/****************************************************************
Description: HD_Uart.c
Author: shijj
Notes: EEPROM驱动
*****************************************************************/
#define __HD_EEPROM_C__
/*- 1.Include---------------------------------------------------*/
#include "Include.h"
#include "HD_EEPROM.h"

//wait to add......

/*- 2.Macro-----------------------------------------------------*/
#define I2C_SDA_OUTPUT    IO_I2C_SDA_OUTPUT
#define I2C_SCL_OUTPUT    IO_I2C_SCL_OUTPUT
#define I2C_SCL_L         IO_I2C_SCL_L
#define I2C_SCL_H         IO_I2C_SCL_H
#define I2C_SDA_H         IO_I2C_SDA_H
#define I2C_SDA_L         IO_I2C_SDA_L
#define I2C_SDA_INPUT     IO_I2C_SDA_INPUT
#define I2C_SDA_PV        IO_I2C_SDA_PV
#define I2C_SCL_INPUT     IO_I2C_SCL_INPUT
#define I2C_WP_H          IO_EE_WP_H
#define I2C_WP_INPUT      IO_EE_WP_INPUT
#define I2C_WP_OUTPUT     IO_EE_WP_OUTPUT
#define I2C_WP_L          IO_EE_WP_L

#define I2C_WP_enable( )    I2C_WP_H;I2C_WP_INPUT
#define I2C_WP_disable( )   I2C_WP_OUTPUT;I2C_WP_L

/*- 3.Private variable------------------------------------------*/
/*private functions defined in this file:------------------------------------*/

void MIS_delay_us(U32 ulDlyCnt)
{
    while(ulDlyCnt--);
}

void I2C_start( void )
{
    I2C_SDA_OUTPUT;
    I2C_SCL_OUTPUT;
    I2C_SCL_L;
    I2C_SDA_H;
    MIS_delay_us( 2 );
    I2C_SCL_H;
    I2C_SDA_L;
    MIS_delay_us( 2 );
    I2C_SCL_L;
    MIS_delay_us( 2 );
}

//------------------------------------------------------------------------------
//Description: send one byte to the i2c bus
//             MSB first
//Input: U8 oneByte - data to be send
//Output: ack signal from the slave 
//------------------------------------------------------------------------------
U8 I2C_sendByte( U8 oneByte )
{ 
    U8 k,ack;
    
    for( k=0;k<8;k++ ) //sending eight bit
    {
        I2C_SCL_L; 
        if( oneByte&0x80 )
        {
            I2C_SDA_H;
        }
        else
        {
            I2C_SDA_L;
        }
        MIS_delay_us( 2 );
        I2C_SCL_H;
        MIS_delay_us( 2 );
        oneByte <<= 1;
    }
    
    I2C_SCL_L;
    MIS_delay_us( 2 );
    I2C_SDA_INPUT;//waiting for ack from slave
    I2C_SCL_H;
    MIS_delay_us( 2 );
    ack = I2C_SDA_PV;
    I2C_SCL_L;
    I2C_SDA_OUTPUT;
    MIS_delay_us( 2 );
    return( ack );
}

//------------------------------------------------------------------------------
//Description: receive one byte from the slave
//             MSB first
//Input: none
//Output: the data received
//------------------------------------------------------------------------------
U8 I2C_rcvByte( void )
{
    U8 k,tmpByte = 0x00;
    
    I2C_SDA_INPUT;
    I2C_SCL_L;
    MIS_delay_us( 2 );
    for( k=0;k<8;k++ )
    {
        tmpByte <<= 0x01;
        I2C_SCL_H;
        if( I2C_SDA_PV )
            tmpByte++;
        MIS_delay_us( 2 );
        I2C_SCL_L;
    }
    I2C_SDA_OUTPUT;
    MIS_delay_us( 2 );
    return( tmpByte );
}

//------------------------------------------------------------------------------
//Input: ack signal to be sent to I2C bus
//Output: none
//------------------------------------------------------------------------------
void I2C_ack( U8 ack )
{
    I2C_SCL_L;
    MIS_delay_us( 2 );
    if( ack==1 )
    {
        I2C_SDA_H;
    }
    else
    {
        I2C_SDA_L;
    }
    MIS_delay_us( 2 );
    I2C_SCL_H;
    I2C_SCL_L;
    MIS_delay_us( 2 );
}

//------------------------------------------------------------------------------
//Description: stop I2C bus
//Input: none
//Output: none
//------------------------------------------------------------------------------
void I2C_stop( void )
{
    I2C_SCL_L;
    I2C_SDA_L;
    MIS_delay_us( 2 );
    I2C_SCL_H;
    I2C_SDA_H;
    I2C_SDA_INPUT;
    I2C_SCL_INPUT;
    MIS_delay_us( 2 );
}

/*******************************************************************************
 Description: 往铁电FM24CL64、EE-AT24LC512写数据函数接口;..
 Input:          
    U16 SubAddr: the addr of salve module to store the data;
    U8 *dataBuff: the pointer of the buffer which stores the data to be written;
    U8 len: the number of the data to be written(unit:Byte);
 *******************************************************************************/
void I2C_readData( U8 sla, U16 iSuba,U8 *pBuf, U16 num )
{
    U8 tryNum;
    U16 k;
    if( num==0x00 )   return;

    //vTaskSuspendAll(); //挂起调度器
    
    for( tryNum=0;tryNum<2;tryNum++ )
    {
        if( tryNum!=0 ) Delay_ms( 6 );
        I2C_start( );
        if( I2C_sendByte( sla )==0x01 )     continue;  //send the slave address
        if( I2C_sendByte( iSuba>>0x08 )==0x01 ) continue;  //send the MSB address
        if( I2C_sendByte( iSuba )==0x01 ) continue;  //send the LSB address
        I2C_start( );
        if( I2C_sendByte( sla+0x01 )==0x01 )continue;  //send the slave address
        for( k=0;k<num-1;k++ )
        {
            *pBuf = I2C_rcvByte( );
            I2C_ack( 0 );
            pBuf++;
        }
        *pBuf = I2C_rcvByte( );
        I2C_ack( 1 );
        I2C_stop( );
        break;
    }
    if(tryNum == 2)
    {
        
    }
    else
    {
        
    }

    //xTaskResumeAll(); //恢复调度器
}

/*******************************************************************************
 Description: 往铁电FM24CL64、EE-AT24LC512写数据函数接口;..
 Input:          
    U16 SubAddr: the addr of salve module to store the data;
    U8 *dataBuff: the pointer of the buffer which stores the data to be written;
    U8 len: the number of the data to be written(unit:Byte);
 *******************************************************************************/
void I2C_writeData( U8 sla, U16 iSuba, U8 *pBuf, U16 num )
{
    U8 tryNum;
    U16 k;
    U16 tmpAddr;

    if( num==0x00 )     return;

    //vTaskSuspendAll(); //挂起调度器
    
    I2C_WP_disable( );
    for( tryNum=0;tryNum<2;tryNum++ )
    {
        if( tryNum!=0 ) Delay_ms(6);
        tmpAddr = iSuba;
        I2C_start( );
        if( I2C_sendByte( sla )==0x01 )    continue;  //send the slave address
        if( I2C_sendByte( tmpAddr>>0x08 )==0x01 ) continue;  //send the MSB address
        if( I2C_sendByte( tmpAddr )==0x01 )       continue;  //send the LSB address
        
        for(k=0;k<num;k++)
        {
            if( I2C_sendByte( pBuf[k] )==0x01 ) break;  //send data
            tmpAddr++;
            if( (tmpAddr%128)==0 && (k+1)<num )
            {
                I2C_stop( );
                Delay_ms(6);
                I2C_start( );
                if( I2C_sendByte( sla )==0x01 )    break;  //send the slave address
                if( I2C_sendByte( tmpAddr>>0x08 )==0x01 ) break;  //send the MSB address
                if( I2C_sendByte( tmpAddr )==0x01 )       break;  //send the LSB address
            }
        }
        I2C_stop( );
        if( k<num ) continue;
        else        break;
    }
    if(tryNum == 2)
    {
        
    }
    else
    {
        
    }

    //I2C_wrBusyWait( sla );
    Delay_ms(6);
    I2C_WP_enable( );    //inhibit EEPROM writing operation

    //xTaskResumeAll(); //恢复调度器
}

