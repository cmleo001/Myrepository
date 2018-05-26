#define _GPIO_C_
#include "general.h"

void vInitialGPIO(void)
{
	//All output pin
	vTubeLedOFF();
	PIN_TUBE_LED_HIGH_DRIVE;
	PIN_TUBE_LED_IO_OUTPUT;

	vRow1Disable();
	vRow2To5Disable();
	//vRow2Disable();
	//vRow3Disable();
	//vRow4Disable();
	//vRow5Disable();
	//vColumn1Disable();
	//vColumn2Disable();
	//vColumn3Disable();
	//vColumn4Disable();
	//vColumn5Disable();
	//vColumn6Disable();
	//vColumn7Disable();
	//vColumn8Disable();
	//PIN_ROW2_IO_OUTPUT;
	//PIN_ROW3_IO_OUTPUT;
	//PIN_ROW4_IO_OUTPUT;
	//PIN_ROW5_IO_OUTPUT;
	PIN_ROW1_IO_OUTPUT;
	vRow2To5Output();
	vLedColumnOutValue(LED_OFF);	//130314ja01
	PIN_COLUMN_IO_OUTPUT;

	//All input pin
	PIN_IR_AS_INT;
	PIN_IR_FALL_EDGE_INT;
	PIN_IR_INT_EN;

	PIN_OTP_INT_IO_INPUT;

	//PIN_BUSY_IO_INPUT;//130315sh01***
	vPinI2cBusyDisable()	;
	PIN_BUSY_IO_OUTPUT;//130315sh01&&&

	PIN_TOUCH_INT_IO_INPUT;
	
	PIN_LIGHT_IN_ALT_FUNC_EN;
}

//Polling OTP_INT pin. This pin is used to MainMCU notify TouchMCU something has happen.
//Then TouchMCU will read the MainMCU's information by I2C.
void vPollingOTP_INT(void)
{
	static BOOL fgLastStatusIsInt=FALSE;	//130322sh01		// 130417jac02
	BOOL fgOTP_INTStatus;
	BYTE bOTP_INTEvent = EVENT_OTP_INT_INTERRUPT;
	fgOTP_INTStatus=PIN_OTP_INT_READ;
	/*			// 130417jac02
	if(fgLastOTP_INT!=fgOTP_INTStatus)
		{
		if(fgOTP_INTStatus)
			{	 // 1-->no interrupt.
//			bOTP_INTEvent = EVENT_OTP_INT_INTERRUPT;
			}
		else	
			{	 // 0-->OTP_INT interrupt is happened.
			//vPutEventQueue(bOTP_INTEvent,0 ,0);
			vMainMCUInterruptRead();
			}
		fgLastOTP_INT=fgOTP_INTStatus;
		}
	*/			// 130417jac02***
	if(fgOTP_INTStatus==TRUE)
		{
		fgLastStatusIsInt=FALSE;
		}
	else
		{
		if(fgLastStatusIsInt==FALSE)
			{
			vMainMCUInterruptRead();
			fgLastStatusIsInt=TRUE;
			}
		}		// 130417jac02&&&
}

#if 0//130315sh01***
//Polling BUSY pin. This pin is used to MainMCU notify TouchMCU it's busy.
//Please don't send the I2C command to MainMCU by I2C.
void vPollingBusy(void)
{
	static BOOL fgLastBusy=0;
	BOOL fgBusyStatus;
	BYTE bBusyEvent;
	fgBusyStatus=PIN_BUSY_READ;
	if(fgLastBusy!=fgBusyStatus)
		{
		if(fgBusyStatus)
			{	 // 1-->not busy.
			bBusyEvent = EVENT_MAIN_MCU_NOT_BUSY;
			}
		else	
			{	 // 0-->Main MCU is busy.
			bBusyEvent = EVENT_MAIN_MCU_BUSY;
			}
			vPutEventQueue(bBusyEvent,0 ,0);
		fgLastBusy=fgBusyStatus;
		}
}
#endif//130315sh01&&&
//Polling Touch interrupt pin. 
void vPollingTouchINT(void)
{
	static BOOL fgLastTouchStatusIsINT=0;		// 130417jac02
	BOOL fgTouchINTStatus;
	fgTouchINTStatus=PIN_TOUCH_INT_READ; //130305gr01
	/*			// 130417jac02
	if(fgLastTouchINT!=fgTouchINTStatus)
		{
		if(fgTouchINTStatus==FALSE)
			{	 // 0-->touch interrupt.
			//vPutEventQueue(EVENT_TOUCH_INTERRUPT,0 ,0);
			if(fgTouchInitial)//130307gr01***
				{
				return;
				}//130307gr01&&&
			vEventTouchSensorInterrupt();
			}
		fgLastTouchINT=fgTouchINTStatus;
		}
	*/			// 130417jac02***
	if(fgTouchINTStatus==TRUE)
		{
		fgLastTouchStatusIsINT=FALSE;
		}
	else
		{
		if(fgLastTouchStatusIsINT==FALSE)
			{
			if(fgTouchInitial)
				{
				return;
				}
			vEventTouchSensorInterrupt();
			fgLastTouchStatusIsINT=TRUE;
			}
		}		// 130417jac02&&&
}

