#define _UTILITY_C_
#include "general.h"

void vChildLock(void)
{

}

void vEventPCINoneIsNormal(void)
{
}

void vEventPCINoneIsError(void)
{
}
#if 0 //130423Ad01***
void vEventCoverSwitchIsNormal(void)
{
	vIntMainMCUError(ERROR_COVER_OPEN,FALSE);	//130308Li02
}

void vEventCoverSwitchIsOpen(void)
{
	//if((bPowerMode==POWER_MODE_ON)||((bPowerMode==POWER_MODE_OFF)&&(bWatchMode!=WATCH_MANUAL)))	//130327Li02
		{
		vIntMainMCUError(ERROR_COVER_OPEN,TRUE);	//130308Li02
		}
}
#endif//130423Ad01&&&

void vSpecialFunctionModeTimer1S(void)
{
	if(fgIsInMonitorMode())
		{
		switch(bModeState)
			{
			case 2:     //every 1s send fan set RPM.
				vIntFanRotaSet(bFanSetRotationSpeedValue);
				break;	
			case 3:     //every 1s send fan detect RPM.
				vIntFanRotaDetectValue(bFanSampleValue);
				break;
			case 4:     //every 1s send fan PWM value.
				vIntFanPwm(bCurrentSetValue);
				break;
			case 5:     //every 1s send Temperature A/D Value.
				vIntTempAdc(bTemperatureADCAverageValue);
				break;
			case 6:     //every 1s send Humidity A/D Value.
				vIntHumiAdc(bHumidityADCAverageValue);
				break;
			case 8:     //every 1s send Temperature [¢J].
				vIntTempReal(bTemperature);
				break;
			case 9:     //every 1s send Humidity [%].
				vIntHumiReal(bHumidity);
				break;
			/*case 20:	//130328Ad02*** //130408Ad03***
				vPCIPowerOn();
				fgIonGenerationGetDeltaVFunction=TRUE;
				vGetIonSampleOneTime();
				break;	//130328Ad02&&&*///130408Ad03&&&
			}
		}
	else if(fgIsInFunctionCheckerTestMode())	//130328le01***
		{
		switch(bModeState)
			{
			case 5:
			case 6:	
				fgIonGenerationGetDeltaVFunction=TRUE;	//130429le01
				//fgIonGenerationGetDeltaVFunction=TRUE;//130408Ad03
				//vGetIonSampleOneTime();//130408Ad03
				vIntIonVolValue(wiDeltaV);//130408Ad03
				break;
			}
		}	//130328le01&&&
}

void vCheckFunctionCheckerModePin(void)	//130403le01***
{
	if(PIN_FUNCTION_CHECKER_READ==1)
		{
		//transfer p64 high to Touch Mcu by I2C
		vIntFunctionCheckerMode(TRUE);
		}
}	//130403le01&&&

