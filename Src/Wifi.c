/*
 * Wifi.c
 *
 *  Created on: Sep 4, 2020
 *      Author: Jeefo
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "string.h"
#include "GSM.h"
#include "UART.h"
#include "LCD.h"
#include "Wifi.h"

//uint16_t onTimer = 0;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

#define WrecBuffSize 1300
#define WprocBuffSize 200
char WrecBuff[WrecBuffSize];
char WprocBuff[WprocBuffSize];
char WprocBuff1[WprocBuffSize];
int WrecBuffPointerWrite = 0;
int WrecBuffPointerRead = 0;
int WprocBuffpointer = 0;
Wifi_State WifiState = Wifi_AT;
WifiFlag wifiFlag;
uint8_t dummy[50];
uint8_t ssid[30] = "flying low";
//uint8_t ssid[30] = "TP-Link_5EDC";
uint8_t passwrd[30] = "underthedome";
//uint8_t passwrd[30] = "Danzall123";
uint8_t temp[130];
uint8_t IP1[100];
uint8_t HTML[] = "<!DOCTYPE html><html><head><style>.button {border: none;color: white;padding: 15px 32px;text-align: center;"
		"text-decoration: none;display: inline-block;font-size: 16px;margin: 4px 2px;cursor: pointer;}.button1 {background-color: #4CAF50;} /* Green */"
		".button2 {background-color: #008CBA;} /* Blue */</style></head><body><button class=\"button button1\">Green</button><button class=\"button button2\">Blue</button>"
		"</body></html>";
uint8_t HTML2[] = "<!DOCTYPE html><html><head></head><body><button class=\"button button1\">Green</button><button class=\"button button2\">Blue</button>"
		"</body></html>";
uint8_t HTML1[] = "<!DOCTYPE html><html><body><button>Dropdown</button></body></html>\r\n";
int len;
uint8_t temp1[500];
uint8_t ConnID[4];


void Wifi_Init(){
	GSM_Send("Wifi init\r\n");
	HAL_UART_Receive_IT(&huart2, (uint8_t *) dummy, 40);
	//HAL_UART_Receive_IT(&huart1, (uint8_t *) dummy, 40);
	//__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);

	//HAL_UART_Receive(&huart3, dummy, 50, 5);
	//strcpy(quality,"N/A");

	wifiFlag.connect = 0;
	wifiFlag.list = 0;
	wifiFlag.ip = 0;
	wifiFlag.print = 1;
	WifiState = GetIP;
	GSM_Send("Done\r\n");
	//WifiState = CPMUX;
}

void Wifi_Service(){
	//Wifi_Send("AT\r\n");
	//sprintf(temp, "Wifi service state-%i\r\n", WifiState);
	//GSM_Send(temp);
	//GSM_Send("Wifi service\r\n");
	switch(WifiState){
	case Wifi_version:
		Wifi_Send("AT+GMR\r\n");
		WifiState = Wifi_AT;
		WifiState = 0;
		break;
	case Wifi_AT:
		Wifi_Send("AT\r\n");
		WifiState = ListAP;
		WifiState = CheckConnect;
		//WifiState = CheckConnect;
		break;
	case ListAP:
		Wifi_Send("AT+CWLAP\r\n");
		//WifiState = GetIP;
		wifiFlag.list = 1;

		break;
	case GetIP:
		Wifi_Send("AT+CIFSR\r\n");
		//WifiState = AT;
		//WifiState = ListAP;
		wifiFlag.print = 0;
		WifiState = CPMUX;
		break;
	case CheckConnect:
		Wifi_Send("AT+CWJAP?\r\n");
		WifiState = 0;
		WifiState = ListAP;
		break;

	case Connect:
		strcpy(temp,"AT+CWJAP=");
		strcat(temp,"\"");
		strcat(temp,ssid);
		strcat(temp,"\",\"");
		strcat(temp,passwrd);
		strcat(temp,"\"");
		strcat(temp,"\r\n");
		Wifi_Send(temp);
		WifiState = 0;

		break;
	case AT:
		Wifi_Send("AT\r\n");
		WifiState = 0;
		break;
	case IP_Stat:
		Wifi_Send("AT+CIPSTATUS\r\n");

		break;
	case CPMUX:
		Wifi_Send("AT+CIPMUX=1\r\n");
		WifiState = ServerOn;
		break;

	case ServerOn:
		Wifi_Send("AT+CIPSERVER=1,5008\r\n");
		WifiState = 0;
		break;
	case ServerOff:
		Wifi_Send("AT+CIPSERVER=0\r\n");
		WifiState = 0;
		break;
	case Dial:
		Wifi_Send("AT+CIPSTART=\"TCP\",\"iot.espressif.cn\",8000\r\n");
		WifiState = 0;
		break;
	case IP_Send:
		len = strlen(HTML1);
		myLongStr(len , temp,10, 10);
		GSM_Send("HTML length is to send ");
		GSM_Send(temp);
		GSM_Send("\r\n");
		//Wifi_Send("AT+CIPSEND=<");
		strcpy((char*)temp,"AT+CIPSEND=");
		strcat((char*)temp,ConnID);
		strcat((char*)temp,",");
		myLongStr(len,temp1,10,10);
		strcat((char*)temp,temp1);
		strcat((char*)temp,"\r\n");
		Wifi_Send((char*)temp);
		//Wifi_Send(">\r\n");
		//Wifi_Send("AT+CIPSEND=<length>\r\n");
		WifiState = 0;
		break;
	case IP_Data:
		GSM_Send("Send data\r\n");
		strcpy((char*)temp1,HTML1);
		strcat((char*)temp1,"\r\n");
		Wifi_Send((char*)temp1);
		GSM_Send("Send data done\r\n");
		WifiState = 0;
		break;
	case Close_Socket:
		Wifi_Send("AT+CLOSE\r\n");
		WifiState = 0;
		break;
	}
}

void Wifi_Send(char* data){
	int size;
	int timeout = 5;
	size = strlen(data);
	HAL_UART_Transmit(&huart2, data, size, timeout);
	HAL_UART_Receive_IT(&huart2, (uint8_t *) dummy, 140);
	//HAL_UART_Transmit_IT(&huart3, data, size);
	//HAL_UART_Receive_IT(&huart1, data, size);
}


void WifirecData(){
	HAL_GPIO_TogglePin(LED2B0_GPIO_Port, LED2B0_Pin);
	//while (WrecBuffPointerWrite != WrecBuffPointerRead){
		if (WrecBuffPointerWrite != WrecBuffPointerRead){

			WprocBuff[WprocBuffpointer] = WrecBuff[WrecBuffPointerRead];
			WrecBuffPointerRead++;
			if (WrecBuffPointerRead > WrecBuffSize) WrecBuffPointerRead = 0;

			WprocBuffpointer++;
			if (WprocBuffpointer > WprocBuffSize) WprocBuffpointer = 0;

			if (WprocBuff[WprocBuffpointer - 1] == '>'){
				WifiState = IP_Data;
				/*if (gsmInfo.socket == 1) gsmState = GPRS_Write;
				if (gsmInfo.dataFlag == 1)gsmState = GPRS_Write;
				else gsmState = SMS_Text;*/
			}
			if (WprocBuff[WprocBuffpointer - 1] == 0x0A){
				WprocBuff[WprocBuffpointer - 1] = 0;
				WprocBuffpointer = 0;
				//GSM_Send(WprocBuff);
				//GSM_Send("\r\n");
				//GSM_Send("0x0A\r\n");
				//GSM_Send("1");
				WifiprocData();
			}
			if (WprocBuff[WprocBuffpointer - 1] == 0x0D){
				WprocBuff[WprocBuffpointer - 1] = 0;
				//WprocBuffpointer = 0;
				//GSM_Send(WprocBuff);
				//GSM_Send("\r\n");

				//
				//HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
				//GSM_Send("proc\r\n");
				//("0x0D\r\n");
				//GSM_Send("0x0D\r\n");
				//GSM_Send("2");
			}
		}
	//}
}

void WifiprocData(){
	//GSM_Send("Process Wifi msg\r\n");

	myStrSection(WprocBuff, temp1,30,',',1);
	if(strncmp((char*)temp1,"CONNECT",7)==0){
		myStrSection(WprocBuff, ConnID,30,',',0);
		sprintf(temp, "Conn %s connected\r\n",ConnID);
		GSM_Send(temp);
	}
	//GSM_Send(WprocBuff);
	//GSM_Send("\r\n");
	if(strncmp((char*)WprocBuff,"+CREG: 0,1",10)==0)HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	if(strncmp((char*)WprocBuff,"OK",2)==0) WifiOK();
	if(strncmp((char*)WprocBuff,"Ai",2)==0) WifiState = Wifi_version;
	if(strncmp((char*)WprocBuff,"No AP",5)==0) WifiState = Connect;

	if(strncmp((char*)WprocBuff,"WIFI CONNECTED",14)==0) WifiState = Connect;	//connected to AP
	if(strncmp((char*)WprocBuff,"WIFI GOT IP",10)==0) WifiState = GetIP;		//connected to AP
	if(strncmp((char*)WprocBuff,"no change",9)==0) WifiState = 0;		//server running

	if(strncmp((char*)WprocBuff,"+CWJAP:",7)==0){
		myStrSection(WprocBuff, temp,30,'"',1);
		if(strncmp(temp,ssid,5)==0) WifiState = GetIP;

	}
	if(strncmp((char*)WprocBuff,"+CIFSR:STAIP",12)==0){
		//GSM_Send(WprocBuff);
		//GSM_Send("\r\n");
		myStrSection(WprocBuff, IP1,30,'"',1);
		wifiFlag.print = 1;
		//strcpy(WprocBuff1,WprocBuff);
		/*if (wifiFlag.ip == 0){
			GSM_Send("Copy1\r\n");
			strcpy(IP1,WprocBuff);
		}
		if (wifiFlag.ip == 1){
			GSM_Send("Copy2\r\n");
			strcpy(IP2,WprocBuff);
		}
		if (wifiFlag.ip == 2){
			GSM_Send("Copy3\r\n");
			strcpy((char*)IP3,WprocBuff);
		}
		if (wifiFlag.ip == 3){
			GSM_Send("Copy4\r\n");
			strcpy(IP4,WprocBuff);
			//
		}*/
		wifiFlag.ip = 1;
	}
	if(strncmp((char*)WprocBuff,"+IPD",3)==0){
		GSM_Send("Got IPD\r\n");
		myStrSection(WprocBuff, temp1,30,':',1);
		myStrSection(WprocBuff, ConnID,30,',',1);
		//sprintf(temp, "%s,%i,%i\r\n",WprocBuff, WrecBuffPointerWrite, WrecBuffPointerRead);
		//GSM_Send(temp);
		WifiState = IP_Send;
		GSM_Send("Processed IPD\r\n");
		//int hlen;
		//hlen = strlen(HTML);
		//sprintf(temp, "Conn %s received:%s\r\n",ConnID, temp1);
		//GSM_Send(temp);
		wifiFlag.print = 0;
	}
	if (wifiFlag.print == 1){
		//sprintf(temp, "%s,%i,%i\r\n",WprocBuff, WrecBuffPointerWrite, WrecBuffPointerRead);
		//GSM_Send(temp);
	}
	wifiFlag.print = 1;
	//if(strncmp((char*)WprocBuff,"busy s...",9)==0) wifiFlag.print = 1;	//BUSY SENDING DATA
	//if(strncmp((char*)WprocBuff,"Recv 5 bytes",4)==0) wifiFlag.print = 1;	//DATA SENT
	if(strncmp((char*)WprocBuff,"SEND OK",7)==0){
		GSM_Send("SUCCESSFULLY SENT DATA\r\n");
		//wifiFlag.print = 1;	//SEND DONE
	}
}

void WifiOK(){
	//sprintf(temp, "%s,%i,%i,%i\r\n",WprocBuff, WrecBuffPointerWrite, WrecBuffPointerRead,wifiFlag.ip);
	//GSM_Send(temp);
	if(wifiFlag.list == 1){
		wifiFlag.list = 0;
		WifiState = GetIP;
	}
	if (wifiFlag.ip == 1){
		wifiFlag.ip = 0;
		GSM_Send(IP1);
		GSM_Send("\r\n");
		myStrSection(IP1, temp,30,'.',0);
		if (strncmp(temp,"0",1) != 0){
			wifiFlag.ip = 2;
			WifiState = CPMUX;
			GSM_Send("IP found\r\n");
		}
		else{
			GSM_Send("IP not found\r\n");
			WifiState = Connect;
		}
		/*GSM_Send(IP2);
		GSM_Send("\r\n");
		GSM_Send(IP3);
		GSM_Send("\r\n");
		GSM_Send(IP4);
		GSM_Send("\r\n");*/
	}
	GSM_Send("Got OK\r\n");
}
void Wifi_Receive(char in){
	//
	WrecBuff[WrecBuffPointerWrite] = (char)in;
	//HAL_UART_Transmit(&huart1, recBuff[recBuffPointerWrite], 2, 10);
	//huart1.Instance->TDR = in;
	WrecBuffPointerWrite++;
	if (WrecBuffPointerWrite > WrecBuffSize) WrecBuffPointerWrite = 0;

}
