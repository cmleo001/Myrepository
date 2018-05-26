#define _MODE_MONITOR_C_
#include "general.h"
#ifdef MONITOR_MODE_FUNCTION
//130308ra01***
#define FAN_MOTOR_FINE_LEVEL_4	4
#define PCI_UNIT_ACC_TIME_LEAST_BYTE	0	//Least significant byte
#define PCI_UNIT_ACC_TIME_LOW_BYTE		1	//Low byte
#define PCI_UNIT_ACC_TIME_HIGH_BYTE		2	//High byte
#define PCI_UNIT_ACC_TIME_MOST_BYTE	3	//The most significant byte
#define FILTER_CLEAN_ACC_TIME_MINUTE	0	//130402ra01
#define FILTER_CLEAN_ACC_TIME_HOUR_RATE	24	// 1 day=24 hours.	//130402ra02

#if 1	//130418ha03***
void vMonitorMode_Buzzer(void)
{
	bModeState++;
	vBuzzerOutput(PI);
}
void vMonitorMode_SendCommand(void)
{
	vSubMcuMonitorModeStatus(bModeState);
	Function(_vMonitorMode_Buzzer);
}

void vMonitorMode_1(void)
{
	//vDisplayLEDAirVolumeSettingIndicationOff();
	vDisplay7segLedAllOff();	//130408ra02
	//Monitor    number display 	"H"	(WHITE)
	vDisplayLEDTimerHOn();			
	//"Digital Indication(Blue)  "Fine Air Volume Level"    (HEX)
	vDisplay7SegShowHexNumOn(bAirVolume);
	
	Function(_vMonitorMode_Buzzer);
}
void vMonitorMode_2(void)
{
	vDisplayLEDTimerHOff();	
	//Monitor    number display  "6"	(WHITE)
	vDisplayLEDTimer6On();			
	//From Main MCU [0x60] read "Set value of Fan rotational speed[rpm]" divided by 10 and display.

	Function(_vMonitorMode_SendCommand);
}
void vMonitorMode_3(void)
{
	//Monitor    number display "6","H"	(WHITE)
	vDisplayLEDTimerHOn();
	//From Main MCU [0x61] read "Detected value of Fan rotational speed[rpm]" divided by 10 and display.

	Function(_vMonitorMode_SendCommand);
}
void vMonitorMode_4(void)
{
	vDisplayLEDTimer6Off();
	vDisplayLEDTimerHOff();
	//Monitor    number display 	"4"	(WHITE)
	vDisplayLEDTimer4On();
	//From Main MCU [0x62] read "Fan PWM value" and display.

	Function(_vMonitorMode_SendCommand);
}
void vMonitorMode_5(void)
{
	//Monitor    number display     "4","H"	(WHITE)
	vDisplayLEDTimerHOn();
	//From Main MCU [0x68] read "Temperature A/D Value" and display.

	Function(_vMonitorMode_SendCommand);
}
void vMonitorMode_6(void)
{
	vDisplayLEDTimerHOff();
	//Monitor    number display     "4","6"	(WHITE)
	vDisplayLEDTimer6On();
	//From Main MCU [0x67] read  "Humidity A/D Value" and display.

	Function(_vMonitorMode_SendCommand);
}
void vMonitorMode_7(void)
{
	//Monitor    number display     "4","6","H"	(WHITE)
	vDisplayLEDTimerHOn();
	//Display Light A/D Value.	(HEX)	
	vDisplay7SegShowHexNumOn(bLightSensorADCAverage);	//130327ra02

	Function(_vMonitorMode_SendCommand);
}
void vMonitorMode_8(void)
{
	vDisplayLEDTimer4Off();
	vDisplayLEDTimer6Off();
	vDisplayLEDTimerHOff();
	//Monitor    number display 	"2"	(WHITE)
	vDisplayLEDTimer2On();		
	//From Main MCU 0x6c read Temperature [¢J] value and display.

	Function(_vMonitorMode_SendCommand);
}
void vMonitorMode_9(void)
{
	//Monitor    number display     "2","H"	(WHITE)
	vDisplayLEDTimerHOn();			
	//"Digital Indication(Blue)     "Humidity [%] Value"    (HEX)

	Function(_vMonitorMode_SendCommand);
}
void vMonitorMode_10(void)
{
	vDisplayLEDTimerHOff();	
	//Monitor    number display     "2","6"	(WHITE)
	vDisplayLEDTimer6On();			
	//From EEPROM read "Accumulated time for cleaning Filter [Minute]" and display.
	//vDisplay7SegShowHexNumOn(bMcuEepromReadByte(EE_CLEANING_FILTER_TIME_HOUR_LOW));
	vDisplay7SegShowHexNumOn(bFilterCleanMin);	//130402ra01	//130427ra01

	Function(_vMonitorMode_SendCommand);
}
void vMonitorMode_11(void)
{
	//Monitor    number display     "2","6","H"	(WHITE)
	vDisplayLEDTimerHOn();
	//"Digital Indication(Blue)     "Accumulated time for cleaning Filter [Hour]"   (HEX)
	//vDisplay7SegShowHexNumOn(bMcuEepromReadByte(EE_CLEANING_FILTER_TIME_HOUR_HIGH));
	vDisplay7SegShowHexNumOn((BYTE)(wFilterCleanHour%FILTER_CLEAN_ACC_TIME_HOUR_RATE));	//130402ra02
	
	Function(_vMonitorMode_Buzzer);
}
void vMonitorMode_12(void)
{
	vDisplayLEDTimer6Off();
	vDisplayLEDTimerHOff();
	//Monitor    number display     "2","4"	(WHITE)
	vDisplayLEDTimer4On();
	//"Digital Indication(Blue)     "Accumulated time for cleaning Filter [Day]"    (HEX)
	//vDisplay7SegShowHexNumOn(bMcuEepromReadByte(EE_CLEANING_FILTER_TIME_HOUR_HIGH));
	vDisplay7SegShowHexNumOn((BYTE)(wFilterCleanHour/FILTER_CLEAN_ACC_TIME_HOUR_RATE));	//130402ra02
	
	Function(_vMonitorMode_Buzzer);
}
void vMonitorMode_13(void)
{
	//Monitor    number display     "2","4","H"	(WHITE)
	vDisplayLEDTimerHOn();
	//From Main MCU [0x63] read 4 Byte and display 0 byte [Least significant byte] value.
	vSubMcuReadPciUnitUseAccTimeValue(PCI_UNIT_ACC_TIME_LEAST_BYTE);
	
	Function(_vMonitorMode_Buzzer);
}
void vMonitorMode_14(void)
{
	vDisplayLEDTimerHOff();
	//Monitor    number display     "2","4","6"	(WHITE)
	vDisplayLEDTimer6On();
	//From Main MCU [0x63] read 4 Byte,and display [Low byte] value.
	vSubMcuReadPciUnitUseAccTimeValue(PCI_UNIT_ACC_TIME_LOW_BYTE);
	
	Function(_vMonitorMode_Buzzer);
}
void vMonitorMode_15(void)
{
	//Monitor    number display     "2","4","6","H"	(WHITE)
	vDisplayLEDTimerHOn();
	//From Main MCU [0x63] read 4 Byte,and display [High byte] value.
	vSubMcuReadPciUnitUseAccTimeValue(PCI_UNIT_ACC_TIME_HIGH_BYTE);
	
	Function(_vMonitorMode_Buzzer);
}
void vMonitorMode_16(void)
{
	//vDisplayLEDTimer2Off();
	//vDisplayLEDTimer4Off();
	//vDisplayLEDTimer6Off();
	//vDisplayLEDTimerHOff();
	vDisplay7segLedAllOff();

	//Monitor    number display 	"1"	(WHITE)
	vDisplayLEDTimer1On();
	//From Main MCU [0x63] read 4 Byte,and display [The most significant byte] value.
	vSubMcuReadPciUnitUseAccTimeValue(PCI_UNIT_ACC_TIME_MOST_BYTE);
	
	Function(_vMonitorMode_Buzzer);
}
void vMonitorMode_17(void)
{
	//Monitor    number display     "1","H"	(WHITE)
	vDisplayLEDTimerHOn();
	//From EEPROM read value,judge occurred "Warning for Cleaning PCI UNIT Electrode" history.(Occurred: Hi , Never: No)
	if(bMcuEepromReadByte(EE_CLEARN_PCI_ELECTRODE)==TRUE)
		{
		vDisplay7SegShowHiOn();
		}
	else
		{
		vDisplay7SegShowNoOn();
		}
	
	Function(_vMonitorMode_Buzzer);
}
void vMonitorMode_18(void)
{
	vDisplayLEDTimerHOff();
	//Monitor    number display     "1","6"	(WHITE)
	vDisplayLEDTimer6On();
	//From EEPROM read "Error Mode"which occurred last display.
	if(bMcuEepromReadByte(EE_ERROR_MODE_LAST)==0)	//130327ra01***
		{
		vDisplay7SegShowNoOn();
		}
	else
		{
		vDisplay7SegShowHexNumOn(bMcuEepromReadByte(EE_ERROR_MODE_LAST));
		}	//130327ra01&&&
		
	Function(_vMonitorMode_Buzzer);
}
void vMonitorMode_19(void)
{
	//Monitor    number display     "1","6","H"	(WHITE)
	vDisplayLEDTimerHOn();
	//From EEPROM read "Error Counter of Ion Generation" value display.
	vSubMcuReadIonErrorCountValue();
	
	Function(_vMonitorMode_Buzzer);
}
void vMonitorMode_20(void)
{
	vDisplayLEDTimer6Off();
	vDisplayLEDTimerHOff();
	//Monitor    number display     "1","4"	(WHITE)
	vDisplayLEDTimer4On();
	//From main mcu [0x69] read "Voltage for judging ion generation" value and display.
	vSubMcuReadIonVoltageValue();
	
	Function(_vMonitorMode_Buzzer);
}
void vMonitorMode_21(void)
{
	//Monitor    number display     "1","4","H"	(WHITE)
	vDisplayLEDTimerHOn();
	//"Digital Indication(Blue)     "Software Version Main" (DEC)
	vDisplay7SegShowDecNumOn(MCU_FIRMWARE_VERSION_DECIMAL);
	
	Function(_vMonitorMode_Buzzer);
}
void vMonitorMode_22(void)
{
	vDisplayLEDTimerHOff();
	//Monitor    number display     "1","4","6"	(WHITE)
	vDisplayLEDTimer6On();
	//"Digital Indication(Blue)     "Software Version Sub"  (DEC)
	vDisplay7SegShowDecNumOn(MCU_FIRMWARE_VERSION_DECIMAL);
	
	Function(_vMonitorMode_Buzzer);
}
void vMonitorMode_23(void)
{
	bModeState=0;	//130306ra01
	//vDisplayLEDTimer1Off();
	//vDisplayLEDTimer4Off();
	//vDisplayLEDTimer6Off();
	vDisplay7segLedAllOff();	//130408ra02
	//vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);   //10s auto off.		// 130415jac02
	//vDisplay7SegShowDecNumAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);	//10s auto off.
	vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);//130402ra03
	
	Function(_vMonitorMode_Buzzer);
}


void vMonitorModeStateUpdate(void)
{
	_asm{ mov  a, %bModeState}; 
	_asm{ add  %PC, a };
	NOP();
	Function(_vMonitorMode_1);
	Function(_vMonitorMode_2);
	Function(_vMonitorMode_3);
	Function(_vMonitorMode_4);
	Function(_vMonitorMode_5);
	Function(_vMonitorMode_6);
	Function(_vMonitorMode_7);
	Function(_vMonitorMode_8);
	Function(_vMonitorMode_9);
	Function(_vMonitorMode_10);
	Function(_vMonitorMode_11);
	Function(_vMonitorMode_12);
	Function(_vMonitorMode_13);
	Function(_vMonitorMode_14);
	Function(_vMonitorMode_15);
	Function(_vMonitorMode_16);
	Function(_vMonitorMode_17);
	Function(_vMonitorMode_18);
	Function(_vMonitorMode_19);
	Function(_vMonitorMode_20);
	Function(_vMonitorMode_21);
	Function(_vMonitorMode_22);
	Function(_vMonitorMode_23);
}

#else	//130418ha03&&&
//130123ra01***
void vMonitorModeStateUpdate(void)
{
	switch(bModeState)	//130306ra01
		{
		case 1:
			//vDisplayLEDAirVolumeSettingIndicationOff();
			vDisplay7segLedAllOff();	//130408ra02
			//Monitor    number display 	"H"	(WHITE)
			vDisplayLEDTimerHOn();			
			//"Digital Indication(Blue)  "Fine Air Volume Level"    (HEX)
			vDisplay7SegShowHexNumOn(bAirVolume);
			break;
		case 2:
			vDisplayLEDTimerHOff();	
			//Monitor    number display  "6"	(WHITE)
			vDisplayLEDTimer6On();			
			//From Main MCU [0x60] read "Set value of Fan rotational speed[rpm]" divided by 10 and display.
            		goto MONITOR_MODE_SEND_COMMAND;
			break;
		case 3:
			//Monitor    number display "6","H"	(WHITE)
			vDisplayLEDTimerHOn();
			//From Main MCU [0x61] read "Detected value of Fan rotational speed[rpm]" divided by 10 and display.
            		goto MONITOR_MODE_SEND_COMMAND;
			break;
		case 4:
			vDisplayLEDTimer6Off();
			vDisplayLEDTimerHOff();
			//Monitor    number display 	"4"	(WHITE)
			vDisplayLEDTimer4On();
			//From Main MCU [0x62] read "Fan PWM value" and display.
            		goto MONITOR_MODE_SEND_COMMAND;
			break;
		case 5:
			//Monitor    number display     "4","H"	(WHITE)
			vDisplayLEDTimerHOn();
			//From Main MCU [0x68] read "Temperature A/D Value" and display.
            		goto MONITOR_MODE_SEND_COMMAND;
			break;
		case 6:
			vDisplayLEDTimerHOff();
			//Monitor    number display     "4","6"	(WHITE)
			vDisplayLEDTimer6On();
			//From Main MCU [0x67] read  "Humidity A/D Value" and display.
            		goto MONITOR_MODE_SEND_COMMAND;
			break;
		case 7:
			//Monitor    number display     "4","6","H"	(WHITE)
			vDisplayLEDTimerHOn();
			//Display Light A/D Value.	(HEX)	
			vDisplay7SegShowHexNumOn(bLightSensorADCAverage);	//130327ra02
			goto MONITOR_MODE_SEND_COMMAND;	//130327ra03
			break;	  
		case 8:
			vDisplayLEDTimer4Off();
			vDisplayLEDTimer6Off();
			vDisplayLEDTimerHOff();
			//Monitor    number display 	"2"	(WHITE)
			vDisplayLEDTimer2On();		
			//From Main MCU 0x6c read Temperature [¢J] value and display.
            		goto MONITOR_MODE_SEND_COMMAND;
			break;
		case 9:
			//Monitor    number display     "2","H"	(WHITE)
			vDisplayLEDTimerHOn();			
			//"Digital Indication(Blue)     "Humidity [%] Value"    (HEX)
            		goto MONITOR_MODE_SEND_COMMAND;
			break;
		case 10:
			vDisplayLEDTimerHOff();	
			//Monitor    number display     "2","6"	(WHITE)
			vDisplayLEDTimer6On();			
			//From EEPROM read "Accumulated time for cleaning Filter [Minute]" and display.
			//vDisplay7SegShowHexNumOn(bMcuEepromReadByte(EE_CLEANING_FILTER_TIME_HOUR_LOW));
			vDisplay7SegShowHexNumOn(FILTER_CLEAN_ACC_TIME_MINUTE);	//130402ra01
			goto MONITOR_MODE_SEND_COMMAND;	//130327ra03
			break;
		case 11:
			//Monitor    number display     "2","6","H"	(WHITE)
			vDisplayLEDTimerHOn();
			//"Digital Indication(Blue)     "Accumulated time for cleaning Filter [Hour]"   (HEX)
			//vDisplay7SegShowHexNumOn(bMcuEepromReadByte(EE_CLEANING_FILTER_TIME_HOUR_HIGH));
			vDisplay7SegShowHexNumOn((BYTE)(wFilterCleanHour%FILTER_CLEAN_ACC_TIME_HOUR_RATE));	//130402ra02
			break;	  
		case 12:
			vDisplayLEDTimer6Off();
			vDisplayLEDTimerHOff();
			//Monitor    number display     "2","4"	(WHITE)
			vDisplayLEDTimer4On();
			//"Digital Indication(Blue)     "Accumulated time for cleaning Filter [Day]"    (HEX)
			//vDisplay7SegShowHexNumOn(bMcuEepromReadByte(EE_CLEANING_FILTER_TIME_HOUR_HIGH));
			vDisplay7SegShowHexNumOn((BYTE)(wFilterCleanHour/FILTER_CLEAN_ACC_TIME_HOUR_RATE));	//130402ra02
			break;	  
		case 13:
			//Monitor    number display     "2","4","H"	(WHITE)
			vDisplayLEDTimerHOn();
			//From Main MCU [0x63] read 4 Byte and display 0 byte [Least significant byte] value.
			vSubMcuReadPciUnitUseAccTimeValue(PCI_UNIT_ACC_TIME_LEAST_BYTE);
			break;	 
		case 14:
			vDisplayLEDTimerHOff();
			//Monitor    number display     "2","4","6"	(WHITE)
			vDisplayLEDTimer6On();
            		//From Main MCU [0x63] read 4 Byte,and display [Low byte] value.
			vSubMcuReadPciUnitUseAccTimeValue(PCI_UNIT_ACC_TIME_LOW_BYTE);
			break;
		case 15:
			//Monitor    number display     "2","4","6","H"	(WHITE)
			vDisplayLEDTimerHOn();
			//From Main MCU [0x63] read 4 Byte,and display [High byte] value.
			vSubMcuReadPciUnitUseAccTimeValue(PCI_UNIT_ACC_TIME_HIGH_BYTE);
			break;
		case 16:
			vDisplayLEDTimer2Off();
			vDisplayLEDTimer4Off();
			vDisplayLEDTimer6Off();
			vDisplayLEDTimerHOff();
			//Monitor    number display 	"1"	(WHITE)
			vDisplayLEDTimer1On();
			//From Main MCU [0x63] read 4 Byte,and display [The most significant byte] value.
			vSubMcuReadPciUnitUseAccTimeValue(PCI_UNIT_ACC_TIME_MOST_BYTE);
			break;
		case 17:
			//Monitor    number display     "1","H"	(WHITE)
			vDisplayLEDTimerHOn();
			//From EEPROM read value,judge occurred "Warning for Cleaning PCI UNIT Electrode" history.(Occurred: Hi , Never: No)
			if(bMcuEepromReadByte(EE_CLEARN_PCI_ELECTRODE)==TRUE)
				{
				vDisplay7SegShowHiOn();
				}
			else
				{
				vDisplay7SegShowNoOn();
				}
			break;
		case 18:
			vDisplayLEDTimerHOff();
			//Monitor    number display     "1","6"	(WHITE)
			vDisplayLEDTimer6On();
			//From EEPROM read "Error Mode"which occurred last display.
			if(bMcuEepromReadByte(EE_ERROR_MODE_LAST)==0)	//130327ra01***
				{
				vDisplay7SegShowNoOn();
				}
			else
				{
				vDisplay7SegShowHexNumOn(bMcuEepromReadByte(EE_ERROR_MODE_LAST));
				}	//130327ra01&&&
			break;	  
		case 19:
			//Monitor    number display     "1","6","H"	(WHITE)
			vDisplayLEDTimerHOn();
			//From EEPROM read "Error Counter of Ion Generation" value display.
			vSubMcuReadIonErrorCountValue();
			break;
		case 20:
			vDisplayLEDTimer6Off();
			vDisplayLEDTimerHOff();
			//Monitor    number display     "1","4"	(WHITE)
			vDisplayLEDTimer4On();
			//From main mcu [0x69] read "Voltage for judging ion generation" value and display.
			vSubMcuReadIonVoltageValue();
			break;
		case 21:
			//Monitor    number display     "1","4","H"	(WHITE)
			vDisplayLEDTimerHOn();
			//"Digital Indication(Blue)     "Software Version Main" (DEC)
			vDisplay7SegShowDecNumOn(MCU_FIRMWARE_VERSION_DECIMAL);
			break;
		case 22:
			vDisplayLEDTimerHOff();
			//Monitor    number display     "1","4","6"	(WHITE)
			vDisplayLEDTimer6On();
			//"Digital Indication(Blue)     "Software Version Sub"  (DEC)
			vDisplay7SegShowDecNumOn(MCU_FIRMWARE_VERSION_DECIMAL);
			break;
		case 23:
			bModeState=0;	//130306ra01
			vDisplayLEDTimer1Off();
			vDisplayLEDTimer4Off();
			vDisplayLEDTimer6Off();
			//vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);   //10s auto off.		// 130415jac02
			//vDisplay7SegShowDecNumAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);	//10s auto off.
			vDisplay7SegShowAirVolumeAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);//130402ra03
			break;
		}
	
	goto BUZZZER;

	MONITOR_MODE_SEND_COMMAND:
		vSubMcuMonitorModeStatus(bModeState);

	BUZZZER:
		bModeState++;
	vBuzzerOutput(PI);
}
#endif	//130418ha03
/************************************************************************************
  The default mode which is the first mode after setting "Monitor Mode".

	"Monitor" number		0
	The power 			ON
	Air Volume 			Level 1(Fine Level 4)
	Timer 				OFF
	Rotation Mode 			OFF
	Louver Mode 			OFF (The louver stops after moving to the horizontal position)
	Watch Mode 			OFF
	Ion Mode 				Manual Mode

 "Air Volume Level", "Rotation Mode" and "Louver Mode" can be changed. Other modes can't be changed.
*************************************************************************************/
void vMonitorModeInitial(void)
{
	if(fgIsAutoRestartFunction())	//130309ra01	Auto Restart Function is valid, it's impossible to set this mode.
		{
		return;
		}
	bSpecialFunctionMode=MODE_MONITOR;
	vSetKeyState(KEY_MONITOR_MODE);
	bModeState=1;	//130306ra01
	vSubMcuSendSpecialMode(bSpecialFunctionMode);	//130327ra02

	//The power 			ON
	bPowerMode=POWER_MODE_ON;
	//vSubMcuSendPowerStatus(POWER_MODE_ON);	//130327ra02		//130418ra01

	//Air Volume 			Level 1(Fine Level 4)
	//vFanVolumeSet(FAN_MOTOR_FINE_LEVEL_4);	//130418ra01
	bAirVolume=FAN_MOTOR_FINE_LEVEL_4;	//130418ra01
	
	//Timer 				OFF
	//vSetOnOffTimer(TIMER_MODE_OFF);	//130411ra01
	
	//Rotation Mode 		OFF
	//vOscillateModeSet(OSCILLATE_OFF);	//130411ra01
	
	//Louver Mode 		OFF (The louver stops after moving to the horizontal position)
	//vLouverModeSet(LOUVER_INITIAL_POSITION);		//130327ra02	//130417ra01		//130418ra01

	//Watch Mode 		OFF
	//vSetWatchMode(WATCH_MANUAL);	//130411ra01
	
	//Ion Mode 			Manual Mode
	//vSetIONMode(ION_MANUAL);		//130411ra01

	//vPutEventQueue(EVENT_IR, IR_POWER, 0);	//130327ra02
	//vBuzzerOutput(PI);	//130418ra01
	//Dispaly Air Volume Setting Indication(WHITE).10s Auto off.    (DEC)
	//vDisplayLEDAirVolumeSettingIndicationAutoOff(DISPLAY_TIME_10_SECOND);
	//Dispaly "Air Volume value" on 7seg.10s Auto off.    (DEC)
	//vDisplay7SegShowDecNumAutoOff(bAirVolume, DISPLAY_TIME_10_SECOND);
	//vDisplay7SegShowDecNumAutoOff(FAN_MOTOR_FINE_LEVEL_4, DISPLAY_TIME_10_SECOND);	//130408ra04
	vDisplay7SegShowAirVolumeAutoOff(FAN_MOTOR_FINE_LEVEL_4, DISPLAY_TIME_10_SECOND);
	vDisplayLEDAirVolume1On();
}


/**********************************************************
Operating "Timer Button" can change displays.
Operating "Timer Button" increases "Monitor Mode" number.
But when number 22 is set, pushing "Timer Button" changes to number 0.
***********************************************************/
void vMonitorModeKeyProcess(void)
{
	if(fgExecuteMonitorMode==FALSE)	//130329ha01
		return;	//130329ha01
	fgExecuteMonitorMode=FALSE;	//130329ha01

	switch(bIRKey)
		{
		case IR_TIMER:
		case IR_TOUCH_TIMER:
			vMonitorModeStateUpdate();
			break;
		case IR_ION_MODE:
		case IR_WATCH_MODE:
		case IR_TOUCH_WATCH_MODE:
		case IR_CHILD_LOCK:	//130411ra02***
		case IR_LIGHT_OFF_FUNCTION:
		case IR_AUTO_RESTART_FUNCTION:
		case IR_FILTER_CLEANING:	//130411ra02&&&
			//if(bModeState==1)	//130306ra01	//130408ra03
			return;
		default:
			if(bModeState==1)	//130306ra01
				{
				vNormalModeKeyProcess();
				}
			break;
		}
}
//130123ra01&&&
//130308ra01&&&

#endif
