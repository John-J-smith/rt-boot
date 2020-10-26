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
*                                           ���غ�/�ṹ��
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
*                                             ���ر���
*********************************************************************************************************
*/

EEPROM_Operation_Typedef  eepromSet;



/*
*********************************************************************************************************
*                                           ���غ�������
*********************************************************************************************************
*/

IIC_IRQ_DEF    I2C_IRQHandlerSelect; 
/*
*********************************************************************************************************
*                                     INITIAL IIC MODULE
*
* ����˵��: ��ʼ��IICģ��
*
* ��ڲ���: ��                            
*
* ���ز���: ��                                      
* 
* ����˵��: �û�������IIC�Ĵ���ǰӦ��ʹ��IICģ�飬����μ�HT_CMU_ClkCtrl0Config()����
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
	HT_I2C->I2CCON &= 0xffd7;    //���Si��STA
}


void Clr_StartStop()
{
	HT_I2C->I2CCON &= 0xffd7;    //���STA   
        HT_I2C->I2CCON &= 0xffef;    //���STOP 

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
	/* ��ȡI2C״̬�Ĵ���I2CSTA */
	/* ����ȫ�ֱ��������ý��в��������������־ */
	/* ����ж��߼�,�жϷ��� */
    
	switch (HT_I2C->I2CSTA & 0xF8)       /* ����״̬�������Ӧ�Ĵ��� */
	{ 
	case 0x08: /* �ѷ�����ʼ���� */    /* �����ͺ������ն���   */
		/* װ��SLA+W*/

        HT_I2C->I2CDAT = eepromSet.deviceAddr;     /* ��д���ַ     */

		/* ����SIλ */
		Clr_si();
		break;

	case 0x18:
	case 0x28: /* �ѷ���I2DAT�е����ݣ��ѽ���ACK */
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
	/* �жϴ������    */
}  

void EEPromRead_IRQHandler(void) 
{
	/* ��ȡI2C״̬�Ĵ���I2CSTA */
	/* ����ȫ�ֱ��������ý��в��������������־ */
	/* ����ж��߼�,�жϷ��� */

	switch (HT_I2C->I2CSTA & 0xF8)       /* ����״̬�������Ӧ�Ĵ��� */
	{ 
	case 0x08: /* �ѷ�����ʼ���� */    /* �����ͺ������ն���   */
		/* װ��SLA+R */

        HT_I2C->I2CDAT = eepromSet.deviceAddr;     /* ��д���ַ     */

		/* ����SIλ */
		Clr_si();
		break;

	case 0x40: /* �ѷ���SLA+R,�ѽ���ACK */
		if (eepromSet.wordNum <= 1) /* ��������һ���ֽ� */   
		{ 
			Set_NoAck();                         /* �´η��ͷ�Ӧ���ź�   */
		}
		else
		{  
			Set_Ack();                          /* �´η���Ӧ���ź�   */
		}
		Clr_si();       /* ����SI,STA     */
		break;
     

	case 0x50: /* �ѽ��������ֽڣ��ѷ���ACK */
		*eepromSet.pword++ = HT_I2C->I2CDAT;
        eepromSet.wordNum--;
		if (eepromSet.wordNum <= 1) /* ��������һ���ֽ� */   
		{ 
			Set_NoAck();                         /* �´η��ͷ�Ӧ���ź�   */
		}
		else
		{  
			Set_Ack();                          /* �´η���Ӧ���ź�   */
		}
		Clr_si();       /* ����SI,STA     */
		break;

	case 0x58: /* �ѽ��������ֽڣ��ѷ��ط�Ӧ�� */
		*eepromSet.pword++ = HT_I2C->I2CDAT;
		iic_stop();             /* ��������     */
		Clr_si();
		break;

	default:
		iic_stop();
		Clr_si();
		break;

	}
	/* �жϴ������    */
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
    EEPROM_Write(deviceAddr, wordAddr, 0, 0);     //�趨��ǰ��ַ   ����һ��stop
    
    for(kk=0;kk<10000;kk++);
    eepromSet.deviceAddr =  deviceAddr|0x01;
    eepromSet.wordAddrH  =  wordAddr>>8;
    eepromSet.wordAddrL  =  wordAddr&0xff;
    eepromSet.wordNum    =  wordNum;
    eepromSet.pword      =  pword;    
    
    
    I2C_IRQHandlerSelect =  EEPromRead_IRQHandler;
    iic_start();                                  //���¿�ʼ
    
    while(i2cend==0);          //waiting for end
    
    Clr_StartStop();
}





