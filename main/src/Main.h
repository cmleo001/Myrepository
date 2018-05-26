#ifndef _MAIN_H_
#define _MAIN_H_




extern BOOL fgAbnormalMode;//130423vi01
extern BYTE bPowerMode;		//The Power mode of now. (Power ON,Power Off,Sleep mode)
extern BYTE bIonMode;
extern BYTE bWatchMode;
extern BYTE bWatchZone;
extern BOOL fgWatchZoneExecute;
//extern BYTE bLastWatchMode;
extern BYTE bSpecialFunctionMode;
extern BOOL fgSpeedUp;	//130407ra01

extern BYTE bAirVolume;	// 1~33

extern BYTE bOscillatingMode;
//extern BYTE bNowOscillatingMode;
extern BOOL fgOscillateMotorGoOneStep;
extern BYTE bOscillateModeSet;

extern BYTE bLouverMode;
extern BYTE bLouverAngle;
extern BOOL fgLouverMotorGoOneStep;

extern bit fgChildLockEnable;
extern BYTE bModeState;

#endif
