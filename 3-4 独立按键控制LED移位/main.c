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
	unsigned char LEDNum = 1;
	P2 = ~LEDNum;
	while(1)
	{
		if(P3_1==0)
		{
			Delay(20);
			while(P3_1==0);
			Delay(20);
			LEDNum=LEDNum<<1;
			if(LEDNum==0)
			{
				LEDNum = 1;
			}
			P2 = ~LEDNum;
		}
		if(P3_0==0)
		{
			Delay(20);
			while(P3_0==0);
			Delay(20);
			LEDNum=LEDNum>>1;
			if(LEDNum==0)
			{
				LEDNum = 128;
			}
			P2 = ~LEDNum;
		}
	}

}