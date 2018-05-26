#ifndef _MODE_WATCH_H_
#define _MODE_WATCH_H_

#ifdef WATCH_MODE_FUNCTION
//130130Me01***
void vWatchModeKey(void);
void vWatchModeKeyProcess(void);

void vWatchModeCheckTimer(void);	
void vWatchZoneExecute(BYTE bZone);
void vAutoFanZoneJudge(void);		//130418Ja01
//130130Me01&&&
void vAutoFanChangeTimer10s(void);		//130418Ja01
extern BYTE bAdjustAutoFanVolumeRem;			//130427Ja01
extern BYTE bLastWatchZone;		//130504Me01
extern WORD	wWatchModeCheckTimercnt;		//130504Me01
#else
#define vWatchModeKey()
#define vWatchModeKeyProcess()
#define vWatchModeCheckTimer()
#define vWatchZoneExecute(bZone)
#define vAutoFanZoneJudge(void)			//130418Ja01
#define vAutoFanChangeTimer10s()		//130418Ja01

#endif




#endif
