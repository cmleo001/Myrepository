#ifndef _MODE_MONITOR_H_
#define _MODE_MONITOR_H_

#ifdef MONITOR_MODE_FUNCTION
void vMonitorModeInitial(void);	//130123ra01
void vMonitorModeKeyProcess(void);	//130123ra01
void vMonitorModeTimer1s(void);	//130123ra01

extern BYTE bMonitorModeState;		//130123ra01
extern BOOL fgDetectValueUpdate;	//130123ra01
#else
#define vMonitorModeInitial()
#define vMonitorModeKeyProcess()
#define vMonitorModeTimer1s()	//130123ra01

#endif



#endif
