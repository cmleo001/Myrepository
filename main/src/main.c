#define _MAIN_C_
#include "general.h"

void vInitialBoard(void);
void vCheckEvent(void);
void vPowerOnPeripheralInitial(void);
void vPowerOnMode(void);
void vPowerOffMode(void);
void vSleepMode(void);
void vInitialVariable(void);
void vInitialWDT(void);
void vPlayerPollingFunction(void);
void vCheckPeripheralStatus(void);
void vInitialInterrupt(void);


//Variable for Power
BYTE bPowerMode _AT_0X7F=POWER_MODE_OFF;		//The Power mode of now. (Power ON,Power Off,Sleep mode)
BOOL fgExecutePowerOnMode=FALSE;
BOOL fgExecutePowerOffMode=FALSE;

//Variable for ION Mode
BYTE bIonMode _AT_0X7E=ION_MANUAL;

//Variable for Watch Mode
BYTE bWatchMode _AT_0X7D=WATCH_MANUAL;
//BYTE bLastWatchMode =WATCH_MANUAL;
BYTE bWatchZone = ZONE_NORMAL;	//130424Ja01
BOOL fgWatchZoneExecute=FALSE;

//Variable for Special function mode.(Demo Mode, Service Monitor Mode........)
BYTE bSpecialFunctionMode _AT_0X7C=MODE_NORMAL;
BOOL fgSpeedUp=FALSE;		//130407ra01


//Variable for Oscillate motor
BYTE bOscillatingMode =OSCILLATE_15D;
BOOL fgOscillateMotorGoOneStep=FALSE;
//BYTE bNowOscillatingMode =OSCILLATE_OFF;
BYTE bOscillateModeSet=OSCILLATE_NONE;

//Variable for Louver motor
//SWING or STOP
BYTE bLouverMode =LOUVER_SWING;	 //130307ro03
//LOUVER_HORIZONTAL_1,	LOUVER_UPPER40D,	LOUVER_HORIZONTAL_3,	LOUVER_LOWER20D,
BYTE bLouverAngle =LOUVER_HORIZONTAL_1;  //130307ro03
BOOL fgLouverMotorGoOneStep=FALSE;
//BYTE bLouverModeSet=LOUVER_NONE;	//130425Me02

//Variable for other function
BOOL fgChildLockEnable=FALSE;
BYTE bModeState =0;

//Variable for Fan motor
BYTE bAirVolume =0;	// 1~33
BYTE bAirVolumeEELast = 0;	//130427Ja01
BOOL fgAirVolumeControl=FALSE;

//Variable for AbnormalMode 
BOOL fgAbnormalMode=FALSE;	//130423vi01

#if 0
void vMainLoop(void)
{
	while(1)
		{
		WDT_CLEAR();
		vTimer1ms();	//130114sh01
		vTimer25ms();	//130114sh01
		vTimer1s();		//130114sh01
		vCheckEvent();
		vPlayerPollingFunction();
		vCheckI2CIntQueue();		//130126sh01
		vMcuEepromService();	//130119le01
		//vCheckADCQueue();		//130308Li01
		}
}
#endif

void main(void)
{
	INT_DIS();
	//vInitialBoard();
	vInitialTimer2();
	vInitialTimer3();
	vInitialADC();
//	vInitialTCC();
	vInitialI2C();
	vInitialEEPROM();
	vInitialGPIO();
//	vInitialDisplay();
//	vInitialUART();
	vInitialPWMA();
	vInitialPWMB();
	vInitialWDT();
	vInitialInterrupt();
//	vInitialVariable();

//	vInitialPCI();

	//check function checker mode pin status,if high,enter function checker mode.
	vCheckFunctionCheckerModePin();	//130403le01


//	vInitialBuzzer();

	INT_EN();               //  Before initial the interrupt is disable.

	//vMainLoop();
	while(1)
		{
		WDT_CLEAR();
//	INT_DIS();
		vTimer1ms();	//130114sh01
	INT_EN();
//	INT_DIS();
		vTimer25ms();	//130114sh01
	INT_EN();
//	INT_DIS();
		vTimer1s();		//130114sh01
	INT_EN();
	INT_DIS(); //130326sh01
		vCheckEvent();
	INT_EN();
//	INT_DIS();
		vPlayerPollingFunction();
	INT_EN();
		//vCheckI2CIntQueue();		//130126sh01
		//vMcuEepromService();	//130119le01
		//vCheckADCQueue();		//130308Li01
//	INT_DIS();
		vPowerOnMode();
	INT_EN();
//	INT_DIS();
		vPowerOffMode();
	INT_EN();
		}

}



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
	//BYTE bADCValue=0;//130417Ad01
	BYTE bTemp;
	BYTE btemp_data[3];

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
			//	{	//I2C, EEPROM, PCI EEPROM
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
			if((fgI2CIntBusy==TRUE)||fgTouchMCUIsBusy()||(fgI2CIntTransferOver==FALSE))//130315sh01//130328sh01
				{
				return;
				}
			vOTPIntEn();//130328sh01
			fgI2CIntBusy=TRUE;//130328sh01
			fgI2CIntTransferOver=FALSE;//130328sh01
			bI2CIntRetransferCount=0;//130418sh01
			bI2CSendBuffer[0]=bGetMixQueue();
			bI2CSendBuffer[1]=bGetMixQueue();
			bI2CSendBuffer[2]=bGetMixQueue();
			bI2CSendBuffer[3]=~(bI2CSendBuffer[0]+bI2CSendBuffer[1]+bI2CSendBuffer[2]);//bI2CSendBuffer[3] is the checksum
			bQueueType=QUEUE_TYPE_NONE;
			return;
#ifdef PCI_FUNCTION
		case QUEUE_TYPE_PCI_EEPROM:
			if(fgEepromCheckReady()==FALSE)	//130322lo01
				return;
			
			fgEepromI2CWriteByte(bGetMixQueue(),bGetMixQueue());	//130322lo01
			bQueueType=QUEUE_TYPE_NONE;
			return;
#endif
		case QUEUE_TYPE_EEPROM:
			if( fgEEPROMWriteCycleIsCompleted() )
				{
				//bI2CData1&=(BYTE)(~QUEUE_TYPE);
				vMcuEepromRealWrite(bGetMixQueue(),bGetMixQueue());
				bQueueType=QUEUE_TYPE_NONE;
				}
			return;	//130321ha04
		default:
			bQueueType=QUEUE_TYPE_NONE;
			return;
		}

	switch(bEvent)
		{
//		case EVENT_POWER_ON:
//			break;
	/*	case EVENT_ADC://130417AD01
			bADCValue=bEventData1;	//130410Li01

			fgADCTransformIsBusy=FALSE;

			switch(bNowADCChannel)
				{
				case ADC_CHANNEL_TEMPERATURE:
					vADCTemperatureEvent(bADCValue);
					break;
				case ADC_CHANNEL_HUMIDITY:
					vADCHumidityEvent(bADCValue);
					break;
				case ADC_CHANNEL_ION:
					vADCIONEvent(bADCValue);
					break;
				}
			break;*///130417AD01
#if 0//130418sh02	
		case EVENT_PCI_NONE_IS_NORMAL:
			vEventPCINoneIsNormal();
			break;
		case EVENT_PCI_NONE_IS_ERROR:
			vEventPCINoneIsError();
			break;
#endif//130418sh02	
		case EVENT_COVER_SWITCH_IS_NORMAL:
			//vEventCoverSwitchIsNormal();//130423Ad01
			vIntMainMCUError(ERROR_COVER_OPEN,FALSE);	//130423Ad01
			break;
		case EVENT_COVER_SWITCH_IS_OPEN:
			//vEventCoverSwitchIsOpen();//130423Ad01
			vIntMainMCUError(ERROR_COVER_OPEN,TRUE);	//130423Ad01
			break;
		//Event about TOUCH MCU to MAIN MCU.//130306sh01***
		//Command about SUB to MAIN.
		case COMMAND_SUB_MAIN_FAN_VOLUME:
			bAirVolume = bEventData1;	//130424Ja01
			vFanVolumeSet(bEventData1);
			break;
		case COMMAND_SUB_MAIN_FAN_VOLUME_EE:	//130427Ja01&&&
			if(bAirVolumeEELast != bEventData1)
				{
				bAdjustAutoFanVolumeRem = 0xFF;
				bAirVolumeEELast = bEventData1;
				}	//130427Ja01&&&
			break;
		case COMMAND_SUB_MAIN_OSCILLATE_MODE:
			bOscillateModeSet=bEventData1;
			//vOscillateModeSet(bEventData1);
			break;
		case COMMAND_SUB_MAIN_LOUVER_MODE:
			vLouverModeSet(bEventData1);
			break;
		case COMMAND_SUB_MAIN_BUZZER_MODE:
			vBuzzerOutput(bEventData1);
			break;
		case COMMAND_SUB_MAIN_WATCH_MODE_STATUS:
			bWatchMode=bEventData1;
			vWatchModeKey();
			break;
		case COMMAND_SUB_MAIN_ION_MODE_STATUS:
			bIonMode=bEventData1;
			break;
		case COMMAND_SUB_MAIN_POWER_STATUS:		//130306a02v***
			bPowerMode=bEventData1;
			if(fgIsInPowerOnMode())
				{
				//vPowerOnMode();
				fgExecutePowerOnMode=TRUE;
				}
			else if(fgIsInPowerOffMode())
				{
				fgExecutePowerOffMode=TRUE;
				//vPowerOffMode();
				}
			//130306a02v&&&
			break;
		case COMMAND_SUB_MAIN_SPECIAL_MODE:
			//bSpecialFunctionMode=bEventData1;	 //130425lo01
			//130313ma01***
			switch(bEventData1)
				{
				case MODE_PRODUCTION_LINE:	
					vFanPower(TRUE);						
					vFanVolumeSet(8);						
					vLouverModeSet(LOUVER_CENTRAL);						
					vBuzzerOutput(PI);						
					break;
				case MODE_DEMO:
					vFanPower(TRUE);
					vLouverModeSet(LOUVER_CENTRAL);  //130408ma01
					vFanVolumeSet(4);
					vBuzzerOutput(PI);
					break;
				case MODE_NORMAL:
					if(fgIsInDemoMode())
						{
						vLouverModeSet(LOUVER_CLOSED_POSITION);//130422ma02
						vBuzzerOutput(PI_PI);
						}
					vFanPower(FALSE);	//130422ma01			
					break;
				case MODE_MONITOR://130408Ad03***
					bSpecialFunctionMode=bEventData1;	//130308Li01 //130425lo01	
					vFanPower(TRUE);		//130418ra01***
					vFanVolumeSet(4);
					vLouverModeSet(LOUVER_INITIAL_POSITION);
					vBuzzerOutput(PI);
					vPCIPowerOnReadAndCheckTime();	//130418ra01&&&
					fgPCIPowerOn=FALSE;//130423lo02
					vIONResetEN();//130410Ad01
					fgPCIPowerPinEnable=TRUE;	
					//vPCIPowerOn();	//130423lo02
					fgIonGenerationGetDeltaVFunction=TRUE;
					break;
				case MODE_FUNCTION_CHECKER_TEST:
					vFanPower(TRUE);	//130417le03
					vLouverModeSet(LOUVER_INITIAL_POSITION);	//130429le01
					vIONResetDIS();//130424Ad02	//130429le01
					//fgPCIPowerPinEnable=TRUE;	//130429le01***
					//vPCIPowerOn();
					//fgIonGenerationGetDeltaVFunction=TRUE;	//130429le01&&&
					break;//130408Ad03&&&
				case MODE_SERVICE_MONITOR:	//130412ra01***
					bSpecialFunctionMode=bEventData1;	//130308Li01 //130425lo01	
					vBuzzerOutput(PI);
					vPCIPowerOnReadAndCheckTime();
					vPCIPowerOff(); //130423lo02
					fgPCIPowerOn=FALSE;//130423lo02
					break;	//130412ra01&&&
				default:
					break;
				}
			//130313ma01&&&				
			bSpecialFunctionMode=bEventData1;	//130308Li01 //130425lo01	
			break;
		case COMMAND_SUB_MAIN_PIN_RESET_ENABLE:
			//130312Ad01***
			if(bEventData1==TRUE)
				{
				vIONResetEN();
				}
			else
				{
				vIONResetDIS();
				}
			//130312Ad01&&&
			break;
		case COMMAND_SUB_MAIN_PIN_CAPSEL_40P_ENABLE:
			if(bEventData1==TRUE)
				{
				vCapacitance40PF();
				}
			else
				{
				vCapacitance4PF();
				}
			break;
#ifdef ION_SENSOR_FUNCTION			
		case COMMAND_SUB_MAIN_PIN_PCI_POWER_ENABLE:
			fgPCIPowerPinEnable=bEventData1;	//130309Ad01
			if(bEventData1==TRUE)	//130309Ad01
				{
				vPCIPowerOn();
				}
			else
				{
				vPCIPowerOff();
				}
			break;
#endif
		case COMMAND_SUB_MAIN_MONITOR_MODE_STATUS:
		case COMMAND_SUB_MAIN_FUNCTION_CHECKER_MODE_STATUS: //130328le01
			bModeState=bEventData1;
			break;
		case COMMAND_SUB_MAIN_REQUEST_HUM_ADC_VALUE:
			vIntHumiAdc(bHumidityADCAverageValue);		//130308Li01
			break;
		case COMMAND_SUB_MAIN_REQUEST_TEMP_ADC_VALUE:
			vIntTempAdc(bTemperatureADCAverageValue);	//130308Li01
			break;
		case COMMAND_SUB_MAIN_REQUEST_FAN_PWM_VALUE:
			vIntFanPwm(bCurrentSetValue);//130309Ke07
			break;
		case COMMAND_SUB_MAIN_REQUEST_TEMP_REAL_VALUE:
			vIntTempReal(bTemperature);	//130308Li01
			break;
		case COMMAND_SUB_MAIN_REQUEST_HUM_REAL_VALUE:
			vIntHumiReal(bHumidity);	//130308Li01
			break;
		case COMMAND_SUB_MAIN_REQUEST_FAN_ROTA_SET_VALUE:
			vIntFanRotaSet(bFanSetRotationSpeedValue);//130309Ke07
			break;
		case COMMAND_SUB_MAIN_REQUEST_FAN_ROTA_DETECT_VALUE:
			vIntFanRotaDetectValue(bFanSampleValue);//130309Ke07
			break;
		case COMMAND_SUB_MAIN_REQUEST_FAN_MOTOR_ROTATION_VALUE:	//130314le01***
			if(bFanSetRotationSpeedValue>=bFanSampleValue)
				{
				vIntFanMotorRotationValue(bFanSetRotationSpeedValue-bFanSampleValue);
				}
			else
				{
				vIntFanMotorRotationValue(bFanSampleValue-bFanSetRotationSpeedValue);
				}
			break;	//130314le01&&&
#ifdef ION_SENSOR_FUNCTION			
		case COMMAND_SUB_MAIN_REQUEST_ION_VOLTAGE_VALUE:		//Von ADC or Voltage value.
			/*fgPCIPowerPinEnable=TRUE;	//130309Ad01  //130408Ad03***
			vPCIPowerOn();

			fgIonGenerationGetDeltaVFunction=TRUE;//130309Ad01
			vGetIonSampleOneTime();//130309Ad01*/
			vIntIonVolValue(wiDeltaV);//130408Ad03&&&
			break;
		case  COMMAND_SUB_MAIN_REQUEST_ION_LEAK_CURRENT_OK_COUNT:	//Voff-avg ok times.
			fgPCIPowerPinEnable=FALSE;	//130309Ad01
			vPCIPowerOff();
		
			bIonSampleTimes=bEventData1;//130309Ad01
			bIonSampleCnt=bIonSampleTimes;	//remember the sample time, because we want to get the Voff-avg.
			fgIonGenerationVoltageOKFunction=TRUE;//130309Ad01
			vGetIonSampleAtProuductLine();//130309Ad01
			break;
		case  COMMAND_SUB_MAIN_REQUEST_ION_GENERATION_OK_COUNT:	//Von ok times.
			if(!fgPCINoneIsError())//130408Ad02
				{
				fgPCIPowerPinEnable=TRUE;	//130309Ad01
				vPCIPowerOn();

				bIonSampleTimes=bEventData1;//130309Ad01
				bIonSampleCnt=bIonSampleTimes;//130326Ad02
				fgIonGenerationVoltageOKFunction=TRUE;//130309Ad01
				vGetIonSampleAtProuductLine();//130309Ad01
				}
			break;
		//case COMMAND_SUB_MAIN_REQUEST_ION_DELTA_VOFF://130309sh04***
			//break;//130309sh04&&&
		/*case COMMAND_SUB_MAIN_REQUEST_ION_DELTA_V:	//130408Ad03***
			fgIonGenerationGetDeltaVFunction=TRUE;//130309Ad01
			vGetIonSampleOneTime();//130309Ad01
			break;*/	//130408Ad03&&&
			
		case COMMAND_SUB_MAIN_REQUEST_ION_ERROR_COUNT_VALUE:
			vIntIonErrorCnt(bMcuEepromReadByte(EE_ION_GENERATION_ERROR_COUNT)); //130327ra02
			break;
#endif
		case COMMAND_SUB_MAIN_REQUEST_PCI_UNIT_USE_ACC_HOUR_VALUE:			//130420lo01***
			bTemp=(BYTE)(dPciTime/PCI_TIME_FOR_SERVICE_MODE);                                          //Display Hour= PCI time(minute) divided by 60, then divided by 1000   
			vIntPciAccHour(bTemp);   
			break;
		case COMMAND_SUB_MAIN_REQUEST_PCI_UNIT_USE_ACC_TIME_VALUE:
			switch(bEventData1)
				{
				case 0:
					bTemp=bpcitemp[0];
					break;
				case 1:
					bTemp=bpcitemp[1];
					break;
				case 2:
					bTemp=bpcitemp[2];
					break;				//130420lo01&&&
				case 3:
					//bTemp=(BYTE)(((wPciTimeInRam*30)>>24)&0x000000ff);
					bTemp=0;
					break;
				}
			vIntPciAccTime(bEventData1,bTemp);	
			break;
		case COMMAND_SUB_MAIN_ERROR_PROCESS:		//130326vi01***
			//vBuzzerOutput(PI_OFF);				//130411vi03//130415vi01
			bLastWatchZone=ZONE_MAX;		//130504Me01
			fgAbnormalMode=TRUE;				//130423vi01***
			vPCIPowerOff();		
			fgPCIPowerOn=FALSE;//130423vi01&&&		
			vLouverModeSet(LOUVER_STOP);	
			vOscillateModeSet(OSCILLATE_OFF);	//130407Ke04
			vFanPower(FALSE);
			break;//130326vi01&&&
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
	BYTE bADCValue=0;	//130316Li02
	//DWORD dwPCITime;	// 130316lo01
	BYTE bTemp;

	//Is there event on the Event Queue? If do,jump to here.
	if(!fgEventQueuEmpty)
		{
		stemp_queue_data=sGetEventQueue();
		switch(bEvent)
			{
			case EVENT_POWER_ON:
				break;
			case EVENT_ADC:
				bADCValue=ADDH;	//130316Li02
				fgADCTransformIsBusy=FALSE;

				switch(bNowADCChannel)
					{
					case ADC_CHANNEL_TEMPERATURE:
						vADCTemperatureEvent(bADCValue);	//130316Li02
						break;
					case ADC_CHANNEL_HUMIDITY:
						vADCHumidityEvent(bADCValue);	//130316Li02
						break;
					case ADC_CHANNEL_ION:
						vADCIONEvent(bADCValue);	//130316Li02
						break;
					}
				break;
			case EVENT_PCI_NONE_IS_NORMAL:
				vEventPCINoneIsNormal();
				break;
			case EVENT_PCI_NONE_IS_ERROR:
				vEventPCINoneIsError();
				break;
			case EVENT_COVER_SWITCH_IS_NORMAL:
				vEventCoverSwitchIsNormal();
				break;
			case EVENT_COVER_SWITCH_IS_OPEN:
				vEventCoverSwitchIsOpen();
				break;
			//Event about TOUCH MCU to MAIN MCU.//130306sh01***
			//Command about SUB to MAIN.
			case COMMAND_SUB_MAIN_FAN_VOLUME:
				vFanVolumeSet(bEventData1);
				break;
			case COMMAND_SUB_MAIN_OSCILLATE_MODE:
				vOscillateModeSet(bEventData1);
				break;
			case COMMAND_SUB_MAIN_LOUVER_MODE:
				vLouverModeSet(bEventData1);
				break;
			case COMMAND_SUB_MAIN_BUZZER_MODE:
				vBuzzerOutput(bEventData1);
				break;
			case COMMAND_SUB_MAIN_WATCH_MODE_STATUS:
				bWatchMode=bEventData1;
				break;
			case COMMAND_SUB_MAIN_ION_MODE_STATUS:
				bIonMode=bEventData1;
				break;
			case COMMAND_SUB_MAIN_POWER_STATUS:		//130306a02v***
				bPowerMode=bEventData1;
				if(bPowerMode==POWER_MODE_ON)
					{
					vPowerOnMode();
					}
				else if(bPowerMode==POWER_MODE_OFF)
					{
					vPowerOffMode();
					}
				//130306a02v&&&
				break;
			case COMMAND_SUB_MAIN_SPECIAL_MODE:
				//130313ma01***
				switch(bEventData1)
					{
					case MODE_PRODUCTION_LINE:	
						vFanPower(TRUE);						
						vFanVolumeSet(8);						
						vLouverModeSet(LOUVER_CENTRAL);						
						vBuzzerOutput(PI);						
						break;
					case MODE_DEMO:
						vFanPower(TRUE);
						vLouverModeSet(LOUVER_CENTRAL);
						vFanVolumeSet(4);
						vBuzzerOutput(PI);
						break;
					case MODE_NORMAL:
						if(bSpecialFunctionMode==MODE_DEMO)
							{
							vFanPower(FALSE);
							vLouverModeSet(LOUVER_STOP);
							vBuzzerOutput(PI_PI);
							}
						break;
					default:
						break;
					}
				//130313ma01&&&				
				bSpecialFunctionMode=bEventData1;	//130308Li01
				break;
			case COMMAND_SUB_MAIN_PIN_RESET_ENABLE:
				//130312Ad01***
				if(bEventData1==TRUE)
					{
					vIONResetEN();
					}
				else
					{
					vIONResetDIS();
					}
				//130312Ad01&&&
				break;
			case COMMAND_SUB_MAIN_PIN_CAPSEL_40P_ENABLE:
				if(bEventData1==TRUE)
					{
					vCapacitance40PF();
					}
				else
					{
					vCapacitance4PF();
					}
				break;
#ifdef ION_SENSOR_FUNCTION			
			case COMMAND_SUB_MAIN_PIN_PCI_POWER_ENABLE:
				fgPCIPowerPinEnable=bEventData1;	//130309Ad01
				if(bEventData1==TRUE)	//130309Ad01
					{
					vPCIPowerOn();
					}
				else
					{
					vPCIPowerOff();
					}
				break;
#endif
			case COMMAND_SUB_MAIN_MONITOR_MODE_STATUS:
				bModeState=bEventData1;
				break;
			case COMMAND_SUB_MAIN_REQUEST_HUM_ADC_VALUE:
				vIntHumiAdc(bHumidityADCAverageValue);		//130308Li01
				break;
			case COMMAND_SUB_MAIN_REQUEST_TEMP_ADC_VALUE:
				vIntTempAdc(bTemperatureADCAverageValue);	//130308Li01
				break;
			case COMMAND_SUB_MAIN_REQUEST_FAN_PWM_VALUE:
				vIntFanPwm(bCurrentSetValue);//130309Ke07
				break;
			case COMMAND_SUB_MAIN_REQUEST_TEMP_REAL_VALUE:
				vIntTempReal(bTemperature);	//130308Li01
				break;
			case COMMAND_SUB_MAIN_REQUEST_HUM_REAL_VALUE:
				vIntHumiReal(bHumidity);	//130308Li01
				break;
			case COMMAND_SUB_MAIN_REQUEST_FAN_ROTA_SET_VALUE:
				vIntFanRotaSet(bFanSetRotationSpeedValue);//130309Ke07
				break;
			case COMMAND_SUB_MAIN_REQUEST_FAN_ROTA_DETECT_VALUE:
				vIntFanRotaDetectValue(bFanSampleValue);//130309Ke07
				break;
			case COMMAND_SUB_MAIN_REQUEST_FAN_MOTOR_ROTATION_VALUE:	//130314le01***
				if(bFanSetRotationSpeedValue>=bFanSampleValue)
					{
					vIntFanMotorRotationValue(bFanSetRotationSpeedValue-bFanSampleValue);
					}
				else
					{
					vIntFanMotorRotationValue(bFanSampleValue-bFanSetRotationSpeedValue);
					}
				break;	//130314le01&&&
#ifdef ION_SENSOR_FUNCTION			
			case COMMAND_SUB_MAIN_REQUEST_ION_VOLTAGE_VALUE:		//Von ADC or Voltage value.
				fgPCIPowerPinEnable=TRUE;	//130309Ad01
				vPCIPowerOn();

				fgIonGenerationGetDeltaVFunction=TRUE;//130309Ad01
				vGetIonSampleOneTime();//130309Ad01
				break;
			case  COMMAND_SUB_MAIN_REQUEST_ION_LEAK_CURRENT_OK_COUNT:	//Voff-avg ok times.
				fgPCIPowerPinEnable=FALSE;	//130309Ad01
				vPCIPowerOff();
			
				bIonSampleTimes=bEventData1;//130309Ad01
				bIonSampleCnt=bIonSampleTimes;	//remember the sample time, because we want to get the Voff-avg.
				fgIonGenerationVoltageOKFunction=TRUE;//130309Ad01
				vGetIonSampleAtProuductLine();//130309Ad01
				break;
			case  COMMAND_SUB_MAIN_REQUEST_ION_GENERATION_OK_COUNT:	//Von ok times.
				fgPCIPowerPinEnable=TRUE;	//130309Ad01
				vPCIPowerOn();

				bIonSampleTimes=bEventData1;//130309Ad01
				fgIonGenerationVoltageOKFunction=TRUE;//130309Ad01
				vGetIonSampleAtProuductLine();//130309Ad01
				break;
			//case COMMAND_SUB_MAIN_REQUEST_ION_DELTA_VOFF://130309sh04***
				//break;//130309sh04&&&
			case COMMAND_SUB_MAIN_REQUEST_ION_DELTA_V:
				fgIonGenerationGetDeltaVFunction=TRUE;//130309Ad01
				vGetIonSampleOneTime();//130309Ad01
				break;
				
			case COMMAND_SUB_MAIN_REQUEST_ION_ERROR_COUNT_VALUE:
				break;
#endif
			case COMMAND_SUB_MAIN_REQUEST_PCI_UNIT_USE_ACC_HOUR_VALUE:			// 130316lo01***
				bTemp=(BYTE)(wPciTimeInRam/2000);                                                 //Display Hour= PCI time(minute) divided by 60, then divided by 1000   
				vIntPciAccHour(bTemp);   
				break;
			case COMMAND_SUB_MAIN_REQUEST_PCI_UNIT_USE_ACC_TIME_VALUE:
				switch(bEventData1)
					{
					case 0:
						bTemp=(BYTE)(wPciTimeInRam*30);
						break;
					case 1:
						bTemp=(BYTE)((wPciTimeInRam*30)>>8);
						break;
					case 2:
						bTemp=(BYTE)((((DWORD)wPciTimeInRam)*30)>>16);
						break;
					case 3:
						//bTemp=(BYTE)(((wPciTimeInRam*30)>>24)&0x000000ff);
						bTemp=0;
						break;
					}
				vIntPciAccTime(bEventData1,bTemp);	
				break;
			}
		}	// 130316lo01&&&
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
/*
void vPowerOnPeripheralInitial(void)
{
	vPCIPowerOnReadAndCheckTime();		//check PCI
	vADCIONInitial();			//ADC initial//130306a02v

}
*/

void vPowerOnMode(void)
{
	if(fgExecutePowerOnMode==FALSE)
		{
		return;
		}
	fgExecutePowerOnMode=FALSE;
	
	//vPowerOnPeripheralInitial();
	//Peripheral initial put in here, because the stack depth is over 8 level.
	vIONResetDIS();//130424Ad02
	vPCICheckApprovedUnitCode(); //130327lo01
	vPCIPowerOnReadAndCheckTime();		//check PCI
	vADCIONInitial();			//ADC initial//130306a02v	//130315Ad01	//130423Ad01
	vLouverModeSet(LOUVER_INITIAL_POSITION);
	//vOscillateModeSet(OSCILLATE_CENTRAL);//130311Ke02
#ifdef MAIN_MCU_DO_POWER_ON_OFF_PROCESS	//130306a02v***

	//vBuzzerOutput(PI);	//130327Ti01

	vFanPower(TRUE);

#endif	//130306a02v&&&

}

void vPowerOffMode(void)
{
	if(fgExecutePowerOffMode==FALSE)
		return;
	fgExecutePowerOffMode=FALSE;
	
	
#ifdef MAIN_MCU_DO_POWER_ON_OFF_PROCESS	//130306a02v***
	//vBuzzerOutput(PI_LONG);	//130327Ti01
	vIONResetEN();//130424Ad02
	vPCIPowerOff(); //130329lo02
	fgPCIPowerOn=FALSE;	//130329lo02
	vOscillateModeSet(OSCILLATE_OFF);	//Stop and memory the position.
	vOscillateModeSet(OSCILLATE_ALL_PIN_DISABLE);
//	vLouverModeSet(LOUVER_STOP);		//Stop and memory the position.		//130326vi01
//	vLouverModeSet(LOUVER_ALL_PIN_DISABLE);
	vLouverModeSet(LOUVER_CLOSED_POSITION);
	
	if(fgIsNotWatchMode())		//130308vi01
		{
		fgTemHumAbnormal=FALSE;//130409vi01
		vFanPower(FALSE);
		}
	else	//130424Ke02***
		{	//130504Me01***
		if(fgAbnormalMode==TRUE)
			{
			if(fgIsInSpeedUpMode())				//speed up mode
				{
				wWatchModeCheckTimercnt= 120;	//120*1s=2min	
				}
			else
				{
				wWatchModeCheckTimercnt= 1200;	//1200*1s=20min
				}
			}	//130504Me01&&&
		vFanPower(TRUE);
		}//130424Ke02&&&
#endif	//130306a02v&&&
	fgAbnormalMode=FALSE;	//130423vi01	//130504Me01
		
}

void vSleepMode(void)
{
}

void vInitialVariable(void)
{
}

void vInitialWDT(void)
{	//130222gr01***
	WDT_PRESCALER_ENABLE;
//	WDT_PRESCALE_1_256;	// 4s
//	WDT_PRESCALE_1_64;		// 1s
	WDT_PRESCALE_1_32;		// 0.5s
	WDT_EN();
}	//130222gr01&&&

void vInitialInterrupt(void)
{
	INTERRUPT_DISI_HARDWARE_DISABLE;
}

#if 0
void vInitialBoard(void)
{
	vInitialTimer3();
	vInitialADC();
//	vInitialTCC();
#ifdef FULL_FUNCTION	//130316ja01
	vInitialEEPROM();
#endif	//130316ja01
	vInitialGPIO();
//	vInitialDisplay();
//	vInitialUART();
	vInitialPWMA();
	vInitialPWMB();
	vInitialWDT();
	vInitialI2C();
	vInitialInterrupt();
//	vInitialVariable();

	vInitialPCI();
//	vInitialBuzzer();
}
#endif

void vPlayerPollingFunction(void)
{
	vPollingAdcValue();//130417Ad01
	//vPollingPCINone();//130418sh02
	vPollingSpeedUpMode();	//130407ra01
	//vPollingCoverSwitch();	//130307Li01
	vPollingTouchMcuBusy();
	//vPollingFG();	//130411Ke01	//130424Ke01

	if(bOscillateModeSet!=OSCILLATE_NONE)
		{
		vOscillateModeSet(bOscillateModeSet);
		bOscillateModeSet=OSCILLATE_NONE;
		}

	/*	//130425Me02***
	if(bLouverModeSet!=LOUVER_NONE)
		{
		vLouverModeSet(bLouverModeSet);
		bLouverModeSet=LOUVER_NONE;
		}	*/		//130425Me02&&&
	vPCIErrorProcess();
	vWatchZoneExecute(bWatchZone);

}
