/******************************************************************************
 Copyright (C) Aug.2��2004  R&D Institute of Reallin Co., Ltd.
 Module         : �������Ͷ���ͷ�ļ�..
 File Name      : macro_typedef.h
 Description    : 
 Author         : liu shun           
 Build Date     : 
 others         : ��ͷ�ļ��Գ��õ��Զ����������Ͷ���
                  
 ------------------------------------------------------------------------------
 Modification History:
 <No.> <version >  <time>        <author>     <contents> 
  2��    
  1��    1.00     2009-02-20    liu shun     build this moudle  
******************************************************************************/
#ifndef _MACRO_TyPEDEF_H
#define _MACRO_TyPEDEF_H

#include "..\INC\Include.h"
/*---------------------------------------------------------------------------*/

/* 1 ------------------------------------------------------------------------
 �곣��ֵ����
-------------------------------------------------------------------------- */         
#define _OffsetOf(TYPE, MEMBER) (U32)(&((TYPE *)0)->MEMBER) 			/*��ȡ������ĳ����Ա��ƫ�Ƶ�ַ*/
#define _AddrOfRam(variable)    (U32)(void *)(&variable)         		 /*��ȡ�ڴ��ַ*/    


/* power fail detect */
typedef enum
{
    E_POWER_FAIL      = 0x00,  /* ����8�μ�⵽���� */
    E_POWER_NORMAL    = 0xFF,  /* ����8�μ�⵽�������� */
} ENUM_Power_Status;

/* power mode */
typedef enum
{
	E_POWERMODE_ON    = 1,
    E_POWERMODE_OFF   = 2,
    E_POWERMODE_SLEEP = 3,
} ENUM_Power_Mode;


/* tick count */
typedef enum
{
    E_TICK20sBASED125msSET    = 160,
	E_TICK20msBASED250usSET   = 80,
    E_TICK250msBASED125msSET  = 2,
    E_TICK1sBASED125msSET     = 8,
    E_TICK1500msBASED125msSET = 12,
    E_TICK3000msBASED125msSET = 24,
    E_TICK250msBASED5msSET    = 50,
    E_TICK100msBASED5msSET    = 20,
    E_TICK500msBASED5msSET    = 100,
    E_TICK1000msBASED5msSET   = 200,
    E_TICK20msBASED5msSET     = 4,
    E_TICK5msBASED5msSET      = 1,
    E_TICK125MS_BASE_250US    = 500,
	E_TICK125MS_BASE_100US    = 1250,
	E_TICK160MS_BASE_100US    = 1600,
    E_TICK10MS_BASE_250US     = 40,
    E_COMM_CHECK_SET_TIME     = 120,
    E_PLC_COMM_CHECK_SET_TIME = 450,
} ENUM_Tick_Cnt;

typedef enum
{
    E_EQUAL    = 0x00,
    E_BIGGER   = 0x01,
    E_LESS     = 0xFF,
} ENUM_COMPARE_RESULT;

/* eeprom page write number */
typedef enum
{
    E_PAGE_SIZE512  = 128, /* 24LC512��ҳдֵ */ 
    E_PAGE_SIZE256  = 64,  /* 24LC256��ҳдֵ */ 
    E_PAGE_SIZE32   = 32,  /* 24LC32��ҳдֵ  */  
    E_PAGE_SIZE8    = 8,   /* 24LC02��ҳдֵ  */ 
    E_PAGE_SIZE     = E_PAGE_SIZE256,
} ENUM_Eeprom_Page_Size;


/* HDLC setup define */
typedef enum
{ 
    BIGGER = 0x01,
    EQUAL = 0x00,
    LESS = 0xFF,
} ENUM_CMP_RESULT;


// λ����궨��
//*****************************************************************************
#define     REVBIT(x,y) ((x) ^= (1 << (y)))    // Reverse bit
#define     SETBIT(x,y) ((x) |= (1 << (y)))    // Set   bit y in byte x
#define     CLRBIT(x,y) ((x) &= (~(1 << (y)))) // Clear bit y in byte x
#define     CHKBIT(x,y) ((x) & (1 << (y)))    // Check bit y in byte x

/* �Զ������ݽṹ���� */
/* BYTE STRUCTION -----------------------------------------------------------*/
typedef union
{
    U8 byte;
    struct
    {
        U8 b0  :1;
        U8 b1  :1;
        U8 b2  :1;
        U8 b3  :1;
        U8 b4  :1;
        U8 b5  :1;
        U8 b6  :1;
        U8 b7  :1;
    }Bit;                       // ������bit��WINAVR�п��ԣ�������Ϊbit��NEC�������ı�����
}BYTE_STRUCT;
/* WORD STRUCTION -----------------------------------------------------------*/
typedef union
{
    U16 word;
    struct
    {
        U8 b0  :1;
        U8 b1  :1;
        U8 b2  :1;
        U8 b3  :1;
        U8 b4  :1;
        U8 b5  :1;
        U8 b6  :1;
        U8 b7  :1;
        U8 b8  :1;
        U8 b9  :1;
        U8 b10 :1;
        U8 b11 :1;
        U8 b12 :1;
        U8 b13 :1;
        U8 b14 :1;
        U8 b15 :1;
    }Bit;
}WORD_STRUCT;
/* ------------------------------------------------------------------------- */ 
typedef union
{
    S32 long_value;
    U8 bytes[4];
}LONG_STRUCT;
/* ------------------------------------------------------------------------- */ 
typedef union
{
    U32 ulong_value;
    U8 bytes[4];
}ULONG_STRUCT;
/* ------------------------------------------------------------------------- */
typedef union
{
    U8     content[8];
    struct
    {
        U8   sec;
        U8   min;
        U8   hour;
        U8   week;
        U8   day;
        U8   month;
        U8   year;
        U8   cs;
    }byte;
}DATE_STRUCT; 


/* ------------------------------------------------------------------------- */
/* data type used int COSEM define */
// -----------------
// -----------------
// 11 bytes
// -----------------
__packed typedef struct
{
    U16 class_id;
    U8  logical_name[6];
    S8  attribute_index;
    U16 data_index;
}ST_CAPTURE_OBJECT;
// -----------------
// 5 bytes
// -----------------
__packed typedef struct
{
    U8  null;
    U8  year;
    U8  month;
    U8  day;
    U8  week;
}ST_DATE;

// -----------------
// 4 bytes
// -----------------
__packed typedef struct
{
    U8  hour;
    U8  minute;
    U8  second;
    U8  hundredths;
}ST_TIME;

// -----------------
// 12 bytes
// -----------------
__packed typedef struct
{
    ST_DATE stDate;
    ST_TIME stTime;
    S16     siDeviation;
    U8      ucStatus;
}ST_DATETIME;


// --------------------------------------
// 14 bytes
// --------------------------------------
__packed typedef struct
{
    U8  ucName;
    ST_DATETIME stStart;
    U8  ucWeekName;
}ST_SEASON;

// --------------------------------------
// 8 bytes
// --------------------------------------
__packed typedef struct
{
    U8  ucName;
    U8  ucDayId[7];
}ST_WEEK_PROFILE;

// --------------------------------------
// 12 bytes
// --------------------------------------
__packed typedef struct
{
    ST_TIME stTime;
    U8      ucScrptLN[6];
    U16     uiScrptSlctr;
}ST_DAY_PROFILE_ACTION;

// --------------------------------------
// 121 bytes
// --------------------------------------
__packed typedef struct
{
    U8  ucId;
    ST_DAY_PROFILE_ACTION stDaySchdl[10];
}ST_DAY_PROFILE;


// --------------------------------------
// 8 bytes
// --------------------------------------
__packed typedef struct
{
    U16 index;
    ST_DATE st_date;
    U8  day_id;
}ST_SPEC_DAY_ENTRY;

// --------------------------------------
// METER TYPE
// --------------------------------------
__packed typedef struct
{
    U16 usNorminalVoltage;
    U16 usRefFreq;
    U32 ulBasicCurrent;
    U32 ulMaxCurrent;
}ST_METER_TYPE;

/*---------------------------------------------------------------------------*/
/*===========================================================================*/
/*---------------------------------------------------------------------------*/

/* ------------------------------------------------------------------------- */
//ϵͳ����״̬
__packed union ErrByte
{
    __packed struct  
    {
        U8 NoBat    :1;
        U8 Rtc      :1;
        U8 Eeprom   :1;  
        U8 dataFlash:1;
        U8 Hardware :1; // �κγ���set   1
        U8 viUnbalance :1;// ��ѹ�������ƽ��
        U8 biaoGaiOpen:1;
        U8 duanGaiOpen:1;
    }Bit;
    U8 Byte;
};


// --------------------------------------
// CT_PT
// --------------------------------------
__packed typedef struct
{
    U16 usCT_Numerator;
    U32 ulTR_All_Numerator;
    U16 usCT_Denominator;
    U16 usTR_All_Denominator;
}ST_PARA_CTPT_TABLE;



#ifndef FALSE
#define FALSE          0
#endif 
/*---------------------------------------------------------------------------*/
/* \brief Flag state definition                                              */
/*---------------------------------------------------------------------------*/
#ifndef TRUE
#define TRUE           1
#endif

#define   METER_S5          //S5 S41�󰲱�֧��CT PT



/* ����ͺŹ��� */
#define  MTR_ID2_S5             '2'
#define  MTR_ID1_S5             '0'
#define  MTR_ID0_S5             '8'
#define  MTR_ID2_S41           	'2'
#define  MTR_ID1_S41        	'0'
#define  MTR_ID0_S41          	'7'


/* �û����� */   
#define  SAUDI_H                '0'
#define  SAUDI_L                '0'

#define  USER_ID_H              SAUDI_H
#define  USER_ID_L              SAUDI_L

/* Ӳ���汾�Ŷ��� */
#define  HARD_VS_CODE1          '1'
#define  HARD_VS_CODE0          '1'

#define _CTT_TEST                 //CTT����ʱ�����

//#define   _KEMA_  //�궨��ѡ�ϱ�ʾkema ��֤����ѡ�� ��ʾ��������

//#define   _EMC_LP_ //ѡ�ϱ�ʾ����EMC���Եĳ���
//#define   _LP_TEST_ //�������߾��Ʋ��� 

//#define   CT_PT_Multip   //��Ҫ����CT��PT�ṩ����Լ(��ʾ֮ǰ���ṩ)
//#define    MICROCHIP_TEST
//#define     USE_INTER_RTC //ʹ���ڲ�ʱ��


#define  SOFT_VS_CODE0          '0'
#define  SOFT_VS_CODE1          '0'
#define  SOFT_VS_CODE2          '4'
#define  SOFT_VS_CODE3          '1'


#define  CHECK_SUM              0xFC1D  //��λ����������ʾ����1DFC


#ifdef _KEMA_
#define  INTER_SOFT_VS_CODE0          '1'
#endif
#ifndef _KEMA_
#define  INTER_SOFT_VS_CODE0          '0'
#endif  


#define  INTER_SOFT_VS_CODE1_S5       '0'
#define  INTER_SOFT_VS_CODE2_S5       '4'
#define  INTER_SOFT_VS_CODE3_S5       '1'



#define  PHS_ON             (6000)  //60V��Ϊ�����жϺͼ̵���״̬���ж�ʱ���õ���C���ѹ����
#define  PHS_ANGLE_ON       (8000)  //80V���ϲ���Ϊ����ó��ĽǶ�����Ч��

#define  POWER_DIV          100

#define  impPerKWH          1000        //�󰲵�Ϊ1000 imp/kWh С����Ϊ10000 imp/kWh



/*����ԭ��˲ʱ���ĵ�λ��DLMS��Լ�ϴ��н��б��ʵ���*/
#define  S16VE_POWER_DIV          100
#define  S16VE_POWER_FACT_MUL     10
#define  S16VE_VOL_MUL            10
#define  S16VE_FREQ_DIV           10

#define   DEFAULT_TARIFF          1


#define NOR_VOLTAGE_LINE     (17200)//���ݵ�ѹ��С��������Ǳ����

#define POWER_P_MIN_NOR_S5   (13300 * 10000 * 3 / 10000)//��Ǳ��Ϊ133V 10A��ǧ��֮3
#define POWER_Q_MIN_NOR_S5   (13300 * 10000 * 3 / 10000)//��Ǳ��Ϊ133V 10A��ǧ��֮3
#define POWER_P_MIN_NOR_S5_230V   (23000 * 10000 * 3 / 10000)//��Ǳ��Ϊ230V 10A��ǧ��֮3
#define POWER_Q_MIN_NOR_S5_230V   (23000 * 10000 * 3 / 10000)//��Ǳ��Ϊ230V 10A��ǧ��֮3
#define POWER_P_MAX_NOR_S5   (24000 * 10000 * 3 / 2)//240V*100A*1.5

#define POWER_P_MIN_NOR_S41  (13300 * 20000 * 3 / 10000)//��Ǳ��Ϊ133V 20A��ǧ��֮3
#define POWER_Q_MIN_NOR_S41  (13300 * 20000 * 3 / 10000)//��Ǳ��Ϊ133V 20A��ǧ��֮3
#define POWER_P_MIN_NOR_S41_230V  (23000 * 20000 * 3 / 10000)//��Ǳ��Ϊ230V 20A��ǧ��֮3
#define POWER_Q_MIN_NOR_S41_230V  (23000 * 20000 * 3 / 10000)//��Ǳ��Ϊ230V 20A��ǧ��֮3
#define POWER_P_MAX_NOR_S41  (24000 * 16000 * 3 / 2)//240V*160A*1.5



#endif
