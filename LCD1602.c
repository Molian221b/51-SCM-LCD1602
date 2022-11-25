#include <reg52.h>
sbit LCD_RS = P3^5;
sbit LCD_RW = P3^6;
sbit LCD_EN = P3^4;
#define LCD_DataPort P0

void LCD_Delay()		//@12.000MHz  1毫秒延迟
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}


void LCD_WriteCommand(unsigned char Command){
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DataPort = Command;
	LCD_EN = 1;
	LCD_Delay();
	LCD_EN = 0;
	LCD_Delay();
}

void LCD_WriteData(unsigned char Data){
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_DataPort = Data;
	LCD_EN = 1;
	LCD_Delay();
	LCD_EN = 0;
	LCD_Delay();
}

void LCD_SetCursor(unsigned char Line, unsigned char Column){
	if(Line==1){
		//设置光标地址，也就是说RS=0时，P0的命令不但可以设置光标显示等，还可以设置光标位置
		LCD_WriteCommand(0x80|(Column-1));
	}else if(Line==2){
		LCD_WriteCommand(0x80|(Column-1)+0x40);
	}
}

void LCD_ShowChar(unsigned char Line, unsigned char Column, unsigned char Char){
	LCD_SetCursor(Line, Column);
	LCD_WriteData(Char);
}

void LCD_ShowString(unsigned char Line, unsigned char Column, unsigned char *String){
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for(i=0;String[i]!='\0';i++){
		LCD_WriteData(String[i]);
	}
}

int LCD_Pow(int X, int Y){
	unsigned char i;
	int Result = 1;
	for(i=0;i<Y;i++){
		Result *= X;
	}
	return Result;
}

void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length){
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for(i=Length;i>0;i--){
			LCD_WriteData(Number/LCD_Pow(10,i-1)%10+0x30);
		//LCD_WriteData(Number/LCD_Pow(10,i-1)%10+'0'); 这种写法也行，'0'的ASCII码就是0x30,注意区别0x00的那个'\0'
	}
}

void LCD_ShowSignedNum(unsigned char Line, unsigned char Column, int Number, unsigned char Length){
	unsigned char i;
	unsigned int Number1; //使用unsigned int Number1是为了防止Numaber出现-32768取反后超出int范围的情况
	LCD_SetCursor(Line, Column);
	if(Number>=0){
		LCD_WriteData('+');
		Number1 = Number;
	}else{
		LCD_WriteData('-');
		Number1 = -Number;
	}
	for(i=Length;i>0;i--){
			LCD_WriteData(Number1/LCD_Pow(10,i-1)%10+0x30);
		//LCD_WriteData(Number1/LCD_Pow(10,i-1)%10+'0'); 这种写法也行，'0'的ASCII码就是0x30,注意区别0x00的那个'\0'
	}
}

void LCD_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length){
	unsigned char i;
	unsigned int SingleNumber;
	LCD_SetCursor(Line, Column);
	for(i=Length;i>0;i--){
		SingleNumber = Number/LCD_Pow(16,i-1)%16;
		if(SingleNumber<10){
			LCD_WriteData(SingleNumber+0x30);
		//LCD_WriteData(SingleNumber+'0');
		}else{
			LCD_WriteData(SingleNumber-10+0x41);//-10是为了排除A-F原本偏离的数字
		//LCD_WriteData(SingleNumber-10+'A');
		}
	}
}

void LCD_ShowBinNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length){
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for(i=Length;i>0;i--){
			LCD_WriteData(Number/LCD_Pow(2,i-1)%2+0x30);
		//LCD_WriteData(Number/LCD_Pow(2,i-1)%2+'0'); 这种写法也行，'0'的ASCII码就是0x30,注意区别0x00的那个'\0'
	}
}

void LCD_Init(){
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x0c);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x01);
}
