#define _BUZZER_C_
#include "general.h"


//			bPiTimes=2									bPiTimes=2									bPiTimes=2
//		+------+		+------+					+------+		+------+					+------+		+------+
//		|		|		|		|					|		|		|		|					|		|		|		|
//------+		+------+		+------------------+		+------+		+------------------+		+------+		+------------------+
//bOnTime bOffTime bOnTime bOffTime	bOffDelayTime		bOnTime	bOffTime	bOnTime		bOffDelayTime		bOnTime	bOffTime	bOnTime		bOffDelayTime
//
//		\-------------------- wTotalBuzzerOnTime--------------------------------------------------------------------------------------------/
//

//130119Ja01***
BYTE bOnTime=0;			//bOnTime is the times of ON during a cycle, one time is 25msec.
BYTE bOnTimeBuffer=0;	//bOnTimeBuffer to save the bOnTime, for setting bOnTime at the beginning of  next cycle. 
BYTE bOffTime=0;		//bOffTime is the times of OFF during a cycle, one time is 25msec.
BYTE bOffTimeBuffer=0;	//bOffTimeBuffer to save the bOffTime, for setting bOffTime at the beginning of  next cycle.
BYTE bOffDelayTime=0;	//bOffDelayTime is the time after ON/OFF , one time is 25msec.
BYTE bPiTimes=0;		//bPiTimes is the number of PI.
//BYTE bPiTimesBuffer=0;	//bPiTimes is the number of PI.	//130227Ja01
#define bPiTimesBuffer	4
BYTE bBuzzerStateMachine=0;	//With bBuzzerStateMachine to set the ON/OFF status.
WORD wTotalBuzzerOnTime=0;

#define PI_LOUD_HC_TIME	1200	//Only for PI_LOUD_HC time setting, it will be setted to 1200. (30s=1200*25ms) 

#if 0
void vInitialBuzzer(void)
{
	vBuzzerVoiceNormal();
	bOnTime = 0;			
	bOnTimeBuffer = 0;
	bOffTime = 0;	
	bOffTimeBuffer = 0;
	bPiTimes =1;
	bBuzzerStateMachine = 0;
	wTotalBuzzerOnTime = 0;
}
#endif
#if 0 //130424Ad04***
//With this function to enable the buzzer, normal or loudly. 
void vPWMBActive(void)    			     
{
	PWMB_ENABLE;
	PWMB_TIMER_ENABLE;
}

//With this function to disable the buzzer.
void vPWMBNonActive(void) 		     
{
	PWMB_DISABLE;
	PWMB_TIMER_DISABLE;
	//vBuzzerVoiceNormal();	//130408Ja01
}
#endif	//130424Ad04***

//With this function to set the parameter of the eight types buzzer output. 
//Every module can call this function with "vBuzzerOutput(buzzer_type)", buzzer type: from 1 to 8.
void vBuzzerOutput(BYTE bBuzzer_Type)
{
	bBuzzerStateMachine = 1;
	bOffDelayTime=0;
//	bPiTimesBuffer=0;

	switch(bBuzzer_Type)
		{
		default:
		case PI_OFF:
			vPWMBNonActive();
			bBuzzerStateMachine = 0;
			break;
		case PI:
			bOnTime = 4;		// 25ms*4=100ms=0.1s
			bOffTime = 0;
			bPiTimes =1;
			vBuzzerVoiceNormal();
			break;
		case PI_LOUD:
			bOnTime = 4;		// 25ms*4=100ms=0.1s
			bOffTime = 0;
			bPiTimes =1;
			vBuzzerVoiceLoud();
			break;
		case PI_LONG:
			bOnTime = 20;		// 25ms*20=500ms=0.5s
			bOffTime = 0;
			bPiTimes =1;
			vBuzzerVoiceNormal();
			break;
		case PI_PI:
			bOnTime = 2;		// 25ms*2=50ms=0.05s
			bOnTimeBuffer = 2;
			bOffTime = 2;		// 25ms*2=50ms=0.05s
			bOffTimeBuffer = 2;
			bPiTimes =2;
			vBuzzerVoiceNormal();
			break;
		case PI_PI_PI:
			bOnTime = 4;		// 25ms*4=100ms=0.1s
			bOnTimeBuffer = 4;
			bOffTime = 4;		// 25ms*4=100ms=0.1s
			bOffTimeBuffer = 4;
			bPiTimes =3;
			vBuzzerVoiceNormal();
			break;
		case PI_LOUD_HC:
			bOnTime = 4;		// 25ms*4=100ms=0.1s
			bOnTimeBuffer = 4;
			bOffTime = 2;		// 25ms*2=50ms=0.05s
			bOffTimeBuffer = 2;
			bPiTimes =4;
//			bPiTimesBuffer =4;	//130227Ja01
			bOffDelayTime = 20; // 25ms*20=500ms=0.5s
			wTotalBuzzerOnTime =PI_LOUD_HC_TIME;
			vBuzzerVoiceLoud();
			vIntWarningBuzzerStart(TRUE);	//130411le01
			break;
		case PI_LOUD_HD:
			bOnTime = 4;		// 25ms*4=100ms=0.1s
			bOnTimeBuffer = 4;
			bOffTime = 2;		// 25ms*2=50ms=0.05s
			bOffTimeBuffer = 2;
			bPiTimes =200;
			vBuzzerVoiceLoud();
			vIntWarningBuzzerStart(TRUE);	//130411le01
			break;
		case PI_LOUD_L:
			bOnTime = 4;		// 25ms*4=100ms=0.1s
			bOnTimeBuffer = 4;
			bOffTime = 2;		// 25ms*2=50ms=0.05s
			bOffTimeBuffer = 2;
			bPiTimes =4;
			vBuzzerVoiceLoud();
			break;
		}
}

//Put this function into 25msec timer task.
void vBuzzerTimer(void)
{
	//Only PI_LOUD_HC, the wTotalBuzzerOnTime is 1200, other buzzer output is 0.
	if(wTotalBuzzerOnTime > 0)		
		{
		wTotalBuzzerOnTime--;
		if(wTotalBuzzerOnTime==0)
			{		//Time is up.
			vPWMBNonActive();
			bBuzzerStateMachine = 0;
			vIntWarningBuzzerStart(FALSE);	//130411le01
			}
		}

	switch(bBuzzerStateMachine)
		{
		default:
			vPWMBNonActive();
		case 0:
			break;
		case 1:                          //On Time (The condition of on time cycle. bBuzzerStateMachine the default is 1)
			if(bOnTime > 0)
				{
				vPWMBActive();
				bOnTime--;
				}
			else 
				{
				vPWMBNonActive();
				bPiTimes--;
				if(bPiTimes==0)
					{
					if(bOffDelayTime==0)
						{
						bBuzzerStateMachine = 0;
						vIntWarningBuzzerStart(FALSE);	//130411le01
						break;
						}
					else
						{
						bOffTime=bOffDelayTime;
						bPiTimes=bPiTimesBuffer;       //130227Ja01
						}
					}
					
				if(bOffTime >0)
					{
					bOffTime--;
					bBuzzerStateMachine = 2;
					}
				else
					{
					bBuzzerStateMachine = 0;
					}
				}
			break;
		case 2:                          //Off Time (The condition of off time cycle )
			if(bOffTime > 0)
				{
				bOffTime--;
				}
			else
				{
				vPWMBActive();
				bOnTime = bOnTimeBuffer;         //With bOnTimeBuffer to set the bOnTime before next cycle
				bOffTime = bOffTimeBuffer;       //With bOffTimeBuffer to set the bOffTime before next cycle
				bOnTime--;					
				bBuzzerStateMachine = 1;
				}
			break;
		}
}
//130119Ja01&&&
