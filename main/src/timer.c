#define _TIMER_C_
#include "general.h"

#define TIEMR_25MS_CNT	(25)	//25*1ms=25ms
#define TIMER_1S_CNT	(40)	//40*25ms=1s
BYTE bTimerReach1ms;
BOOL fgTimerReach25ms;
BOOL fgTimerReach1s;
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
	TC3IF=0;
	bTimerReach1ms++;
//Please put 1ms function in here. If it need very exatc 1ms time./////////////////
	//vOscillateMotorTimer();
	vHorizontalMotorGoStep(bOscillateStep);
	//vLouverMotorTimer();
	vVerticalMotorGoStep(bLouverStep);
//	vIonMeasure();	//130221Ju01
	vPollingFG();	//130424Ke01
	
////////////////////////////////////////////////////////////////////////
	if(bCnt25ms)
		{
		bCnt25ms--;
		if(bCnt25ms == 0)
			{
			bCnt25ms = TIEMR_25MS_CNT;
			fgTimerReach25ms=TRUE;
//Please put 1ms function in here. If it need very exatc 25ms time./////////////////
			vBuzzerTimer();


			
////////////////////////////////////////////////////////////////////////
			if(bCnt1s)
				{
				bCnt1s--;
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


void vInitialTCC(void)
{

}

void vInitialTimer1(void)
{

}

void vInitialTimer2(void)
{
	//Used for Fan Motro FG feed-back.
	TC2_CLOCK_SOURCE_FM;
	TC2_SIGNAL_EDGE_FALL;
	TC2_MODE_TIMER;			//Timer counter mode
	TC2_CLOCK_SOURCE_TC2;		//External Clock enable.
	TC2_DATA_BUFFER_HIGH = 0;	
	TC2_DATA_BUFFER_LOW   = 0;	//Timer2 counter set 0.
}

//130114sh01***
// System Timer. Every 1ms interrupt once.
void vInitialTimer3(void)
{
	bTimerReach1ms = 0;
	fgTimerReach25ms=FALSE;//130114sh01
	fgTimerReach1s=FALSE;//130114sh01

	//bTimerReach1ms_bit = 0;
	bCnt1s = TIMER_1S_CNT;
	bCnt25ms = TIEMR_25MS_CNT;

	// Set timer3 interrupt interval as 1 ms(250 * 4us).
	CPUS = 1;		//CPU Oscillator Source Select->main-oscillator(Fm)
	TC3_CLOCK_SOURCE_FM;	//TC3 clock source select bit->Fm is used as Fc
	TC3CR = 0x08;	//Timer 3 Control Register->Timer/Counter 3 clock source select(4£gs)
	TC3_DUTY_BUFFER = 250;	//Timer 3 Duty Buffer Register
	TC3IF = 0;	//Timer 3 int flag
	TC3_INT_EN;	//Timer 3 int enable
	TC3_START;	//Timer 3 start
}

//Timer 1ms, run in mainloop().
void vTimer1ms(void)
{
	if(bTimerReach1ms==0)
		return;
	bTimerReach1ms--;
	//Put function below here.
//	vPCIWriteService();		// 130307lo01

	vIonMeasure();	//130221Ju01
	vCheckADCQueue();		//130308Li01
	vOscillateMotorTimer();
	vLouverMotorTimer();

	if(bI2CIntRetransferCount<I2C_INT_RETRANSFER_COUNT_MAX)//130418sh01***//if I2C INT low last for 30ms,then pull high the INT pin,after 5ms, pull low again
		{
		if(bI2CIntRetransferCount==I2C_INT_RETRANSFER_LOW_COUNT)
			{
			vOTPIntDis();
			}
		else if(bI2CIntRetransferCount==I2C_INT_RETRANSFER_LOW_COUNT+I2C_INT_RETRANSFER_HIGH_COUNT)
			{
			vOTPIntEn();
			bI2CIntRetransferCount=0;
			}
		bI2CIntRetransferCount++;
		}//130418sh01&&&

}

//Timer 25ms, run in mainloop().
void vTimer25ms(void)
{
	if(!fgTimerReach25ms)
		return;
	fgTimerReach25ms=FALSE;
	//Put function below here.
	vPCIWriteTimeAndCheckTime();
	vCheckPciUnit();
	vTemperatureAndHumidityTimer();
	vPollingCoverSwitch();	//130307Li01
	vDisplay7SegLedTimer();	// 130325jac01
}

//Timer 1second, run in mainloop().
void vTimer1s(void)
{
	if(!fgTimerReach1s)
		return;
	fgTimerReach1s=FALSE;
	//Put function below here.
	vIonGenerationJudgmentControl();	//130221Ju01
	vPCITimer1s();
	
	vIon1sTimer();	//130221Ju01
	vGetIonSampleOneTime();	//130309Ad01
	vGetIonSampleAtProuductLine();	//130309Ad01
	
	vWatchModeCheckTimer();	//130130Me01***
	vAutoFanChangeTimer10s();	//130418Ja01

	vSpecialFunctionModeTimer1S();
	vFanTimer1S();	// 130427jac02


}
//130114sh01&&&


