#define _LOUVER_MOTOR_C_
#include "general.h"

#ifdef LOUVER_MOTOR_FUNCTION
//Vertical all angle need step about step motor.
//[5] Drive Direction	CW / CCW
//[6] Step Angle		5.625¢X/ 64 puls
#define VERTICAL_ANGLE_0	0
#define VERTICAL_ANGLE_20	268	//(20/5.625)*64puls=227.55556,228=0xE4,228+40	//130426Me01
#define VERTICAL_ANGLE_60	723	// (60/5.625)*64 puls=682.66667	683+40//130426Me01
#define VERTICAL_ANGLE_80	910		// (80/5.625)*64 puls=910.22222
#define VERTICAL_ANGLE_110	1252	// (110/5.625)*64 puls=1251.55556
#define VERTICAL_ANGLE_115	1308	// (115/5.625)*64 puls=1308.44444



//Rotation angle 15 degree		52.5~67.5
//Rotation angle 30 degree		45 ~ 75
//Rotation angle 60 degree		30 ~ 90
//Rotation angle 90 degree		15 ~105
//Rotation angle 120 degree		0 ~ 120
//0deg is initial position, 60deg is central position
//
//Left to right angles
//0deg 15deg 30deg 45deg 52.5deg 60deg 67.5deg 75deg 90deg 105deg 120deg
//	<-------CW
//	------->CCW
#define CW	1
#define CCW	0
#define VERTICAL_SPEED_MAX		4	// 2ms=500pps
#define VERTICAL_SPEED_HIGH	4	// 4ms=250pps		For move to the memorized.
#define VERTICAL_SPEED_LOW		17	// 17ms=58.8pps	For SWING.
#define VERTICAL_SPEED_SLOW	30	// 30ms=33pps, It's used for brake and speed-up.

WORD wVerticalCWMargin=VERTICAL_ANGLE_115;
WORD wVerticalCCWMargin=0;
WORD wVerticalNowPosition=VERTICAL_ANGLE_115;
//WORD wVerticalMemorizedPosition=0;	//record the stop position.	//130425Me02
WORD wVerticalStopPosition=0;
BOOL fgVerticalCWDirection=FALSE;	//default: CCW
BYTE bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
#ifdef FULL_FUNCTION                       //130316ro01
WORD wVerticalCWBrakePosition;   //130316ro01
WORD wVerticalCCWBrakePosition;   //130316ro01
BYTE bVerticalFastSpeed;  //130316ro01
const BYTE bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01   //130316ro01
#endif
BYTE bVerticalTimerCount=0;	// Every 1ms count 1. It's used for calculate time to next step.

WORD wVerticalChangeDirectStopTime=0;	//SHARP spec: when hoirzontal motor change direction, need to stop 0.3s then start.
BOOL fgVerticalMotorOn=FALSE;
#define DIR_DELAY_COUNT         300	// 300*1ms=300ms=0.3s, to delay 0.3s when the direction is changed,300 for 1ms.
void vVerticalMotorGoStep(BYTE bStep);
#define vVerticalMotorAllPinOff()	{vVerticalMotorGoStep(8);}

void vVerticalCWGoOneStep(void);
void vVerticalCCWGoOneStep(void);

//Puls 1->8 is CCW
//Puls 8->1 is CW
#define VERTICAL_MOTOR_TOTAL_PULS		8
const BYTE bVerticalMotorVector[VERTICAL_MOTOR_TOTAL_PULS+1] =
{
			// 1234	vertical motor pin
	0x01,	// 0001	step 1
	0x03,	// 0011	step 2
	0x02,	// 0010	step 3
	0x06,	// 0110	step 4
	0x04,	// 0100	step 5
	0x0c,	// 1100	step 6
	0x08,	// 1000	step 7
	0x09,	// 1001	step 8
	0x00	// 0000	let the motor all pin off.
};
#ifdef FULL_FUNCTION                       //130316ro01
void vLouverModeSet(BYTE bmode)
{
	fgVerticalMotorOn = TRUE;
	wVerticalChangeDirectStopTime=0;
	bLouverMode=bmode;
	
	switch(bLouverMode)
		{
		default:
			fgVerticalMotorOn = FALSE;
			break;
		case LOUVER_STOP:
			fgVerticalMotorOn = FALSE;
			wVerticalMemorizedPosition=wVerticalNowPosition;
			vMcuEepromWriteByte(EE_LOUVER_MEMORIZED_POSITION_LOW,(BYTE)(wVerticalMemorizedPosition&0x00FF));
			vMcuEepromWriteByte(EE_LOUVER_MEMORIZED_POSITION_HIGH,(BYTE)(wVerticalMemorizedPosition>>8));
			break;

		case LOUVER_OFF_MEMORIZED:
			wVerticalMemorizedPosition=bMcuEepromReadByte(EE_LOUVER_MEMORIZED_POSITION_HIGH)*0x100;
			wVerticalMemorizedPosition+=bMcuEepromReadByte(EE_LOUVER_MEMORIZED_POSITION_LOW);
			wVerticalStopPosition=wVerticalMemorizedPosition;
//			wVerticalNowPosition=VERTICAL_ANGLE_115;
			if(wVerticalStopPosition>wVerticalNowPosition)
				{
				fgVerticalCWDirection=TRUE;
				wVerticalCWMargin=wVerticalStopPosition;
				wVerticalCWBrakePosition=wVerticalCWMargin-VERTICAL_SPEED_SLOW+VERTICAL_SPEED_MAX;
				}
			else if(wVerticalStopPosition<wVerticalNowPosition)
				{
				fgVerticalCWDirection=FALSE;
				wVerticalCCWMargin=wVerticalStopPosition;
				wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;
				}
			bLouverAngle=bLouverMode;
			goto jumppoint;
			/*130314ro01
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
			//bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01
			bVerticalTimerCount=0;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
			*/
			
			break;
		case LOUVER_CLOSED_POSITION:
			wVerticalStopPosition=VERTICAL_ANGLE_115;
			wVerticalCWMargin=VERTICAL_ANGLE_115;
			wVerticalCCWMargin=VERTICAL_ANGLE_0;
//			wVerticalNowPosition=VERTICAL_ANGLE_115;
			fgVerticalCWDirection=TRUE;
			wVerticalCWBrakePosition=wVerticalCWMargin-VERTICAL_SPEED_SLOW+VERTICAL_SPEED_MAX;
//			wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;
			goto jumppoint;
			/*130314ro01
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
			//bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01
			bVerticalTimerCount=0;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
//			vMcuEepromWriteByte(EE_LOUVER_MODE,bLouverMode);
			*/
			break;
		case LOUVER_INITIAL_POSITION:
			wVerticalStopPosition=VERTICAL_ANGLE_0;
			wVerticalCWMargin=VERTICAL_ANGLE_115;
			wVerticalCCWMargin=VERTICAL_ANGLE_0;
			wVerticalNowPosition=VERTICAL_ANGLE_115;
			fgVerticalCWDirection=FALSE;
			wVerticalCWBrakePosition=wVerticalCWMargin-VERTICAL_SPEED_SLOW+VERTICAL_SPEED_MAX;
			wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;
			goto jumppoint;
			/*130314ro01
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
			//bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01
			bVerticalTimerCount=0;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
//			vMcuEepromWriteByte(EE_LOUVER_MODE,bLouverMode);
			*/
			break;

		case LOUVER_HORIZONTAL_1:
		case LOUVER_HORIZONTAL_3:
			wVerticalStopPosition=VERTICAL_ANGLE_20;
//			wVerticalNowPosition=VERTICAL_ANGLE_115;
			if(wVerticalStopPosition>wVerticalNowPosition)
				{
				fgVerticalCWDirection=TRUE;
				wVerticalCWMargin=wVerticalStopPosition;
				wVerticalCWBrakePosition=wVerticalCWMargin-VERTICAL_SPEED_SLOW+VERTICAL_SPEED_MAX;
				}
			else
				{
				fgVerticalCWDirection=FALSE;
				wVerticalCCWMargin=wVerticalStopPosition;
				wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;
				}
			bLouverAngle=bLouverMode;
			goto jumppoint;
			/*130314ro01
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
			//bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01
			bVerticalTimerCount=0;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
			*/
			
			break;

		case LOUVER_UPPER40D:
			wVerticalStopPosition=VERTICAL_ANGLE_60;
//			wVerticalNowPosition=VERTICAL_ANGLE_115;
			if(wVerticalStopPosition>wVerticalNowPosition)
				{
				fgVerticalCWDirection=TRUE;
				wVerticalCWMargin=wVerticalStopPosition;
				wVerticalCWBrakePosition=wVerticalCWMargin-VERTICAL_SPEED_SLOW+VERTICAL_SPEED_MAX;
				}
			else
				{
				fgVerticalCWDirection=FALSE;
				wVerticalCCWMargin=wVerticalStopPosition;
				wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;
				}
			bLouverAngle=bLouverMode;
			goto jumppoint;
			/*130314ro01
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
			//bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01
			bVerticalTimerCount=0;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
			*/
			
			break;
	
		case LOUVER_LOWER20D:
			wVerticalStopPosition=VERTICAL_ANGLE_0;
//			wVerticalNowPosition=VERTICAL_ANGLE_115;

			fgVerticalCWDirection=FALSE;
			wVerticalCCWMargin=wVerticalStopPosition;
			wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;
			bLouverAngle=bLouverMode;
			goto jumppoint;
			/*130314ro01
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
			//bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01
			bVerticalTimerCount=0;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
			*/
			
			break;

		case LOUVER_SWING:
			wVerticalStopPosition=VERTICAL_ANGLE_115;	//Don't stop.
			wVerticalCWMargin=VERTICAL_ANGLE_80;
			wVerticalCCWMargin=VERTICAL_ANGLE_0;
//			wVerticalNowPosition=VERTICAL_ANGLE_0;
//			fgVerticalCWDirection=TRUE;
			wVerticalCWBrakePosition=wVerticalCWMargin-VERTICAL_SPEED_SLOW+VERTICAL_SPEED_MAX;
			wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_LOW;//130305ro01
			//bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01
			bVerticalTimerCount=0;
			break;
		case LOUVER_CENTRAL:
			//130312ro02***
			wVerticalStopPosition=VERTICAL_ANGLE_20;
//			wVerticalNowPosition=VERTICAL_ANGLE_115;
			
			fgVerticalCWDirection=FALSE;
			wVerticalCCWMargin=VERTICAL_ANGLE_0;
			wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;
			bLouverAngle=bLouverMode;
			goto jumppoint;
			/*130314ro01
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
			bVerticalTimerCount=0;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
			*/
			
			break;	//130312ro02&&&
		case LOUVER_ALL_PIN_DISABLE:
			fgVerticalMotorOn = FALSE;
			vVerticalMotorAllPinOff();
			break;
		}
jumppoint:
	bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
	bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
	bVerticalTimerCount=0;
	wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
}
#else

#define VERTICAL_MEMORIZE_POSITION_LOW_BYTE bVerticalMemorizedPosition[0] //130425Me02
#define VERTICAL_MEMORIZE_POSITION_HIGH_BYTE bVerticalMemorizedPosition[1] //130425Me02

void vLouverModeSet(BYTE bmode)
{
	fgVerticalMotorOn = TRUE;
	wVerticalChangeDirectStopTime=0;
	bLouverMode=bmode;
	
	switch(bLouverMode)
		{
		default:
			fgVerticalMotorOn = FALSE;
			break;
		case LOUVER_STOP:
			fgVerticalMotorOn = FALSE;
			//wVerticalMemorizedPosition=wVerticalNowPosition;
			vMcuEepromWriteByte(EE_LOUVER_MEMORIZED_POSITION_LOW,(BYTE)(wVerticalNowPosition&0x00FF));//130316ro01
			vMcuEepromWriteByte(EE_LOUVER_MEMORIZED_POSITION_HIGH,(BYTE)(wVerticalNowPosition>>8));   //130316ro01
			break;

		case LOUVER_OFF_MEMORIZED:
			VERTICAL_MEMORIZE_POSITION_HIGH_BYTE=bMcuEepromReadByte(EE_LOUVER_MEMORIZED_POSITION_HIGH);//130425Me02
			VERTICAL_MEMORIZE_POSITION_LOW_BYTE=bMcuEepromReadByte(EE_LOUVER_MEMORIZED_POSITION_LOW);//130425Me02
			wVerticalStopPosition=wVerticalMemorizedPosition;
//			wVerticalNowPosition=VERTICAL_ANGLE_115;
			if(wVerticalStopPosition>wVerticalNowPosition)
				{
				fgVerticalCWDirection=TRUE;
				wVerticalCWMargin=wVerticalStopPosition;
		//		wVerticalCWBrakePosition=wVerticalCWMargin-VERTICAL_SPEED_SLOW+VERTICAL_SPEED_MAX;   //130316ro01
				}
			else if(wVerticalStopPosition<wVerticalNowPosition)
				{
				fgVerticalCWDirection=FALSE;
				wVerticalCCWMargin=wVerticalStopPosition;
		//		wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;  //130316ro01
				}
			bLouverAngle=bLouverMode;
			goto jumppoint;
			/*130314ro01
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
			//bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01
			bVerticalTimerCount=0;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
			*/
			break;
			
		case LOUVER_CLOSED_POSITION:
			wVerticalStopPosition=VERTICAL_ANGLE_115;
			wVerticalCWMargin=VERTICAL_ANGLE_115;
			wVerticalCCWMargin=VERTICAL_ANGLE_0;
//			wVerticalNowPosition=VERTICAL_ANGLE_115;
			fgVerticalCWDirection=TRUE;
			wVerticalNowPosition=VERTICAL_ANGLE_0;	//130402ro02
			//wVerticalCWBrakePosition=wVerticalCWMargin-VERTICAL_SPEED_SLOW+VERTICAL_SPEED_MAX;  //130316ro01
//			wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;
			goto jumppoint;
			/*130314ro01
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
			//bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01
			bVerticalTimerCount=0;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
//			vMcuEepromWriteByte(EE_LOUVER_MODE,bLouverMode);
			*/
			break;
		case LOUVER_INITIAL_POSITION:
			wVerticalStopPosition=VERTICAL_ANGLE_0;
			wVerticalCWMargin=VERTICAL_ANGLE_115;
			wVerticalCCWMargin=VERTICAL_ANGLE_0;
			wVerticalNowPosition=VERTICAL_ANGLE_115;
			fgVerticalCWDirection=FALSE;
			//wVerticalCWBrakePosition=wVerticalCWMargin-VERTICAL_SPEED_SLOW+VERTICAL_SPEED_MAX;
			//wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;  //130316ro01
			goto jumppoint;
			/*130314ro01
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
			//bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01
			bVerticalTimerCount=0;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
//			vMcuEepromWriteByte(EE_LOUVER_MODE,bLouverMode);
			*/
			break;

		case LOUVER_HORIZONTAL_1:
		case LOUVER_HORIZONTAL_3:
			wVerticalStopPosition=VERTICAL_ANGLE_20;
//			wVerticalNowPosition=VERTICAL_ANGLE_115;
			if(wVerticalStopPosition>wVerticalNowPosition)
				{
				fgVerticalCWDirection=TRUE;
				wVerticalCWMargin=VERTICAL_ANGLE_60;//130423gr01
			//	wVerticalCWBrakePosition=wVerticalCWMargin-VERTICAL_SPEED_SLOW+VERTICAL_SPEED_MAX;     //130316ro01
				}
			else
				{
				fgVerticalCWDirection=FALSE;
				wVerticalCCWMargin=VERTICAL_ANGLE_0;//130423gr01
			//	wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;   //130316ro01
				}
			bLouverAngle=bLouverMode;
			goto jumppoint;
			/*130314ro01
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
			//bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01
			bVerticalTimerCount=0;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
			*/
			break;
			

		case LOUVER_UPPER40D:
			wVerticalStopPosition=VERTICAL_ANGLE_60;
//			wVerticalNowPosition=VERTICAL_ANGLE_115;
			if(wVerticalStopPosition>wVerticalNowPosition)
				{
				fgVerticalCWDirection=TRUE;
				wVerticalCWMargin=wVerticalStopPosition;
			//	wVerticalCWBrakePosition=wVerticalCWMargin-VERTICAL_SPEED_SLOW+VERTICAL_SPEED_MAX;    //130316ro01
				}
			else
				{
				fgVerticalCWDirection=FALSE;
				wVerticalCCWMargin=wVerticalStopPosition;
			//	wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;   //130316ro01
				}
			bLouverAngle=bLouverMode;
			goto jumppoint;
			/*130314ro01
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
			//bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01
			bVerticalTimerCount=0;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
			*/
			break;
			
	
		case LOUVER_LOWER20D:
			wVerticalStopPosition=VERTICAL_ANGLE_0;
//			wVerticalNowPosition=VERTICAL_ANGLE_115;

			fgVerticalCWDirection=FALSE;
			wVerticalCCWMargin=wVerticalStopPosition;
			//wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;   //130316ro01
			bLouverAngle=bLouverMode;
			goto jumppoint;
			/*130314ro01
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
			//bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01
			bVerticalTimerCount=0;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
			*/
			break;
			

		case LOUVER_SWING:
			wVerticalStopPosition=VERTICAL_ANGLE_115;	//Don't stop.
			wVerticalCWMargin=VERTICAL_ANGLE_80;
			wVerticalCCWMargin=VERTICAL_ANGLE_0;
//			wVerticalNowPosition=VERTICAL_ANGLE_0;
//			fgVerticalCWDirection=TRUE;
			//wVerticalCWBrakePosition=wVerticalCWMargin-VERTICAL_SPEED_SLOW+VERTICAL_SPEED_MAX;    //130316ro01***
			//wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;
			bVerticalNowSpeed=VERTICAL_SPEED_LOW;
			//bVerticalFastSpeed=VERTICAL_SPEED_LOW;//130305ro01
			//bVerticalSlowSpeed=VERTICAL_SPEED_SLOW;	//130306Ja01                                                     //130316ro01&&&
			bVerticalTimerCount=0;
			return;	//130322ro01
		case LOUVER_CENTRAL:
			//130312ro02***
			wVerticalStopPosition=VERTICAL_ANGLE_20;
//			wVerticalNowPosition=VERTICAL_ANGLE_115;
			
			fgVerticalCWDirection=FALSE;
			wVerticalCCWMargin=VERTICAL_ANGLE_0;
			//wVerticalCCWBrakePosition=wVerticalCCWMargin+VERTICAL_SPEED_SLOW-VERTICAL_SPEED_MAX;    //130316ro01
			//bLouverAngle=bLouverMode;
			goto jumppoint;
			/*130314ro01
			bVerticalNowSpeed=VERTICAL_SPEED_SLOW;
			bVerticalFastSpeed=VERTICAL_SPEED_HIGH;
			bVerticalTimerCount=0;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
			*/
			break;
			//130312ro02&&&
		case LOUVER_ALL_PIN_DISABLE:
			fgVerticalMotorOn = FALSE;
			vVerticalMotorAllPinOff();
			break;
		}
jumppoint:
	bVerticalNowSpeed=VERTICAL_SPEED_HIGH;
	bVerticalTimerCount=0;
	wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
	//bVerticalFastSpeed=VERTICAL_SPEED_HIGH;     //130316ro01
}
#endif


//be called is 1ms timer
#ifdef FULL_FUNCTION		//130316ro01
void vLouverMotorTimer(void)
{
	if(fgVerticalMotorOn==FALSE)
		{
		return;
		}

	//Stop 0.3s, if need.
	if(wVerticalChangeDirectStopTime!=0)
		{
		wVerticalChangeDirectStopTime--;
		return;
		}

	//Count one step time, if time is up, go one step.
	bVerticalTimerCount++;
	if(bVerticalTimerCount>=bVerticalNowSpeed)
		{
		bVerticalTimerCount=0;
		}
	else
		{
		return;
		}
	
	if(fgVerticalCWDirection)
		{	//CW
		vVerticalCWGoOneStep();
		wVerticalNowPosition++;
		
		//If the motor position reach the stop position, stop the motor.
		if(wVerticalNowPosition==wVerticalStopPosition)
			{
			bLouverMode=LOUVER_STOP;
			fgVerticalMotorOn=FALSE;
			return;
			}

		//If the motor position reach the CW margin, change the direction and pause 0.3s. 
		if(wVerticalNowPosition==wVerticalCWMargin)
			{
			fgVerticalCWDirection = FALSE;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
			return;
			}

		//Speed-up and speed-down control.
		if(wVerticalNowPosition>=wVerticalCWBrakePosition)
			{	//speed-down (brake)
			if(bVerticalNowSpeed<bVerticalSlowSpeed)
				{
				bVerticalNowSpeed++;
				}
			}
		else
			{	//speed-up and speed normal.
			if(bVerticalNowSpeed>bVerticalFastSpeed)
				{
				bVerticalNowSpeed--;
				}
			}
		}
	else
		{	//CCW
		vVerticalCCWGoOneStep();
		wVerticalNowPosition--;
		
		//If the motor position reach the stop position, stop the motor.
		if((wVerticalNowPosition==wVerticalStopPosition)&&(bLouverAngle!=LOUVER_CENTRAL)) //130312ro02
			{
			bLouverMode=LOUVER_STOP;
			fgVerticalMotorOn=FALSE;
			return;
			}
		
		//If the motor position reach the CCW margin, change the direction and pause 0.3s. 
		if(wVerticalNowPosition==wVerticalCCWMargin)
			{
			fgVerticalCWDirection = TRUE;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
			return;
			}
		
		//Speed-up and speed-down control.
		if(wVerticalNowPosition<=wVerticalCCWBrakePosition)
			{	//speed-down (brake)
			if(bVerticalNowSpeed<bVerticalSlowSpeed)
				{
				bVerticalNowSpeed++;
				}
			}
		else
			{	//speed-up and speed normal.
			if(bVerticalNowSpeed>bVerticalFastSpeed)
				{
				bVerticalNowSpeed--;
				}
			}
		}
}
#else
void vLouverMotorTimer(void)                       //130316ro01***
{
	if(fgVerticalMotorOn==FALSE)
		{
		return;
		}

	//Stop 0.3s, if need.
	if(wVerticalChangeDirectStopTime!=0)
		{
		wVerticalChangeDirectStopTime--;
		return;
		}

	//Count one step time, if time is up, go one step.
	bVerticalTimerCount++;
	if(bVerticalTimerCount>=bVerticalNowSpeed)
		{
		bVerticalTimerCount=0;
		}
	else
		{
		return;
		}

	if(fgVerticalCWDirection)
		{	//CW
		vVerticalCWGoOneStep();
		wVerticalNowPosition++;
		
		//If the motor position reach the stop position, stop the motor.
		if(wVerticalNowPosition==wVerticalStopPosition)
			{
			bLouverMode=LOUVER_STOP;
			fgVerticalMotorOn=FALSE;
			vIntLouverMotorOn(fgVerticalMotorOn);	//130424Me01
			//return;    //130327ro01
			}

		//If the motor position reach the CW margin, change the direction and pause 0.3s. 
		if(wVerticalNowPosition>=wVerticalCWMargin)    //130327ro01
			{
			fgVerticalCWDirection = FALSE;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
			return;
			}
		}
	else
		{	//CCW
		if(wVerticalNowPosition!=0)	//130329ro02
			{
			vVerticalCCWGoOneStep();
			wVerticalNowPosition--;
			}
		
		//If the motor position reach the stop position, stop the motor.
		if((wVerticalNowPosition==wVerticalStopPosition)&&(bLouverMode!=LOUVER_CENTRAL)) //130312ro02	//130401ro02
			{
			//bLouverMode=LOUVER_STOP;     //130402ro01
			fgVerticalMotorOn=FALSE;
			vIntLouverMotorOn(fgVerticalMotorOn);	//130424Me01
			//return;    //130327ro01
			if(bLouverMode==LOUVER_INITIAL_POSITION)	//130328ro02	//130401ro02
				{
				vIntLouverInitialFinish(TRUE);    //130329ro02
				}
			}
		
		//If the motor position reach the CCW margin, change the direction and pause 0.3s. 
		if(wVerticalNowPosition<=wVerticalCCWMargin)
			{
			fgVerticalCWDirection = TRUE;
			wVerticalChangeDirectStopTime=DIR_DELAY_COUNT;
			//return;   //130327ro01
			}
		}
}
#endif                                      //130316ro01&&&
BYTE bLouverStep=0;
void vVerticalCWGoOneStep(void)
{
	if(bLouverStep==0)
		{
		bLouverStep=VERTICAL_MOTOR_TOTAL_PULS-1;
		}
	else
		{
		bLouverStep--;
		}
	fgLouverMotorGoOneStep=TRUE;
	//vVerticalMotorGoStep(bOscillateStep);
}

void vVerticalCCWGoOneStep(void)
{
	bLouverStep++;
	bLouverStep%=VERTICAL_MOTOR_TOTAL_PULS;
	fgLouverMotorGoOneStep=TRUE;
	//vVerticalMotorGoStep(bOscillateStep);
}

void vVerticalMotorGoStep(BYTE bStep)
{
	BYTE btemp = bVerticalMotorVector[bStep];
	if(fgLouverMotorGoOneStep==FALSE)
		return;
	fgLouverMotorGoOneStep=FALSE;
	
	if(btemp&0x01)
		{
		vLouverMotor4EN();
		}
	else
		{
		vLouverMotor4DIS();
		}
	
	if(btemp&0x02)
		{
		vLouverMotor3EN();
		}
	else
		{
		vLouverMotor3DIS();
		}
	
	if(btemp&0x04)
		{
		vLouverMotor2EN();
		}
	else
		{
		vLouverMotor2DIS();
		}
	
	if(btemp&0x08)
		{
		vLouverMotor1EN();
		}
	else
		{
		vLouverMotor1DIS();
		}
}


#endif
