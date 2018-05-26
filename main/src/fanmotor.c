#define _FAN_MOTOR_C_
#include "general.h"

#ifdef FAN_MOTOR_FUNCTION
//Fan Motor use the PWMA to control.

//130119Ke01***
//#define FAN_PWM_PERIOD_25K	//130309Ke01
#define FAN_PWM_PERIOD_16K	//130309Ke01

#ifdef FAN_PWM_PERIOD_25K
//Set period [T=(PRDX+1)*(1/Fosc) *(TMRX 預分頻比值)=(159+1)*1/8*2=40us], 25KHz
#define FAN_MOTOR_PWM_PERIOD							159 
#elif defined(FAN_PWM_PERIOD_16K)
//Set period [T=(PRDX+1)*(1/Fosc) *(TMRX 預分頻比值)=(249+1)*1/8*2=62.5us], 16KHz
#define FAN_MOTOR_PWM_PERIOD							249	//130309Ke01
#endif

#define SET_HIGH_LOW_MODE				33		//Decide high and low level on user

#define TABLE_VALUE_MAX 					160						//130411Ke02  //130503Ju01	
#define TABLE_VALUE_MIN					20			//Table rang  is 12~100 in this case		//130411Ke02

#define PWM_OUTPUT_CONTIUNS_TIME		3			//PWM consecutive output time is 3 seconds.
#define LOW_LEVEL_DELAY_TIME			3			//Adjust speed delay time of low speed mode is 3 seconds.
#define HIGH_LEVEL_DELAY_TIME			1			//Adjust speed delay time of high speed mode is 1 second.

#define FG_ERROR_TIME	15	// 15 second

//Set fan valume table, valume can be seted by PWM or AD and so on.
//130309Ke01***
#ifdef FAN_PWM_PERIOD_25K
const BYTE bSetFanTable[AIR_VOLUME_MAX]=			//130309Ke02	
{
	14,
	15,
	16,
	17,		//Air Volume Level 1
	18,
	19,
	20,
	22,		//Air Volume Level 2
	23,
	25,
	26,
	27,		//Air Volume Level 3
	29,
	31,
	32,
	34,		//Air Volume Level 4
	35,
	36,
	38,
	40,		//Air Volume Level 5
	41,
	42,
	44,
	46,		//Air Volume Level 6
	47,
	49,
	51,
	53,		//Air Volume Level 7
	55,
	57,
	59,
	61,		//Air Volume Level 8
	90		//Air Volume Level 9
}
#endif

#ifdef FAN_PWM_PERIOD_16K
#if 0
const BYTE bSetFanTable[AIR_VOLUME_MAX]=		//130309Ke02
{	
	22,//L1
	24,//L2
	26,//L3
	28,//L4-----Air Volume Level 1
	30,//L5
	32,//L6
	34,//L7
	36,//L8-----Air Volume Level 2
	38,//L9
	40,//L10
	42,//L11
	45,//L12-----Air Volume Level 3
	47,//L13
	49,//L14
	51,//L15
	54,//L16-----Air Volume Level 4
	56,//L17
	58,//L18
	61,//L19
	64,//L20-----Air Volume Level 5
	67,//L21
	69,//L22
	72,//L23
	74,//L24-----Air Volume Level 6
	77,//L25
	80,//L26
	83,//L27
	86,//L28-----Air Volume Level 7
	88,//L29
	92,//L30
	95,//L31
	98,//L32-----Air Volume Level 8
	137//L33----Air Volume Level 9
	};
#endif
//130309Ke01&&&
const BYTE bSetFanTable[AIR_VOLUME_MAX]=		//130427Ju01
{	
	22,//L1
	24,//L2
	26,//L3
	28,//L4-----Air Volume Level 1
	29,//L5
	31,//L6
	33,//L7
	35,//L8-----Air Volume Level 2
	37,//L9
	39,//L10
	41,//L11
	43,//L12-----Air Volume Level 3
	46,//L13
	48,//L14
	50,//L15
	52,//L16-----Air Volume Level 4
	55,//L17
	57,//L18
	59,//L19
	62,//L20-----Air Volume Level 5
	64,//L21
	67,//L22
	70,//L23
	72,//L24-----Air Volume Level 6
	75,//L25
	78,//L26
	81,//L27
	84,//L28-----Air Volume Level 7
	86,//L29
	90,//L30
	93,//L31
	96,//L32-----Air Volume Level 8
	135//L33----Air Volume Level 9	//130503Ju01
	};
//130427Ju01&&&
#endif

//This table is pulse number of 1 second  by time2 and used adjust speed.
//	number of rotations [rpm] = ( number of pulse / 1 second) ÷ 1[sec] × 60[sec] ÷ 6[ number of pulse / 1 rotation ]
//							 = ( number of pulse / 1 second ) × 10
//     For simply ,we used rpm/10 deputy  rpm.
const BYTE bFanSpeedSpecTable[AIR_VOLUME_MAX]=		//130309Ke02
	{
	43,		// 430 rpm
	46,		// 460 rpm
	50,
	53,
	56,
	60,
	63,
	66,
	69,
	73,
	76,
	79,
	83,
	86,
	89,
	93,
	96,
	99,
	102,
	106,
	109,
	112,
	116,
	119,
	122,
	126,
	129,
	132,
	135,
	139,
	142,
	145,		// 1450 rpm
	180		// 1800 rpm
	};

 BYTE bFanSampleIntervalTime=1; 	// Fan sample interval time
 BYTE bFgErrorCount=0;				//FG pin feedback counter
 BYTE bFanSetRotationSpeedValue;	//Fan current set  value. Rotation speed.
 BYTE bFanSampleValue=0;			//Fan sample value through FG pin
 BYTE bCurrentSetValue=0;			//Fan current PWM value
 #ifdef FAN_AUTO_ADJUST_EVERY_10MIN		// 130427jac02***
#define FAN_10MIN_COUNT		600
#define FAN_SPEED_UP_10MIN_COUNT		10
#define FAN_3SEC_COUNT		3
#define FAN_6SEC_COUNT		6
WORD wFan10MinTimer=FAN_10MIN_COUNT;
BYTE bFan6SecTimer=FAN_3SEC_COUNT;
#endif		// 130427jac02&&&
 BYTE bFanSampleGapTimeCount=0;	//Fan speed sample gap time
 BOOL fgFanPowerOn=FALSE;			//FanPowerflag
 BOOL fgFirstValueSet=FALSE;			//Set Fan volume first

void vInitialPWMA(void)
{
	//Used for Fan Motro control.
	PWMA_ENABLE;
	PWMA_PRESCALER_1_2;
	PWMA_CLOCK_SOURCE_FM;	//130227a01Ke
	vSetFanMotorPeriod(FAN_MOTOR_PWM_PERIOD);		//Set fan inital pwm  period.
	vSetFanMotorHighDuty(bSetFanTable[3]);	//Set fan inital volume is Air Volume Level 1.	
}


void vFanPower(BYTE fgPowerOn)
{
	if(fgPowerOn)
		{
		fgFanPowerOn=TRUE;
		PWMA_ENABLE;
		PWMA_TIMER_ENABLE;		//130227a01Ke		
		}
	else
		{
		fgFanPowerOn=FALSE;
		PWMA_DISABLE;
		PWMA_TIMER_DISABLE;		//130227a01Ke	
		PIN_FAN_MOTOR_OUT_LOW; //130325a01Ke
		}
}

void vFanVolumeAutoAdjust(void)
{
#ifdef	FAN_AUTO_ADJUST_EVERY_10MIN	// 130427jac02***
#else
	if(fgFirstValueSet)
		{
		fgFirstValueSet=FALSE;
		return;
		}
#endif										// 130427jac01&&&
	//if current value is lower than  feedback value	
	if(bFanSetRotationSpeedValue>bFanSampleValue)	//130309Ke03
		{
		if(bFanSetRotationSpeedValue>(bFanSampleValue+9))		// 130427jac01***
			{
			//bCurrentSetValue=bCurrentSetValue + 2;	//speed up
			bCurrentSetValue=bCurrentSetValue + 4;//130503Ju01
			}
		else
			{
			bCurrentSetValue=bCurrentSetValue + 1;	//speed up
			}
		}

	//if current value is higher than  feedback value
	if(bFanSetRotationSpeedValue<bFanSampleValue)	//130309Ke03
		{
		if(bFanSetRotationSpeedValue<(bFanSampleValue-9))
			{
			//bCurrentSetValue=bCurrentSetValue - 2;	//speed up
			bCurrentSetValue=bCurrentSetValue - 4;//130503Ju01
			}
		else
			{
			bCurrentSetValue=bCurrentSetValue - 1;	//speed down		// 130427jac01&&&
			}
		}
	
	//Table rang  is 12~100 in this case.
	if(bCurrentSetValue>=TABLE_VALUE_MAX)
		{
		bCurrentSetValue=TABLE_VALUE_MAX;
		}
	else if(bCurrentSetValue<=TABLE_VALUE_MIN)
		{
		bCurrentSetValue=TABLE_VALUE_MIN;
		}	

	vSetFanMotorHighDuty(bCurrentSetValue);
}

// ********************************************************************
// Function : 	  void vFanFGTimer(void)	
// Description : FG(Pin56) detected and turn speed with feedback value. Put it into 1 second time.
// Parameter : None
// Return    :    None
// ********************************************************************
#ifdef FAN_AUTO_ADJUST_EVERY_10MIN
void vFanTimer1S(void)		// 130427jac02***	
{
	if(fgAbnormalMode==TRUE)//130424Ke02***
		{
		return;
		}//130424Ke02&&&
	//If the fan feed-back is too slow than AirVolume1/2, we think it's error.

	if(fgFanPowerOn==TRUE)
		{
		if(TC2_DATA_BUFFER_LOW>(bFanSpeedSpecTable[0]/2))
			{
			bFgErrorCount=0;
			}
		else	
			{
			if(bFgErrorCount>=FG_ERROR_TIME)//130309Ke04
				{
				vIntMainMCUError(ERROR_FAN_MOTOR_ROTATION,TRUE);	//130309Ke06	//130322ke01	//130411Ke01
				bFgErrorCount=0;
				}
			bFgErrorCount++;
			TC2_DATA_BUFFER_LOW=0;
			return;
			}
		if(bAirVolume==AIR_VOLUME_MAX)
			{
			if(bFan6SecTimer>FAN_3SEC_COUNT)
				{
				bFan6SecTimer--;
				TC2_DATA_BUFFER_LOW=0;
				return;
				}
			}
		else
			{
			if(bFan6SecTimer!=0)
				{
				if(bFan6SecTimer>FAN_3SEC_COUNT)
					{
					TC2_DATA_BUFFER_LOW=0;
					bFan6SecTimer--;
					return;
					}
				else
					{
					bFan6SecTimer--;
					}
				}
			else
				{
				if(wFan10MinTimer>0)
					{
					wFan10MinTimer--;
					}
				else
					{
					wFan10MinTimer=FAN_10MIN_COUNT;
					if(fgIsInSpeedUpMode())
						{
						wFan10MinTimer=FAN_SPEED_UP_10MIN_COUNT;
						}
					bFan6SecTimer=FAN_3SEC_COUNT;
					}
				TC2_DATA_BUFFER_LOW=0;
				return;
				}
			}
		bFanSampleValue=TC2_DATA_BUFFER_LOW;		//Sample falling edge number 
		TC2_DATA_BUFFER_LOW=0;
		//It has a feedback value, FG had  been detected,adjust PWM value.
		vFanVolumeAutoAdjust();
		}
	else
		{
		bFgErrorCount=0;
		}
}
#else
void vFanTimer1S(void)			
{
	if(fgAbnormalMode==TRUE)//130424Ke02***
		{
		return;
		}//130424Ke02&&&

	if(fgFanPowerOn==TRUE)
		{
		bFanSampleValue=TC2_DATA_BUFFER_LOW;		//Sample falling edge number 
		TC2_DATA_BUFFER_LOW=0;

		//It has a feedback value, FG had  been detected,adjust PWM value.
		//If the fan feed-back is too slow than AirVolume1/2, we think it's error.
		if(bFanSampleValue>(bFanSpeedSpecTable[0]/2))
			{
			bFanSampleGapTimeCount--;			
			if(bFanSampleGapTimeCount==0)
				{
				bFanSampleGapTimeCount=bFanSampleIntervalTime;
				vFanVolumeAutoAdjust();
				}
			bFgErrorCount=0;
			}
		//When FG don't detected for 15 consecutive seconds,fan power off
		else	
			{
			bFgErrorCount++;
			if(bFgErrorCount>=FG_ERROR_TIME)//130309Ke04
				{
				vIntMainMCUError(ERROR_FAN_MOTOR_ROTATION,TRUE);	//130309Ke06	//130322ke01	//130411Ke01
				//vPutEventQueue(EVENT_IR, IR_POWER, 0);//130309Ke06
				bFgErrorCount=0;
				}
			}
		}
	else          //130427Ju01***
		{
		bFgErrorCount=0;
		}
	          //130427Ju01&&&
}
#endif	// 130427jac02&&&

// ********************************************************************
// Function : 	  void vFanVolumeSet(void)	
// Description : Fan volume set and adjust.         
// Parameter : value of adjust fan volume by user. (1~33)
// Return    :    None
// ********************************************************************
void vFanVolumeSet(BYTE value)
{
//Set Fan Volume value
	if(value<=AIR_VOLUME_MAX)	//130309Ke02
		{	
		bFanSetRotationSpeedValue=bFanSpeedSpecTable[value - 1];
		bCurrentSetValue=bSetFanTable[value - 1];
		vSetFanMotorHighDuty(bCurrentSetValue);	
		}
	
//Adjudge set value is high level or low level,and set .
#ifdef FAN_AUTO_ADJUST_EVERY_10MIN		// 130427jac02***
		wFan10MinTimer=FAN_10MIN_COUNT;
		if(fgIsInSpeedUpMode())
			{
			wFan10MinTimer=FAN_SPEED_UP_10MIN_COUNT;
			}
		bFan6SecTimer=FAN_6SEC_COUNT;
#else
	if(value==SET_HIGH_LOW_MODE)
		{
		bFanSampleIntervalTime=HIGH_LEVEL_DELAY_TIME;
		}
	else
		{
		bFanSampleIntervalTime=LOW_LEVEL_DELAY_TIME;
		}

	fgFirstValueSet=TRUE;
//Set Fan sample delay time,if first set fan value,adjust it after output consecutive 3 seconds,or adjust it depend on sample delay time.
	//bFanSetRotationSpeedValue=bFanSetRotationSpeedValue*bFanSampleIntervalTime;//130309Ke03

//bFanSampleValue=bFallEdgeNumber*TimerCount(high is 1,low is 3),so bFanSetRotationSpeedValue will be the same as bFanSampleValue.
	bFanSampleGapTimeCount=PWM_OUTPUT_CONTIUNS_TIME;
#endif					// 130427jac02&&&

}


//130119Ke01&&&
#endif



