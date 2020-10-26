/****************************************************************
Description: HD_EEPROM.h
Author: shijj
Notes: EEPROM 驱动头文件
*****************************************************************/
#ifndef __HD_EEPROM_H
#define __HD_EEPROM_H
/*- 1.Macro-----------------------------------------------------*/

/*- 2.Type prototype--------------------------------------------*/

/*- 3.Public variable-------------------------------------------*/


/*- 4.Public function-------------------------------------------*/
#ifndef __HD_EEPROM_C__
    #define __GLOBAL  extern
#else
    #define __GLOBAL
#endif

__GLOBAL    void      HD_EEPROM_Init(void);
__GLOBAL    void      I2C_writeData( U8 sla, U16 iSuba, U8 *pBuf, U16 num );
__GLOBAL    void      I2C_readData( U8 sla, U16 iSuba,U8 *pBuf, U16 num );

#undef __GLOBAL  

/*- 5.End-------------------------------------------------------*/

#endif
