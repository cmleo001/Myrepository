#define _DISPLAY_C_
#include "general.h"

#ifdef MAIN_DISPLAY_FOR_TEST	// 130325jac01***
#define DISPLY_TIMER_100MS		4
BYTE bRow7SegLedShowData[5]={LED_OFF,LED_OFF,LED_OFF,LED_OFF,LED_OFF};
BOOL fg7SegHexShow=FALSE;
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

void vDisplay7SegLedTimer(void)
{
	static BYTE b7segTimer100ms=0;
	//static BYTE bAutoOffTimeCount=0;
	static BYTE bLastDisplayData[5]={LED_OFF,LED_OFF,LED_OFF,LED_OFF,LED_OFF};
	b7segTimer100ms++;
	if(b7segTimer100ms<DISPLY_TIMER_100MS)		// 0.1ms
		{
		return;
		}
	b7segTimer100ms=0;

	if(b7SegRightShow==LED_7SEG_NUM)
		{
		if(fg7SegHexShow)
			{
			b7SegRightShow=bLedNumber[b7SegLeftShow%16];
			b7SegLeftShow=bLedNumber[b7SegLeftShow/16];
			}
		else
			{
			b7SegRightShow=bLedNumber[b7SegLeftShow%10];
			b7SegLeftShow=bLedNumber[b7SegLeftShow/10];
			}	// 130325jac01&&&
		}
	

	// I2C Send CMD
	if((bLastDisplayData[0]!=bRow7SegLedShowData[0])||(bLastDisplayData[1]!=bRow7SegLedShowData[1]))
		{
		bLastDisplayData[0]=bRow7SegLedShowData[0];
		bLastDisplayData[1]=bRow7SegLedShowData[1];
		// i2c cmd
		vIntSend7SegLEDRow0_1( bRow7SegLedShowData[0], bRow7SegLedShowData[1]);
		}
	if(bLastDisplayData[2]!=bRow7SegLedShowData[2])
		{
		bLastDisplayData[2]=bRow7SegLedShowData[2];
		// i2c cmd
		vIntSend7SegLEDRow2( bRow7SegLedShowData[2]);
		}
	if((bLastDisplayData[3]!=bRow7SegLedShowData[3])||(bLastDisplayData[4]!=bRow7SegLedShowData[4]))
		{
		bLastDisplayData[3]=bRow7SegLedShowData[3];
		bLastDisplayData[4]=bRow7SegLedShowData[4];
		vIntSend7SegLEDRow3_4( bRow7SegLedShowData[3], bRow7SegLedShowData[4]);
		// i2c cmd
		}
}

void vDisplay7segLedAllOn(void)
{
	bRow7SegLedShowData[0]=LED_ON;		
	bRow7SegLedShowData[1]=LED_ON;
	bRow7SegLedShowData[2]=LED_ON;
	bRow7SegLedShowData[3]=LED_7SEG_ON;		
	bRow7SegLedShowData[4]=LED_7SEG_ON;	
}
void vDisplay7segLedAllOff(void)
{
	bRow7SegLedShowData[0]=LED_OFF;	
	bRow7SegLedShowData[1]=LED_OFF;
	bRow7SegLedShowData[2]=LED_OFF;
	bRow7SegLedShowData[3]=LED_OFF;
	bRow7SegLedShowData[4]=LED_OFF;		
}
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
}

//Display the Oscillate Angle in 7 segments.
//OSCILLATE_15D, OSCILLATE_30D, OSCILLATE_60D, OSCILLATE_90D, OSCILLATE_120D
void vDisplayShowOscillateAngle(BYTE bOscillateAngle)				
{
	BYTE bVariable;			// 130315ja01
	switch(bOscillateAngle)
		{
		default:
		case OSCILLATE_15D:
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


void vDisplayShowLouverAngle(BYTE bLouverAngle)				
{
	switch(bLouverAngle)
			{
			default:
			case LOUVER_HORIZONTAL_3:
			case LOUVER_HORIZONTAL_1:
				vDisplay7SegShowHorizontalOn();
				break;
			case LOUVER_UPPER40D:
				vDisplay7SegShowUpperOn();
				break;
			case LOUVER_LOWER20D:
				vDisplay7SegShowUnderLineOn();
				break;
	
			}
}


#endif	// 130325jac01&&&

#ifdef SHOW_3DIGITAL_NUMBER	//130323ha02***
//wNumber display in the 7segment and 1,2,4,6 LED.
// 7segment		--> 0~99
// 1,2,4,6 LED	--> 0xx~13xx
//LED	1	2	4	6
// 0		0	0	0	0
// 1		1	0	0	0
// 2		0	1	0	0
// 3		1	1	0	0
// 4		0	0	1	0
// 5		1	0	1	0
// 6		0	1	1	0
// 7		1	0	0	1
// 8		0	1	0	0
// 9		1	1	0	1
// 10	0	0	1	1
// 11	1	0	1	1
// 12	0	1	1	1
// 13	1	1	1	1
void vShow3DigitalNumber(WORD wNumber)
{
	BYTE bCentesimal;
	BYTE unit;
	bCentesimal=wNumber/100;
	unit=wNumber%100;
	vDisplay7SegShowDecNum(unit);
	if((bCentesimal%2)==0)
		{	// 0,2,4,6,8
		vDisplayLEDTimer1H(FALSE);
		}
	else
		{	// 1,3,5,7,9
		vDisplayLEDTimer1H(TRUE);
		}
	
	if(bCentesimal>=6)
		{	// 6,7,8,9,10,11,12,13
		vDisplayLEDTimer6H(TRUE);
		}
	else
		{	// 0,1,2,3,4,5
		vDisplayLEDTimer6H(FALSE);
		}
	
	switch(bCentesimal)
		{
		case 0:
		case 1:
		case 7:
			vDisplayLEDTimer2H(FALSE);
			vDisplayLEDTimer4H(FALSE);
			break;
		case 4:
		case 5:
		case 10:
		case 11:
			vDisplayLEDTimer2H(FALSE);
			vDisplayLEDTimer4H(TRUE);
			break;
		case 2:
		case 3:
		case 8:
		case 9:
			vDisplayLEDTimer2H(TRUE);
			vDisplayLEDTimer4H(FALSE);
			break;
		case 6:
		case 12:
		case 13:
			vDisplayLEDTimer2H(TRUE);
			vDisplayLEDTimer4H(TRUE);
			break;
		}
}
#endif	//130323ha02&&&

