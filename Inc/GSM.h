/*
 * GSM.h
 *
 *  Created on: Apr 24, 2019
 *      Author: Jeefo
 */

#ifndef GSM_H_
#define GSM_H_

void GSM_Service();
void GSM_Send(char* data);
void Debug_Send(char* data);
void GSM_Init();
void sendSMS(char* num, char* msg);
void GSM_Receive(char in);
void recData();
void procData();
void OK();
void Context();
void checkGPRS();
void procSMS();
void buildInfo();
void buildTest();
void getSignal();
void caps(char* str);
void Error();
void pec_Update(char* pec, char index);
void GPRS_SendData(char* gprs);
void Socket1();
void DataStatus();
void DataDecrypt();
int Getvalue(char in);
void getIMEI();
void getCCID();
void Register();
void VoltageAlarm();
void Call();
void Balance();
void Network();
//void alarmFunc(Alarm input);
void Deny();
void GSM_Init();
char CheckUser();
void RegisterConfirm();
typedef enum{
	GSM_Off = 1,
	GSM_On,
	GSM_Enable,
	Search,
	SMSconfig,
	Operator,
	Imei,
	Ccid,
	GprsContext,
	GprsConfig,
	GprsConfig1,
	USSD_Config,
	USSD,
	CallerID,
	SMS_Check,
	SMS_Send,
	SMS_Text,
	GPRS_Attach,
	GPRS_On,
	GPRS_IP,
	GPRS_SS,
	GPRS_Off,
	SocketOpen,
	SocketClose,
	SMS_Del,
	Signal,
	SocketListen,
	SocketCheck,
	GPRS_Write,
	GPRS_Send,
	AutoBaud,
	DataMode,
	GPRS_Text
}State;


typedef struct{
	int signal;
	int config;
	int send;
	int prompt;
	int content;
	int context;
	int gprsPending;
	int gprsActive;
	int del;
	int reply;
	int restartCount;
	int socket;
}SMSflags;

typedef struct{
	char index[4];
	char recMSISDN[25];
	int prompt;
	char content1[180];
	char IP[30];
	int count;
	char build[160];
}SMSinfo;

typedef struct{
	char url[30];
	char urlport[6];
	char imei[40];
	char ccid[40];
	int socket1;
	//int socket2;
	//int socket3;
	//int socket4;
	int socket;
	int registered;
	int gprsDataPending;
	int userFlag;
	int msisdnFlag;
	int passwordFlag;
	int alarm;
	char user[15];
	char user1[15];
	//char user2[15];
	char msisdn[20];
	char password[15];
	char network[25];
	char balance[15];
	int low;
	char vth[10];
	int vth_l;
	int vthFlag;
	int relayFlag;
	int ccidFlag;
	int activeFlag;
	int updateFlag;
	int modeFlag;
	int vThreshold;
	int ccidStatus;
	int balanceFlag;
	int balancePending;
	int GPRStimer;
	int GPRSinterval;
	char GPRSint[10];
	int imeiFlag;
	int dataFlag;
	int GPRS_Rec;
}GSMinfo;
#endif /* GSM_H_ */
