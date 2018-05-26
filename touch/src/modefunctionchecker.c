#define _MODE_FUNCTION_CHECKER_C_
#include "general.h"


#ifdef FUNCTION_CHECKER_MODE_FUNCTION

#define FAN_MOTOR_FINE_LEVEL_1		1
#define FAN_MOTOR_FINE_LEVEL_24		24
//#define HUMIDITY_VALUE_MIN		0x53
//#define HUMIDITY_VALUE_MAX	0x5c
//#define TEMPERATURE_VALUE_MIN	0x7f
//#define TEMPERATURE_VALUE_MAX	0x73
#define LIGHT_SENSOR_VALUE_BRIGHT	0x30
#define LIGHT_SENSOR_VALUE_DARK		0x29
#define DIGITAL_DISPLAY_NUM_1	1
#define DIGITAL_DISPLAY_NUM_2	2
#define DIGITAL_DISPLAY_NUM_3	3
#define DIGITAL_DISPLAY_NUM_4	4
#define DIGITAL_DISPLAY_NUM_5	5
#define DIGITAL_DISPLAY_NUM_6	6
#define DIGITAL_DISPLAY_NUM_7	7
#define DIGITAL_DISPLAY_NUM_8	8
#define DIGITAL_DISPLAY_NUM_9	9
#define DIGITAL_DISPLAY_NUM_10	10
#define DIGITAL_DISPLAY_NUM_11	11
#define DIGITAL_DISPLAY_NUM_12	12
#define DIGITAL_DISPLAY_NUM_13	13
#define DIGITAL_DISPLAY_NUM_14	14



void vFunctionCheckerModeKeyProcess(void)
{
	if(fgExecuteFunctionCheckerMode==FALSE)	//130329ha01
		return;	//130329ha01
	fgExecuteFunctionCheckerMode=FALSE;	//130329ha01
	
	bIRKeySub=(bIRKeySub+3)/4;	//Air volume from 1~33 to 1~9.		//130310ha01
	switch(bModeState)	//130306ra01
		{
		case 0:
			if(bIRKey==IR_NEXT_STEP)
				{
				//vDisplayLEDAllOff();//130419gr01
				//vDisplay7segLedAllOff();//130419gr01
				vDisplay7segLedAndTouchLedAllOff();//130419gr01

				vDisplayLEDTubeWhiteOn(); //"Plasmacluster Sign(Blue)" lights up.
				//vFanVolumeSet(bAirVolume);	//130409le01
				vFanVolumeSet(FAN_MOTOR_FINE_LEVEL_24);
				//vDisplay7SegShowHexNumOn(MCU_FIRMWARE_VERSION_DECIMAL); //"Version Number"(Main MCU) //130407le01
				vDisplay7SegShowDecNumOn(MCU_FIRMWARE_VERSION_UNIT);	//130407le01 

				goto BUZZER_PI_AND_STATE;	//130314le02
				}
			break;
		case 1:
			if(bIRKey==IR_TOUCH_WATCH_MODE)
				{
				//vDisplayLEDAllOff();	//130409le01***
				//vDisplay7segLedAllOff();
				vDisplayLEDTubeWhiteOff();	//130409le01&&&
				vDisplay7SegShowDecNumOn(MCU_FIRMWARE_VERSION_DECIMAL); //"Version Number"(Main MCU)	//130429le02
				vDisplayLEDPCIReplacingOn();
				bModeState++;	//130306ra01
				//goto BUZZER_PI_LOUD;	//130313le01	//130407le02
				vBuzzerOutput(PI_LOUD);	//130407le02
				}
			break;
		case 2:
			if(bIRKey==IR_TOUCH_HORIZONTAL_OSCILLATING)
				{
				//vDisplayLEDAllOff();	
				vDisplayLEDPCIReplacingOff();	//130409le01
				vDisplayLEDFilterCleanOn();
				vDisplayLEDClothingDeodorantOn();
				vDisplayLEDTimer4On();
				vDisplayLEDOffTimerOn();
				vDisplayLEDTimer1On();
				//vDisplayLEDTubeWhiteOn();	//Plasmacluster sign lights up.	130409le01
				vDisplayLEDPlasmaclusterShowerOn();	//130409le01
				vDisplayLEDWarningBuzzerOn();
				vDisplayLEDWatchGreenOn();
				vOscillateModeSet(OSCILLATE_15D);

				//vDisplay7SegShowHexNumOn(MCU_FIRMWARE_VERSION_DECIMAL);//"Version Number". (Sub MCU)	//130407le01				
				vDisplay7SegShowDecNumOn(MCU_FIRMWARE_VERSION_UNIT);	//130407le01

				goto BUZZER_PI_AND_STATE;	//130314le02
				}
			break;
		case 3:
			if(bIRKey==IR_TOUCH_VERTICAL_DIRECTION)
				{
				//vDisplay7segLedAllOff();//130419gr01
				//vDisplayLEDAllOff();//130419gr01
				vDisplay7segLedAndTouchLedAllOff();//130419gr01

				vDisplayLEDWatchRedOn();
				vDisplayLEDChildLockSignOn();
				vDisplayLEDChildLockIndicationOn();
				vOscillateModeSet(OSCILLATE_OFF);
				vLouverModeSet(LOUVER_SWING);

				vDisplay7SegShowDecNumOn(MCU_FIRMWARE_VERSION_DECIMAL);//"Version Number". (Sub MCU)	//130429le02

				goto BUZZER_PI_AND_STATE;	//130314le02
				}
			break;
		case 4:
			if(bIRKey==IR_TOUCH_RESET)
				{
				//vDisplayLEDAllOff(); //130419gr01
				//vDisplay7segLedAllOff();	//130409le01 //130419gr01
				vDisplay7segLedAndTouchLedAllOff();//130419gr01

				vDisplayLEDAirVolumeSettingIndicationOn();	//130322le01
				vDisplayLEDAngleSettingIndicationOn();				
				//vDisplayLEDWatchRedOff();	//130322le01	130409le01

				vLouverModeSet(LOUVER_STOP);
				//vSubMcuPinCapsel40PEnable(TRUE);	//Ion Sensor Capse:l ON.	//130409le01
				vSubMcuPinCapsel40PEnable(FALSE);	//Ion Sensor Capse:l ON.	//130409le01

				vDisplay7SegShowDecNumOn(DIGITAL_DISPLAY_NUM_1);

				goto BUZZER_PI_AND_STATE;	//130314le02
				}
			break;
		case 5:
			if(bIRKey==IR_TOUCH_TIMER)
				{
				//vDisplayLEDAllOff();	//130409le01***
				//vDisplay7segLedAllOff();	//130328le01
				vDisplayLEDAirVolumeSettingIndicationOff();	//130409le01
				vDisplayLEDAngleSettingIndicationOff();	//130409le01
				//vDisplayLEDTimerHOn();	//130409le01

				//vSubMcuPinCapsel40PEnable(FALSE);	//Ion Sensor Capse:l OFF	130409le01
				vSubMcuPinCapsel40PEnable(TRUE);	//Ion Sensor Capse:l OFF	130409le01
				//vSubMcuPinIonResetEnable(FALSE);	//Ion Sensor Reset: ON.	130409le01
				vSubMcuPinIonResetEnable(TRUE);	//Ion Sensor Reset: ON.	130409le01
				
				//vSubMcuReadIonDeltaV();	//130328le01
				vDisplay7SegShowDecNumOn(DIGITAL_DISPLAY_NUM_2);

				goto BUZZER_PI;    //130313le01
				}
			break;
		case 6:
			if(bIRKey==IR_TOUCH_TIMER)	//130419le02
		//	if(bIRKey==IR_NEXT_STEP)	//130419le02
				{
				//vDisplayLEDAllOff();	//130409le01***
				//vDisplay7segLedAllOff();	//130328le01
				vDisplayLEDOnTimerOff();	//130409le01&&&
			
				//vSubMcuPinIonResetEnable(TRUE);	//Ion Sensor Reset: OFF.  //130313le01	130409le01			
				vSubMcuPinIonResetEnable(FALSE);	//Ion Sensor Reset: OFF.  //130313le01	130409le01
				//vDisplayLEDTubeWhiteOn();		//Plasmacluster: ON.	//130312le01	//130409le01
				vSubMcuPinPciPowerEnable(TRUE);	//PC:ON	//130409le01

				//vSubMcuReadIonDeltaV();	//130328le01				
				vDisplay7SegShowDecNumOn(DIGITAL_DISPLAY_NUM_3);

				goto BUZZER_PI;    //130313le01
				}
		case 7:
			if(bIRKey==IR_TOUCH_POWER)
				{

				//vDisplayLEDAllOff();	//130409le01
				vDisplayLEDTimer2Off();	//130328le01
				
				//vDisplayLEDTubeWhiteOff();	//Plasmacluster: OFF.	//130409le01
				vSubMcuPinPciPowerEnable(FALSE);	//PC:OFF	//130409le01
				vDisplay7SegShowDecNumOn(DIGITAL_DISPLAY_NUM_4);
				
				//if(bLightSensorADCAverage > LIGHT_SENSOR_VALUE_BRIGHT)	//130313le01
				if(fgTheLightSourceIsDark==FALSE)	//130328le01
					{
					vDisplayLEDTimer6On();
					bModeState++;	//130313le01
					}
				
				goto BUZZER_PI;    //130313le01
				}
			break;
		case 8:
			//if(fgTheLightSourceIsDark==FALSE)	//light sensor Bright
			if(bIRKey==IR_NEXT_STEP)	//130328le01
				{
				//vDisplayLEDAllOff();	//130409le01
				vDisplayLEDTimer6Off();	//130328le01
				
				//if(bLightSensorADCAverage < LIGHT_SENSOR_VALUE_DARK)	//130313le01
				if(fgTheLightSourceIsDark==TRUE)	//130328le01
					{
					vDisplayLEDTimerHOn();
					bModeState++;	//130313le01
					}
				vDisplay7SegShowDecNumOn(DIGITAL_DISPLAY_NUM_5);
				goto BUZZER_PI;    //130313le01
				}
			break;
		case 9:
			if((bIRKey==IR_TOUCH_AIR_VOLUME)&&(bIRKeySub==1))	//130310ha01
				{
				//vDisplayLEDAllOff();	//130409le01
				vDisplayLEDTimerHOff();	//130328le01
				
				vFanVolumeSet(FAN_MOTOR_FINE_LEVEL_1);
				vDisplayLEDAirVolume1On();
				vDisplay7SegShowDecNumOn(DIGITAL_DISPLAY_NUM_6);

				goto BUZZER_PI_AND_STATE;	//130314le02
				}
			break;
		case 10:
			if((bIRKey==IR_TOUCH_AIR_VOLUME)&&(bIRKeySub==2))	//130310ha01
				{
				//vDisplayLEDAllOff();	//130409le01
				vDisplayLEDAirVolume1Off();	//130409le01

				vDisplayLEDAirVolume2On();
				vDisplay7SegShowDecNumOn(DIGITAL_DISPLAY_NUM_7);

				goto BUZZER_PI_AND_STATE;	//130314le02
				}
			break;
		case 11:
			if((bIRKey==IR_TOUCH_AIR_VOLUME)&&(bIRKeySub==3))	//130310ha01
				{
				//vDisplayLEDAllOff();	//130409le01
				vDisplayLEDAirVolume2Off();	//130409le01

				vDisplayLEDAirVolume3On();
				vDisplay7SegShowDecNumOn(DIGITAL_DISPLAY_NUM_8);

				goto BUZZER_PI_AND_STATE;	//130314le02
				}
			break;
		case 12:
			if((bIRKey==IR_TOUCH_AIR_VOLUME)&&(bIRKeySub==4))	//130310ha01
				{
				//vDisplayLEDAllOff();	//130409le01
				vDisplayLEDAirVolume3Off();	//130409le01

				vDisplayLEDAirVolume4On();
				vDisplay7SegShowDecNumOn(DIGITAL_DISPLAY_NUM_9);

				goto BUZZER_PI_AND_STATE;	//130314le02
				}
			break;
		case 13:
			if((bIRKey==IR_TOUCH_AIR_VOLUME)&&(bIRKeySub==5))	//130310ha01
				{
				//vDisplayLEDAllOff();	//130409le01
				vDisplayLEDAirVolume4Off();	//130409le01
				vDisplayLEDAirVolume5On();
				vDisplay7SegShowDecNumOn(DIGITAL_DISPLAY_NUM_10);

				goto BUZZER_PI_AND_STATE;	//130314le02
				}
			break;
		case 14:
			if((bIRKey==IR_TOUCH_AIR_VOLUME)&&(bIRKeySub==6))	//130310ha01
				{
				//vDisplayLEDAllOff();	//130409le01
				vDisplayLEDAirVolume5Off();	//130409le01
				vDisplayLEDAirVolume6On();
				vDisplay7SegShowDecNumOn(DIGITAL_DISPLAY_NUM_11);
	
				goto BUZZER_PI_AND_STATE;	//130314le02
				}
			break;
		case 15:
			if((bIRKey==IR_TOUCH_AIR_VOLUME)&&(bIRKeySub==7))	//130310ha01
				{
				//vDisplayLEDAllOff();	//130409le01
				vDisplayLEDAirVolume6Off();	//130409le01

				vSubMcuReadFanMotorRotationValue();	//130313le01

				vDisplay7SegShowDecNumOn(DIGITAL_DISPLAY_NUM_12);

				goto BUZZER_PI;    //130313le01
				}
			break;
		case 16:
			if((bIRKey==IR_TOUCH_AIR_VOLUME)&&(bIRKeySub==8))	//130310ha01
				{
				//vDisplayLEDAllOff();	//130409le01
				vDisplayLEDAirVolume7Off();	//130409le01

				vSubMcuReadTempAdcValue();	//130313le01
				vDisplay7SegShowDecNumOn(DIGITAL_DISPLAY_NUM_13);

				goto BUZZER_PI;    //130313le01	
				}
			break;
		case 17:
			if((bIRKey==IR_TOUCH_AIR_VOLUME)&&(bIRKeySub==9))	//130310ha01
				{
				//vDisplayLEDAllOff();	//130409le01
				vDisplayLEDAirVolume8Off();	//130409le01

				vSubMcuReadHumAdcValue();	//130313le01
				vDisplay7SegShowDecNumOn(DIGITAL_DISPLAY_NUM_14);

				goto BUZZER_PI;    //130313le01					
				}
			break;
		case 18:
			if(bIRKey==IR_TIMER)
				{
				//vPowerOffMode();	//130328le01
				fgExecutePowerOffMode=TRUE;	//130328le01
				//goto BUZZER_PI_LOUD;	//130313le01	130328le01	
				}
			break;
		default:
			break;
		}
	return;
	

	//BUZZER_PI_LOUD:	//130407le02
	BUZZER_PI:	//130407le02
		vBuzzerOutput(PI);	//130313le01&&&
		vSubMcuFunctionCheckerModeStatus(bModeState);	//130407le02
		return;	//130314le02***
	BUZZER_PI_AND_STATE:
		bModeState++;
	//BUZZER_PI:	//130313le01***	//130407le02
	//	vSubMcuFunctionCheckerModeStatus(bModeState);	//130328le01	//130407le02
		vBuzzerOutput(PI);	//130314le02&&&
}

/**********************************************************
(1)First connect to the PWB Unit.
(2)Cover open
(3)ISSW OFF
(4)AC on
FNC: Hi	(No.21 pin of Main MCU).
ISSW: OFF
COVER: OFF
Light Sensor: Bright
RHT: About 28 degrees C
HMSN: About 52%
***********************************************************/
void vFunctionCheckerModeInitial(void)
{
	bSpecialFunctionMode=MODE_FUNCTION_CHECKER_TEST;
	vSetKeyState(KEY_FUNCTION_CHECKER_MODE);
	bModeState = 0;	//130306ra01

	vSubMcuSendSpecialMode(bSpecialFunctionMode);	//130328le01
	//vSubMcuSendPowerStatus(POWER_MODE_ON);	//130409le01	//130417le03
	//vDisplayLEDAllOn();//130419gr01
	//vDisplay7segLedAllOn();//130419gr01
	vDisplay7segLedAndTouchLedAllOn();//130419gr01

	vBuzzerOutput(PI);
}
#endif

