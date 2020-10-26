/**
* @file    main.c
* @author  Application Team
* @version V1.00
* @date    2019-03-08
* @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "Include.h"
#include <stdio.h>
#include "common.h"
#include "v_stdio.h"
#include "sfud.h"
#include "fal.h"
#include "easyflash.h"

/* Private functions ---------------------------------------------------------*/
#define FLASH_PASS_KEY
extern pFunction Jump_To_Application;
extern uint32_t JumpAddress;

#define BS_START_ADDR (0x00074000UL)

__root const char BOOT_VER[] = "BOOT-2043-100";

//掉电检测 1-有电， 0-掉电
U8 gucPowerDown = FALSE;

/*******************************************************************************
* @Description: 掉电检测
* @Param      :
* @Return     :
* @History    :
* <No.> <version>   <time>          <author>    <contents>
* 1     1.0         2019-06-19      @shijj      create
*******************************************************************************/
void AL_PowerDown_Dtc(void)
{
    if(0 == PFAL_Read())
    {
	    IO_LED_RUN_H;
	    IO_LED_TX_H;
	    IO_LED_RX_H;
        while(1);
    }
}


void deinit_before_jump(void)
{
    uint32_t temp;

    __disable_irq();
    // disable all interrupt
    NVIC->ICER[0] = 0xFFFFFFFF;
    // clear pendings
    NVIC->ICPR[0] = 0xFFFFFFFF;
    // stop sys tick
    temp = SysTick->CTRL;
    temp &= ~0x02;
    SysTick->CTRL = temp;
}

extern void __hal_app_jump(uint32_t ulAppAddr);
void JumpToApp(void)
{
    HD_clrWDT();
    /*Jedge the stack address：0x200000000~0x20007FFF*/
    if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFF80000 ) == 0x20000000)
    {
        deinit_before_jump();
        __hal_app_jump(ApplicationAddress);
    }
}

/**
* @brief  Jump to APP.
* @param  None.
* @retval None.
**/
void _JumpToApp(void)
{
    HD_clrWDT();
    /*Jedge the stack address：0x200000000~0x20007FFF*/
    if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFF80000 ) == 0x20000000)
    {
        deinit_before_jump();
        /*Jump to the user code*/
        JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
        Jump_To_Application = (pFunction) JumpAddress;

        __set_CONTROL(0);
        /*Set stack top value of user code as current stack top value */
        __set_MSP(*(__IO uint32_t*) ApplicationAddress);

        Jump_To_Application();
    }
}

/**
* @brief  Jump to BS.
* @param  None.
* @retval None.
**/
typedef void (*pFun)(void);
void Jump_to_BS(void)
{
	pFun Jump_To_Application;
	U32 JumpAddress;

	deinit_before_jump();
	//Jump to the user code
	JumpAddress = *(__IO uint32_t*) (BS_START_ADDR + 4);
	Jump_To_Application = (pFun) JumpAddress;
	//Set stack top value of user code as current stack top value
	__set_MSP(*(__IO uint32_t*) BS_START_ADDR);
    __set_PSP(*(__IO uint32_t*) BS_START_ADDR);

	Jump_To_Application();
}

void print_boot_info(void)
{
    //LOG(" __   __   __  ___\r\n");
    //LOG("|__) /  \\ /  \\  |\r\n");
    //LOG("|__) \\__/ \\__/  |\r\n");


    //LOG(" ______   _____   _____  _______\r\n");
    //LOG(" |_____] |     | |     |    |\r\n");
    //LOG(" |_____] |_____| |_____|    |\r\n");

    LOG("\r\n ______     ______     ______     ______  \r\n");
    LOG("/\\  == \\   /\\  __ \\   /\\  __ \\   /\\__  _\\ \r\n");
    LOG("\\ \\  __<   \\ \\ \\/\\ \\  \\ \\ \\/\\ \\  \\/_/\\ \\/ \r\n");
    LOG(" \\ \\_____\\  \\ \\_____\\  \\ \\_____\\    \\ \\_\\ \r\n");
    LOG("  \\/_____/   \\/_____/   \\/_____/     \\/_/ \r\n");
    
    LOG("version %s\r\n", BOOT_VER);
}

/**
* @brief  Main program.
* @param  None
* @retval None
*/
int main(void)
{
    AL_Init();

    print_boot_info();
    sfud_init();
    fal_init();
    easyflash_init();
    HT_FreeDog();
    ef_set_env("boot_ver", BOOT_VER);

    if(PFAL_Read() != 0)
    {
	    if(Boot_getFotaFlg())
	    {
	        IO_LED_RUN_L;
	        IO_LED_TX_L;
	        IO_LED_RX_L;
	        if(Boot_CheckFirmware())
	        {
	            if(Boot_UpdateFirmware())
	            {
                    ef_set_env("iap_need_copy_app", "0");
                    ef_set_env("iap_sta", "success");
	            	AL_PowerDown_Dtc();
	                goto jump_to_boot;
	            }
				else
				{
					while (1);
				}
	        }
	        AL_PowerDown_Dtc();
	    }
    }
	else
	{
		while (1);
	}

jump_to_boot:
    /*Jump to user code*/
    JumpToApp();

    while (1)
    {
        AL_PowerDown_Dtc();
        HD_clrWDT();
    }
}


#ifndef  ASSERT_NDEBUG
/**
* @brief  Reports the name of the source file and the source line number
*         where the assert_errhandler error has occurred.
* @param  file: pointer to the source file name
* @param  line: assert_errhandler error line source number
* @retval None
*/
void assert_errhandler(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/*********************************** END OF FILE ******************************/
