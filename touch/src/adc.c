#define _ADC_C_
#include "general.h"

#ifdef ADC_FUNCTION
//Variable about ADC.
//BYTE bNowADCChannel=0;
//BOOL fgADCTransformIsBusy=FALSE;		//130309Li02

//Variable about light sensor.
#define LIGHT_SENSOR_SAMPLE_TIMES		64	//Get 64 times=25ms*64=1.6s ADC value, then get the average ADC value.
#define LIGHT_LEVEL_DARK		0x29    //The max margin about dark. 130122Li01***
#define LIGHT_LEVEL_LIGHT		0x32   //The min margin about light.
BOOL fgTheLightSourceIsDark=FALSE;	//130328Li01
WORD wLightSensorADCValue=0;	//We will get the ADC average value in this variable.	130122Li01
BYTE bLightSensorCount=0;		//130122Li01
BYTE bLightSensorADCAverage=0;	//130312Li03
BOOL fgLastLightSourceIsDark=TRUE;//130417sh01
//Adc value conversion function        //130122Li01***
void vLightSensorEvent(BYTE bADCValue)
{
	//BYTE bADCSampleValue;			//130122Li01	//130315vi01
	//static BOOL fgLastLightSourceIsDark=TRUE;	//130413sh01//130417sh01
	wLightSensorADCValue+=bADCValue;	//AD high 8-bit data buffer
	bLightSensorCount ++;
	if (bLightSensorCount >=LIGHT_SENSOR_SAMPLE_TIMES)            //receive AD value 64times
		{
		bLightSensorCount =0;            
		
		wLightSensorADCValue>>=6;                 //get the average of 64 pieces
		bLightSensorADCAverage=(BYTE)wLightSensorADCValue;	//130312Li03
		if(bLightSensorADCAverage > LIGHT_LEVEL_LIGHT)          //"bright" range
			{
			fgTheLightSourceIsDark=FALSE;
			}
		else if(bLightSensorADCAverage < LIGHT_LEVEL_DARK)           //"dark" range
			{
			fgTheLightSourceIsDark=TRUE;
#ifdef FUNCTION_CHECKER_MODE_FUNCTION	//130425le01
			if((fgIsInFunctionCheckerTestMode())&&(bModeState==8))	//130328le01***
				{
				vPutEventQueue(EVENT_IR,IR_NEXT_STEP,0);
				}	//130328le01&&&
#endif	//130425le01
			}
		wLightSensorADCValue= 0;
		if(fgLastLightSourceIsDark!=fgTheLightSourceIsDark)//130413sh01
			{
			vLightDarkEvent();
			fgLastLightSourceIsDark=fgTheLightSourceIsDark;//130413sh01
			}
		}
}//130122Li01&&&

//Every 25ms
#if 0	//130419ha01
void vLightSensorTimer(void)   //130122Li01***
{
//	if(bWatchMode!=WATCH_MANUAL)	//light sensor valid in Watch mode //130326li01
		{
		//vPutADCQueue(ADC_CHANNEL_LIGHT);		//130312Li01
		ADC_START;	//130312Li01
		}
}	//130122Li01&&&
#endif	//130419ha01

#if 0	//130419ha01
void vISR_ADC(void)
{
	ADIF=0;
	vPutEventQueue(EVENT_ADC,0,0);
	RETI();
}
#endif	//130419ha01

void vInitialADC(void)
{
	ADC_INPUT_SOURCE_VDD;
	ADC_CALIBRATION_0LSB;
	ADC_OSCILLATE_CLOKE_RATE_32;	//Fosc/32

	ADC_OPERATING;
	ADC_INT_EN;
	
	vSetADCChannel(ADC_CHANNEL_LIGHT);		//130312Li01
}

#else
void vISR_ADC(void)
{
	ADIF=0;
	RETI();
}

#endif


