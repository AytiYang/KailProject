#include <REGX52.H>
#include "delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"


unsigned char KeyNum;
unsigned int pd[10];
unsigned int pd_in[10];
unsigned char i;
unsigned char j;
unsigned char length;
//1-9 对应数字,10对应0,
//11对应确认,12对应取消
//13-16闲置
void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	LCD_ShowString(2,1,"________________");
	pd[0] = 1;
	pd[1] = 1;
	pd[2] = 2;
	pd[3] = 7;
	length = 4;
	i=0;
	while(1)
	{
		KeyNum = MatrixKey();
		LCD_ShowNum(1,16,i,1);
		if(KeyNum)
		{
			if(KeyNum<=10)
			{
				pd_in[i] = KeyNum;
				//LCD_ShowNum(2,1,KeyNum,2);
				LCD_ShowNum(2,i,pd_in[i++],1);
			}
			else if (KeyNum == 11)
			{
				j = 0;
				while(j++<i)
				{
					if(pd_in[j]!=pd[j])break;
				}
				if(i<length||j<i)
				{
					LCD_ShowString(1,10,"Err!");
				}
				else
				{
					LCD_ShowString(1,10,"True");
				}
			}
			else if(KeyNum == 12)
			{
				LCD_ShowString(2,i--,"_");
			}
		}
		
	}
}