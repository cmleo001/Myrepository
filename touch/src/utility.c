#define _UTILITY_C_
#include "general.h"

/////////////////////////////////////////////////////
// About ON/OFF Timer
/////////////////////////////////////////////////////

BYTE wOnOffTimerCountLo=100;	//130417Ti01***
BYTE wOnOffTimerCountHi=0;
#define HOUR_1 36		// 3600 second=1 hour
#define HOUR_2 72		// 7200 second=2 hour
#define HOUR_4 144	// 14400 second=4 hour
#define HOUR_6 216	// 21600 second=6 hour	//130417Ti01&&&

#define TIMER_MODE_SPEED_UP	20	// On/Off timer mode at speed up is 1/20.
#define ION_MODE_SPEED_UP		10	// Plasmacluster shower mode at speed is 1/10.
BOOL fgOnOffTimerReach=FALSE;	//130327Ti01


#define AIR_VOLUME_DEFAULT_VALUE 4	//130307le01

//130308le02***
void vAutoRestartFunctionWithin10s(void)
{
	if(fgIsAutoRestartFunction())	
		{
		if(bAutoRestartTimerCounter>0)
			{
			bAutoRestartTimerCounter=0;
			//vDisplayLEDAllOff();//130419gr01
			//vDisplay7segLedAllOff();	//130327le02//130419gr01
			vDisplay7segLedAndTouchLedAllOff();//130419gr01

			}
		}
}	//130308le02&&&

void vChildLock(void)
{
	vAutoRestartFunctionWithin10s();	//130308le02
//130128le01***
	if(fgIsChildLockFunction())
		{	//Child Lock OFF
		fgChildLockEnable = FALSE;
		//close Child Lock Sign and Child Lock Indication 
		vDisplayLEDChildLockSignOff();
		vDisplayLEDChildLockIndicationOff();
		vBuzzerOutput(PI_PI);	//sound pipi
		}
	else
		{	//Child Lock ON
		fgChildLockEnable = TRUE;
		//open Child Lock Sign and Child Lock Indication
		vDisplayLEDChildLockSignOn();
		vDisplayLEDChildLockIndicationOn();
		vBuzzerOutput(PI);	//sound pi
		}

	//Child Lock Memory Function(only when auto restart function is valid)
	if(fgIsAutoRestartFunction())
		{
		vMcuEepromWriteByte(EE_CHILD_LOCK,fgChildLockEnable);
		}
//130128le01&&&
}

void vAutoRestartFunction1sTimer(void)	//130308le02***
{
	if(bAutoRestartTimerCounter)
		{
		bAutoRestartTimerCounter--;
		if(bAutoRestartTimerCounter==0)
			{
			//vDisplayLEDAllOff();//130419gr01
			//vDisplay7segLedAllOff();//130419gr01
			vDisplay7segLedAndTouchLedAllOff();//130419gr01

			return;
			}
		}
}	//130308le02&&&


//130306le01***
void vAutoRestartKey(void)
{
	//if watch mode is set,even though the power is off ,the operating is invalid.
	if(fgIsInWatchMode()||fgIsInPowerOnMode()||fgIsInTimerOnOffFunction())	//It's mean in watch mode.	 //130328le02 130401le01
		{
		return;
		}

	if(fgIsAutoRestartFunction())
		{
		fgAutoRestartFunction=FALSE;
		vBuzzerOutput(PI_PI);	//buzzer sound pipi
		//vDisplay7segLedAllOff();		//all leds do not light up //130419gr01
		//vDisplayLEDAllOff();	//130308le01 //130419gr01
		vDisplay7segLedAndTouchLedAllOff(); //130419gr01

		}
	else
		{
		fgAutoRestartFunction=TRUE;
		bAutoRestartTimerCounter=10;	//130308le02
		vBuzzerOutput(PI);	//buzzer sound pi
		
		//vDisplay7segLedAllOn();	//all leds light up for 10s //130419gr01
		//vDisplayLEDAllOn();	//130308le01 //130419gr01
		vDisplay7segLedAndTouchLedAllOn();//130419gr01

		}
	//write the auto restart function valid/invalid to eeprom
	vMcuEepromWriteByte(EE_AUTO_START,fgAutoRestartFunction);
	
}
//130306le01&&&

//130306le02***
void vLightOff(void)
{
	if(fgIsInWatchMode()||fgIsInPowerOnMode())	//It's mean in watch mode.	//130328le03
		{
		return;
		}

	/*
	In "Danger Zone" or "Virus Zone", even when "Light OFF function" is valid, "Plasmacluster Sign(Blue)" isn't turned off 
         but blinks (0.5sec ON / 0.5sec OFF). 
	*/
	if(fgIsLightOffFunction())
		{	// on-->off
		fgLightOffFunction=FALSE;
		vBuzzerOutput(PI_PI);
		//Air volume becomes brightness normal
		vDisplayLEDBright();	//130327le03
		//vDisplayLEDTubeWhiteOn();	//turn on Plasmacluster sign(Blue)	//130322gr01	130328le03
		
		}
	else
		{	//off-->on
		fgLightOffFunction=TRUE;
		vBuzzerOutput(PI);
		//Air volume becomes brightness 30%
		vDisplayLEDDim();	//130327le03
		if((bWatchZone==ZONE_DANGER)||(bWatchZone==ZONE_VIRUS))	//130327le03***	130328le03
			{
			vDisplayLEDTubeWhiteBlinkOn(DISPLAY_TIME_0_5_SECOND);
			}
		else	//130328le03
			{
			vDisplayLEDTubeWhiteOff();	//turn off Plasmacluster sign(Blue) in spite of the judge result of "light sensor"		//130322gr01
			}
		}
	//write Light Off Function to eeprom
	if(fgIsAutoRestartFunction())
		{
		vMcuEepromWriteByte(EE_LIGHT_OFF,fgLightOffFunction);
		}
}
//130306le02&&&


//130306le03***
//- Auto Restart function is valid or invalid
//If "Auto Restart function" is valid, the following items are memorized.
//- Power
//- Watch Mode
//- Air Volume
//- Child Lock
//- Rotation Mode
//- Louver Mode
//	If "Louver Mode" is "STOP", the stopped position is memorized.
//- Light OFF Function
void vAutoRestart(void)
{
	//130307le01***
	fgAutoRestartFunction=bMcuEepromReadByte(EE_AUTO_START);

	if(fgIsAutoRestartFunction())
		{
		fgAutoRestartFirstPower=TRUE;	//130415le01
		//bWatchMode=bMcuEepromReadByte(EE_WATCH_MODE);	//130417le01***
		//vSetWatchMode(bWatchMode);
		vSetWatchMode(bMcuEepromReadByte(EE_WATCH_MODE));	//130417le01&&&
		//transfer bWatchMode to main MCU by i2c
		
		fgLightOffFunction=bMcuEepromReadByte(EE_LIGHT_OFF);

		fgChildLockEnable=bMcuEepromReadByte(EE_CHILD_LOCK);
		
		//130412Ke04***
		bOscillatingMode=bMcuEepromReadByte(EE_OSCILLATE_MODE_ON_OFF);
		bOscillatingModeAngle=bMcuEepromReadByte(EE_OSCILLATE_MODE_ANGLE);	//130420Ke01

		bLouverMode=bMcuEepromReadByte(EE_LOUVER_MODE);
		bLouverAngle=bMcuEepromReadByte(EE_LOUVER_ANGLE);
	
		/*	//130422gr01***
		if(bLouverMode==LOUVER_SWING)
			{
			vLouverModeSet(bLouverMode);
			}
		else
			{
			vLouverModeSet(bLouverAngle);
			}
			*/	//130422gr01&&&
	
		//fgAutoRestartFirstPower=TRUE;	//130327le01	//130415le01
		//bPowerMode=bMcuEepromReadByte(EE_POWER_MODE);	//130417le01***
		//if(fgIsInPowerOnMode())	//power on
		if(bMcuEepromReadByte(EE_POWER_MODE)==POWER_MODE_ON)	//130417le01&&&
			{
			if(bOscillatingMode==OSCILLATE_ON)	//130420Ke01***
				{
				vOscillateModeSet(bOscillatingModeAngle);
				}	//130420Ke01&&&

			//bIonMode=bMcuEepromReadByte(EE_ION_MODE);	//130417le01***
			//if(bIonMode==ION_CLOTHING_DEODORANT)
			if(bMcuEepromReadByte(EE_ION_MODE)==ION_CLOTHING_DEODORANT)	//130417le01&&&
				{
				fgExecutePowerOffMode=TRUE;	//130321ha01
				//vPowerOffMode();	//130321ha01
				}
			else
				{
				//bIonMode=ION_MANUAL;	//130417le01
				vModeIonManualInit();
				fgExecutePowerOnMode=TRUE;
				//vPowerOnMode();
				}

			//bTimerMode=bMcuEepromReadByte(EE_ON_OFF_TIMER);	//130417le01***
			//if(fgIsInTimerOnOffFunction())
			if(bMcuEepromReadByte(EE_ON_OFF_TIMER)!=TIMER_MODE_OFF)	//130417le01&&&
				{
				//bTimerMode=TIMER_MODE_OFF;	//130417le01
				fgExecutePowerOffMode=TRUE;
				fgExecutePowerOnMode=FALSE;	//130417le02
				//vPowerOffMode();
				}
			}
		else	//power off
			{
			fgExecutePowerOffMode=TRUE;	//130321ha01
			//vPowerOffMode();	//130321ha01
			}
		}
	else
		{
		//when first plug a socket and Auto Restart Function is invalid, set to default value

		vMcuEepromRealWrite(EE_OSCILLATE_MODE_ANGLE,OSCILLATE_15D);	//130412Ke04	130424le01
		
		//bAirVolume=AIR_VOLUME_DEFAULT_VALUE;	//130314le03***
		vMcuEepromRealWrite(EE_AIR_VOLUME,AIR_VOLUME_DEFAULT_VALUE);	//130316le01
		
		//bOscillatingMode=OSCILLATE_OFF;
		vMcuEepromRealWrite(EE_OSCILLATE_MODE_ON_OFF,OSCILLATE_OFF);	//130316le01
		
		//the louver stops after moving to the horizon position.
		vMcuEepromRealWrite(EE_LOUVER_ANGLE,LOUVER_HORIZONTAL_1);	//130422gr01

		//bLouverMode=LOUVER_STOP;
		vMcuEepromRealWrite(EE_LOUVER_MODE,LOUVER_STOP);	//130316le01
		
		//bWatchMode=WATCH_MANUAL;
		vMcuEepromRealWrite(EE_WATCH_MODE,WATCH_MANUAL);	//130316le01
		
		//bIonMode=ION_MANUAL;
		vMcuEepromRealWrite(EE_ION_MODE,ION_MANUAL);	//130314le03&&&	//130316le01
		}
	bAirVolumeStore = bMcuEepromReadByte(EE_AIR_VOLUME);	//130502Ja01	
	//130307le01&&&
}
//130306le03&&&


void vLightDarkEvent(void)
{
	//if(fgIsNotWatchMode()||((bErrorMode!=ERROR_TEM_HUM_SENSOR)&&(bErrorMode!=ERROR_NONE)))	//130326li01	//130409Li02//130417sh04
	if(fgIsNotWatchMode()||(fgAbnormalMode==TRUE))//130417sh04
		return;	//130326li01
	
	//if(fgIsLightOffFunction()||(fgPCIIsOverTime==TRUE))	//130409le02***//130409Li02	//130504Li01
	if(fgIsLightOffFunction())	//130504Li01
		{
		return;
		}	//130409le02&&&

	if(fgTheLightSourceIsDark)
		{	//Dark
		vDisplayLEDTubeWhiteOff();	//130322gr01
		//Tube LED dark.
		//Air Volume Indecation dark. 30%
		vDisplayLEDDim();	//130312Li02
		}
	else
		{	//Light
		if(fgIsInPowerOnMode()&&fgPCIIsOverTime==FALSE)	//130326li01	//130504Li01
			{
			vDisplayLEDTubeWhiteOn();	//130322gr01
			}
		//Tube LED light.
		//Air Volume Indecation light. 100%
		vDisplayLEDBright();		//130312Li02
		}
}
	
/////////////////////////////////////////////////////
// About Filter Clean
/////////////////////////////////////////////////////
//130122su01***
#define SEC_TO_MIN_CNT_TIMES				60		//'1s*60=1min counter number
#define NIN_TO_HOUR_CNT_TIMES	 			60		//'1min*60=1hour counter number
#define SEC_TO_HOUR_CNT_TIMES	 			3600	//'60min*60s=3600s=1hour counter number
#define SEC_TO_HOUR_SPEED_UP	 			1800	//'60min*60s=3600s=1hour counter number
#define FILTER_CLEAN_TIME_OUT_HOUR		720
#define FILTER_CLEAN_SPEED_UP_RATE		1800           //130402vi01
#define FILTER_CLEAN_SPEED_UP_1MIN_TO_HOUR	(FILTER_CLEAN_SPEED_UP_RATE/NIN_TO_HOUR_CNT_TIMES)		// 1min=1800*60=30hours	//130402vi01	

BYTE bFilterCleanSec=0;	//130402vi01	//130427ra01
BYTE bFilterCleanMin=0;		//130427ra01
//WORD wFilterCleanHour;		//130423vi02
BOOL fgFilterNeedClean=FALSE;	//130427ra01

#define FILTER_CLEAN_LOW_BYTE		bFilterCleanHourRegister[0]			//130423vi02***
#define FILTER_CLEAN_HIGH_BYTE 	bFilterCleanHourRegister[1]			//130423vi02&&&

void vFilterCleanPowerCheck(void)	//130402vi01
{
#if 0		//130402vi01
	if(bWatchMode!=WATCH_MANUAL)	//It's mean in watch mode.
		{
		}
	else
#endif		//130402vi01
	if(fgIsInPowerOffMode()&&fgIsNotWatchMode())//130402vi01***
		{
		return;
		}
	else		//130402vi01&&&
		{	//Not in watch mode.
		bFilterCleanSec = 0;	//130402vi01
//130423vi02***
		FILTER_CLEAN_HIGH_BYTE=bMcuEepromReadByte(EE_CLEANING_FILTER_TIME_HOUR_HIGH);		//130402vi01
		FILTER_CLEAN_LOW_BYTE=bMcuEepromReadByte(EE_CLEANING_FILTER_TIME_HOUR_LOW);		//130402vi01
//130423vi02&&&
		//"Filter Clean Sign(Orange)" lights up when the accumulated time comes up to 720 hours.
		if(wFilterCleanHour >= FILTER_CLEAN_TIME_OUT_HOUR)		
			{
			fgFilterNeedClean = TRUE;
			//"Filter Clean Sign(Orange)" LED lights up;
			vDisplayLEDFilterCleanOn();
			}
		}
}

void vFilterCleanTimeSave(void)
{
	//write accumulated time into EEPROM.	
	//130423vi02***
	vMcuEepromWriteByte(EE_CLEANING_FILTER_TIME_HOUR_LOW, FILTER_CLEAN_LOW_BYTE);
	vMcuEepromWriteByte(EE_CLEANING_FILTER_TIME_HOUR_HIGH, FILTER_CLEAN_HIGH_BYTE);
	//130423vi02&&&
	if(wFilterCleanHour >= FILTER_CLEAN_TIME_OUT_HOUR)		//"Filter Clean Sign(Orange)" lights up when the accumulated time comes up to 720 hours.
		{
		fgFilterNeedClean = TRUE;
		//"Filter Clean Sign(Orange)" LED lights up;
		vDisplayLEDFilterCleanOn();
		}
}

/*void timer_1s_callback(void)*/
void vFilterCleanTimer(void)
{
	//The accumulated time for cleaning Filter is counted when the power is "ON" and when the power is "OFF" in "watch mode".	

	if(fgAbnormalMode == TRUE)	//130412ma01*** 
		{
		return;
		}	//130412ma01&&&

	if(fgIsInPowerOnMode() || fgIsInWatchMode())		 
		{
		if(fgFilterNeedClean) 
			{
			return;	
			}
		bFilterCleanSec++;		//130402vi01
#if 0		//130402vi01
		//130312vi01***
		if(bSpecialFunctionMode==MODE_SPEED_UP)
			{
			wFilterCleanSec+=SEC_TO_HOUR_SPEED_UP;
			}
		else
			{
			wFilterCleanSec++;
			}

		if(wFilterCleanSec>=SEC_TO_HOUR_CNT_TIMES)
			{
			wFilterCleanSec-=SEC_TO_HOUR_CNT_TIMES;
			wFilterCleanHour++;
			//write accumulated time into data EEPROM every 1 hour.
			vFilterCleanTimeSave();		
			}
		//130312vi01&&&
#endif		//130402vi01
		if(bFilterCleanSec >= SEC_TO_MIN_CNT_TIMES)	//130402vi01***
			{
			bFilterCleanSec=0;
			bFilterCleanMin++;
			if(fgIsInSpeedUpMode())		
				{
				wFilterCleanHour+=FILTER_CLEAN_SPEED_UP_1MIN_TO_HOUR;
				vFilterCleanTimeSave();		
				}					
			else					
				{
				if(bFilterCleanMin >= NIN_TO_HOUR_CNT_TIMES)
					{
					bFilterCleanMin = 0;
					wFilterCleanHour++;
					vFilterCleanTimeSave();		
					}
				}
			//write accumulated time into data EEPROM every 1 hour.
			}			//130402vi01&&&
		}
}

//Reset Filter Clean time.
//pushing Reset button consecutive 3s clear the accumulated time for cleaning Filter.
void vResetFilterCleaningKey(void)		//130306a01v
{
	if(fgAbnormalMode==TRUE)		//130312vi02***
		{
		if(bErrorMode!=ERROR_TEM_HUM_SENSOR)//130424vi03
			{
			return;
			}
		}			//130312vi02&&&
	vBuzzerOutput(PI);
	bFilterCleanSec = 0;//130402vi01
	bFilterCleanMin = 0;//130402vi01
	wFilterCleanHour = 0;
	vFilterCleanTimeSave();
	fgFilterNeedClean = FALSE;
	//turns off "Filter Clean Sign" LED;
	vDisplayLEDFilterCleanOff();
}
//130122su01&&&


/////////////////////////////////////////////////////
// About ON/OFF Timer
/////////////////////////////////////////////////////

void vTimerLedDigitalOff(void)//130314Ti01***
{
	//LED_1 off
	vDisplayLEDTimer1Off();
	//LED_2 off
	vDisplayLEDTimer2Off();
	//LED_4 off
	vDisplayLEDTimer4Off();
	//LED_6 off
	vDisplayLEDTimer6Off();
}

void vTimerLedOnOffHourOff(void)
{
	//LED_ON off
	vDisplayLEDOnTimerOff();
	//LED_OFF off
	vDisplayLEDOffTimerOff();
	// LED_H off
	vDisplayLEDTimerHOff();
}//130314Ti01&&&


void vTimerOnOffStop(void)		//130306a05v***
{
	//if(fgIsInTimerOnOffFunction())	//130411Ti01
		{
		bTimerMode=TIMER_MODE_OFF;
		vMcuEepromWriteByte(EE_ON_OFF_TIMER,bTimerMode);//130411Ti01
		wOnOffTimerCountLo=100;//130417Ti01
		wOnOffTimerCountHi=0;//130417Ti01
		vTimerLedDigitalOff();//130314Ti01
		vTimerLedOnOffHourOff();//130314Ti01
		}
}
//130306a05v&&&

//130424vi01***
void vTimerLedOnOffShow(void)
{
	if(fgIsInPowerOnMode())
		{
		vDisplayLEDOffTimerOn();
		}
	else if(fgIsInPowerOffMode())
		{
		vDisplayLEDOnTimerOn();
		}
}

void vTimerShow(BYTE bTimer)			
{
	vDisplayLEDTimerHOn();
	switch(bTimer)
		{
		case TIMER_MODE_OFF:
			vTimerLedOnOffHourOff();
			break;
		case TIMER_MODE_1H:
			vDisplayLEDTimer1On();
			break;
		case TIMER_MODE_2H:
			vDisplayLEDTimer2On();
			break;
		case TIMER_MODE_4H:
			vDisplayLEDTimer4On();
			break;
		case TIMER_MODE_6H:
			vDisplayLEDTimer6On();
			break;
		}
}
//130424vi01&&&

void vTimerKey(void)//130125Ti01***
{
	//To shut down all display leds during leds light up for 10s with autoRestart key enable
	vAutoRestartFunctionWithin10s();	//130309Ti01
	
	vTimerLedOnOffHourOff();//130424vi01
	vTimerLedDigitalOff();	//130424vi01
/*		 //130426jac01
	if(fgIsInPowerOffMode())
		{
		//bAirVolume=bMcuEepromReadByte(EE_AIR_VOLUME);//130327Ti02***	
		//vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_5_SECOND);		// 130415jac02
		vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_5_SECOND);
		vDisplayLEDAirVolumeAutoOff(bAirVolume,DISPLAY_TIME_5_SECOND);//130327Ti02&&&
		}
*/			 //130426jac01
	bTimerMode++;
	switch(bTimerMode)
		{
		default:
			bTimerMode=TIMER_MODE_OFF;
		//case TIMER_MODE_OFF://130424vi01
			wOnOffTimerCountHi=0;//130417Ti01
			if(fgIsInPowerOffMode())	//130329Ti01***
				{
				vDisplayLEDAirVolumeSettingIndicationOff();
				vDisplay7SegShowAirVolumeOff();
				vDisplayLEDAirVolume1to9Off();
				}//130329Ti01&&&
			//PiPi
			vBuzzerOutput(PI_PI);
			break;
		case TIMER_MODE_1H: 
			wOnOffTimerCountHi=HOUR_1;//130417Ti01
			goto BUZZER;//130424vi01
		case TIMER_MODE_2H:
			wOnOffTimerCountHi=HOUR_2;//130417Ti01
			goto BUZZER;//130424vi01
		case TIMER_MODE_4H:
			wOnOffTimerCountHi=HOUR_4;//130417Ti01
			goto BUZZER;//130424vi01
		case TIMER_MODE_6H:
			wOnOffTimerCountHi=HOUR_6;//130417Ti01
			goto BUZZER;//130314Ti01&&&//130424vi01
		BUZZER://130424vi01
			if(fgIsInPowerOffMode())		// 130426jac01***
				{
				bAirVolume=bMcuEepromReadByte(EE_AIR_VOLUME);//130327Ti02***	//130503Ti01
				//vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_5_SECOND);		// 130415jac02
				vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_5_SECOND);
				vDisplayLEDAirVolumeAutoOff(bAirVolume,DISPLAY_TIME_5_SECOND);//130327Ti02&&&
				}		// 130426jac01&&&
			vBuzzerOutput(PI);//130424vi01
			break;//130314Ti01&&&
		}
	
	vTimerLedOnOffShow();		//130424vi01
	vTimerShow(bTimerMode);	//130424vi01
	//record bTimerMode to EEPROM
	vMcuEepromWriteByte(EE_ON_OFF_TIMER,bTimerMode);	//130309Ti01
	wOnOffTimerCountLo=100;//130418Ti01
}	

void vOnOffTimerSetAtSpeedUp(void)	//130312Ti02
{
	if(wOnOffTimerCountHi>0)//130418Ti01
		{
		wOnOffTimerCountLo-=(wOnOffTimerCountLo%20);//130417Ti01
		if(wOnOffTimerCountLo==0)
			{
			wOnOffTimerCountLo=100;
			wOnOffTimerCountHi--;
			}
		}
}

//The below function is called when timer 1s		//130125Ti01***//130417Ti01***
void vOnOffTimer(void)
{
	if(wOnOffTimerCountLo)
		{
		if(fgIsInSpeedUpMode())	//130312Ti02
			{	//Speed up mode.
			if(bIonMode==ION_PLASMA_CLUSTER_SHOWER)
				{
				wOnOffTimerCountLo-=ION_MODE_SPEED_UP;
				}
			else
				{
				wOnOffTimerCountLo-=TIMER_MODE_SPEED_UP;
				}
			}
		else
			{	//Normal mode
			wOnOffTimerCountLo--;
			}
		if(wOnOffTimerCountLo==0)
			{
			wOnOffTimerCountLo=100;
			if(wOnOffTimerCountHi)
				{
				wOnOffTimerCountHi--;
				if(wOnOffTimerCountHi==HOUR_1)	//130316Ti01***
					{
					bTimerMode=TIMER_MODE_1H;
					//LED_2 off	
					vDisplayLEDTimer2Off();
					//LED_1 on
					vDisplayLEDTimer1On();
					//Clothing mode needn't to write bTimerMode to EEPROM	//130311Ti01*** 			
					//if(bIonMode!=ION_CLOTHING_DEODORANT)	//130415Ti03
						{
						goto WRITE_TIMER_MODE_TO_EEPROM1;
						}	
					}
				else if(wOnOffTimerCountHi==HOUR_2)
					{
					bTimerMode=TIMER_MODE_2H;
					//LED_4 off
					vDisplayLEDTimer4Off();
					//LED_2 on
					vDisplayLEDTimer2On();
					goto WRITE_TIMER_MODE_TO_EEPROM1;
					}
				else if(wOnOffTimerCountHi==HOUR_4)
					{	
					bTimerMode=TIMER_MODE_4H;
					//LED_6 off
					vDisplayLEDTimer6Off();
					//LED_4 on
					vDisplayLEDTimer4On();
					goto WRITE_TIMER_MODE_TO_EEPROM1;
					}
				else if(wOnOffTimerCountHi==0)//130312Ti01***//130411Ti02***
					{
					bTimerMode=TIMER_MODE_OFF;
					fgOnOffTimerReach=TRUE;	//130327Ti01
					if(bIonMode==ION_PLASMA_CLUSTER_SHOWER)
						{
						vModeIonManualInit();
						}
					else
						{
						vPutEventQueue(EVENT_IR, IR_POWER, 0);
						}
					}//130312Ti01&&&
				else
					{
					return;
					}//130411Ti02&&&
				}
				//record bTimerMode to EEPROM
			WRITE_TIMER_MODE_TO_EEPROM1:
			if(bIonMode!=ION_CLOTHING_DEODORANT)//130415Ti03
				{
				vMcuEepromWriteByte(EE_ON_OFF_TIMER,bTimerMode);	//130309Ti01	//130316Ti01&&&
				}
			}						
		}
}//130125Ti01&&&//130417Ti01&&&



void vSetOnOffTimer(BYTE btimer_mode)		//130309Ti01***//130415Ti02
{
	vTimerLedDigitalOff();		//130424vi01	
	vTimerLedOnOffHourOff();		//130424vi01
	
#if 1
	//if(fgIsNotTimerOnOffFunction())//130316Ti01***//130415Ti02
	if(btimer_mode==TIMER_MODE_OFF)//130415Ti02
		{
		wOnOffTimerCountHi=0;//130417Ti01
		goto WRITE_TIMER_MODE_TO_EEPROM2;	
		}
	else if(btimer_mode==TIMER_MODE_1H)//130415Ti02
		{
		wOnOffTimerCountHi=HOUR_1;//130417Ti01
		//goto WRITE_TIMER_MODE_TO_EEPROM2;	//130504Ti01
		}
	else if(btimer_mode==TIMER_MODE_2H)//130415Ti02
		{
		wOnOffTimerCountHi=HOUR_2;//130410Ti01//130417Ti01
		}
	else if(btimer_mode==TIMER_MODE_4H)//130415Ti02
		{
		wOnOffTimerCountHi=HOUR_4;//130410Ti01//130417Ti01
		}
	else if(btimer_mode==TIMER_MODE_6H)//130415Ti02
		{
		wOnOffTimerCountHi=HOUR_6;//130410Ti01//130417Ti01
		}

	if(bIonMode!=ION_PLASMA_CLUSTER_SHOWER)	//130415Ti02***
		{
		vTimerLedOnOffShow();		//130424vi01***
		vTimerShow(btimer_mode);
		bTimerMode=btimer_mode;	//130424vi01&&&
		}//130415Ti02&&&
#else
	switch(bTimerMode)
	   {
	   case TIMER_MODE_OFF:
		   wOnOffTimerCount=0;
		   vTimerLedOnOffHourOff();//130314Ti01
		   break;
	   case TIMER_MODE_1H:
		   wOnOffTimerCount=HOUR_1;
		   if(bIonMode!=ION_PLASMA_CLUSTER_SHOWER)//130311Ti01
				{
				//LED_H on
				vDisplayLEDTimerHOn();
				//LED_1 on
				vDisplayLEDTimer1On();
				}
		   break;
	   case TIMER_MODE_2H:
		   wOnOffTimerCount=HOUR_2;
		   //LED_2 on
		   vDisplayLEDTimer2On();
		   goto LED_TIMER_ON_ONLY;	
	   case TIMER_MODE_4H:
		   wOnOffTimerCount=HOUR_4;
		   //LED_4 on
		   vDisplayLEDTimer4On();
		   goto LED_TIMER_ON_ONLY;
	   case TIMER_MODE_6H:
		   wOnOffTimerCount=HOUR_6;
		   //LED_6 on
		   vDisplayLEDTimer6On();
		   goto LED_TIMER_ON_ONLY;
	   LED_TIMER_ON_ONLY:
		   //LED_H on
		   vDisplayLEDTimerHOn();
		   break;
	   }
#endif
	//record bTimerMode to EEPROM
WRITE_TIMER_MODE_TO_EEPROM2:	//130316Ti01
	wOnOffTimerCountLo=100;//130418Ti01
	if(fgIsNotIonMode())	//130311Ti01
		{
		vMcuEepromWriteByte(EE_ON_OFF_TIMER,bTimerMode);	
		}	
}	//130309Ti01&&&

/////////////////////////////////////////////////////
// About Main MCU return value
/////////////////////////////////////////////////////
void vGiveHumidityADCValue(BYTE bdata1, BYTE bdata2)
{
/*
	//if((hum_value >= 0x05) && (hum_value <= 0xcb))
		{
		//air volume indication 6 lights up
		vDisplayLEDAirVolume6On();
		fgBlue6State = TRUE;
		}
*/
}

void vGiveTemperatureADCValue(BYTE bdata1, BYTE bdata2)
{
/*
	//if((temp_value >= 0x1c) && (temp_value <= 0xf4))
		{
		//air volume indication 3 lights up 
		vDisplayLEDAirVolume3On();
		fgBlue3State = TRUE;
		}
*/
}

void vGiveFanPWMValue(BYTE bdata1, BYTE bdata2)
{
}

void vGiveTemperatureValue(BYTE bdata1, BYTE bdata2)
{
}

void vGiveHumidityValue(BYTE bdata1, BYTE bdata2)
{
}

void vGiveIONVoltageValue(BYTE bdata1, BYTE bdata2)
{
/*
	//if(I2C read value)      Ion Generation Judgement
		{
		//update touch led state, air volume indication Turbo(purple) lights up
		vDisplayLEDAirVolume9On();
		bProductModeStateMachine++;
		}
*/
}

void vGiveIONErrorCount(BYTE bdata1, BYTE bdata2)
{
/*
	//if(I2C read value > 1)
		{
		//set digital indication display Version("Major Version No. of Sub MCU") Number
		vDisplay7SegHexNum(MCU_FIRMWARE_VERSION_UNIT, DISPLAY_NO_DISAPPEAR);
		//buzzer_driver(Pi);
		vBuzzerOutput(PI);
		//update touch led state, air volume indication 1 lights up
		vDisplayLEDAirVolume1On();
		bProductModeStateMachine++;
		}
*/
}

//ACC Time total is 4 bytes. unit:hour.
// bdata1=ACC Time/1000
void vGivePCIAccTimeValue(BYTE bdata1, BYTE bdata2)
{
}



