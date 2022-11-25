#include <reg52.h>
#include "Delayms.h"
#include "LCD1602.h"

void main(){
	LCD_Init();
	LCD_ShowString(1,6,"Temp:250");
	LCD_ShowChar(1,14,0xdf);
	LCD_ShowChar(1,15,'C');
	LCD_ShowString(1,22,"\"BOOM!!!\"");
	LCD_ShowString(2,1,"What are you talking about?");
	LCD_ShowString(2,29,"Get out!");
	while(1){
		delayms(500);
		LCD_WriteCommand(0x18);//向左移屏
	}
}
