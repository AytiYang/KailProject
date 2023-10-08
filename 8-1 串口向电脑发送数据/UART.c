#include <REGX52.H>
/**
  * @brief 串口初始化
  * @param  无
  * @retval 无
  */
void UART_Init()		//4800bps@12.000MHz
{	
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF4;			//设置定时初始值
	TH1 = 0xF4;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
}
/**
  * @brief 串口发送一个字节数据
  * @param  Byte,一个字节数据,16进制
  * @retval 无
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(T1==0);
	TI = 0;
}