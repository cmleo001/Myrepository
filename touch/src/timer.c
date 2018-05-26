#define _TIMER_C_
#include "general.h"

#define TIEMR_25MS_CNT	(25)	//25*1ms=25ms
#define TIMER_1S_CNT	(40)	//40*25ms=1s
BOOL fgTimerReach1ms;					// 130315ja01
BOOL fgTimerReach25ms;
BOOL fgTimerReach1s;
BOOL fgTimerReach100ms;					// 130315ja01
BYTE bCnt1s=TIMER_1S_CNT;
BYTE bCnt25ms=TIEMR_25MS_CNT;

void vISR_TCC(void)
{
	TCIF=0;
	
}

void vISR_Timer1(void)
{
	TC1IF=0;
	
}

void vISR_Timer2(void)
{
	TC2IF=0;
	
}

//130114sh01***
// System Timer. Every 1ms interrupt once.
void vISR_Timer3(void)
{
	TC3IF = 0;
	//bTimerReach1ms++;					// 130315ja01
	fgTimerReach1ms=TRUE;					// 130315ja01
//Please put 1ms function in here. If it need very exatc 1ms time./////////////////


	
////////////////////////////////////////////////////////////////////////
	if(bCnt25ms)
		{
		bCnt25ms--;
		if(bCnt25ms == 0)
			{
			bCnt25ms = TIEMR_25MS_CNT;
			fgTimerReach25ms=TRUE;
//Please put 1ms function in here. If it need very exatc 25ms time./////////////////




			
////////////////////////////////////////////////////////////////////////
			if(bCnt1s)
				{
				bCnt1s--;
////////////////////////////////////////////////////////////////////////					// 130315ja01***
				if(bCnt1s%4==0)
					{
					fgTimerReach100ms=TRUE;
					}
//Please put 1ms function in here. If it need very exatc 100ms time./////////////////////
					








//////////////////////////////////////////////////////////////////////					// 130315ja01&&&
				if(bCnt1s == 0)
					{
					bCnt1s = TIMER_1S_CNT;
					fgTimerReach1s=TRUE;
//Please put 1ms function in here. If it need very exatc 1s time.///////////////////



					
////////////////////////////////////////////////////////////////////////
					}
				}
			}
		}
	RETI();
}
//130114sh01&&&

//Used for IR receive.
void vInitialTCC(void)
{
	// Set tcc interrupt period as 32us.
	TCC_CLOCK_SOURCE_FM;
	TCC_SIGNAL_SOURCE_INTERNAL;
	TCC_SIGNAL_EDGE_RISE;
	TCC_PRESCALER_EN;
	TCC_PRESCALER_1_256;
	TCC_INT_DIS;
}

void vInitialTimer1(void)
{

}

void vInitialTimer2(void)
{

}

//130114sh01***
// System Timer. Every 1ms interrupt once.
void vInitialTimer3(void)
{
	fgTimerReach1ms=FALSE;
	//bTimerReach1ms = 0;					// 130315ja01
	fgTimerReach25ms=FALSE;//130114sh01
	fgTimerReach1s=FALSE;//130114sh01
	fgTimerReach100ms=FALSE;					// 130315ja01
	//bTimerReach1ms_bit = 0;
	bCnt1s = TIMER_1S_CNT;
	bCnt25ms = TIEMR_25MS_CNT;

	// Set timer3 interrupt interval as 1 ms(250 * 4us).
	CPUS = 1;		//CPU Oscillator Source Select->main-oscillator(Fm)
	TC3_CLOCK_SOURCE_FM;	//TC3 clock source select bit->Fm is used as Fc
	TC3CR = 0x08;	//Timer 3 Control Register->Timer/Counter 3 clock source select(4μs)
	TC3_DUTY_BUFFER = 250;	//Timer 3 Duty Buffer Register
	TC3IF = 0;	//Timer 3 int flag
	TC3_INT_EN;	//Timer 3 int enable
	TC3_START;	//Timer 3 start
}

//Timer 1ms, run in mainloop().
void vTimer1ms(void)
{
	if(TCC>IR_MAX_TCC_COUNT)		//130412st01***
		{
		TCC=IR_MAX_TCC_COUNT;
		bIRStateMachine=0;
		}	//130412st01&&&

	if(fgTimerReach1ms==FALSE)					// 130315ja01
		return;
	fgTimerReach1ms=FALSE;					// 130315ja01
	//Put function below here.

	vDisplayRowShiftTimer();	// 1ms			//130119ja01

}

//Timer 100ms=0.1s , run in mainloop().
void vTimer100ms(void)
{
	if(!fgTimerReach100ms)					// 130315ja01***
		return;
	fgTimerReach100ms=FALSE;					// 130315ja01&&&

	vDisplay7SegLedTimer();	//130119ja01//130306ja03//130308ja04
	if(bPlugInACPowerTimeCount<250)		//130123gr03	
		{
		bPlugInACPowerTimeCount++;	//130123gr03	
		}
	vLEDDisplay();//130314gr01
	vDisplayLEDAirVolumeIndicationTimer();	//130308Me01

	if(bPowerOnOffTimerCount<250)//130420sh01***//power key is allowed only 0.5s past, since the last power key is executed.
		{
		bPowerOnOffTimerCount++;
		}//130420sh01&&&

}

//Timer 25ms, run in mainloop().
void vTimer25ms(void)
{
	//static BYTE bcount=0;	//for 100ms timer.					// 130315ja01
	if(!fgTimerReach25ms)
		return;
	fgTimerReach25ms=FALSE;

	//bcount++;					// 130315ja01***
	//if(bcount==4)
	//	{
	//	bcount=0;
	//	vTimer100ms();
	//	}					// 130315ja01&&&
	
	//Put function below here.
	vLightSensorTimer();
	//vDisplayBlinkTimer();		//25ms,不需要放在中斷中	//130119ja01//130306ja03//130308ja06

	//so3g2020_timer();//130123gr01
	//key_continue_press_timer();//130123gr01
	vTouchMultiKeyCount();//130123gr02
//	vProductModeTimer25ms();	//130123ma01	//130313ma02
	vDemoModeTimer();	//130124ma01

	vDigitalIndicationShowTimer();//130305Ke02

	if(bIRFineKeyTimerCount<200)	//130422le01***
		{
		bIRFineKeyTimerCount++;
		}	//130422le01&&&
}

//Timer 1second, run in mainloop().
void vTimer1s(void)
{
	static BYTE wOscillateShowTimeOutCount=OSCILLATE_MOTOR_CENTRAL_TIMEOUT_TIME;	//130417Ke01

	if(!fgTimerReach1s)
		return;
	fgTimerReach1s=FALSE;
	//Put function below here.
	vFilterCleanTimer();	//130122su01
	vOnOffTimer();	//130125Ti01

	//vIonModeTimer();	// 130129ja01
	vAutoRestartFunction1sTimer();	//130308le02
	//vMonitorModeTimer1s();	//130123ra01

	if(fgIsInMonitorMode())
		{
		if(bModeState==8)
			{
			vDisplay7SegShowHexNumOn(bLightSensorADCAverage);	//130327ra02
			}
		}

	vTouchICReadCommand(TOUCH_REGISTER_INTERFACE_CONFIGURATION_HIGH,TOUCH_REGISTER_INTERFACE_CONFIGURATION_LOW); //130326gr02 //130419gr01

	if(fgOscillateInitialProcess)	//130417Ke01***
		{
		wOscillateShowTimeOutCount--;
		if(wOscillateShowTimeOutCount==0)
			{
			wOscillateShowTimeOutCount=OSCILLATE_MOTOR_CENTRAL_TIMEOUT_TIME;
			fgOscillateInitialProcess=FALSE;	
			vDisplay7SegMessageClear();
			}
		}
	else	//if(fgIsInPowerOffMode())
		{
		wOscillateShowTimeOutCount=OSCILLATE_MOTOR_CENTRAL_TIMEOUT_TIME;
		}	//130417Ke01&&&

}
//130114sh01&&&


