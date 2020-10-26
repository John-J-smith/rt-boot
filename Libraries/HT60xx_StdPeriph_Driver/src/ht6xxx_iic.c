/*
*********************************************************************************************************
*                                              HT6XXXX
*                                           Library Function
*
*                                   Copyright 2013, Hi-Trend Tech, Corp.
*                                        All Rights Reserved
*                                         
*
* Project      : HT6xxx
* File         : ht6xxx_iic.c
* By           : SocTeam
* Version      : CurrentVersion
* Description  : 
*********************************************************************************************************
*/

#define  __HT6XXX_IIC_C

#include "ht6xxx_iic.h"

volatile unsigned char i2cend=0;

/*
*********************************************************************************************************
*                                           本地宏/结构体
*********************************************************************************************************
*/

//typedef void  (*IIC_IRQ_DEF)(void);

IIC_IRQ_DEF    I2C_IRQHandlerSelect;   

typedef struct
{
    unsigned char  deviceAddr;
    unsigned char  wordAddrH;
    unsigned char  wordAddrL;
    unsigned char  wordAddrNum;
    unsigned char  wordNum;
    unsigned char* pword;
}EEPROM_Operation_Typedef;


/*
*********************************************************************************************************
*                                             本地变量
*********************************************************************************************************
*/

EEPROM_Operation_Typedef  eepromSet;



/*
*********************************************************************************************************
*                                           本地函数申明
*********************************************************************************************************
*/

IIC_IRQ_DEF    I2C_IRQHandlerSelect; 
/*
*********************************************************************************************************
*                                     INITIAL IIC MODULE
*
* 函数说明: 初始化IIC模块
*
* 入口参数: 无                            
*
* 返回参数: 无                                      
* 
* 特殊说明: 用户在配置IIC寄存器前应先使能IIC模块，具体参见HT_CMU_ClkCtrl0Config()函数
*********************************************************************************************************
*/
void HT_IIC_Init()
{
    /*  assert_param  */
    //HT_I2C->I2CCON = 0x7fc3;  
    HT_I2C->I2CCON = 0x1c0;      //100k max
  
} 


//**********************************************************************************
//							  I2c start
//********************************************************************************** 
void iic_start(void)
{
 	HT_I2C->I2CCON |= 0x0020;
    i2cend=0;
}
//**********************************************************************************
//							  I2c stop
//********************************************************************************** 


void iic_stop(void)
{
	HT_I2C->I2CCON |= 0x0010;
    i2cend=1;
}

//**********************************************************************************
//							  I2c stop
//********************************************************************************** 


void Clr_si(void)
{
	HT_I2C->I2CCON &= 0xffd7;    //清除Si和STA
}


void Clr_StartStop()
{
	HT_I2C->I2CCON &= 0xffd7;    //清除STA   
        HT_I2C->I2CCON &= 0xffef;    //清除STOP 

}
//**********************************************************************************
//							  I2c stop
//********************************************************************************** 


void Set_Ack(void)
{
	HT_I2C->I2CCON |= 0x04;
}


//**********************************************************************************
//							  I2c stop
//********************************************************************************** 


void Set_NoAck(void)
{
	HT_I2C->I2CCON &= ~0x0004;
}


void EEPromWrite_IRQHandler(void) 
{
	/* 读取I2C状态寄存器I2CSTA */
	/* 按照全局变量的设置进行操作及设置软件标志 */
	/* 清除中断逻辑,中断返回 */
    
	switch (HT_I2C->I2CSTA & 0xF8)       /* 根据状态码进行相应的处理 */
	{ 
	case 0x08: /* 已发送起始条件 */    /* 主发送和主接收都有   */
		/* 装入SLA+W*/

        HT_I2C->I2CDAT = eepromSet.deviceAddr;     /* 先写入地址     */

		/* 清零SI位 */
		Clr_si();
		break;

	case 0x18:
	case 0x28: /* 已发送I2DAT中的数据，已接收ACK */
         if(eepromSet.wordAddrNum==2)
         {
             HT_I2C->I2CDAT = eepromSet.wordAddrH;
             eepromSet.wordAddrNum--;
         }
         else if(eepromSet.wordAddrNum==1)
         {
             HT_I2C->I2CDAT = eepromSet.wordAddrL;
             eepromSet.wordAddrNum--;
         }
         else
         {
             if(eepromSet.wordNum)
             {
                 HT_I2C->I2CDAT = *eepromSet.pword++;
                 eepromSet.wordNum--;
             }
             else
             {
                 iic_stop();
             }
         }
         Clr_si();         
        break;
		default:
			iic_stop();
			Clr_si();
			break;

	}
	/* 中断处理结束    */
}  

void EEPromRead_IRQHandler(void) 
{
	/* 读取I2C状态寄存器I2CSTA */
	/* 按照全局变量的设置进行操作及设置软件标志 */
	/* 清除中断逻辑,中断返回 */

	switch (HT_I2C->I2CSTA & 0xF8)       /* 根据状态码进行相应的处理 */
	{ 
	case 0x08: /* 已发送起始条件 */    /* 主发送和主接收都有   */
		/* 装入SLA+R */

        HT_I2C->I2CDAT = eepromSet.deviceAddr;     /* 先写入地址     */

		/* 清零SI位 */
		Clr_si();
		break;

	case 0x40: /* 已发送SLA+R,已接收ACK */
		if (eepromSet.wordNum <= 1) /* 如果是最后一个字节 */   
		{ 
			Set_NoAck();                         /* 下次发送非应答信号   */
		}
		else
		{  
			Set_Ack();                          /* 下次发送应答信号   */
		}
		Clr_si();       /* 清零SI,STA     */
		break;
     

	case 0x50: /* 已接收数据字节，已返回ACK */
		*eepromSet.pword++ = HT_I2C->I2CDAT;
        eepromSet.wordNum--;
		if (eepromSet.wordNum <= 1) /* 如果是最后一个字节 */   
		{ 
			Set_NoAck();                         /* 下次发送非应答信号   */
		}
		else
		{  
			Set_Ack();                          /* 下次发送应答信号   */
		}
		Clr_si();       /* 清零SI,STA     */
		break;

	case 0x58: /* 已接收数据字节，已返回非应答 */
		*eepromSet.pword++ = HT_I2C->I2CDAT;
		iic_stop();             /* 结束总线     */
		Clr_si();
		break;

	default:
		iic_stop();
		Clr_si();
		break;

	}
	/* 中断处理结束    */
}


void  EEPROM_Write(unsigned char  deviceAddr, unsigned short int wordAddr, unsigned char  wordNum,  unsigned char* pword)
{
    eepromSet.deviceAddr =  deviceAddr&0xFE;
    eepromSet.wordAddrH  =  wordAddr>>8;
    eepromSet.wordAddrL  =  wordAddr&0xff;
    eepromSet.wordAddrNum=  2;
    eepromSet.wordNum    =  wordNum;
    eepromSet.pword      =  pword;
    I2C_IRQHandlerSelect =  EEPromWrite_IRQHandler;
    
    iic_start();
    
    while(i2cend==0);            //waiting for end
    
    Clr_StartStop();
}


void  EEPROM_Read(unsigned char  deviceAddr, unsigned short int wordAddr, unsigned char  wordNum,  unsigned char* pword)
{
    int kk;
    EEPROM_Write(deviceAddr, wordAddr, 0, 0);     //设定当前地址   多了一个stop
    
    for(kk=0;kk<10000;kk++);
    eepromSet.deviceAddr =  deviceAddr|0x01;
    eepromSet.wordAddrH  =  wordAddr>>8;
    eepromSet.wordAddrL  =  wordAddr&0xff;
    eepromSet.wordNum    =  wordNum;
    eepromSet.pword      =  pword;    
    
    
    I2C_IRQHandlerSelect =  EEPromRead_IRQHandler;
    iic_start();                                  //重新开始
    
    while(i2cend==0);          //waiting for end
    
    Clr_StartStop();
}





