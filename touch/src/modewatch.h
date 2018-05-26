#ifndef _MODE_WATCH_H_
#define _MODE_WATCH_H_

extern BOOL fgDisplayLEDAirVolume1To9;

#ifdef WATCH_MODE_FUNCTION
												
void vWatchModeZoneChange(void);	//130130Me01
void vWatchModeKey(void);
void vWatchModeKeyProcess(void);
void vSetWatchMode(BYTE bwatch_mode);//130308Me01
void vDangerAirDisplay(void);

#else
#define vWatchModeZoneChange()		//130130Me01
#define vWatchModeKey()
#define vWatchModeKeyProcess()
#define vSetWatchMode(bwatch_mode)		//130308Me01
#define vDangerAirDisplay()


#endif



#endif
