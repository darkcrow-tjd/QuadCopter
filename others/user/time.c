/*******************************************************************************
// file				:	time.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	£º8.00M
// IDE				: Keil uVision4
// date				£º2014.2.28
*******************************************************************************/ 
 
 #include "time.h"
 
 void Delayms(vu32 m)
{
  uint i;
  for(; m != 0; m--)	
       for (i=0; i<50000; i++);
}

 void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

