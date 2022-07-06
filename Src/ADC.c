/*
 * ADC.c
 *
 *  Created on: Jun 24, 2019
 *      Author: Jeefo
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
//#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
#include "GSM.h"
//#include "motor.h"
//#include "RTC.h"
#include "ADC.h"
#include "LCD.h"
#include "stdlib.h"
#include "string.h"
/* USER CODE END Includes */
extern ADC_HandleTypeDef hadc1;
uint32_t adc[20];
uint32_t Main_V;
uint32_t System_V;
uint32_t Main_I;
uint32_t Batt_V;
//uint32_t Vsys;
uint32_t counter = 0;
uint32_t V_max;
uint32_t V_min = 17000;
uint32_t V_thresh;
int diff;
char dbounce;

void ADC_Service(){
	//Debug_Send("ADCR start\r\n");
	HAL_ADC_Start_DMA(&hadc1, adc, 4);
	//Debug_Send("ADCR stop\r\n");
	//HAL_DMA_Start_IT(&hadc.*DMA_Handle, (uint32_t)&hadc.*Instance.DR, adc, 6);
	//HAL_DMA_PollForTransfer(&hadc.DMA_Handle, 1, 100);
	char temp[90];
	char temp1[10];
	//sprintf(temp, "1:%i  2:%i  3:%i  4:%i  5:%i  6:%i  7:%i  8:%i  9:%i\r\n",adc[0],adc[1],adc[2],adc[3],adc[4],adc[5],adc[6],adc[7],adc[8]);

	Main_V = GetVolt(adc[0]);	//10

	//Main_V *= 2;
	System_V = GetVolt(adc[1]);	//11 missing
	Main_I = GetVolt(adc[2]);	//13
	Batt_V = GetVolt(adc[3]);	//1

	if (Batt_V > V_max){
		diff = Batt_V - V_max;
		if(diff > 100) dbounce++;
		if (dbounce > 2){
			V_max = Batt_V;
			dbounce = 0;
		}

	}
	if (Batt_V < V_min) V_min = Batt_V;
	V_thresh = V_max - 50;
	if (Batt_V < V_thresh){
		dbounce++;
		if (dbounce > 2){
			V_max = Batt_V;
			dbounce = 0;
			HAL_GPIO_WritePin(SOL_CNTRL_GPIO_Port, SOL_CNTRL_Pin, GPIO_PIN_SET);
			GSM_Send("Charging done\r\n");
		}
		else{
			HAL_GPIO_WritePin(SOL_CNTRL_GPIO_Port, SOL_CNTRL_Pin, GPIO_PIN_RESET);
		}

		//SOL_CNTRL_Pin

	}
	else dbounce = 0;

	if (Batt_V > 14500){	//charge complete

	}
	if (Batt_V < 12300){	//

	}
	/*AC_I = GetVolt(adc[5]);
	AC_I_real = GetCurr(AC_I);
	Vin = GetVolt(adc[1]);
	Vin *= 11;
	Vsys = GetVolt(adc[0]);
	M_I = GetVolt(adc[6]);*/
	strcpy(temp, "1:");
	itoa(adc[0],temp1,10);
	strcat(temp,temp1);
	//strcat(temp,"  Main I:");
	strcat(temp,"  2:");

	itoa(adc[1],temp1,10);
	strcat(temp,temp1);
	//strcat(temp,"  Main I:");
	strcat(temp,"  3:");

	itoa(adc[2],temp1,10);
	strcat(temp,temp1);
	//strcat(temp,"  Main I:");
	strcat(temp,"  4:");

	itoa(adc[3],temp1,10);
	strcat(temp,temp1);
	//strcat(temp,"  Main I:");
	strcat(temp,"\r\n");
	//GSM_Send(temp);
	//sprintf(temp, "I:%i  AC:%i A real:%i\r\n",adc[6], adc[5], AC_I);
	//strcpy(temp, "Main V:"); //myStrLong(char *p_str,char p_base)
	strcpy(temp, "B:");
	itoa(Batt_V,temp1,10);
	strcat(temp,temp1);
	//strcat(temp,"  Main I:");
	strcat(temp,"  T:");
	//itoa(adc[0],temp1,10);
	itoa(V_thresh,temp1,10);
	//itoa(System_V,temp1,10);
	strcat(temp,temp1);
	//LineSelect(LINE1);
	//LCD_Print(temp);
	//GSM_Send(temp);
	//strcat(temp,"  System v:");
	strcat(temp," M:");
	//itoa(adc[2],temp1,10);
	itoa(V_max,temp1,10);
	strcat(temp,temp1);
	/*strcat(temp," S:");
	//itoa(adc[2],temp1,10);
	itoa(Batt_V,temp1,10);
	strcat(temp,temp1);*/
	//strcat(temp,"  Vbatt:");
	//strcat(temp,"  4:");
	//itoa(adc[3],temp1,10);
	//strcat(temp,temp1);
	itoa(counter,temp1,10);
	strcat(temp,"  C:");
	strcat(temp,temp1);
	strcat(temp,"\r\n");
	//LineSelect(LINE2);
	//LCD_Print(temp);
	counter++;
	if (counter == 4){
		V_max = Batt_V;
		V_min = Batt_V;
	}
	//while (HAL_ADC_PollForConversion(&hadc, 10) != HAL_OK);
	//adcval = HAL_ADC_GetValue(&hadc);
	//sprintf(temp1, "2:%i\r\n",adcval);
	//strcat(temp, temp1);
	//Debug_Send(temp);
	GSM_Send(temp);
}

uint32_t GetADC(){
	return Main_I;
}

uint32_t GetVolt(uint32_t in){
	float temp;
	uint32_t val;
	temp = in;
	//temp *= 0.8057;		//3.3v
	//temp *= 0.791;			//3.24v
	temp *= 0.798;			//3.27v
	temp *= 11;				//4.7kohm || 47kohm
	val = temp;
	val += 400;	//compensation
	return val;
}

uint32_t GetCurr(uint32_t in){
	in -= 1800;
	float current;
	uint32_t val;
	current = in * 1000;
	current /= 80;
	val = current;
	return val;

}

