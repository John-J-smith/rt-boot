/**
  * @file    v_stdio.h
  * @author  Application Team
  * @version V4.3.0
  * @date    2018-09-04
  * @brief   standard printf.
******************************************************************************/

#ifndef __V_STDIO_H
#define __V_STDIO_H

#include <stdint.h>

#define LOG    printf

void Stdio_Init(void);
void Delay_us(volatile uint32_t n);
void Delay_ms(volatile uint32_t n);

#endif

/*********************************** END OF FILE ******************************/
