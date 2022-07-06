/*
 * Wifi.h
 *
 *  Created on: Sep 4, 2020
 *      Author: Jeefo
 */

#ifndef WIFI_H_
#define WIFI_H_

void Wifi_Init();
void Wifi_Service();
void WifirecData();
void WifiprocData();
void Wifi_Receive(char in);
void Wifi_Send(char* data);
void WifiOK();

typedef enum{
	Wifi_version = 1,
	Wifi_AT,
	ListAP,
	GetIP,
	CheckConnect,
	Connect,
	AT,
	IP_Stat,
	CPMUX,
	ServerOn,
	ServerOff,
	Dial,
	IP_Send,
	IP_Data,
	Close_Socket

}Wifi_State;

typedef struct{
	char connect;
	char list;
	char ip;
	char print;
}WifiFlag;


#endif /* WIFI_H_ */
