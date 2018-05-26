#define _MODE_WATCH_C_
#include "general.h"

BOOL fgDisplayLEDAirVolume1To9=FALSE;
#ifdef WATCH_MODE_FUNCTION
//130308Me01***	


void vSetWatchMode(BYTE bwatch_mode)
{
	bWatchMode=bwatch_mode;
	//switch(bWatchMode)	//130425Ja01&&&
		//{
		//default:
		//case WATCH_MANUAL:

		if(bWatchMode == WATCH_MANUAL)
			{
//			if(fgIsNotIonMode())
//				{
//				vSetKeyState(KEY_NORMAL);
//				}
			bAdjustAutoFanVolume = AUTO_FAN_NORMAL;	//130502Ja01
			bAirVolumeStore = bMcuEepromReadByte(EE_AIR_VOLUME);	//130504Ja03
			fgDisplayLEDAirVolume1To9=FALSE;		//130410Me01
			if(fgIsInPowerOffMode())	//130322me01
				{
				if(fgFilterNeedClean==TRUE)	//130402vi01
					{
					vDisplayLEDFilterCleanOff();	//130402vi01
					}
				vDisplayLEDAirVolume1BlinkOff();	//130322me01
				if(fgIsInTimerOnOffFunction())	//130402Ti01***
					{
					vDisplayLEDAirVolumeSettingIndicationOff();
					vDisplay7SegShowAirVolumeOff();
					vDisplayLEDAirVolume1to9Off();
					}	//130402Ti01&&&
				}
			else	//if(fgIsInPowerOnMode())	//130416Me02***
				{
				if(fgIsNotIonMode())
					{
					bAirVolume=bMcuEepromReadByte(EE_AIR_VOLUME);
					vFanVolumeSet(bAirVolume);
					}
				vDisplayLEDAirVolumeOn(bAirVolume);	//130410Me01	//130502Me01
				}	//130416Me02&&&
			
			//vDisplayLEDWatchRedOff();
			vDisplayLEDWatchGreenOff();
			//vDisplayLEDWarningBuzzerOff();
			vDisplayLEDWatchRedBlinkOff();
			vDisplayLEDWarningBuzzerBlinkOff();		//130401Me02
			vDisplayLEDTubeWhiteBlinkOff();//130402Me03
			if(fgIsNotLightOffFunction())	//130409Li01***
				{
				if(fgAutoRestartFirstPower==FALSE)	//130415le01***
					{
					vDisplayLEDBright();
					}	//130415le01&&&		
				if((fgPCIIsOverTime==FALSE)&&fgIsInPowerOnMode())
					{
					vDisplayLEDTubeWhiteOn();
					}
				}	//130409Li01&&&
			if((bWatchZone==ZONE_DANGER)||(bWatchZone==ZONE_VIRUS))	//130325Me01***
				{
				vDisplay7SegMessageClear();
				}	//130325Me01&&&
			bWatchZone=ZONE_NORMAL;
			}

			//break;	
		//case WATCH_MODE_WITH_BUZZER:
		if(bWatchMode == WATCH_MODE_WITH_BUZZER)
			{
			//vSetKeyState(KEY_WATCH_OR_ION_MODE);	//130413lo01
			fgLastLightSourceIsDark=FALSE;//130417sh03
			vDisplayLEDWatchGreenOn();
			vDisplayLEDWarningBuzzerOn();
			}
			//break;
		//case WATCH_MODE_WITHOUT_BUZZER:
		if(bWatchMode == WATCH_MODE_WITHOUT_BUZZER)
			{
			//vSetKeyState(KEY_WATCH_OR_ION_MODE);	//130413lo01
			if((bWatchZone==ZONE_NORMAL))	//||(bWatchZone==ZONE_CAUTION))//130403Me01	//130410Me03
				{
				vDisplayLEDWatchGreenOn();
				}
			vDisplayLEDWarningBuzzerBlinkOff();	
			vDisplayLEDWarningBuzzerOff();
			}
			//break;
		//}	//130425Ja01&&&
	//130401Me01***
	if(fgIsInPowerOnMode()&&(bWatchZone!=ZONE_DANGER)&&(bWatchZone!=ZONE_VIRUS))	 //130402Me01  //130409lo01//130416Me01
		{
		//130420Ju01***
		if(!fgOscillateInitialProcess)
			{
			vDisplayLEDAngleSettingIndicationOff(); 
			fgOscillateAngleIsShowing=FALSE;
			if(bErrorMode != ERROR_TEM_HUM_SENSOR)		//130427ma02
				{
				vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);
				}
			//vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);		// 130415jac02
			}
		//130420Ju01&&&
		}
		//130401Me01&&&

	if(bErrorMode != ERROR_TEM_HUM_SENSOR)	//130427ma02***
		{
		vMcuEepromWriteByte(EE_WATCH_MODE,bWatchMode);
		}	//130427ma02&&&
	vSubMcuSendWatchModeStatus(bWatchMode);
}

void vWatchModeKey(void)		
{
	//if((bWatchMode!=WATCH_MANUAL)&&(bErrorMode==ERROR_TEM_HUM_SENSOR))	//tem and huminity error
	if(bErrorMode==ERROR_TEM_HUM_SENSOR)	//130312Me02					//tem and huminity error
		{
		vBuzzerOutput(PI_PI_PI);
		return;
		}

	vAutoRestartFunctionWithin10s();					//auto restar function

	if(fgIsInPowerOffMode())
		{
		vDisplayLEDAirVolume1BlinkOn(DISPLAY_TIME_1_2_SECOND);		//air volume 1 indication blink(1.2s)	
		}

	
	bWatchMode++;
#if 0
	switch(bWatchMode)
		{
		default:
			bWatchMode=WATCH_MANUAL;
		case WATCH_MANUAL:
			//if(bIonMode==ION_MANUAL)
				//{
				//vSetKeyState(KEY_NORMAL);
				//}
			//pipi
			vBuzzerOutput(PI_PI);
			//130313Me01***
			//vDisplayLEDWatchGreenOff();
			//vDisplayLEDWarningBuzzerOff();
			//vDisplayLEDWatchRedBlinkOff();
			//vDisplayLEDTubeWhiteBlink(0,FALSE);
			//vDisplay7SegMessageClear();
			//bWatchZone=ZONE_NORMAL;
			//if(bIonMode==ION_MANUAL)
				//{
				//bAirVolume=bMcuEepromReadByte(EE_AIR_VOLUME);
				//vFanVolumeSet(bAirVolume);
				//}
			//130313Me01&&&
			break;
		case WATCH_MODE_WITH_BUZZER:
			//vSetKeyState(KEY_WATCH_OR_ION_MODE);
			//LedWatchGreen light;
			//vDisplayLEDWatchGreenOn();
			//LedWarningBuzzer light;
			//vDisplayLEDWarningBuzzerOn();
			//pi(LOUD)
			vBuzzerOutput(PI_LOUD);
			break;
		case WATCH_MODE_WITHOUT_BUZZER:
			//vSetKeyState(KEY_WATCH_OR_ION_MODE);
			//LedWatchGreen light;
			//vDisplayLEDWarningBuzzerBlinkOff();	//130313Me01
			//vDisplayLEDWarningBuzzerOff();	//130313Me01
			//pi
			vBuzzerOutput(PI);
			break;
	}
#else
	if(bWatchMode==WATCH_MODE_WITH_BUZZER)
		{
		vBuzzerOutput(PI_LOUD);
		}
	else if(bWatchMode==WATCH_MODE_WITHOUT_BUZZER)
		{
		vBuzzerOutput(PI);
		}
	else
		{
		bWatchMode=WATCH_MANUAL;
		vBuzzerOutput(PI_PI);
		}
#endif
	
		/*	//130329Me01***		//130401Me01***
	if((bWatchMode!=WATCH_MANUAL)||(bWatchZone!=ZONE_DANGER))
		{
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);
		vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);
		}
	*/	//130329Me01&&&		//130401Me01&&&
	
	vSetWatchMode(bWatchMode);
	vFilterCleanPowerCheck();  //130417ma01	
	//touch mcu send watch mode to main mcu
	//vMcuEepromWriteByte(EE_WATCH_MODE,bWatchMode);
	//vSubMcuSendWatchModeStatus(bWatchMode);
}	

void vWatchModeZoneChange(void)
{	
	if(fgIsNotWatchMode())
		{
		return;
		}
	fgDisplayLEDAirVolume1To9=FALSE;
	vDisplayLEDWatchGreenOff();
	//vDisplayLEDWatchRedOff();	//130416Me03
	vDisplayLEDWatchRedBlinkOff();
	//vDisplayLEDWarningBuzzerOff();
	vDisplayLEDWarningBuzzerBlinkOff();
	if((bWatchZone!=ZONE_DANGER)&&fgIsInPowerOnMode())	 //130410Me02***//130419Me01
		{
		vDisplayLEDAirVolumeOn(bAirVolume);
		}	//130410Me02&&&
	
	//130407Me01***
	if((bWatchZone==ZONE_DANGER)||(bWatchZone==ZONE_VIRUS))
		{	
		//130420Ju01***
		if(!fgOscillateInitialProcess)
			{
			vDisplayLEDAirVolumeSettingIndicationOff();
			vDisplayLEDAngleSettingIndicationOff();	//130412Me01
			fgOscillateAngleIsShowing=FALSE;
			vDisplay7SegMessageClear();
			}
		//130420Ju01&&&
		}	
	//130407Me01&&&
	//if((bWatchZone==ZONE_CAUTION)||(bWatchZone==ZONE_PRECAUTION)||(bWatchZone==ZONE_NORMAL))	//130322me01
	else
		{
		//vDisplayLEDWatchRedBlinkOff();
//		vDisplayLEDBlink(LED_TUBE_WHITE,DISPLAY_TIME_0_5_SECOND,FALSE);
		vDisplayLEDTubeWhiteBlinkOff();		//130402Me03
		if(fgIsNotLightOffFunction())		//130427Me01***
			{	
			if((fgPCIIsOverTime==FALSE)&&fgIsInPowerOnMode())
				{
				vDisplayLEDTubeWhiteOn();
				}
			}	//130427Me01&&&
		//130407Me01***
		//vDisplayLEDWarningBuzzerBlinkOff();
		//vDisplay7SegShowLoBlinkOff();
		//vDisplay7SegShowHiBlinkOff();
		vDisplay7SegBlinkOff();
		//130407Me01&&&

		//130401Me05***
		//if((bWatchZone==ZONE_DANGER)||(bWatchZone==ZONE_VIRUS))	//130325Me01***
			//{
			//vDisplay7SegMessageClear();	//130407Me01
			//}	//130325Me01&&&	//130401Me05&&&
		if(bWatchMode==WATCH_MODE_WITH_BUZZER)
			{
			vDisplayLEDWarningBuzzerOn();
			}
		}
	
	switch(bWatchZone)
		{
		case ZONE_VIRUS:
//			vDisplayLEDBlink(LED_TUBE_WHITE,DISPLAY_TIME_0_5_SECOND,TRUE);	//plasmacluster sign (blue)  0.5s blink
			//vDisplayLEDWatchRedBlinkOn(DISPLAY_TIME_0_5_SECOND);
			//7seg  "lo"0.5s blink
			vDisplay7SegShowLoBlinkOn(DISPLAY_TIME_0_5_SECOND);
			//if(bWatchMode==WATCH_MODE_WITH_BUZZER)
				//{
				//vDisplayLEDWarningBuzzerBlinkOn(DISPLAY_TIME_0_5_SECOND);
				//}
			goto warn_buzzer_blink_and_led_blink;
			break;
		case ZONE_DANGER:
			//vDisplayLEDWatchRedBlinkOn(DISPLAY_TIME_0_5_SECOND);
//			vDisplayLEDBlink(LED_TUBE_WHITE,DISPLAY_TIME_0_5_SECOND,TRUE);	//plasmacluster sign (blue)  0.5s blink
			
			//7seg "HI" 0.5s blink
			vDisplay7SegShowHiBlinkOn(DISPLAY_TIME_0_5_SECOND);
			//if(bWatchMode==WATCH_MODE_WITH_BUZZER)
				//{
				//vDisplayLEDWarningBuzzerBlinkOn(DISPLAY_TIME_0_5_SECOND);
				//}
			if(fgIsInPowerOnMode())
				{
				fgDisplayLEDAirVolume1To9=TRUE;	//Air Volume indication 1 to 9 are changed every 0.5s
				}
			goto warn_buzzer_blink_and_led_blink;
			break;
		case ZONE_PRECAUTION:
			//vDisplayLEDBlink(LED_WATCH_RED,DISPLAY_TIME_0_5_SECOND,FALSE);
			//vDisplayLEDBlink(LED_TUBE_WHITE,DISPLAY_TIME_0_5_SECOND,FALSE);
			//vDisplayLEDBlink(LED_WARNING_BUZZER,DISPLAY_TIME_0_5_SECOND,FALSE);
			//vDisplay7SegMessageClear();
			vDisplayLEDWatchRedOn();	//watch mode red
			//if(bWatchMode==WATCH_MODE_WITH_BUZZER)
				//{
				//vDisplayLEDWarningBuzzerOn();
				//}	
			break;
		case ZONE_CAUTION:
			//vDisplayLEDBlink(LED_WATCH_RED,DISPLAY_TIME_0_5_SECOND,FALSE);
			//vDisplayLEDBlink(LED_TUBE_WHITE,DISPLAY_TIME_0_5_SECOND,FALSE);
			//vDisplayLEDBlink(LED_WARNING_BUZZER,DISPLAY_TIME_0_5_SECOND,FALSE);
			//vDisplay7SegMessageClear();
			vDisplayLEDWatchRedOn();	//watch mode red
			vDisplayLEDWatchGreenOn();	//watch mode green light	
			//if(bWatchMode==WATCH_MODE_WITH_BUZZER)
			//	{
			//	vDisplayLEDWarningBuzzerOn();
			//	}
			break;

		case ZONE_NORMAL:	//130322me01
			vDisplayLEDWatchGreenOn();	//130322me01
			break;
	
		warn_buzzer_blink_and_led_blink:
			{	
			//plasmacluster sign (blue)  0.5s blink
			vDisplayLEDTubeWhiteBlinkOn(DISPLAY_TIME_0_5_SECOND);		   //130402Me03
			vDisplayLEDWatchRedBlinkOn(DISPLAY_TIME_0_5_SECOND);
			if(bWatchMode==WATCH_MODE_WITH_BUZZER)
				{
				vDisplayLEDWarningBuzzerBlinkOn(DISPLAY_TIME_0_5_SECOND);
				}
			}
		default:
			break;
		}
	
	/*
	if(bPowerMode==POWER_MODE_ON)
		{
		fgDisplayLEDAirVolume1To9=FALSE;
		switch(bWatchZone)
			{
			case ZONE_VIRUS:
				vDisplay7segLedAllOff();
				vDisplayLEDBlink(LED_WATCH_RED,DISPLAY_TIME_0_5_SECOND,TRUE);				//watch mode red	0.5s blink
				vDisplay7SegBlinkMessage(CMD_7SEG_MESSAGE_SHOW,MESSAGE_7SEG_LO,DISPLAY_TIME_0_5_SECOND,TRUE);
				//7seg  "lo"0.5s blink
				if(bWatchMode==WATCH_MODE_WITH_BUZZER)
					{
					//warnbuzzer 0.5s blink(red)
					vDisplayLEDBlink(LED_WARNING_BUZZER,DISPLAY_TIME_0_5_SECOND,TRUE);
					}
				break;
			case ZONE_DANGER:
				//watch mode red	0.5s blink
				//plasmacluster sign (blue)  0.5s blink
				//7seg "HI" 0.5s blink
				//Air Volume indication 1 to 9 are changed every 0.5s
				vDisplay7segLedAllOff();
				vDisplayLEDBlink(LED_WATCH_RED,DISPLAY_TIME_0_5_SECOND,TRUE);
				vDisplayLEDBlink(LED_TUBE_WHITE,DISPLAY_TIME_0_5_SECOND,TRUE);
				vDisplay7SegBlinkMessage(CMD_7SEG_MESSAGE_SHOW,MESSAGE_7SEG_HI,DISPLAY_TIME_0_5_SECOND,TRUE);
				if(bWatchMode==WATCH_MODE_WITH_BUZZER)
					{
					//warnbuzzer 0.5s blink(red)
					vDisplayLEDBlink(LED_WARNING_BUZZER,DISPLAY_TIME_0_5_SECOND,TRUE);
					}
				fgDisplayLEDAirVolume1To9=TRUE;
				break;
			case ZONE_PRECAUTION:
				//watch mode red
				vDisplay7segLedAllOff();
				vDisplayLEDWatchRedOn();
				if(bWatchMode==WATCH_MODE_WITH_BUZZER)
					{
					//warnbuzzer (red)
					vDisplayLEDWarningBuzzerOn();
					}				
				break;
			case ZONE_CAUTION:
				//watch mode red light
				//watch mode green light	
				vDisplayLEDWatchRedOn();
				vDisplayLEDWatchGreenOn();
				break;
			default:
				break;
			}
		}
	else if((bPowerMode==POWER_MODE_OFF)||(bPowerMode==POWER_MODE_OFF_PROGRESS))
		{
		vDisplayLEDAirVolume1BlinkOn(DISPLAY_TIME_1_2_SECOND)//air volume 1 indication blink(1.2s)	
		switch(bWatchZone)		
			{
			case ZONE_VIRUS:
				//watch mode red 0.5s blink
				//7seg "LO" 0.5s blink
				vDisplayLEDBlink(LED_WATCH_RED,DISPLAY_TIME_0_5_SECOND,TRUE);
				vDisplay7SegBlinkMessage(CMD_7SEG_MESSAGE_SHOW,MESSAGE_7SEG_LO,DISPLAY_TIME_0_5_SECOND,TRUE);
				if(bWatchMode==WATCH_MODE_WITH_BUZZER)
					{
					//warnbuzzer 0.5s blink
					vDisplayLEDBlink(LED_WARNING_BUZZER,DISPLAY_TIME_0_5_SECOND,TRUE);
					}
				break;
			case ZONE_DANGER:
				//watch mode red	0.5s blink
				//7seg "HI" 0.5s blink
				//plasmacluster sign (blue)  0.5s blink
				vDisplayLEDBlink(LED_WATCH_RED,DISPLAY_TIME_0_5_SECOND,TRUE);
				vDisplayLEDBlink(LED_TUBE_WHITE,DISPLAY_TIME_0_5_SECOND,TRUE);
				vDisplay7SegBlinkMessage(CMD_7SEG_MESSAGE_SHOW,MESSAGE_7SEG_HI,DISPLAY_TIME_0_5_SECOND,TRUE);
				if(bWatchMode==WATCH_MODE_WITH_BUZZER)
					{
					//warnbuzzer 0.5s blink(red)
					vDisplayLEDBlink(LED_WARNING_BUZZER,DISPLAY_TIME_0_5_SECOND,TRUE);
					}			
				break;
			case ZONE_PRECAUTION:
				//watch mode red	0.5s blink
				vDisplayLEDBlink(LED_WATCH_RED,DISPLAY_TIME_0_5_SECOND,TRUE);
				if(bWatchMode==WATCH_MODE_WITH_BUZZER)
					{
					//warnbuzzer 0.5s blink(red)
					vDisplayLEDBlink(LED_WARNING_BUZZER,DISPLAY_TIME_0_5_SECOND,TRUE);
					}
				break;
			case ZONE_CAUTION:
				//watch mode red light
				//watch mode green light	
				vDisplayLEDWatchRedOn();
				vDisplayLEDWatchGreenOn();
				break;
			default:
				break;
			}
		}
	*/	
}
//130308Me01&&&

#endif
