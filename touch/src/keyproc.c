#define _KEYPROC_C_
#include "general.h"

BYTE _bKeyState=KEY_NORMAL;

/*	//130307ha02
void vPowerKey(void)
{
//130306a02v**

	if(bPowerMode==POWER_MODE_OFF)		
		{
		vPowerOnMode();
		}
	else if(bPowerMode==POWER_MODE_ON)
		{
		vPowerOffMode();
		}
//130306a02v&&&
}
*/	//130307ha02

//130305Ke01***
//BOOL fgDigitalIndicationShow=FALSE;	//The display of "Digital Indication"---1-1-1-1  flag
//BOOL fgFirstOscillateOn=FALSE; //Power on after inserting a plug into a socket  //130412Ke04
//BOOL fgAngleLEDOn=TRUE;
//130305Ke01&&&
#if 0	//130412Ti01***
//130312Ke02***
void vAirVolumeKeyProcess(void)
{
	//At power off mode, WatchMode or OnTimerMode can adjust air volume.
	if(fgIsInPowerOffMode())	//130402Ke02***
		{
		if(fgIsNotWatchMode()&&fgIsNotTimerOnOffFunction()	)
			{
			return;
			}
		}	//130402Ke02&&&

//	if((bWatchMode==WATCH_MANUAL)&&(bPowerMode==POWER_MODE_OFF))//130327Ke06  //130402Ke02
//		return;	//130402Ke02

//	if((bWatchMode!=WATCH_MANUAL)&&(bPowerMode==POWER_MODE_OFF)&&(bTimerMode==TIMER_MODE_OFF))//130327Ke06  //130402Ke02
//		return; //130402Ke02

	if(fgIsInPowerOnMode())//130327Ke06***
		{
		vFanVolumeSet(bAirVolume); 		
		}	//130327Ke06&&&

	vMcuEepromWriteByte(EE_AIR_VOLUME,bAirVolume);	//130306Ke01  //130325Ke03
	//When in watch Mode low temperature and in on timer set,set air volume,LED display just 5sec
	if(fgIsInTimerOnOffFunction())//130327Ke04
		{
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_5_SECOND);
		//vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_5_SECOND); //130327Ke04		// 130415jac02
		vDisplayLEDAirVolumeAutoOff(bAirVolume,DISPLAY_TIME_5_SECOND );//130401Ke01
		}
	else if(!fgOscillateInitialProcess)//130327Ke05	//130409Ke06
		{
		vDisplayLEDAngleSettingIndicationOff();	//130409Ke08
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);
		//vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);  //130327Ke04		// 130415jac02
		vDisplayLEDAirVolumeOn(bAirVolume);//130401Ke01	//130409Ke01
		}
}
//130312Ke02&&&
#endif	//130412Ti01&&&

#define AUTO_FAN_CONTROL	//130418ha01
INT8 bAirVolumeStore;		//130418ha01	//130426Ja01
BYTE bee_air_volume;	//130427Ja01
#define bAirVolumeOffset	(bAdjustAutoFanVolume-4)	//130418ha01
//Update air volume control addition/decrease/1to33key to one function	//130412Ti01***
void vAirVolumeControl(void)
{
	BYTE NormalFineControlGap;//130313Ke01  Select AirVolumeKey or FineControlKey,4 or 1 addtion/decrease.
	//BYTE bee_air_volume;	//130418ha01	//130422Ja01//130427Ja01
	BYTE bair_volume_max;	//130418ha01
	if(fgIsInPowerOnMode())
		{	//Power On Mode
#ifdef AUTO_FAN_CONTROL	//130418ha01***
		bair_volume_max=AIR_VOLUME_MAX;
		if((fgIsInWatchMode()))
			{
			if(bWatchZone==ZONE_DANGER)
				{
				if(((bIRKey==IR_TOUCH_AIR_VOLUME)&&(fgTouchIsFirstPress==TRUE))||(bIRKey!=IR_TOUCH_AIR_VOLUME))	//130407Me02***
					{
					if(bIRKey!=IR_AIR_VOLUME_CONTROL)	//130429Ja01
						{
						if(fgIRFineNotPressContinue==TRUE)	//130429Ja01
							{
							vBuzzerOutput(PI_PI_PI);
							}
						}
					}		//130407Me02&&&
				return;
				}
			//If air volume is 33(Max), don't execute AutoFanControl.
			if(bAirVolume>=AIR_VOLUME_MAX)
				{
				bAdjustAutoFanVolume=AUTO_FAN_NORMAL;
				}
			}
		else
			{
			bAdjustAutoFanVolume=AUTO_FAN_NORMAL;
			//bWatchModeAutoFanStatus=AUTO_FAN_NORMAL;
			}
#else	//130418ha01&&&
		if((fgIsInWatchMode())&&(bWatchZone==ZONE_DANGER))
			{
			if(((bIRKey==IR_TOUCH_AIR_VOLUME)&&(fgTouchIsFirstPress==TRUE))||(bIRKey!=IR_TOUCH_AIR_VOLUME))	//130407Me02***
				{
				vBuzzerOutput(PI_PI_PI);
				}		//130407Me02&&&
			return;
			}
#endif	//130418ha01
		}
	else
		{	//Power Off Mode
		if(fgIsNotTimerOnOffFunction())
			{
			return;
			}
		}
	
	NormalFineControlGap=AIR_FINE_CONTROL_GAP;
	switch(bIRKey)
		{
		case IR_AIR_VOLUME_CONTROL_LO:
			NormalFineControlGap=AIR_NORMAL_CONTROL_GAP;
		case IR_FINE_CONTROL_LO:
			if(bAirVolume<=NormalFineControlGap)//130312Ke01
				{
				bAirVolume=AIR_VOLUME_MIN;
				vBuzzerOutput(PI_PI_PI);
				}
			else
			//Normal adjust, adjust gap is AIR_NORMAL_CONTROL_GAP
				{
				bAirVolume-=NormalFineControlGap;
				if(fgIRFineNotPressContinue==TRUE)	//130422le01
					{
					vBuzzerOutput(PI);
					}
				}
			break;
		case IR_AIR_VOLUME_CONTROL_HI:
			NormalFineControlGap=AIR_NORMAL_CONTROL_GAP;	
		case IR_FINE_CONTROL_HI:
#ifdef AUTO_FAN_CONTROL	//130418ha01***
			if(bAirVolume<bair_volume_max)	//130409Ke07***
				{
				bAirVolume+=NormalFineControlGap;
				if(fgIRFineNotPressContinue==TRUE)	//130422le01
					{
					vBuzzerOutput(PI);
					}
				}
			else
			//Normal adjust, adjust gap is AIR_NORMAL_CONTROL_GAP
				{
				vBuzzerOutput(PI_PI_PI);
				}	//130409Ke07&&&
#else	//130418ha01&&&
			if(bAirVolume<AIR_VOLUME_MAX)	//130409Ke07***
				{
				bAirVolume+=NormalFineControlGap;
				if(bAirVolume>AIR_VOLUME_MAX)
					{
					bAirVolume=AIR_VOLUME_MAX;
					}
				if(fgIRFineNotPressContinue==TRUE)	//130422le01
					{
					vBuzzerOutput(PI);
					}
				}
			else
			//Normal adjust, adjust gap is AIR_NORMAL_CONTROL_GAP
				{
				vBuzzerOutput(PI_PI_PI);
				}	//130409Ke07&&&
#endif	//130418ha01
			break;
		case IR_TOUCH_AIR_VOLUME:	
			bAirVolume=bIRKeySub;
			//Buzzer On Pi
			if(fgTouchIsFirstPress) //130326gr01***
				{
				vBuzzerOutput(PI);
				} //130326gr01&&&
			break;
		}
	//vAirVolumeKeyProcess();
#ifdef AUTO_FAN_CONTROL	//130418ha01***
	if(bIRKey==IR_AIR_VOLUME_CONTROL)
		{	//Air volume level change. (Auto fan control.)
		//If air volume is 33(Max), don't auto fan control.
		if(bAirVolume>=AIR_VOLUME_MAX)
			return;

		bair_volume_max=AIR_VOLUME_WATCH_MAX;
		bAirVolume=(BYTE)((INT8)bAirVolumeStore+(INT8)bAirVolumeOffset);
		}
	else
		{	//User press key to adjust the air volume.
		// 		bAirVolume = bAirVolumeStore + bAirVolumeOffset
		// ==>	bAirVolumeStore = bAirVolume - bAirVolumeOffset;
		bAirVolumeStore=(INT8)bAirVolume-(INT8)bAirVolumeOffset;

		bee_air_volume=bAirVolumeStore;	//130422Ja01
		if(bAirVolumeStore < (AIR_VOLUME_MAX+4) && fgIsInWatchMode()&&(bAdjustAutoFanVolume == AUTO_FAN_MINUS))	//130422Ja01	//130504Ja02
			bair_volume_max = AIR_VOLUME_WATCH_MAX;	//130422Ja01

		if(bee_air_volume>bair_volume_max && bee_air_volume < AIR_VOLUME_OVERFLOW)	//130422Ja01&&&
			{
			bee_air_volume=bair_volume_max;
			}
		else if(bee_air_volume<AIR_VOLUME_MIN || bee_air_volume > AIR_VOLUME_OVERFLOW)
			{
			bee_air_volume=AIR_VOLUME_MIN;
			}

		vMcuEepromWriteByte(EE_AIR_VOLUME,bee_air_volume);	//130306Ke01  //130325Ke03
		bair_volume_max = AIR_VOLUME_MAX;
		}	//130422Ja01&&&
		
	if(bAirVolume>bair_volume_max && bAirVolume < AIR_VOLUME_OVERFLOW)	//130422Ja01&&&
		{
		bAirVolume=bair_volume_max;
		}
	else if(bAirVolume<AIR_VOLUME_MIN || bAirVolume > AIR_VOLUME_OVERFLOW)
		{
		bAirVolume=AIR_VOLUME_MIN;
		}	//130422Ja01&&&

	if(fgIsInPowerOnMode())//130327Ke06***
		{
		vFanVolumeSet(bAirVolume);
		}	//130327Ke06&&&

	vDisplayLEDAirVolumeOn(bAirVolume);
	//When in watch Mode low temperature and in on timer set,set air volume,LED display just 5sec
	if((bIRKey!=IR_AIR_VOLUME_CONTROL) || (bIRKeySub == SHOW_THE_AIR_VOLUME))	//130427Ja01	//130502Ja01
		{
		if((fgIsInTimerOnOffFunction())&&(fgIsInPowerOffMode()))//130327Ke04
			{
			vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_5_SECOND);
			vDisplayLEDAirVolumeAutoOff(bAirVolume,DISPLAY_TIME_5_SECOND );//130401Ke01
			}
		else if(!fgOscillateInitialProcess)//130327Ke05	//130409Ke06
			{
			vDisplayLEDAngleSettingIndicationOff();	//130409Ke08
			vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);
			}
		}
#else	//130418ha01&&&

	if(fgIsInPowerOnMode())//130327Ke06***
		{
		vFanVolumeSet(bAirVolume); 		
		}	//130327Ke06&&&

	vMcuEepromWriteByte(EE_AIR_VOLUME,bAirVolume);	//130306Ke01  //130325Ke03
	vDisplayLEDAirVolumeOn(bAirVolume);
	//When in watch Mode low temperature and in on timer set,set air volume,LED display just 5sec
	if((fgIsInTimerOnOffFunction())&&(fgIsInPowerOffMode()))//130327Ke04
		{
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_5_SECOND);
		//vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_5_SECOND); //130327Ke04
		vDisplayLEDAirVolumeAutoOff(bAirVolume,DISPLAY_TIME_5_SECOND );//130401Ke01
		}
	else if(!fgOscillateInitialProcess)//130327Ke05	//130409Ke06
		{
		vDisplayLEDAngleSettingIndicationOff();	//130409Ke08
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);
		//vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);  //130327Ke04
//		vDisplayLEDAirVolumeOn(bAirVolume);//130401Ke01	//130409Ke01
		}
#endif	//130418ha01
	fgOscillateAngleIsShowing=FALSE;  //130419Ju01
}//130412Ti01&&&

void vOscillateMoveToCentral(void)	//130412Ke04***
{
	fgOscillateAngleShowEnable=TRUE;	//130422Ke01
	fgOscillateInitialProcess=TRUE;
	vI2cSendCommand2Para(COMMAND_SUB_MAIN_OSCILLATE_MODE,OSCILLATE_CENTRAL);
	//bPlugInACPowerTimeCount=0;
	vDisplayLEDAirVolumeSettingIndicationOff();
#ifdef FUNCTION_CHECKER_MODE_FUNCTION	//130429le01***
	if(bSpecialFunctionMode!=MODE_FUNCTION_CHECKER_TEST)
#endif	//130429le01&&&
		{
		vDisplayLEDAngleSettingIndicationOn();	
		}
}	//130412Ke04&&&


#if 0	//130412Ti01***
//130313Ke01***
void vAirVolumeControlDecrease(void)
{
	if(fgIsInPowerOffMode() && fgIsNotTimerOnOffFunction() )	//130312vi04***
		{
		return;
		}			//130312vi04&&&

	//130309Ke09***
	if(bWatchZone==ZONE_DANGER)//If in danger zone,set fan volume is invalid,buzzer sound PiPiPi
		{
		vBuzzerOutput(PI_PI_PI);
		return;
		}
	//130309Ke09&&&

	NormalFineControlGap=(bIRKey==IR_AIR_VOLUME_CONTROL_LO)?AIR_NORMAL_CONTROL_GAP:AIR_FINE_CONTROL_GAP;
	if(bAirVolume<=NormalFineControlGap)//130312Ke01
		{
		bAirVolume=AIR_VOLUME_MIN;
		vBuzzerOutput(PI_PI_PI);
		}
	else
	//Normal adjust, adjust gap is AIR_NORMAL_CONTROL_GAP
		{
		bAirVolume-=NormalFineControlGap;
		vBuzzerOutput(PI);
		}
	vAirVolumeKeyProcess();
}

void vAirVolumeControlAdditon(void)
{
	if(fgIsInPowerOffMode()&&fgIsNotTimerOnOffFunction()	)	//130312vi04***
		{
		return;
		}			//130312vi04&&&

	//130309Ke09***
	if(bWatchZone==ZONE_DANGER)//If in danger zone,set fan volume is invalid,buzzer sound PiPiPi
		{
		vBuzzerOutput(PI_PI_PI);
		return;
		}
	//130309Ke09&&&

	NormalFineControlGap=(bIRKey==IR_AIR_VOLUME_CONTROL_HI)?AIR_NORMAL_CONTROL_GAP:AIR_FINE_CONTROL_GAP;	
//	bAirVolume+=NormalFineControlGap;
//	//if air volume is exceed the max air volume,adjust air volume as the AIR_VOLUME_MAX,and buzzer PiPiPi
//	if(bAirVolume>=AIR_VOLUME_MAX)
//		{
//		bAirVolume=AIR_VOLUME_MAX;
//		vBuzzerOutput(PI_PI_PI);
//		}
//	else
	//Normal adjust, adjust gap is AIR_NORMAL_CONTROL_GAP
//		{
//		vBuzzerOutput(PI);
//		}
	
	//130409Ke07***
	if(bAirVolume<AIR_VOLUME_MAX)
		{
		bAirVolume+=NormalFineControlGap;
		if(bAirVolume>AIR_VOLUME_MAX)
			{
			bAirVolume=AIR_VOLUME_MAX;
			}
		vBuzzerOutput(PI);
		}
	else
	//Normal adjust, adjust gap is AIR_NORMAL_CONTROL_GAP
		{
		vBuzzerOutput(PI_PI_PI);
		}
	//130409Ke07&&&
	vAirVolumeKeyProcess();
}
//130313Ke01&&&
#endif	//130412Ti01&&&

#if 0
void vAirVolumeControlLoKey(void)
{
	//bAirVolume=bMcuEepromReadByte(EE_AIR_VOLUME);	//130306Ke01
	if((bPowerMode==POWER_MODE_OFF)&&(bTimerMode==TIMER_MODE_OFF))	//130312vi04***
		{
		return;
		}			//130312vi04&&&

	//130309Ke09***
	if(ZONE_DANGER)//If in danger zone,set fan volume is invalid,buzzer sound PiPiPi
		{
		vBuzzerOutput(PI_PI_PI);
		return;
		}
	//130309Ke09&&&

	//if air volume is below the minimal  air volume,adjust air volume as the AIR_VOLUME_MIN,and buzzer PiPiPi
	if(bAirVolume<=AIR_NORMAL_CONTROL_GAP)//130312Ke01
		{
		bAirVolume=AIR_VOLUME_MIN;
		vBuzzerOutput(PI_PI_PI);
		}
	else
	//Normal adjust, adjust gap is AIR_NORMAL_CONTROL_GAP
		{
		bAirVolume-=AIR_NORMAL_CONTROL_GAP;
		vBuzzerOutput(PI);
		}
	
	vAirVolumeKeyProcess();//130312Ke02
	
	//130309Ke08***
	if((bWatchZone==ZONE_VIRUS)&&(bTimerMode!=TIMER_MODE_OFF))//When in watch Mode low temperature and in on timer set,set air volume,LED display just 5sec
		{
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_5_SECOND);
		}
	else
		{
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);
		}
	//130309Ke08&&&

}

void vAirVolumeControlHiKey(void)
{
	//bAirVolume=bMcuEepromReadByte(EE_AIR_VOLUME);	//130306Ke01
	if((bPowerMode==POWER_MODE_OFF)&& (bTimerMode==TIMER_MODE_OFF))	//130312vi04***
		{
		return;
		}			//130312vi04&&&

	//130309Ke09***
	if(ZONE_DANGER)//If in danger zone,set fan volume is invalid,buzzer sound PiPiPi
		{
		vBuzzerOutput(PI_PI_PI);
		return;
		}
	//130309Ke09&&&

	bAirVolume+=AIR_NORMAL_CONTROL_GAP;
	//if air volume is exceed the max air volume,adjust air volume as the AIR_VOLUME_MAX,and buzzer PiPiPi
	if(bAirVolume>=AIR_VOLUME_MAX)
		{
		bAirVolume=AIR_VOLUME_MAX;
		vBuzzerOutput(PI_PI_PI);
		}
	else
	//Normal adjust, adjust gap is AIR_NORMAL_CONTROL_GAP
		{
		vBuzzerOutput(PI);
		}

	vAirVolumeKeyProcess();//130312Ke02
	
	//130309Ke08***
	if((bWatchZone==ZONE_VIRUS)&&(bTimerMode!=TIMER_MODE_OFF))//When in watch Mode low temperature and in on timer set,set air volume,LED display just 5sec
		{
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_5_SECOND);
		}
	else
		{
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);
		}
	//130309Ke08&&&

}


void vFineControlLoKey(void)
{
	//bAirVolume=bMcuEepromReadByte(EE_AIR_VOLUME);	//130306Ke01
	if((bPowerMode==POWER_MODE_OFF)&& (bTimerMode==TIMER_MODE_OFF))	//130312vi04***
		{
		return;
		}			//130312vi04&&&

	//130309Ke09***
	if(ZONE_DANGER)//If in danger zone,set fan volume is invalid,buzzer sound PiPiPi
		{
		vBuzzerOutput(PI_PI_PI);
		return;
		}
	//130309Ke09&&&

	//if air volume is below the minimal  air volume,adjust air volume as the AIR_VOLUME_MIN,and buzzer PiPiPi
	if(bAirVolume<=AIR_VOLUME_MIN)
		{
		bAirVolume=AIR_VOLUME_MIN;
		vBuzzerOutput(PI_PI_PI);
		}
	else
	//Fine adjust, adjust gap is AIR_FINE_CONTROL_GAP
		{
		bAirVolume-=AIR_FINE_CONTROL_GAP;
		vBuzzerOutput(PI);
		}
	
	vAirVolumeKeyProcess();//130312Ke02
	
	//130309Ke08***
	if((bWatchZone==ZONE_VIRUS)&&(bTimerMode!=TIMER_MODE_OFF))//When in watch Mode low temperature and in on timer set,set air volume,LED display just 5sec
		{
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_5_SECOND);
		}
	else
		{
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);
		}
	//130309Ke08&&&
	
}

void vFineControlHiKey(void)
{
	//bAirVolume=bMcuEepromReadByte(EE_AIR_VOLUME);	//130306Ke01
	if((bPowerMode==POWER_MODE_OFF)&& (bTimerMode==TIMER_MODE_OFF))	//130312vi04***
		{
		return;
		}			//130312vi04&&&

	//130309Ke09***
	if(ZONE_DANGER)//If in danger zone,set fan volume is invalid,buzzer sound PiPiPi
		{
		vBuzzerOutput(PI_PI_PI);
		return;
		}
	//130309Ke09&&&

	//if air volume is below the minimal  air volume,adjust air volume as the AIR_VOLUME_MIN,and buzzer PiPiPi
	if(bAirVolume>=AIR_VOLUME_MAX)
		{
		bAirVolume=AIR_VOLUME_MAX;
		vBuzzerOutput(PI_PI_PI);
		}
	else
	//Fine adjust, adjust gap is AIR_FINE_CONTROL_GAP
		{
		bAirVolume+=AIR_FINE_CONTROL_GAP;
		vBuzzerOutput(PI);
		}

	vAirVolumeKeyProcess();//130312Ke02

	//130309Ke08***
	if((bWatchZone==ZONE_VIRUS)&&(bTimerMode!=TIMER_MODE_OFF))//When in watch Mode low temperature and in on timer set,set air volume,LED display just 5sec
		{
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_5_SECOND);
		}
	else
		{
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);
		}
	//130309Ke08&&&
	
}
//130116Ke01&&&
#endif

//130305Ke01***
void vOscillatingAngleKey(void)
{
	//When Power is OFF or On-Time is set,this key is invalid.
	if(fgIsInPowerOffMode())
		{
		return;
		}

	//But before reaching the initial position and until moving to the central position, 
	// operating "Horizontal Oscillating Button" or "Oscillating Angle Button" 
	//is invalid and the buzzer sounds "PiPiPi".	
	if((!fgOscillateInitialFinish)||(bOscillatingMode==OSCILLATE_OFF))//130313Ke01
		{
		vBuzzerOutput(PI_PI_PI);//PiPiPi
		return;
		}
	/*//130313Ke01
	//If "Rotation Mode" is "OFF", operating this button is invalid and the buzzer sounds "PiPiPi".
	if(bOscillatingMode==OSCILLATE_OFF)
		{
		vBuzzerOutput(PI_PI_PI);
		return;
		}
	*/

	fgOscillateAngleShowEnable=TRUE;	//130418Ke04
	
	
	//When LED on
	vDisplayLEDAirVolumeSettingIndicationOff();
	if(fgOscillateAngleIsShowing)	//130412Ke04	//130419Ju01
		{
		//Change the angle
		vIONModeSetting();			//130423jac01	
		bOscillatingModeAngle++;
		if(bOscillatingModeAngle>OSCILLATE_120D)	//130322ha01
			{
			bOscillatingModeAngle=OSCILLATE_15D;	//130322ha01
			}
		//130418Ju01***
		/*vOscillateModeSet(bOscillatingModeAngle);	//130412Ke04
		if(bOscillatingModeAngle==OSCILLATE_15D)
			{
			vBuzzerOutput(PI_PI);
			}
		else
			{
			vBuzzerOutput(PI);
			}
		*/	//130418Ju01&&&
		vMcuEepromWriteByte(EE_OSCILLATE_MODE_ANGLE, bOscillatingModeAngle);	//130322ha01
		}
	//When LED off

	/*else	//130419Ju01***
		{
		fgOscillateAngleIsShowing=TRUE;	//130412Ke04
		//vBuzzerOutput(PI);//130401Ke02                 //130418Ju01
		//vOscillateModeSet(bOscillatingModeAngle);	//130412Ke04          ////130418Ju01
		}	*/	//130419Ju01&&&

	//130418Ju01***
	vOscillateModeSet(bOscillatingModeAngle);	//130412Ke04
	if(bOscillatingModeAngle==OSCILLATE_15D)
		{
		vBuzzerOutput(PI_PI);
		}
	else
		{
		vBuzzerOutput(PI);
		}
	//130418Ju01&&&
}
//130305Ke01&&&
//130305Ke02***
//Every 25ms.
void vDigitalIndicationShowTimer(void)
{
	static BYTE DigitalShowCount=0;
	if((fgOscillateInitialProcess)&&fgIsInPowerOnMode())	//130409Ke06	//130412Ke04
		{
		if(DigitalShowCount == 8)
			{
			vDisplay7SegShowLeftOn();
			}		
		if(DigitalShowCount == 16)
			{
			vDisplay7SegShowLeftMiddleOn();
			}		
		if(DigitalShowCount == 24)
			{
			vDisplay7SegShowRightMiddleOn();
			}		
		if(DigitalShowCount == 32)
			{
			vDisplay7SegShowRightOn();
			DigitalShowCount=0;
			}	
		DigitalShowCount++;
		}
}
//130305Ke02&&&

void vLouverAngleKey(void)
{//130307ro01***

	if(fgIsInPowerOffMode())//130312vi04***
		{
		return;
		}			//130312vi04&&&

	//if((!fgLouverInitialFinish)||fgOscillateInitialProcess)	//130328ro02***	//130409Ke02     //130418Ju02
	if(!fgLouverInitialFinish)        //130418Ju02
		{
		vBuzzerOutput(PI_PI_PI);
		return;
		}	//130328ro02&&&
	vDisplayLEDAirVolumeSettingIndicationOff();//130409Ke02
	//vDisplayLEDAngleSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);     //130308ro01	// 130415jac02
	
	if(bLouverMode==LOUVER_SWING)
		{
		bLouverMode=LOUVER_STOP;
		vMcuEepromWriteByte(EE_LOUVER_MODE,bLouverMode);          //130312ro01
		//vDisplay7SegShowHorizontalAutoOff(DISPLAY_TIME_10_SECOND);    //130308ro01    //130418Ju02
		bLouverAngle=LOUVER_HORIZONTAL_1;
		//vLouverModeSet(LOUVER_HORIZONTAL_1);             //130418Ju02
		vBuzzerOutput(PI_PI);                                    //130308ro02
		}
	else
		{
		if(bLouverAngle>=LOUVER_LOWER20D)	 //130402ro03***//130422gr01
			{
			bLouverAngle=LOUVER_HORIZONTAL_1;
			}
		else
			{
			bLouverAngle++;					//130402ro03&&&
			}
#if 1
		//130314Ke03***
		if((bLouverAngle==LOUVER_HORIZONTAL_1)||(bLouverAngle==LOUVER_HORIZONTAL_3))	//||(bLouverAngle==LOUVER_HORIZONTAL_3))	//130322ha02   //130328ro03
			{
			vBuzzerOutput(PI_PI);     
			}
		else	// if((bLouverAngle==LOUVER_UPPER40D)||(bLouverAngle==LOUVER_LOWER20D))	//130322ha02
			{
			vBuzzerOutput(PI);
			}
		//vDisplayLEDshow;
		//130418Ju02***
		/*vDisplay7SegShowLouverAngleAutoOff(bLouverAngle, DISPLAY_TIME_10_SECOND);
		vLouverModeSet(bLouverAngle);*/
		//130418Ju02&&&

		//130314Ke03&&&
#endif
#if 0 
		bLouverAngle++;
		switch(bLouverAngle)
			{
			default:
				bLouverAngle=LOUVER_HORIZONTAL_1;
			case LOUVER_HORIZONTAL_1:
				vDisplay7SegShowHorizontalAutoOff(DISPLAY_TIME_10_SECOND);  //130308ro01
				vLouverModeSet(LOUVER_HORIZONTAL_1);
				vBuzzerOutput(PI_PI);                            //130308ro02
				break;
			case LOUVER_UPPER40D:
				vDisplay7SegShowUpperAutoOff(DISPLAY_TIME_10_SECOND);    //130308ro01
				vLouverModeSet(LOUVER_UPPER40D);
				vBuzzerOutput(PI);
				break;
			case LOUVER_HORIZONTAL_3:
				vDisplay7SegShowHorizontalAutoOff(DISPLAY_TIME_10_SECOND);   //130308ro01
				vLouverModeSet(LOUVER_HORIZONTAL_3);
				vBuzzerOutput(PI_PI);                                    //130308ro02
				break;
			case LOUVER_LOWER20D:
				vDisplay7SegShowUnderLineAutoOff(DISPLAY_TIME_10_SECOND)	//130308ro01
				vLouverModeSet(LOUVER_LOWER20D);
				vBuzzerOutput(PI);                                    //130308ro02
				break;
			}
#endif
		vMcuEepromWriteByte(EE_LOUVER_ANGLE,bLouverAngle);          //130312ro01
		}

	//130418Ju02***
	//vDisplayLEDshow
	if(!fgOscillateInitialProcess)
		{
		vDisplay7SegShowLouverAngleAutoOff(bLouverAngle, DISPLAY_TIME_10_SECOND);
		}
	fgOscillateAngleIsShowing=FALSE;  //130419Ju01
	vLouverModeSet(bLouverAngle);
	//130418Ju02&&&
}
//130307ro01&&&

//130305Ke02***
//After power on, first press this key, the oscillate motor will go to central, we need to set timeout time.
void vHorizontalOscillatingKey(void)
{
	//When Power is OFF or On-Time is set,this key is invalid.
	if(fgIsInPowerOffMode())
		{
		return;
		}

	if(fgOscillateInitialProcess)	//130327Ke03	//130409Ke06
		{
		vBuzzerOutput(PI_PI_PI);//130327Ke03
		return;
		}
	//130412Ke04***
	vIONModeSetting();			//130423jac01	
	fgOscillateAngleShowEnable=TRUE;	//130418Ke04
	
	//HorizontalOscillatingKey is valid.
	if(bOscillatingMode==OSCILLATE_OFF) 
		{//Let the oscillate On. 
		//Buzzer On Pi
		vBuzzerOutput(PI);
		vDisplayLEDAirVolumeSettingIndicationOff();
			
		//bOscillatingModeAngle=bMcuEepromReadByte(EE_OSCILLATE_MODE_ANGLE);	//130418Ke02
		vOscillateModeSet(bOscillatingModeAngle);
			
		bOscillatingMode=OSCILLATE_ON;
		}
	//HoriztontalMotor PowerOff
	else
		{	//Let the oscillate Off.
		bOscillatingMode=OSCILLATE_OFF;
		vOscillateModeSet(OSCILLATE_OFF);//130325Ke02
		//Buzzer on PiPi
		vBuzzerOutput(PI_PI);
		vMcuEepromWriteByte(EE_OSCILLATE_MODE_ANGLE, OSCILLATE_OFF_MEMORIZED);
		}
	vMcuEepromWriteByte(EE_OSCILLATE_MODE_ON_OFF, bOscillatingMode);	//130322ha03
	//130412Ke04&&&
}
//130305Ke02&&&

void vVerticalDirectionKey(void)
{//130307ro02***
	if(fgIsInPowerOffMode())	//130312vi04***
		{
		return;
		}			//130312vi04&&&

	//if((!fgLouverInitialFinish)||fgOscillateInitialProcess)	//130328ro02***	//130409Ke03    //130418Ju02
	if(!fgLouverInitialFinish)       //130418Ju02
		{
		vBuzzerOutput(PI_PI_PI);
		return;
		}	//130328ro02&&&
	vDisplayLEDAirVolumeSettingIndicationOff();//130409Ke03
	//vDisplayLEDAngleSettingIndicationOff();	//130401ro01     //130418Ju02
	if(!fgOscillateInitialProcess)  //130418Ju02
		{
		vDisplay7SegShowLouverAngleOff();	//130401ro01    
		}//130418Ju02
	//fgAngleLEDOn=FALSE;//130411Ju01
	fgOscillateAngleIsShowing=FALSE;//130419Ju01
	if(fgVerticalMotorOn==TRUE)	//130424Me01
		{
		bLouverMode=LOUVER_STOP;
		//vMcuEepromWriteByte(EE_LOUVER_MODE, bLouverMode);	//130329ro01    //130418Ju02
		vMcuEepromWriteByte(EE_LOUVER_ANGLE, LOUVER_OFF_MEMORIZED);	//130402ro01
		bLouverAngle=LOUVER_OFF_MEMORIZED;	//130329ro01 //130402ro01 //130422gr01

		vBuzzerOutput(PI_PI);
		}
	else
		{	//Louver STOP
		bLouverMode=LOUVER_SWING;
		bLouverAngle=LOUVER_LOWER20D;	 //130411ro02

		vBuzzerOutput(PI);
		}
	vLouverModeSet(bLouverMode);
	vMcuEepromWriteByte(EE_LOUVER_MODE, bLouverMode);	//130322ha04

}
//130307ro02&&&

#if 0	//130412Ti01***
//130307Ke01***
void vAirVolumeControl1To33Key(void)
{
	bAirVolume=bIRKeySub;

	//130312Ke03***
	if(bWatchZone==ZONE_DANGER)//If in danger zone,set fan volume is invalid,buzzer sound PiPiPi
		{
		if(fgTouchIsFirstPress==TRUE)	//130407Me02***
			{
			vBuzzerOutput(PI_PI_PI);
			}		//130407Me02&&&
		return;
		}//130312Ke03&&&

	if(fgIsInPowerOffMode()&& fgIsNotTimerOnOffFunction())	//130312vi04***
		{
		return;
		}			//130312vi04&&&

	//130312Ke03&&&
	vAirVolumeKeyProcess();//130313Ke01
	//Fan Volume set as bAirVolume
	//vFanVolumeSet(bAirVolume);//130313Ke01

#if 0	//130408Ke04
	//Show Number  and off after 10s
	if(fgIsNotTimerOnOffFunction())
		{
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume,DISPLAY_TIME_10_SECOND);	//130326Ke05
		vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);
		}
	else
		{
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume,DISPLAY_TIME_5_SECOND);	//130326Ke05
		vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_5_SECOND);
		}
#endif	//130408Ke04
	//Show touch LED 
	//vDisplayLEDAirVolumeOn(bAirVolume );//130313Ke01

	//Buzzer On Pi
	if(fgTouchIsFirstPress) //130326gr01***
		{
		vBuzzerOutput(PI);
		} //130326gr01&&&
	//vMcuEepromWriteByte(EE_AIR_VOLUME,bAirVolume);//130313Ke01

}
//130307Ke01&&&
#endif	//130412Ti01&&&


void vNormalModeKeyProcess(void)
{
	switch(bIRKey)
		{
		//Remote Key
		case IR_TIMER:
		case IR_TOUCH_TIMER:
			vIONModeSetting();//130413lo01
			vTimerKey();
			break;
		case IR_ION_MODE:
			vIONModeKey();
			break;
		case IR_AIR_VOLUME_CONTROL_HI:		//130423jac01***
		case IR_FINE_CONTROL_HI:
			if(bIonMode==ION_CLOTHING_DEODORANT)	
				{
				vIONModeSetting();
				}
			vAirVolumeControl();
			break;		//130423jac01&&&
		case IR_AIR_VOLUME_CONTROL_LO:
		case IR_FINE_CONTROL_LO:
			//vAirVolumeControlDecrease();	//130412Ti01***
			//break;	
		case IR_TOUCH_AIR_VOLUME:	
			vIONModeSetting();//130413lo01
		case IR_AIR_VOLUME_CONTROL:	//130418ha01
			//vAirVolumeControlAdditon();	
			vAirVolumeControl();	//130412Ti01&&&
			break;
		case IR_OSCILLATING_ANGLE:
			//vIONModeSetting();//130413lo01		//130423jac01
			vOscillatingAngleKey();
			break;
		case IR_LOUVER_ANGLE:
			vIONModeSetting();//130413lo01
			vLouverAngleKey();
			break;
		case IR_HORIZONTAL_OSCILLATING:
		case IR_TOUCH_HORIZONTAL_OSCILLATING:
			//vIONModeSetting();//130413lo01		//130423jac01
			vHorizontalOscillatingKey();
			break;
		case IR_VERTICAL_DIRECTION:
		case IR_TOUCH_VERTICAL_DIRECTION:
			vIONModeSetting();//130413lo01
			vVerticalDirectionKey();
			break;
		case IR_WATCH_MODE:
		case IR_TOUCH_WATCH_MODE:
			vWatchModeKey();
			break;
			
		//Touch Key
//		case IR_TOUCH_RESET:
			//vResetKey();			//130306a01v
//			break;
		//case IR_TOUCH_AIR_VOLUME:	//130412Ti01***
			//vAirVolumeControl1To33Key();	
			//break;	//130412Ti01&&&

		//Special or Hot Key
#ifdef PRODUCTION_LINE_MODE_FUNCTION
		case IR_PRODUCTION_LINE_MODE:
			vProductionLineModeInitial();
			break;
#endif
#ifdef FUNCTION_CHECKER_MODE_FUNCTION
		case IR_FUNCTION_CHECKER_TEST_MODE:
			vFunctionCheckerModeInitial();
			break;
#endif
//		case IR_SPEED_UP_MODE:
//			vSpeedUpModeInitial();
//			break;
		case IR_SERVICE_MONITOR_MODE:
			vServiceMonitorModeInitial();
			break;
		case IR_MONITOR_MODE:
			vMonitorModeInitial();
			break;
		case IR_DEMO_MODE:
			vDemoModeInitial();
			break;

		case IR_CHILD_LOCK:
			vChildLock();
			break;
		case IR_LIGHT_OFF_FUNCTION:
			vLightOff();	//130326st01
			break;
		case IR_AUTO_RESTART_FUNCTION:
			vAutoRestartKey();	//130306le01
			break;
		case IR_FILTER_CLEANING:
			vResetFilterCleaningKey();	//130306a01v
			break;
		}
}


//All key statsu common key.
void vComKeyProc(void)
{
	switch(bIRKey)
		{
		case IR_POWER:
		case IR_TOUCH_POWER:
			if(bPowerOnOffTimerCount<POWER_ON_OFF_VALID_TIME)//130420sh01***//power key is allowed only 0.5s past since the last power key is executed.
				{
				bIRKey=IR_NONE;
				return;
				}	//130420sh01&&&

		//vPowerKey();
			//130307ha02**
			if(bErrorMode!=ERROR_NONE)//130326vi01***
				{
				//bErrorMode=ERROR_NONE;		//130408vi01 delete	
				//fgAbnormalMode=FALSE;	//130408vi01 delete	
				if(fgOnOffTimerReach==TRUE)		//130412vi01****	
					{
					}
				else								//130412vi01&&&	
					{
					fgExecutePowerOffMode=TRUE;
					break;
					}
				}//130326vi01&&&

			if(fgIsInMonitorMode())
				{
				return;
				}
#ifdef FUNCTION_CHECKER_MODE_FUNCTION  //130423gr02***
			else if(fgIsInFunctionCheckerTestMode())
				{
				return;
				}
#endif
#ifdef PRODUCTION_LINE_MODE_FUNCTION				
			else if(fgIsInProductionLineMode())
				{
				return;
				}
#endif
			//if(fgIsInFunctionCheckerTestMode() ||fgIsInMonitorMode() || fgIsInProductionLineMode())	//130328le01***  //130417ma02
				//{
				//return;
				//}	//130328le01&&&//130423gr02&&&
			//130417ma02

			if(fgIsInPowerOffMode())		
				{
				if(fgIsInDemoMode())  //130327ma02
					{
					return;
					}
				else if(fgIsInServiceMonitorMode())
					{
					bSpecialFunctionMode=MODE_NORMAL;
					vSetKeyState(KEY_NORMAL);
					vSubMcuSendSpecialMode(bSpecialFunctionMode);
					fgExecutePowerOffMode=TRUE;	//130321ha01
					//vPowerOffMode();	//130321ha01
					return;
					}
				
				fgExecutePowerOnMode=TRUE;
				//vPowerOnMode();
				}
			else if(fgIsInPowerOnMode())
				{
				fgExecutePowerOffMode=TRUE;	//130321ha01
				//vPowerOffMode();	//130321ha01
				}
			//130307ha02&&&
			break;
		//case IR_POWER_OFF:
			//fgExecutePowerOffMode=TRUE;	//130321ha01
			//vPowerOffMode();	//130306a02v	//130321ha01
			//break;
		}
}

void vEventKeyProcess(void)
{
	if(bIRKey==IR_NONE)
		return;

	//when watch zone is Danger zone or PreCaution zone,the "warning buzzer" is sounding,within 30s,
	//operate any key can stop the "warning buzzer" immediately and the key is invalid at first time.
	if((fgWarningBuzzerStart==TRUE)&&(bIRKey != IR_AIR_VOLUME_CONTROL))	//130411le01***	//130422Ja01
		{
		fgWarningBuzzerStart=FALSE;
		vBuzzerOutput(PI_OFF);
		return;
		}	//130411le01&&&

	vComKeyProc();

	//Judge the hotkey function.
	///////////////////////////////////////////////
	vHotKeyInput();	//130123gr03

	if(fgIsChildLockFunction())	//130309le01***
		{
		if(bIRKey!=IR_CHILD_LOCK)
			{
			return;
			}
		}	//130309le01&&&


	switch(bKeyState())
		{
		default:
			vSetKeyState(KEY_NORMAL);
		//case KEY_SPEED_UP_MODE:
		case KEY_NORMAL:
			//If system abnormal, all key is disable. Except Temp and Hudi error.
			if((fgAbnormalMode==TRUE)&&(bErrorMode!=ERROR_TEM_HUM_SENSOR))		//130313vi01***
				{
				break;		//130326vi01
				}		//130313vi01&&&
			vNormalModeKeyProcess();
			break;

		//Special function mode KeyState
		case KEY_DEMO_MODE:
			fgExecuteDemoMode=TRUE;	//130329ha01
			//vDemoModeKeyProcess();	//130329ha01
			return;	//130329ha01
#ifdef FUNCTION_CHECKER_MODE_FUNCTION
		case KEY_FUNCTION_CHECKER_MODE:
			fgExecuteFunctionCheckerMode=TRUE;	//130329ha01
			//vFunctionCheckerModeKeyProcess();	//130329ha01
			return;	//130329ha01
#endif
		case KEY_MONITOR_MODE:
			fgExecuteMonitorMode=TRUE;	//130329ha01
			//vMonitorModeKeyProcess();	//130329ha01
			return;	//130329ha01
#ifdef PRODUCTION_LINE_MODE_FUNCTION
		case KEY_PRODUCTION_LINE_MODE:
			vProductionLineModeKeyProcess();
			break;
#endif
		case KEY_SERVICE_MONITOR_MODE:
			vServiceMonitorModeKeyProcess();
			break;
#if 0	//130413lo01
		case KEY_WATCH_OR_ION_MODE:
			//vNormalModeKeyProcess();	//130306Me01
			//vWatchModeKeyProcess();
			if((fgAbnormalMode==TRUE)&&(bErrorMode!=ERROR_TEM_HUM_SENSOR))	//130408vi02***//196 205
				{
				break;	
				}				//130408vi02&&&
			if(fgIsInIonMode())
				{
				vIONModeKeyProcess();
				}
			else
				{
				vNormalModeKeyProcess();//130312Bi01;
				}
			break;
#endif	//130413lo01			
/*			
		case KEY_WATCH_MODE_WITH_BUZZER:
		case KEY_WATCH_MODE_WITHOUT_BUZZER:
			vWatchModeKeyProcess();
			break;
		case KEY_ION_PLASMACLUSTER_SHOWER_MODE:
		case KEY_ION_CLOTHING_DEODORANT_MODE:
			vIONModeKeyProcess();
			break;
*/
		}
	bIRKey=IR_NONE;
}


