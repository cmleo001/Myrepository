#define _MODE_DEMO_C_
#include "general.h"

#ifdef DEMO_MODE_FUNCTION
//130124ma01***
#define DEMO_MODE_COUNT_NUM		 	120	//計時的最大值3s

void vDemoModeTimer(void)
{
	if(bSpecialFunctionMode!=MODE_DEMO)		//130416st01***
		{
		return;
		}	//130416st01&&&
//130306ra01***
	if(bModeTimeCount<=DEMO_MODE_COUNT_NUM)	
		{
		bModeTimeCount++;
		if(bModeTimeCount==DEMO_MODE_COUNT_NUM)
			{
			vPutEventQueue(EVENT_IR, IR_NEXT_STEP, 0);
			}
		}
//130306ra01&&&
}
/* //130413gr01***
//130314ma01***
void vDemoModeAirVolumeOddOn(void)
{
	vDisplayLEDAirVolume1to8Off();  //130316ma01
	vDisplayLEDAirVolume1On();
	//vDisplayLEDAirVolume2Off();  //130316ma01
	vDisplayLEDAirVolume3On();
	//vDisplayLEDAirVolume4Off();  //130316ma01
	vDisplayLEDAirVolume5On();
	//vDisplayLEDAirVolume6Off();  //130316ma01
	vDisplayLEDAirVolume7On();
	//vDisplayLEDAirVolume8Off();  //130316ma01
}

void vDemoModeAirVolumeEvenOn(void)
{
	vDisplayLEDAirVolume1to8On();  //130316ma01
	vDisplayLEDAirVolume1Off();
	//vDisplayLEDAirVolume2On();  //130316ma01
	vDisplayLEDAirVolume3Off();
	//vDisplayLEDAirVolume4On();  //130316ma01
	vDisplayLEDAirVolume5Off();
	//vDisplayLEDAirVolume6On();  //130316ma01
	vDisplayLEDAirVolume7Off();
	//vDisplayLEDAirVolume8On();  //130316ma01	
}
*/ //130413gr01&&&
//130314ma02&&&

void vDemoModeInitial(void)
{
	if(fgIsInWatchMode()||fgIsInPowerOnMode()||fgIsInTimerOnOffFunction())//130325ma01***	//130422ra01
		{
		return;
		}//130325ma02&&&
	
	bSpecialFunctionMode=MODE_DEMO;
	vSetKeyState(KEY_DEMO_MODE);
	vSubMcuSendSpecialMode(bSpecialFunctionMode);
	bModeTimeCount = 0; //130309ma02
	bModeState = 1;	//130306ra01
	//power status:on
	//bPowerMode=POWER_MODE_ON;  //130309ma02
	//fan power status:on
	//vFanPower(TRUE);  //130309ma02   //130313ma01
	// watch mode indication (green) lights up
#if 0  //130327ma01***
	vDisplayLEDWatchGreenOn();
	//Child Lock Sign lights up
	vDisplayLEDChildLockSignOn();
	//warning buzzer indication lights up
	vDisplayLEDWarningBuzzerOn();
	//Filter Clean Sign lights up
	vDisplayLEDFilterCleanOn();
	//Louver Mode state: Horizontal
	//vLouverModeSet(LOUVER_HORIZONTAL_1);  //130313ma01
	//I2C write (fine air volume level , 4)
	//vFanVolumeSet(4); //130309ma02   //130313ma01
	//Digital Indication show 88
	vDisplay7SegShowDecNumOn(88); //130309ma02
	//Air Volume Indication (1,3,5,7) lights up,(2,4,6,8) off
	vDemoModeAirVolumeOddOn();	//130314ma01
#endif  //130327ma01&&&
	//vSetKeyState(KEY_DEMO_MODE);	//130316ma01
	vPutEventQueue(EVENT_IR, IR_NEXT_STEP, 0);
	//bSpecialFunctionMode=MODE_DEMO;//130309ma02
}



#if 1	//130416ha02***
void vDemoMode_OddOn(void)
{
	vDisplayLEDAirVolumeOddOn(); //130413gr01
	bModeState++;
}
void vDemoMode_EvenOn(void)
{
	vDisplayLEDAirVolumeEvenOn(); //130413gr01
	if(bModeState != 8)
		{
		bModeState++;		
		}
	else
		{
		bModeState = 1;	
		}
}
//130417ma02***
void vDemoModePublicOff_1_6(void)
{
	vDisplayLEDWatchRedBlinkOff(); 
	vDisplayLEDTubeWhiteBlinkOff();
	vDisplayLEDWarningBuzzerBlinkOff(); 
	vDisplay7SegShowHiBlinkOff();
	vDisplayLEDChildLockSignOn();
}
void vDemoModePublicOn_5_8(void)
{
	vDisplayLEDFilterCleanOn();
	vDisplayLEDWatchRedBlinkOn(DISPLAY_TIME_0_5_SECOND); 
	vDisplayLEDTubeWhiteBlinkOn(DISPLAY_TIME_0_5_SECOND);
	vDisplayLEDWarningBuzzerBlinkOn(DISPLAY_TIME_0_5_SECOND);
	vDisplay7SegMessageClear();
	vDisplayLEDAirVolumeSettingIndicationOff();
}
//130417ma02&&&

void vDemoMode_1(void)
{
	vDemoModePublicOff_1_6();  //130417ma02
	vDisplayLEDPCIReplacingOn();  //130314ma02
	vDisplayLEDWatchGreenOn();
	//130417ma02
	vDisplayLEDWarningBuzzerOn();
	vDisplayLEDFilterCleanOn();
	vDisplay7SegShowHexNumOn(0xD1);

	Function(_vDemoMode_OddOn);
}
void vDemoMode_2(void)
{
	vDisplayLEDPCIReplacingOff();  //130314ma02
	vDisplayLEDAirVolumeSettingIndicationOn();
	vDisplayLEDChildLockSignOff();
	vDisplay7SegShowDecNumOn(4);  //130402ma01
	
	Function(_vDemoMode_EvenOn);
}
void vDemoMode_3(void)
{
	vDisplayLEDPCIReplacingOn();  //130314ma02
	vDisplayLEDFilterCleanOff();
	vDisplayLEDWatchRedOn();
	
	Function(_vDemoMode_OddOn);
}
void vDemoMode_4(void)
{
	vDisplayLEDPCIReplacingOff();  //130314ma02
	vDisplayLEDChildLockSignOn();
	vDisplayLEDWatchGreenOff();
	vBuzzerOutput(PI_LOUD_HC);
	
	Function(_vDemoMode_EvenOn);
}
void vDemoMode_5(void)
{
	vDisplayLEDFilterCleanOn();
	vDemoModePublicOn_5_8();  //130417ma02
	vDisplayLEDChildLockSignOff();
	//130417ma02
	vDisplay7SegShowHiBlinkOn(DISPLAY_TIME_0_5_SECOND);//130306ja03
	vFanVolumeSet(AIR_VOLUME_MAX);//130309ma02
	//130417ma02
	vBuzzerOutput(PI_LOUD_HD);
	vDisplayLEDAirVolume1to9On();	//130314ma01   //130402ma02
	bModeState++;	//130306ra01
}
void vDemoMode_6(void)
{
	vBuzzerOutput(PI_OFF);  //130320ma01
	vDemoModePublicOff_1_6();  //130417ma02
	vDisplayLEDAirVolume9Off();//130314ma02
	vDisplayLEDFilterCleanOff();
	vFanVolumeSet(4);//130309ma02
	vDisplayLEDWarningBuzzerOn();
	//130417ma02
	vDisplayLEDWatchGreenOn();
	vDisplay7SegShowHexNumOn(0xD2);
	
	Function(_vDemoMode_EvenOn);
}
void vDemoMode_7(void)
{
	vDisplayLEDPCIReplacingOn();  //130314ma02
	vDisplayLEDChildLockSignOff();
	vDisplayLEDAirVolumeSettingIndicationOn();
	vDisplay7SegShowDecNumOn(4);  //130402ma01
	
	Function(_vDemoMode_OddOn);
}
void vDemoMode_8(void)
{
	vDisplayLEDPCIReplacingOff();  //130314ma02
	vDemoModePublicOn_5_8();  //130417ma02
	vDisplay7SegShowLoBlinkOn(DISPLAY_TIME_0_5_SECOND);//130306ja03
	vDisplayLEDFilterCleanOn();
	//130417ma02
	vDisplayLEDWatchGreenOff();
	//130417ma02
	vBuzzerOutput(PI_LOUD_L);
	
	Function(_vDemoMode_EvenOn);
}

void vDemoModeKeyProcess(void)
{
	if(fgExecuteDemoMode==FALSE)	//130329ha01
		return;	//130329ha01
	fgExecuteDemoMode=FALSE;	//130329ha01
	
	//130311ma01***
	if(bIRKey==IR_DEMO_MODE)
		{
		vDemoModeExit();
		return;
		}
	
	if(bIRKey!=IR_NEXT_STEP) 
		{//130309ma02
		return; 
		}//130309ma02
	//130311ma01&&&

	bModeTimeCount = 0;

//	bjump_addr<<=1;	
//	_asm{ mov  a, %bjump_addr}
//	Call(bjump_addr);
	_asm{ mov  a, %bModeState}; 
	_asm{ add  %PC, a };
	NOP();
	Function(_vDemoMode_1);
	Function(_vDemoMode_2);
	Function(_vDemoMode_3);
	Function(_vDemoMode_4);
	Function(_vDemoMode_5);
	Function(_vDemoMode_6);
	Function(_vDemoMode_7);
	Function(_vDemoMode_8);
}
#else	//130416ha02&&&
void vDemoModeKeyProcess(void)
{
	if(fgExecuteDemoMode==FALSE)	//130329ha01
		return;	//130329ha01
	fgExecuteDemoMode=FALSE;	//130329ha01
	
	//130311ma01***
	if(bIRKey==IR_DEMO_MODE)
		{
		vDemoModeExit();
		return;
		}
	
	if(bIRKey!=IR_NEXT_STEP) 
		{//130309ma02
		return; 
		}//130309ma02
	//130311ma01&&&

	bModeTimeCount = 0;

	switch(bModeState)	//130306ra01
		{
		case 1:
			//vBuzzerOutput(PI_OFF);  //130320ma01  //130327ma01
			vDisplayLEDWatchRedBlinkOff(); //130314ma02
			vDisplayLEDTubeWhiteBlinkOff();  //130314ma02
			vDisplayLEDWarningBuzzerBlinkOff();  //130314ma02
			vDisplay7SegShowHiBlinkOff();	   //130314ma02  //130316ma01  //130320ma01
			//tube LED lights up
			//vDisplayLEDTubeWhiteOn();//130309ma02
			// watch mode indication (red) off
			//vDisplayLEDWatchRedOff();  //130314ma02
			//unit replacing lights up
			vDisplayLEDPCIReplacingOn();  //130314ma02
			// watch mode indication (green) lights up
			vDisplayLEDWatchGreenOn();
			//child lock sign lights up
			vDisplayLEDChildLockSignOn();
			//Warining buzzer indication not blink
			//vDisplayLEDWarningBuzzerOff();//130309ma02
			//vDisplayLEDWarningBuzzerOff();//130309ma02
			//warning buzzer indication lights up
			vDisplayLEDWarningBuzzerOn();
			//Filter Clean Sign lights up
			vDisplayLEDFilterCleanOn();
			//Digital Indication show d1
			vDisplay7SegShowHexNumOn(0xD1);
			//Air Volume Indication (1,3,5,7) lights up,(2,4,6,8) off
			goto ODD_ON;	//130314ma01
			break;
		case 2:
			//unit replacing light off
			vDisplayLEDPCIReplacingOff();  //130314ma02
			//Air Volume Indication lights up
			vDisplayLEDAirVolumeSettingIndicationOn();
			//Child Lock Sign off
			vDisplayLEDChildLockSignOff();
			//Digital Indication show 4
			vDisplay7SegShowDecNumOn(4);  //130402ma01
			//Air Volume Indication (1,3,5,7) off,(2,4,6,8) lights up
			goto EVEN_ON;	//130314ma01
			break;
		case 3:
			//unit replacing lights up
			vDisplayLEDPCIReplacingOn();  //130314ma02
			//Filter Clean Sign off
			vDisplayLEDFilterCleanOff();
			//watch mode indication (red) lights up
			vDisplayLEDWatchRedOn();
			//Air Volume Indication (1,3,5,7) lights up,(2,4,6,8) off
			goto ODD_ON;	//130314ma01
			break;
		case 4:
			//unit replacing light off
			vDisplayLEDPCIReplacingOff();  //130314ma02
			//Child Lock Sign lights up
			vDisplayLEDChildLockSignOn();
			// watch mode indication (green) off
			vDisplayLEDWatchGreenOff();
			//buzzer sound(Pi(Loud HC))
			vBuzzerOutput(PI_LOUD_HC);
			//Air Volume Indication (1,3,5,7) off,(2,4,6,8) lights up
			goto EVEN_ON;	//130314ma01
			break;
		case 5:
			//turbo mode indication  on
			//vDisplayLEDAirVolume9On();//130314ma02   //130402ma02
			//Filter Clean Sign lights up
			vDisplayLEDFilterCleanOn();
			vDisplayLEDWatchRedBlinkOn(DISPLAY_TIME_0_5_SECOND); //130309ma02
			vDisplayLEDTubeWhiteBlinkOn(DISPLAY_TIME_0_5_SECOND); //130309ma02   //130314ma02
			//Child Lock Sign off
			vDisplayLEDChildLockSignOff();
			//Warining buzzer indication blink
			vDisplayLEDWarningBuzzerBlinkOn(DISPLAY_TIME_0_5_SECOND);//130306ja03
			vDisplay7SegMessageClear();   //130415ma02
			//Digital Indication show Hi(blink)
			vDisplay7SegShowHiBlinkOn(DISPLAY_TIME_0_5_SECOND);//130306ja03
			//I2C write (fine air volume level , 33(Turbo))
			vFanVolumeSet(AIR_VOLUME_MAX);//130309ma02
			//Air Volume Setting Indication off
			vDisplayLEDAirVolumeSettingIndicationOff();
			//buzzer sound(Pi(Loud HD))
			vBuzzerOutput(PI_LOUD_HD);
			//Air Volume Indication (1--8) all lights up
			vDisplayLEDAirVolume1to9On();	//130314ma01   //130402ma02
			bModeState++;	//130306ra01
			break;
		case 6:
			vBuzzerOutput(PI_OFF);  //130320ma01
			vDisplayLEDWatchRedBlinkOff(); //130314ma02
			vDisplayLEDTubeWhiteBlinkOff();  //130314ma02
			vDisplayLEDWarningBuzzerBlinkOff();  //130314ma02
			vDisplay7SegShowHiBlinkOff();	   //130314ma02 //130316ma01    //130320ma01
			//turbo mode indication  off
			vDisplayLEDAirVolume9Off();//130314ma02
			//Warining buzzer indication not blink
			//vDisplayLEDWarningBuzzerOff();//130309ma02
			//Filter Clean Sign off
			vDisplayLEDFilterCleanOff();
			// tube LED lights up
			//vDisplayLEDTubeWhiteOn();//130309ma02
			//I2C write (fine air volume level , 4)
			vFanVolumeSet(4);//130309ma02
			//warning buzzer indication lights up
			vDisplayLEDWarningBuzzerOn();
			// watch mode indication (red) off
			//vDisplayLEDWatchRedOff(); //130314ma02
			//Child Lock Sign lights up
			vDisplayLEDChildLockSignOn();
			// watch mode indication (green) lights up
			vDisplayLEDWatchGreenOn();
			//Digital Indication show d2
			vDisplay7SegShowHexNumOn(0xD2);
			//Air Volume Indication (1,3,5,7) off,(2,4,6,8) lights up
			goto EVEN_ON;	//130314ma01
			break;
		case 7:
			//unit replacing lights up
			vDisplayLEDPCIReplacingOn();  //130314ma02
			//Child Lock Sign off
			vDisplayLEDChildLockSignOff();
			//Air Volume Setting Indication lights up
			vDisplayLEDAirVolumeSettingIndicationOn();
			//Digital Indication show 4
			vDisplay7SegShowDecNumOn(4);  //130402ma01
			//Air Volume Indication (1,3,5,7) lights up,(2,4,6,8) off
			goto ODD_ON;	//130314ma01
			break;
		case 8:
			//unit replacing light off
			vDisplayLEDPCIReplacingOff();  //130314ma02
			//Warining buzzer indication blink
			vDisplayLEDWarningBuzzerBlinkOn(DISPLAY_TIME_0_5_SECOND);//130306ja03
			vDisplayLEDTubeWhiteBlinkOn(DISPLAY_TIME_0_5_SECOND);//130309ma02  //130314ma02
			vDisplay7SegMessageClear();   //130415ma02
			//Digital Indication show Lo(blink)
			vDisplay7SegShowLoBlinkOn(DISPLAY_TIME_0_5_SECOND);//130306ja03
			//Filter Clean Sign lights up
			vDisplayLEDFilterCleanOn();
			//Air Volume Setting Indication off
			vDisplayLEDAirVolumeSettingIndicationOff();
			// watch mode indication (green) off
			vDisplayLEDWatchGreenOff();
			vDisplayLEDWatchRedBlinkOn(DISPLAY_TIME_0_5_SECOND); //130309ma02  //130314ma02
			//buzzer sound(Pi(Loud L))
			vBuzzerOutput(PI_LOUD_L);
			//Air Volume Indication (1,3,5,7) off,(2,4,6,8) lights up
			goto EVEN_ON;	//130314ma01	
			break;
		default:
			break;
			
		}
	//130314ma01***
	return;

	ODD_ON:
		vDisplayLEDAirVolumeOddOn(); //130413gr01
		//vDemoModeAirVolumeOddOn(); //130413gr01
		bModeState++;
		return;
	EVEN_ON:
		vDisplayLEDAirVolumeEvenOn(); //130413gr01
		//vDemoModeAirVolumeEvenOn(); //130413gr01
		if(bModeState != 8)
			{
			bModeState++;		
			}
		else
			{
			bModeState = 1;	
			}
	//130314ma01&&&
}
#endif

void vDemoModeExit(void)
{
	vSetKeyState(KEY_NORMAL);
	bSpecialFunctionMode=MODE_NORMAL;
	vSubMcuSendSpecialMode(bSpecialFunctionMode);	//130313ma01
	
	//tube led lights up
	//vDisplayLEDTubeWhiteBlink(DISPLAY_TIME_0_5_SECOND);//130309ma02  //130311ma01
	//Warining buzzer indication not blink
	//vDisplayLEDWarningBuzzerOff();//130309ma02
	//fan power status off
	//vFanPower(FALSE);//130309ma02	//130313ma01
	//power status off
	//vertical louver mode:STOPTOU90D
	//LouverModeSet(LOUVER_STOP);//130309ma02	//130313ma01
	//all led off
	//vDisplayLEDAllOff();//130419gr01
	//vDisplay7segLedAllOff();//130419gr01
	vDisplay7segLedAndTouchLedAllOff();//130419gr01

	//buzzer(PiPi)
	//BuzzerOutput(PI_PI);	//130313ma01
	//Air Volume Indication (1--8) all off
	//vDisplayLEDAirVolume1to8(FALSE);  //130311ma02
}
#endif
