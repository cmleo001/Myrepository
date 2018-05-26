#define _MODE_PRODUCTION_LINE_C_
#include "general.h"

#ifdef PRODUCTION_LINE_MODE_FUNCTION

//130123ma01***
#define MAX_COUNT_NUM		 	250 //�p�ɪ��̤j��
#define STEP3_COUNT_NUM 		120 // 25ms*120=3000ms=3s,�i�Jstep3���ɶ��n�D
#define STEP5_COUNT_NUM 		200 // 25ms*200=5000ms=5s,�i�Jstpe5���ɶ��n�D
#define LEAKCURRENTJUDGMENTTIME 		3 //130309ma03
#define IONGENERATIONJUDGMENTTIME 		5  //130309ma03
BOOL fgProductModeTimeStatus = FALSE;//130309ma02				// 3s�p�� from init to step3  //35add
BOOL fgProductModeBlue3State = FALSE;//130309ma01
BOOL fgProductModeBlue6State = FALSE;//130309ma01
/*   //130312ma01***
BOOL fgProductModeIonDeltaVoff = FALSE;//130309ma01
BOOL fgProductModeIonDeltaV = FALSE;//130309ma01	
*/   //130312ma01&&&
//�p�ɨ��
//�\��:�p���ܶq�ۼW�A�o�e�i��U�@�Bkey
/*   //130313ma02***
void vProductModeTimer25ms(void)
{
//130306ra01***
	if(bModeTimeCount<MAX_COUNT_NUM)
		{
		bModeTimeCount++;
		}
	
	switch(bModeState)
		{
		case 3:
			if(bModeTimeCount>STEP3_COUNT_NUM)
				{
				fgProductModeTimeStatus =TRUE; //130309ma02
				bModeTimeCount=0;
				}
			break;
		case 5:
			if(bModeTimeCount>STEP5_COUNT_NUM)
				{
				vPutEventQueue(EVENT_IR, IR_NEXT_STEP, 0);
				bModeTimeCount=0;
//130306ra01&&&
				}
			break;
		}
}
*/   //130313ma02&&&

//�i�Jproduct line mode�ɪ���l�ƨ��
void vProductionLineModeInitial(void)
{
	if(fgIsInWatchMode()||fgIsInPowerOnMode()||fgIsInTimerOnOffFunction())	//130422ra01***
		{
		return;
		}	//130422ra01&&&
	
	if(fgIsAutoRestartFunction())
		{
		return;
		} //130309ma02
	bModeTimeCount = 0;	//130306ra01
	bModeState = 1;	//130306ra01
	vSubMcuSendSpecialMode(MODE_PRODUCTION_LINE);   //130313ma01
	vSubMcuReadIonLeakCurrentOkCount(LEAKCURRENTJUDGMENTTIME);   //130313ma02
	//set FM(FanMotor): on  POWER:on
	//vFanPower(TRUE);//130309ma02   //130313ma01
	//tube led lights up
	vDisplayLEDTubeWhiteOn();  //130312ma02
	//the louver moves to the opened position:VERT_MODE_STOPTOL20D
	//vLouverModeSet(LOUVER_INITIAL_POSITION);   //130313ma01
	//the louver moves to the horizontal positon and stop
	//vLouverModeSet(LOUVER_HORIZONTAL_1);	//130309ma02   //130313ma01
	//�q�LI2C�]�m�{�b��FanVolume�O8
	//vFanVolumeSet(8);   //130313ma01
	//buzzer(Pi)
	//vBuzzerOutput(PI);   //130313ma01
	//�]�m�Ҧ��O�G
	//vDisplay7segLedAllOn();//130419gr01
	//update touch led state,make all lights up 
	//vDisplayLEDAllOn();//130419gr01
	vDisplay7segLedAndTouchLedAllOn();//130419gr01

	vSetKeyState(KEY_PRODUCTION_LINE_MODE);
	bSpecialFunctionMode=MODE_PRODUCTION_LINE;
	//�q�LI2C�]�m�{�b��mode�Oproduct_mode
	//vSubMcuSendSpecialMode(MODE_PRODUCTION_LINE);//130309ma02    //130313ma01
}

BYTE bProductIonCount = 0;   //130415ma01
//product line mode �C��step�ҹ�{���\��
void vProductionLineModeKeyProcess(void)
{
	//BOOL fgBlue3State = FALSE;//130309ma01
	//BOOL fgBlue6State = FALSE;//130309ma01
	//BYTE bReadEepromValue;  //130313ma02  //130316ma01
	
	switch(bModeState)	//130306ra01
		{
		case 1:
			if(bIRKey == IR_TOUCH_TIMER)  //130320ma02
				{
				//all lights off
				vDisplay7segLedAndTouchLedAllOff();//130419gr01
				//vDisplay7segLedAllOff();//130419gr01
				//child lock sign lights up
				vDisplayLEDChildLockSignOn();
				//set digital indication display Version("Major Version No. of Main MCU") Number
				vDisplay7SegShowDecNumOn(MCU_FIRMWARE_VERSION_UNIT);//130309ma02
				//update touch led state all off
				//vDisplayLEDAllOff();//130419gr01

				//buzzer_driver(Pi)
				//vBuzzerOutput(PI);	//130313le03
				//bModeState++;	//130306ra01
				goto MODE_STATE;  //130316ma01
				//bModeTimeCount=0;	//130306ra01 //130309ma02
				}
			break;
		case 2:
			if(bIRKey == IR_TOUCH_RESET)
				{
				//child lock sign off
				vDisplayLEDChildLockSignOff();
				//set digital indication display Version("Minor Version No. of Main MCU") Number
				vDisplay7SegShowDecNumOn(MCU_FIRMWARE_VERSION_DECIMAL);//130309ma02  //130402ma01  //130427ma01
				//update touch led state, unit replacing lights up
 				vDisplayLEDPCIReplacingOn();
				//buzzer_driver(Pi);
				//vBuzzerOutput(PI);	//130313le03
				//bModeState++;	//130306ra01
				goto MODE_STATE;  //130316ma01
				//bModeTimeCount=0;	//130306ra01  //130309ma02
				}
			break;
		case 3:
			if((bIRKey == IR_TOUCH_HORIZONTAL_OSCILLATING) && fgProductModeTimeStatus) //130309ma02   //130320ma02
				{
				fgProductModeTimeStatus =FALSE;//130309ma02
				//filter clean lights up
				vDisplayLEDFilterCleanOn();
				//update touch led state, unit replacing off
 				vDisplayLEDPCIReplacingOff();
				//�q�LI2C Read leak current of ion sensor judgement
				//vSubMcuReadIonLeakCurrentOkCount(LEAKCURRENTJUDGMENTTIME);//130309ma02  //130309ma03
				//130309ma01***
				//130313ma02***
				if(bProductIonCount > 1) //130316ma01   //130415ma01
					{
					bProductIonCount = 0;   //130415ma01
					//set digital indication display Version("Major Version No. of Sub MCU") Number
					vDisplay7SegShowDecNumOn(MCU_FIRMWARE_VERSION_UNIT);//130309ma02
					//buzzer_driver(Pi);
					//vBuzzerOutput(PI);
					//update touch led state, air volume indication 1 lights up
					vDisplayLEDAirVolume1On();
					//bModeState++;	//130306ra01
					goto MODE_STATE;  //130316ma01
					}
				  
				//130313ma02&&&
				/*if(fgProductModeIonDeltaVoff)
					{
					fgProductModeIonDeltaVoff = FALSE;
					bModeState++;
					}*/  //130312ma01
				//130309ma01&&&
				//bModeTimeCount = 0;//�p���ܶq�]��0   	//130306ra01  //130309ma02
				}
			break;
		case 4:
			if(bIRKey ==IR_TOUCH_VERTICAL_DIRECTION)   //130320ma02
				{
				//�q�Li2cŪ��hum_value(���)�Mtemp_value(�ū�)
				vSubMcuReadHumAdcValue();
				vSubMcuReadTempAdcValue();
				vSubMcuReadIonGenerationOkCount(IONGENERATIONJUDGMENTTIME);  //130313ma02
				/*  //130309ma01
				//if((hum_value >= 0x05) && (hum_value <= 0xcb))
					{
					//air volume indication 6 lights up
					vDisplayLEDAirVolume6On();
					fgBlue6State = TRUE;
					}
				 
				//if((temp_value >= 0x1c) && (temp_value <= 0xf4))
					{
					//air volume indication 3 lights up 
					vDisplayLEDAirVolume3On();
					fgBlue3State = TRUE;
					}
				*/   //130309ma01
				//PC:on
				vSubMcuPinPciPowerEnable(TRUE);//130309ma02
				 //child lock indication lights up
				 vDisplayLEDChildLockIndicationOn();
				//filter clean off
				vDisplayLEDFilterCleanOff();
				//update touch led state, air volume indication 1 off
				vDisplayLEDAirVolume1Off();
				//set digital indication display Version("Minor Version No. of Sub MCU") Number
				vDisplay7SegShowDecNumOn(MCU_FIRMWARE_VERSION_DECIMAL);//130309ma02    //130402ma01    //130427ma01
				//buzzer_driver(Pi);
				//vBuzzerOutput(PI);	//130313le03
				goto BUZZER_PI;	//130313le03
				}
			//130309ma01***
			/*if((fgProductModeBlue3State==TRUE) && (fgProductModeBlue6State==TRUE)) 
				{
				bModeState++;	//130306ra01
				//bModeTimeCount=0; //130306ra01 
				fgProductModeBlue3State = FALSE; 
				fgProductModeBlue6State = FALSE;
				}*/  //130312ma01
			//130309ma01&&&
			break;
		case 5:
			if(bIRKey == IR_NEXT_STEP)   //130313ma02
				{
				//�q�LI2C Read(product_ion_cnt)  
				//vSubMcuReadIonGenerationOkCount(IONGENERATIONJUDGMENTTIME);//130309ma02   //130309ma03  //130313ma02
				//130309ma01***
				//130313ma02***
				if(bProductIonCount)  //130316ma01   //130415ma01
					{
					//update touch led state, air volume indication Turbo(purple) lights up
					vDisplayLEDAirVolume9On();
					bModeState++;	//130306ra01
					}
				//130313ma02&&& 
				/*if(fgProductModeIonDeltaV)
					{
					fgProductModeIonDeltaV = FALSE;
					bModeState++;
					}*/  //130312ma01
				//130309ma01&&&
				//watch (red) lights up
				vDisplayLEDWatchRedOn();
				//child lock indication off
				vDisplayLEDChildLockIndicationOff();
				//air volume indication 3 lights up 
				vDisplayLEDAirVolume3Off();  //130313ma02
				//air volume indication 6 lights up
				vDisplayLEDAirVolume6Off();  //130313ma02  //130314ma02
				//set digital indication display 1
				vDisplay7SegShowDecNumOn(1);//130309ma02
				//buzzer_driver(Pi)
				//vBuzzerOutput(PI);	//130313le03
				goto BUZZER_PI;	//130313le03
				//bModeTimeCount = 0;	//130306ra01  //130309ma02
				}
			break;
		case 6:	
			if((bIRKey == IR_WATCH_MODE) || (bIRKey == IR_TOUCH_WATCH_MODE))   //130320ma02
				{
				//PC:off 
				vSubMcuPinPciPowerEnable(FALSE);//130309ma02
				//set FM:off power:off   
				//vFanPower(FALSE);//130309ma02   	//130422ma01
				//fgFanPowerOn=FALSE;
				//all lights off
				//vDisplay7segLedAllOff();//130419gr01
				//buzzer_driver(Pi-);
				//vBuzzerOutput(PI_LONG);	//130313le03
				//update touch led state all off;
				//vDisplayLEDAllOff();//130419gr01
				vSubMcuSendSpecialMode(MODE_NORMAL);	//130422ma01
				vDisplay7segLedAndTouchLedAllOff();//130419gr01

				vBuzzerOutput(PI_LONG);  //130316ma01
				bModeState++;   //130403ma01
				}
			break;
		default:
			break;
		}
	return;
//130316ma01***
	MODE_STATE: 
	bModeState++;
 //130316ma01&&&		
	BUZZER_PI:	//130313le03***
	vBuzzerOutput(PI);
	//130316ma01
}
#endif
