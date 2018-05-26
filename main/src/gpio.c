#define _GPIO_C_
#include "general.h"

void vInitialGPIO(void)
{
	//All output pin
	vPCIPowerOff();
	PIN_PCI_POWER_IO_OUTPUT;
	vOTPIntDis();
	PIN_OTP_INT_IO_OUTPUT;
	//vIONResetDIS();//130424Ad02
	vIONResetEN();//130424Ad02
	PIN_ION_RESET_IO_OUTPUT;
	vCapacitance40PF();
	PIN_CAP40F_IO_OUTPUT;

	vLouverMotor1DIS();
	vLouverMotor2DIS();
	vLouverMotor3DIS();
	vLouverMotor4DIS();
	PIN_LOUVER_MOTOR1_IO_OUTPUT;
	PIN_LOUVER_MOTOR2_IO_OUTPUT;
	PIN_LOUVER_MOTOR3_IO_OUTPUT;
	PIN_LOUVER_MOTOR4_IO_OUTPUT;

	vBuzzerVoiceNormal();
	PIN_BUZZER_VOICE_CONTROL_IO_OUTPUT;
	vSDAHigh();
	vSCLHigh();
	PIN_SDA_OPEN_DRAIN;
	PIN_SDA_IO_OUTPUT;
	PIN_SCL_OPEN_DRAIN;
	PIN_SCL_IO_OUTPUT;
	//vI2CFree();//130315sh01***
	//PIN_BUSY_IO_OUTPUT;
	PIN_BUSY_IO_INPUT;//130315sh01&&&

	vRotationMotor1DIS();
	vRotationMotor2DIS();
	vRotationMotor4DIS();
	vRotationMotor5DIS();
	PIN_ROTATION_MOTOR1_IO_OUTPUT;
	PIN_ROTATION_MOTOR2_IO_OUTPUT;
	PIN_ROTATION_MOTOR4_IO_OUTPUT;
	PIN_ROTATION_MOTOR5_IO_OUTPUT;

	PIN_BUZZER_OUT_LOW;
	PIN_BUZZER_IO_OUTPUT;

	PIN_FAN_MOTOR_OUT_LOW;
	PIN_FAN_MOTOR_IO_OUTPUT;

	//All input pin
	PIN_PCI_NONE_IO_INPUT;
	PIN_COVER_SWITCH_IO_INPUT;
	
	//ADC input
	PIN_ION_IN_ALT_FUNC_EN;
	PIN_TH_OUT_IN_ALT_FUNC_EN;
	PIN_NTC_IN_ALT_FUNC_EN;

	PIN_TC2_INPUT;

	//FunctionCheckerMode Pin
	PIN_FUNCTION_CHECKER_PULL_DOWN;	//130403le01
}
#if 0//130418sh02
void vPollingPCINone(void)
{
	static bit fgLastPCINone=1;
	bit fgPCINoneStatus;
	BYTE bPCINoneEvent;
	fgPCINoneStatus=PIN_PCI_NONE_READ;
	if(fgLastPCINone!=fgPCINoneStatus)
		{
		if(fgPCINoneIsNormal())
			{
			bPCINoneEvent = EVENT_PCI_NONE_IS_NORMAL;



			
			}
		else	
			{
			bPCINoneEvent = EVENT_PCI_NONE_IS_ERROR;



			
			}
		vPutEventQueue(bPCINoneEvent,0 ,0);
		fgLastPCINone=fgPCINoneStatus;
		}
}
#endif//130418sh02
void vPollingSpeedUpMode(void)	//130407ra01***
{
#if 0//130418sh02
	static BYTE bLastSpeedUpModeState=0;
	BYTE bSpeedUpModeStatus;
	bSpeedUpModeStatus=PIN_SPEED_UP_MODE;
	if(bLastSpeedUpModeState!=bSpeedUpModeStatus)
		{
		if(fgSpeedUpModeEntry())
			{
			fgSpeedUp=TRUE;
			}
		else	
			{
			fgSpeedUp=FALSE;
			}
		vIntSpeedUpMode(fgSpeedUp);
		bLastSpeedUpModeState=bSpeedUpModeStatus;
		}
#else//130418sh02***
	static BOOL fgLastStatusIsSpeedUpMode=FALSE;
	BOOL fgSpeedUpModeStatus;
	fgSpeedUpModeStatus=PIN_SPEED_UP_MODE;
	if(fgSpeedUpModeEntry())
		{
		if(fgLastStatusIsSpeedUpMode==FALSE)
			{
			fgSpeedUp=TRUE;
			vIntSpeedUpMode(fgSpeedUp);
			fgLastStatusIsSpeedUpMode=TRUE;
			}
		}
	else
		{
		if(fgLastStatusIsSpeedUpMode==TRUE)
			{			
			fgSpeedUp=FALSE;
			vIntSpeedUpMode(fgSpeedUp);
			fgLastStatusIsSpeedUpMode=FALSE;
			}
		}
#endif//130418sh02&&&
}//130407ra01&&&

#if 0	//130410vi01
void vPollingCoverSwitch(void)
{
	static BOOL fgLastCoverSwitch=0;
	BOOL fgCoverSwitchStatus;
	BYTE bCoverSwitchEvent;
	fgCoverSwitchStatus=PIN_COVER_SWITCH_READ;
	if(fgIsInPowerOnMode()||(fgIsInPowerOffMode()&&fgIsInWatchMode())||fgIsInFunctionCheckerTestMode())	//130327Li02
		{	//130327Li02
		if(fgLastCoverSwitch!=fgCoverSwitchStatus)
			{
			if(fgCoverSwitchIsNormal())
				{
				bCoverSwitchEvent = EVENT_COVER_SWITCH_IS_NORMAL;
				}
			else	
				{
				bCoverSwitchEvent = EVENT_COVER_SWITCH_IS_OPEN;
				}
			vPutEventQueue(bCoverSwitchEvent,0 ,0);
			fgLastCoverSwitch=fgCoverSwitchStatus;
			}
		}	//130327Li02
	else		//130327Li02***
		{
		fgLastCoverSwitch=0;	//default close
		}	//130327Li02&&&
}
#else
#define COVER_SWITCH_ERROR_TIMES 8	// 25ms*8=200ms=0.2s	//130307Li01
#define COVER_IS_OPEN 1
#define COVER_IS_CLOSE 0	
//Put this function in 25ms.
void vPollingCoverSwitch(void)		//130307Li01***
{
	static BOOL fgLastCoverSwitch=COVER_IS_CLOSE;
	BOOL fgCoverSwitchStatus;
	BYTE bCoverSwitchEvent;
	static BYTE bCoverSwitchCount; //130307Li01
	fgCoverSwitchStatus=PIN_COVER_SWITCH_READ;

	if(fgIsInPowerOnMode()||fgIsInWatchMode()) //130327Li02
		{
		if(fgCoverSwitchIsOpen()&& (bCoverSwitchCount<=COVER_SWITCH_ERROR_TIMES))
			{
			bCoverSwitchCount++;
			}
		if(bCoverSwitchCount==COVER_SWITCH_ERROR_TIMES)
			{
			vPutEventQueue(EVENT_COVER_SWITCH_IS_OPEN,0 ,0);
			bCoverSwitchCount = 0;
			}
		}
	else
		{
		bCoverSwitchCount = 0;
		if(fgLastCoverSwitch!=fgCoverSwitchStatus)
			{
			if(fgCoverSwitchIsOpen())
				{
				bCoverSwitchEvent = EVENT_COVER_SWITCH_IS_OPEN;
				}
			else 
				{
				bCoverSwitchEvent = EVENT_COVER_SWITCH_IS_NORMAL;
				}
			vPutEventQueue(bCoverSwitchEvent,0 ,0);
			fgLastCoverSwitch=fgCoverSwitchStatus;
			}
		}
}
#endif	//130410vi01&&&

void vPollingTouchMcuBusy(void)//130315sh01***
{
#if 0//130418sh02
	static BOOL fgLastBusyStatus=0;
	BOOL  fgBusyStatus;
	fgBusyStatus=PIN_BUSY_READ;
	if(fgLastBusyStatus!=fgBusyStatus)
		{
		if(fgBusyStatus)
			{
			fgI2CIntBusy=FALSE;
			}
		fgLastBusyStatus=fgBusyStatus;
		}
#else//130418sh02
	static BOOL fgLastStatusIsBusy=TRUE;
	BOOL fgNoBusyStatus;
	fgNoBusyStatus=PIN_BUSY_READ;
	if(fgTouchMCUIsNotBusy())
		{
		if(fgLastStatusIsBusy==TRUE)
			{
			fgI2CIntBusy=FALSE;
			fgLastStatusIsBusy=FALSE;
			}
		}
	else
		{
		fgLastStatusIsBusy=TRUE;
		}
#endif//130418sh02
}//130315sh01&&&


//Polling FG pin.	//130411Ke01***
void vPollingFG(void)
{
	static BOOL fgFGPrevious=0;
	//BOOL fgTouchINTStatus;	//130424Ke01 	,No used

	if(fgFanFGIsON() && (fgFGPrevious==0))
		{	//FG pin rise edge.
		TC2_DATA_BUFFER_LOW++;
		}
	fgFGPrevious=PIN_FAN_FG_READ;
}	//130411Ke01&&&

