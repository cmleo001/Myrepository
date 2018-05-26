#ifndef _UTILITY_H_
#define _UTILITY_H_

extern BOOL fgOnOffTimerReach;	//130327Ti01
//extern WORD wFilterCleanHour;	//130402ra02             //130423vi02
extern BOOL fgFilterNeedClean;	//130402vi01
extern BYTE bFilterCleanSec;	//130427ra01
extern BYTE bFilterCleanMin;	//130427ra01

void vChildLock(void);
void vLightOff(void);	//130306le02
void vAutoRestart(void);	//130306le03
void vAutoRestartKey(void);	//130306le01
void vAutoRestartFunction1sTimer(void);	//130308le02
void vAutoRestartFunctionWithin10s(void);	//130308le02

static WORD wFilterCleanHour	@0x99;		//130423vi02***
static BYTE bFilterCleanHourRegister[2] @0x99; //130423vi02&&&


void vLightDarkEvent(void);

void vTimerOnOffStop(void);		//130306a05v


void vFilterCleanTimer(void);	//130122su01
//void vResetKey(void);	//130122su01			//130306a01v
void vResetFilterCleaningKey(void);		//130306a01v
void vFilterCleanPowerCheck(void);	//130122su01//130402vi01

void vTimerShow(BYTE bTimer);	//130424vi01	
void vTimerKey(void);	//130125Ti01
void vSetOnOffTimer(BYTE bTimerMode);	//130309Ti01
void vOnOffTimer(void);		//130125Ti01

void vGiveHumidityADCValue(BYTE bdata1, BYTE bdata2);
void vGiveTemperatureADCValue(BYTE bdata1, BYTE bdata2);
void vGiveFanPWMValue(BYTE bdata1, BYTE bdata2);
void vGiveTemperatureValue(BYTE bdata1, BYTE bdata2);
void vGiveHumidityValue(BYTE bdata1, BYTE bdata2);
void vGiveIONVoltageValue(BYTE bdata1, BYTE bdata2);
void vGiveIONErrorCount(BYTE bdata1, BYTE bdata2);
void vGivePCIAccTimeValue(BYTE bdata1, BYTE bdata2);
void vOnOffTimerSetAtSpeedUp(void);


#endif
