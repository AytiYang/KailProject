#include <REGX52.H>


void Delay(unsigned int xms)		//@12.000MHz
{
	unsigned char data i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
	
}

void main()
{
	while(1)
	{
		if(P3_1==0)//这里实现的是按下按钮状态还没改变，只有松手
			//才改变状态
		{
			Delay(20);
			while(P3_1==0);
			Delay(20);
			P2_0 = ~P2_0;
		}
	}
}