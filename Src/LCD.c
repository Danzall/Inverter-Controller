/*
 * LCD.c
 *
 *  Created on: Oct 28, 2019
 *      Author: Jeefo
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
//#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
//#include "GSM.h"
#include "LCD.h"
/* USER CODE END Includes */

I_D Control;
LCD_State lcdState = Initalize;
char LCD[15];
extern I2C_HandleTypeDef hi2c1;

void LCD_Init(){
	LCD[0] = 0x00;
	LCD[1] = 0x38;			//Function
	LCD[2] = 0x00;
	LCD[3] = 0x39;			//Function
	LCD[4] = 0x14;			//Oscillator
	LCD[5] = 0x74;
	LCD[6] = 0x54;
	LCD[7] = 0x6F;
	LCD[8] = 0x0C;
	LCD[9] = 0x01;
	LCD[10] = 0x00;
	//HAL_I2C_Master_Transmit(&hi2c1, 0xCB, LCD, 11, 10);
	LCD_Send(Instruction, LCD,11);
	Debug_Send("LCD initialize\r\n");
}

void LCD_Service(){
	Debug_Send("LCD service\r\n");
	switch(lcdState){
	case Initalize:
		LCD_Init();
		lcdState = ClearScreen;
		break;
	case ClearScreen:
		//LCD_Send(I_D control, char* data)
		Debug_Send("Clear screen\r\n");
		ClearScreenF();
		//LCD_Print("test123456789 10");
		//LCD_Send(Data,"Test",strlen("Test"));
		Debug_Send("Screen cleared\r\n");
		lcdState = SelectLine;

		break;
	case SelectLine:
		//LCD_Send(Instruction, 0x80,1);
		LineSelect(0x80);
		LCD_Print("One ");
		Debug_Send("LCD one\r\n");
		lcdState = WriteData;
		break;
	case WriteData:
		//LCD_Send(Instruction, 0xC0,1);
		LineSelect(0xC0);
		LCD_Print("Two ");
		Debug_Send("LCD two\r\n");
		lcdState = Three;

		break;
	case Three:
		LCD_Print("Three");
		lcdState = ADE;
		lcdState = ClearScreen;
		break;
	case ADE:
		LCD_Print("Three");
		//ADE_Get();
		char temp[20];
		char ade[5];
		//ade = ADE_Get();
		Debug_Send("ADE:");
		myLongStr(ade[0],temp,10,10);
		//Debug_Send(ADE_Get());
		Debug_Send("\r\n");
		lcdState = ClearScreen;
		break;

	}
}

void LCD_Send(I_D control, char* data, int len){
	char temp[20];
	int index = 1;
	int len1;
	int lenc;
	len1 = len + 1;
	//len1 = strlen(data);
	lenc = len1;
	//len1++;
	if (control == Instruction) temp[0] = 0x00;		//instruction
	else temp[0] = 0x40;							//data
	while (lenc){
		temp[index] = *data;
		data++;
		index++;
		lenc--;
	}
	//HAL_I2C_Master_Transmit(&hi2c1, 0x7C, temp, len1, 10);
	HAL_I2C_Master_Transmit(&hi2c1, 0x7C, temp, len1, 10);		//debug
}

void LCD_Print(char* data){
	int len;
	len = strlen(data);
	LCD_Send(Data, data, len);
}

void ClearScreenF(){
	LCD[0] = 0x00;		//instruction
	LCD[1] = 0x01;
	HAL_I2C_Master_Transmit(&hi2c1, 0x7C, LCD, 2, 10);
	int busy = 0;

	while(busy){
		HAL_I2C_Master_Receive(&hi2c1, 0x7C, LCD, 1, 20);
		if (LCD[0]&0x80) busy = 1;
		else busy = 0;

	}
	HAL_Delay(5);

}

void LineSelect(int in){
	LCD[0] = 0x00;		//instruction
	LCD[1] = in;
	HAL_I2C_Master_Transmit(&hi2c1, 0x7C, LCD, 2, 10);
	HAL_Delay(15);
}







