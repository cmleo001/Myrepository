#ifndef _MAIN_H_
#define _MAIN_H_

 
extern BYTE bPowerMode;		//The Power mode of now. (Power ON,Power Off,Sleep mode)
extern BOOL fgExecutePowerOnMode;
extern BOOL fgExecutePowerOffMode;	//130321ha01
extern BYTE bPowerOnOffTimerCount;	//130420sh01
#define POWER_ON_OFF_VALID_TIME	5	//	5*0.1s=0.5s	//130420sh01


extern BYTE bIonMode;
extern BYTE bWatchMode;
extern BYTE bWatchZone;
//extern BOOL fgWatchModeError;	//130311Me01	//130411le01
//extern BYTE bWatchModeAutoFanStatus;	// (-4, 0 ,+4 ), but it's signed int. We change it to (0, 4, 8) become unsigned int.	//130418Ja01
extern BYTE bAdjustAutoFanVolume;	// (-4, -3, -2, -1, 0, 1, 2, 3, 4) but we change it to (0, 1, 2, 3, 4, 5, 6, 7, 8)	//130418Ja01

extern BYTE bSpecialFunctionMode;
extern BOOL fgExecuteDemoMode;		//130329ha01
extern BOOL fgExecuteFunctionCheckerMode;	//130329ha01
extern BOOL fgExecuteMonitorMode;	//130329ha01
extern BOOL fgSpeedUp;	//130407ra01

extern BYTE bOscillatingMode;
extern BYTE bOscillatingModeAngle;
extern BOOL fgOscillateAngleShowEnable;	//130418Ke04
extern BOOL fgOscillateAngleIsShowing;//130419Ju01

extern BYTE bLouverMode;	//130307ro03
extern BYTE bLouverAngle;	//130307ro03

//130309vi01***
//for abnormal mode		
extern BOOL fgAbnormalMode;		
extern BYTE bErrorMode;
extern BOOL fgErrorModeFirstPower;	
//130309vi01&&&

extern BYTE bIRKey;
extern BYTE bIRKeySub;	//130310ha01

extern BYTE bAirVolume;	// 1~33
extern BYTE bFanVolumeType;		//130424Ke03
extern BYTE bFanVolumeShowType;	//130424Ke03
extern BYTE bAirVolumeType;		 //130426jac01


extern BOOL fgChildLockEnable;
extern BOOL fgAutoRestartFunction;	//130306le01
extern BYTE bAutoRestartTimerCounter;	//130308le02
extern BOOL fgAutoRestartFirstPower;	//130327le01

extern BOOL fgLightOffFunction;	//130306le02
extern BOOL fgOscillateInitialFinish;//130305Ke02
extern BOOL fgOscillateInitialProcess;	//130409Ke06
extern BOOL fgLouverInitialFinish;    //130328ro02
extern BOOL fgPCIIsOverTime;		//130409Li02

extern BYTE bPlugInACPowerTimeCount;	//unit:0.1s, when AC power plug in, start to count.	//130123gr03	

//For Special Function Mode
extern BYTE bModeState;		//130306ra01
extern BYTE bModeTimeCount;	//130306ra01
#define vSpecialFunctionNextStep()	{bModeState++;}

//For On/Off Timer.
extern BYTE bTimerMode;	//130310ha02

//For Buzzer.
extern BYTE bBuzzerType;	//130321ha02
extern BYTE bLouverType;	//130325ha01
extern BYTE bOscillateType;	//130325ha01
extern BOOL fgWarningBuzzerStart;	//130411le01
extern BOOL fgVerticalMotorOn;		//130424Me01

#define SHOW_THE_AIR_VOLUME	0xFF	// Just used for IR_AIR_VOLUME_CONTROL.	//130502Ja01
void vPowerOnMode(void);
void vEnterPowerOffMode(void);
void vPowerOffMode(void);



#endif
