#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "Timer0.h"


unsigned char Sec=55,Min=59,Hour=23;
void main()
{
	LCD_Init();
	Timer0_Init();
	LCD_ShowString(1,1,"Clock:");
	LCD_ShowString(2,3,":");
	LCD_ShowString(2,6,":");
	while(1)
	{
		LCD_ShowNum(2,1,Hour,2);
		LCD_ShowNum(2,4,Min,2);
		LCD_ShowNum(2,7,Sec,2);
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;//中断函数结束后,这个变量依然会存活
	//与全局变量的区别是,static后的只能该函数自己用
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		Sec++;
		if(Sec>=60)
		{
			Min++;
			Sec=0;
		}
		if(Min>=60)
		{
			Hour++;
			Min=0;
		}
		if(Hour>=24)
		{
			Hour=0;
		}
	}
	
}