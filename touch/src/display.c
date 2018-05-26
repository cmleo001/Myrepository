#define _DISPLAY_C_
#include "general.h"

#ifdef DISPLAY_7SEG_FUNCTION

enum
{
	LED_ROW1_TURN
	,LED_ROW2_TURN
	,LED_ROW3_TURN
	,LED_ROW4_TURN
	,LED_ROW5_TURN
	,LED_ROW_MAX
};



//#define LED_7SEG_SHIFT_TIME_COUNT		3		// 3(ms)*5(Row)*66(Fram)=1s//130415jac01		

//BYTE bRow7SegLedShowData[5]={LED_OFF,LED_OFF,LED_OFF,LED_OFF,LED_OFF};			// 130328jac01***
//BYTE bRow7SegLedBlinkData[5]={LED_OFF,LED_OFF,LED_OFF,LED_OFF,LED_OFF};
//BYTE bRow7SegLedAutoOffData[3]={LED_OFF,LED_OFF,LED_OFF};						// 130328jac01&&&
BOOL fg7SegAutoOff=FALSE;					// 130315ja01
//BOOL fg7SegHexShow=FALSE;	//130423jac03
const BYTE bLedNumber[16]=
	{
	LED_7_SEGMENT_NUM0
	,LED_7_SEGMENT_NUM1
	,LED_7_SEGMENT_NUM2
	,LED_7_SEGMENT_NUM3
	,LED_7_SEGMENT_NUM4
	,LED_7_SEGMENT_NUM5
	,LED_7_SEGMENT_NUM6
	,LED_7_SEGMENT_NUM7
	,LED_7_SEGMENT_NUM8
	,LED_7_SEGMENT_NUM9
	,LED_7_SEGMENT_A
	,LED_7_SEGMENT_b
	,LED_7_SEGMENT_C
	,LED_7_SEGMENT_d
	,LED_7_SEGMENT_E
	,LED_7_SEGMENT_F
	};
void vInitial7SegLedDisplay(void)			// 130328jac01***
{
	bRow7SegLedShowData[0]=LED_OFF;
	bRow7SegLedShowData[1]=LED_OFF;
	bRow7SegLedShowData[2]=LED_OFF;
	bRow7SegLedShowData[3]=LED_OFF;
	bRow7SegLedShowData[4]=LED_OFF;
	bRow7SegLedBlinkData[0]=LED_OFF;
	bRow7SegLedBlinkData[1]=LED_OFF;
	bRow7SegLedBlinkData[2]=LED_OFF;
	bRow7SegLedBlinkData[3]=LED_OFF;
	bRow7SegLedBlinkData[4]=LED_OFF;
	bRow7SegLedAutoOffData[0]=LED_OFF;
	bRow7SegLedAutoOffData[1]=LED_OFF;
	bRow7SegLedAutoOffData[2]=LED_OFF;
}			// 130328jac01&&&
//Every 1ms excuted.
//BYTE bVariable;
void vDisplayRowShiftTimer(void)
{
	static BYTE bDisplayRowShiftTimer=0;
/*		// 130415jac01
	static BYTE bDisplayTimerCount=0;
	if(bDisplayTimerCount<LED_7SEG_SHIFT_TIME_COUNT)		// 3(ms)*5(Row)*66(Fram)=1s		
		{
		bDisplayTimerCount++;
		return;
		}
	bDisplayTimerCount=0;
*/		// 130415jac01
#if 0	//130423jac03
	if(b7SegRightBlink==LED_7SEG_NUM)
		{
		if(fg7SegHexShow)
			{
			b7SegRightBlink=bLedNumber[b7SegLeftBlink%16];
			b7SegLeftBlink=bLedNumber[b7SegLeftBlink/16];
			}
		else
			{
			b7SegRightBlink=bLedNumber[b7SegLeftBlink%10];
			if(b7SegLeftBlink>9)	// 130325jac02***
				{
				b7SegLeftBlink=bLedNumber[b7SegLeftBlink/10];
				}
			else
				{
				b7SegLeftBlink=LED_OFF;
				}
			}	// 130325jac02&&&
		}

	if(b7SegRightShow==LED_7SEG_NUM)
		{
		if(fg7SegHexShow)
			{
			b7SegRightShow=bLedNumber[b7SegLeftShow%16];
			//fg7SegHexShow=FALSE;		// 130403jac01
			b7SegLeftShow=bLedNumber[b7SegLeftShow/16];
			}
		else
			{
			b7SegRightShow=bLedNumber[b7SegLeftShow%10];
			if(b7SegLeftShow>9)		// 130325jac02***
				{
				b7SegLeftShow=bLedNumber[b7SegLeftShow/10];
				}
			else
				{
				b7SegLeftShow=LED_OFF;
				}
			}	// 130325jac02&&&
		}
#endif	//130423jac03
	vRow1Disable();// 130315ja01***
	//vRow2Disable();
	//vRow3Disable();
	//vRow4Disable();
	//vRow5Disable();
	vRow2To5Disable();	//130314ja01
	vLedColumnOutValue(bRow7SegLedShowData[bDisplayRowShiftTimer]);

	switch(bDisplayRowShiftTimer)
		{
		case LED_ROW1_TURN:
			vRow1Enable();
			break;
		case LED_ROW2_TURN:
			vRow2Enable();
			break;
		case LED_ROW3_TURN:
			vRow3Enable();
			break;
		case LED_ROW4_TURN:
			vRow4Enable();
			break;
		case LED_ROW5_TURN:
			vRow5Enable();
			break;
		}
	bDisplayRowShiftTimer++;
	bDisplayRowShiftTimer%=LED_ROW_MAX;
}

void vDisplay7segLedAllOn(void)
{
	bRow7SegLedShowData[0]=LED_ON;		// 130307ja01***
	bRow7SegLedShowData[1]=LED_ON;
	bRow7SegLedShowData[2]=LED_ON;
	bRow7SegLedShowData[3]=LED_7SEG_ON;		// 130316ja01
	bRow7SegLedShowData[4]=LED_7SEG_ON;		// 130307ja01&&&// 130316ja01
}

void vDisplay7segLedAndTouchLedAllOn(void)//130419gr01***
{
//Touch LED ON
	bLEDShowData2=LED_ON;
	bLEDShowData1=LED_ON;

//7seg Led ON
	bRow7SegLedShowData[0]=LED_ON;		// 130307ja01***
	bRow7SegLedShowData[1]=LED_ON;
	bRow7SegLedShowData[2]=LED_ON;
	bRow7SegLedShowData[3]=LED_7SEG_ON;		// 130316ja01
	bRow7SegLedShowData[4]=LED_7SEG_ON;		// 130307ja01&&&// 130316ja01

	bRow7SegLedAutoOffData[0]=LED_OFF;	//130426le01***
	bRow7SegLedAutoOffData[1]=LED_OFF;
	bRow7SegLedAutoOffData[2]=LED_OFF;	
	fg7SegAutoOff=FALSE;	//130426le01&&&

}//130419gr01&&&

void vDisplay7segLedAllOff(void)
{
	bRow7SegLedShowData[0]=LED_OFF;		// 130307ja01***
	bRow7SegLedShowData[1]=LED_OFF;
	bRow7SegLedShowData[2]=LED_OFF;
	bRow7SegLedShowData[3]=LED_OFF;
	bRow7SegLedShowData[4]=LED_OFF;		// 130307ja01&&&
	
	bRow7SegLedBlinkData[0]=LED_OFF;		// 130307ja01***
	bRow7SegLedBlinkData[1]=LED_OFF;
	bRow7SegLedBlinkData[2]=LED_OFF;
	bRow7SegLedBlinkData[3]=LED_OFF;
	bRow7SegLedBlinkData[4]=LED_OFF;	
	
	bRow7SegLedAutoOffData[0]=LED_OFF;	//130429jac01***
	bRow7SegLedAutoOffData[1]=LED_OFF;
	bRow7SegLedAutoOffData[2]=LED_OFF;	
	fg7SegAutoOff=FALSE;	//130429jac01&&&
}


void vDisplay7segLedAndTouchLedAllOff(void) //130419gr01***
{
//Touch LED OFF
	bLEDShowData2=LED_OFF;
	bLEDShowData1=LED_OFF;
	bLEDBlinkData1=LED_OFF;
	bLEDBlinkData2=LED_OFF;

	fgOscillateAngleIsShowing=FALSE;  //130425Ju01
	
//7seg Led OFF
	vDisplay7segLedAllOff();
}//130419gr01&&&

BYTE bDisplay7SegLedBlinkTime=DISPLAY_NO_DISAPPEAR;
BYTE bDisplay7SegLedAutoOffTime=DISPLAY_NO_DISAPPEAR;
#define LED_TUBE_WHITE_BIT	0x02		// 130401jac01
//Excute this function every 0.1s.
void vDisplay7SegLedTimer(void)//130308ja04
{
	static BYTE bBlinkTimeCount=0;
	//static BYTE bAutoOffTimeCount=0;
	static BOOL fgDisplay7SegLedOn=FALSE;		// 130401jac01
	
	//for 7Seg display Blink
	bBlinkTimeCount++;
	if(bBlinkTimeCount>=bDisplay7SegLedBlinkTime)		// 130401jac01***
		{
		bBlinkTimeCount=0;
		if(fgDisplay7SegLedOn==TRUE)
			{
			bRow7SegLedShowData[0]|=bRow7SegLedBlinkData[0];			
			bRow7SegLedShowData[1]|=bRow7SegLedBlinkData[1];			
			bRow7SegLedShowData[2]|=bRow7SegLedBlinkData[2];
			if((b7SegRightShow==LED_OFF)&&(b7SegLeftShow==LED_OFF))
				{
				b7SegRightShow=b7SegRightBlink;			
				b7SegLeftShow=b7SegLeftBlink;
				}
			fgDisplay7SegLedOn=FALSE;
			}
		else
			{
			bRow7SegLedShowData[0]&=~bRow7SegLedBlinkData[0];			
			bRow7SegLedShowData[1]&=~bRow7SegLedBlinkData[1];			
			bRow7SegLedShowData[2]&=~bRow7SegLedBlinkData[2];
			if((b7SegRightShow==b7SegRightBlink)&&(b7SegLeftShow==b7SegLeftBlink))
				{
				b7SegRightShow=LED_OFF;
				b7SegLeftShow=LED_OFF;
				}
			fgDisplay7SegLedOn=TRUE;
			}
		}
	
/*	// 130401jac01&&&
	if(bBlinkTimeCount>=bDisplay7SegLedBlinkTime)
		{
		bBlinkTimeCount=0;
		bRow7SegLedShowData[0]^=bRow7SegLedBlinkData[0];			
		bRow7SegLedShowData[1]^=bRow7SegLedBlinkData[1];			
		bRow7SegLedShowData[2]^=bRow7SegLedBlinkData[2];	

		if(((b7SegRightShow==b7SegRightBlink)&&(b7SegLeftShow==b7SegLeftBlink))||((b7SegRightShow==LED_OFF)&&(b7SegLeftShow==LED_OFF)))
			{
			b7SegRightShow^=b7SegRightBlink;			
			b7SegLeftShow^=b7SegLeftBlink;
			}
		}
*/	// 130401jac01
		
	//for 7Seg display auto off
	//bAutoOffTimeCount++
	//if(bAutoOffTimeCount==bDisplay7SegLedAutoOffTime)
	bDisplay7SegLedAutoOffTime--;
	if(bDisplay7SegLedAutoOffTime==0)
		{
		bRow7SegLedShowData[0]&=(~bRow7SegLedAutoOffData[0]);	//130322ja01
		bRow7SegLedShowData[1]&=(~bRow7SegLedAutoOffData[1]);	//130322ja01
		bRow7SegLedShowData[2]&=(~bRow7SegLedAutoOffData[2]);	//130322ja01
		bRow7SegLedAutoOffData[0]=LED_OFF;
		bRow7SegLedAutoOffData[1]=LED_OFF;
		bRow7SegLedAutoOffData[2]=LED_OFF;
		if(fg7SegAutoOff==TRUE)					// 130315ja01***
			{
			bRow7SegLedShowData[3]=LED_OFF;
			bRow7SegLedShowData[4]=LED_OFF;
			fg7SegAutoOff=FALSE;
			}					// 130315ja01&&&
		bDisplay7SegLedAutoOffTime=DISPLAY_NO_DISAPPEAR;
	//	fgAngleLEDOn=FALSE;	//130326Ke04
		fgOscillateAngleIsShowing=FALSE;	//130419Ju01
	//	bAutoOffTimeCount=0;
		}

	if(bRow7SegLedShowData[0]&LED_TUBE_WHITE_BIT)		// 130401jac01***
		{
		vTubeLedON();
		}
	else
		{
		vTubeLedOFF();
		}		// 130401jac01&&&
}

//bOffTime:Auto Off Time,UNIT:0.1s
void vDisplayShowAirVolume(BYTE bDecNumber)				
{
	switch(bDecNumber)
		{
		case AIR_VOLUME_MAX:
			vDisplay7SegShowHiOn();	
			break;
		default:
			vDisplay7SegShowDecNumOn(bDecNumber);	
			break;
		}
	vDisplayLEDAirVolumeSettingIndicationOn();		// 130415jac02
}

//Display the air volume Lo~2~32~Hi in 7 segments, and blink function.
void vDisplayShowAirVolumeBlink(BYTE bDecNumber,BYTE bTime)	
{
	switch(bDecNumber)
		{
		case AIR_VOLUME_MAX:
			vDisplay7SegShowHiBlinkOn(bTime);		// 130311ja02
			break;
		default:
			vDisplay7SegShowDecNumBlinkOn(bDecNumber,bTime);		// 130311ja02
			break;
		}
	vDisplayLEDAirVolumeSettingIndicationBlinkOn(bTime);		// 130415jac02
}

//Display the air volume Lo~2~32~Hi in 7 segments, and auto off function.
void vDisplayShowAirVolumeAutoOff(BYTE bDecNumber,BYTE bTime)	
{

	if(fgOscillateInitialProcess==TRUE)	//130424Ju01***
		{
		return;
		}	//130424Ju01&&&

	switch(bDecNumber)
		{
		case AIR_VOLUME_MAX:
			vDisplay7SegShowHiAutoOff(bTime);		// 130311ja02
			break;
		default:
			vDisplay7SegShowDecNumAutoOff(bDecNumber,bTime);		// 130311ja02
			break;
		}
	vDisplayLEDAirVolumeSettingIndicationAutoOff(bTime); 		// 130415jac02
}


//Display the Oscillate Angle in 7 segments.
//OSCILLATE_15D, OSCILLATE_30D, OSCILLATE_60D, OSCILLATE_90D, OSCILLATE_120D
void vDisplayShowOscillateAngle(BYTE bOscillateAngle)				
{
	BYTE bVariable;					// 130315ja01
	vDisplayLEDAngleSettingIndicationOn();		// 130415jac02
	switch(bOscillateAngle)
		{
		default:
	//	case OSCILLATE_15D://130423vi04
			vDisplay7SegShowPOn();		// 130311ja02
			return;
		case OSCILLATE_30D:
			bVariable=3;
			break;
		case OSCILLATE_60D:
			bVariable=6;
			break;
		case OSCILLATE_90D:
			bVariable=9;
			break;
		case OSCILLATE_120D:
			bVariable=12;
			break;
		}
	vDisplay7SegShowDecNumOn(bVariable);		// 130311ja02
}
//130310ha03&&&
void vDisplayShowOscAngleBlink(BYTE bOscillateAngle,BYTE bBlinkTime)		// 130311ja02***				
{
	BYTE bVariable;					// 130315ja01
	vDisplayLEDAngleSettingIndicationBlinkOn(bBlinkTime);		// 130415jac02
	switch(bOscillateAngle)
		{
		default:
	//	case OSCILLATE_15D://130423vi04
			vDisplay7SegShowPBlinkOn(bBlinkTime);
			return;
		case OSCILLATE_30D:
			bVariable=3;
			break;
		case OSCILLATE_60D:
			bVariable=6;
			break;
		case OSCILLATE_90D:
			bVariable=9;
			break;
		case OSCILLATE_120D:
			bVariable=12;
			break;
		}
	vDisplay7SegShowDecNumBlinkOn(bVariable, bBlinkTime);
}

void vDisplayShowOscAngleAutoOff(BYTE bOscillateAngle,BYTE bOffTime)				
{
	BYTE bVariable;					// 130315ja01
	if(fgOscillateAngleShowEnable==FALSE)	//130418Ke04
		return;	//130418Ke04
	
	vDisplayLEDAngleSettingIndicationAutoOff(bOffTime);		// 130415jac02
	fgOscillateAngleIsShowing=TRUE;//130419Ju01
	switch(bOscillateAngle)
		{
		default:
		//case OSCILLATE_15D://130423vi04
			vDisplay7SegShowPAutoOff(bOffTime);
			return;
		case OSCILLATE_30D:
			bVariable=3;
			break;
		case OSCILLATE_60D:
			bVariable=6;
			break;
		case OSCILLATE_90D:
			bVariable=9;
			break;
		case OSCILLATE_120D:
			bVariable=12;
			break;
		}
	vDisplay7SegShowDecNumAutoOff(bVariable,bOffTime);
}


void vDisplayShowLouverAngle(BYTE bLouverAngle)				
{
	switch(bLouverAngle)
			{
			default:
		//	case LOUVER_HORIZONTAL_3://130423vi04
		//	case LOUVER_HORIZONTAL_1://130423vi04
				vDisplay7SegShowHorizontalOn();
				break;
			case LOUVER_UPPER40D:
				vDisplay7SegShowUpperOn();
				break;
			case LOUVER_LOWER20D:
				vDisplay7SegShowUnderLineOn();
				break;
	
			}
	vDisplayLEDAngleSettingIndicationOn();		// 130415jac02
}


void vDisplayShowLouverAngleBlink(BYTE bLouverAngle,BYTE bBlinkTime)				
{
	switch(bLouverAngle)
		{
		default:
		//case LOUVER_HORIZONTAL_3://130423vi04
		//case LOUVER_HORIZONTAL_1://130423vi04
			vDisplay7SegShowHorizontalBlinkOn(bBlinkTime);
			break;
		case LOUVER_UPPER40D:
			vDisplay7SegShowUpperBlinkOn(bBlinkTime);
			break;
		case LOUVER_LOWER20D:
			vDisplay7SegShowUnderLineBlinkOn(bBlinkTime);
			break;
		}
	vDisplayLEDAngleSettingIndicationBlinkOn(bBlinkTime);		// 130415jac02
}
void vDisplayShowLouverAngleAutoOff(BYTE bLouverAngle,BYTE bOffTime)				
{
	switch(bLouverAngle)
		{
		default:
		//case LOUVER_HORIZONTAL_3://130423vi04
		//case LOUVER_HORIZONTAL_1://130423vi04
			vDisplay7SegShowHorizontalAutoOff(bOffTime);
			break;
		case LOUVER_UPPER40D:
			vDisplay7SegShowUpperAutoOff(bOffTime);
			break;
		case LOUVER_LOWER20D:
			vDisplay7SegShowUnderLineAutoOff(bOffTime);
			break;
		}
	vDisplayLEDAngleSettingIndicationAutoOff(bOffTime);		// 130415jac02
}

void vDisplay7SegMessageClear(void)		// 130415jac03
{
	b7SegLeftShow=LED_OFF;
	b7SegRightShow=LED_OFF;
	b7SegLeftBlink=LED_OFF;
	b7SegRightBlink=LED_OFF;
}		// 130415jac03

void vDisplay7SegBlinkOff(void)		// 130416jac01***
{
	if((b7SegLeftShow==b7SegLeftBlink)&&(b7SegRightShow==b7SegRightBlink))
		{
		b7SegLeftShow=LED_OFF;
		b7SegRightShow=LED_OFF;
		}
	b7SegLeftBlink=LED_OFF;
	b7SegRightBlink=LED_OFF;
}				// 130416jac01&&&

void vOecCount(BYTE bData)		// 130423jac03***
{
	BYTE bTemp;
	bTemp=(BYTE)(bData/10);
	if(bTemp>0)
		{
		b7SegLeftShow=bLedNumber[bTemp];
		}
	else
		{
		b7SegLeftShow=LED_OFF;
		}
	b7SegRightShow=bLedNumber[bData%10];
}

void vDisplay7SegShowDecNumOn(BYTE bDecNumber)	
{
	fg7SegAutoOff=FALSE;
	//fg7SegHexShow=FALSE;
	vOecCount(bDecNumber);
}

void vDisplay7SegShowDecNumAutoOff(BYTE bDecNumber,BYTE bTime)
{
	//if(fgOscillateInitialProcess==FALSE)	//130418Ke03  //130424Ju01
		{
		//fg7SegHexShow=FALSE;
		bDisplay7SegLedAutoOffTime=bTime;
		vOecCount(bDecNumber);
		fg7SegAutoOff=TRUE;
		}
}					// 130315ja01// 130403jac01	
//130419ha01&&&

void vDisplay7SegShowDecNumBlinkOn(BYTE bDecNumber,BYTE bTime)
{
	BYTE bTemp;
	//fg7SegHexShow=FALSE;
	bDisplay7SegLedBlinkTime=bTime;
	bTemp=(BYTE)(bDecNumber/10);
	if(bTemp>0)
		{
		b7SegLeftBlink=bLedNumber[bTemp];
		}
	else
		{
		b7SegLeftBlink=LED_OFF;
		}
	b7SegRightBlink=bLedNumber[bDecNumber%10];
}

void vDisplay7SegShowHexNumOn(BYTE bHexNumber)				
{
	fg7SegAutoOff=FALSE;
	//fg7SegHexShow=TRUE;
	b7SegLeftShow=bLedNumber[bHexNumber/16];
	b7SegRightShow=bLedNumber[bHexNumber%16];
}

void vDisplay7SegShowHexNumBlinkOn(BYTE bHexNumber,BYTE bTime)
{
	//fg7SegHexShow=TRUE;
	bDisplay7SegLedBlinkTime=bTime;
	b7SegLeftBlink=bLedNumber[bHexNumber/16];
	b7SegRightBlink=bLedNumber[bHexNumber%16];
}
void vDisplay7SegShowHexNumAutoOff(BYTE bHexNumber,BYTE bTime)
{
	//fg7SegHexShow=TRUE;
	bDisplay7SegLedAutoOffTime=bTime;
	b7SegLeftShow=bLedNumber[bHexNumber/16];
	b7SegRightShow=bLedNumber[bHexNumber%16];
	fg7SegAutoOff=TRUE;
}	// 130423jac03&&&

#endif

