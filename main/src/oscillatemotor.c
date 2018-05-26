#define _OSCILLATE_MOTOR_C_
#include "general.h"

#ifdef OSCILLATE_MOTOR_FUNCTION

//Horizontal all angle need step about step motor.
//[5] Drive Direction	CW / CCW
//[6] Step Angle		3.75¢X/ 42.5 puls
//[7] Mechanical reduction ratio	1 / 3
//130425Ke01***
#define HORIZONTAL_STEP_EVERY_ANGLE		(WORD)(35.5)
#define HORIZONTAL_ANGLE_0					 (HORIZONTAL_STEP_EVERY_ANGLE*0)			//0
#define HORIZONTAL_ANGLE_7_5				((15*HORIZONTAL_STEP_EVERY_ANGLE)/2)		//270
#define HORIZONTAL_ANGLE_15					(15*HORIZONTAL_STEP_EVERY_ANGLE)			//540
#define HORIZONTAL_ANGLE_30					(30*HORIZONTAL_STEP_EVERY_ANGLE)			//1080
#define HORIZONTAL_ANGLE_45					(45*HORIZONTAL_STEP_EVERY_ANGLE)			//1620
#define HORIZONTAL_ANGLE_52_5				((103*HORIZONTAL_STEP_EVERY_ANGLE)/2)		//1890
#define HORIZONTAL_ANGLE_60					(60*HORIZONTAL_STEP_EVERY_ANGLE)			
#define HORIZONTAL_ANGLE_CENTER			2138
#define HORIZONTAL_ANGLE_67_5				((135*HORIZONTAL_STEP_EVERY_ANGLE)/2)		//2160
#define HORIZONTAL_ANGLE_75					(75*HORIZONTAL_STEP_EVERY_ANGLE)			//2700
#define HORIZONTAL_ANGLE_90					(90*HORIZONTAL_STEP_EVERY_ANGLE)			//3240
#define HORIZONTAL_ANGLE_105				(105*HORIZONTAL_STEP_EVERY_ANGLE)			//3780	
#define HORIZONTAL_ANGLE_120				(120*HORIZONTAL_STEP_EVERY_ANGLE)			//4320
#define HORIZONTAL_ANGLE_125				(125*HORIZONTAL_STEP_EVERY_ANGLE)			//4500
//130425Ke01&&&

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
//#define HORIZONTAL_SPEED_MAX		2	// 2ms=500pps
#define HORIZONTAL_SPEED_MAX		3	//130308Ke01	
#define HORIZONTAL_SPEED_HIGH		6	// 6ms=166.7pps
#define HORIZONTAL_SPEED_LOW		8	// 8ms=125pps
#define HORIZONTAL_SPEED_SLOW		50	// 50ms=20pps, It's used for brake and speed-up.

WORD wHorizontalCWMargin=0;
WORD wHorizontalCCWMargin=HORIZONTAL_ANGLE_125;
WORD wHorizontalNowPosition=HORIZONTAL_ANGLE_125;

WORD wHorizontalStopPosition=HORIZONTAL_ANGLE_125;	//130323ha01

WORD wHorizontalMemorizedPosition=0;
BOOL fgHorizontalCWDirection=TRUE;	//If true: CW.
WORD wHorizontalCWBrakePosition;
WORD wHorizontalCCWBrakePosition;
BYTE bHorizontalNowSpeed=HORIZONTAL_SPEED_HIGH;
BYTE bHorizontalFastSpeed;

BYTE bHorizontalSlowSpeed=HORIZONTAL_SPEED_SLOW;

BYTE bHorizontalTimerCount=0;	// Every 1ms count 1. It's used for calculate time to next step.

WORD wHorizontalChangeDirectStopTime=0;	//SHARP spec: when hoirzontal motor change direction, need to stop 0.3s then start.
BOOL fgHorizontalMotorOn=FALSE;
BOOL fgOscillateInitialFinish=FALSE;	//Whether oscillate initialization process has been executed flag
#define DIR_DELAY_COUNT         300	// 300*1ms=300ms=0.3s, to delay 0.3s when the direction is changed,300 for 1ms.
void vHorizontalMotorGoStep(BYTE bstep);
#define vHorizontalMotorAllPinOff()	{vHorizontalMotorGoStep(8);}

void vHorizontalCWGoOneStep(void);
void vHorizontalCCWGoOneStep(void);

//Puls 1->8 is CCW
//Puls 8->1 is CW
#define HORIZONTAL_MOTOR_TOTAL_PULS	8
const BYTE bHorizontalMotorVector[HORIZONTAL_MOTOR_TOTAL_PULS+1] = 
{
			// 1245	horizontal motor pin
	0x02,	// 0010	step 1
	0x03,	// 0011	step 2
	0x01,	// 0001	step 3
	0x09,	// 1001	step 4
	0x08,	// 1000	step 5
	0x0c,	// 1100	step 6
	0x04,	// 0100	step 7
	0x06,	// 0110	step 8
	0x00	// 0000	let the motor all pin off.
};

void vOscillateModeSet(BYTE bmode)
{
	fgHorizontalMotorOn = TRUE;
	wHorizontalChangeDirectStopTime=0;
	bOscillatingMode=bmode;
//	if(bmode==OSCILLATE_ON)
//		{
//		bOscillatingMode=bMcuEepromReadByte(EE_OSCILLATE_MODE_ON_OFF);
//		vMcuEepromWriteByte(EE_OSCILLATE_MODE_ON_OFF,bmode);
//		}
	wHorizontalStopPosition=HORIZONTAL_ANGLE_125;	//default is no stop position.	//130323ha01
	switch(bmode)
		{
		case OSCILLATE_ON:
			fgHorizontalMotorOn = TRUE;
			break;

		default:
			fgHorizontalMotorOn = FALSE;
			break;
		case OSCILLATE_OFF:
			fgHorizontalMotorOn = FALSE;
			wHorizontalMemorizedPosition=wHorizontalNowPosition;
			vMcuEepromWriteByte(EE_OSCILLATE_MEMORIZED_POSITION_LOW,(BYTE)(wHorizontalMemorizedPosition&0x00FF));
			vMcuEepromWriteByte(EE_OSCILLATE_MEMORIZED_POSITION_HIGH,(BYTE)(wHorizontalMemorizedPosition>>8));
			//vMcuEepromWriteByte(EE_OSCILLATE_MODE_ON_OFF,bOscillatingMode);
			break;

		case OSCILLATE_OFF_MEMORIZED:
			fgHorizontalMotorOn = TRUE;
			wHorizontalStopPosition=bMcuEepromReadByte(EE_OSCILLATE_MEMORIZED_POSITION_HIGH)*0x100;	//130323ha01
			wHorizontalStopPosition+=bMcuEepromReadByte(EE_OSCILLATE_MEMORIZED_POSITION_LOW);	//130323ha01
			if(wHorizontalNowPosition>=wHorizontalStopPosition)	//130323ha01***
				{
				fgHorizontalCWDirection=TRUE;
				}
			else
				{
				fgHorizontalCWDirection=FALSE;
				}	//130323ha01&&&
			wHorizontalCWMargin=HORIZONTAL_ANGLE_0;//130419Ke01
			wHorizontalCCWMargin=HORIZONTAL_ANGLE_120;//130419Ke01
			bHorizontalNowSpeed=HORIZONTAL_SPEED_SLOW;
			bHorizontalFastSpeed=HORIZONTAL_SPEED_MAX;
			goto OscillateSet;
			break;

		case OSCILLATE_CENTRAL:
			if(wHorizontalNowPosition==wHorizontalStopPosition)	//hm,
				{
				wHorizontalCWMargin=HORIZONTAL_ANGLE_0;
				wHorizontalCCWMargin=HORIZONTAL_ANGLE_CENTER;//130425Ke01
				wHorizontalNowPosition=HORIZONTAL_ANGLE_125;
				fgHorizontalCWDirection=TRUE;
				bHorizontalNowSpeed=HORIZONTAL_SPEED_SLOW;
				bHorizontalFastSpeed=HORIZONTAL_SPEED_MAX;
				}
			goto OscillateSet;
			break;

		case OSCILLATE_15D:
			wHorizontalCWMargin=HORIZONTAL_ANGLE_52_5;
			wHorizontalCCWMargin=HORIZONTAL_ANGLE_67_5;
			bHorizontalFastSpeed=HORIZONTAL_SPEED_LOW;
			goto OscillateSet;
			break;

		case OSCILLATE_30D:
			wHorizontalCWMargin=HORIZONTAL_ANGLE_45;
			wHorizontalCCWMargin=HORIZONTAL_ANGLE_75;
			bHorizontalFastSpeed=HORIZONTAL_SPEED_HIGH;
			goto OscillateSet;
			break;

		case OSCILLATE_60D:
			wHorizontalCWMargin=HORIZONTAL_ANGLE_30;
			wHorizontalCCWMargin=HORIZONTAL_ANGLE_90;
			bHorizontalFastSpeed=HORIZONTAL_SPEED_HIGH;
			goto OscillateSet;
			break;

		case OSCILLATE_90D:
			wHorizontalCWMargin=HORIZONTAL_ANGLE_15;
			wHorizontalCCWMargin=HORIZONTAL_ANGLE_105;
			bHorizontalFastSpeed=HORIZONTAL_SPEED_HIGH;
			goto OscillateSet;
			break;

		case OSCILLATE_120D:
			wHorizontalCWMargin=HORIZONTAL_ANGLE_0;
			wHorizontalCCWMargin=HORIZONTAL_ANGLE_120;
			bHorizontalFastSpeed=HORIZONTAL_SPEED_HIGH;
			goto OscillateSet;
			break;

		case OSCILLATE_CENTER:	//130323ha01***
			wHorizontalStopPosition=HORIZONTAL_ANGLE_60;	//default is no stop position.
			if(wHorizontalNowPosition>=HORIZONTAL_ANGLE_60)
				{
				fgHorizontalCWDirection=TRUE;
				wHorizontalCWMargin=HORIZONTAL_ANGLE_60;
				wHorizontalCCWMargin=HORIZONTAL_ANGLE_90;
				}
			else
				{
				fgHorizontalCWDirection=FALSE;
				wHorizontalCWMargin=HORIZONTAL_ANGLE_30;
				wHorizontalCCWMargin=HORIZONTAL_ANGLE_60;
				}
			bHorizontalNowSpeed=HORIZONTAL_SPEED_SLOW;
			bHorizontalFastSpeed=HORIZONTAL_SPEED_MAX;
			goto OscillateSet;	//130323ha01&&&

		case OSCILLATE_ALL_PIN_DISABLE:
			fgHorizontalMotorOn = FALSE;
			vHorizontalMotorAllPinOff();
			break;
		}
	return;
OscillateSet:
	//vMcuEepromWriteByte(EE_OSCILLATE_MODE_ON_OFF,bOscillatingMode);
	wHorizontalCWBrakePosition=wHorizontalCWMargin+HORIZONTAL_SPEED_SLOW-HORIZONTAL_SPEED_MAX;
	wHorizontalCCWBrakePosition=wHorizontalCCWMargin-HORIZONTAL_SPEED_SLOW+HORIZONTAL_SPEED_MAX;
	bHorizontalTimerCount=0;
	bHorizontalSlowSpeed=HORIZONTAL_SPEED_SLOW;


}

//be called is 1ms timer
void vOscillateMotorTimer(void)
{
	if(fgHorizontalMotorOn==FALSE)
		{
		return;
		}
	
	//Stop 0.3s, if need.
	if(wHorizontalChangeDirectStopTime!=0)
		{
		wHorizontalChangeDirectStopTime--;
		return;
		}
	
	//Count one step time, if time is up, go one step.
	bHorizontalTimerCount++;
	if(bHorizontalTimerCount>=bHorizontalNowSpeed)
		{
		bHorizontalTimerCount=0;
		}
	else
		{
		return;
		}
	
	if(fgHorizontalCWDirection)
		{	//CW
		vHorizontalCWGoOneStep();
		wHorizontalNowPosition--;
		
		//If the motor position reach the Stop position, stop the motor. 
		if(wHorizontalNowPosition==wHorizontalStopPosition)	//130323ha01***
			{
			bOscillatingMode=OSCILLATE_OFF;
			fgHorizontalMotorOn=FALSE;
			}	//130323ha01&&&

		//If the motor position reach the CW margin, change the direction and pause 0.3s. 
		if(wHorizontalNowPosition==wHorizontalCWMargin)
			{
			fgHorizontalCWDirection = FALSE;
			wHorizontalChangeDirectStopTime=DIR_DELAY_COUNT;
			return;
			}
		if(bOscillatingMode!=OSCILLATE_OFF_MEMORIZED)	//130419Ke01***
			{
			if(wHorizontalNowPosition<=wHorizontalCWMargin)
				{
				fgHorizontalCWDirection=FALSE;
				return;
				}
			}	//130419Ke01&&&
		//Speed-up and speed-down control.
		if(wHorizontalNowPosition<=wHorizontalCWBrakePosition)
			{	//speed-down (brake)
			if(bHorizontalNowSpeed<bHorizontalSlowSpeed)
				{
				bHorizontalNowSpeed++;
				}
			}
		else
			{	//speed-up and speed normal.
			if(bHorizontalNowSpeed>bHorizontalFastSpeed)
				{
				bHorizontalNowSpeed--;
				}
			}
		
		}
	else
		{	//CCW
		vHorizontalCCWGoOneStep();
		wHorizontalNowPosition++;
		
		//If the motor position reach the Stop position, stop the motor. 
		if(wHorizontalNowPosition==wHorizontalStopPosition)	//130323ha01***
			{
			bOscillatingMode=OSCILLATE_OFF;
			fgHorizontalMotorOn=FALSE;
			}	//130323ha01&&&

		//If the motor position reach the CCW margin, change the direction and pause 0.3s. 
		if(wHorizontalNowPosition==wHorizontalCCWMargin)
			{
			if((bOscillatingMode==OSCILLATE_CENTRAL)||(bOscillatingMode== OSCILLATE_OFF_MEMORIZED))
				{
				bOscillatingMode=OSCILLATE_OFF;
				fgHorizontalMotorOn=FALSE;
				fgOscillateInitialFinish=TRUE;//130305Ke02
				wHorizontalNowPosition=HORIZONTAL_ANGLE_60;	//130425Ke01
				vIntOscillateInitialFinish(fgOscillateInitialFinish);//130305Ke02
				}
			else
				{
				fgHorizontalCWDirection = TRUE;
				wHorizontalChangeDirectStopTime=DIR_DELAY_COUNT;
				}
			return;
			}
		if(bOscillatingMode!=OSCILLATE_OFF_MEMORIZED)
			{	//130419Ke01***
			if(wHorizontalNowPosition>=wHorizontalCCWMargin)
				{
				fgHorizontalCWDirection=TRUE;
				return;
				}
			}	//130419Ke01&&&
		//Speed-up and speed-down control.
		if(wHorizontalNowPosition>=wHorizontalCCWBrakePosition)
			{	//speed-down (brake)
			if(bHorizontalNowSpeed<bHorizontalSlowSpeed)
				{
				bHorizontalNowSpeed++;
				}
			}
		else
			{	//speed-up and speed normal.
			if(bHorizontalNowSpeed>bHorizontalFastSpeed)
				{
				bHorizontalNowSpeed--;
				}
			}
		}
}

BYTE bOscillateStep=0;
void vHorizontalCWGoOneStep(void)
{
	if(bOscillateStep==0)
		{
		bOscillateStep=HORIZONTAL_MOTOR_TOTAL_PULS-1;
		}
	else
		{
		bOscillateStep--;
		}
	fgOscillateMotorGoOneStep=TRUE;
	//vHorizontalMotorGoStep(bOscillateStep);
}

void vHorizontalCCWGoOneStep(void)
{
	bOscillateStep++;
	bOscillateStep%=HORIZONTAL_MOTOR_TOTAL_PULS;
	fgOscillateMotorGoOneStep=TRUE;
	//vHorizontalMotorGoStep(bOscillateStep);
}

void vHorizontalMotorGoStep(BYTE bstep)
{
	BYTE btemp = bHorizontalMotorVector[bstep];
	if(fgOscillateMotorGoOneStep==FALSE)
		return;
	fgOscillateMotorGoOneStep=FALSE;
	if(btemp&0x01)
		{
		vRotationMotor5EN();
		}
	else
		{
		vRotationMotor5DIS();
		}
	
	if(btemp&0x02)
		{
		vRotationMotor4EN();
		}
	else
		{
		vRotationMotor4DIS();
		}
	
	if(btemp&0x04)
		{
		vRotationMotor2EN();
		}
	else
		{
		vRotationMotor2DIS();
		}
	
	if(btemp&0x08)
		{
		vRotationMotor1EN();
		}
	else
		{
		vRotationMotor1DIS();
		}
}


#endif
