#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"
#include "Key.h"
#include "Timer0.h"

char KeyNumber,MODE,TimeSetSelect,TimeSetFlashFlag;
unsigned MonthMaxDays[] = {31,29,31,30,31,30,31,31,30,31,30,31}; 

void TimeShow(void)
{
	DS1302_ReadTime();
	LCD_ShowNum(1,1,DS1302_Time[0],2);
	LCD_ShowNum(1,4,DS1302_Time[1],2);
	LCD_ShowNum(1,7,DS1302_Time[2],2);
	LCD_ShowNum(2,1,DS1302_Time[3],2);
	LCD_ShowNum(2,4,DS1302_Time[4],2);
	LCD_ShowNum(2,7,DS1302_Time[5],2);
	//LCD_ShowString(2,10,"Day");
	//LCD_ShowNum(2,13,DS1302_Time[6],1);
	//LCD_ShowNum(2,13,TimeSetFlashFlag,2);
}
void TimeSet(void)
{
	//LCD_ShowNum(1,12,TimeSetSelect,2);
	if(TimeSetSelect == 0 && TimeSetFlashFlag == 1){LCD_ShowString(1,1,"  ");}
	else{LCD_ShowNum(1,1,DS1302_Time[0],2);}
	if(TimeSetSelect == 1 && TimeSetFlashFlag == 1){LCD_ShowString(1,4,"  ");}
	else{LCD_ShowNum(1,4,DS1302_Time[1],2);}
	if(TimeSetSelect == 2 && TimeSetFlashFlag == 1){LCD_ShowString(1,7,"  ");}
	else{LCD_ShowNum(1,7,DS1302_Time[2],2);}
	if(TimeSetSelect == 3 && TimeSetFlashFlag == 1){LCD_ShowString(2,1,"  ");}
	else{LCD_ShowNum(2,1,DS1302_Time[3],2);}
	if(TimeSetSelect == 4 && TimeSetFlashFlag == 1){LCD_ShowString(2,4,"  ");}
	else{LCD_ShowNum(2,4,DS1302_Time[4],2);}
	if(TimeSetSelect == 5 && TimeSetFlashFlag == 1){LCD_ShowString(2,7,"  ");}
	else{LCD_ShowNum(2,7,DS1302_Time[5],2);}
	
	
	
	
	
	if(KeyNumber==2)
	{
		TimeSetSelect++;
		TimeSetSelect%=6;
	}
	if(KeyNumber==3)
	{
		DS1302_Time[TimeSetSelect]++;
		if(DS1302_Time[0]>99){DS1302_Time[0] =0;}
		if(DS1302_Time[1]>12){DS1302_Time[1] =1;}
		
		if(DS1302_Time[0]%100==0||DS1302_Time[0]%4==0)	//判断闰年
		{
			if(DS1302_Time[1]==2)
			{
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}
			}
			else
			{
				if(DS1302_Time[2]>MonthMaxDays[DS1302_Time[1]-1]){DS1302_Time[2] = 1;}
			}
		}
		else
		{
			if(DS1302_Time[1]==2)
			{
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}
			}
			else
			{
				if(DS1302_Time[2]>MonthMaxDays[DS1302_Time[1]-1]){DS1302_Time[2] = 1;}
			}
		}
		if(DS1302_Time[3]>23){DS1302_Time[3]=0;}
		if(DS1302_Time[4]>59){DS1302_Time[4]=0;}
		if(DS1302_Time[5]>59){DS1302_Time[5]=0;}
	}
	if(KeyNumber==4)
	{
		DS1302_Time[TimeSetSelect]--;
		if(DS1302_Time[0]<0){DS1302_Time[0] =99;}
		if(DS1302_Time[1]<1){DS1302_Time[1] =12;}
		
		if(DS1302_Time[0]%100==0||DS1302_Time[0]%4==0)	//判断闰年
		{
			if(DS1302_Time[1]==2)
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=29;}	//过小判断
				if(DS1302_Time[2]>29){DS1302_Time[2]=29;}	//过大判断
			}
			else
			{
				if(DS1302_Time[2]<1){DS1302_Time[2] = MonthMaxDays[DS1302_Time[1]-1];}
				if(DS1302_Time[2]>MonthMaxDays[DS1302_Time[1]-1]){DS1302_Time[2] = MonthMaxDays[DS1302_Time[1]-1];}
			}
		}
		else
		{
			if(DS1302_Time[1]==2)
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=28;}
				if(DS1302_Time[2]>28){DS1302_Time[2]=28;}
			}
			else
			{
				if(DS1302_Time[2]<1){DS1302_Time[2] = MonthMaxDays[DS1302_Time[1]-1];}
				if(DS1302_Time[2]>MonthMaxDays[DS1302_Time[1]-1]){DS1302_Time[2] = MonthMaxDays[DS1302_Time[1]-1];}
			}
		}
		if(DS1302_Time[3]<0){DS1302_Time[3]=23;}
		if(DS1302_Time[4]<0){DS1302_Time[4]=59;}
		if(DS1302_Time[5]<0){DS1302_Time[5]=59;}
	}
	//设置完后更新显示
}


void main()
{
	LCD_Init();
	DS1302_Init();
	DS1302_SetTime();
	LCD_ShowString(1,3,"-");
	LCD_ShowString(1,6,"-");
	LCD_ShowString(2,3,":");
	LCD_ShowString(2,6,":");
	Timer0_Init();
	while(1)
	{
		KeyNumber =Key();
		if(KeyNumber==1)
		{
			if(MODE==0){MODE = 1;}
			else if(MODE==1){MODE = 0;DS1302_SetTime();TimeSetSelect=0;}
		}
		switch(MODE)
		{
			case 0:TimeShow();break;
			case 1:TimeSet();break;
		}
		
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;//中断函数结束后,这个变量依然会存活
	//与全局变量的区别是,static后的只能该函数自己用
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	T0Count++;
	if(T0Count>=500)
	{
		T0Count=0;
		TimeSetFlashFlag = !TimeSetFlashFlag;

	}
	
}
