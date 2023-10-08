#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"

unsigned char Second;
unsigned char Minute;
unsigned char Hour;



void main()
{
	LCD_Init();
	DS1302_Init();
	DS1302_SetTime();
	LCD_ShowString(2,3,":");
	LCD_ShowString(2,6,":");

	while(1)
	{
		DS1302_ReadTime();
		LCD_ShowNum(1,1,DS1302_Time[0],2);
		LCD_ShowNum(1,4,DS1302_Time[1],2);
		LCD_ShowNum(1,7,DS1302_Time[2],2);
		LCD_ShowNum(2,1,DS1302_Time[3],2);
		LCD_ShowNum(2,4,DS1302_Time[4],2);
		LCD_ShowNum(2,7,DS1302_Time[5],2);
		LCD_ShowString(2,10,"Day");
		LCD_ShowNum(2,13,DS1302_Time[6],1);
		
		Delay(500);
	}
}


//BCD码为什么9后面变16
//9->16  0000 1001  -> 0001 0000
//         0    9   ->   1    0