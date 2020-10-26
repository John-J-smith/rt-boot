/****************************************************************
Description: HD_UART.h
Author: shijj
Notes: 液晶驱动头文件
*****************************************************************/
#ifndef __HD_UART_H
#define __HD_UART_H
/*- 1.Macro-----------------------------------------------------*/

#define UART_IT_RXNE   1
#define UART_IT_TXNE   2

/* UART TX State */
#define TXSTART     0
#define TXONGOING   1
#define TXFINISH    2
#define MAX_UART_BUF_SIZE (1024)

/* UART RX State */
#define RXSTART     0
#define RXONGOING   1
#define RXFINISH    2
#define RXERROR     3

#define RS485_1_INPUT    do{IO_RS485_1_DIR_L;}while(0)
#define RS485_1_OUTPUT   do{IO_RS485_1_DIR_H;}while(0)

#define RS485_2_INPUT    do{IO_RS485_2_DIR_L;}while(0)
#define RS485_2_OUTPUT   do{IO_RS485_2_DIR_H;}while(0)

/*- 2.Type prototype--------------------------------------------*/
/* 帧格式*/
typedef enum
{
    E_BAUD_300    = 0,
    E_BAUD_600    = 1,
    E_BAUD_1200   = 2,
    E_BAUD_2400	  = 3,
    E_BAUD_4800	  = 4,
    E_BAUD_9600	  = 5,
    E_BAUD_19200  = 6,
    E_BAUD_38400  = 7,
    E_BAUD_57600  = 8,
    E_BAUD_115200 = 9,
    E_BAUD_230400 = 10,
    E_BAUD_460800 = 11,
    E_BAUD_MAX    = 12,
} ENUM_UART_Baud_cfg;

typedef enum
{
    E_UART_7E1 = 0,
    E_UART_8N1 = 1,
    E_UART_8E1 = 2,
    E_UART_8O1 = 3,
}E_UART_Data_cfg;

typedef enum
{
    E_UART_TX_FINISH = 0,
    E_UART_TX_GOING = 5,
    E_UART_TX_READY = 2,  
}E_UART_TX_STATUS;

typedef enum
{
    E_UART_NBIOT = 0,
    E_UART_RS485 = 1,
    E_UART_DEBUG = 2,
    E_UART_CHNL_MAX = 3,
}ENUM_UART_CHANNEL;

__packed typedef struct
{
    U16 usLen;
    U8  pucBuf[MAX_UART_BUF_SIZE];
}Msg_t;

__packed typedef struct
{
  Msg_t *stRxMsg;
  U16   usRxPtr;                   /* 接收数据指针*/
  U8    ucRxSta;                   /* 接收状态           */
  U16   usTimeOut;                 /* 接收超时           */
  Msg_t *stTxMsg;
  U16   usTxPtr;                   /* 发送数据指针*/
  U8    ucTxSta;                   /* 发送状态*/
  U16   sentDelayCnt;              /* 发送前延时等待时间 */
  U8    ucBaud;                    /* 通道波特率*/
  U8    ucDataCfg;                 /* 通道配置字*/
  U8    ucSelfChkCnt;              /* 自检标志*/
}Uart_Struct;

/*- 3.Public variable-------------------------------------------*/




/*- 4.Public function-------------------------------------------*/
#ifndef __HD_UART_C__
    #define __GLOBAL  extern
#else
    #define __GLOBAL
#endif

__GLOBAL    void    HD_UART_Init(U8 ucChnl, U8 ucBaud, U8 ucType);
__GLOBAL    void    HD_UART_Var_Init(void);

#undef __GLOBAL  

/*- 5.End-------------------------------------------------------*/

#endif
