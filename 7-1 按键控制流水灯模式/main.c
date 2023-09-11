#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>
unsigned char KeyNum,LEDMode;

void main()
{
	P2 = 0xFE;//1111 1110点亮最低位
	Timer0_Init();
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			if(KeyNum==1)
			{
				LEDMode++;
				if(LEDMode>=2)LEDMode = 0;
			}

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
		if(LEDMode==0){P2 = _cror_(P2,1);}
		if(LEDMode==1){P2 = _crol_(P2,1);}
	}
	
}