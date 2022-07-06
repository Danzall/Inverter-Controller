/*
 * LCD.h
 *
 *  Created on: Oct 28, 2019
 *      Author: Jeefo
 */

#ifndef LCD_H_
#define LCD_H_

typedef enum{
	Data = 1,
	Instruction
} I_D;

typedef enum{
	Initalize = 1,
	ClearScreen,
	SelectLine,
	WriteData,
	Three,
	ADE
} LCD_State;

#define LINE1 0x80
#define LINE2 0xC0
void LCD_Init();
void LCD_Service();
void LCD_Send(I_D control, char* data, int len);
void LCD_Print(char* data);
void ClearScreenF();
void LineSelect(int in);
#endif /* LCD_H_ */
