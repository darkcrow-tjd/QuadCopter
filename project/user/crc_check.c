/*******************************************************************************
// file				:	crc_check.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	£º8.00M
// IDE				: Keil uVision4
// date				£º2014.2.28
*******************************************************************************/

#include "crc_check.h"

u16 CRC16Check(u8 *buf, u8 len) 
{
    u8  i, j;
    u16 uncrcReg = 0xffff;
    u16 uncur;

   for (i = 0; i < len; i++) 
    {
         uncur = buf[i] << 8;
       for (j = 0; j < 8; j++) 
      { 
             if ((short)(uncrcReg ^ uncur) < 0)
           {
                uncrcReg = (uncrcReg << 1) ^ 0x1021;
           }
           else
             {
                   uncrcReg <<= 1; 
             } 
                
             uncur <<= 1;            
         }
     }
 
     return uncrcReg;
}
