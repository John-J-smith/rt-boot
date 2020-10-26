/**
******************************************************************************
* @file    common.c
* @author  Application Team
* @version V4.3.0
* @date    2018-09-04
******************************************************************************
* @attention
******************************************************************************
*/
#include "common.h"
#include "Include.h"
#include "ht6xxx_flash.h"


pFunction Jump_To_Application;
uint32_t JumpAddress;

extern uint32_t FlashDestination;
extern volatile uint32_t g_bAppRun;
U8 uart_snd_flg = 0;
U8 uart_rcv_flg = 0;
U8 key_val = 0;

/**
* @brief  Integer switch to string.
* @inparam   intnum.
* @outparam  str
* @retval None.
**/
void Int2Str(uint8_t* str, int32_t intnum)
{
    uint32_t i, j ;
    uint32_t Div = 1000000000;
    uint32_t Status = 0;

    for (i = 0; i < 10; i++)
    {
        j = 0;
        str[j++] = (intnum / Div) + 48;

        intnum = intnum % Div;
        Div /= 10;
        if ((str[j-1] == '0') & (Status == 0))
        {
            j = 0;
        }
        else
        {
            Status++;
        }
    }
}

/**
* @brief  String switch to integer.
* @inparam   inputstr:
* @outparam  intnum£º
* @retval 0: Error.
1£ºCorrect.
**/
uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum)
{
    uint32_t i = 0, res = 0;
    uint32_t val = 0;

    if (inputstr[0] == '0' && (inputstr[1] == 'x' || inputstr[1] == 'X'))
    {
        if (inputstr[2] == '\0')
        {
            return 0;
        }
        for (i = 2; i < 11; i++)
        {
            if (inputstr[i] == '\0')
            {
                *intnum = val;
                res = 1;
                break;
            }
            if (ISVALIDHEX(inputstr[i]))
            {
                val = (val << 4) + CONVERTHEX(inputstr[i]);
            }
            else
            {
                res = 0;
                break;
            }
        }

        if (i >= 11)
        {
            res = 0;
        }
    }
    else
    {
        for (i = 0; i < 11; i++)
        {
            if (inputstr[i] == '\0')
            {
                *intnum = val;
                res = 1;
                break;
            }
            else if ((inputstr[i] == 'k' || inputstr[i] == 'K') && (i > 0))
            {
                val = val << 10;
                *intnum = val;
                res = 1;
                break;
            }
            else if ((inputstr[i] == 'm' || inputstr[i] == 'M') && (i > 0))
            {
                val = val << 20;
                *intnum = val;
                res = 1;
                break;
            }
            else if (ISVALIDDEC(inputstr[i]))
            {
                val = val * 10 + CONVERTDEC(inputstr[i]);
            }
            else
            {
                res = 0;
                break;
            }
        }
        if (i >= 11)
        {
            res = 0;
        }
    }

    return res;
}

/**
* @brief    Calculate the number of Falsh page.
* @inparam  Size: Length of file.
* @outparam None.
* @retval   The number of Falsh page.
**/
uint32_t FLASH_PagesMask(volatile uint32_t Size)
{
    uint32_t pagenumber = 0x0;
    uint32_t size = Size;

    if ((size % PAGE_SIZE) != 0)
    {
        pagenumber = (size / PAGE_SIZE) + 1;
    }
    else
    {
        pagenumber = size / PAGE_SIZE;
    }
    return pagenumber;
}

/**
* @brief  Erase FLASH sector.
* @param  SectorAddr: sector address.
* @retval None
*/
void FLASH_SectorEraseUnderUnlock(uint32_t SectorAddr)
{
    //FLASH->PGADDR = SectorAddr;
    //FLASH->SERASE = FLASH_SERASE_KEY;
    //while (FLASH->SERASE != 0);
    HT_Flash_PageErase(SectorAddr);
}

/**
* @brief  FLASH one word progarm .
* @param  Addr: program address
Word: word to write
* @retval None
*/
void FLASH_ProgramOneWord(uint32_t Addr, uint32_t Word)
{
    //FLASH->PGADDR = Addr;
    //FLASH->PGDATA = Word;
    HT_Flash_WordWrite(&Word, Addr, 4);
}

/**
* @brief  Unlock FLASH.
* @param  None
* @retval None
*/
void FLASH_Unlock(void)
{
    //FLASH->PASS = 0x55AAAA55;
}

/**
* @brief  Lock FLASH.
* @param  None
* @retval None
*/
void FLASH_Lock(void)
{
    //FLASH->PASS = 0;
}
