#define _MODE_ION_C_
#include "general.h"

#ifdef ION_MODE_FUNCTION
// 130129ja01***
//#define PLASMA_CLUSTER_TIME_START			0
//#define PLASMA_CLUSTER_TIME_END				3600
//#define PLASMA_CLUSTER_TIME_OFF				65500

//WORD wIonModePlasmaclusterTimer=PLASMA_CLUSTER_TIME_OFF;


void vModeIonManualInit(void)
{
//	if(fgIsNotWatchMode())
//		{
//		vSetKeyState(KEY_NORMAL);
//		}
	fgOscillateAngleShowEnable=FALSE;	//130418Ke04
	
	bIonMode=ION_MANUAL;
	vSubMcuSendIonModeStatus(bIonMode);	//130402lo01
	vMcuEepromWriteByte(EE_ION_MODE, ION_MANUAL);		//130308bi01
	
	//Read EEPROM:Air Volume,Off Timer,Horizontal Oscillating,Vertical Direction
	//set:Air Volume,Off Timer,Horizontal Oscillating,Vertical Direction
	// Air Volume Led On
	//130320bi01***
	if(bWatchZone!=ZONE_DANGER)
		{
		bAirVolume=bMcuEepromReadByte(EE_AIR_VOLUME);	//130504Ja01	
		//vFanVolumeSet(bAirVolume);				
		//vDisplayLEDAirVolumeOn(bAirVolume );
		//vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND)   //130408lo01	
		vPutEventQueue(EVENT_IR, IR_AIR_VOLUME_CONTROL, SHOW_THE_AIR_VOLUME);	//130502Ja01
		}
	else//130407Me01***
		{
		vWatchModeZoneChange();
		vFanVolumeSet(AIR_VOLUME_MAX);
		}	//130407Me01&&&

	//130320bi01&&&
	//130308bi01***
	//Set off time
	bTimerMode=bMcuEepromReadByte(EE_ON_OFF_TIMER);	 //130309bi01
	vSetOnOffTimer(bTimerMode);		 //130309bi01
	//Out load
	//bAirVolume=bMcuEepromReadByte(EE_AIR_VOLUME);
	//vFanVolumeSet(bAirVolume);		
#if 0	//130412Ke04
	if(bOscillatingMode==OSCILLATE_OFF)	//130410lo01***
		{
		vOscillateModeSet(OSCILLATE_OFF_MEMORIZED);
		}
	else
		{
		vOscillateModeSet(bMcuEepromReadByte(EE_OSCILLATE_MODE_ANGLE));
		}			//130410lo01&&&
#endif	//130412Ke04

	bLouverMode=bMcuEepromReadByte(EE_LOUVER_MODE);  //130425lo03
	if(bLouverMode==LOUVER_STOP) //130402lo02***
		{
		vLouverModeSet(bMcuEepromReadByte(EE_LOUVER_ANGLE));
		}
	else
		{
		vLouverModeSet(LOUVER_SWING);
		}		//130402lo02&&&
	//Display	
	//vDisplayLEDAirVolumeOn(bAirVolume );	
	vDisplayLEDPlasmaclusterShowerOff();
	vDisplayLEDClothingDeodorantOff();
	//vDisplayLEDTubeWhiteOff();	//130327lo01
	//vDisplayLEDTimerHOff();
	fgOscillateAngleIsShowing=FALSE;//130419Ju01
	//vDisplayLEDAirVolumeSettingIndicationAutoOff(100);	//130502lo01
	vDisplayLEDAngleSettingIndicationOff();	//130409Ke09
	//vDisplay7SegShowDecNumAutoOff(bAirVolume, 100);	
	//130308bi01&&&

	//130412Ke04***
	bOscillatingMode=bMcuEepromReadByte(EE_OSCILLATE_MODE_ON_OFF);
	if(bOscillatingMode==OSCILLATE_ON)
		{
		bOscillatingModeAngle=bMcuEepromReadByte(EE_OSCILLATE_MODE_ANGLE);
		vOscillateModeSet(bOscillatingModeAngle);	
		}
	else
		{
		if(fgAutoRestartFirstPower==FALSE)//130420Ke01
			{
			vOscillateModeSet(OSCILLATE_OFF_MEMORIZED);	
			}
		}
	//130412Ke04&&&
}
BOOL fgIonSetAngle=FALSE;	//If Ion mode set 90D,60D, don't show the angle. TRUE:don't show.	// 130423jac02
void vIonPlasmaclusterShowerInit(void)
{
	//vSetKeyState(KEY_WATCH_OR_ION_MODE);
	bIonMode=ION_PLASMA_CLUSTER_SHOWER;
	vSubMcuSendIonModeStatus(bIonMode);	//130402lo01
	vMcuEepromWriteByte(EE_ION_MODE, ION_PLASMA_CLUSTER_SHOWER);		//130308bi01
	bAirVolume=AIR_VOLUME_MAX;			//130413lo01***
	bOscillatingModeAngle=OSCILLATE_90D;
	bLouverMode=LOUVER_SWING;		//130413lo01&&&
	//wIonModePlasmaclusterTimer=PLASMA_CLUSTER_TIME_START;//Change to"Manual Mode"after 60 minutes
	//Turbo Air Volume Level:9(Fine Air VolumeLevel:33)
	//Off time:no
	//Horizontal Oscillating:90 degree
	//Vertical Direction:swing
	// TouchLed On

	//130308bi01***	
	//set timer:
	vSetOnOffTimer(TIMER_MODE_1H);		//130312Bi02
	//vOffTimerMemory();
	//vMcuEepromWriteByte(EE_TIMER_MODE_MEMORY,bTimerMode);	 //130309bi01
	//Output load
	vFanVolumeSet(AIR_VOLUME_MAX);
	vOscillateModeSet(OSCILLATE_90D);	//130413lo01
	fgIonSetAngle=TRUE;			// 130423jac02
	bOscillatingMode=OSCILLATE_ON;			//130423jac01
	vLouverModeSet(LOUVER_SWING);

	//Display	
	//vDisplayLEDAngleSettingIndicationOff();			//130423jac02//130424Ju01
	vDisplayLEDClothingDeodorantOff();
	//vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);//130424Ju01
	vDisplayLEDAngleSettingIndicationOff();	//130413lo01 
	//vDisplayLEDTubeWhiteOn();	//130327lo01
	vDisplayLEDPlasmaclusterShowerOn();
	vDisplayLEDAirVolume1to9On();	
	//vDisplay7SegShowHiAutoOff(DISPLAY_TIME_10_SECOND);//130424Ju01
	if(bWatchZone!=ZONE_DANGER)	//130502lo01***
		{
		vDisplay7SegShowAirVolumeAutoOff(AIR_VOLUME_MAX, DISPLAY_TIME_10_SECOND);//130424Ju01
		}  //130502lo01&&&
	//130308bi01&&&

}
void vIonClothingDeodorantInit(void)
{
	//vSetKeyState(KEY_WATCH_OR_ION_MODE);	//130413lo01
	bIonMode=ION_CLOTHING_DEODORANT;
	vSubMcuSendIonModeStatus(bIonMode);	//130402lo01
	vMcuEepromWriteByte(EE_ION_MODE, ION_CLOTHING_DEODORANT);		//130308bi01
	bOscillatingModeAngle=OSCILLATE_60D;
	bLouverMode=LOUVER_SWING;		//130413lo01&&&
	//Turbo Air Volume Level:8¡]Fine Air VolumeLevel:32¡^
	//Off time:2hour
	//Horizontal Oscillating:60 degree
	//Vertical Direction:swing
	// TouchLed On
	
	bAirVolume=AIR_VOLUME_ION_MAX;	 //130409lo01	//130503Me01
	vFanVolumeSet(AIR_VOLUME_ION_MAX);	//130503Me01
	//130320bi01***
	if(bWatchZone!=ZONE_DANGER)	 //130409lo02
		{
		vDisplayLEDAirVolume9Off();	
		//vDisplay7SegShowDecNumAutoOff(AIR_VOLUME_ION_MAX, DISPLAY_TIME_10_SECOND);//130424Ju01
		vDisplay7SegShowAirVolumeAutoOff(AIR_VOLUME_ION_MAX, DISPLAY_TIME_10_SECOND);//130424Ju01
		}
	else	//130504lo01***
		{
		vDisplay7SegShowOscillateAngleOff();
		}	//130504lo01&&&
	//130320bi01&&&
	//130308bi01***
	//Set Off time Mode
	vSetOnOffTimer(TIMER_MODE_2H);	//130309bi01
	//Output load
	//vFanVolumeSet(AIR_VOLUME_ION_MAX);
	vOscillateModeSet(OSCILLATE_60D);	//130413lo01
	fgIonSetAngle=TRUE;			// 130423jac02
	bOscillatingMode=OSCILLATE_ON;		//130423jac01
	vLouverModeSet(LOUVER_SWING);

	//Dispaly	
	vDisplayLEDAngleSettingIndicationOff();		//130423jac02
	vDisplayLEDClothingDeodorantOn();
	vDisplayLEDPlasmaclusterShowerOff();		
	//vDisplayLEDAirVolume1to8On();
	//vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);  //130502lo01
	//vDisplay7SegShowDecNumAutoOff(AIR_VOLUME_ION_MAX, DISPLAY_TIME_10_SECOND);	
	//130308bi01&&&
}


void vIONModeKey(void)
{
	BYTE bbuzzer_type=PI;		//130314Bi01	//130325ja01
	if(fgIsInPowerOffMode())
		{
		return;
		}

	bIonMode++;
	//bIonMode=bIonMode%ION_MAX; //130423gr02
	if(bIonMode==ION_PLASMA_CLUSTER_SHOWER) 	//130417lo02***
		{
		vIonPlasmaclusterShowerInit();
		}
	else if(bIonMode==ION_CLOTHING_DEODORANT)
		{
		vIonClothingDeodorantInit();
		}
	else
		{
		bbuzzer_type=PI_PI;		
		vModeIonManualInit();
		}			//130417lo02&&&
	vBuzzerOutput(bbuzzer_type);	//130314Bi01	//130325ja01	
}

//130413lo01***
void vIONModeSetting(void)
{
	if(fgIsInIonMode())
		{
		vDisplayLEDClothingDeodorantOff();
		vDisplayLEDPlasmaclusterShowerOff();

		bIonMode=ION_MANUAL;
		vSubMcuSendIonModeStatus(bIonMode);
		
		vMcuEepromWriteByte(EE_ION_MODE, ION_MANUAL);
		vMcuEepromWriteByte(EE_AIR_VOLUME,bAirVolume);
		vMcuEepromWriteByte(EE_OSCILLATE_MODE_ANGLE, bOscillatingModeAngle);
		vMcuEepromWriteByte(EE_OSCILLATE_MODE_ON_OFF, bOscillatingMode);		//130423jac01
		vMcuEepromWriteByte(EE_LOUVER_MODE, bLouverMode);	
		}
}
//130413lo01&&&

#if 0
//130306a03v***
void vSetIONMode(BYTE bmode)		
{
	switch(bmode)
		{
		default:
		case ION_MANUAL:
			vModeIonManualInit();
			break;
			
		case ION_PLASMA_CLUSTER_SHOWER:
			vIonPlasmaclusterShowerInit();
			break;
			
		case ION_CLOTHING_DEODORANT:
			vIonClothingDeodorantInit();
			break;
		}
}
//130306a03v&&&

void vIonFunctionForSettingChange(void)// Air control key:volume,Horizontal,Vertical
{
	switch(bIonMode)
		{
		case ION_PLASMA_CLUSTER_SHOWER:
		case ION_CLOTHING_DEODORANT:		
				vModeIonManualInit();
				vBuzzerOutput(PI);  //130329lo01
			break;
		default:				
			break;
		}
}
#endif
#if 0
void vIonFunctionForTimeChange(void)// Air control key:volume,Horizontal,Vertical
{
	switch(bIonMode)
		{
		case ION_MANUAL:
			//vTimerKey();
			break;
		case ION_PLASMA_CLUSTER_SHOWER:
			break;
		case ION_CLOTHING_DEODORANT:
			vModeIonManualInit();
			break;
		default:
			break;
		}
}

void vIONModeKeyProcess(void)
{
	switch(bIRKey)
		{
		//Remote Key
		case IR_POWER:  //130408lo02***
		case IR_TOUCH_POWER:
			break;	//130408lo02&&&
		case IR_ION_MODE:
			vIONModeKey();
			break;
		case IR_WATCH_MODE:
		case IR_TOUCH_WATCH_MODE:
			vWatchModeKey();
			break;
		case IR_CHILD_LOCK:	//130327lo02***
			vChildLock();
			break;	//130327lo02&&&
		case IR_FILTER_CLEANING:
			vResetFilterCleaningKey();		//130306a01v
			break;
		//130320Bi01***
#ifdef FULL_FUNCTION
		case IR_TIMER:
		case IR_TOUCH_TIMER:
		case IR_OSCILLATING_ANGLE:
		case IR_LOUVER_ANGLE:
		case IR_HORIZONTAL_OSCILLATING:
		case IR_TOUCH_HORIZONTAL_OSCILLATING:
		case IR_VERTICAL_DIRECTION:
		case IR_TOUCH_VERTICAL_DIRECTION:
		//case IR_CHILD_LOCK:	//130327lo02
			vIonFunctionForSettingChange();				
			break;
#endif
		default:
			if(bWatchMode!=ZONE_DANGER)		
				{
				vIonFunctionForSettingChange();
				}
			break;
		}
		//130320Bi01&&&
}
#endif

#if 0
void vIonModeTimer(void)
{
	if(wIonModePlasmaclusterTimer==PLASMA_CLUSTER_TIME_END)		//60minutes change manual mode
		{
		vModeIonManualInit();
		wIonModePlasmaclusterTimer=PLASMA_CLUSTER_TIME_OFF;
		}
	if(wIonModePlasmaclusterTimer++>PLASMA_CLUSTER_TIME_END)
		{
		wIonModePlasmaclusterTimer=PLASMA_CLUSTER_TIME_OFF;
		}
}
#endif

// 130129ja01&&&
#endif

