#ifndef _ADC_H_
#define _ADC_H_

#define ADC_CHANNEL_TEMPERATURE	3	//Main MCU
#define ADC_CHANNEL_HUMIDITY		2	//Main MCU
#define ADC_CHANNEL_ION			6	//Main MCU
#define ADC_CHANNEL_LIGHT			5	//Touch MCU
extern BOOL fgTheLightSourceIsDark;
extern BOOL fgADCTransformIsBusy;
extern BYTE bNowADCChannel;

extern BOOL fgTemHumAbnormal;//130409vi01
void vISR_ADC(void);
void vInitialADC(void);
void vCheckADCQueue(void);
void vPutADCQueue(BYTE bChannel);
#define vReadADCChannel(channel)	vPutADCQueue(channel)

#ifdef TEMPERATURE_SENSOR_FUNCTION
void vADCTemperatureEvent(BYTE bADCValue);		//130316Li02
extern BYTE bTemperature;
extern BYTE bTemperatureADCAverageValue;
#else
#define vADCTemperatureEvent(bADCValue)		//130316Li02
#define  bTemperature	0
#define  bTemperatureADCAverageValue	0
#endif

#ifdef HUMIDITY_SENSOR_FUNCTION
void vADCHumidityEvent(BYTE bADCValue);		//130316Li02
extern BYTE bHumidity;
extern BYTE bHumidityADCAverageValue;
#else
#define vADCHumidityEvent(bADCValue)	//130316Li02
#define  bHumidity	0
#define  bHumidityADCAverageValue	0
#endif

#if defined(TEMPERATURE_SENSOR_FUNCTION)||defined(HUMIDITY_SENSOR_FUNCTION)
void vTemperatureAndHumidityTimer(void);
#else
#define vTemperatureAndHumidityTimer()
#endif

extern BOOL fgIonGenerationJudgmentControl;
#ifdef ION_SENSOR_FUNCTION
void vADCIONEvent(BYTE bADCValue);
//void vADCIONInitial(void);
void vIonMeasure(void);
void vIonGenerationJudgmentControl(void);
void vGetIonSampleAtProuductLine(void);
void vGetIonSampleOneTime(void);
void vIon1sTimer(void);
void vPollingAdcValue(void);//130417Ad01
//130423Ad01***
#define ION_CHECK_AFTER_POWER_ON					30	//When the power becomes "ON" and 30 seconds pass, start the control for Ion Generation Judgment. //130424Ad03
#define ION_CHECK_EVERY_3H							10800	// 3 hours=3*3600 second = 10800 second//130424Ad03

#define ION_CHECK_IS_SPEED_UP 5400	// Ion sensor check time is 180X at speed up mode.
#define vADCIONInitial()	{if(fgIsInSpeedUpMode()) wIon3hCount=ION_CHECK_IS_SPEED_UP;else{wIon3hCount=ION_CHECK_EVERY_3H-ION_CHECK_AFTER_POWER_ON;}}  //130424Ad03

//speed-up mode power on after 30s Ion check
extern WORD wIon3hCount;
//130423Ad01&&&
extern INT16 wiDeltaV;
extern BOOL fgAdcFinish;//130417Ad01
//130309Ad01***
extern BOOL fgIonGenerationVoltageOKFunction;
extern BOOL fgIonGenerationGetDeltaVFunction;
extern BOOL fgPCIPowerPinEnable;
extern BYTE bIonSampleTimes;
extern BYTE bIonSampleCnt;
extern BYTE bIonErrorCount;
//130309Ad01&&&
#else
#define vADCIONEvent(bADCValue)
#define vADCIONInitial()
#define vIonMeasure()
#define vIonGenerationJudgmentControl()
#define vGetIonSampleAtProuductLine()
#define vGetIonSampleOneTime()
#define vIon1sTimer()

#define fgIonGenerationVoltageOKFunction	0
#define fgIonGenerationGetDeltaVFunction	0
#define fgPCIPowerPinEnable		0
#define bIonSampleTimes	0
#define bIonSampleCnt	0
#define bIonErrorCount	0
#endif



#endif

