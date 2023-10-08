#include <REGX52.H>
#include "Delay.h"
sbit RCK = P3^5;	//RCLK
sbit SCK = P3^6;	//SRCLK
sbit SER = P3^4;	//SER

#define MATRIX_LED_PORT P0
/**
  * @brief 74HC595写入一个字节
  * @param  一个字节
  * @retval 无
  */
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0;i<8;i++)
	{
	SER = Byte&(0x80>>i);
	SCK = 1;
	SCK = 0;
	}
	RCK = 1;	//将数据送到io
	RCK = 0;
//	SER = Byte&0x80;//&1000 0000,取Byte的最高位,原本SER是单个位,但是非0即1,
//					//所以这里SER被赋予1或0,而不是0x什么什么
//	SCK = 1;	//上升沿移位
//	SCK = 0;	//移位后复位0

}
/**
  * @brief LED点阵逐列显示
  * @param  列数,列样式(16进制数)
  * @param  高位在上,1为亮,0为灭
  * @retval 无
  */
void MatrixLED_ShowColumn(unsigned char Column,Data)//列,数据
{
	_74HC595_WriteByte(Data);
	MATRIX_LED_PORT = ~(0x80>>Column);
	Delay(1);	//延时
	MATRIX_LED_PORT = 0xFF;		//位选清零,防止残影
}
void MatrixLED_Init()
{
	SCK = 0;
	RCK = 0;
}