#define _MODE_SERVICE_MONITOR_C_
#include "general.h"

#ifdef SERVICE_MONITOR_MODE_FUNCTION


//130306ra02***	//130123ra01***
/*********************************************************************************
 NO. |  			Item								|			Display
----------------------------------------------------------------------------------		
  0    |Mode set									| All LEDs ON
  1	|Accumulated time for Unit Replacement				|"Air Volume Indication Level 1" lights up.
	|											|"Digital Indication [(*1)]" lights up.
  2	|History of "Warning for Cleaning PCI UNIT Electrode"	|"Air Volume Indication Level 1" lights up.
	|											|"Air Volume Indication Level 2" lights up.
	|											|"Digital Indication [(*2)]" lights up.
  3	|"Error Mode" which occurred last					|"Air Volume Indication Level 1" lights up.
	|											|"Air Volume Indication Level 2" lights up.
	|											|"Air Volume Indication Level 3" lights up.
	|											|"Digital Indication [(*3)]" lights up.
**********************************************************************************
Remark:
(*1) Time[hours] of "Accumulated time for Unit Replacement" divided by 1000[hours]
	This item is displayed in decimal, not hexadecimal.
	(example 1) 15000 hours ¡÷ "15"
	(example 2) 17800 hours ¡÷ "17"
	
(*2) If "Warning for Cleaning PCI UNIT Electrode" has ever occurred, "Hi" lights up.
	If "Warning for Cleaning PCI UNIT Electrode" has never occurred, "No" lights up.
	
(*3) Memorized "Error Mode" which occurred last and their displays are as follows.
	Other "Error Mode" isn't memorized.
	-------------------------------------------
	Error Items						 |	Display
	-------------------------------------------
	Non 								 |	"No"
	Fan Motor Rotation Error 				 |	"C1"
	Temperature and Humidity Sensor Error 	 |	"C4"
	Microcomputer Communication Error 	 |	"C6"		//delete
	PCI Unit Data Error 					 |	"C8"
	-------------------------------------------
*/

#if 1	//130418ha02***
void vServiceMonitorMode_End(void)
{
	bModeState++;
	vBuzzerOutput(PI);		//130311ra01
}
void vServiceMonitorMode_1(void)
{
	//Turn off all LED display.
	//vDisplay7segLedAllOff();//130419gr01
	//vDisplayLEDAllOff();//130419gr01
	vDisplay7segLedAndTouchLedAllOff();//130419gr01
	
	vDisplayLEDAirVolume1On();
	//From [0x63] read Pci ACC Time for 4 Byte.
	vSubMcuReadPciUnitUseAccHourValue();	//Get the ACC time byte0(bit 0~7).
	
	Function(_vServiceMonitorMode_End);
}
void vServiceMonitorMode_2(void)
{
	//From EEPROM read value,judge occurred "Warning for Cleaning PCI UNIT Electrode" history.(Occurred: Hi , Never: No)
	if(bMcuEepromReadByte(EE_CLEARN_PCI_ELECTRODE)==TRUE)
		{
		vDisplay7SegShowHiOn();
		}
	else
		{
		vDisplay7SegShowNoOn();
		}
	vDisplayLEDAirVolume2On();
	
	Function(_vServiceMonitorMode_End);
}
void vServiceMonitorMode_3(void)
{
	vDisplayLEDAirVolume3On();
	//From EEPROM read "LAST ERROR" type.Judge which ERROR type and display.
	if(bMcuEepromReadByte(EE_ERROR_MODE_LAST)==0)	//130327ra01***
		{
		vDisplay7SegShowNoOn();
		}
	else
		{
		vDisplay7SegShowHexNumOn(bMcuEepromReadByte(EE_ERROR_MODE_LAST));
		}//130327ra01&&&
		
	Function(_vServiceMonitorMode_End);
}
void vServiceMonitorMode_4(void)
{
	//vDisplayLEDAllOn(); //130419gr01
	//vDisplay7segLedAllOn();//130419gr01
	vDisplay7segLedAndTouchLedAllOn();//130419gr01
	
	bModeState = 0;	//130123ra01
	
	Function(_vServiceMonitorMode_End);
}


void vServiceMonitorModeStateUpdate(void)
{
	_asm{ mov  a, %bModeState}; 
	_asm{ add  %PC, a };
	NOP();
	Function(_vServiceMonitorMode_1);
	Function(_vServiceMonitorMode_2);
	Function(_vServiceMonitorMode_3);
	Function(_vServiceMonitorMode_4);
}

#else	//130418ha02&&&
void vServiceMonitorModeStateUpdate(void)
{
	switch(bModeState)	//130123ra01
		{
		case 1:
			//Turn off all LED display.
			//vDisplay7segLedAllOff();//130419gr01
			//vDisplayLEDAllOff();//130419gr01
			vDisplay7segLedAndTouchLedAllOff();//130419gr01

			vDisplayLEDAirVolume1On();
			//From [0x63] read Pci ACC Time for 4 Byte.
			vSubMcuReadPciUnitUseAccHourValue();	//Get the ACC time byte0(bit 0~7).
			break;
		case 2:
			//From EEPROM read value,judge occurred "Warning for Cleaning PCI UNIT Electrode" history.(Occurred: Hi , Never: No)
			if(bMcuEepromReadByte(EE_CLEARN_PCI_ELECTRODE)==TRUE)
				{
				vDisplay7SegShowHiOn();
				}
			else
				{
				vDisplay7SegShowNoOn();
				}
			vDisplayLEDAirVolume2On();
			break;		
		case 3:
			vDisplayLEDAirVolume3On();
			//From EEPROM read "LAST ERROR" type.Judge which ERROR type and display.
			if(bMcuEepromReadByte(EE_ERROR_MODE_LAST)==0)	//130327ra01***
				{
				vDisplay7SegShowNoOn();
				}
			else
				{
				vDisplay7SegShowHexNumOn(bMcuEepromReadByte(EE_ERROR_MODE_LAST));
				}//130327ra01&&&
			break;
		case 4:
			//vDisplayLEDAllOn(); //130419gr01
			//vDisplay7segLedAllOn();//130419gr01
			vDisplay7segLedAndTouchLedAllOn();//130419gr01

			bModeState = 0;	//130123ra01
			break;							
		}
	bModeState++;
	vBuzzerOutput(PI);		//130311ra01
}
#endif	//130418ha02
/************************************************************************************
 Insert a plug into a socket without pushing any buttons.
 First, push "Vertical Direction Button(Unit)". 
 And push "Reset Button(Unit)" 3 times without releasing "Vertical Direction Button(Unit)".
 At this time, the buzzer sounds "Pi" and "Service Monitor Mode" is set.
 But the above operation needs to be executed within from 0.5 second to 5 seconds after inserting a plug.
 <Dispaly:>	All LEDs On.
 <Sound:>	Pi.
*************************************************************************************/
void vServiceMonitorModeInitial(void)
{
	if(fgIsInWatchMode()||fgIsInPowerOnMode()||fgIsInTimerOnOffFunction())	//130415ra01***	//130422ra01	It is impossible to set "service monitor mode" when the "Watch Mode" is set valid.
		{
		return;
		}//130415ra01&&&
	if(fgIsAutoRestartFunction())	//130309ra01	Auto Restart Function is valid, it's impossible to set this mode.
		{
		return;
		}
	bSpecialFunctionMode=MODE_SERVICE_MONITOR;
	vSetKeyState(KEY_SERVICE_MONITOR_MODE);
	vSubMcuSendSpecialMode(bSpecialFunctionMode);
	//vBuzzerOutput(PI);
	//All LED "TURN ON" and display "88" on the 7seg.
	//vDisplayLEDAllOn();//130419gr01
	//vDisplay7segLedAllOn();//130419gr01
	vDisplay7segLedAndTouchLedAllOn();//130419gr01

	bModeState=1;	//130123ra01
}

void vServiceMonitorModeKeyProcess(void)
{
	switch(bIRKey)
		{
		//case IR_WATCH_MODE:
		case IR_TOUCH_WATCH_MODE:
			vServiceMonitorModeStateUpdate();
			break;
		default:
			break;
		}
}
//130306ra02&&&

//130123ra01&&&
#endif

