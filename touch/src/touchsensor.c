#define _TOUCH_SENSOR_C
#include "general.h"

#ifdef TOUCH_SENSOR_FUNCTION
//////////////////////////////////////////////////////////////////
//	About Touch LED process.
//////////////////////////////////////////////////////////////////
//Register-0x000e:1 1 1 1 1 1 1 1 led2 led3 led4 led5 led6 led7 led8 led9, when hight 8 bits are"1":output;are"0":input
//Register-0x000f:0 0 0 0 0 1 1 1 0 0 0 0 0 pci_led 0 led1,bit11~bit15 and bit3~bit7 are reserred, only when bit8~bit10 are"1",:output;are"0":input
#define LED_AIR_VOL2_TO_9_CONTROL_ADDR	0x0e	//130123gr01
#define LED_AIR_VOL1_PCI_CONTROL_ADDR	0x0f	//130123gr01

#define SET_TOUCH_IC_GPIO0_TO_7_OUTPUT_HIGH	0xff	//130123gr01
#define SET_TOUCH_IC_GPIO8_TO_10_OUTPUT_HIGH	0x07	//130123gr01

//bit	15	14	13	12	11	10	9	8	7	6	5	4	3	2	1	0
//LED	LEDTubeWhite					PCI		air1	air2	air3	air4	air5	air6	air7	air8	air9
//BYTE bLEDShowData1=0;	//Record 8 LEDs status.register 0x000e	//130314gr01***//130328gr01
//BYTE bLEDShowData2=0;	//Record 3 LEDs status.register 0x000f&Tube White	//130328gr01

BYTE bLEDBlinkTime=0;	// unit:0.1s	
BYTE bLEDBlinkCount=0;	// unit:0.1s	
//BYTE bLEDBlinkData1=0;	//130328gr01
//BYTE bLEDBlinkData2=0;	//130328gr01

BYTE bLEDOnTime=0;
//BYTE bLEDOnTimeCount=0;//130314gr01&&&					// 130315ja01
//BYTE bLEDAutoOffData1=0; 130328gr01
//BYTE bLEDAutoOffData2=0; //130328gr01



//////////////////////////////////////////////////////////////////
//	About Touch Key process.
//////////////////////////////////////////////////////////////////
#define	TOUCH_FRESH_DATA_BIT		0x80	//FreshDat is 1, has new report.//130417gr01
#define	TOUCH_STRIP_STATUS_BIT	0x70	//bit12~bit14 are strip ststus.//130417gr01
#define	TOUCH_STRIP_POSITION_BIT	0x07FF	//low 11 bits are strip position.
#define	TOUCH_STRIP_KEY_MAX_VALUE	0x07FF
#define 	TOUCH_STRIP_STEP			34	//130327JA01
#define	TOUCH_STRIP_VALUE_DIVIDE	(TOUCH_STRIP_KEY_MAX_VALUE/TOUCH_STRIP_STEP)	//130305gr01

#define TOUCH_IS_PRESSING_3S	120	// 25ms*120=3000ms=3second	//130123gr02

//#define TOUCH_REGISTER_STRIPS_KEY		0x0106	//130123gr02 //130419gr01
//#define TOUCH_REGISTER_BUTTON_KEY	0x0109	//130123gr02 //130419gr01
#define TOUCH_REGISTER_STRIPS_KEY_HIGH		0x01	//130123gr02//130419gr01
#define TOUCH_REGISTER_STRIPS_KEY_LOW		0x06	//130123gr02//130419gr01

#define TOUCH_REGISTER_BUTTON_KEY_HIGH	0x01	//130123gr02//130419gr01
#define TOUCH_REGISTER_BUTTON_KEY_LOW	0x09	//130123gr02//130419gr01

#define DATA_ENABLE_AND_ATTENTION_MODE 0x07 //130326gr02	//130417gr01

#define READ_TOUCH_REGISTER_STRIPS_KEY		0x06	//130123gr02 //130417gr01
#define READ_TOUCH_REGISTER_BUTTON_KEY	0x09	//130123gr02 //130417gr01


//130417gr01***
#define TOUCH_BUTTON_1	0x02 
#define TOUCH_BUTTON_2	0x04
#define TOUCH_BUTTON_3	0x10 
#define TOUCH_BUTTON_4	0x20 
#define TOUCH_BUTTON_5	0x40
#define TOUCH_BUTTON_6	0x80 

#define TOUCH_BUTTON_7	0x24
#define TOUCH_BUTTON_8	0x44
#define TOUCH_BUTTON_9	0x60
//130417gr01&&&
BOOL fgTouchInitial=TRUE; //True is mean touch IC is initialing.	//130305gr01
BYTE bTouchMultiKeyMode=IR_TOUCH_NONE;//130123gr02
BYTE bTouchMultiKeyCount=0;//130123gr02

BOOL fgTouchIsFirstPress=FALSE; //130326gr01

//130123gr02***
/*//130305gr01***
const WORD TouchRegisterInitialTable[][2]=
	{
	{0x0000,	0x0007},	//{address,data}
	{0x0001,	0x0004}, 
	{0x0002,	0x0032},
	{0x0004,	0xF600},
	{0x0008,	0x01FF},
	{0x000D,	0x0200},
	{0x000F,	0x0700},
	{0x0010,	0x3A3A},
	{0x0011,	0x3A3A}, 
	{0x0012,	0x3A3A}, 
	{0x0013,	0x3234},
	{0x0014,	0x3E32}, 
	{0x0015,	0x363C},
	{0x0016,	0x3430},
	{0x0017,	0x3434},
	{0x001E,	0x0000},
	{0x0022,	0x07FF},
	{0x0023,	0x0000},
	{0x0024,	0x5656}, 
	{0x0025,	0x5656},
	{0x0026,	0x5656},
	{0x0027,	0x5656}, 
	{0x0028,	0x5656},
	{0x0029,	0x5656},
	{0x002B,	0x0000}, 
	{0x000E,	0x0000},
	{0x00FF,	0x00FF}
	};	//130123gr02&&&
*/
//130307gr01***
const BYTE TouchRegisterInitialAdressTable[] =
{
	0x00,
	0x01,
	0x02,
	0x03,
	0x04, 
	0x08,
	0x0D,
	0x0F, 
	0x10,
	0x11,
	0x12,
	0x13,
	0x14,
	0x15,
	0x16,
	0x17,
	0x1E,
	0x22,
	0x23, 
	0x24,
	0x25,
	0x26,
	0x27,
	0x28,
	0x29,
	0x2B,
	0x0E,
	0xFF
}; //130307gr01&&&
//130415gr01***
const BYTE TouchRegisterInitialDataTableHigh[]=
{
	0x00,
	0x01,//130326gr02
	0x00,
	0x03,
	0xf6, 
	0x01,
	0x02, 
	0x07, 
	0xaa,
	0xaa,
	0xaf, 
	0xaf,
	0x89, 
	0x35, 
	0xa0, 
	0xb5, 
	0x00,
	0x07, 
	0x00,
	0x56, 
	0x56, 
	0x56,
	0x56, 
	0x56, 
	0x56,
	0x00, 
	0x00,
	0xff   //130307gr01
};
const BYTE TouchRegisterInitialDataTableLow[]=
{
	0x07,
	0x04,//130326gr02
	0x32,
	0x84,
	0x00, 
	0xff,
	0x00, 
	0x00, 
	0xaa,
	0xaa,
	0xaa, 
	0xaf,
	0xb7, 
	0xa0, 
	0xa7, 
	0xa0, 
	0x00,
	0xff, 
	0x00,
	0x56, 
	0x56, 
	0x56,
	0x56, 
	0x56, 
	0x56,
	0x00, 
	0x00,
	0xff    //130307gr01
};


/*
const WORD TouchRegisterInitialDataTable[] =
{
	0x0007,
	0x0104,//130326gr02
	0x0032,
	0x0384,
	0xf600, 
	0x01ff,
	0x0200, 
	0x0700, 
	0xaaaa,
	0xaaaa,
	0xafaa, 
	0xafaf,
	0x89b7, 
	0x35a0, 
	0xa0a7, 
	0xb5a0, 
	0x0000,
	0x07ff, 
	0x0000,
	0x5656, 
	0x5656, 
	0x5656,
	0x5656, 
	0x5656, 
	0x5656,
	0x0000, 
	0x0000,
	0xffff    //130307gr01
};//130305gr01&&&
*/
//130415gr01&&&




//////////////////////////////////////////////////////////////////
//	About Hot Key process.
//////////////////////////////////////////////////////////////////
#define MODE_KEY_COL_MAX_NUM		7	//130123gr03
#define MODE_KEY_ROW_MAX_NUM	4
BYTE bIRCodeData[6]={IR_NONE,IR_NONE,IR_NONE,IR_NONE,IR_NONE,IR_NONE};  //receive key and storage //130123gr03***
#define ARRAY_2_TO_ARRAY_1	//130416ha01
#ifdef ARRAY_2_TO_ARRAY_1	//130416ha01***
const BYTE AllModeKey[MODE_KEY_COL_MAX_NUM*MODE_KEY_ROW_MAX_NUM] =
	{
	IR_TOUCH_HORIZONTAL_OSCILLATING,	IR_TOUCH_HORIZONTAL_RESET,	IR_TOUCH_HORIZONTAL_OSCILLATING,	IR_TOUCH_HORIZONTAL_RESET,	IR_TOUCH_HORIZONTAL_OSCILLATING,	IR_TOUCH_HORIZONTAL_RESET,	IR_PRODUCTION_LINE_MODE,	
	IR_TOUCH_VERTICAL_DIRECTION,		IR_TOUCH_VERTICAL_RESET,		IR_TOUCH_VERTICAL_DIRECTION,		IR_TOUCH_VERTICAL_RESET,		IR_TOUCH_VERTICAL_DIRECTION,		IR_TOUCH_VERTICAL_RESET,		IR_SERVICE_MONITOR_MODE,
	IR_NONE,							IR_NONE,						IR_TOUCH_HORIZONTAL_OSCILLATING,	IR_AIR_VOLUME_CONTROL_HI,	IR_AIR_VOLUME_CONTROL_HI,		IR_AIR_VOLUME_CONTROL_HI,	IR_MONITOR_MODE,
	IR_NONE,							IR_NONE,						IR_TOUCH_VERTICAL_DIRECTION,		IR_ION_MODE,					IR_ION_MODE,						IR_ION_MODE,					IR_AUTO_RESTART_FUNCTION
	};//130123gr03&&&
#else	//130416ha01&&&
const BYTE AllModeKey[][MODE_KEY_COL_MAX_NUM] =
	{
	{IR_TOUCH_HORIZONTAL_OSCILLATING,	IR_TOUCH_HORIZONTAL_RESET,	IR_TOUCH_HORIZONTAL_OSCILLATING,	IR_TOUCH_HORIZONTAL_RESET,	IR_TOUCH_HORIZONTAL_OSCILLATING,	IR_TOUCH_HORIZONTAL_RESET,	IR_PRODUCTION_LINE_MODE},	
	{IR_TOUCH_VERTICAL_DIRECTION,		IR_TOUCH_VERTICAL_RESET,		IR_TOUCH_VERTICAL_DIRECTION,		IR_TOUCH_VERTICAL_RESET,		IR_TOUCH_VERTICAL_DIRECTION,		IR_TOUCH_VERTICAL_RESET,		IR_SERVICE_MONITOR_MODE},
	{IR_NONE,						IR_NONE,						IR_TOUCH_HORIZONTAL_OSCILLATING,	IR_AIR_VOLUME_CONTROL_HI,	IR_AIR_VOLUME_CONTROL_HI,		IR_AIR_VOLUME_CONTROL_HI,	IR_MONITOR_MODE},
	{IR_NONE,						IR_NONE,						IR_TOUCH_VERTICAL_DIRECTION,		IR_ION_MODE,					IR_ION_MODE,						IR_ION_MODE,					IR_AUTO_RESTART_FUNCTION},
#ifdef FULL_FUNCTION //			//130316gr01***
	{IR_TOUCH_HORIZONTAL_OSCILLATING,	IR_TOUCH_VERTICAL_HORIZONTAL,	IR_TOUCH_HORIZONTAL_OSCILLATING,	IR_TOUCH_VERTICAL_HORIZONTAL,	IR_TOUCH_HORIZONTAL_OSCILLATING,	IR_TOUCH_VERTICAL_HORIZONTAL,	IR_SPEED_UP_MODE},
	{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}
#endif //130316gr01&&&
	};//130123gr03&&&
#endif	//130416ha01


//130314gr01***
//////////////////////////////////////////////////////////////////
//	About Touch LED process.
//////////////////////////////////////////////////////////////////
#define LED_AIR_VOLUME1_AND_PCI_REPLACEING_BIT	0x07
//#define LED_TUBE_WHITE_BIT	0x80		// 130401jac01

//Put in 100ms.
void vLEDDisplay(void)
{
	static BYTE bLastLEDNumControl1=0;
	static BYTE bLastLEDNumControl2=0;
	//For blink control.
	if(bLEDOnTime==0)//130413gr02***
		{
		bLEDBlinkCount++;
		if(bLEDBlinkCount==bLEDBlinkTime)
			{
			bLEDBlinkCount=0;
			bLEDShowData1^=bLEDBlinkData1;
			bLEDShowData2^=bLEDBlinkData2;
			}
		}

	//For auto off control.
	else	//if(bLEDOnTime>0)
		{
		bLEDOnTime--;					// 130315ja01***
		if(bLEDOnTime==0)
			{
			bLEDShowData1&=(~bLEDAutoOffData1);//130402gr01
			bLEDShowData2&=(~bLEDAutoOffData2);//130402gr01
			//bLEDShowData1^=bLEDAutoOffData1;
			//bLEDShowData2^=bLEDAutoOffData2;
			bLEDAutoOffData1=0;
			bLEDAutoOffData2=0;
			//bLEDOnTime=250;
			}
		} //130413gr02&&&
#if 0	
	bLEDOnTimeCount++;
	if(bLEDOnTimeCount>bLEDOnTime)
		{
		bLEDShowData1^=bLEDAutoOffData1;
		bLEDShowData2^=bLEDAutoOffData2;
		bLEDAutoOffData1=0;
		bLEDAutoOffData2=0;
		}
#endif					// 130315ja01&&&
	if((bLastLEDNumControl1==bLEDShowData1)&&(bLastLEDNumControl2==bLEDShowData2))
		{return;}

/*		// 130401jac01
	//LED display about tube led.
	if(bLEDShowData2&LED_TUBE_WHITE_BIT)
		{
		vTubeLedON();
		}
	else
		{
		vTubeLedOFF();
		}
*/		// 130401jac01
	
	//LED display about all led.
	//vTouchICWriteCommand(LED_AIR_VOL2_TO_9_CONTROL_ADDR,((WORD)(bLEDShowData1))+SET_TOUCH_IC_GPIO0_TO_7_OUTPUT); //130415gr01
	//vTouchICWriteCommand(LED_AIR_VOL1_PCI_CONTROL_ADDR,((WORD)(bLEDShowData2))+SET_TOUCH_IC_GPIO8_TO_10_OUTPUT); //130415gr01
	vTouchICWriteCommand(LED_AIR_VOL2_TO_9_CONTROL_ADDR,SET_TOUCH_IC_GPIO0_TO_7_OUTPUT_HIGH,bLEDShowData1); //130415gr01
	vTouchICWriteCommand(LED_AIR_VOL1_PCI_CONTROL_ADDR,SET_TOUCH_IC_GPIO8_TO_10_OUTPUT_HIGH,bLEDShowData2); //130415gr01

	bLastLEDNumControl1=bLEDShowData1;
	bLastLEDNumControl2=bLEDShowData2;
}
//130314gr01&&&



//130123gr01***
//Register-0x000e:1 1 1 1 1 1 1 1 led2 led3 led4 led5 led6 led7 led8 led9, when hight 8 bits are"1":output;are"0":input
//Register-0x000f:0 0 0 0 0 1 1 1 0 0 0 0 0 pci_led 0 led1,bit11~bit15 and bit3~bit7 are reserred, only when bit8~bit10 are"1",:output;are"0":input
void vDisplayLEDAirVolumeOn(BYTE bLEDNUM )//130415gr01
{
	//vDisplayLEDAirVolume1to9Off();//130328gr01
	bLEDOnTime=0;//130417gr02
	switch((bLEDNUM+3)/4) //130415gr01
		{
		case 1:
			vDisplayLEDAirVolume1to1On();//130328gr01
			break;
		case 2:
			vDisplayLEDAirVolume1to2On();
			break;
		case 3:
			vDisplayLEDAirVolume1to3On();
			break;
		case 4:
			vDisplayLEDAirVolume1to4On();
			break;
		case 5:
			vDisplayLEDAirVolume1to5On();
			break;
		case 6:
			vDisplayLEDAirVolume1to6On();
			break;
		case 7:
			vDisplayLEDAirVolume1to7On();
			break;
		case 8:
			vDisplayLEDAirVolume1to8On();
			break;
		case 9:
			vDisplayLEDAirVolume1to9On();
			break;
 		}
 }
void vDisplayLEDAirVolumeAutoOff(BYTE bLEDNum,BYTE bTime)//130415gr01
{
	switch((bLEDNum+3)/4) //130415gr01
		{
		case 1:
			vDisplayLEDAirVolume1to1AutoOff(bTime);
			break;
		case 2:
			vDisplayLEDAirVolume1to2AutoOff(bTime);
			break;
		case 3:
			vDisplayLEDAirVolume1to3AutoOff(bTime);
			break;
		case 4:
			vDisplayLEDAirVolume1to4AutoOff(bTime);
			break;
		case 5:
			vDisplayLEDAirVolume1to5AutoOff(bTime);
			break;
		case 6:
			vDisplayLEDAirVolume1to6AutoOff(bTime);
			break;
		case 7:
			vDisplayLEDAirVolume1to7AutoOff(bTime);
			break;
		case 8:
			vDisplayLEDAirVolume1to8AutoOff(bTime);
			break;
		case 9:
			vDisplayLEDAirVolume1to9AutoOff(bTime);
			break;
		}
} //130328gr02&&&
void vDisplayLEDAirVolume1to9Off(void) //130416gr01***
{
	bLEDOnTime=0;
	LED_AIR_VOLUME_1_BIT=0;
	bLEDShowData1=0;
}	//130416gr01&&&

#if 0			
void vLEDBlink(BYTE bLEDNum,BYTE bTime)
{
	switch(bLEDNum)
		{
		case 1:
			vDisplayLEDAirVolume1BlinkOn(bTime);
			break;
		case 2:
			vDisplayLEDAirVolume1to2BlinkOn(bTime);
			break;
		case 3:
			vDisplayLEDAirVolume1to3BlinkOn(bTime);
			break;
		case 4:
			vDisplayLEDAirVolume1to4BlinkOn(bTime);
			break;
		case 5:
			vDisplayLEDAirVolume1to5BlinkOn(bTime);
			break;
		case 6:
			vDisplayLEDAirVolume1to6BlinkOn(bTime);
			break;
		case 7:
			vDisplayLEDAirVolume1to7BlinkOn(bTime);
			break;
		case 8:
			vDisplayLEDAirVolume1to8BlinkOn(bTime);
			break;
		case 9:
			vDisplayLEDAirVolume1to9BlinkOn(bTime);
			break;
 		}
}
#endif


//130308Me01***
#define DisplayLEDAirVolume1	1
#define DisplayLEDAirVolume2	6
#define DisplayLEDAirVolume3	11
#define DisplayLEDAirVolume4	16
#define DisplayLEDAirVolume5	21
#define DisplayLEDAirVolume6	26
#define DisplayLEDAirVolume7	31
#define DisplayLEDAirVolume8	36
#define DisplayLEDAirVolume9	41
#define DisplayAllOff			46
#define NextDisplay				50
BYTE bDangerTimerCnt=0;

//Put in 100ms.
void vDisplayLEDAirVolumeIndicationTimer(void)
{
	if(fgDisplayLEDAirVolume1To9==FALSE)
		{
		bDangerTimerCnt=0;	//130413Me01	
		return;
		}

	bDangerTimerCnt++;
	switch(bDangerTimerCnt)
		{
		case DisplayLEDAirVolume1:
			vDisplayLEDAirVolume1to9Off();		//130418Me02
			vDisplayLEDAirVolume1On();
			break;
		case DisplayLEDAirVolume2:
			vDisplayLEDAirVolume2On();
			break;
		case DisplayLEDAirVolume3:
			vDisplayLEDAirVolume3On();
			break;
		case DisplayLEDAirVolume4:
			vDisplayLEDAirVolume4On();
			break;
		case DisplayLEDAirVolume5:
			vDisplayLEDAirVolume5On();
			break;
		case DisplayLEDAirVolume6:
			vDisplayLEDAirVolume6On();
			break;
		case DisplayLEDAirVolume7:
			vDisplayLEDAirVolume7On();
			break;
		case DisplayLEDAirVolume8:
			vDisplayLEDAirVolume8On();
			break;
		case DisplayLEDAirVolume9:
			vDisplayLEDAirVolume9On();
			break;
		case DisplayAllOff:
			vDisplayLEDAirVolume1to9Off();	//130413Me01
			break;
		case NextDisplay:
			bDangerTimerCnt=0;
			break;
		default:
			break;
		}
}
//130308Me01&&&



//130123gr04***
//#define TOUCH_LED_BRIGHT_REGISTER_VALUE 0x5656 //130415gr01
//#define TOUCH_LED_DIM_REGISTER_VALUE	0x4848 //130415gr01
#define TOUCH_LED_BRIGHT_REGISTER_VALUE_HIGH 0x56 //130415gr01
#define TOUCH_LED_BRIGHT_REGISTER_VALUE_LOW 0x56 //130415gr01

#define TOUCH_LED_DIM_REGISTER_VALUE_HIGH 0x48 //130415gr01
#define TOUCH_LED_DIM_REGISTER_VALUE_LOW 0x48 //130415gr01

// 0x24 control brightness of LED9 and led8;
// 0x25 control brightness of LED7 and led6;
// 0x26 control brightness of LED5 and led4;
// 0x27 control brightness of LED3 and led2;
// 0x28 control brightness of LED1, 
// 0x29 control brightness of PCI_LED,PCI LED do not need adjust.
#define TOUCH_LED_CONTROL_REGISTER_START_ADDRESS	0x24


void TouchLEDBrightnessAdjust(BYTE fgLEDIsBright)
{
	BYTE i;
	if(fgLEDIsBright)	//LED Bright
		{
		for(i=0;i<5;i++)//130409gr01
			{
			//vTouchICWriteCommand(TOUCH_LED_CONTROL_REGISTER_START_ADDRESS+i,TOUCH_LED_BRIGHT_REGISTER_VALUE); //130415gr01
			vTouchICWriteCommand(TOUCH_LED_CONTROL_REGISTER_START_ADDRESS+i,TOUCH_LED_BRIGHT_REGISTER_VALUE_HIGH,TOUCH_LED_BRIGHT_REGISTER_VALUE_LOW); //130415gr01
			}
		}
	else		//LED Dim
		{
		for(i=0;i<5;i++)//130409gr01
			{
			//vTouchICWriteCommand(TOUCH_LED_CONTROL_REGISTER_START_ADDRESS+i,TOUCH_LED_DIM_REGISTER_VALUE); //130415gr01
			vTouchICWriteCommand(TOUCH_LED_CONTROL_REGISTER_START_ADDRESS+i,TOUCH_LED_DIM_REGISTER_VALUE_HIGH,TOUCH_LED_DIM_REGISTER_VALUE_LOW); //130415gr01
			}
		}
}


//130123gr02***
//////////////////////////////////////////////////////////////////
//	About Touch Key process.
//////////////////////////////////////////////////////////////////
static BYTE bTouchStatusMechine=0;
void vInitialTouchSensor(void)	//130302gr01***//130305gr01***//130307gr01***//130308gr01***
{
	static BYTE i=0;
	BYTE bTouchRegisterInitialData;
	if(fgTouchInitial==FALSE)
		{
		return;
		}

	switch(bTouchStatusMechine)
		{
		case 0:		//Check INT pin is low then continue.
			if(fgTouchIntDIS())
				break;
			bTouchStatusMechine++;
			break;
		case 1:		//If I2C queue is full, don't send command.
			if(fgI2CCommandBusy||(bMixQueueRemain<5))	//130322sh01
				break;
			bTouchStatusMechine++;
			//break;	//130322sh01
		case 2:		//If Touch initial table is 0xff, it means the end.
			if(TouchRegisterInitialAdressTable[i]==0XFF)
				{
				bTouchStatusMechine=3;
				i=0;
				}
			else
				{	//Get initial table data, then send to Touch IC.
				bTouchRegisterInitialData=TouchRegisterInitialAdressTable[i];
				//vTouchICWriteCommand(bTouchRegisterInitialData,TouchRegisterInitialDataTable[i]);//130415gr01
				//vTouchICWriteCommand(bTouchRegisterInitialData,TouchRegisterInitialDataTableHigh[i],TouchRegisterInitialDataTableLow[i]);//130415gr01	//130418sh03	&&&		
				fgI2CCommandBusy=TRUE;//130418sh03***
				vPinI2cBusyEnable();//130315sh01
				vI2CWriteCommand(I2C_WRITE_TO_TOUCH,bTouchRegisterInitialData,TouchRegisterInitialDataTableHigh[i],TouchRegisterInitialDataTableLow[i]);
				i++;
				bTouchStatusMechine=1;
				}
			break;
		case 3:		//Dummy read, the specification.
			vTouchICReadCommand(TOUCH_REGISTER_STRIPS_KEY_HIGH,TOUCH_REGISTER_STRIPS_KEY_LOW);	//dummy read	,it must be 0x0106.	//130419gr01		
			bTouchStatusMechine++;			
			break;
		case 4:		//If INT is high, it means the initial is finish.
			if(fgTouchIntEN())
				{
				i++;
				if(i>250)
					{
					bTouchStatusMechine++;
					}
				break;
				}

			if(fgIsLightOffFunction())	//130410le01***
				{
				vDisplayLEDDim();
				}	//130410le01&&&
		default:
			bTouchStatusMechine=0;
			i=0;
			fgTouchInitial=FALSE;
			break;
		}
}	//130305gr01&&&//130307gr01&&&&130308gr01&&&

void vEventTouchSensorInterrupt(void)
{
	vTouchICReadCommand(TOUCH_REGISTER_STRIPS_KEY_HIGH,TOUCH_REGISTER_STRIPS_KEY_LOW); //130419gr01
	vTouchICReadCommand(TOUCH_REGISTER_BUTTON_KEY_HIGH,TOUCH_REGISTER_BUTTON_KEY_LOW); //130419gr01
}

//130417gr01***
#define STRIP_LOW_BYTE	bTouchDataRegister[0]
#define STRIP_HIGH_BYTE	bTouchDataRegister[1]
#define BUTTON_HIGH_BYTE bTouchDataRegister[2]

void vEventTouchRead(BYTE bAddrLow, BYTE bDataHigh,BYTE bDataLow)
{
	BYTE bNowKeyCode=IR_TOUCH_NONE;
	BYTE bNowKeyCodeSub=IR_TOUCH_NONE;	//just for air volume 1~33		//130310ha01
	static BYTE bLastStripStatus=0; //130326gr01
	static BOOL bLastButtonKeyIsPress=FALSE; //130418gr01
	BYTE btemp;
	switch(bAddrLow)
		{
		default:
			return;
		case READ_TOUCH_REGISTER_STRIPS_KEY:
			STRIP_HIGH_BYTE=bDataHigh;
			STRIP_LOW_BYTE=bDataLow;
			return;
		case READ_TOUCH_REGISTER_BUTTON_KEY:
			BUTTON_HIGH_BYTE=bDataHigh;
			break;
		case READ_TOUCH_REGISTER_INTERFACE_CONFIGURATION: //130326gr02***
			if((bDataLow&DATA_ENABLE_AND_ATTENTION_MODE)==0) //if bit0~bit2 is 0,stand for touch is reseted
				{
				fgTouchInitial=TRUE;
				}
			return;//130326gr02&&&	
		}

	btemp=(STRIP_HIGH_BYTE&TOUCH_STRIP_STATUS_BIT);
	if(btemp!=0)
		{
		if(bLastStripStatus!=btemp)//130326gr01***
			{
			fgTouchIsFirstPress=TRUE;
			}
		else
			{
			fgTouchIsFirstPress=FALSE;
			} //130326gr01&&&
		bLastStripStatus=btemp;//130326gr01
		//wStripKeyValue=((STRIP_LOW_BYTE*0x100+STRIP_HIGH_BYTE)&TOUCH_STRIP_POSITION_BIT);
		wTouchStripsRegister=wTouchStripsRegister&TOUCH_STRIP_POSITION_BIT;
		
		bNowKeyCode=IR_TOUCH_AIR_VOLUME;		//130310ha01
		bNowKeyCodeSub=(wTouchStripsRegister/TOUCH_STRIP_VALUE_DIVIDE)+1;		//air volume is 1~33. Add 1 can makesure it's 1~34.	//130310ha01
		if(bNowKeyCodeSub>AIR_VOLUME_MAX)	//if air volume key is 34, let it is 33.	//130310ha01
			{
			bNowKeyCodeSub=AIR_VOLUME_MAX;	//130310ha01
			}

		if((bNowKeyCodeSub!=bAirVolume)&&(BUTTON_HIGH_BYTE==0)) //130413gr03***//130418gr01
			{
			vPutEventQueue(EVENT_IR, bNowKeyCode,bNowKeyCodeSub);	
			} //130413gr03&&&
		return;			
		}
	else
		{
		bLastStripStatus=0;
		fgTouchIsFirstPress=FALSE;
		}

	
	switch(BUTTON_HIGH_BYTE)
		{
		case TOUCH_BUTTON_1:
			bNowKeyCode=IR_TOUCH_POWER;
			break;
			
		case TOUCH_BUTTON_2:
			bNowKeyCode=IR_TOUCH_RESET;
			break;
			
		case TOUCH_BUTTON_3:
			bNowKeyCode=IR_TOUCH_WATCH_MODE;
			break;
			
		case TOUCH_BUTTON_4:
			bNowKeyCode=IR_TOUCH_HORIZONTAL_OSCILLATING;
			break;
			
		case TOUCH_BUTTON_5:
			bNowKeyCode=IR_TOUCH_VERTICAL_DIRECTION;
			break;
			
		case TOUCH_BUTTON_6:
			bNowKeyCode=IR_TOUCH_TIMER;
			break;

		case TOUCH_BUTTON_7:
			bNowKeyCode=IR_TOUCH_HORIZONTAL_RESET;
			break;
			
		case TOUCH_BUTTON_8:
			bNowKeyCode=IR_TOUCH_VERTICAL_RESET;
			break;

		case TOUCH_BUTTON_9:
			bNowKeyCode=IR_TOUCH_VERTICAL_HORIZONTAL;
			break;
		}

	if((bNowKeyCode!=IR_TOUCH_HORIZONTAL_RESET)&&(bNowKeyCode!=IR_TOUCH_VERTICAL_HORIZONTAL)) //130418gr01***
		{
		if(bPlugInACPowerTimeCount>POWER_UP_5S)
			{
			if((bLastButtonKeyIsPress==TRUE)&&(BUTTON_HIGH_BYTE!=0))
				{
				bTouchMultiKeyMode=IR_TOUCH_NONE;
				bTouchMultiKeyCount=0;
				return;
				}
			}
		} //130418gr01&&&
			
	//if((bNowKeyCode==IR_TOUCH_NONE)&&(bTouchMultiKeyMode!= IR_TOUCH_NONE)) //130309gr03
	if(bNowKeyCode!=bTouchMultiKeyMode) //130309gr03
		{				
		if(bTouchMultiKeyCount<=TOUCH_IS_PRESSING_3S)
			{	//short press key
			if(bTouchMultiKeyMode!=IR_TOUCH_NONE)//			//130316gr01***
				{
				vPutEventQueue(EVENT_IR, bTouchMultiKeyMode,0);
				}	//130316gr01&&&		
			bTouchMultiKeyMode= IR_TOUCH_NONE;
			bTouchMultiKeyCount=0;
			}
		}

	switch(bNowKeyCode)
		{
		case IR_TOUCH_NONE:
			break;
		case IR_TOUCH_TIMER:
		case IR_TOUCH_VERTICAL_HORIZONTAL:
		case IR_TOUCH_HORIZONTAL_RESET:
		case IR_TOUCH_RESET: //130307gr02
			bTouchMultiKeyMode=bNowKeyCode;
			bTouchMultiKeyCount=0;
			break;
		default:
			vPutEventQueue(EVENT_IR, bNowKeyCode,0);	//130310ha01
			break;
		}

	if(BUTTON_HIGH_BYTE==0)	//130418gr01***
		{
		bLastButtonKeyIsPress=FALSE;
		}
	else
		{
		bLastButtonKeyIsPress=TRUE;
		}	//130418gr01&&&
	
}
//130417gr01&&&

// Put in 25ms.
void vTouchMultiKeyCount(void)
{
	BYTE bNowMultiKey=IR_TOUCH_NONE;//130316gr01***
	if(bTouchMultiKeyMode!= IR_TOUCH_NONE)
		{
		bTouchMultiKeyCount++;
		if(bTouchMultiKeyCount>TOUCH_IS_PRESSING_3S)
			{
			switch(bTouchMultiKeyMode)//130307gr02***
				{
				case IR_TOUCH_TIMER:
					bNowMultiKey=IR_CHILD_LOCK;
					break;
				case IR_TOUCH_HORIZONTAL_RESET:
					bNowMultiKey=IR_DEMO_MODE;
					break;
				case IR_TOUCH_VERTICAL_HORIZONTAL:
					bNowMultiKey=IR_LIGHT_OFF_FUNCTION;
					break;
				case IR_TOUCH_RESET:
					bNowMultiKey=IR_FILTER_CLEANING;
					break;
				}	//130307gr02&&&
			vPutEventQueue(EVENT_IR,bNowMultiKey,0); //130316gr01&&&
			bTouchMultiKeyMode= IR_TOUCH_NONE;
			bTouchMultiKeyCount=0;
			}
		}
}	//130123gr02&&&



//////////////////////////////////////////////////////////////////
//	About Hot Key process.
//////////////////////////////////////////////////////////////////
void vExcuteHotkeyFunction(BYTE bModeKey)
{
	switch(bModeKey)
		{
#ifdef PRODUCTION_LINE_MODE_FUNCTION
		case IR_PRODUCTION_LINE_MODE:
#endif			
		case IR_SERVICE_MONITOR_MODE:
		case IR_MONITOR_MODE:
#ifdef FULL_FUNCTION //130316gr01***
		case IR_SPEED_UP_MODE:
#endif //130316gr01&&&
			if(bPlugInACPowerTimeCount<=POWER_UP_5S)
				{
				vPutEventQueue(EVENT_IR, bModeKey,0);
				}
			break;
		case IR_AUTO_RESTART_FUNCTION:
			vPutEventQueue(EVENT_IR, bModeKey,0);
			break;
		}
}

void vHotKeyInput(void) //130123gr03***
{
	BYTE  i,j;	//130327ha01
	bIRCodeData[0]=bIRCodeData[1];
	bIRCodeData[1]=bIRCodeData[2];
	bIRCodeData[2]=bIRCodeData[3];
	bIRCodeData[3]=bIRCodeData[4];
	bIRCodeData[4]=bIRCodeData[5];
	bIRCodeData[5]=bIRKey;

	//compare the storaged IR key and the hot key table,ok then transmit hot key value to tuner,NG do nothing.
#ifdef ARRAY_2_TO_ARRAY_1	//130416ha01***
	for(i=0; i<MODE_KEY_ROW_MAX_NUM ;i++)
		{
		if(bIRCodeData[MODE_KEY_COL_MAX_NUM-2] == AllModeKey[i* MODE_KEY_COL_MAX_NUM + MODE_KEY_COL_MAX_NUM-2])
			{
			for(j=(MODE_KEY_COL_MAX_NUM-3);;j--)
				{
				if(AllModeKey[i*MODE_KEY_COL_MAX_NUM+j]!=IR_NONE)	//130419le01
					{	//130419le01
					if(bIRCodeData[j]!=AllModeKey[i*MODE_KEY_COL_MAX_NUM+j])
						{
						break;
						}
					}	//130419le01
				if(j==0)
					{
					vExcuteHotkeyFunction(AllModeKey[i*MODE_KEY_COL_MAX_NUM+MODE_KEY_COL_MAX_NUM-1]);
					bIRCodeData[4]=IR_NONE;
					bIRCodeData[5]=IR_NONE;
					break;
					}
				}

			}
		}
#else	//130416ha01&&&
	for(i=0; i<MODE_KEY_ROW_MAX_NUM ;i++)
		{
		if(bIRCodeData[MODE_KEY_COL_MAX_NUM-2]==AllModeKey[i][MODE_KEY_COL_MAX_NUM-2])
			{
			for(j=(MODE_KEY_COL_MAX_NUM-3);;j--)
				{
				if(bIRCodeData[j]!=AllModeKey[i][j])
					{
					break;
					}
				if(j==0)
					{
					vExcuteHotkeyFunction(AllModeKey[i][MODE_KEY_COL_MAX_NUM-1]);
					bIRCodeData[4]=IR_NONE;
					bIRCodeData[5]=IR_NONE;
					break;
					}
				}

			}
		}
#endif	//130416ha01
#if 0	//130327ha01&&&
	for(i=0; i<MODE_KEY_ROW_MAX_NUM ;i++)
		{
#ifdef FULL_FUNCTION //130316gr01***
		if((AllModeKey[i][0]==0xff)&&(AllModeKey[i][1]==0xff))
#endif	//130316gr01&&&
		
		if((bIRCodeData[MODE_KEY_COL_MAX_NUM-2])==(AllModeKey[i][MODE_KEY_COL_MAX_NUM-2]))
			{
			if((bIRCodeData[MODE_KEY_COL_MAX_NUM-3])==(AllModeKey[i][MODE_KEY_COL_MAX_NUM-3]))
				{
				if((bIRCodeData[3])==(AllModeKey[i][3]))
					{
					if((bIRCodeData[2])==(AllModeKey[i][2])) //最少按四個Key才能進入
						{
//						if(	((AllModeKey[i][0]==IR_NONE)&&(AllModeKey[i][1]==IR_NONE)&&(AllModeKey[i][2]==bIRCodeData[2]))||
//							((AllModeKey[i][0]==IR_NONE)&&(AllModeKey[i][1]==bIRCodeData[1])&&(AllModeKey[i][2]==bIRCodeData[2]))||
//							((AllModeKey[i][0]==bIRCodeData[0])&&(AllModeKey[i][1]==bIRCodeData[1])&&(AllModeKey[i][2]==bIRCodeData[2])))
						if((AllModeKey[i][0]==IR_NONE)&&(AllModeKey[i][1]==IR_NONE))
							{
							goto EXECUTE_HOT_KEY;
							//vExcuteHotkeyFunction(AllModeKey[i][MODE_KEY_COL_MAX_NUM-1]);
							//bIRCodeData[5]=IR_NONE;
							}
						else if((AllModeKey[i][0]==IR_NONE))
							{
							if((AllModeKey[i][1]==bIRCodeData[1]))
								{
								goto EXECUTE_HOT_KEY;
								//vExcuteHotkeyFunction(AllModeKey[i][MODE_KEY_COL_MAX_NUM-1]);
								//bIRCodeData[5]=IR_NONE;
								}
							}
						else if((AllModeKey[i][0]==bIRCodeData[0]))
							{
							if(AllModeKey[i][1]==bIRCodeData[1])
								{
								goto EXECUTE_HOT_KEY;
								//vExcuteHotkeyFunction(AllModeKey[i][MODE_KEY_COL_MAX_NUM-1]);
								//bIRCodeData[5]=IR_NONE;
								}
							}
						}
					}
				}
			}
		//i++;
		}
	return;
EXECUTE_HOT_KEY:
	vExcuteHotkeyFunction(AllModeKey[i][MODE_KEY_COL_MAX_NUM-1]);
	bIRCodeData[5]=IR_NONE;
	return;
#endif	//130327ha01
}	//130123gr03&&&


#endif



