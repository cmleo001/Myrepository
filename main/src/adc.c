#define _ADC_C_
#include "general.h"

BYTE bADCToTemperature(BYTE bAdcValue);

//Variable about ADC.
BYTE bNowADCChannel=0;
BOOL fgADCTransformIsBusy=FALSE;
BOOL fgTemHumAbnormal=FALSE;		//130308Li01
BOOL fgAdcFinish=FALSE;	//130417Ad01
///////////////////////////////////////////////
//	About ADC Transform Queue variable
///////////////////////////////////////////////
#define ADC_QUEUE_MAX_NUMBER	3	//Because Main MCU has 3 ADC channel.
BYTE bADCQueue[ADC_QUEUE_MAX_NUMBER];
BOOL fgADCQueueFull=FALSE;
BOOL fgADCQueueEmpty=TRUE;
BYTE bADCQueueStartIndex=0;
BYTE bADCQueueEndIndex=0;
void vPutADCQueue(BYTE bChannel)
{
	INT_DIS();
	if(!fgADCQueueFull)
		{
		bADCQueue[bADCQueueEndIndex]=bChannel;
		bADCQueueEndIndex=(bADCQueueEndIndex+1)%ADC_QUEUE_MAX_NUMBER;
		fgADCQueueEmpty=FALSE;
		if(bADCQueueStartIndex==bADCQueueEndIndex)				
			{
			fgADCQueueFull=TRUE;
			}
		}
	INT_EN();
}

BYTE bGetADCQueue(void)
{
	BYTE bchannel;
	INT_DIS();
	if(!fgADCQueueEmpty)
		{
		bchannel=bADCQueue[bADCQueueStartIndex];
		bADCQueueStartIndex++;
		bADCQueueStartIndex%=ADC_QUEUE_MAX_NUMBER;

		fgADCQueueFull=FALSE;  
		
		if(bADCQueueStartIndex==bADCQueueEndIndex)
			{
			fgADCQueueEmpty=TRUE;
			}
		}
	INT_EN();
	return bchannel;
}

//Please put this function in 1ms timer.
//It will check ADC queue then set the ADC channel.
//Next step is start ADC transform, and get the ADC value 
//Next step will dispatch the ADC value to source.
void vCheckADCQueue(void)
{
	//static BYTE badc_state_mechina=0;

	if(fgADCTransformIsBusy)
		return;
	
	if(!fgADCQueueEmpty)
		{
		bNowADCChannel=bGetADCQueue();
		vSetADCChannel(bNowADCChannel);
		fgADCTransformIsBusy=TRUE;
		vDelay5us();
		vDelay5us();
		vDelay5us();
		vDelay5us();	//Delay 20us sampling Time.
		ADC_START;
		}
}

void vISR_ADC(void)
{
	ADIF=0;
	//vPutEventQueue(EVENT_ADC,ADDH,0);	//130410Li01//130417Ad01
	fgAdcFinish=TRUE;//130417Ad01
	RETI();
}

void vPollingAdcValue()	//130417Ad01***
{
	if(fgAdcFinish==FALSE)
		return;
	fgAdcFinish=FALSE;
	
	fgADCTransformIsBusy=FALSE;

	switch(bNowADCChannel)
		{
		case ADC_CHANNEL_TEMPERATURE:
			vADCTemperatureEvent(ADDH);
			break;
		case ADC_CHANNEL_HUMIDITY:
			vADCHumidityEvent(ADDH);
			break;
		case ADC_CHANNEL_ION:
			vADCIONEvent(ADDH);
			break;
		}
}	//130417Ad01&&&

void vInitialADC(void)
{
	ADC_INPUT_SOURCE_VREF;		//130329Me02
	ADC_CALIBRATION_0LSB;
	ADC_OSCILLATE_CLOKE_RATE_8;	//Fosc/8

	ADC_OPERATING;
	ADC_INT_EN;
}



#ifdef TEMPERATURE_SENSOR_FUNCTION
/////////////////////////////////////////////////////
//	Function About Temperature.
/////////////////////////////////////////////////////
//Variable about Temperature.
#define TEMPERATURE_SAMPLE_TIMES	64	// 64times*25ms=1.6s

WORD wTemperatureADCValueSum=0;
BYTE bTemperatureSampleCount=TEMPERATURE_SAMPLE_TIMES;
BYTE bTemperatureADCAverageValue=0;
BYTE bTemperature=0;
//BOOL fgTemperatureAbnormal=FALSE;		//130308Li01
void vADCTemperatureEvent(BYTE bADCValue)
{
	wTemperatureADCValueSum += bADCValue;
	bTemperatureSampleCount--;
	if(bTemperatureSampleCount==0)
		{
		bTemperatureSampleCount=TEMPERATURE_SAMPLE_TIMES;
		wTemperatureADCValueSum >>= 6;	//get the avarage value for 64 times sample
		bTemperatureADCAverageValue=(BYTE)wTemperatureADCValueSum;//bTemperature save the avarage temp value of 64 times sample
		bTemperature=bADCToTemperature(bTemperatureADCAverageValue);	//130327Li01
		wTemperatureADCValueSum=0;	//130327Li01
		if(fgIsInPowerOffMode()&&fgIsNotWatchMode())	//130327Li01
			return;	//130327Li01
			
		if(	(bTemperatureADCAverageValue<=0x1b)
			||(bTemperatureADCAverageValue>=0xf5))
			{	//Temperature abnormal.
			fgTemHumAbnormal = TRUE;		//130308Li01
			vIntMainMCUError(ERROR_TEM_HUM_SENSOR, TRUE);	//130308Li01
			}
		else
			{	//Temperature normal.
			if(fgTemHumAbnormal)
				{
				vIntMainMCUError(ERROR_TEM_HUM_SENSOR, FALSE);
				}
			fgTemHumAbnormal=FALSE;		//130315Li02&&&
			}
		
		// call temperature function(bTemperature)
		vAutoFanZoneJudge();	//130418Ja01
		}
}

BYTE bADCToTemperature(BYTE bAdcValue)
{
	WORD v,dv;
	BYTE bCount;
	BOOL fgAdd;

	if(bAdcValue > 188) return 0;
	if(bAdcValue < 82) return 46;

	if(bAdcValue > 104)//temp<35
	{
		v = 4608;
		dv = 104;
		if(bAdcValue > 145)//temp<18
		{
			bCount = bAdcValue - 145;
			fgAdd = FALSE;
		}
		else
		{
			bCount = 145 - bAdcValue;
			fgAdd = TRUE;
		}
	}
	else
	{
		v = 10522;
		dv = 125;
		if(bAdcValue > 91)//temp<41
		{
			bCount = bAdcValue - 91;
			fgAdd = FALSE;
		}
		else
		{
			bCount = 91 - bAdcValue;
			fgAdd = TRUE;
		}
	}

	while(bCount--)
	{
		if(fgAdd)
		{
			v += dv;
		}
		else
		{
			v -= dv;
		}
	}

	v += 128;
	v >>= 8;//devide 256

	return (BYTE)v;
}
#endif

#ifdef HUMIDITY_SENSOR_FUNCTION
/////////////////////////////////////////////////////
//	Function About Humidity.
/////////////////////////////////////////////////////
//Variable about Humidity.
#define HUMIDITY_SAMPLE_TIMES	64

WORD wHumidityADCValueSum=0;
BYTE bHumiditySampleCount=HUMIDITY_SAMPLE_TIMES;
BYTE bHumidityADCAverageValue=0;
BYTE bHumidity=0;
//BOOL fgHumidityAbnormal=FALSE;		//130308Li01
void vADCHumidityEvent(BYTE bADCValue)
{
	wHumidityADCValueSum+=bADCValue;
	bHumiditySampleCount--;
	if(bHumiditySampleCount==0)
		{
		bHumiditySampleCount=HUMIDITY_SAMPLE_TIMES;
		wHumidityADCValueSum >>= 6;	//get the avarage value for 64 times sample
		bHumidityADCAverageValue=(BYTE)wHumidityADCValueSum;//bHumidity save the avarage hum value of 64 times sample
		bHumidity= (BYTE)bHumidityADCAverageValue/1.816685534+4.468284738;	//130327Li01
		wHumidityADCValueSum=0;	//130327Li01
		if(fgIsInPowerOffMode()&&fgIsNotWatchMode())	//130327Li01
			return;	//130327Li01
		if(	(bHumidityADCAverageValue<=0x04)		//less than or equal to 6%.
			||(bHumidityADCAverageValue>=0xcc))	//more than or equal to 117%.
			{	//Humidity abnormal.
			fgTemHumAbnormal=TRUE;	//130308Li01
			vIntMainMCUError(ERROR_TEM_HUM_SENSOR, TRUE);
			}
		else
			{	//Humidity normal.
			if(fgTemHumAbnormal)
				{
				vIntMainMCUError(ERROR_TEM_HUM_SENSOR, FALSE);
				}
			fgTemHumAbnormal=FALSE;		//130315Li02&&&
			}
		
		// call humidity function(bHumidity)
		vAutoFanZoneJudge();	//130418Ja01
		}
}
#endif

#if defined(TEMPERATURE_SENSOR_FUNCTION)||defined(HUMIDITY_SENSOR_FUNCTION)
void vTemperatureAndHumidityTimer(void)
{
	if(fgAbnormalMode==TRUE)		//130423vi01
		{
		wHumidityADCValueSum=0;//130424vi02***
		bHumiditySampleCount=HUMIDITY_SAMPLE_TIMES;
		wTemperatureADCValueSum=0;
		bTemperatureSampleCount=TEMPERATURE_SAMPLE_TIMES;//130424vi02&&&
		return;
		}						//130423vi01

	//if((bPowerMode==POWER_MODE_ON)||(bWatchMode!=WATCH_MANUAL))
	//if((bPowerMode==POWER_MODE_ON)||((bPowerMode==POWER_MODE_OFF)&&(bWatchMode!=WATCH_MANUAL)))	//130308Li01	//130327Li01
		{
#ifdef TEMPERATURE_SENSOR_FUNCTION
		vPutADCQueue(ADC_CHANNEL_TEMPERATURE);
#endif
#ifdef HUMIDITY_SENSOR_FUNCTION
		vPutADCQueue(ADC_CHANNEL_HUMIDITY);
#endif
		}
}
#endif

BOOL fgIonGenerationJudgmentControl=FALSE;
#ifdef ION_SENSOR_FUNCTION
/////////////////////////////////////////////////////
//	Function About Ion Sensor.
/////////////////////////////////////////////////////
//130221Ju01***
//Variable about Ion
//#define ION_CHECK_AFTER_POWER_ON					30	//When the power becomes "ON" and 30 seconds pass, start the control for Ion Generation Judgment. //130424Ad03
//#define ION_CHECK_EVERY_3H							10800	// 3 hours=3*3600 second = 10800 second //130424Ad03
#define ION_SAMPLE_COUNT_WHEN_PCI_ON			90	//PCI on check the Von max 90 times.
//#define ION_SAMPLE_COUNT_WHEN_PCI_ON_SPEED_UP	45	//PCI on check the Von max 90 times.	//130326Ad03//130412Ad01
#define ION_ERROR_OCCUR_COUNT						112	//Error Counter of Ion Generation.
#define ION_CHECK_MODE_SPEED_UP					180	//130312Ad01

#define V_0_5	0x19//409	// 0.5/(5V/4096)=409.6, 4096 is 2^12, ADC is 12 bits.//130409Ad01
#define V_0_1	0x05//81	// 0.1/(5V/4096)=81.92, 4096 is 2^12, ADC is 12 bits.//130409Ad01

INT16 wiDeltaVoffAvg=0;

INT16 wiDeltaV=0;
//INT16 wiDeltaVOn=0;
BOOL fgIonSampleV1=TRUE;
BOOL fgIonMeasure=FALSE;
//WORD wIonDetectCount=ION_CHECK_AFTER_POWER_ON;
WORD wIon3hCount=ION_CHECK_EVERY_3H-ION_CHECK_AFTER_POWER_ON;	//10800s//130325Ad02
//BYTE bIonDelayCount=35;//in order to make sure the temp and hum sample over, we begin the Ion sample after 35ms
BYTE bIonSampleTimes=0;//90times
BYTE bIonSampleCnt=0;//130312Ad01
BYTE bIonOKCount=0;//3//3 times

//For production line mode to get (Voff-avg>0.5V) times or (Von-Voff-avg)<0.1 times
BOOL fgIonGenerationVoltageOKFunction=FALSE;
BOOL fgIonGenerationGetDeltaVFunction=FALSE;
BOOL fgPCIPowerPinEnable=FALSE;	//130309Ad01

void vADCIONEvent(BYTE bADCValue)
{
	if(fgIonSampleV1)
		{
		fgIonSampleV1=FALSE;
		wiDeltaV = bADCValue;//must be signed type
		}
	else
		{
		fgIonSampleV1=TRUE;
		wiDeltaV = bADCValue-wiDeltaV;
		}
}

//void vADCIONInitial(void)
//{
 //    	wIon3hCount=ION_CHECK_AFTER_POWER_ON;
//}

//Every 3 hours excute "Ion Generation Judgment Control".
void vIon1sTimer(void)
{	//130309Ad01***
	//If the DeltaV and DeltaVoff-avg OK count judgement is running, the ION generation judgement control will stop.
	if((fgIonGenerationVoltageOKFunction==TRUE)||(fgIonGenerationGetDeltaVFunction==TRUE))
		{
		fgIonGenerationJudgmentControl=FALSE;
		}
	else if((fgIsInPowerOnMode())&&(fgIonGenerationJudgmentControl==FALSE))//130412Ad01
		{
		//in orde to avoid speed-up mode sample collision
		//130312Ad01***
		if(fgIsInSpeedUpMode())
			{	//Speed-up mode.
			wIon3hCount+=ION_CHECK_MODE_SPEED_UP;
			}
		else
			{	//Normal mode.
			wIon3hCount++;
			}
		
		if(wIon3hCount>=ION_CHECK_EVERY_3H)
			{
			wIon3hCount-=ION_CHECK_EVERY_3H;
			fgIonGenerationJudgmentControl=TRUE;
			}
		}	//130309Ad01&&&	//130312Ad01&&&

}


//130309Ad01***
static BYTE bStateMachine1s=0;
void vGetIonSampleAtProuductLine(void)
{
	if(fgIonGenerationVoltageOKFunction!=TRUE)
		{
		return;
		}
#if 1
	//1303016Ad01***
	if(bStateMachine1s==0)
		{
		if(fgPCIPowerPinEnable==FALSE) //130408Ad01***
			{
			wiDeltaVoffAvg=0;//130309Ad01
			} //130408Ad01&&&
		wiDeltaV=0;//130309Ad01
		bIonOKCount=0;//130309Ad01
		}
	else if(bStateMachine1s==1)
		{
		fgIonSampleV1=TRUE;
		fgIonMeasure=TRUE;		//call the vIonMeasure()
		//vIonMeasure();	//call the fuction directly, make sure the exact time//130424Ad01
		}
	else if(bStateMachine1s==2)
		{
		if(fgPCIPowerPinEnable==FALSE)
			{
			wiDeltaVoffAvg+=wiDeltaV;//please make sure we already get the wiDeltaV last 1ms?????????????
			if(wiDeltaV<V_0_5)
				{
				bIonOKCount++;
				}
			}
		else if(fgPCIPowerPinEnable)
			{	//Get delta Von >= 0.1V is ok.
			wiDeltaV-=wiDeltaVoffAvg;
			if((wiDeltaV>=V_0_1)||(wiDeltaV<=(-V_0_1)))		//130328Ad02	//130408Ad01
				{
				bIonOKCount++;
				}
			}
		bIonSampleTimes--;
		if(bIonSampleTimes==0)
			{
			if(fgPCIPowerPinEnable==FALSE)
				{
				vIntIonLeakCurrentOkCount(bIonOKCount);
				wiDeltaVoffAvg/=bIonSampleCnt;
				}
			else
				{
				vIntIonGenerationOkCount(bIonOKCount);
				}
			bIonOKCount=0;
			bStateMachine1s=0;
			fgIonGenerationVoltageOKFunction=FALSE;
			return;
			}
		else
			{
			bStateMachine1s=1;
			fgIonSampleV1=TRUE;
			fgIonMeasure=TRUE;		//call the vIonMeasure()
			//vIonMeasure();	//call the fuction directly, make sure the exact time//130424Ad01
			}
		}
	bStateMachine1s++;
	//1303016Ad01***
#else
	if(fgIonGenerationJudgmentControl==TRUE)
		{
		fgIonGenerationJudgmentControl=FALSE;
		bStateMachine1s=0;
		}
	
	switch(bStateMachine1s)
		{
		case 0:
			wiDeltaVoffAvg=0;//130309Ad01
			wiDeltaVOn=0;//130309Ad01
			bIonOKCount=0;//130309Ad01
			bStateMachine1s++;
			break;
		case 1:
			fgIonSampleV1=TRUE;
			fgIonMeasure=TRUE;		//call the vIonMeasure()
			vIonMeasure();	//call the fuction directly, make sure the exact time
			bStateMachine1s++;
			break;
		case 2:
			if(fgPCIPowerPinEnable==FALSE)
				{
				wiDeltaVoffAvg+=wiDeltaV;//please make sure we already get the wiDeltaV last 1ms?????????????
				}

			if(fgPCIPowerPinEnable)
				{	//Get delta Von >= 0.1V is ok.
				wiDeltaVOn=wiDeltaV-wiDeltaVoffAvg;
				if(wiDeltaVOn>=V_0_1)
					{
					bIonOKCount++;
					}
				}
			else	
				{	//Get delta Voff < 0.5V is ok.
				if(wiDeltaV<V_0_5)
					{
					bIonOKCount++;
					}
				}

			bIonSampleTimes--;
			if(bIonSampleTimes==0)
				{
				if(fgPCIPowerPinEnable==FALSE)
					{
					vIntIonLeakCurrentOkCount(bIonOKCount);
					wiDeltaVoffAvg/=bIonSampleCnt;
					}
				else
					{
					vIntIonGenerationOkCount(bIonOKCount);
					}
				bIonOKCount=0;
				bStateMachine1s=0;
				fgIonGenerationVoltageOKFunction=FALSE;
				}
			else
				{
				fgIonSampleV1=TRUE;
				fgIonMeasure=TRUE;		//call the vIonMeasure()
				vIonMeasure();	//call the fuction directly, make sure the exact time
				}
			break;
		}
	#endif
}
//130309Ad01&&&
//130309Ad02***
void vGetIonSampleOneTime(void)
{
	if(fgIonGenerationGetDeltaVFunction!=TRUE)
		return;
#if 1
	//1303016Ad01***
	/*if(bStateMachine1s==1)	//130408Ad03
		{
		fgIonSampleV1=TRUE;
		fgIonMeasure=TRUE;		//call the vIonMeasure()
		vIonMeasure();	//call the fuction directly, make sure the exact time
		}
	else if(bStateMachine1s==2)
		{
		vIntIonDeltaV(wiDeltaV);
		bStateMachine1s=0;
		fgIonGenerationGetDeltaVFunction=FALSE;
		return;
		}
	bStateMachine1s++;
	//1303016Ad01&&&*/		//130408Ad03
	if(bStateMachine1s==1)	//130408Ad03***
		{
		fgIonSampleV1=TRUE;
		vPutADCQueue(ADC_CHANNEL_ION);
		bStateMachine1s=0;
		}
	bStateMachine1s++;//130408Ad03&&&
#else
	if(fgIonGenerationJudgmentControl==TRUE)
		{
		fgIonGenerationJudgmentControl=FALSE;
		bStateMachine1s=0;
		}

	switch(bStateMachine1s)
		{
		case 0:
			bStateMachine1s++;
			break;
		case 1:
			fgIonSampleV1=TRUE;
			fgIonMeasure=TRUE;		//call the vIonMeasure()
			vIonMeasure();	//call the fuction directly, make sure the exact time
			bStateMachine1s++;
			break;
		case 2:
			vIntIonDeltaV(wiDeltaV);
			bStateMachine1s=0;
			fgIonGenerationGetDeltaVFunction=FALSE;
			break;
		}
#endif
	
}
//130309Ad02&&&

//Judgment which is executed every 3 hours.
//This function put in 1s timer.
void vIonGenerationJudgmentControl(void)
{
	BYTE bIonErrorCnt;//130312Ad01
	if(fgIonGenerationJudgmentControl!=TRUE)
		return;
#if 1
	//130316Ad01***
	if(bStateMachine1s==0)
		{
		vPCIPowerOff();
		wiDeltaVoffAvg=0;
		bIonOKCount=0;
		bIonSampleTimes=0;//130306Ad01
		}
	else if(bStateMachine1s==5)
		{
		fgIonSampleV1=TRUE;
		fgIonMeasure=TRUE;		//call the vIonMeasure()
		//vIonMeasure();	//130424Ad01
		}
	else if((bStateMachine1s>5)&&(bStateMachine1s<13))
		{
		wiDeltaVoffAvg+=wiDeltaV;//please make sure we already get the wiDeltaV last 1ms?????????????
		fgIonSampleV1=TRUE;
		fgIonMeasure=TRUE;		//call the vIonMeasure()
		//vIonMeasure();	//call the fuction directly, make sure the exact time//130424Ad01
		}
	else if(bStateMachine1s==13)
		{
		wiDeltaVoffAvg+=wiDeltaV;
		wiDeltaVoffAvg/=8;
		vPCIPowerOn();
			if((wiDeltaVoffAvg>V_0_5)||(wiDeltaVoffAvg<(-V_0_5)))
				{
				fgIonMeasure=FALSE;//don't need to run vIonMeasure
				bStateMachine1s=0;
				fgIonGenerationJudgmentControl=FALSE;
				return;
				}
		fgIonSampleV1=TRUE;//130424Ad01
		fgIonMeasure=TRUE;
		//vIonMeasure();	//call the fuction directly, make sure the exact time//130424Ad01
		}
	if(bStateMachine1s==14)
		{
		wiDeltaV-=wiDeltaVoffAvg;
		if((wiDeltaV>=V_0_1)||(wiDeltaV<=(-V_0_1)))
			{
			bIonOKCount++;
			if(bIonOKCount>=3)
				{
				bIonErrorCnt=0;
				vMcuEepromWriteByte(EE_ION_GENERATION_ERROR_COUNT,bIonErrorCnt);
				//i2c int ,restore bIonErrorCount to eeprom
				fgIonMeasure=FALSE;
				bStateMachine1s=0;
				fgIonGenerationJudgmentControl=FALSE;
				return;
				}
			}
		bIonSampleTimes++;
#if 0 //130412Ad01***
		if(fgIsInSpeedUpMode())	//130326Ad03***
			{
			if(bIonSampleTimes>=ION_SAMPLE_COUNT_WHEN_PCI_ON_SPEED_UP)
				{
				goto ERROR_COUNT_OVER;
				}
			}
		else
			{
			if(bIonSampleTimes>=ION_SAMPLE_COUNT_WHEN_PCI_ON)
				{
				goto ERROR_COUNT_OVER;
				}
			}
		goto CONTINUE_TO_CHECK_ION;
//		if(bIonSampleTimes>=ION_SAMPLE_COUNT_WHEN_PCI_ON)//130306Ad01
	ERROR_COUNT_OVER:	//130326Ad03&&&
			{
			bIonErrorCnt=bMcuEepromReadByte(EE_ION_GENERATION_ERROR_COUNT);//130312Ad01
			if(bIonErrorCnt<ION_ERROR_OCCUR_COUNT)	//130328Ad01***
				{
			bIonErrorCnt++;//130312Ad01
			vMcuEepromWriteByte(EE_ION_GENERATION_ERROR_COUNT,bIonErrorCnt);//130312Ad01
				}	//130328Ad01&&&
			///i2c int ,restore bIonErrorCount to eeprom
			if(bIonErrorCnt>=ION_ERROR_OCCUR_COUNT)//130312Ad01
				{
				vIntMainMCUError(WARNIN_GCLEANING_PCI_UNIT,TRUE);	//130309Ad01
				//The power becomes "OFF".At this time, the louver stops immediately.
				}
			fgIonMeasure=FALSE;
			bStateMachine1s=0;
			fgIonGenerationJudgmentControl=FALSE;
			return;
			}
	CONTINUE_TO_CHECK_ION:	//130326Ad03
		fgIonMeasure=TRUE;
		vIonMeasure();	//call the fuction directly, make sure the exact time
		bStateMachine1s=13;
		}
	bStateMachine1s++;
	//130316Ad01&&&
#else
	if(bIonSampleTimes>=ION_SAMPLE_COUNT_WHEN_PCI_ON)
		{
			bIonErrorCnt=bMcuEepromReadByte(EE_ION_GENERATION_ERROR_COUNT);
			if(bIonErrorCnt<ION_ERROR_OCCUR_COUNT)	
				{
				bIonErrorCnt++;
				vMcuEepromWriteByte(EE_ION_GENERATION_ERROR_COUNT,bIonErrorCnt);
				}	
			///i2c int ,restore bIonErrorCount to eeprom
			if(bIonErrorCnt>=ION_ERROR_OCCUR_COUNT)
				{
				vIntMainMCUError(WARNIN_GCLEANING_PCI_UNIT,TRUE);	
				//The power becomes "OFF".At this time, the louver stops immediately.
				}
			fgIonMeasure=FALSE;
			bStateMachine1s=0;
			fgIonGenerationJudgmentControl=FALSE;
			return;
		}
		fgIonSampleV1=TRUE;//130424Ad01
		fgIonMeasure=TRUE;
		//vIonMeasure();	//call the fuction directly, make sure the exact time//130424Ad01
		bStateMachine1s=13;
		}
	bStateMachine1s++;
#endif //130412Ad01&&&
#else
	switch(bStateMachine1s)
		{
		case 0:
			vPCIPowerOff();
			wiDeltaVoffAvg=0;
			bIonOKCount=0;
			bIonSampleTimes=0;//130306Ad01
			break;
		case 5:
			fgIonSampleV1=TRUE;
			fgIonMeasure=TRUE;		//call the vIonMeasure()
			vIonMeasure();	//call the fuction directly, make sure the exact time
			break;
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			wiDeltaVoffAvg+=wiDeltaV;//please make sure we already get the wiDeltaV last 1ms?????????????

			fgIonSampleV1=TRUE;
			fgIonMeasure=TRUE;		//call the vIonMeasure()
			vIonMeasure();	//call the fuction directly, make sure the exact time
			break;
		case 13:
			wiDeltaVoffAvg+=wiDeltaV;
			
			wiDeltaVoffAvg/=8;
			
			vPCIPowerOn();
			if((wiDeltaVoffAvg>V_0_5)||(wiDeltaVoffAvg<(-V_0_5)))
				{
				fgIonMeasure=FALSE;//don't need to run vIonMeasure
				bStateMachine1s=0;
				fgIonGenerationJudgmentControl=FALSE;
				return;
				}
			
			fgIonMeasure=TRUE;
			vIonMeasure();	//call the fuction directly, make sure the exact time
			break;
		case 14:
			wiDeltaVOn=wiDeltaV-wiDeltaVoffAvg;
			if((wiDeltaVOn>=V_0_1)||(wiDeltaVOn<=(-V_0_1)))
				{
				bIonOKCount++;
				if(bIonOKCount>=3)
					{
					bIonErrorCnt=0;
					vMcuEepromWriteByte(EE_ION_GENERATION_ERROR_COUNT,bIonErrorCnt);
					//i2c int ,restore bIonErrorCount to eeprom
					fgIonMeasure=FALSE;
					bStateMachine1s=0;
					fgIonGenerationJudgmentControl=FALSE;
					return;
					}
				}

			bIonSampleTimes++;
			if(bIonSampleTimes>=ION_SAMPLE_COUNT_WHEN_PCI_ON)//130306Ad01
				{
				bIonErrorCnt=bMcuEepromReadByte(EE_ION_GENERATION_ERROR_COUNT);//130312Ad01
				bIonErrorCnt++;//130312Ad01
				vMcuEepromWriteByte(EE_ION_GENERATION_ERROR_COUNT,bIonErrorCnt);//130312Ad01
				///i2c int ,restore bIonErrorCount to eeprom
				if(bIonErrorCnt>=ION_ERROR_OCCUR_COUNT)//130312Ad01
					{
					vIntMainMCUError(WARNIN_GCLEANING_PCI_UNIT,TRUE);	//130309Ad01
					//The power becomes "OFF".At this time, the louver stops immediately.
					}
				fgIonMeasure=FALSE;
				bStateMachine1s=0;
				fgIonGenerationJudgmentControl=FALSE;
				return;
				}
			
			fgIonMeasure=TRUE;
			vIonMeasure();	//call the fuction directly, make sure the exact time
			bStateMachine1s=13;
			break;
		default:
			break;//130306Ad01
		}
#endif
	
}

//Every 1ms excute 1 times.
void vIonMeasure(void)
{
	 static WORD bStateMachine1ms=0;
	if(fgIonMeasure!=TRUE) 
		return;
	
	if(bStateMachine1ms>=999)//130424Ad01
		{
		bStateMachine1ms=0;
		}
	
#if 1
	//130316Ad01***
	if(bStateMachine1ms==0)//130325Ad01
		{
		vIONResetEN();
		}
	else if(bStateMachine1ms==1)
		{
		vIONResetDIS();
		}
	else if(bStateMachine1ms==2)
		{
		vPutADCQueue(ADC_CHANNEL_ION);
		}
	else if(bStateMachine1ms==998)//130424Ad01
		{
		if(fgADCTransformIsBusy)
				{
				vPutADCQueue(ADC_CHANNEL_ION);
				}
			else
				{
				bNowADCChannel=ADC_CHANNEL_ION;
				vSetADCChannel(ADC_CHANNEL_ION);
				fgADCTransformIsBusy=TRUE;
				vDelay5us();
				vDelay5us();
				vDelay5us();
				vDelay5us();	//Delay 20us sampling Time.
				ADC_START;
				}
			fgIonMeasure=FALSE;
		}
	bStateMachine1ms++;
	//130316Ad01&&&
#else
	switch(bStateMachine1ms)
		{
		case 0:
			vIONResetEN();
			break;
		case 1:
			vIONResetDIS();
			break;
		case 2:
			//we must be sure that there is only Ion in the queue,so we can begin the transform immediately.
			//we will check queue in the main loop,then run, then check event and get the ADC value
			vPutADCQueue(ADC_CHANNEL_ION);
			break;
		case 999:
			if(fgADCTransformIsBusy)
				{
				vPutADCQueue(ADC_CHANNEL_ION);
				break;
				}
			else
				{
				bNowADCChannel=ADC_CHANNEL_ION;
				vSetADCChannel(ADC_CHANNEL_ION);
				fgADCTransformIsBusy=TRUE;
				vDelay5us();
				vDelay5us();
				vDelay5us();
				vDelay5us();	//Delay 20us sampling Time.
				ADC_START;
				}
			fgIonMeasure=FALSE;
			break;
		default:
			break;//130306Ad01
		}
	bStateMachine1ms++;
#endif
}
//130221Ju01&&&
#endif

