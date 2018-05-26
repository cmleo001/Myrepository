#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#ifdef MAIN_DISPLAY_FOR_TEST	// 130325jac01***

#define LED_7_SEGMENT_NUM0		0x3f
#define LED_7_SEGMENT_NUM1 	0x06
#define LED_7_SEGMENT_NUM2 	0x5b
#define LED_7_SEGMENT_NUM3 	0x4f
#define LED_7_SEGMENT_NUM4 	0x66
#define LED_7_SEGMENT_NUM5 	0x6d
#define LED_7_SEGMENT_NUM6 	0x7d
#define LED_7_SEGMENT_NUM7 	0x27
#define LED_7_SEGMENT_NUM8 	0x7f
#define LED_7_SEGMENT_NUM9 	0x6f

#define LED_7_SEGMENT_A			0x77
#define LED_7_SEGMENT_B			0x7f
#define LED_7_SEGMENT_C			0x39
#define LED_7_SEGMENT_D			0x3f
#define LED_7_SEGMENT_E			0x79
#define LED_7_SEGMENT_F			0x71
#define LED_7_SEGMENT_G			0x3d
#define LED_7_SEGMENT_H			0x76
#define LED_7_SEGMENT_I			0x06
#define LED_7_SEGMENT_J			0x1E
#define LED_7_SEGMENT_K			0x75
#define LED_7_SEGMENT_L			0x38
#define LED_7_SEGMENT_M			0x37
#define LED_7_SEGMENT_N			0x37
#define LED_7_SEGMENT_O			0x3f
#define LED_7_SEGMENT_P			0x73
#define LED_7_SEGMENT_Q			0x7B
#define LED_7_SEGMENT_R			0x7B
#define LED_7_SEGMENT_S			0x6d
#define LED_7_SEGMENT_T			0x31
#define LED_7_SEGMENT_U			0x3e
#define LED_7_SEGMENT_V			0x3E
#define LED_7_SEGMENT_W			0x7E
#define LED_7_SEGMENT_X			0x76
#define LED_7_SEGMENT_Y			0x72
#define LED_7_SEGMENT_Z			0x1B

#define LED_7_SEGMENT_a			0x5f
#define LED_7_SEGMENT_b			0x7c
#define LED_7_SEGMENT_c			0x58
#define LED_7_SEGMENT_d			0x5e
#define LED_7_SEGMENT_e			0x79
#define LED_7_SEGMENT_f			0x71
#define LED_7_SEGMENT_g			0x6f
#define LED_7_SEGMENT_h			0x74
#define LED_7_SEGMENT_i			0x10
#define LED_7_SEGMENT_j			0x1c
#define LED_7_SEGMENT_k			0x78
#define LED_7_SEGMENT_l			0x04
#define LED_7_SEGMENT_m			0x37
#define LED_7_SEGMENT_n			0x37
//#define LED_7_SEGMENT_n			0x54
#define LED_7_SEGMENT_o			0x5c
#define LED_7_SEGMENT_p			0x73
#define LED_7_SEGMENT_q			0x7B
#define LED_7_SEGMENT_r			0x50
#define LED_7_SEGMENT_s			0x6d
#define LED_7_SEGMENT_t			0x78
#define LED_7_SEGMENT_u			0x1C
#define LED_7_SEGMENT_v			0x3E
#define LED_7_SEGMENT_w			0x7E
#define LED_7_SEGMENT_X			0x76
#define LED_7_SEGMENT_y			0x6e
#define LED_7_SEGMENT_Z			0x1B
//for Fan H/V
#define LED_7_SEG_UNDER_LINE	0x08
#define LED_7_SEG_DASH_LINE		0x40
#define LED_7_SEG_UP_LINE		0x01
#define LED_7_SEG_LEFT				0x30	//Left
#define LED_7_SEG_RIGHT			0x06	//Right

//ROW1
#define LED_FILTER_CLEAN_BIT			0X01//0x01<<0//led36		
//#define LED_RHYTHMIC_MODE_BIT					0x01<<1//LED1
//#define LED_TIMER_BIT							0x01<<2//LED38
//#define LED_OSCILLATING_ANGLE120_BIT				0x01<<3//LED50
//#define LED_ION_MODE_BIT						0x01<<4//LED47
//#define LED_VERTICAL_LOUWER_SWING_BIT			0x01<<5//LED41
//#define LED_HORIZONTAL_OSCILLATING_BIT			0x01<<6//LED42
#define LED_CHILD_LOCK_SIGN_BIT		0X80//0x01<<7//LED53		
#define NOT_LED_FILTER_CLEAN_BIT		0XFE//led36		
//#define LED_RHYTHMIC_MODE_BIT					0x01<<1//LED1
//#define LED_TIMER_BIT							0x01<<2//LED38
//#define LED_OSCILLATING_ANGLE120_BIT				0x01<<3//LED50
//#define LED_ION_MODE_BIT						0x01<<4//LED47
//#define LED_VERTICAL_LOUWER_SWING_BIT			0x01<<5//LED41
//#define LED_HORIZONTAL_OSCILLATING_BIT			0x01<<6//LED42
#define NOT_LED_CHILD_LOCK_SIGN_BIT		0X7F//LED53		


//ROW2
#define LED_ON_TIMER_BIT									0X01//0x01<<0//LED54		
#define LED_TIMER_1_BIT									0X02//0x01<<1//LED55
#define LED_TIMER_2_BIT									0X04//0x01<<2//LED56
#define LED_OFF_TIMER_BIT								0X08//0x01<<3//LED57		
#define LED_WATCH_RED_BIT								0X10//0x01<<4//LED58
#define LED_TIMER_4_BIT									0X20//0x01<<5//LED59
#define LED_TIMER_6_BIT									0X40//0x01<<6//LED67
#define LED_CLOTHING_DEODORANT_BIT					0X80//0x01<<7//LED68

#define NOT_LED_ON_TIMER_BIT							0XFE//LED54		
#define NOT_LED_TIMER_1_BIT								0xFD//LED55
#define NOT_LED_TIMER_2_BIT								0xFB//LED56
#define NOT_LED_OFF_TIMER_BIT							0xF7//LED57		
#define NOT_LED_WATCH_RED_BIT						0xEF//LED58
#define NOT_LED_TIMER_4_BIT								0xDF//LED59
#define NOT_LED_TIMER_6_BIT								0xBF//LED67
#define NOT_LED_CLOTHING_DEODORANT_BIT			0x7F//LED68


//ROW3
//#define NOT_LED_OSCILLATING_ANGLE90_BIT								0x01<<0//LED60
#define LED_CHILD_LOCK_INDICATION_BIT				0X02//0x01<<1//LED62
#define LED_PLASMACLUSTER_SHOWER_BIT				0X04//0x01<<2//LED64			
#define LED_AIR_VOLME_SETTING_INDICATION_BIT		0X08//0x01<<3//LED69			
#define LED_WATCH_GREEN_BIT							0X10//0x01<<4//LED58
#define LED_TIMER_H_BIT									0X20//0x01<<5//LED71
#define LED_WARNING_BUZZER_BIT						0X40//0x01<<6//LED72
#define LED_ANGLE_SETTING_INDICATION_BIT			0X80//0x01<<7//LED70	

#define NOT_LED_CHILD_LOCK_INDICATION_BIT				0xFD//LED62
#define NOT_LED_PLASMACLUSTER_SHOWER_BIT			0xFB//LED64			
#define NOT_LED_AIR_VOLME_SETTING_INDICATION_BIT	0xF7//LED69			
#define NOT_LED_WATCH_GREEN_BIT							0xEF//LED58
#define NOT_LED_TIMER_H_BIT								0xDF//LED71
#define NOT_LED_WARNING_BUZZER_BIT						0xBF//LED72
#define NOT_LED_ANGLE_SETTING_INDICATION_BIT		0x7F//LED70	
//ROW4: right 7Seg

//ROW5: Left 7Seg

#define LED_OFF		0x00
#define LED_ON		0xFF
#define LED_7SEG_ON		0x7F
#define LED_7SEG_NUM		0xFF


#define DISPLAY_NO_DISAPPEAR	0xFF
extern BYTE bRow7SegLedShowData[5];
extern BOOL fg7SegHexShow;
#define b7SegLeftShow			bRow7SegLedShowData[4]
#define b7SegRightShow		bRow7SegLedShowData[3]
void vDisplay7SegLedTimer(void);
//void vDisplayRowShiftTimer(void);
void vDisplay7segLedAllOn(void);
void vDisplay7segLedAllOff(void);
//extern const BYTE bLedNumber[16];
#define vDisplay7SegMessageClear()			{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}			

#define vDisplay7SegShowHiOn()				{b7SegLeftShow=LED_7_SEGMENT_H;b7SegRightShow=LED_7_SEGMENT_i;}				
#define vDisplay7SegShowHiOff()				{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}

#define vDisplay7SegShowNoOn()				{b7SegLeftShow=LED_7_SEGMENT_N;b7SegRightShow=LED_7_SEGMENT_o;}			
#define vDisplay7SegShowNoOff()				{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}			

#define vDisplay7SegShowPOn()				{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_7_SEGMENT_P;}				
#define vDisplay7SegShowPOff()				{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}				

#define vDisplay7SegShowLoOn()				{b7SegLeftShow=LED_7_SEGMENT_L;b7SegRightShow=LED_7_SEGMENT_o;}		
#define vDisplay7SegShowLoOff()				{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}		

#define vDisplay7SegShowUnderLineOn()				{b7SegLeftShow=LED_7_SEG_UNDER_LINE;b7SegRightShow=LED_7_SEG_UNDER_LINE;}		
#define vDisplay7SegShowUnderLineOff()				{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}		

#define vDisplay7SegShowHorizontalOn()			{b7SegLeftShow=LED_7_SEG_DASH_LINE;b7SegRightShow=LED_7_SEG_DASH_LINE;}		
#define vDisplay7SegShowHorizontalOff()			{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}		

#define vDisplay7SegShowUpperOn()				{b7SegLeftShow=LED_7_SEG_UP_LINE;b7SegRightShow=LED_7_SEG_UP_LINE;}		
#define vDisplay7SegShowUpperOff()				{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}		

#define vDisplay7SegShowLeftOn()					{b7SegLeftShow=LED_7_SEG_LEFT;b7SegRightShow=LED_OFF;}
#define vDisplay7SegShowLeftOff()					{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}

#define vDisplay7SegShowLeftMiddleOn()			{b7SegLeftShow=LED_7_SEG_RIGHT;b7SegRightShow=LED_OFF;}					
#define vDisplay7SegShowLeftMiddleOff()			{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}					

#define vDisplay7SegShowRightMiddleOn()			{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_7_SEG_LEFT;}					
#define vDisplay7SegShowRightMiddleOff()			{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}					

#define vDisplay7SegShowRightOn()			{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_7_SEG_RIGHT;}					
#define vDisplay7SegShowRightOff()			{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}					

#define vDisplay7SegShowU3On()			{b7SegLeftShow=LED_7_SEGMENT_U;b7SegRightShow=LED_7_SEGMENT_NUM3;}							
#define vDisplay7SegShowU3Off()			{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}							

#define vDisplay7SegShowHexNumOn(bHexNumber)		{fg7SegHexShow=TRUE;b7SegLeftShow=bHexNumber;b7SegRightShow=LED_7SEG_NUM;}	
#define vDisplay7SegShowHexNumOff()			{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}		

#define vDisplay7SegShowDecNumOn(bDecNumber)			{fg7SegHexShow=FALSE;b7SegLeftShow=bDecNumber;b7SegRightShow=LED_7SEG_NUM;}			
#define vDisplay7SegShowDecNumOff()			{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}			

#define vDisplayLEDFilterCleanOn()			{bRow7SegLedShowData[0]|=LED_FILTER_CLEAN_BIT;}	
#define vDisplayLEDFilterCleanOff()			{bRow7SegLedShowData[0]&=NOT_LED_FILTER_CLEAN_BIT;}		

#define vDisplayLEDChildLockSignOn()			{bRow7SegLedShowData[0]|=LED_CHILD_LOCK_SIGN_BIT;}				
#define vDisplayLEDChildLockSignOff()			{bRow7SegLedShowData[0]&=NOT_LED_CHILD_LOCK_SIGN_BIT;}				

#define vDisplayLEDOnTimerOn()			{bRow7SegLedShowData[1]|=LED_ON_TIMER_BIT;}					
#define vDisplayLEDOnTimerOff()			{bRow7SegLedShowData[1]&=NOT_LED_ON_TIMER_BIT;}					

#define vDisplayLEDTimer1On()			{bRow7SegLedShowData[1]|=LED_TIMER_1_BIT;}					
#define vDisplayLEDTimer1Off()			{bRow7SegLedShowData[1]&=NOT_LED_TIMER_1_BIT;}					

#define vDisplayLEDTimer2On()			{bRow7SegLedShowData[1]|=LED_TIMER_2_BIT;}					
#define vDisplayLEDTimer2Off()			{bRow7SegLedShowData[1]&=NOT_LED_TIMER_2_BIT;}					

#define vDisplayLEDOffTimerOn()			{bRow7SegLedShowData[1]|=LED_OFF_TIMER_BIT;}						
#define vDisplayLEDOffTimerOff()			{bRow7SegLedShowData[1]&=NOT_LED_OFF_TIMER_BIT;}						

#define vDisplayLEDWatchRedOn()			{bRow7SegLedShowData[1]|=LED_WATCH_RED_BIT;}					
#define vDisplayLEDWatchRedOff()			{bRow7SegLedShowData[1]&=NOT_LED_WATCH_RED_BIT;}					

#define vDisplayLEDTimer4On()			{bRow7SegLedShowData[1]|=LED_TIMER_4_BIT;}					
#define vDisplayLEDTimer4Off()			{bRow7SegLedShowData[1]&=NOT_LED_TIMER_4_BIT;}					

#define vDisplayLEDTimer6On()			{bRow7SegLedShowData[1]|=LED_TIMER_6_BIT;}					
#define vDisplayLEDTimer6Off()			{bRow7SegLedShowData[1]&=NOT_LED_TIMER_6_BIT;}					

#define vDisplayLEDClothingDeodorantOn()			{bRow7SegLedShowData[1]|=LED_CLOTHING_DEODORANT_BIT;}			
#define vDisplayLEDClothingDeodorantOff()			{bRow7SegLedShowData[1]&=NOT_LED_CLOTHING_DEODORANT_BIT;}			

#define vDisplayLEDChildLockIndicationOn()			{bRow7SegLedShowData[2]|=LED_CHILD_LOCK_INDICATION_BIT;}			
#define vDisplayLEDChildLockIndicationOff()			{bRow7SegLedShowData[2]&=NOT_LED_CHILD_LOCK_INDICATION_BIT;}			

#define vDisplayLEDPlasmaclusterShowerOn()			{bRow7SegLedShowData[2]|=LED_PLASMACLUSTER_SHOWER_BIT;}				
#define vDisplayLEDPlasmaclusterShowerOff()			{bRow7SegLedShowData[2]&=NOT_LED_PLASMACLUSTER_SHOWER_BIT;}				

#define vDisplayLEDAirVolumeSettingIndicationOn()			{bRow7SegLedShowData[2]|=LED_AIR_VOLME_SETTING_INDICATION_BIT;}				
#define vDisplayLEDAirVolumeSettingIndicationOff()			{bRow7SegLedShowData[2]&=NOT_LED_AIR_VOLME_SETTING_INDICATION_BIT;}				

#define vDisplayLEDWatchGreenOn()			{bRow7SegLedShowData[2]|=LED_WATCH_GREEN_BIT;}				
#define vDisplayLEDWatchGreenOff()			{bRow7SegLedShowData[2]&=NOT_LED_WATCH_GREEN_BIT;}				

#define vDisplayLEDTimerHOn()			{bRow7SegLedShowData[2]|=LED_TIMER_H_BIT;}					
#define vDisplayLEDTimerHOff()			{bRow7SegLedShowData[2]&=NOT_LED_TIMER_H_BIT;}					

#define vDisplayLEDWarningBuzzerOn()			{bRow7SegLedShowData[2]|=LED_WARNING_BUZZER_BIT;}				
#define vDisplayLEDWarningBuzzerOff()			{bRow7SegLedShowData[2]&=NOT_LED_WARNING_BUZZER_BIT;}				

#define vDisplayLEDAngleSettingIndicationOn()			{bRow7SegLedShowData[2]|=LED_ANGLE_SETTING_INDICATION_BIT;}		
#define vDisplayLEDAngleSettingIndicationOff()			{bRow7SegLedShowData[2]&=NOT_LED_ANGLE_SETTING_INDICATION_BIT;}		

void vDisplayShowAirVolume(BYTE bDecNumber);
void vDisplayShowOscillateAngle(BYTE bOscillateAngle);		
void vDisplayShowLouverAngle(BYTE bLouverAngle);

#define vDisplay7SegShowAirVolumeOn(bDecNumber)								{vDisplayShowAirVolume(bDecNumber);}	
#define vDisplay7SegShowAirVolumeOff()										{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}	

#define vDisplay7SegShowOscillateAngleOn(bOscillateAngle)						{vDisplayShowOscillateAngle(bOscillateAngle);}		
#define vDisplay7SegShowOscillateAngleOff()									{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}		

#define vDisplay7SegShowLouverAngleOn(bLouverAngle)							{vDisplayShowLouverAngle(bLouverAngle);}
#define vDisplay7SegShowLouverAngleOff()										{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}

#else
#define vDisplay7SegLedTimer()
#define vDisplay7segLedAllOn()
#define vDisplay7segLedAllOff()
#define vDisplay7SegMessageClear()						

#define vDisplay7SegShowHiOn()								
#define vDisplay7SegShowHiOff()				
#define vDisplay7SegShowHiBlinkOn(bTime)				
#define vDisplay7SegShowHiBlinkOff()				
#define vDisplay7SegShowHiAutoOff(bTime)				

#define vDisplay7SegShowNoOn()							
#define vDisplay7SegShowNoOff()							
#define vDisplay7SegShowNoBlinkOn(bTime)				
#define vDisplay7SegShowNoBlinkOff()				
#define vDisplay7SegShowNoAutoOff(bTime)				

#define vDisplay7SegShowPOn()								
#define vDisplay7SegShowPOff()								
#define vDisplay7SegShowPBlinkOn(bTime)				
#define vDisplay7SegShowPBlinkOff()				
#define vDisplay7SegShowPAutoOff(bTime)				

#define vDisplay7SegShowLoOn()						
#define vDisplay7SegShowLoOff()						
#define vDisplay7SegShowLoBlinkOn(bTime)				
#define vDisplay7SegShowLoBlinkOff()				
#define vDisplay7SegShowLoAutoOff(bTime)			

#define vDisplay7SegShowUnderLineOn()						
#define vDisplay7SegShowUnderLineOff()						
#define vDisplay7SegShowUnderLineBlinkOn(bTime)				
#define vDisplay7SegShowUnderLineBlinkOff()				
#define vDisplay7SegShowUnderLineAutoOff(bTime)			

#define vDisplay7SegShowHorizontalOn()					
#define vDisplay7SegShowHorizontalOff()					
#define vDisplay7SegShowHorizontalBlinkOn(bTime)			
#define vDisplay7SegShowHorizontalBlinkOff()			
#define vDisplay7SegShowHorizontalAutoOff(bTime)	

#define vDisplay7SegShowUpperOn()						
#define vDisplay7SegShowUpperOff()						
#define vDisplay7SegShowUpperBlinkOn(bTime)		
#define vDisplay7SegShowUpperBlinkOff()			
#define vDisplay7SegShowUpperAutoOff(bTime)			

#define vDisplay7SegShowLeftOn()					
#define vDisplay7SegShowLeftOff()					
#define vDisplay7SegShowLeftBlinkOn(bTime)		
#define vDisplay7SegShowLeftBlinkOff()				
#define vDisplay7SegShowLeftAutoOff(bTime)		

#define vDisplay7SegShowLeftMiddleOn()								
#define vDisplay7SegShowLeftMiddleOff()								
#define vDisplay7SegShowLeftMiddleBlinkOn(bTime)			
#define vDisplay7SegShowLeftMiddleBlinkOff()						
#define vDisplay7SegShowLeftMiddleAutoOff(bTime)			

#define vDisplay7SegShowRightMiddleOn()								
#define vDisplay7SegShowRightMiddleOff()								
#define vDisplay7SegShowRightMiddleBlinkOn(bTime)			
#define vDisplay7SegShowRightMiddleBlinkOff()						
#define vDisplay7SegShowRightMiddleAutoOff(bTime)			

#define vDisplay7SegShowRightOn()								
#define vDisplay7SegShowRightOff()								
#define vDisplay7SegShowRightBlinkOn(bTime)			
#define vDisplay7SegShowRightBlinkOff()						
#define vDisplay7SegShowRightAutoOff(bTime)			

#define vDisplay7SegShowU3On()										
#define vDisplay7SegShowU3Off()										
#define vDisplay7SegShowU3BlinkOn(bTime)						
#define vDisplay7SegShowU3BlinkOff()									
#define vDisplay7SegShowU3AutoOff(bTime)					

#define vDisplay7SegShowHexNumOn(bHexNumber)			
#define vDisplay7SegShowHexNumOff()					
#define vDisplay7SegShowHexNumBlinkOn(bHexNumber,bTime)		
#define vDisplay7SegShowHexNumBlinkOff()					
#define vDisplay7SegShowHexNumAutoOff(bHexNumber,bTime)		

#define vDisplay7SegShowDecNumOn(bDecNumber)						
#define vDisplay7SegShowDecNumOff()						
#define vDisplay7SegShowDecNumBlinkOn(bDecNumber,bTime)		
#define vDisplay7SegShowDecNumBlinkOff()		
#define vDisplay7SegShowDecNumAutoOff(bDecNumber,bTime)	


#define vDisplayLEDFilterCleanOn()				
#define vDisplayLEDFilterCleanOff()					
#define vDisplayLEDFilterCleanBlinkOn(bTime)					
#define vDisplayLEDFilterCleanBlinkOff()					
#define vDisplayLEDFilterCleanAutoOff(bTime)					

#define vDisplayLEDChildLockSignOn()							
#define vDisplayLEDChildLockSignOff()							
#define vDisplayLEDChildLockSignBlinkOn(bTime)						
#define vDisplayLEDChildLockSignBlinkOff()								
#define vDisplayLEDChildLockSignAutoOff(bTime)						

#define vDisplayLEDOnTimerOn()								
#define vDisplayLEDOnTimerOff()								
#define vDisplayLEDOnTimerOnBlinkOn(bTime)							
#define vDisplayLEDOnTimerOnBlinkOff()									
#define vDisplayLEDOnTimerOnAutoOff(bTime)							

#define vDisplayLEDTimer1On()								
#define vDisplayLEDTimer1Off()								
#define vDisplayLEDTimer1BlinkOn(bTime)							
#define vDisplayLEDTimer1BlinkOff()									
#define vDisplayLEDTimer1AutoOff(bTime)							

#define vDisplayLEDTimer2On()								
#define vDisplayLEDTimer2Off()								
#define vDisplayLEDTimer2BlinkOn(bTime)							
#define vDisplayLEDTimer2BlinkOff()									
#define vDisplayLEDTimer2AutoOff(bTime)							

#define vDisplayLEDOffTimerOn()									
#define vDisplayLEDOffTimerOff()									
#define vDisplayLEDOffTimerBlinkOn(bTime)								
#define vDisplayLEDOffTimerBlinkOff()										
#define vDisplayLEDOffTimerAutoOff(bTime)								

#define vDisplayLEDWatchRedOn()								
#define vDisplayLEDWatchRedOff()								
#define vDisplayLEDWatchRedBlinkOn(bTime)							
#define vDisplayLEDWatchRedBlinkOff()									
#define vDisplayLEDWatchRedAutoOff(bTime)							

#define vDisplayLEDTimer4On()								
#define vDisplayLEDTimer4Off()								
#define vDisplayLEDTimer4BlinkOn(bTime)							
#define vDisplayLEDTimer4BlinkOff()									
#define vDisplayLEDTimer4AutoOff(bTime)							

#define vDisplayLEDTimer6On()								
#define vDisplayLEDTimer6Off()								
#define vDisplayLEDTimer6BlinkOn(bTime)							
#define vDisplayLEDTimer6BlinkOff()									
#define vDisplayLEDTimer6AutoOff(bTime)							

#define vDisplayLEDClothingDeodorantOn()						
#define vDisplayLEDClothingDeodorantOff()						
#define vDisplayLEDClothingDeodorantBlinkOn(bTime)					
#define vDisplayLEDClothingDeodorantBlinkOff()							
#define vDisplayLEDClothingDeodorantAutoOff(bTime)					

#define vDisplayLEDChildLockIndicationOn()						
#define vDisplayLEDChildLockIndicationOff()						
#define vDisplayLEDChildLockIndicationBlinkOn(bTime)					
#define vDisplayLEDChildLockIndicationBlinkOff()							
#define vDisplayLEDChildLockIndicationAutoOff(bTime)					

#define vDisplayLEDPlasmaclusterShowerOn()							
#define vDisplayLEDPlasmaclusterShowerOff()							
#define vDisplayLEDPlasmaclusterShowerBlinkOn(bTime)								
#define vDisplayLEDPlasmaclusterShowerBlinkOff()										
#define vDisplayLEDPlasmaclusterShowerAutoOff(bTime)							

#define vDisplayLEDAirVolumeSettingIndicationOn()							
#define vDisplayLEDAirVolumeSettingIndicationOff()							
#define vDisplayLEDAirVolumeSettingIndicationBlinkOn(bTime)						
#define vDisplayLEDAirVolumeSettingIndicationBlinkOff()								
#define vDisplayLEDAirVolumeSettingIndicationAutoOff(bTime)						

#define vDisplayLEDWatchGreenOn()							
#define vDisplayLEDWatchGreenOff()							
#define vDisplayLEDWatchGreenBlinkOn(bTime)						
#define vDisplayLEDWatchGreenBlinkOff()								
#define vDisplayLEDWatchGreenAutoOff(bTime)						

#define vDisplayLEDTimerHOn()								
#define vDisplayLEDTimerHOff()								
#define vDisplayLEDTimerHBlinkOn(bTime)							
#define vDisplayLEDTimerHBlinkOff()									
#define vDisplayLEDTimerHAutoOff(bTime)							

#define vDisplayLEDWarningBuzzerOn()							
#define vDisplayLEDWarningBuzzerOff()							
#define vDisplayLEDWarningBuzzerBlinkOn(bTime)						
#define vDisplayLEDWarningBuzzerBlinkOff()								
#define vDisplayLEDWarningBuzzerAutoOff(bTime)						

#define vDisplayLEDAngleSettingIndicationOn()					
#define vDisplayLEDAngleSettingIndicationOff()					
#define vDisplayLEDAngleSettingIndicationBlinkOn(bTime)				
#define vDisplayLEDAngleSettingIndicationBlinkOff()						
#define vDisplayLEDAngleSettingIndicationAutoOff(bTime)				


#define vDisplay7SegShowAirVolumeOn(bDecNumber)									
#define vDisplay7SegShowAirVolumeOff()											
#define vDisplay7SegShowAirVolumeBlinkOn(bDecNumber,bTime)						
#define vDisplay7SegShowAirVolumeBlinkOff()									
#define vDisplay7SegShowAirVolumeAutoOff(bDecNumber,bTime)						

#define vDisplay7SegShowOscillateAngleOn(bOscillateAngle)								
#define vDisplay7SegShowOscillateAngleOff()											
#define vDisplay7SegShowOscillateAngleBlinkOn(bOscillateAngle,bBlinkTime)			
#define vDisplay7SegShowOscillateAngleBlinkOff()								
#define vDisplay7SegShowOscillateAngleAutoOff(bOscillateAngle,bOffTime)			

#define vDisplay7SegShowLouverAngleOn(bLouverAngle)							
#define vDisplay7SegShowLouverAngleOff()										
#define vDisplay7SegShowLouverAngleBlinkOn(bLouverAngle,bBlinkTime)				
#define vDisplay7SegShowLouverAngleBlinkOff()									
#define vDisplay7SegShowLouverAngleAutoOff(bLouverAngle,bOffTime)						

#define LED_OFF		0x00
#define LED_ON		0xFF

#endif	// 130325jac01&&&

//#define SHOW_3DIGITAL_NUMBER
#ifdef SHOW_3DIGITAL_NUMBER	//130323ha02***
void vShow3DigitalNumber(WORD wNumber);
#endif



#endif

