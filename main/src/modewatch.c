#define _MODE_WATCH_C_
#include "general.h"

#ifdef WATCH_MODE_FUNCTION

//130130Me01***
#define	TEMP_26	26
#define	TEMP_25	25
#define	TEMP_27	27
#define	TEMP_28	28

#define	TEMP_29	29
#define	TEMP_30	30
#define	TEMP_31	31
#define	TEMP_32	32

#define	HUM_65		65
#define	HUM_40		40

WORD	wWatchModeCheckTimercnt;	//unit:1s

BYTE bLastWatchZone=ZONE_MAX;	//record the last Zone	//130504Me01
static BYTE bZoneCount=0;		//If the same zone, count +1
static BYTE bWatchModeAutoFanStatus _AT_0X7A = AUTO_FAN_NORMAL;		//130418Ja01
static BYTE bAdjustAutoFanVolume _AT_0X7B = AUTO_FAN_NORMAL;		//130418Ja01
static BYTE bAutoFanChangeTimercnt  = 0;							//130418Ja01
BYTE bAdjustAutoFanVolumeRem = 0xFF;	//Remember the adjust value when (31 jump to 32) or (2 jump to 1).	//130427Ja01



#define WATCH_MODE_ZONE_COUNT_FOR_SOUND 6
//130416Me01***
const BYTE bDangerZoneTable[]=
{
	5,44,//{humidity,temperature}
	7,43,
	12,42,
	17,41,
	25,40,
	33,39,
	40,38,
	45,37,
	52,36,
	55,35,
	60,34,
	64,33,
	68,32,
	78,31,
	83,30,
	88,29,
	98,28,
	0xff,0xff
};

const BYTE bPrecautionZoneTable[]=
{
	5,40,//{humidity,temperature}
	7,39,
	12,38,
	17,37,
	30,35,
	40,34,
	45,33,
	50,32,
	60,31,
	64,30,
	68,29,
	73,28,
	83,27,
	88,26,
	98,25,
	0xff,0xff
};

const BYTE bCautionZoneTable[]=
{
	5,36,//{humidity,temperature}
	10,35,
	15,34,
	19,33,
	28,32,
	38,31,
	44,30,
	50,29,
	55,28,
	60,27,
	68,26,
	73,25,
	83,24,
	88,23,
	98,22,
	0xff,0xff
};

const BYTE bVirusZoneTable[]=
{
	10,35,	//{humidity,temperature}
	15,34,
	16,33,
	17,32,
	18,31,
	19,30,
	21,29,
	22,28,
	23,27,
	26,26,
	28,25,
	29,24,
	34,23,
	36,22,
	38,21,
	42,20,
	45,19,
	48,18,
	51,17,
	54,16,
	58,15,
	61,14,
	64,13,
	66,12,
	70,11,
	74,10,
	79,9,
	84,8,
	90,7,
	96,6,
	100,5,
	0xff,0xff
};
//130416Me01&&&
//const BYTE *bJudgeZoneTable[]=
//{
//	&bVirusZoneTable[0][0],
//	&bCautionZoneTable[0][0],
//	&bPrecautionZoneTable[0][0],
//	&bDangerZoneTable[0][0]
//};

/*	//130418Ja01&&&
void vAirVolumeControl(void)
{	
	if(fgIsInPowerOnMode())
		{
		//i2c receive bIonMode
		switch(bIonMode)
			{
			case ION_MANUAL:								//fan volume level fine set
				if(	((bHumidity>HUM_65)&&(bTemperature>TEMP_29))||
					((bHumidity<HUM_40)&&(bTemperature>TEMP_31))||
					((HUM_40<bHumidity<HUM_65)&&(bTemperature>TEMP_30)))
						{
						//vFanVolumeAdd4();
						bAirVolume+=AIR_NORMAL_CONTROL_GAP;
						if(bAirVolume>=AIR_VOLUME_ION_MAX)
							bAirVolume=AIR_VOLUME_ION_MAX;
						}
				else	if(((bHumidity>HUM_65)&&(bTemperature<TEMP_26))||
						((bHumidity<HUM_40)&&(bTemperature<TEMP_28))||
						((HUM_40<bHumidity<HUM_65)&&(bTemperature<TEMP_27)))
						{
						//vFanVolumeMinus4();
						if(bAirVolume<(AIR_NORMAL_CONTROL_GAP+1))
							{
							bAirVolume=AIR_VOLUME_MIN;
							}
						else
							{
							bAirVolume-=AIR_NORMAL_CONTROL_GAP;
							}
 						}	
 				vFanVolumeSet(bAirVolume);
				break;
			case ION_PLASMA_CLUSTER_SHOWER:
				vFanVolumeSet(AIR_VOLUME_MAX);
				break;
			case ION_CLOTHING_DEODORANT:
				vFanVolumeSet(AIR_VOLUME_ION_MAX);
				break;
			default:
				break;
			}
		}
	else if(fgIsInPowerOffMode())
		{
		vFanVolumeSet(AIR_VOLUME_MIN);	
		}
}*/	//130418Ja01&&&

//130418Ja01&&&
void vAutoFanZoneJudge(void)
{	
	if(fgIsInSpeedUpMode() && wWatchModeCheckTimercnt > 60)
		return;
	
	if(wWatchModeCheckTimercnt > 600)
		return;		
	
	//if(fgIsInIonMode())	//130504Ja01
		//{
		//return;
		//}
	
	if(fgIsInWatchMode()&& wWatchModeCheckTimercnt) //130422Ja01
		{
		//i2c receive bIonMode
		//if(fgIsNotIonMode())	//130504Ja01
			{	//fan volume level fine set
			if(	((bHumidity>HUM_65)&&(bTemperature>TEMP_29))||
				((bHumidity<HUM_40)&&(bTemperature>TEMP_31))||
				((HUM_40<bHumidity<HUM_65)&&(bTemperature>TEMP_30)))
				{
				//vFanVolumeAdd4();
				if(bWatchModeAutoFanStatus != AUTO_FAN_PLUS)
					{
					bWatchModeAutoFanStatus = AUTO_FAN_PLUS;
					goto SET_TIMER_COUNT_IS_0;
					}
				}
			else	if(((bHumidity>HUM_65)&&(bTemperature<TEMP_26))||
				((bHumidity<HUM_40)&&(bTemperature<TEMP_28))||
				((HUM_40<bHumidity<HUM_65)&&(bTemperature<TEMP_27)))
				{
				//vFanVolumeMinus4();
				if(bWatchModeAutoFanStatus != AUTO_FAN_MINUS)
					{
					bWatchModeAutoFanStatus = AUTO_FAN_MINUS;
					goto SET_TIMER_COUNT_IS_0;
					}
				}
			else if(bWatchModeAutoFanStatus != AUTO_FAN_NORMAL)
				{
				//Normal
				bWatchModeAutoFanStatus = AUTO_FAN_NORMAL;
				goto SET_TIMER_COUNT_IS_0;
				}
			}
		}
	return;
SET_TIMER_COUNT_IS_0:		
	bAutoFanChangeTimercnt = 0;

}//130418Ja01&&&

#define AUTO_FAN_CONTROL_TIME		9	// 9,8,7,6,5,4,3,2,1,0 total 10s.
void vAutoFanChangeTimer10s(void)		//130418Ja01&&&
{
	if(bAdjustAutoFanVolume == bWatchModeAutoFanStatus)
		{
		return;
		}	
	if(bWatchZone == ZONE_DANGER)
		{
		return;
		}
	//130427Ja01&&&
	if(fgIsInPowerOffMode())	//130422Ja01&&&
		{
		bAdjustAutoFanVolume = bWatchModeAutoFanStatus;
		bAutoFanChangeTimercnt = 0;
		goto SEND_AUTO_FAN_STATUS;
		}	//130422Ja01&&&	
	if(bAutoFanChangeTimercnt == 0)
		{
		if(bAdjustAutoFanVolumeRem != 0xFF)
			{
			if(bWatchModeAutoFanStatus <= bAdjustAutoFanVolumeRem)	
				{
				bAdjustAutoFanVolume = bAdjustAutoFanVolumeRem;
				bAdjustAutoFanVolumeRem = 0xFF;
				}
			else
				{
				bAdjustAutoFanVolume = bWatchModeAutoFanStatus;
				bAdjustAutoFanVolumeRem = 0xFF;
				}
			goto SEND_AUTO_FAN_STATUS;
			}		
		if(bAdjustAutoFanVolume > bWatchModeAutoFanStatus)
			{
			if(bAirVolume <= (AIR_VOLUME_MIN+1))	//130422Ja01&&&
				{
				bAdjustAutoFanVolumeRem  = bAdjustAutoFanVolume;	//130427Ja01
				bAdjustAutoFanVolume = bWatchModeAutoFanStatus;
				}	//130422Ja01&&&
			else	//130427Ja01
				{
				bAdjustAutoFanVolume --;
				bAdjustAutoFanVolumeRem = 0xFF;				
				}
			}
		else //if(bAdjustAutoFanVolume < bWatchModeAutoFanStatus)
			{
			if(bAirVolume >= (AIR_VOLUME_WATCH_MAX-1))	//130422Ja01&&&
				{
				bAdjustAutoFanVolumeRem  = bAdjustAutoFanVolume;	//130427Ja01
				bAdjustAutoFanVolume = bWatchModeAutoFanStatus;
				}	//130422Ja01&&&
			else	//130427Ja01
				{					
				bAdjustAutoFanVolume ++;
				bAdjustAutoFanVolumeRem = 0xFF;
				}
			}
		goto SEND_AUTO_FAN_STATUS;
		}
	bAutoFanChangeTimercnt --;
	return;
	
SEND_AUTO_FAN_STATUS:
	bAutoFanChangeTimercnt = AUTO_FAN_CONTROL_TIME;
	vIntWatchAutoFanStatusChange(0,bAdjustAutoFanVolume);
}//130418Ja01&&&		//130427Ja01&&&	

void vVirusZonecontrol(void)
{
	//vAirVolumeControl();		130418Ja01

	if(bZoneCount==0)
		{
		if(bWatchMode==WATCH_MODE_WITH_BUZZER)			//first virus zone  buzzer sound
			{
			//pi(loud )	0.6S
			vBuzzerOutput(PI_LOUD_L);
			}
		}
}

void vDangerZonecontrol(void)
{
	if(bLastWatchZone!=ZONE_DANGER)		//130503Me02***
		{
		if(fgIsInPowerOnMode()&&fgIsNotIonMode())	//130503Me01
			{
			//vFanVolumeSet(AIR_VOLUME_MAX);
			bAirVolume=AIR_VOLUME_MAX;
			}
		if(fgIsInPowerOffMode())
			{
			//vFanVolumeSet(AIR_VOLUME_MIN);
			bAirVolume=AIR_VOLUME_MIN;
			}
		vFanVolumeSet(bAirVolume);
		}	//130503Me02&&&

	if(bZoneCount==0)
		{
		if(bWatchMode==WATCH_MODE_WITH_BUZZER)			//first virus zone  buzzer sound
			{
			//pi(loud hd)	 30S
			vBuzzerOutput(PI_LOUD_HD);
			}
		}
}

void vPrecautionZonecontrol(void)
{
	//vAirVolumeControl();		130418Ja01

	if(bZoneCount==0)
		{
		if(bWatchMode==WATCH_MODE_WITH_BUZZER)			//first virus zone  buzzer sound
			{
			//pi(loud hC)	 30S
			vBuzzerOutput(PI_LOUD_HC);
			}
		}
}

/*		//130418Ja01&&&
void vCautionZonecontrol(void)
{
	vAirVolumeControl();
}

void vNormalZonecontrol(void)
{
	vAirVolumeControl();
}
*/		//130418Ja01&&&

void vWatchZoneExecute(BYTE bZone)
{
	if(fgWatchZoneExecute==FALSE)
		return;
	fgWatchZoneExecute=FALSE;

	if(bLastWatchZone!=bZone)
		{
		bZoneCount=0;
		//i2c send the watch zone to touch mcu
		vIntWatchZoneStatusChange(bZone);
		}
	else
		{
		bZoneCount++;
		bZoneCount%=WATCH_MODE_ZONE_COUNT_FOR_SOUND;	//6 times sound one time.
		}
	/*
	switch(bZone)
		{
		//default:
			//bLastWatchZone=ZONE_NORMAL;
			//break;
		case ZONE_NORMAL:			//130418Ja01
			vNormalZonecontrol();		
			break;					//130418Ja01
		case ZONE_PRECAUTION:
			vPrecautionZonecontrol();
			break;
		case ZONE_CAUTION:		//130418Ja01
			vCautionZonecontrol();
			break;				//130418Ja01
		case ZONE_DANGER:
			vDangerZonecontrol();
			break;
		case ZONE_VIRUS:
			vVirusZonecontrol();
			break;
		}*/	//130425Me02***
	if(bWatchZone==ZONE_PRECAUTION)
		{
		vPrecautionZonecontrol();
		}
	else	if(bWatchZone==ZONE_DANGER)
		{
		vDangerZonecontrol();
		}
	else	if(bWatchZone==ZONE_VIRUS)
		{
		vVirusZonecontrol();
		}	//130425Me02&&&
	bLastWatchZone=bZone;		//130503Me02
}

void vWatchZoneJudge(void)		//130327Me01***
{
 	BYTE bWatchZoneIndex=0; 
	BYTE j=0;
 	BYTE bjudgeTemperature=0;
	BYTE bjudgeHumidity=0;
 	for(bWatchZoneIndex=0;bWatchZoneIndex<ZONE_DANGER;bWatchZoneIndex++)//need judge 4 table
		{
		j=0;
		while(1)
			{
			if(bWatchZoneIndex==0)
				{
				bjudgeHumidity=bVirusZoneTable[j];		//130416Me01***
				bjudgeTemperature=bVirusZoneTable[j+1];
				}
			else if(bWatchZoneIndex==1)
				{
				bjudgeHumidity=bCautionZoneTable[j];
				bjudgeTemperature=bCautionZoneTable[j+1];		
				}
			else if(bWatchZoneIndex==2)
				{
				bjudgeHumidity=bPrecautionZoneTable[j];
				bjudgeTemperature=bPrecautionZoneTable[j+1];		
				}
			else if(bWatchZoneIndex==3)
				{
				bjudgeHumidity=bDangerZoneTable[j];
				bjudgeTemperature=bDangerZoneTable[j+1];			//130416Me01&&&
				}
			if(bjudgeHumidity==0xff)
				{
				break;
				}

			if((bjudgeHumidity>bHumidity)&&(bjudgeTemperature>=bTemperature))
				{
				bWatchZone=bWatchZoneIndex;
				fgWatchZoneExecute=TRUE;
				//vWatchZoneExecute(fgWatchZoneExecute);
				return;
				}
				
			j+=2;		//130416Me01
			}
		}
	//if(bWatchZone==ZONE_DANGER)//130401Me04***
		//{
		bWatchZone=ZONE_DANGER;
		fgWatchZoneExecute=TRUE;
		//vWatchZoneExecute(fgWatchZoneExecute);
		//}//130401Me04&&&
}
//130327Me01&&&
//put in 1s timer
void vWatchModeCheckTimer(void)
{	
	if(fgAbnormalMode==TRUE)		//130423vi01***
		{
		return;
		}						//130423vi01&&&
		
	if(fgIsInWatchMode())	//It's in watch mode.	
		{
		if(wWatchModeCheckTimercnt>0)
			{
			wWatchModeCheckTimercnt--;
			}
		
		if(wWatchModeCheckTimercnt==0)
			{
			vWatchZoneJudge();

			if(fgIsInSpeedUpMode())
				{
				wWatchModeCheckTimercnt=60;		//60*1s=1min
				}
			else
				{
				wWatchModeCheckTimercnt=600;		//600*1s=10min
				}
			}
		}
	//else	//130418Ja01&&&   //130422Ja01
		//{
		//bWatchModeAutoFanStatus = AUTO_FAN_NORMAL;
		//bAdjustAutoFanVolume = AUTO_FAN_NORMAL;
		//}	//130418Ja01&&&	//130422Ja01
}


void vWatchModeKey(void)
{
	if(fgIsNotWatchMode())		//130417Me01***
		{
		//bWatchMode=ZONE_NORMAL;	//130424Ja01//130426jac02
		bWatchZone=ZONE_NORMAL;	//130426jac02
		bLastWatchZone=ZONE_MAX;	
		bWatchModeAutoFanStatus = AUTO_FAN_NORMAL;		//130422Ja01
		bAdjustAutoFanVolume = AUTO_FAN_NORMAL;			//130422Ja01
		bAutoFanChangeTimercnt = 0;				//130422Ja01
		}		//130417Me01&&&
	if(bWatchMode==WATCH_MODE_WITH_BUZZER)
		{
		if(fgIsInSpeedUpMode())				//speed up mode
			{
			wWatchModeCheckTimercnt= 120;	//120*1s=2min	
			}
		else
			{
			wWatchModeCheckTimercnt= 1200;	//1200*1s=20min
			}
		}
	//130408Me01***
	if( fgIsInPowerOffMode())
		{
		if(fgIsInWatchMode())
			{
			vFanPower(TRUE);
			vFanVolumeSet(AIR_VOLUME_MIN);
			}
		else
			{
			vFanPower(FALSE);
			}
		}
		//130408Me01&&&
}

#if 0
void vWatchModeKeyProcess(void)
{
	switch(bIRKey)
		{
		case IR_POWER:
			break;
		default:
			break;
		}
}
#endif
//130130Me01&&&


#endif

