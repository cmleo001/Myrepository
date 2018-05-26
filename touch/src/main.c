#define _MAIN_C_
#include "general.h"

//Variable for Power
BYTE bPowerMode _AT_0X7F=POWER_MODE_OFF;		//The Power mode of now. (Power ON,Power Off,Sleep mode)
BYTE bPlugInACPowerTimeCount _AT_0X7E=0;	//unit:0.1s, when AC power plug in, start to count.	//130123gr03	
BOOL fgExecutePowerOnMode=FALSE;
BOOL fgExecutePowerOffMode=FALSE;	//130321ha01
BYTE bPowerOnOffTimerCount=0;	//Put in 100ms timer.	//130420sh01

//Variable for ION Mode
BYTE bIonMode _AT_0X7D=ION_MANUAL;

//Variable for Watch Mode
BYTE bWatchMode _AT_0X7C=WATCH_MANUAL;
BYTE bLastWatchMode _AT_0X7B=WATCH_MANUAL;
BYTE bWatchZone _AT_0X7A=ZONE_NORMAL;		//130401Me03
//BOOL fgWatchModeError =FALSE;				//130311Me01	//130411le01
//BYTE bWatchModeAutoFanStatus = AUTO_FAN_NORMAL;	// (-4, 0 ,+4 ), but it's signed int. We change it to (0, 4, 8) become unsigned int.	//130418Ja01
BYTE bAdjustAutoFanVolume = AUTO_FAN_NORMAL;	// (-4, -3, -2, -1, 0, 1, 2, 3, 4) but we change it to (0, 1, 2, 3, 4, 5, 6, 7, 8)	//130418Ja01


//Variable for Special function mode.(Demo Mode, Service Monitor Mode........)
BYTE bSpecialFunctionMode _AT_0X79=MODE_NORMAL;
BOOL fgExecuteDemoMode=FALSE;		//130329ha01
BOOL fgExecuteFunctionCheckerMode=FALSE;	//130329ha01
BOOL fgExecuteMonitorMode=FALSE;	//130329ha01
BOOL fgSpeedUp=FALSE;	//130407ra01

//Variable for Oscillate motor
BYTE bOscillatingMode _AT_0X78=OSCILLATE_OFF;			//OSCILLATE_ON, OSCILLATE_OFF
BYTE bOscillatingModeAngle _AT_0X77=OSCILLATE_15D;	//OSCILLATE_15D, OSCILLATE_30D, OSCILLATE_60D, OSCILLATE_90D, OSCILLATE_120D
BOOL fgOscillateInitialFinish=FALSE;	//130305Ke02	
BOOL fgOscillateInitialProcess=FALSE;	//130403Ke06	//130409Ke06
BOOL fgOscillateAngleShowEnable=FALSE;	//130418Ke04
BOOL fgOscillateAngleIsShowing=FALSE;//130419Ju01

BOOL fgLouverInitialFinish=FALSE;    //130328ro02
BOOL fgLouverPlugSocketInitial=TRUE;      //130329ro01
//Variable for Louver motor
//SWING or STOP
BYTE bLouverMode _AT_0X76=LOUVER_STOP;	 //130307ro03
//LOUVER_HORIZONTAL_1,	LOUVER_UPPER40D,	LOUVER_HORIZONTAL_3,	LOUVER_LOWER20D,
BYTE bLouverAngle _AT_0X75=LOUVER_HORIZONTAL_1;  //130307ro03
BOOL fgVerticalMotorOn=FALSE;	//130424Me01
 
//Variable for other function
BOOL fgChildLockEnable=FALSE;
BOOL fgAutoRestartFunction=FALSE;	//130306le01
BYTE bAutoRestartTimerCounter _AT_0X74=0;	//130308le02
BOOL fgAutoRestartFirstPower=FALSE;	//130327le01


BOOL fgLightOffFunction=FALSE;	//130306le02
BOOL fgPCIIsOverTime=FALSE;	//130409Li02

//130309vi01***
//for abnormal(error) mode   
//warning for Cleaning PCI UNIT Electrode
//Cover Open Error
//PCI Unit Connection Error
//Fan Motor Rotation Error
//Temperature and Humidity Sensor Error
//Microcomputer Communication Error
//PCI Unit Data Error
BOOL fgAbnormalMode=FALSE;
BYTE bErrorMode _AT_0X73=ERROR_NONE;
//BOOL fgErrorModeFirstPower=FALSE;		//abnormal mode first push power key//130326vi01
//130309vi01&&&

//Variable for Fan motor
BYTE bAirVolume _AT_0X72=AIR_VOLUME_DEFAULT_VALUE;	// 1~33
BYTE bFanVolumeType=FAN_VOLUME_NONE;	//For set air volume.//130424Ke03
BYTE bFanVolumeShowType=DISPLAY_TIME_NONE;	//130424Ke03
BYTE bAirVolumeType=FAN_VOLUME_NONE;	//For show air volume.	 //130426jac01
//Variable for Key
BYTE bIRKey _AT_0X71=IR_NONE;
BYTE bIRKeySub _AT_0X70=IR_NONE;	//130310ha01	//just for touch air volume key.

//For Special Function Mode
BYTE bModeState _AT_0X6F=0;	//130306ra01   搭ぶ跑秖计,盢┮ΤModeいノ ModeStateMachine参ノ bModeState蠢.
BYTE bModeTimeCount _AT_0X6E=0;	//130306ra01   搭ぶ跑秖计,盢┮ΤModeいノ ModeTimeCount 参ノ bModeTimeCount蠢.

//For On/Off Timer.
BYTE bTimerMode _AT_0X6D=TIMER_MODE_OFF;	//130310ha02

//For cover switch.

//For Buzzer.
BYTE bBuzzerType=PI_NONE;	//130321ha02
BYTE bLouverType=LOUVER_NONE;	//130325ha01
BYTE bOscillateType=OSCILLATE_NONE;	//130325ha01
BYTE bOscillateTypeStore;	//130412Ke04
	
BOOL fgWarningBuzzerStart=FALSE;	//130411le01

void vPowerOnMode(void)
{
	if(fgTouchInitial==TRUE)	//130415le01
		{
		return;	//130415le01
		}
	
	if(fgExecutePowerOnMode==FALSE)
		{
		return;
		}
	fgExecutePowerOnMode=FALSE;



//130306a02v***
	if(fgIsChildLockFunction())			//130308vi02***
		{
		if((fgAutoRestartFirstPower==TRUE)||(fgOnOffTimerReach==TRUE))//130402le01***	//130415Ti01***
			{
			vDisplayLEDChildLockSignOn();
			vDisplayLEDChildLockIndicationOn();
			}
		else
			{	//130402le01&&&
			return;
			}
		}					//130308vi02&&&
		
//130309vi01***	
#if 0//130326vi01
	if((bErrorMode!=ERROR_NONE)&&(fgErrorModeFirstPower==TRUE))		
		{
		fgErrorModeFirstPower=FALSE;
		vAbnormalModeCancel();	//130312vi03
		return;
		}				
	else
		{
		//fgAbnormalMode=FALSE;		130312vi03
		bErrorMode=ERROR_NONE;
		}
#endif//130326vi01
//130309vi01&&&

	bErrorMode=ERROR_NONE;		//130412vi01 	
	fgAbnormalMode=FALSE;		//130412vi01	 


	 vAutoRestartFunctionWithin10s();//130308vi03

		
	//vPowerOnPeripheralInitial();//no

	fgLouverInitialFinish=FALSE;   //130328ro02
	bPowerMode=POWER_MODE_ON_PROGRESS;
	vSubMcuSendPowerStatus(POWER_MODE_ON);
	

#ifndef MAIN_MCU_DO_POWER_ON_OFF_PROCESS
	
	vFanPower(TRUE);
	
#endif	
#if 0//130417sh01
	if(fgIsInWatchMode()||fgIsLightOffFunction())		//130329Li02***
		{	//Watch mode or Light off function
		}
	else
		{	//Not watch mode
		vDisplayLEDTubeWhiteOn();
		vDisplayLEDBright();
		}	//130329Li02&&&
#else
	if((fgIsNotWatchMode()||(fgLastLightSourceIsDark==FALSE))&&fgIsNotLightOffFunction()&&(fgPCIIsOverTime==FALSE))		
		{
		vDisplayLEDTubeWhiteOn();
		//vDisplayLEDBright();//130417sh02
		}
#endif//130417sh01

	//bWatchMode=bMcuEepromReadByte(EE_WATCH_MODE);	//130411Ti02
	if(fgIsInWatchMode())
		{
		vDisplayLEDAirVolume1BlinkOff();
		if(bWatchZone==ZONE_DANGER)		//130413Me01***
			{
			fgDisplayLEDAirVolume1To9=TRUE;
			vFanVolumeSet(AIR_VOLUME_MAX);		//130418Me01
			}		//130413Me01&&&
		}

	//bIonMode=bMcuEepromReadByte(EE_ION_MODE);  //130425lo01***
	//bIonMode=ION_MANUAL;  //130503lo01
	//vMcuEepromWriteByte(EE_ION_MODE, ION_MANUAL);  //130503lo01
//	if(fgIsInIonMode())
//		{
//		vModeIonManualInit();	//130413lo01
//		}
//	else  //130425lo01&&&
		{
		if(bWatchZone!=ZONE_DANGER)	//130418Me01
			{
			bAirVolume=bMcuEepromReadByte(EE_AIR_VOLUME);
			if(fgIsInWatchMode())	//130422Ja01
				{
				//if(fgAutoRestartFirstPower==FALSE)	//130425le01	//130426Ja01
					{
					vPutEventQueue(EVENT_IR, IR_AIR_VOLUME_CONTROL, SHOW_THE_AIR_VOLUME);	//130422Ja01 	//130502Ja01
					}
				}
			//vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);//JACKY define 100
			vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);//130327Ke02
			vDisplayLEDAirVolumeOn(bAirVolume );
			vFanVolumeSet(bAirVolume);
			}
		}

//The buzzer doesn't sound when the timer reach by setting on timer mode//130327Ti01***
	if((fgAutoRestartFirstPower==FALSE)&&(fgOnOffTimerReach==FALSE))	//130327le01	//130327Ti01	//130425le01***
		{
		vBuzzerOutput(PI);
		}
	else
		{
		fgAutoRestartFirstPower=FALSE;
		fgOnOffTimerReach=FALSE;
		}//130327Ti01&&&	//130425le01&&&

	vTimerOnOffStop();
	//130306a02v&&&
	/*if((bWatchMode !=WATCH_MANUAL)||(fgLightOffFunction==TRUE))		//130329Li02***	//130329Li02***
			{	//Watch mode or Light off function
			}
		else
			{	//Not watch mode
			vDisplayLEDTubeWhiteOn();
			vDisplayLEDBright();
		}	//130329Li02&&&*/	//130329Li02&&&
	bPowerMode=POWER_MODE_ON;	//130306a02v
	vFilterCleanPowerCheck();	//130122su01	//130402vi01
	vMcuEepromWriteByte(EE_POWER_MODE, bPowerMode);	//130308vi01	
	//bOscillatingMode=OSCILLATE_OFF;//130401Ke03 //130425lo01

	fgOscillateAngleShowEnable=FALSE;	//130418Ke04
	//130412Ke04***
	bOscillatingMode=bMcuEepromReadByte(EE_OSCILLATE_MODE_ON_OFF);
	if(bOscillatingMode==OSCILLATE_ON)
		{
		//bOscillatingModeAngle=bMcuEepromReadByte(EE_OSCILLATE_MODE_ANGLE);//130426Ju01
		vOscillateModeSet(bOscillatingModeAngle);
		}
	//130412Ke04&&&

	bPowerOnOffTimerCount=0;	//130420sh01

#if 0	//130412Ke04
	//130409Ke05***
	fgOscillateInitialProcess=bMcuEepromReadByte(EE_OSCILLATE_INITIAL_PROCESS);	//130409Ke06
	if(fgOscillateInitialProcess)	//130409Ke06
		{
		//vDisplayLEDWatchGreenOn();
		vDisplayLEDAirVolumeSettingIndicationOff();	
		vDisplayLEDAngleSettingIndicationOn();	
		vOscillateMoveToCentral();
		bPlugInACPowerTimeCount=0;	
		bOscillatingMode=OSCILLATE_ON;
		}
	else
		{
		bOscillatingMode=bMcuEepromReadByte(EE_OSCILLATE_MODE_ON_OFF);
		if(bOscillatingMode==OSCILLATE_ON)
			{
			bOscillatingModeAngle=bMcuEepromReadByte(EE_OSCILLATE_MODE_ANGLE);
			vDisplayLEDAirVolumeSettingIndicationOff();
			//vDisplayLEDAngleSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);
			vDisplay7SegShowOscillateAngleAutoOff(bOscillatingModeAngle, DISPLAY_TIME_10_SECOND);
			vOscillateModeSet(bOscillatingModeAngle);
			}
		}
	//130409Ke05&&&
#endif	//130412Ke04
}


void vPowerOffMode(void)
{
	if(fgExecutePowerOffMode==FALSE)	//130321ha01
		return;
	fgExecutePowerOffMode=FALSE;	//130321ha01

//130306a02v***
	bPowerMode=POWER_MODE_OFF_PROGRESS;
	vSubMcuSendPowerStatus(POWER_MODE_OFF);
	fgPCIIsOverTime=FALSE;	//130504Li02
	
	fgOscillateInitialProcess=FALSE;//130321Ke01	//130409Ke06	
	//vDisplayLEDAllOff();//130419gr01
	//vDisplay7segLedAllOff();//130419gr01
	vDisplay7segLedAndTouchLedAllOff();//130419gr01
	if(bLastWatchMode!=WATCH_MANUAL)//130417vi01*** 
		{
		vSetWatchMode(bLastWatchMode);
		bLastWatchMode=WATCH_MANUAL;	
		}//130417vi01&&& 

	//The buzzer doesn't sound when the timer reach by setting off timer mode//130327Ti01***
	if((fgOnOffTimerReach==FALSE)&&(fgAutoRestartFirstPower==FALSE))	//130327le01	//130327Ti01
		{
		vBuzzerOutput(PI_LONG);
		}
	else
		{
		fgOnOffTimerReach=FALSE;
		fgAutoRestartFirstPower=FALSE;	//130327le01
		}	//130327Ti01&&&

#ifndef MAIN_MCU_DO_POWER_ON_OFF_PROCESS
	vOscillateModeSet(OSCILLATE_OFF);	//Stop and memory the position.
	vOscillateModeSet(OSCILLATE_ALL_PIN_DISABLE);
	//vLouverModeSet(LOUVER_STOP);		//Stop and memory the position.
	vLouverModeSet(LOUVER_ALL_PIN_DISABLE);
	
	if(fgIsNotWatchMode())		//130308vi01	//130424le01	
		{
		vFanPower(FALSE);
		}
#endif	
	if(fgIsInWatchMode())	//130308vi01***	
		{
		//bAirVolume = AIR_VOLUME_MIN;	//130427Ti01	
		vDisplayLEDAirVolume1BlinkOn(DISPLAY_TIME_1_2_SECOND);
		vFanVolumeSet(AIR_VOLUME_MIN);
		
		vWatchModeZoneChange();	
		}               //130308vi01&&&

	fgAbnormalMode=FALSE;	//130408vi01***
	bErrorMode=ERROR_NONE;	//130408vi01&&&

	vTimerOnOffStop();
	if(fgIsChildLockFunction())	//130325vi01***
		{
		vDisplayLEDChildLockIndicationOn();
		vDisplayLEDChildLockSignOn();
		}	//130325vi01&&&
	bIonMode=ION_MANUAL;   //130503lo01
	vMcuEepromWriteByte(EE_ION_MODE, ION_MANUAL);   //130503lo01
	bPowerMode=POWER_MODE_OFF;
	vFilterCleanPowerCheck();	//130402vi01
	vMcuEepromWriteByte(EE_POWER_MODE, bPowerMode);	//130308vi01
//130306a02v&&&
	bPowerOnOffTimerCount=0;	//130420sh01
}

//130309vi01***
void vAbnormalModeCancel(void)
{
	vDisplay7SegMessageClear();
	fgAbnormalMode=FALSE;
}

void vErrorModeProcess(BYTE bMode,BYTE fgerror)
{
#if 0//130408vi01***
	if(fgIsInFunctionCheckerTestMode()&&(bMode!=ERROR_COVER_OPEN))	//130311vi01***
		{
		return;
		}		//130311vi01&&&
#endif
	if(fgAbnormalMode==TRUE)		
		{
		return;
		}
	
#ifdef FUNCTION_CHECKER_MODE_FUNCTION
	 if(fgIsInFunctionCheckerTestMode())
		{
		if(bMode!=ERROR_COVER_OPEN)
			{
			return;
			}
		}
	 else
#endif	//130425Me02&&&	
 	if(fgIsInPowerOffMode()&&fgIsNotWatchMode())
		{
		return;
		}


	if(fgerror==TRUE)//130329vi01
		{
		if(bErrorMode==bMode)	//130408vi01***
			{
			return;
			}		//130408vi01&&&
		bErrorMode=bMode;
		}
//	fgErrorModeFirstPower=TRUE;//130326vi01
#if 0		//130326vi01
	switch(bMode)
		{
		case WARNIN_GCLEANING_PCI_UNIT:
			vMcuEepromWriteByte(EE_CLEARN_PCI_ELECTRODE, bMode);
			fgExecutePowerOffMode=TRUE;	//130321ha01
			//vPowerOffMode();	//130321ha01
			vDisplay7SegShowU3BlinkOn(DISPLAY_TIME_0_5_SECOND);		//0.5s on /0.5s off
			break;		
		case ERROR_FAN_MOTOR_ROTATION:
		case ERROR_PCI_UNIT_DATA:
			vMcuEepromWriteByte(EE_ERROR_MODE_LAST, bMode);
			goto errorled_flash_and_power;
			break;
		case ERROR_TEM_HUM_SENSOR:
			if(fgerror)		//tem and hum error		//130313vi01***
				{
				vMcuEepromWriteByte(EE_ERROR_MODE_LAST, bMode);
				
				/*if(bSpecialFunctionMode==MODE_PRODUCTION_LINE)		//130311vi01***
					{
					return;
					}	*/	//130311vi01&&&

				if(bPowerMode==POWER_MODE_ON)
					{
					if(bWatchMode!=WATCH_MANUAL)
						{
						bLastWatchMode=bWatchMode;
						vSetWatchMode(WATCH_MANUAL);
						}
					vDisplay7SegShowHexNumBlinkOn(bMode, DISPLAY_TIME_0_5_SECOND);		//0.5s on /0.5s off
					return;
					}
				else		//power off
					{
					if(bWatchMode!=WATCH_MANUAL)
						{
						vSetWatchMode(WATCH_MANUAL);
						goto errorled_flash_and_power;			
						}
					}

				}
			else			//if(!fgerror)//tem and hum normal
				{
				vAbnormalModeCancel();
				if(bLastWatchMode!=WATCH_MANUAL)
					{
					vSetWatchMode(bLastWatchMode);
					bLastWatchMode=WATCH_MANUAL;	
					}
				fgAbnormalMode=FALSE;
				bErrorMode=ERROR_NONE;
				fgErrorModeFirstPower=FALSE;
				return;
				}				//130313vi01&&&
			break;
		case ERROR_COVER_OPEN:		//130311vi01***
			if(fgerror==TRUE)
				{	//Cover is open
				if(bSpecialFunctionMode==MODE_FUNCTION_CHECKER_TEST)
					{
					return;
					}
				}
			else if(fgerror==FALSE)
				{	//Cover is closed.
				if(bSpecialFunctionMode==MODE_FUNCTION_CHECKER_TEST)
					{
					vPutEventQueue(EVENT_IR, IR_NEXT_STEP, 0);
					}
				return;
				}
			goto errorled_flash_and_power;			
			break;	//130311vi01&&&			
		case ERROR_COMMUNICATION_WITH_TOUCH:
		case ERROR_PCI_UNIT_CONNECTION:
			goto errorled_flash_and_power;
			break;

		errorled_flash_and_power:	
			fgExecutePowerOffMode=TRUE;	//130321ha01
			//vPowerOffMode();	//130321ha01
			vDisplay7SegShowHexNumBlinkOn(bMode, DISPLAY_TIME_0_5_SECOND);		//0.5s on /0.5s off
		default:
			return;
		}
#else//130326vi01***
	switch(bMode)
		{
		case WARNIN_GCLEANING_PCI_UNIT:
			vMcuEepromWriteByte(EE_CLEARN_PCI_ELECTRODE, TRUE);//130411vi02		//TRUE:occur
			//vDisplay7segLedAllOff();//130419gr01
			//vDisplayLEDAllOff();//130419gr01
			vDisplay7segLedAndTouchLedAllOff();//130419gr01

			vDisplay7SegShowU3BlinkOn(DISPLAY_TIME_0_5_SECOND);		//0.5s on /0.5s off
			break;		
		case ERROR_FAN_MOTOR_ROTATION:
		case ERROR_PCI_UNIT_DATA:
			vMcuEepromWriteByte(EE_ERROR_MODE_LAST, bMode);
			goto errorled_flash;
		case ERROR_TEM_HUM_SENSOR:
			if(fgerror)		//tem and hum error		
				{
				vMcuEepromWriteByte(EE_ERROR_MODE_LAST, bMode);
				
				if(fgIsInPowerOnMode())
					{
					if(fgIsInWatchMode())
						{
						bLastWatchMode=bWatchMode;
						vSetWatchMode(WATCH_MANUAL);
						}
					vDisplayLEDAirVolumeSettingIndicationOff();//130403vi01
					if(fgOscillateInitialFinish==TRUE)		//130427ra02***
						{
						vDisplayLEDAngleSettingIndicationOff();//130403vi01
						}	//130427ra02&&&
					vDisplay7SegMessageClear();//130403vi01
					vDisplay7SegShowHexNumBlinkOn(bMode, DISPLAY_TIME_0_5_SECOND);		//0.5s on /0.5s off
					goto BUZZER_STOP;	//130415vi01
					}
				else		//power off
					{
					if(fgIsInWatchMode())
						{
						vSetWatchMode(WATCH_MANUAL);
						goto errorled_flash;			
						}
					}

				}
			else			//tem and hum normal
				{
				vAbnormalModeCancel();
				if(bLastWatchMode!=WATCH_MANUAL)
					{
					vSetWatchMode(bLastWatchMode);
					bLastWatchMode=WATCH_MANUAL;	
					}
				fgAbnormalMode=FALSE;//130329vi01		//130401vi01
				bErrorMode=ERROR_NONE;//130329vi01		//130401vi01
				return;
				}				
		case ERROR_COVER_OPEN:		
			if(fgerror==TRUE)
				{	//Cover is open
#ifdef FUNCTION_CHECKER_MODE_FUNCTION  //130423gr02
				if(fgIsInFunctionCheckerTestMode())
					{
					//fgAbnormalMode=FALSE;				//130402vi02//130408vi01
					bErrorMode=ERROR_NONE;				//130402vi02
					return;
					}
#endif //130423gr02
				}
			else if(fgerror==FALSE)
				{	//Cover is closed.
#ifdef FUNCTION_CHECKER_MODE_FUNCTION //130423gr02
				if(fgIsInFunctionCheckerTestMode())
					{
					vPutEventQueue(EVENT_IR, IR_NEXT_STEP, 0);
					}
#endif	//130423gr02
				return;
				}
			goto errorled_flash;			
		case ERROR_COMMUNICATION_WITH_TOUCH:
		case ERROR_PCI_UNIT_CONNECTION:
			goto errorled_flash;
			break;

		errorled_flash:	
		//	fgAbnormalMode=TRUE;//130408vi01//130411vi01
			//vDisplay7segLedAllOff();//130419gr01
			//vDisplayLEDAllOff();//130419gr01
			vDisplay7segLedAndTouchLedAllOff();//130419gr01

			vDisplay7SegShowHexNumBlinkOn(bMode, DISPLAY_TIME_0_5_SECOND);		//0.5s on /0.5s off
			break;
		default:
			return;
		}
	if(bErrorMode==ERROR_TEM_HUM_SENSOR)//130423vi01***	
		{
		if(fgIsInTimerOnOffFunction())	//130424vi01***
			{
			vDisplayLEDOnTimerOn();
			vTimerShow(bTimerMode);
			}	//130424vi01&&&
		}			
	else
		{
		vTimerOnOffStop();
		}//130423vi01&&&
	bWatchZone=ZONE_NORMAL;		//130504Me01
	fgAbnormalMode=TRUE;//130408vi01		//130411vi01
	fgOscillateInitialProcess=FALSE;		//130412vi02
	vSubMcuSendError(bErrorMode);
BUZZER_STOP:	//130415vi01
	if(fgWarningBuzzerStart==TRUE)//130415vi01***
		{
		fgDisplayLEDAirVolume1To9=FALSE;
		vBuzzerOutput(PI_OFF);
		}		//130415vi01&&&

#endif//130326vi01&&&

}
//130309vi01&&&



//130412Ke04***
void vOscillateStatusCheck(void)
{
	//OscillateMotor has not been finished
	if(fgOscillateInitialFinish==FALSE)
		{
		//Power off when oscillate is initialing,power on,it is initial continue.
		if(fgOscillateInitialProcess)
			{
			vOscillateMoveToCentral();
			}
		//Oscillate Motor initial whatever which mode you choos when you need initial.
		else if((bOscillateType>=OSCILLATE_15D)&&(bOscillateType<=OSCILLATE_OFF_MEMORIZED))
			{
			vOscillateMoveToCentral();		
			}
		bOscillateTypeStore=bOscillateType;
		if(fgIsInIonMode())  //130425lo02***
			{
			fgIonSetAngle=FALSE;
			}  //130425lo02&&&
		}

	// OscillateMotor has been finished
	else
		{
		//Set oscillate angle when initial is finished.
		if(bOscillateTypeStore!=OSCILLATE_NONE)
			{
			vI2cSendCommand2Para(COMMAND_SUB_MAIN_OSCILLATE_MODE,bOscillateTypeStore);
#ifdef FUNCTION_CHECKER_MODE_FUNCTION	//130429le01***
			if(bSpecialFunctionMode!=MODE_FUNCTION_CHECKER_TEST)
#endif	//130429le01&&&
				{
				vDisplay7SegShowOscillateAngleAutoOff(bOscillateTypeStore, DISPLAY_TIME_10_SECOND);//130326Ke02
				}
			//vDisplayLEDAngleSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);	//130408Ke05	//130418Ke05
			vDisplayLEDAirVolumeSettingIndicationOff();
			bOscillateTypeStore=OSCILLATE_NONE;
			}
		//Set oscillate angle in normal.
		else
			{
			vI2cSendCommand2Para(COMMAND_SUB_MAIN_OSCILLATE_MODE,bOscillateType);
			if(bOscillateType!=OSCILLATE_OFF)
				{
				//if(fgIsNotIonMode()) //130417lo01***			// 130423jac02
				if(fgIonSetAngle==FALSE)	// 130423jac02
					{
					vDisplay7SegShowOscillateAngleAutoOff(bOscillateType, DISPLAY_TIME_10_SECOND);//130326Ke02
					//vDisplayLEDAngleSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);	//130408Ke05	//130418Ke05
					//vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);	//130418Ke05
					} 		//130417lo01&&&
				else		// 130423jac02***
					{
					fgIonSetAngle=FALSE;
					}		// 130423jac02&&&
				}
			else
				{
				//vDisplay7SegMessageClear();	//130418Ke05
				vDisplayLEDAngleSettingIndicationOff();//130326Ke03
				vDisplay7SegShowOscillateAngleOff();	//130418Ke05
				vDisplayLEDAirVolumeSettingIndicationOff();//130409Ke08
				}
			}
		}
}


void vFanVolumeSetValue(void)	//130424Ke03***		 //130426jac01***
{	
	//if(fgIsInPowerOnMode())
		{
		vI2cSendCommand2Para(COMMAND_SUB_MAIN_FAN_VOLUME_EE,bee_air_volume);	//130427Ja01
		vI2cSendCommand2Para(COMMAND_SUB_MAIN_FAN_VOLUME,bFanVolumeType);
		}	
}	//130424Ke03&&&

void vFanVolumeShow(void)	//130424Ke03***
{	
	vDisplayShowAirVolumeAutoOff(bAirVolumeType, bFanVolumeShowType);
}	//130424Ke03&&&		 //130426jac01&&&

#if 1
BYTE bQueueType=QUEUE_TYPE_NONE;

#define bEvent		btemp_data[0]
#define bEventData1	btemp_data[1]
#define bEventData2	btemp_data[2]
#define bI2CData1	btemp_data[0]
#define bI2CData2	btemp_data[1]
#define bI2CData3	btemp_data[2]

void vCheckEvent(void)      	
{
	//BYTE bADCValue=0;
	BYTE btemp_data[3];
	BYTE OscillateFinishAngle=OSCILLATE_90D;	//130409Ke04
	
	if(bQueueType==QUEUE_TYPE_NONE)
		{
		if(fgMixQueuEmpty==FALSE)
			{	//Queue has data.
			//bEvent=bGetMixQueue();
			bQueueType=bGetMixQueue();
			//if((bEvent&QUEUE_TYPE_EVENT)==QUEUE_TYPE_EVENT)
			//	{	//Event
			//	bQueueType=QUEUE_TYPE_EVENT;
			//	}
			//else
			//	{	//I2C, EEPROM
			//	bQueueType=bEvent&QUEUE_TYPE;
			//	}
			}
		else
			{	//Queue no data.
			return;
			}
		}
	
	switch(bQueueType)
		{
		case QUEUE_TYPE_EVENT:
			//bEvent&=(~QUEUE_TYPE_EVENT);
			bEvent=bGetMixQueue();
			bEventData1=bGetMixQueue();
			bEventData2=bGetMixQueue();
			bQueueType=QUEUE_TYPE_NONE;
			break;
		case QUEUE_TYPE_I2C:
			if(fgI2CCommandBusy==FALSE)
				{
				//bI2CData1&=(BYTE)(~QUEUE_TYPE_I2C);
				//bI2CData2=bGetMixQueue();
				//bI2CData3=bGetMixQueue();
				//bI2CData4=bGetMixQueue();
				fgI2CCommandBusy=TRUE;
				vPinI2cBusyEnable();//130315sh01
				vI2CWriteCommand(bGetMixQueue(),bGetMixQueue(),bGetMixQueue(),bGetMixQueue());
				bQueueType=QUEUE_TYPE_NONE;
				}
			return;
		case QUEUE_TYPE_EEPROM:
			if( fgEEPROMWriteCycleIsCompleted() )
				{
				//bI2CData1&=(BYTE)(~QUEUE_TYPE_EEPROM);
				vMcuEepromRealWrite(bGetMixQueue(),bGetMixQueue());
				bQueueType=QUEUE_TYPE_NONE;
				}
			return;	//130322ha05
		default:
			bQueueType=QUEUE_TYPE_NONE;
			return;
		}

	//Is there event on the Event Queue? If do,jump to here.
//	if(!fgEventQueuEmpty)
		{
//		stemp_queue_data=sGetEventQueue();
//		if(bEvent==EVENT_EEPROM)	//130316le01***
//			{
//			bEepromAddrBackup=bEventData1;
//			bEepromDataBackup=bEventData2;
//			fgEepromHasData=TRUE;
//			return;
//			}	//130316le01&&&
			
		switch(bEvent)
			{
			case EVENT_IR:
				bIRKey=bEventData1;
				bIRKeySub=bEventData2;	//130310ha01
				//vEventKeyProcess();
				break;
//			case EVENT_POWER_ON:
//				break;
#ifdef ADC_FUNCTION
			case EVENT_ADC:
				//bADCValue=ADDH;
				//bADCValue<<=4;
				//bADCValue+=ADDL;
				vLightSensorEvent(ADDH);	//130312Li01
				break;
#endif
//			case EVENT_OTP_INT_INTERRUPT:	//130126sh01***
//				vMainMCUInterruptRead();
//				break;	//130126sh01&&&
			case EVENT_TOUCH_READ_REGISTER_ADDRESS://130408sh01***
				//bI2cData2=bEventData1;//130417gr01
				bI2cData3=bEventData1;//130417gr01
				break;//130408sh01&&&
			case EVENT_TOUCH_READ:
			 	//Register address Hi to bI2cData2
				//Register address Lo to bI2cData3
				//vEventTouchRead(bI2cData2*0x100+bI2cData3, bEventData1*0x100+bEventData2 ); //130417gr01
				vEventTouchRead(bI2cData3,bEventData1,bEventData2); //130417gr01
				break;
//			case EVENT_TOUCH_INTERRUPT:
//				if(fgTouchInitial)//130307gr01***
//					{
//					break;
//					}//130307gr01&&&
//				vEventTouchSensorInterrupt();
//				break;

			//Event about MAIN MCU to TOUCH MCU.
			//Command about MAIN to SUB.
//130308ra01***
			case COMMAND_MAIN_SUB_GIVE_HUM_ADC_VALUE:
				//130309ma01***
				switch(bSpecialFunctionMode)
					{
#ifdef PRODUCTION_LINE_MODE_FUNCTION
					case MODE_PRODUCTION_LINE:
						if((bEventData1 >= PRODUCTION_LINE_MODE_HUM_MIN) && (bEventData1 <= PRODUCTION_LINE_MODE_HUM_MAX))
							{
							//air volume indication 6 lights up
							vDisplayLEDAirVolume6On();
							fgProductModeBlue6State = TRUE;
							if(fgProductModeBlue3State==TRUE)
								{
								vSpecialFunctionNextStep();
								}
							}
						break;
#endif
#ifdef FUNCTION_CHECKER_MODE_FUNCTION
					case MODE_FUNCTION_CHECKER_TEST:	//130313le01***
						if((bEventData1 >= HUMIDITY_VALUE_50)&&(bEventData1 <= HUMIDITY_VALUE_55))
							{
							vDisplayLEDAirVolume9On();
							vSpecialFunctionNextStep();
							}
						break;	//130313le01&&&
#endif
					default:
						vDisplay7SegShowHexNumOn(bEventData1);
						break;
					}				
				//130309ma01&&&
				break;
			case COMMAND_MAIN_SUB_GIVE_TEMP_ADC_VALUE:
				//130309ma01***
				switch(bSpecialFunctionMode)
					{
					case MODE_MONITOR:		//130327ra02***
						vDisplay7SegShowHexNumOn(bEventData1);
						break;	//130327ra02&&&
#ifdef PRODUCTION_LINE_MODE_FUNCTION
					case MODE_PRODUCTION_LINE:				 
						if((bEventData1 >= PRODUCTION_LINE_MODE_TEM_MIN) && (bEventData1 <= PRODUCTION_LINE_MODE_TEM_MAX))
							{
							//air volume indication 3 lights up 
							vDisplayLEDAirVolume3On();
							fgProductModeBlue3State = TRUE;
							if(fgProductModeBlue6State==TRUE)
								{
								vSpecialFunctionNextStep();
								}
							}
						break;
#endif
#ifdef FUNCTION_CHECKER_MODE_FUNCTION
					case MODE_FUNCTION_CHECKER_TEST:	//130313le01***
						if((bEventData1 >= TEMPERATURE_VALUE_25) && (bEventData1 <= TEMPERATURE_VALUE_30))	//Temperature A/D from 25 degrees C to 30 degrees C.
							{
							vDisplayLEDAirVolume8On();
							vSpecialFunctionNextStep();
							}
						break;	//130313le01&&&
#endif
					//default:
					//	vDisplay7SegShowHexNumOn(bEventData1);
					//	break;
					}				
				//130309ma01&&&
				break;
			case COMMAND_MAIN_SUB_INT_SPEED_UP_MODE:	//130407ra01***
				if(bEventData1)
					{
					fgSpeedUp=TRUE;
					vOnOffTimerSetAtSpeedUp();	//130312Ti02
					}
				else
					{
					fgSpeedUp=FALSE;
					}
				break;	//130407ra01&&&
				
			case COMMAND_MAIN_SUB_GIVE_ION_VOLTAGE_VALUE:	//130313le01***//130408Ad04
				switch(bSpecialFunctionMode)
					{
					case MODE_MONITOR:
						vDisplay7SegShowHexNumOn(bEventData1);
						break;	
#ifdef FUNCTION_CHECKER_MODE_FUNCTION
					case MODE_FUNCTION_CHECKER_TEST:
						if(bModeState==5)
							{
							if((bEventData1>= ION_SENSOR_RESET_ON_4v)&&(bEventData1 <= ION_SENSOR_RESET_ON_5v))	//判斷?壓值是否超出?圍(4v--5v).
								{
								vDisplayLEDOnTimerOn();
								vSpecialFunctionNextStep();
								//vPutEventQueue(EVENT_IR,IR_NEXT_STEP,0);	//130328le01	130419le02
								}
							}
						else if(bModeState==6)
							{
							if((bEventData1 >= ION_SENSOR_RESET_OFF_2v)&&(bEventData1 <= ION_SENSOR_RESET_OFF_3v))	//判斷Ion Sensor voltage是否在2v--3v之間.
								{
								vDisplayLEDTimer2On();
								vSpecialFunctionNextStep();
								}
							}
						break;				
#endif
					}
				break;	//130313le01&&&
#ifdef FUNCTION_CHECKER_MODE_FUNCTION
			case COMMAND_MAIN_SUB_INT_FUNCTION_CHECKER_MODE:	//130403le01***
				bIRKey=IR_FUNCTION_CHECKER_TEST_MODE;
				//vPutEventQueue(EVENT_IR,IR_FUNCTION_CHECKER_TEST_MODE,0);
				break;	//130403le01&&&
#endif				
			case COMMAND_MAIN_SUB_GIVE_FAN_PWM_VALUE:
			case COMMAND_MAIN_SUB_GIVE_TEMP_REAL_VALUE:
			case COMMAND_MAIN_SUB_GIVE_HUM_REAL_VALUE:
//			case COMMAND_MAIN_SUB_GIVE_ION_VOLTAGE_VALUE:
//			case COMMAND_MAIN_SUB_GIVE_ION_DELTA_VOFF:
			case COMMAND_MAIN_SUB_GIVE_ION_ERROR_COUNT_VALUE:
				//vDisplay7SegShowHexNumOn(bEventData1);
				//break;
			case COMMAND_MAIN_SUB_GIVE_FAN_ROTA_SET_VALUE:
			case COMMAND_MAIN_SUB_GIVE_FAN_ROTA_DETECT_VALUE:
				vDisplay7SegShowHexNumOn(bEventData1);	//130327ra02
				break;	//130313le01&&&
#ifdef FUNCTION_CHECKER_MODE_FUNCTION	//130425Ja01				
			case COMMAND_MAIN_SUB_GIVE_FAN_MOTOR_ROTATION_VALUE:
				if((bEventData1>=FAN_ROTATIONAL_SPEED_MIN)&&(bEventData1<=FAN_ROTATIONAL_SPEED_MAX))
					{
					vDisplayLEDAirVolume7On();
					vSpecialFunctionNextStep();
					}	
				break;	
#endif		//130425Ja01					
			case COMMAND_MAIN_SUB_GIVE_PCI_UNIT_USE_ACC_HOUR_VALUE:
				vDisplay7SegShowDecNumOn(bEventData1);
				break;
			case COMMAND_MAIN_SUB_GIVE_PCI_UNIT_USE_ACC_TIME_VALUE:
				vDisplay7SegShowHexNumOn(bEventData2);
				break;
#ifdef PRODUCTION_LINE_MODE_FUNCTION	//130425Ja01				
			case COMMAND_MAIN_SUB_GIVE_ION_LEAK_CURRENT_OK_COUNT:
				//130309ma01***
				switch(bSpecialFunctionMode)
					{
					case MODE_PRODUCTION_LINE:
						 //130313ma02***
						bProductIonCount = bEventData1;  //130415ma01
						fgProductModeTimeStatus = TRUE;
						break;
					default:
						vDisplay7SegShowHexNumOn(bEventData1);
						break;
					}	
				//130309ma01&&&
				break;
#endif	//130425Ja01
			case COMMAND_MAIN_SUB_GIVE_ION_GENERATION_OK_COUNT:
				//130309ma01***
				switch(bSpecialFunctionMode)
					{
#ifdef PRODUCTION_LINE_MODE_FUNCTION					
					case MODE_PRODUCTION_LINE:					
						//130313ma02***
						bProductIonCount = bEventData1;  //130415ma01
						bIRKey=IR_NEXT_STEP;
						break;
#endif
					default:
						vDisplay7SegShowHexNumOn(bEventData1);
						break;
					}	
				//130309ma01&&&				
				break;

//130305Ke02***
			case COMMAND_MAIN_SUB_INT_OSCILLATE_INITIAL_FINISH:
				fgOscillateInitialFinish=TRUE;	//130409Ke06
				fgOscillateInitialProcess=FALSE;//130409Ke06
				bOscillatingMode=OSCILLATE_ON;	
				vOscillateStatusCheck();	//130412Ke04
				break;
//130305Ke02&&&
//130328ro02***
			case COMMAND_MAIN_SUB_INT_LOUVER_INITIAL_FINISH:     
				fgLouverInitialFinish=TRUE;     

				if((fgLouverPlugSocketInitial==TRUE)&&(fgAutoRestartFunction==FALSE))//130329ro01***    //130422gr01
					{
					vLouverModeSet(LOUVER_HORIZONTAL_1);
					fgLouverPlugSocketInitial=FALSE;
					//bLouverAngle=LOUVER_HORIZONTAL_1;	//130402ro04//130422gr01
					//vMcuEepromWriteByte(EE_LOUVER_ANGLE, LOUVER_HORIZONTAL_1);	//130402ro04//130422gr01
					}
				else
					{
					bLouverMode=bMcuEepromReadByte(EE_LOUVER_MODE);	//130425Me01
					if(bLouverMode==LOUVER_STOP)
						{
						vLouverModeSet(bLouverAngle);	//130402ro01 //130422gr01
						}
					else
						{
						vLouverModeSet(bLouverMode);
						}
					} //130329ro01&&&

				break;
//130328ro02&&&
			case COMMAND_MAIN_SUB_INT_WATCH_ZONE_STATUS_CHANGE:
				//130308Me01***
				bWatchZone=bEventData1;
				//if((bWatchZone==ZONE_DANGER)||(bWatchZone==ZONE_PRECAUTION))	//130311Me01***	130411le01***
				//	{
				//	fgWatchModeError=TRUE;
				//	}		//130311Me01&&&	130411le01&&&
				vWatchModeZoneChange();
				if(fgIsInIonMode())
					break;
				if(bWatchZone != ZONE_DANGER)	//130424Ja01
					{
					bIRKey=IR_AIR_VOLUME_CONTROL;	//130424Ja01
					}
				//130308Me01&&&
				break;

			case COMMAND_MAIN_SUB_INT_WARNING_BUZZER_START:	//130411le01***
				if(bSpecialFunctionMode!=MODE_DEMO)	//130416le01
					{	//130416le01
					fgWarningBuzzerStart=bEventData1;
					}	//130416le01
				break;	//130411le01&&&

			case COMMAND_MAIN_SUB_INT_WATCH_AUTO_FAN_STATUS_CHANGE:	//130418Ja01&&&
				//bWatchModeAutoFanStatus = bEventData1;
				bAdjustAutoFanVolume = bEventData2;
				if(fgIsNotIonMode()) //130504Ja01
					{
					bIRKey=IR_AIR_VOLUME_CONTROL;
					}
				break;	//130418Ja01&&&
				
			case COMMAND_MAIN_SUB_INT_PCI_OVER_TIME:
				vDisplayLEDTubeWhiteOff();		  // 130307lo04
				vDisplayLEDPCIReplacingBlinkOn(DISPLAY_TIME_0_2_SECOND);          // 130307lo04
				fgPCIIsOverTime=TRUE;	//130409Li02
				break;
			case COMMAND_MAIN_SUB_INT_PCI_CRITICAL:
				vDisplayLEDPCIReplacingBlinkOn(DISPLAY_TIME_0_4_SECOND);          // 130307lo03
				break;
//130308ra01&&&				
			case COMMAND_MAIN_SUB_ERROR://130309vi01***
				if(fgIsInFunctionCheckerTestMode()||fgIsInNormalMode())		//130311vi01
					{
					vErrorModeProcess(bEventData1,bEventData2);
					}
				break;	//130309vi01&&&
#ifdef MAIN_DISPLAY_FOR_TEST	// 130325jac01***
			case COMMAND_MAIN_SUB_7SEG_LED_0_1_ROW:
				bRow7SegLedShowData[0]=bEventData1;
				bRow7SegLedShowData[1]=bEventData2;
				break;
			case COMMAND_MAIN_SUB_7SEG_LED_2_ROW:
				bRow7SegLedShowData[2]=bEventData1;
				break;
			case COMMAND_MAIN_SUB_7SEG_LED_3_4_ROW:
				bRow7SegLedShowData[3]=bEventData1;
				bRow7SegLedShowData[4]=bEventData2;
				break;	
#endif	// 130325jac01&&&

			case COMMAND_MAIN_SUB_LOUVER_MOTOR_ON:	//130424Me01***
				fgVerticalMotorOn=bEventData1;
				break;	//130424Me01&&&
			}
		}
}

#else

#ifdef QUEUE_USE_STRUCT
#define bEvent		stemp_queue_data.bEvent
#define bEventData1	stemp_queue_data.bData1
#define bEventData2	stemp_queue_data.bData2
#else //defined(QUEUE_USE_ARRAY)
#define bEvent		stemp_queue_data[0]
#define bEventData1	stemp_queue_data[1]
#define bEventData2	stemp_queue_data[2]
#endif

void vCheckEvent(void)      	
{
#ifdef QUEUE_USE_STRUCT
	event_queue stemp_queue_data;
#else //defined(QUEUE_USE_ARRAY)
	BYTE* stemp_queue_data;
#endif
	WORD wADCValue=0;
	//BYTE bFanTempValue=0;	//130313le01	//130314le01
	//Is there event on the Event Queue? If do,jump to here.
	if(!fgEventQueuEmpty)
		{
		stemp_queue_data=sGetEventQueue();
		if(bEvent==EVENT_EEPROM)	//130316le01***
			{
			bEepromAddrBackup=bEventData1;
			bEepromDataBackup=bEventData2;
			fgEepromHasData=TRUE;
			return;
			}	//130316le01&&&
			
		switch(bEvent)
			{
			case EVENT_IR:
				bIRKey=bEventData1;
				bIRKeySub=bEventData2;	//130310ha01
				vEventKeyProcess();
				break;
//			case EVENT_POWER_ON:
//				break;
#ifdef ADC_FUNCTION
			case EVENT_ADC:
				wADCValue=ADDH;
				wADCValue<<=4;
				wADCValue+=ADDL;
				//fgADCTransformIsBusy=FALSE;	//130309Li02
				vLightSensorEvent(wADCValue);	//130312Li01

				/*switch(bNowADCChannel)		//130312Li01***
					{
					case ADC_CHANNEL_LIGHT:
						vLightSensorEvent(wADCValue);
						break;
					}*/		//130312Li01&&&
				break;
#endif
			case EVENT_OTP_INT_INTERRUPT:	//130126sh01***
				vMainMCUInterruptRead();
				break;	//130126sh01&&&
#if 0	//DISPLAY_7SEG_FUNCTION			// jacky mark for Display change
			case COMMAND_MAIN_SUB_DISPLAY_ALL_ON:
				vDisplay7segLedAllOn();
				break;
			case COMMAND_MAIN_SUB_DISPLAY_ALL_OFF:
				vDisplay7segLedAllOff();
				break;

			case COMMAND_MAIN_SUB_LED_DISPLAY:// 130301ja04***
				//vDisplayLEDShow(bEventData1,bEventData2);
				break;
			case COMMAND_MAIN_SUB_7_SEG_DISPLAY:
				//vDisplay7SegShowMessage(bEventData1,bEventData2);
				break;
			case COMMAND_MAIN_SUB_LED_Blink_ON:	//130306ja03***
				//vDisplayLEDBlink(bEventData1,bEventData2,TRUE);
				break;
			case COMMAND_MAIN_SUB_LED_Blink_OFF:
				//vDisplayLEDBlink(bEventData1,bEventData2,FALSE);
				break;
			case COMMAND_MAIN_SUB_7_SEG_DEC_Blink_ON:
				vDisplay7SegBlinkMessage(CMD_7SEG_NUM_DEC_SHOW,bEventData1,bEventData2,TRUE);
				break;
			case COMMAND_MAIN_SUB_7_SEG_HEX_Blink_ON:
				vDisplay7SegBlinkMessage(CMD_7SEG_NUM_HEX_SHOW,bEventData1,bEventData2,TRUE);
				break;
			case COMMAND_MAIN_SUB_7_SEG_MESSAGE_Blink_ON:
				vDisplay7SegBlinkMessage(CMD_7SEG_MESSAGE_SHOW,bEventData1,bEventData2,TRUE);
				break;
			case COMMAND_MAIN_SUB_7_SEG_DEC_Blink_OFF:
				vDisplay7SegBlinkMessage(CMD_7SEG_NUM_DEC_SHOW,bEventData1,bEventData2,FALSE);
				break;
			case COMMAND_MAIN_SUB_7_SEG_HEX_Blink_OFF:
				vDisplay7SegBlinkMessage(CMD_7SEG_NUM_HEX_SHOW,bEventData1,bEventData2,FALSE);
				break;
			case COMMAND_MAIN_SUB_7_SEG_MESSAGE_Blink_OFF:
				vDisplay7SegBlinkMessage(CMD_7SEG_MESSAGE_SHOW,bEventData1,bEventData2,FALSE);//130306ja03&&&
				break;
			case COMMAND_MAIN_SUB_LED_AUTO_DISAPPEAR:
				vDisplayLEDAutoOff(bEventData1,bEventData2);
				break;
			case COMMAND_MAIN_SUB_7_SEG_DEC_AUTO_DISAPPEAR:
				vDisplay7SegAutoOff(CMD_7SEG_NUM_DEC_SHOW,bEventData1,bEventData2);
				break;
			case COMMAND_MAIN_SUB_7_SEG_HEX_AUTO_DISAPPEAR:
				vDisplay7SegAutoOff(CMD_7SEG_NUM_HEX_SHOW,bEventData1,bEventData2);
				break;
			case COMMAND_MAIN_SUB_7_SEG_MESSAGE_AUTO_DISAPPEAR:
				vDisplay7SegAutoOff(CMD_7SEG_MESSAGE_SHOW,bEventData1,bEventData2);
				break;		
#endif			// 130301ja04&&&

			case EVENT_TOUCH_READ:
			 	//Register address Hi to bI2cData2
				//Register address Lo to bI2cData3
				vEventTouchRead(bI2cData2*0x100+bI2cData3, bEventData1*0x100+bEventData2 );
				break;
			case EVENT_TOUCH_INTERRUPT:
				if(fgTouchInitial)//130307gr01***
					{
					break;
					}//130307gr01&&&
				vEventTouchSensorInterrupt();
				break;

			//Event about MAIN MCU to TOUCH MCU.
			//Command about MAIN to SUB.
/*
			case COMMAND_MAIN_SUB_GIVE_HUM_ADC_VALUE:
				vGiveHumidityADCValue(bEventData1, bEventData2);
				break;
			case COMMAND_MAIN_SUB_GIVE_TEMP_ADC_VALUE:
				vGiveTemperatureADCValue(bEventData1, bEventData2);
				break;
			case COMMAND_MAIN_SUB_GIVE_FAN_PWM_VALUE:
				vGiveFanPWMValue(bEventData1, bEventData2);
				break;
			case COMMAND_MAIN_SUB_GIVE_TEMP_REAL_VALUE:
				vGiveTemperatureValue(bEventData1, bEventData2);
				break;
			case COMMAND_MAIN_SUB_GIVE_HUM_REAL_VALUE:
				vGiveHumidityValue(bEventData1, bEventData2);
				break;
			case COMMAND_MAIN_SUB_GIVE_ION_VOL_VALUE:
				vGiveIONVoltageValue(bEventData1, bEventData2);
				break;
			case COMMAND_MAIN_SUB_GIVE_ION_ERROR_CNT:
				vGiveIONErrorCount(bEventData1, bEventData2);
				break;
			case COMMAND_MAIN_SUB_GIVE_PCI_UNIT_USE_ACC_TIME_VALUE:
				vGivePCIAccTimeValue(bEventData1, bEventData2);
				break;
*/				
//130308ra01***
			case COMMAND_MAIN_SUB_GIVE_HUM_ADC_VALUE:
				//130309ma01***
				switch(bSpecialFunctionMode)
					{
					case MODE_PRODUCTION_LINE:
						if((bEventData1 >= PRODUCTION_LINE_MODE_HUM_MIN) && (bEventData1 <= PRODUCTION_LINE_MODE_HUM_MAX))
							{
							//air volume indication 6 lights up
							vDisplayLEDAirVolume6On();
							#ifdef PRODUCTION_LINE_MODE_FUNCTION
							fgProductModeBlue6State = TRUE;
							if(fgProductModeBlue3State==TRUE)
								{
								vSpecialFunctionNextStep();
								}
							#endif
							}
						break;
					case MODE_FUNCTION_CHECKER_TEST:	//130313le01***
						if((bEventData1 >= HUMIDITY_VALUE_50)&&(bEventData1 <= HUMIDITY_VALUE_55))
							{
							vDisplayLEDAirVolume9On();
							vSpecialFunctionNextStep();
							}
						break;	//130313le01&&&
					default:
						vDisplay7SegShowHexNumOn(bEventData1);
						break;
					}				
				//130309ma01&&&
				break;
			case COMMAND_MAIN_SUB_GIVE_TEMP_ADC_VALUE:
				//130309ma01***
				switch(bSpecialFunctionMode)
					{
					case MODE_PRODUCTION_LINE:				 
						if((bEventData1 >= PRODUCTION_LINE_MODE_TEM_MIN) && (bEventData1 <= PRODUCTION_LINE_MODE_TEM_MAX))
							{
							//air volume indication 3 lights up 
							vDisplayLEDAirVolume3On();
							#ifdef PRODUCTION_LINE_MODE_FUNCTION
							fgProductModeBlue3State = TRUE;
							if(fgProductModeBlue6State==TRUE)
								{
								vSpecialFunctionNextStep();
								}
							#endif
							}
						break;
					case MODE_FUNCTION_CHECKER_TEST:	//130313le01***
						if((bEventData1 >= TEMPERATURE_VALUE_25) && (bEventData1 <= TEMPERATURE_VALUE_30))	//Temperature A/D from 25 degrees C to 30 degrees C.
							{
							vDisplayLEDAirVolume8On();
							vSpecialFunctionNextStep();
							}
						break;	//130313le01&&&
					default:
						vDisplay7SegShowHexNumOn(bEventData1);
						break;
					}				
				//130309ma01&&&
				break;
			case COMMAND_MAIN_SUB_GIVE_FAN_PWM_VALUE:
			case COMMAND_MAIN_SUB_GIVE_TEMP_REAL_VALUE:
			case COMMAND_MAIN_SUB_GIVE_HUM_REAL_VALUE:
			case COMMAND_MAIN_SUB_GIVE_ION_VOLTAGE_VALUE:
//			case COMMAND_MAIN_SUB_GIVE_ION_DELTA_VOFF:
			case COMMAND_MAIN_SUB_GIVE_ION_ERROR_COUNT_VALUE:
				vDisplay7SegShowHexNumOn(bEventData1);
				break;
			case COMMAND_MAIN_SUB_GIVE_ION_DELTA_V:	//130313le01***
				switch(bSpecialFunctionMode)
					{
					case MODE_MONITOR:
						vDisplay7SegShowHexNumOn(bEventData1);
						break;	
					case MODE_FUNCTION_CHECKER_TEST:
						if(bModeState==5)
							{
							if((bEventData1>= ION_SENSOR_RESET_ON_4v)&&(bEventData1 <= ION_SENSOR_RESET_ON_5v))	//判斷?壓值是否超出?圍(4v--5v).
								{
								vDisplayLEDOnTimerOn();
								vSpecialFunctionNextStep();
								}
							}
						else if(bModeState==6)
							{
							if((bEventData1 >= ION_SENSOR_RESET_OFF_2v)&&(bEventData1 <= ION_SENSOR_RESET_OFF_3v))	//判斷Ion Sensor voltage是否在2v--3v之間.
								{
								vDisplayLEDTimer2On();
								vSpecialFunctionNextStep();
								}
							}
						
						break;				
					}
				break;	//130313le01&&&
			case COMMAND_MAIN_SUB_GIVE_FAN_ROTA_SET_VALUE:
				/*switch(bSpecialFunctionMode)	//130313le01***	//130314le01***
					{
					case MODE_MONITOR:
						vDisplay7SegShowHexNumOn(bEventData1/10);
						break;
					case MODE_FUNCTION_CHECKER_TEST:
						bFanSetValue=bEventData1;	
						break;
					}
				break;*/ 	//130313le01&&&
			case COMMAND_MAIN_SUB_GIVE_FAN_ROTA_DETECT_VALUE:
				/*switch(bSpecialFunctionMode)	//130313le01***
					{
					case MODE_MONITOR:
						vDisplay7SegShowHexNumOn(bEventData1/10);
						break;
					case MODE_FUNCTION_CHECKER_TEST:
						if(bFanSetValue < bEventData1) 
							{
							bFanTempValue = (bEventData1-bFanSetValue);
							}
						else
							{
							bFanTempValue = (bFanSetValue-bEventData1);
							}
						
						if((bFanTempValue >=FAN_ROTATIONAL_SPEED_MIN)&&(bFanTempValue <= FAN_ROTATIONAL_SPEED_MAX))
							{
							vDisplayLEDAirVolume7On();
							vSpecialFunctionNextStep();
							}	
						break;
					}*/
				vDisplay7SegShowHexNumOn(bEventData1/10);
				break;	//130313le01&&&	
			case COMMAND_MAIN_SUB_GIVE_FAN_MOTOR_ROTATION_VALUE:
				if((bEventData1>=FAN_ROTATIONAL_SPEED_MIN)&&(bEventData1<=FAN_ROTATIONAL_SPEED_MAX))
					{
					vDisplayLEDAirVolume7On();
					vSpecialFunctionNextStep();
					}	
				break;	
			case COMMAND_MAIN_SUB_GIVE_PCI_UNIT_USE_ACC_HOUR_VALUE:
				vDisplay7SegShowDecNumOn(bEventData1);
				break;
			case COMMAND_MAIN_SUB_GIVE_PCI_UNIT_USE_ACC_TIME_VALUE:
				vDisplay7SegShowHexNumOn(bEventData2);
				break;
			case COMMAND_MAIN_SUB_GIVE_ION_LEAK_CURRENT_OK_COUNT:
				//130309ma01***
				switch(bSpecialFunctionMode)
					{
#ifdef PRODUCTION_LINE_MODE_FUNCTION					
					case MODE_PRODUCTION_LINE:					
						 //130313ma02***
						vMcuEepromWriteByte(EE_ION_LEAK_CURRENT_OK_COUNT, bEventData1);
						fgProductModeTimeStatus = TRUE;
						/*if(bEventData1 > PRODUCTION_LINE_MODE_ION_ERROR_COUNT)
							{
							//set digital indication display Version("Major Version No. of Sub MCU") Number
							vDisplay7SegShowDecNumOn(MCU_FIRMWARE_VERSION_UNIT);
							//buzzer_driver(Pi);
							vBuzzerOutput(PI);
							//update touch led state, air volume indication 1 lights up
							vDisplayLEDAirVolume1On();
							/*#ifdef PRODUCTION_LINE_MODE_FUNCTION
							fgProductModeIonDeltaVoff = TRUE;
							#endif*/   //130312ma01 */
							//bModeState++;  //130312ma01
							//}
						//130313ma02&&&
						break;
#endif
					default:
						vDisplay7SegShowHexNumOn(bEventData1);
						break;
					}	
				//130309ma01&&&
				break;
			case COMMAND_MAIN_SUB_GIVE_ION_GENERATION_OK_COUNT:
				//130309ma01***
				switch(bSpecialFunctionMode)
					{
#ifdef PRODUCTION_LINE_MODE_FUNCTION					
					case MODE_PRODUCTION_LINE:					
						//130313ma02***
						vMcuEepromWriteByte(EE_ION_GENERATION_OK_COUNT, bEventData1);
						fgProductModeTimeStatus = TRUE;
						//if(bEventData1)
							//{
							//update touch led state, air volume indication Turbo(purple) lights up
							//vDisplayLEDAirVolume9On();
							/*#ifdef PRODUCTION_LINE_MODE_FUNCTION
							fgProductModeIonDeltaV = TRUE;
							#endif*/  //130312ma01
							//bModeState++;   //130312ma01
							//}
						//130313ma02&&&
						break;
#endif
					default:
						vDisplay7SegShowHexNumOn(bEventData1);
						break;
					}	
				//130309ma01&&&				
				break;



//130305Ke02***
			case COMMAND_MAIN_SUB_INT_OSCILLATE_INITIAL_FINISH:
				fgOscillateInitialFinish=TRUE;
				//bOscillatingModeAngle=bMcuEepromReadByte(EE_OSCILLATE_MODE_ANGLE);//130311Ke01
				vDisplay7SegShowPAutoOff(DISPLAY_TIME_10_SECOND);
				vOscillateModeSet(bOscillatingModeAngle);	
				break;
//130305Ke02&&&
			case COMMAND_MAIN_SUB_INT_FAN_VOLUME:
				break;
			case COMMAND_MAIN_SUB_INT_FUNCTION_TEST_MODE:
				break;
			case COMMAND_MAIN_SUB_INT_SPEED_UP_MODE:
				break;
			case COMMAND_MAIN_SUB_INT_WATCH_ZONE_STATUS_CHANGE:
				//130308Me01***
				bWatchZone=bEventData1;
				if((bWatchZone==ZONE_DANGER)||(bWatchZone==ZONE_PRECAUTION))	//130311Me01***
					{
					fgWatchModeError=TRUE;
					}		//130311Me01&&&
				vWatchModeZoneChange();
				//130308Me01&&&
				break;
			case COMMAND_MAIN_SUB_INT_PCI_OVER_TIME:
				vDisplayLEDTubeWhiteOff();		  // 130307lo04
				vDisplayLEDPCIReplacingBlinkOn(DISPLAY_TIME_0_2_SECOND);          // 130307lo04
				break;
			case COMMAND_MAIN_SUB_INT_PCI_CRITICAL:
				vDisplayLEDPCIReplacingBlinkOn(DISPLAY_TIME_0_4_SECOND);          // 130307lo03
				break;
//130308ra01&&&				
			case COMMAND_MAIN_SUB_ERROR://130309vi01***
				if((bSpecialFunctionMode==MODE_FUNCTION_CHECKER_TEST)||(bSpecialFunctionMode==MODE_NORMAL))		//130311vi01
					{
					vErrorModeProcess(bEventData1,bEventData2);
					}
				break;	//130309vi01&&&
			}
		}
	/*
	else
		{
		if( (bPowerMode==POWER_MODE_OFF) && (!fgBatteryIsCharging())&&(fgHdmiDetect==FALSE) )	//110121a01davy
			{
			if(wTimerCount>=WAIT_STANDBY_TIMEOUT)   //090103a02bi&&&	//090730a01h
				{
				//vSleepMode();
				}
			}
		}
	*/
}
#endif


void vSleepMode(void)
{
}

void vInitialVariable(void)
{
	bPlugInACPowerTimeCount=0;

	bLEDShowData1=0;//130328gr01***
	bLEDShowData2=0;
	bLEDBlinkData1=0;	
	bLEDBlinkData2=0;	
	bLEDAutoOffData1=0; 
	bLEDAutoOffData2=0; //130328gr01&&&
	
	vMcuEepromWriteByte(EE_OSCILLATE_INITIAL_PROCESS, FALSE);//130409Ke05	//130409Ke06
	//bAirVolumeStore = bMcuEepromReadByte(EE_AIR_VOLUME);	//130426Ja01	//130502Ja01
	//bAirVolume=bMcuEepromReadByte(EE_AIR_VOLUME);	//130306Ke01
	//bWatchMode=bMcuEepromReadByte(EE_WATCH_MODE);	//130402Me02
	//bIonMode=bMcuEepromReadByte(EE_ION_MODE);	//130425le01
	bFilterCleanSec=0;		//130427ra01
	bFilterCleanMin=0;		//130427ra01
}

void vInitialWDT(void)
{	//130222gr01***
	WDT_PRESCALER_ENABLE;
//	WDT_PRESCALE_1_256;	// 4s
//	WDT_PRESCALE_1_64;		// 1s
	WDT_PRESCALE_1_32;		// 0.5s	//130316ha01
	WDT_EN();
}	//130222gr01&&&

#if 0	//130419ha01
void vInitialInterrupt(void)
{
	INTERRUPT_DISI_HARDWARE_DISABLE;
}
#endif	//130419ha01


void vPlayerPollingFunction(void)
{
	vPollingOTP_INT();//130302sh01
	vPollingTouchINT(); //130305gr01
	if(bMixQueueRemain>=(QUEUE_SIZE_I2C*3))//130420sh02
		{
		if(bBuzzerType!=PI_NONE)	//130321ha02
			{
			//vI2cSendCommandBuzzer(bBuzzerType);	//130321ha02//130415sh01
			vI2cSendCommand2Para(COMMAND_SUB_MAIN_BUZZER_MODE,bBuzzerType);//130415sh01
			bBuzzerType=PI_NONE;	//130321ha02
			}

		if((bLouverType!=LOUVER_NONE)&&(fgLouverInitialFinish==TRUE))	//130325ha01***//130423Me01
			{
			vI2cSendCommand2Para(COMMAND_SUB_MAIN_LOUVER_MODE,bLouverType);
			if(bLouverType!=LOUVER_STOP)	//130424Me01***
				{
				fgVerticalMotorOn=TRUE;
				}
			else
				{
				fgVerticalMotorOn=FALSE;
				}		//130424Me01&&&
			bLouverType=LOUVER_NONE;
			}	//130325ha01&&&
		
		if(bOscillateType!=OSCILLATE_NONE)	//130325ha01***
			{
			vOscillateStatusCheck();	//130412Ke04
			bOscillateType=OSCILLATE_NONE;
			}	//130325ha01&&&
		}
		if(bFanVolumeShowType!=DISPLAY_TIME_NONE)	//130424Ke03***		 //130426jac01***
			{
			vFanVolumeShow();
			bFanVolumeShowType=DISPLAY_TIME_NONE;
			}	//130424Ke03&&&

		if(bFanVolumeType!=FAN_VOLUME_NONE)	//130424Ke03***
			{
			vFanVolumeSetValue();
			bFanVolumeType=FAN_VOLUME_NONE;
			}	//130424Ke03&&&		 //130426jac01&&&
}

//void vCheckPeripheralStatus(void)
//{
//	vAutoRestart();	//130306le01
//}

#if 0	//130419ha01
void vInitialBoard(void)
{
	vInitialTimer3();
	vInitialADC();
	vInitialTCC();
//	vInitialEEPROM();
	vInitialGPIO();
	vInitial7SegLedDisplay();			// 130328jac01
	vInitialUART();
	vInitialPWMA();                                                                      
	vInitialPWMB();
	vInitialWDT();
	vInitialI2C();
	
	//vInitialInterrupt();	//130419ha01
	INTERRUPT_DISI_HARDWARE_DISABLE;	//130419ha01
	
	vInitialVariable();
	//vInitialTouchSensor(); //130305gr01
}
#endif	//130419ha01

void main(void)
{
	INT_DIS();
	//vInitialBoard();
	vInitialTimer3();
	vInitialADC();
	vInitialTCC();
	vInitialEEPROM();
	vInitialGPIO();
	vInitial7SegLedDisplay();			// 130328jac01
	vInitialUART();
	vInitialPWMA();                                                                      
	vInitialPWMB();
	vInitialWDT();
	vInitialI2C();
	
	//vInitialInterrupt();	//130419ha01
	INTERRUPT_DISI_HARDWARE_DISABLE;	//130419ha01
	
	vInitialVariable();
	//vInitialTouchSensor(); //130305gr01
	INT_EN();               //  Before initial the interrupt is disable.

//	vCheckPeripheralStatus();
	vAutoRestart();	//130306le01
	
	//vMainLoop();	//130307ha01***
	while(1)
		{
		WDT_CLEAR();
		INT_DIS();
		vInitialTouchSensor(); //130305gr01
		INT_EN();
		INT_DIS();
		vTimer1ms();	//130114sh01
		INT_EN();
		INT_DIS();
		vTimer25ms();	//130114sh01
		INT_EN();
		INT_DIS();
		vTimer100ms();	// 130315ja01
		INT_EN();
		INT_DIS();
		vTimer1s();		//130114sh01
		INT_EN();
		INT_DIS();
		vPlayerPollingFunction();
		INT_EN();
//		INT_DIS();	//130419ha01
//		vCheckI2CCommandQueue();	//130419ha01
//		INT_EN();	//130419ha01
//		INT_DIS();	//130419ha01
//		vIRCheck();	//130419ha01
		//vMcuEepromService();	//130119le01
//		INT_EN();	//130419ha01
		INT_DIS();
		vCheckEvent();
		INT_EN();
		INT_DIS();
		vEventKeyProcess();
		INT_EN();
		INT_DIS();
		vPowerOnMode();
		INT_EN();
		INT_DIS();
		vPowerOffMode();	//130321ha01
		INT_EN();
		INT_DIS();
		vDemoModeKeyProcess();	//130329ha01
		INT_EN();
#ifdef FUNCTION_CHECKER_MODE_FUNCTION		
		INT_DIS();
		vFunctionCheckerModeKeyProcess();	//130329ha01
		INT_EN();
#endif		
		INT_DIS();
		vMonitorModeKeyProcess();	//130329ha01
		INT_EN();
		bIRKey=IR_NONE;	//130329ha01
		}
	//130307ha01&&&
}

