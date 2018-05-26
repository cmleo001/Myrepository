#ifndef _ADC_H_
#define _ADC_H_

#define ADC_CHANNEL_TEMPERATURE	3	//Main MCU
#define ADC_CHANNEL_HUMIDITY		2	//Main MCU
#define ADC_CHANNEL_ION			6	//Main MCU
#define ADC_CHANNEL_LIGHT			5	//Touch MCU
#ifdef ADC_FUNCTION
extern BOOL fgTheLightSourceIsDark;
extern BYTE bLightSensorADCAverage;	//130312Li03
extern BOOL fgLastLightSourceIsDark;//130417sh01

void vISR_ADC(void);
void vInitialADC(void);

void vLightSensorEvent(BYTE bADCValue);	 //130122Li01
//void vLightSensorTimer(void);   //130122Li01	//130419ha01
#define vLightSensorTimer()	{ADC_START;}	//130419ha01

#else
#define fgTheLightSourceIsDark	0
#define bLightSensorADCAverage	0


void vISR_ADC(void);
#define vInitialADC()

#define vLightSensorEvent(bADCValue)
#define vLightSensorTimer()
#endif


#endif

