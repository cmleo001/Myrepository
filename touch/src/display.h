#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#ifdef DISPLAY_7SEG_FUNCTION

#define LED_7_SEGMENT_NUM0	0x3f
#define LED_7_SEGMENT_NUM1 	0x06
#define LED_7_SEGMENT_NUM2 	0x5b
#define LED_7_SEGMENT_NUM3 	0x4f
#define LED_7_SEGMENT_NUM4 	0x66
#define LED_7_SEGMENT_NUM5 	0x6d
#define LED_7_SEGMENT_NUM6 	0x7d
#define LED_7_SEGMENT_NUM7 	0x27
#define LED_7_SEGMENT_NUM8 	0x7f
#define LED_7_SEGMENT_NUM9 	0x6f
/*
#define LED_7_SEGMENT_A			0x77
#define LED_7_SEGMENT_a			0x5f
#define LED_7_SEGMENT_b			0x7c
#define LED_7_SEGMENT_C			0x39
#define LED_7_SEGMENT_d			0x5e
#define LED_7_SEGMENT_E			0x79
#define LED_7_SEGMENT_F			0x71
#define LED_7_SEGMENT_G			0x3d
#define LED_7_SEGMENT_H			0x76
#define LED_7_SEGMENT_i			0x10
#define LED_7_SEGMENT_L			0x38
#define LED_7_SEGMENT_P			0x73
#define LED_7_SEGMENT_U			0x3e
#define LED_7_SEGMENT_o			0x5c
#define LED_7_SEGMENT_n			0x37
*/

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
/*			// 130328jac01
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
*/	//130328jac01***

#define _RAM_ADDR_SHOW_DATA		@0x80
#define _RAM_ADDR_SHOW_DATA1		@0x80
#define _RAM_ADDR_SHOW_DATA2		@0x81
#define _RAM_ADDR_SHOW_DATA3		@0x82
#define _RAM_ADDR_SHOW_DATA4		@0x83
#define _RAM_ADDR_SHOW_DATA5		@0x84

#define _RAM_ADDR_BLINK_DATA		@0x85
#define _RAM_ADDR_BLINK_DATA1		@0x85
#define _RAM_ADDR_BLINK_DATA2		@0x86
#define _RAM_ADDR_BLINK_DATA3		@0x87
#define _RAM_ADDR_BLINK_DATA4		@0x88
#define _RAM_ADDR_BLINK_DATA5		@0x89

#define _RAM_ADDR_AUTOOFF_DATA		@0x8A
#define _RAM_ADDR_AUTOOFF_DATA1		@0x8A
#define _RAM_ADDR_AUTOOFF_DATA2		@0x8B
#define _RAM_ADDR_AUTOOFF_DATA3		@0x8C
//#define _RAM_ADDR_AUTOOFF_DATA4		@0x8D
//#define _RAM_ADDR_AUTOOFF_DATA5		@0x8E


static BYTE bRow7SegLedShowData[5]				_RAM_ADDR_SHOW_DATA;		//0x80/0x81/0x82/0x83/0x84
//ROW1
static BOOL LED_FILTER_CLEAN_BIT					_RAM_ADDR_SHOW_DATA1@0;	//led36	
static BOOL LED_TUBE_BIT						_RAM_ADDR_SHOW_DATA1@1;	//Tube  		// 130401jac01
static BOOL LED_CHILD_LOCK_SIGN_BIT				_RAM_ADDR_SHOW_DATA1@7;	//LED53		


//ROW2
static BOOL LED_ON_TIMER_BIT					_RAM_ADDR_SHOW_DATA2@0;	//LED54		
static BOOL LED_TIMER_1_BIT						_RAM_ADDR_SHOW_DATA2@1;	//LED55
static BOOL LED_TIMER_2_BIT						_RAM_ADDR_SHOW_DATA2@2;	//LED56
static BOOL LED_OFF_TIMER_BIT					_RAM_ADDR_SHOW_DATA2@3;	//LED57		
static BOOL LED_WATCH_RED_BIT					_RAM_ADDR_SHOW_DATA2@4;	//LED58
static BOOL LED_TIMER_4_BIT						_RAM_ADDR_SHOW_DATA2@5;	//LED59
static BOOL LED_TIMER_6_BIT						_RAM_ADDR_SHOW_DATA2@6;	//LED67
static BOOL LED_CLOTHING_BIT					_RAM_ADDR_SHOW_DATA2@7;	//LED68


//ROW3
static BOOL LED_CHILD_LOCK_IND_BIT				_RAM_ADDR_SHOW_DATA3@1;	//LED62
static BOOL LED_PLAS_SHOWER_BIT				_RAM_ADDR_SHOW_DATA3@2;	//LED64			
static BOOL LED_AIR_SETTING_IND_BIT				_RAM_ADDR_SHOW_DATA3@3;	//LED69			
static BOOL LED_WATCH_GREEN_BIT				_RAM_ADDR_SHOW_DATA3@4;	//LED58
static BOOL LED_TIMER_H_BIT						_RAM_ADDR_SHOW_DATA3@5;	//LED71
static BOOL LED_WARNING_BUZZER_BIT				_RAM_ADDR_SHOW_DATA3@6;	//LED72
static BOOL LED_ANGLE_SET_IND_BIT				_RAM_ADDR_SHOW_DATA3@7;	//LED70	
//ROW4: right 7Seg

//ROW5: Left 7Seg

static BYTE bRow7SegLedBlinkData[5]					_RAM_ADDR_BLINK_DATA;		//0x85/0x86/0x87/0x88/0x89
//ROW1
static BOOL LED_FILTER_CLEAN_BLINK_BIT				_RAM_ADDR_BLINK_DATA1@0;	//led36	
static BOOL LED_TUBE_BLINK_BIT					_RAM_ADDR_BLINK_DATA1@1;	//Tube  		// 130401jac01
static BOOL LED_CHILD_LOCK_SIGN_BLINK_BIT			_RAM_ADDR_BLINK_DATA1@7;	//LED53		


//ROW2
static BOOL LED_ON_TIMER_BLINK_BIT				_RAM_ADDR_BLINK_DATA2@0;	//LED54		
static BOOL LED_TIMER_1_BLINK_BIT					_RAM_ADDR_BLINK_DATA2@1;	//LED55
static BOOL LED_TIMER_2_BLINK_BIT					_RAM_ADDR_BLINK_DATA2@2;	//LED56
static BOOL LED_OFF_TIMER_BLINK_BIT				_RAM_ADDR_BLINK_DATA2@3;	//LED57		
static BOOL LED_WATCH_RED_BLINK_BIT				_RAM_ADDR_BLINK_DATA2@4;	//LED58
static BOOL LED_TIMER_4_BLINK_BIT					_RAM_ADDR_BLINK_DATA2@5;	//LED59
static BOOL LED_TIMER_6_BLINK_BIT					_RAM_ADDR_BLINK_DATA2@6;	//LED67
static BOOL LED_CLOTHING_BLINK_BIT				_RAM_ADDR_BLINK_DATA2@7;	//LED68


//ROW3
static BOOL LED_CHILD_LOCK_IND_BLINK_BIT			_RAM_ADDR_BLINK_DATA3@1;	//LED62
static BOOL LED_PLAS_SHOWER_BLINK_BIT			_RAM_ADDR_BLINK_DATA3@2;	//LED64			
static BOOL LED_AIR_SETTING_IND_BLINK_BIT			_RAM_ADDR_BLINK_DATA3@3;	//LED69			
static BOOL LED_WATCH_GREEN_BLINK_BIT			_RAM_ADDR_BLINK_DATA3@4;	//LED58
static BOOL LED_TIMER_H_BLINK_BIT					_RAM_ADDR_BLINK_DATA3@5;	//LED71
static BOOL LED_WARNING_BUZZER_BLINK_BIT			_RAM_ADDR_BLINK_DATA3@6;	//LED72
static BOOL LED_ANGLE_SET_IND_BLINK_BIT			_RAM_ADDR_BLINK_DATA3@7;	//LED70	
//ROW4: right 7Seg

//ROW5: Left 7Seg

static BYTE bRow7SegLedAutoOffData[3]				_RAM_ADDR_AUTOOFF_DATA;		//0x8A/0x8B/0x8C
//ROW1
static BOOL LED_FILTER_CLEAN_AUTOOFF_BIT			_RAM_ADDR_AUTOOFF_DATA1@0;	//led36	
static BOOL LED_TUBE_AUTOOFF_BIT					_RAM_ADDR_AUTOOFF_DATA1@1;	//Tube 		// 130401jac01
static BOOL LED_CHILD_LOCK_SIGN_AUTOOFF_BIT		_RAM_ADDR_AUTOOFF_DATA1@7;	//LED53		


//ROW2
static BOOL LED_ON_TIMER_AUTOOFF_BIT				_RAM_ADDR_AUTOOFF_DATA2@0;	//LED54		
static BOOL LED_TIMER_1_AUTOOFF_BIT				_RAM_ADDR_AUTOOFF_DATA2@1;	//LED55
static BOOL LED_TIMER_2_AUTOOFF_BIT				_RAM_ADDR_AUTOOFF_DATA2@2;	//LED56
static BOOL LED_OFF_TIMER_AUTOOFF_BIT				_RAM_ADDR_AUTOOFF_DATA2@3;	//LED57		
static BOOL LED_WATCH_RED_AUTOOFF_BIT			_RAM_ADDR_AUTOOFF_DATA2@4;	//LED58
static BOOL LED_TIMER_4_AUTOOFF_BIT				_RAM_ADDR_AUTOOFF_DATA2@5;	//LED59
static BOOL LED_TIMER_6_AUTOOFF_BIT				_RAM_ADDR_AUTOOFF_DATA2@6;	//LED67
static BOOL LED_CLOTHING_AUTOOFF_BIT				_RAM_ADDR_AUTOOFF_DATA2@7;	//LED68


//ROW3
static BOOL LED_CHILD_LOCK_IND_AUTOOFF_BIT		_RAM_ADDR_AUTOOFF_DATA3@1;	//LED62
static BOOL LED_PLAS_SHOWER_AUTOOFF_BIT			_RAM_ADDR_AUTOOFF_DATA3@2;	//LED64			
static BOOL LED_AIR_SETTING_IND_AUTOOFF_BIT		_RAM_ADDR_AUTOOFF_DATA3@3;	//LED69			
static BOOL LED_WATCH_GREEN_AUTOOFF_BIT			_RAM_ADDR_AUTOOFF_DATA3@4;	//LED58
static BOOL LED_TIMER_H_AUTOOFF_BIT				_RAM_ADDR_AUTOOFF_DATA3@5;	//LED71
static BOOL LED_WARNING_BUZZER_AUTOOFF_BIT		_RAM_ADDR_AUTOOFF_DATA3@6;	//LED72
static BOOL LED_ANGLE_SET_IND_AUTOOFF_BIT		_RAM_ADDR_AUTOOFF_DATA3@7;	//LED70				// 130328jac01&&&

#define LED_OFF		0x00
#define LED_ON		0xFF
#define LED_7SEG_ON		0x7F
#define LED_7SEG_NUM		0xFF


#define DISPLAY_NO_DISAPPEAR	0xFF
//extern BYTE bRow7SegLedShowData[5];			// 130328jac01***
//extern BYTE bRow7SegLedBlinkData[5];
//extern BYTE bRow7SegLedAutoOffData[3];					// 130328jac01&&&
#define b7SegLeftShow			bRow7SegLedShowData[4]
#define b7SegRightShow		bRow7SegLedShowData[3]
#define b7SegLeftBlink			bRow7SegLedBlinkData[4]
#define b7SegRightBlink		bRow7SegLedBlinkData[3]
//#define b7SegLeftAutoOff			bRow7SegLedAutoOffData[4]					// 130315ja01***
//#define b7SegRightAutoOff		bRow7SegLedAutoOffData[3]
extern BOOL fg7SegAutoOff;					// 130315ja01&&&
//extern BOOL fg7SegHexShow;	// 130423jac03
void vDisplay7SegLedTimer(void);
void vDisplayRowShiftTimer(void);
void vDisplay7segLedAllOn(void);
void vDisplay7segLedAllOff(void);
void vInitial7SegLedDisplay(void);			// 130328jac01
void vDisplay7segLedAndTouchLedAllOff(void); //130419gr01
void vDisplay7segLedAndTouchLedAllOn(void); //130419gr01

extern BYTE bDisplay7SegLedBlinkTime;
extern BYTE bDisplay7SegLedAutoOffTime;
extern const BYTE bLedNumber[16];
//#define vDisplay7SegMessageClear()			{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;b7SegLeftBlink=LED_OFF;b7SegRightBlink=LED_OFF;}			// 130415jac03		
void vDisplay7SegMessageClear(void);		// 130415jac03
void vDisplay7SegBlinkOff(void);		// 130416jac01
#define vDisplay7SegShowHiOn()				{fg7SegAutoOff=FALSE;b7SegLeftShow=LED_7_SEGMENT_H;b7SegRightShow=LED_7_SEGMENT_i;}			// 130328jac02		
#define vDisplay7SegShowHiOff()				{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}
#define vDisplay7SegShowHiBlinkOn(bTime)		{bDisplay7SegLedBlinkTime=bTime;b7SegLeftBlink=LED_7_SEGMENT_H;b7SegRightBlink=LED_7_SEGMENT_i;}		// 130401jac01***	
#define vDisplay7SegShowHiBlinkOff()			vDisplay7SegBlinkOff()		// 130416jac01	
#define vDisplay7SegShowHiAutoOff(bTime)		{bDisplay7SegLedAutoOffTime=bTime;b7SegLeftShow=LED_7_SEGMENT_H;b7SegRightShow=LED_7_SEGMENT_i;fg7SegAutoOff=TRUE;}							// 130315ja01

#define vDisplay7SegShowNoOn()				{fg7SegAutoOff=FALSE;b7SegLeftShow=LED_7_SEGMENT_N;b7SegRightShow=LED_7_SEGMENT_o;}			// 130328jac02			
#define vDisplay7SegShowNoOff()				{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}			
#define vDisplay7SegShowNoBlinkOn(bTime)		{bDisplay7SegLedBlinkTime=bTime;b7SegLeftBlink=LED_7_SEGMENT_N;b7SegRightBlink=LED_7_SEGMENT_o;}		
#define vDisplay7SegShowNoBlinkOff()			vDisplay7SegBlinkOff()		// 130416jac01	
#define vDisplay7SegShowNoAutoOff(bTime)		{bDisplay7SegLedAutoOffTime=bTime;b7SegLeftShow=LED_7_SEGMENT_N;b7SegRightShow=LED_7_SEGMENT_o;fg7SegAutoOff=TRUE;}							// 130315ja01

#define vDisplay7SegShowPOn()				{fg7SegAutoOff=FALSE;b7SegLeftShow=LED_OFF;b7SegRightShow=LED_7_SEGMENT_P;}		// 130328jac02					
#define vDisplay7SegShowPOff()				{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}				
#define vDisplay7SegShowPBlinkOn(bTime)		{bDisplay7SegLedBlinkTime=bTime;b7SegLeftBlink=LED_OFF;b7SegRightBlink=LED_7_SEGMENT_P;}		
#define vDisplay7SegShowPBlinkOff()			vDisplay7SegBlinkOff()		// 130416jac01	
#define vDisplay7SegShowPAutoOff(bTime)		{bDisplay7SegLedAutoOffTime=bTime;b7SegLeftShow=LED_OFF;b7SegRightShow=LED_7_SEGMENT_P;fg7SegAutoOff=TRUE;}							// 130315ja01

#define vDisplay7SegShowLoOn()				{fg7SegAutoOff=FALSE;b7SegLeftShow=LED_7_SEGMENT_L;b7SegRightShow=LED_7_SEGMENT_o;}		// 130328jac02			
#define vDisplay7SegShowLoOff()				{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}		
#define vDisplay7SegShowLoBlinkOn(bTime)		{bDisplay7SegLedBlinkTime=bTime;b7SegLeftBlink=LED_7_SEGMENT_L;b7SegRightBlink=LED_7_SEGMENT_o;}		
#define vDisplay7SegShowLoBlinkOff()			vDisplay7SegBlinkOff()		// 130416jac01	
#define vDisplay7SegShowLoAutoOff(bTime)		{bDisplay7SegLedAutoOffTime=bTime;b7SegLeftShow=LED_7_SEGMENT_L;b7SegRightShow=LED_7_SEGMENT_o;fg7SegAutoOff=TRUE;}						// 130315ja01

#define vDisplay7SegShowUnderLineOn()				{fg7SegAutoOff=FALSE;b7SegLeftShow=LED_7_SEG_UNDER_LINE;b7SegRightShow=LED_7_SEG_UNDER_LINE;}		// 130328jac02			
#define vDisplay7SegShowUnderLineOff()				{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}		
#define vDisplay7SegShowUnderLineBlinkOn(bTime)		{bDisplay7SegLedBlinkTime=bTime;b7SegLeftBlink=LED_7_SEG_UNDER_LINE;b7SegRightBlink=LED_7_SEG_UNDER_LINE;}		
#define vDisplay7SegShowUnderLineBlinkOff()			vDisplay7SegBlinkOff()		// 130416jac01	
#define vDisplay7SegShowUnderLineAutoOff(bTime)		{bDisplay7SegLedAutoOffTime=bTime;b7SegLeftShow=LED_7_SEG_UNDER_LINE;b7SegRightShow=LED_7_SEG_UNDER_LINE;fg7SegAutoOff=TRUE;}						// 130315ja01

#define vDisplay7SegShowHorizontalOn()			{fg7SegAutoOff=FALSE;b7SegLeftShow=LED_7_SEG_DASH_LINE;b7SegRightShow=LED_7_SEG_DASH_LINE;}		// 130328jac02			
#define vDisplay7SegShowHorizontalOff()			{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}		
#define vDisplay7SegShowHorizontalBlinkOn(bTime)	{bDisplay7SegLedBlinkTime=bTime;b7SegLeftBlink=LED_7_SEG_DASH_LINE;b7SegRightBlink=LED_7_SEG_DASH_LINE;}		
#define vDisplay7SegShowHorizontalBlinkOff()		vDisplay7SegBlinkOff()		// 130416jac01	
#define vDisplay7SegShowHorizontalAutoOff(bTime)	{bDisplay7SegLedAutoOffTime=bTime;b7SegLeftShow=LED_7_SEG_DASH_LINE;b7SegRightShow=LED_7_SEG_DASH_LINE;fg7SegAutoOff=TRUE;}					// 130315ja01

#define vDisplay7SegShowUpperOn()				{fg7SegAutoOff=FALSE;b7SegLeftShow=LED_7_SEG_UP_LINE;b7SegRightShow=LED_7_SEG_UP_LINE;}			// 130328jac02		
#define vDisplay7SegShowUpperOff()				{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}		
#define vDisplay7SegShowUpperBlinkOn(bTime)		{bDisplay7SegLedBlinkTime=bTime;b7SegLeftBlink=LED_7_SEG_UP_LINE;b7SegRightBlink=LED_7_SEG_UP_LINE;}
#define vDisplay7SegShowUpperBlinkOff()			vDisplay7SegBlinkOff()		// 130416jac01
#define vDisplay7SegShowUpperAutoOff(bTime)		{bDisplay7SegLedAutoOffTime=bTime;b7SegLeftShow=LED_7_SEG_UP_LINE;b7SegRightShow=LED_7_SEG_UP_LINE;fg7SegAutoOff=TRUE;}						// 130315ja01

#define vDisplay7SegShowLeftOn()					{fg7SegAutoOff=FALSE;b7SegLeftShow=LED_7_SEG_LEFT;b7SegRightShow=LED_OFF;}		// 130328jac02	
#define vDisplay7SegShowLeftOff()					{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}
#define vDisplay7SegShowLeftBlinkOn(bTime)		{bDisplay7SegLedBlinkTime=bTime;b7SegLeftBlink=LED_7_SEG_LEFT;b7SegRightBlink=LED_OFF;}
#define vDisplay7SegShowLeftBlinkOff()				vDisplay7SegBlinkOff()		// 130416jac01
#define vDisplay7SegShowLeftAutoOff(bTime)		{bDisplay7SegLedAutoOffTime=bTime;b7SegLeftShow=LED_7_SEG_LEFT;b7SegRightShow=LED_OFF;fg7SegAutoOff=TRUE;}					// 130315ja01

#define vDisplay7SegShowLeftMiddleOn()			{fg7SegAutoOff=FALSE;b7SegLeftShow=LED_7_SEG_RIGHT;b7SegRightShow=LED_OFF;}		// 130328jac02						
#define vDisplay7SegShowLeftMiddleOff()			{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}					
#define vDisplay7SegShowLeftMiddleBlinkOn(bTime)	{bDisplay7SegLedBlinkTime=bTime;b7SegLeftBlink=LED_7_SEG_RIGHT;b7SegRightBlink=LED_OFF;}		
#define vDisplay7SegShowLeftMiddleBlinkOff()		vDisplay7SegBlinkOff()		// 130416jac01		
#define vDisplay7SegShowLeftMiddleAutoOff(bTime)	{bDisplay7SegLedAutoOffTime=bTime;b7SegLeftShow=LED_7_SEG_RIGHT;b7SegRightShow=LED_OFF;fg7SegAutoOff=TRUE;}							// 130315ja01

#define vDisplay7SegShowRightMiddleOn()				{fg7SegAutoOff=FALSE;b7SegLeftShow=LED_OFF;b7SegRightShow=LED_7_SEG_LEFT;}		// 130328jac02					
#define vDisplay7SegShowRightMiddleOff()				{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}					
#define vDisplay7SegShowRightMiddleBlinkOn(bTime)		{bDisplay7SegLedBlinkTime=bTime;b7SegLeftBlink=LED_OFF;b7SegRightBlink=LED_7_SEG_LEFT;}		
#define vDisplay7SegShowRightMiddleBlinkOff()			vDisplay7SegBlinkOff()		// 130416jac01		
#define vDisplay7SegShowRightMiddleAutoOff(bTime)		{bDisplay7SegLedAutoOffTime=bTime;b7SegLeftShow=LED_OFF;b7SegRightShow=LED_7_SEG_LEFT;fg7SegAutoOff=TRUE;}							// 130315ja01

#define vDisplay7SegShowRightOn()					{fg7SegAutoOff=FALSE;b7SegLeftShow=LED_OFF;b7SegRightShow=LED_7_SEG_RIGHT;}		// 130328jac02						
#define vDisplay7SegShowRightOff()					{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}					
#define vDisplay7SegShowRightBlinkOn(bTime)			{bDisplay7SegLedBlinkTime=bTime;b7SegLeftBlink=LED_OFF;b7SegRightBlink=LED_7_SEG_RIGHT;}		
#define vDisplay7SegShowRightBlinkOff()				vDisplay7SegBlinkOff()		// 130416jac01		
#define vDisplay7SegShowRightAutoOff(bTime)			{bDisplay7SegLedAutoOffTime=bTime;b7SegLeftShow=LED_OFF;b7SegRightShow=LED_7_SEG_RIGHT;fg7SegAutoOff=TRUE;}							// 130315ja01

//#define vDisplay7SegShowLo()								
//#define vDisplay7SegShowLoBlink(bTime)					
//#define vDisplay7SegShowLoAutoOff(bTime)					

#define vDisplay7SegShowU3On()								{fg7SegAutoOff=FALSE;b7SegLeftShow=LED_7_SEGMENT_U;b7SegRightShow=LED_7_SEGMENT_NUM3;}		// 130328jac02								
#define vDisplay7SegShowU3Off()								{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}							
#define vDisplay7SegShowU3BlinkOn(bTime)						{bDisplay7SegLedBlinkTime=bTime;b7SegLeftBlink=LED_7_SEGMENT_U;b7SegRightBlink=LED_7_SEGMENT_NUM3;}					
#define vDisplay7SegShowU3BlinkOff()							vDisplay7SegBlinkOff()		// 130416jac01					
#define vDisplay7SegShowU3AutoOff(bTime)						{bDisplay7SegLedAutoOffTime=bTime;b7SegLeftShow=LED_7_SEGMENT_U;b7SegRightShow=LED_7_SEGMENT_NUM3;fg7SegAutoOff=TRUE;}									// 130315ja01

//#define vDisplay7SegShowHexNumOn(bHexNumber)				{fg7SegAutoOff=FALSE;fg7SegHexShow=TRUE;b7SegLeftShow=bHexNumber;b7SegRightShow=LED_7SEG_NUM;}	// 130328jac02	//130419ha01
void vDisplay7SegShowHexNumOn(BYTE bHexNumber);	//130419ha01
#define vDisplay7SegShowHexNumOff()							{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}		
//#define vDisplay7SegShowHexNumBlinkOn(bHexNumber,bTime)		{fg7SegHexShow=TRUE;bDisplay7SegLedBlinkTime=bTime;b7SegLeftBlink=bHexNumber;b7SegRightBlink=LED_7SEG_NUM;}	// 130423jac03***
#define vDisplay7SegShowHexNumBlinkOff()						vDisplay7SegBlinkOff()		// 130416jac01	
//#define vDisplay7SegShowHexNumAutoOff(bHexNumber,bTime)		{fg7SegHexShow=TRUE;bDisplay7SegLedAutoOffTime=bTime;b7SegLeftShow=bHexNumber;b7SegRightShow=LED_7SEG_NUM;fg7SegAutoOff=TRUE;}					// 130315ja01
void vDisplay7SegShowHexNumBlinkOn(BYTE bHexNumber,BYTE bTime);
void vDisplay7SegShowHexNumAutoOff(BYTE bHexNumber,BYTE bTime);

void vDisplay7SegShowDecNumBlinkOn(BYTE bDecNumber,BYTE bTime);
//#define vDisplay7SegShowDecNumOn(bDecNumber)				{fg7SegAutoOff=FALSE;fg7SegHexShow=FALSE;b7SegLeftShow=bDecNumber;b7SegRightShow=LED_7SEG_NUM;}	// 130328jac02	// 130403jac01	//130419ha01
void vDisplay7SegShowDecNumOn(BYTE bDecNumber);	//130419ha01
#define vDisplay7SegShowDecNumOff()							{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;}			
//#define vDisplay7SegShowDecNumBlinkOn(bDecNumber,bTime)		{fg7SegHexShow=FALSE;bDisplay7SegLedBlinkTime=bTime;b7SegLeftBlink=bDecNumber;b7SegRightBlink=LED_7SEG_NUM;}		// 130403jac01		// 130423jac03&&&
#define vDisplay7SegShowDecNumBlinkOff()						vDisplay7SegBlinkOff()		// 130416jac01
//#define vDisplay7SegShowDecNumAutoOff(bDecNumber,bTime)		{fg7SegHexShow=FALSE;bDisplay7SegLedAutoOffTime=bTime;b7SegLeftShow=bDecNumber;b7SegRightShow=LED_7SEG_NUM;fg7SegAutoOff=TRUE;}	// 130315ja01// 130403jac01	//130419ha01
void vDisplay7SegShowDecNumAutoOff(BYTE bDecNumber,BYTE bTime);	//130419ha01

/*
#define vDisplayLEDTubeWhiteOn()
#define vDisplayLEDTubeWhiteOff()
#define vDisplayLEDTubeWhiteBlinkOn(bTime)
#define vDisplayLEDTubeWhiteBlinkOff()
#define vDisplayLEDTubeWhiteAutoOff(bTime)
*/

#define vDisplayLEDFilterCleanOn()					{LED_FILTER_CLEAN_BIT=1;}				// 130328jac01***
#define vDisplayLEDFilterCleanOff()					{LED_FILTER_CLEAN_BIT=0;}		
#define vDisplayLEDFilterCleanBlinkOn(bTime)		{bDisplay7SegLedBlinkTime=bTime;LED_FILTER_CLEAN_BLINK_BIT=1;}			
#define vDisplayLEDFilterCleanBlinkOff()				{LED_FILTER_CLEAN_BIT=0;LED_FILTER_CLEAN_BLINK_BIT=0;}	
#define vDisplayLEDFilterCleanAutoOff(bTime)		{bDisplay7SegLedAutoOffTime=bTime;LED_FILTER_CLEAN_BIT=1;LED_FILTER_CLEAN_AUTOOFF_BIT=1;}			

#define vDisplayLEDTubeWhiteOn()					{LED_TUBE_BIT=1;}		// 130401jac01
#define vDisplayLEDTubeWhiteOff()					{LED_TUBE_BIT=0;}		// 130401jac01
#define vDisplayLEDTubeWhiteBlinkOn(bTime)		{bDisplay7SegLedBlinkTime=bTime;LED_TUBE_BLINK_BIT=1;}		// 130401jac01
#define vDisplayLEDTubeWhiteBlinkOff()				{LED_TUBE_BIT=0;LED_TUBE_BLINK_BIT=0;}		// 130401jac01
#define vDisplayLEDTubeWhiteAutoOff(bTime)		{bDisplay7SegLedAutoOffTime=bTime;LED_TUBE_BIT=1;LED_TUBE_AUTOOFF_BIT=1;}		// 130401jac01



#define vDisplayLEDChildLockSignOn()				{LED_CHILD_LOCK_SIGN_BIT=1;}				
#define vDisplayLEDChildLockSignOff()				{LED_CHILD_LOCK_SIGN_BIT=0;}				
#define vDisplayLEDChildLockSignBlinkOn(bTime)		{bDisplay7SegLedBlinkTime=bTime;LED_CHILD_LOCK_SIGN_BLINK_BIT=1;}				
#define vDisplayLEDChildLockSignBlinkOff()			{LED_CHILD_LOCK_SIGN_BIT=0;LED_CHILD_LOCK_SIGN_BLINK_BIT=0;}				
#define vDisplayLEDChildLockSignAutoOff(bTime)		{bDisplay7SegLedAutoOffTime=bTime;LED_CHILD_LOCK_SIGN_BIT=1;LED_CHILD_LOCK_SIGN_AUTOOFF_BIT=1;}				


#define vDisplayLEDOnTimerOn()					{LED_ON_TIMER_BIT=1;}					
#define vDisplayLEDOnTimerOff()					{LED_ON_TIMER_BIT=0;}					
#define vDisplayLEDOnTimerOnBlinkOn(bTime)		{bDisplay7SegLedBlinkTime=bTime;LED_ON_TIMER_BLINK_BIT=1;}					
#define vDisplayLEDOnTimerOnBlinkOff()			{LED_ON_TIMER_BIT=0;LED_ON_TIMER_BLINK_BIT=0;}					
#define vDisplayLEDOnTimerOnAutoOff(bTime)		{bDisplay7SegLedAutoOffTime=bTime;LED_ON_TIMER_BIT=1;LED_ON_TIMER_AUTOOFF_BIT=1;}					

#define vDisplayLEDTimer1On()					{LED_TIMER_1_BIT=1;}					
#define vDisplayLEDTimer1Off()					{LED_TIMER_1_BIT=0;}					
#define vDisplayLEDTimer1BlinkOn(bTime)			{bDisplay7SegLedBlinkTime=bTime;LED_TIMER_1_BLINK_BIT=1;}					
#define vDisplayLEDTimer1BlinkOff()				{LED_TIMER_1_BIT=0;LED_TIMER_1_BLINK_BIT=0;}					
#define vDisplayLEDTimer1AutoOff(bTime)			{bDisplay7SegLedAutoOffTime=bTime;LED_TIMER_1_BIT=1;LED_TIMER_1_BLINK_AUTOOFF_BIT=1;}					

#define vDisplayLEDTimer2On()					{LED_TIMER_2_BIT=1;}					
#define vDisplayLEDTimer2Off()					{LED_TIMER_2_BIT=0;}					
#define vDisplayLEDTimer2BlinkOn(bTime)			{bDisplay7SegLedBlinkTime=bTime;LED_TIMER_2_BLINK_BIT=1;}					
#define vDisplayLEDTimer2BlinkOff()				{LED_TIMER_2_BIT=0;LED_TIMER_2_BLINK_BIT=0;}					
#define vDisplayLEDTimer2AutoOff(bTime)			{bDisplay7SegLedAutoOffTime=bTime;LED_TIMER_2_BIT=1;LED_TIMER_2_AUTOOFF_BIT=1;}					

#define vDisplayLEDOffTimerOn()					{LED_OFF_TIMER_BIT=1;}						
#define vDisplayLEDOffTimerOff()					{LED_OFF_TIMER_BIT=0;}					
#define vDisplayLEDOffTimerBlinkOn(bTime)			{bDisplay7SegLedBlinkTime=bTime;LED_OFF_TIMER_BLINK_BIT=1;}						
#define vDisplayLEDOffTimerBlinkOff()				{LED_OFF_TIMER_BIT=0;LED_OFF_TIMER_BLINK_BIT=0;}						
#define vDisplayLEDOffTimerAutoOff(bTime)			{bDisplay7SegLedAutoOffTime=bTime;LED_OFF_TIMER_BIT=1;LED_OFF_TIMER_AUTOOFF_BIT=1;}						

#define vDisplayLEDWatchRedOn()					{LED_WATCH_RED_BIT=1;}					
#define vDisplayLEDWatchRedOff()					{LED_WATCH_RED_BIT=0;}					
#define vDisplayLEDWatchRedBlinkOn(bTime)		{bDisplay7SegLedBlinkTime=bTime;LED_WATCH_RED_BLINK_BIT=1;}					
#define vDisplayLEDWatchRedBlinkOff()				{LED_WATCH_RED_BIT=0;LED_WATCH_RED_BLINK_BIT=0;}					
#define vDisplayLEDWatchRedAutoOff(bTime)			{bDisplay7SegLedAutoOffTime=bTime;LED_WATCH_RED_BIT=1;LED_WATCH_RED_AUTOOFF_BIT=1;}					

#define vDisplayLEDTimer4On()								{LED_TIMER_4_BIT=1;}					
#define vDisplayLEDTimer4Off()								{LED_TIMER_4_BIT=0;}					
#define vDisplayLEDTimer4BlinkOn(bTime)						{bDisplay7SegLedBlinkTime=bTime;LED_TIMER_4_BLINK_BIT=1;}					
#define vDisplayLEDTimer4BlinkOff()							{LED_TIMER_4_BIT=0;LED_TIMER_4_BLINK_BIT=0;}					
#define vDisplayLEDTimer4AutoOff(bTime)						{bDisplay7SegLedAutoOffTime=bTime;LED_TIMER_4_BIT=1;LED_TIMER_4_AUTOOFF_BIT=1;}					

#define vDisplayLEDTimer6On()								{LED_TIMER_6_BIT=1;}					
#define vDisplayLEDTimer6Off()								{LED_TIMER_6_BIT=0;}					
#define vDisplayLEDTimer6BlinkOn(bTime)						{bDisplay7SegLedBlinkTime=bTime;LED_TIMER_6_BLINK_BIT=1;}					
#define vDisplayLEDTimer6BlinkOff()							{LED_TIMER_6_BIT=0;LED_TIMER_6_BLINK_BIT=0;}					
#define vDisplayLEDTimer6AutoOff(bTime)						{bDisplay7SegLedAutoOffTime=bTime;LED_TIMER_6_BIT=1;LED_TIMER_6_AUTOOFF_BIT=1;}					


/***********************************************************************************		// 130415jac02***

7		6		5		4		3		2		1		0
		6		4				Offtimer	2		1		ontimer

***********************************************************************************/
#define vDisplayLEDTimerAllOn()					{bRow7SegLedShowData[1]|=0x6F;LED_TIMER_H_BIT=1;}					
#define vDisplayLEDTimerAllOff()					{bRow7SegLedShowData[1]&=0x90;LED_TIMER_H_BIT=0;}					

#define vDisplayLEDTimer1hOn()					{LED_TIMER_1_BIT=1;LED_TIMER_H_BIT=1;}					
#define vDisplayLEDTimer1hOff()					{LED_TIMER_1_BIT=0;LED_TIMER_H_BIT=0;}					
#define vDisplayLEDTimer1hBlinkOn(bTime)			{bDisplay7SegLedBlinkTime=bTime;LED_TIMER_1_BLINK_BIT=1;LED_TIMER_H_BLINK_BIT=1;}					
#define vDisplayLEDTimer1hBlinkOff()				{LED_TIMER_1_BIT=0;LED_TIMER_1_BLINK_BIT=0;LED_TIMER_H_BIT=0;LED_TIMER_H_BLINK_BIT=0;}					
#define vDisplayLEDTimer1hAutoOff(bTime)			{bDisplay7SegLedAutoOffTime=bTime;LED_TIMER_1_BIT=1;LED_TIMER_1_BLINK_AUTOOFF_BIT=1;LED_TIMER_H_BIT=1;LED_TIMER_H_AUTOOFF_BIT=1;}					

#define vDisplayLEDTimer2hOn()					{LED_TIMER_2_BIT=1;LED_TIMER_H_BIT=1;}					
#define vDisplayLEDTimer2hOff()					{LED_TIMER_2_BIT=0;LED_TIMER_H_BIT=0;}					
#define vDisplayLEDTimer2hBlinkOn(bTime)			{bDisplay7SegLedBlinkTime=bTime;LED_TIMER_2_BLINK_BIT=1;LED_TIMER_H_BLINK_BIT=1;}					
#define vDisplayLEDTimer2hBlinkOff()				{LED_TIMER_2_BIT=0;LED_TIMER_2_BLINK_BIT=0;LED_TIMER_H_BLINK_BIT=0;}					
#define vDisplayLEDTimer2hAutoOff(bTime)			{bDisplay7SegLedAutoOffTime=bTime;LED_TIMER_2_BIT=1;LED_TIMER_2_AUTOOFF_BIT=1;LED_TIMER_H_BIT=1;LED_TIMER_H_AUTOOFF_BIT=1;}					

#define vDisplayLEDTimer4hOn()					{LED_TIMER_4_BIT=1;LED_TIMER_H_BIT=1;}					
#define vDisplayLEDTimer4hOff()					{LED_TIMER_4_BIT=0;LED_TIMER_H_BIT=1;}					
#define vDisplayLEDTimer4hBlinkOn(bTime)			{bDisplay7SegLedBlinkTime=bTime;LED_TIMER_4_BLINK_BIT=1;LED_TIMER_H_BLINK_BIT=1;}					
#define vDisplayLEDTimer4hBlinkOff()				{LED_TIMER_4_BIT=0;LED_TIMER_4_BLINK_BIT=0;LED_TIMER_H_BLINK_BIT=0;}					
#define vDisplayLEDTimer4hAutoOff(bTime)			{bDisplay7SegLedAutoOffTime=bTime;LED_TIMER_4_BIT=1;LED_TIMER_4_AUTOOFF_BIT=1;LED_TIMER_H_BIT=1;LED_TIMER_H_AUTOOFF_BIT=1;}					

#define vDisplayLEDTimer6hOn()					{LED_TIMER_6_BIT=1;LED_TIMER_H_BIT=1;}					
#define vDisplayLEDTimer6hOff()					{LED_TIMER_6_BIT=0;LED_TIMER_H_BIT=1;}					
#define vDisplayLEDTimer6hBlinkOn(bTime)			{bDisplay7SegLedBlinkTime=bTime;LED_TIMER_6_BLINK_BIT=1;LED_TIMER_H_BLINK_BIT=1;}					
#define vDisplayLEDTimer6hBlinkOff()				{LED_TIMER_6_BIT=0;LED_TIMER_6_BLINK_BIT=0;LED_TIMER_H_BLINK_BIT=0;}					
#define vDisplayLEDTimer6hAutoOff(bTime)			{bDisplay7SegLedAutoOffTime=bTime;LED_TIMER_6_BIT=1;LED_TIMER_6_AUTOOFF_BIT=1;LED_TIMER_H_BIT=1;LED_TIMER_H_AUTOOFF_BIT=1;}			// 130415jac02&&&				

#define vDisplayLEDClothingDeodorantOn()						{LED_CLOTHING_BIT=1;}			
#define vDisplayLEDClothingDeodorantOff()						{LED_CLOTHING_BIT=0;}			
#define vDisplayLEDClothingDeodorantBlinkOn(bTime)				{bDisplay7SegLedBlinkTime=bTime;LED_CLOTHING_BLINK_BIT=1;}			
#define vDisplayLEDClothingDeodorantBlinkOff()					{LED_CLOTHING_BIT=0;LED_CLOTHING_BLINK_BIT=0;}			
#define vDisplayLEDClothingDeodorantAutoOff(bTime)				{bDisplay7SegLedAutoOffTime=bTime;LED_CLOTHING_BIT=1;LED_CLOTHING_AUTOOFF_BIT=1;}			

#define vDisplayLEDChildLockIndicationOn()						{LED_CHILD_LOCK_IND_BIT=1;}			
#define vDisplayLEDChildLockIndicationOff()						{LED_CHILD_LOCK_IND_BIT=0;}			
#define vDisplayLEDChildLockIndicationBlinkOn(bTime)				{bDisplay7SegLedBlinkTime=bTime;LED_CHILD_LOCK_IND_BLINK_BIT=1;}			
#define vDisplayLEDChildLockIndicationBlinkOff()					{LED_CHILD_LOCK_IND_BIT=0;LED_CHILD_LOCK_IND_BLINK_BIT=0;}			
#define vDisplayLEDChildLockIndicationAutoOff(bTime)				{bDisplay7SegLedAutoOffTime=bTime;LED_CHILD_LOCK_IND_BIT=1;LED_CHILD_LOCK_IND_AUTOOFF_BIT=1;}			

#define vDisplayLEDPlasmaclusterShowerOn()					{LED_PLAS_SHOWER_BIT=1;}				
#define vDisplayLEDPlasmaclusterShowerOff()					{LED_PLAS_SHOWER_BIT=0;}				
#define vDisplayLEDPlasmaclusterShowerBlinkOn(bTime)			{bDisplay7SegLedBlinkTime=bTime;LED_PLAS_SHOWER_BLINK_BIT=1;}						
#define vDisplayLEDPlasmaclusterShowerBlinkOff()				{LED_PLAS_SHOWER_BIT=0;LED_PLAS_SHOWER_BLINK_BIT=0;}						
#define vDisplayLEDPlasmaclusterShowerAutoOff(bTime)			{bDisplay7SegLedAutoOffTime=bTime;LED_PLAS_SHOWER_BIT=1;LED_PLAS_SHOWER_ATTOOFF_BIT=1;}					

#define vDisplayLEDAirVolumeSettingIndicationOn()				{LED_AIR_SETTING_IND_BIT=1;}				
#define vDisplayLEDAirVolumeSettingIndicationOff()				{LED_AIR_SETTING_IND_BIT=0;}				
#define vDisplayLEDAirVolumeSettingIndicationBlinkOn(bTime)		{bDisplay7SegLedBlinkTime=bTime;LED_AIR_SETTING_IND_BLINK_BIT=1;}				
#define vDisplayLEDAirVolumeSettingIndicationBlinkOff()			{LED_AIR_SETTING_IND_BIT=0;LED_AIR_SETTING_IND_BLINK_BIT=0;}				
#define vDisplayLEDAirVolumeSettingIndicationAutoOff(bTime)		{bDisplay7SegLedAutoOffTime=bTime;LED_AIR_SETTING_IND_BIT=1;LED_AIR_SETTING_IND_AUTOOFF_BIT=1;}				

#define vDisplayLEDWatchGreenOn()							{LED_WATCH_GREEN_BIT=1;}				
#define vDisplayLEDWatchGreenOff()							{LED_WATCH_GREEN_BIT=0;}				
#define vDisplayLEDWatchGreenBlinkOn(bTime)					{bDisplay7SegLedBlinkTime=bTime;LED_WATCH_GREEN_BLINK_BIT=1;}				
#define vDisplayLEDWatchGreenBlinkOff()						{LED_WATCH_GREEN_BIT=0;LED_WATCH_GREEN_BLINK_BIT=0;}				
#define vDisplayLEDWatchGreenAutoOff(bTime)					{bDisplay7SegLedAutoOffTime=bTime;LED_WATCH_GREEN_BIT=1;LED_WATCH_GREEN_AUTOOFF_BIT=1;}				

#define vDisplayLEDTimerHOn()								{LED_TIMER_H_BIT=1;}					
#define vDisplayLEDTimerHOff()								{LED_TIMER_H_BIT=0;}					
#define vDisplayLEDTimerHBlinkOn(bTime)						{bDisplay7SegLedBlinkTime=bTime;LED_TIMER_H_BLINK_BIT=1;}					
#define vDisplayLEDTimerHBlinkOff()							{LED_TIMER_H_BIT=0;LED_TIMER_H_BLINK_BIT=0;}					
#define vDisplayLEDTimerHAutoOff(bTime)						{bDisplay7SegLedAutoOffTime=bTime;LED_TIMER_H_BIT=1;LED_TIMER_H_AUTOOFF_BIT=1;}					

#define vDisplayLEDWarningBuzzerOn()							{LED_WARNING_BUZZER_BIT=1;}				
#define vDisplayLEDWarningBuzzerOff()							{LED_WARNING_BUZZER_BIT=0;}				
#define vDisplayLEDWarningBuzzerBlinkOn(bTime)				{bDisplay7SegLedBlinkTime=bTime;LED_WARNING_BUZZER_BLINK_BIT=1;}				
#define vDisplayLEDWarningBuzzerBlinkOff()						{LED_WARNING_BUZZER_BIT=0;LED_WARNING_BUZZER_BLINK_BIT=0;}				
#define vDisplayLEDWarningBuzzerAutoOff(bTime)				{bDisplay7SegLedAutoOffTime=bTime;LED_WARNING_BUZZER_BIT=1;LED_WARNING_BUZZER_AUTOOFF_BIT=1;}				

#define vDisplayLEDAngleSettingIndicationOn()					{LED_ANGLE_SET_IND_BIT=1;LED_ANGLE_SET_IND_AUTOOFF_BIT=0;}	// 130417jac01	
#define vDisplayLEDAngleSettingIndicationOff()					{LED_ANGLE_SET_IND_BIT=0;fgOscillateAngleIsShowing=FALSE;}				//130423jac02
#define vDisplayLEDAngleSettingIndicationBlinkOn(bTime)			{bDisplay7SegLedBlinkTime=bTime;LED_ANGLE_SET_IND_BLINK_BIT=1;}		
#define vDisplayLEDAngleSettingIndicationBlinkOff()				{LED_ANGLE_SET_IND_BIT=0;LED_ANGLE_SET_IND_BLINK_BIT=0;}		
#define vDisplayLEDAngleSettingIndicationAutoOff(bTime)			{bDisplay7SegLedAutoOffTime=bTime;LED_ANGLE_SET_IND_BIT=1;LED_ANGLE_SET_IND_AUTOOFF_BIT=1;}			// 130328jac01&&&		// 130401jac01&&&		


void vDisplayShowAirVolume(BYTE bDecNumber);
void vDisplayShowAirVolumeBlink(BYTE bDecNumber,BYTE bTime);	
void vDisplayShowAirVolumeAutoOff(BYTE bDecNumber,BYTE bTime);	
void vDisplayShowOscillateAngle(BYTE bOscillateAngle);		
void vDisplayShowOscAngleBlink(BYTE bOscillateAngle,BYTE bBlinkTime);
void vDisplayShowOscAngleAutoOff(BYTE bOscillateAngle,BYTE bOffTime);
void vDisplayShowLouverAngle(BYTE bLouverAngle);
void vDisplayShowLouverAngleBlink(BYTE bLouverAngle,BYTE bBlinkTime);
void vDisplayShowLouverAngleAutoOff(BYTE bLouverAngle,BYTE bOffTime);		

#define vDisplay7SegShowAirVolumeOn(bDecNumber)								{vDisplayShowAirVolume(bDecNumber);}	
#define vDisplay7SegShowAirVolumeOff()										{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;vDisplayLEDAirVolumeSettingIndicationOff();}			// 130415jac02***
#define vDisplay7SegShowAirVolumeBlinkOn(bDecNumber,bTime)					{vDisplayShowAirVolumeBlink(bDecNumber,bTime);}	
#define vDisplay7SegShowAirVolumeBlinkOff()									{b7SegRightShow=LED_OFF;b7SegLeftShow=LED_OFF;b7SegLeftBlink=LED_OFF;b7SegRightBlink=LED_OFF;vDisplayLEDAirVolumeSettingIndicationBlinkOff();vDisplayLEDAirVolumeSettingIndicationOff();}
//#define vDisplay7SegShowAirVolumeAutoOff(bDecNumber,bTime)					{vDisplayShowAirVolumeAutoOff(bDecNumber,bTime);}	//130424Ke03
#define vDisplay7SegShowAirVolumeAutoOff(bDecNumber,bTime)				{bAirVolumeType=bDecNumber; bFanVolumeShowType=bTime;}	//130424Ke03	 //130426jac01

#define vDisplay7SegShowOscillateAngleOn(bOscillateAngle)						{vDisplayShowOscillateAngle(bOscillateAngle);}		
#define vDisplay7SegShowOscillateAngleOff()									{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;vDisplayLEDAngleSettingIndicationOff();}		
#define vDisplay7SegShowOscillateAngleBlinkOn(bOscillateAngle,bBlinkTime)			{vDisplayShowOscAngleBlink(bOscillateAngle,bBlinkTime);}
#define vDisplay7SegShowOscillateAngleBlinkOff()								{b7SegRightShow=LED_OFF;b7SegLeftShow=LED_OFF;b7SegLeftBlink=LED_OFF;b7SegRightBlink=LED_OFF;vDisplayLEDAngleSettingIndicationOff();vDisplayLEDAngleSettingIndicationBlinkOff();}
#define vDisplay7SegShowOscillateAngleAutoOff(bOscillateAngle,bOffTime)			{vDisplayShowOscAngleAutoOff(bOscillateAngle,bOffTime);}

#define vDisplay7SegShowLouverAngleOn(bLouverAngle)							{vDisplayShowLouverAngle(bLouverAngle);}
#define vDisplay7SegShowLouverAngleOff()										{b7SegLeftShow=LED_OFF;b7SegRightShow=LED_OFF;vDisplayLEDAngleSettingIndicationOff();}
#define vDisplay7SegShowLouverAngleBlinkOn(bLouverAngle,bBlinkTime)				{vDisplayShowLouverAngleBlink(bLouverAngle,bBlinkTime);}
#define vDisplay7SegShowLouverAngleBlinkOff()									{b7SegRightShow=LED_OFF;b7SegLeftShow=LED_OFF;b7SegLeftBlink=LED_OFF;b7SegRightBlink=LED_OFF;vDisplayLEDAngleSettingIndicationOff();vDisplayLEDAngleSettingIndicationBlinkOff();}		// 130415jac02&&&
#define vDisplay7SegShowLouverAngleAutoOff(bLouverAngle,bOffTime)				{vDisplayShowLouverAngleAutoOff(bLouverAngle,bOffTime);}		

#else
#define vDisplay7SegLedTimer()
#define vDisplayRowShiftTimer()
#define vDisplay7segLedAllOn()
#define vDisplay7segLedAllOff()
#define vDisplay7SegMessageClear()						
#define vInitial7SegLedDisplay()			// 130328jac01

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

//#define vDisplay7SegShowLo()								
//#define vDisplay7SegShowLoBlink(bTime)					
//#define vDisplay7SegShowLoAutoOff(bTime)					

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

#endif


#endif

