#ifndef _DEFINE_H_
#define _DEFINE_H_
//All same parameters about Main MCU and Touch MCU, please put in here.

typedef unsigned char 		BYTE;
typedef signed char 		INT8;
typedef unsigned short 	WORD;
typedef signed short 		INT16;
typedef unsigned long 		DWORD;
typedef signed long		INT32;
typedef bit				BOOL;
//#define BYTE		unsigned int
//#define WORD	unsigned short
//#define DWORD	unsigned long
//#define BOOL		bit

#define TRUE		1
#define FALSE	0

#define RESULT_FAIL		1
#define RESULT_SUCCESS	0

//{version unit,version decimal,month,day}   ex:0.50 2013/01/20
#define MCU_FIRMWARE_VERSION_UNIT			0
#define MCU_FIRMWARE_VERSION_DECIMAL		15
#define MCU_FIRMWARE_VERSION_YEAR			13
#define MCU_FIRMWARE_VERSION_MONTH			5
#define MCU_FIRMWARE_VERSION_DAY				6



/////////////////////////////////////////////////////////
//All Function Define.
////////////////////////////////////////////////////////
//#define QUEUE_USE_STRUCT
#define QUEUE_USE_ARRAY
#define MAIN_MCU_DO_POWER_ON_OFF_PROCESS	//130306a02v
//#define FULL_FUNCTION

#ifdef MAIN_MCU
//Main MCU
#define MIX_QUEUE_FUNCTION
#define MIX_QUEUE_MAX_NUMBER	30
//#define EVENT_QUEUE_FUNCTION
#define EEPROM_FUNCTION
#define I2C_HARDWARE_FUNCTION
//#define DISPLAY_7SEG_FUNCTION
#define OSCILLATE_MOTOR_FUNCTION
#define LOUVER_MOTOR_FUNCTION
#define TEMPERATURE_SENSOR_FUNCTION
#define HUMIDITY_SENSOR_FUNCTION
#define ION_SENSOR_FUNCTION
#define FAN_MOTOR_FUNCTION
#define PCI_FUNCTION
#define WATCH_MODE_FUNCTION
#define FAN_AUTO_ADJUST_EVERY_10MIN		// 130427jac02
#endif

#ifdef TOUCH_MCU
//Touch MCU
#define MIX_QUEUE_FUNCTION
#define MIX_QUEUE_MAX_NUMBER	50	//56 //130409Ke05//130420sh02
//#define EVENT_QUEUE_FUNCTION
#define IR_FUNCTION
//#define IR_COUNT_VALUE_USE_ARRAY_SAVE	//130306a01w
#define EEPROM_FUNCTION
#define I2C_HARDWARE_FUNCTION
#define DISPLAY_7SEG_FUNCTION
#define TOUCH_SENSOR_FUNCTION
#define DEMO_MODE_FUNCTION
//#define FUNCTION_CHECKER_MODE_FUNCTION
//#define PRODUCTION_LINE_MODE_FUNCTION
#define SERVICE_MONITOR_MODE_FUNCTION
#define MONITOR_MODE_FUNCTION
#define SPEED_UP_MODE_FUNCTION
#define ION_MODE_FUNCTION
#define WATCH_MODE_FUNCTION
#define ADC_FUNCTION
#endif


/////////////////////////////////////////////////////////
//Define the PCB version for compiler.
////////////////////////////////////////////////////////
#define LF	0
#define EVT	0
#define ET	1
#define DVT	1
#define EPP	2
#define PVT	2
#define PCB_VERSION		PVT

#define MCU_CRYSTAL		8000000ul	//8MHz
////////////////////////
//About Event Queue
////////////////////////
#define EVENT_QUEUE_MAX_NUMBER 	3	//Because the ADC event is always occur every 20ms.	
#define UART_QUEUE_MAX_NUMBER	30	//Because we add the MCU F/W version function.We need 10 bytes more.	

#define QUEUE_TYPE				0xE0	// ttt xxxxx
#define QUEUE_TYPE_NONE		0xFF
#define QUEUE_TYPE_EVENT		0x80	// 1xxx xxxx, xxx xxxx is Event.
#define QUEUE_TYPE_reserve		0x60	// 011x xxxx, x xxxx is reserve.
#define QUEUE_TYPE_EEPROM		0x40	// 010x xxxx, x xxxx is EEPROM address.
#define QUEUE_TYPE_PCI_EEPROM	0x20	// 001x xxxx, x xxxx is PCI EEPROM address.
#define QUEUE_TYPE_I2C			0xC0	// 110x xxxx, x xxxx is I2C para.


////////////////////////
//About mode Macro
////////////////////////
#define fgIsInDemoMode()				(bSpecialFunctionMode==MODE_DEMO)
#define fgIsInFunctionCheckerTestMode()	(bSpecialFunctionMode==MODE_FUNCTION_CHECKER_TEST)
#define fgIsInMonitorMode()				(bSpecialFunctionMode==MODE_MONITOR)
#define fgIsInProductionLineMode()		(bSpecialFunctionMode==MODE_PRODUCTION_LINE)
#define fgIsInServiceMonitorMode()		(bSpecialFunctionMode==MODE_SERVICE_MONITOR)
//#define fgIsInSpeedUpMode()				(bSpecialFunctionMode==MODE_SPEED_UP)
#define fgIsInSpeedUpMode()			(fgSpeedUp==TRUE)	//130407ra01
#define fgIsInNormalMode()				(bSpecialFunctionMode==MODE_NORMAL)
#define fgIsInWatchMode()				(bWatchMode!=WATCH_MANUAL)
#define fgIsNotWatchMode()				(bWatchMode==WATCH_MANUAL)
#define fgIsInIonMode()					(bIonMode!=ION_MANUAL)
#define fgIsNotIonMode()					(bIonMode==ION_MANUAL)
#define fgIsInPowerOnMode()				(bPowerMode==POWER_MODE_ON)
#define fgIsInPowerOffMode()				(bPowerMode==POWER_MODE_OFF)
#define fgIsChildLockFunction()			(fgChildLockEnable==TRUE)
#define fgIsAutoRestartFunction()			(fgAutoRestartFunction==TRUE)
#define fgIsLightOffFunction()				(fgLightOffFunction==TRUE)
#define fgIsNotLightOffFunction()			(fgLightOffFunction==FALSE)
#define fgIsInTimerOnOffFunction()		(bTimerMode!=TIMER_MODE_OFF)
#define fgIsNotTimerOnOffFunction()		(bTimerMode==TIMER_MODE_OFF)


////////////////////////
//About I2C slave address
////////////////////////
#define SLAVE_ADDRESS_MAIN_MCU    		0xa0
#define SLAVE_ADDRESS_TOUCH_IC		0x58


//////////////////////////////////////////////
//about key state
//////////////////////////////////////////////
enum KEY_STATES
{
	KEY_NORMAL,
	KEY_DEMO_MODE,
	KEY_FUNCTION_CHECKER_MODE,
	KEY_MONITOR_MODE,
	KEY_PRODUCTION_LINE_MODE,
	KEY_SERVICE_MONITOR_MODE,
	KEY_SPEED_UP_MODE,

	KEY_WATCH_OR_ION_MODE,
	
//	KEY_WATCH_MODE_WITH_BUZZER,
//	KEY_WATCH_MODE_WITHOUT_BUZZER,
//	KEY_ION_PLASMACLUSTER_SHOWER_MODE,
//	KEY_ION_CLOTHING_DEODORANT_MODE,

	KEY_MAX
};

//////////////////////////////////////////////
//Error mode
//warning for Cleaning PCI UNIT Electrode
//Cover Open Error
//PCI Unit Connection Error
//Fan Motor Rotation Error
//Temperature and Humidity Sensor Error
//Microcomputer Communication Error
//PCI Unit Data Error
//////////////////////////////////////////////
//130309vi01***
#define ERROR_NONE						0
#define WARNIN_GCLEANING_PCI_UNIT	0xC3	// U3
#define ERROR_FAN_MOTOR_ROTATION		0xC1
#define ERROR_TEM_HUM_SENSOR			0xC4
#define ERROR_COMMUNICATION_WITH_TOUCH	0xC6
#define ERROR_PCI_UNIT_DATA			0xC8
#define ERROR_COVER_OPEN				0xE7
#define ERROR_PCI_UNIT_CONNECTION		0xE9	
#define ERROR_MAX
//130309vi01&&&

//////////////////////////////////////////////
//about Air Volume
//////////////////////////////////////////////
#define AIR_VOLUME_MAX			33
#define AIR_VOLUME_WATCH_MAX	32
#define AIR_VOLUME_ION_MAX	32
#define AIR_VOLUME_MIN			1
#define AIR_VOLUME_OVERFLOW		0xF8	//130422Ja01

#define AIR_NORMAL_CONTROL_GAP 	4		
#define AIR_FINE_CONTROL_GAP 	 	1		//Air volume adjust gap in fine adjust or normal adjust
#define AIR_VOLUME_DEFAULT_VALUE 4	//130307le01

#define FAN_VOLUME_NONE	0xFF	//130424Ke03

//130418Ja01&&&
//////////////////////////////////////////////
// define watch mode auto fan status
//////////////////////////////////////////////
#define AUTO_FAN_MINUS		0
#define AUTO_FAN_NORMAL	4
#define AUTO_FAN_PLUS		8
//130418Ja01&&&

//////////////////////////////////////////////
//about Temperature and Humidity
//////////////////////////////////////////////
  //130309ma01***
#define PRODUCTION_LINE_MODE_HUM_MAX		 	0xcb	//楞程
#define PRODUCTION_LINE_MODE_HUM_MIN		 	0x05	//楞程
#define PRODUCTION_LINE_MODE_TEM_MAX		 	0xf4	//放程
#define PRODUCTION_LINE_MODE_TEM_MIN		 	0x1c	//放程
#define PRODUCTION_LINE_MODE_ION_ERROR_COUNT		 	1	//瞒簗代刚岿粇Ω计
  //130309ma01&&&


//////////////////////////////////////////////
//about key define must as the same with MPEG
//////////////////////////////////////////////
enum IR_KEYS
{
	//Remote Key
	IR_POWER,	// 0x00
	IR_TIMER,
	IR_WATCH_MODE,
	IR_ION_MODE,
	IR_AIR_VOLUME_CONTROL_LO,
	IR_AIR_VOLUME_CONTROL_HI,	// 05
	IR_FINE_CONTROL_LO,
	IR_FINE_CONTROL_HI,
	IR_OSCILLATING_ANGLE,
	IR_LOUVER_ANGLE,
	IR_HORIZONTAL_OSCILLATING,	// 10
	IR_VERTICAL_DIRECTION,

	//Touch Key
	IR_TOUCH_TIMER=20,			// 20
	IR_TOUCH_RESET,
	IR_TOUCH_POWER,
	IR_TOUCH_AIR_VOLUME,	//130310ha01
	IR_TOUCH_HORIZONTAL_OSCILLATING,
	IR_TOUCH_VERTICAL_DIRECTION,	// 25
 	IR_TOUCH_WATCH_MODE,
	
	IR_TOUCH_NONE,	//It's mean no touch TouchKey.	//20
	
	//Touch assemble key. It's used at hot key.
	IR_TOUCH_HORIZONTAL_RESET,
	IR_TOUCH_VERTICAL_RESET,	
	IR_TOUCH_VERTICAL_HORIZONTAL,	// 30
	
	//Special or Hot Key
	IR_PRODUCTION_LINE_MODE,
	IR_FUNCTION_CHECKER_TEST_MODE,
	IR_SPEED_UP_MODE,
	IR_SERVICE_MONITOR_MODE,
	IR_MONITOR_MODE,				// 35
	IR_DEMO_MODE,

	IR_CHILD_LOCK,
	IR_LIGHT_OFF_FUNCTION,
	IR_AUTO_RESTART_FUNCTION,
	IR_FILTER_CLEANING,			// 40
	
	//This key is used in special mode.
	IR_NEXT_STEP,
	IR_POWER_OFF,
	IR_AIR_VOLUME_CONTROL,	//For auto fan control.	//130418ha01
	
	IR_NONE,//=0xFF,
	IR_MAX

};

////////////////////////
//About Secial Function mode
////////////////////////
enum SPECIAL_MODES
{
	MODE_NORMAL,
	MODE_PRODUCTION_LINE,
	MODE_FUNCTION_CHECKER_TEST,
	MODE_SPEED_UP,
	MODE_SERVICE_MONITOR,
	MODE_MONITOR,
	MODE_DEMO,
	MODE_MAX
};

////////////////////////
//About ION mode
////////////////////////
enum ION_MODES
{
	ION_MANUAL,
	ION_PLASMA_CLUSTER_SHOWER,
	ION_CLOTHING_DEODORANT,
	ION_MAX
};

////////////////////////
//About Watch mode
////////////////////////
enum WATCH_MODES
{
	WATCH_MANUAL,
	WATCH_MODE_WITH_BUZZER,
	WATCH_MODE_WITHOUT_BUZZER,
	WATCH_MAX
};

////////////////////////
//About Watch Zone
////////////////////////
enum WATCH_ZONES
{	
	ZONE_VIRUS,
	ZONE_NORMAL,
	ZONE_CAUTION,
	ZONE_PRECAUTION,
	ZONE_DANGER,
	ZONE_MAX
};

////////////////////////
//About Oscillating Angle
////////////////////////
enum OSCILLATING_MODES
{
	OSCILLATE_ON,
	OSCILLATE_OFF,
	OSCILLATE_CENTRAL,
	OSCILLATE_15D,
	OSCILLATE_30D,
	OSCILLATE_60D,
	OSCILLATE_90D,
	OSCILLATE_120D,
	OSCILLATE_OFF_MEMORIZED,		//Let the step motor go to the lastest position.
	OSCILLATE_CENTER,	//130323ha01

	OSCILLATE_ALL_PIN_DISABLE,		//Let the step motor all pin off.
	OSCILLATE_CHECK	//130412Ke04
};
#define OSCILLATE_NONE	0xFF

#define OSCILLATE_MOTOR_CENTRAL_TIMEOUT_TIME	35		// 35*1s=35s	//130322ha03	//130417Ke01

////////////////////////
//About Vertical Louver Angle
////////////////////////
enum LOUVER_MODES
{
	LOUVER_HORIZONTAL_1,
	LOUVER_UPPER40D,
	LOUVER_HORIZONTAL_3,
	LOUVER_LOWER20D,
	LOUVER_OFF_MEMORIZED,		//Let the step motor go to the lastest position.
	
	LOUVER_STOP,
	LOUVER_SWING,
	
	LOUVER_INITIAL_POSITION,
	LOUVER_CLOSED_POSITION,
	LOUVER_ALL_PIN_DISABLE,
	LOUVER_CENTRAL     //130312ro02

};
#define LOUVER_NONE	0xFF

////////////////////////
//About Buzzer Output
////////////////////////
enum BUZZER_MODES
{
	PI,
	PI_LOUD,
	PI_LONG,
	PI_PI,
	PI_PI_PI,
	PI_LOUD_HC,
	PI_LOUD_HD,
	PI_LOUD_L,
	PI_OFF,
	PI_MAX
};
#define PI_NONE	0xFF

/////////////////////////////////////////////////////
// About ON/OFF Timer
/////////////////////////////////////////////////////
//the variable&macro used in Timer key
typedef enum TIMER_MODE
{
	TIMER_MODE_OFF,
	TIMER_MODE_1H,
	TIMER_MODE_2H,
	TIMER_MODE_4H,
	TIMER_MODE_6H,
	TIMER_MODE_MAX
};

/////////////////////////////////////////////////////
// About PCI 
/////////////////////////////////////////////////////
enum PCI_ERROR
{	
	PCI_ERROR_TIME_17500H=1,
	PCI_ERROR_TIME_19000H,
	PCI_ERROR_CONNECTION,
	PCI_ERROR_DATA
};
#define PCI_ERROR_NONE	0xFF


////////////////////////
//About All event
////////////////////////
enum EVENTS
{
//Event about Touch MCU
	EVENT_IR,
	EVENT_POWER_ON,
	EVENT_POWER_OFF,
	EVENT_OTP_INT_INTERRUPT,
	EVENT_MAIN_MCU_BUSY,
	EVENT_MAIN_MCU_NOT_BUSY,
	EVENT_ADC,
	EVENT_TOUCH_READ,	//130126sh01
	EVENT_TOUCH_INTERRUPT,
	EVENT_TOUCH_READ_REGISTER_ADDRESS,//130408sh01
	EVENT_COMMUNICATE_WITH_TOUCH_ERROR,//130309sh02

//Event about Main MCU
	EVENT_PCI_NONE_IS_NORMAL,
	EVENT_PCI_NONE_IS_ERROR,
	EVENT_COVER_SWITCH_IS_OPEN,
	EVENT_COVER_SWITCH_IS_NORMAL,

//Event about TOUCH MCU to MAIN MCU.//130306sh01***
//Command about SUB to MAIN.
	COMMAND_SUB_MAIN_FAN_VOLUME,
	COMMAND_SUB_MAIN_FAN_VOLUME_EE,			//130427Ja01
	COMMAND_SUB_MAIN_OSCILLATE_MODE,		//130315Li01
	COMMAND_SUB_MAIN_LOUVER_MODE,			//130315Li01
	COMMAND_SUB_MAIN_BUZZER_MODE,
	COMMAND_SUB_MAIN_WATCH_MODE_STATUS,
	COMMAND_SUB_MAIN_ION_MODE_STATUS,
	COMMAND_SUB_MAIN_POWER_STATUS,
	COMMAND_SUB_MAIN_SPECIAL_MODE,
	COMMAND_SUB_MAIN_PIN_RESET_ENABLE,
	COMMAND_SUB_MAIN_PIN_CAPSEL_40P_ENABLE,
	COMMAND_SUB_MAIN_PIN_PCI_POWER_ENABLE,
	COMMAND_SUB_MAIN_MONITOR_MODE_STATUS,	//130313Li01
	COMMAND_SUB_MAIN_FUNCTION_CHECKER_MODE_STATUS,		//130313Li01
	
	COMMAND_SUB_MAIN_REQUEST_HUM_ADC_VALUE,
	COMMAND_SUB_MAIN_REQUEST_TEMP_ADC_VALUE,
	COMMAND_SUB_MAIN_REQUEST_TEMP_REAL_VALUE,
	COMMAND_SUB_MAIN_REQUEST_HUM_REAL_VALUE,
	COMMAND_SUB_MAIN_REQUEST_FAN_PWM_VALUE,
	COMMAND_SUB_MAIN_REQUEST_FAN_ROTA_SET_VALUE,
	COMMAND_SUB_MAIN_REQUEST_FAN_ROTA_DETECT_VALUE,
	COMMAND_SUB_MAIN_REQUEST_ION_VOLTAGE_VALUE,
	//COMMAND_SUB_MAIN_REQUEST_ION_DELTA_VOFF,//130309sh04
	COMMAND_SUB_MAIN_REQUEST_ION_DELTA_V,
	COMMAND_SUB_MAIN_REQUEST_ION_LEAK_CURRENT_OK_COUNT,//130309sh04
	COMMAND_SUB_MAIN_REQUEST_ION_GENERATION_OK_COUNT,//130309sh04
	COMMAND_SUB_MAIN_REQUEST_ION_ERROR_COUNT_VALUE,
	COMMAND_SUB_MAIN_REQUEST_PCI_UNIT_USE_ACC_TIME_VALUE,
	COMMAND_SUB_MAIN_REQUEST_PCI_UNIT_USE_ACC_HOUR_VALUE,  // 130309lo01
	COMMAND_SUB_MAIN_REQUEST_INT_VALUE,
	COMMAND_SUB_MAIN_REQUEST_FAN_MOTOR_ROTATION_VALUE,	//130314le01
	COMMAND_SUB_MAIN_ERROR_PROCESS,	//130326vi01


//Event about MAIN MCU to TOUCH MCU.
//Command about MAIN to SUB.
	COMMAND_MAIN_SUB_GIVE_HUM_ADC_VALUE,
	COMMAND_MAIN_SUB_GIVE_TEMP_ADC_VALUE,
	COMMAND_MAIN_SUB_GIVE_TEMP_REAL_VALUE,
	COMMAND_MAIN_SUB_GIVE_HUM_REAL_VALUE,
	COMMAND_MAIN_SUB_GIVE_FAN_PWM_VALUE,
	COMMAND_MAIN_SUB_GIVE_FAN_ROTA_SET_VALUE,
	COMMAND_MAIN_SUB_GIVE_FAN_ROTA_DETECT_VALUE,
	COMMAND_MAIN_SUB_GIVE_ION_VOLTAGE_VALUE,
	//COMMAND_MAIN_SUB_GIVE_ION_DELTA_VOFF,//130309sh04
	COMMAND_MAIN_SUB_GIVE_ION_DELTA_V,
	COMMAND_MAIN_SUB_GIVE_ION_LEAK_CURRENT_OK_COUNT,//130309sh04
	COMMAND_MAIN_SUB_GIVE_ION_GENERATION_OK_COUNT,//130309sh04
	COMMAND_MAIN_SUB_GIVE_ION_ERROR_COUNT_VALUE,
	COMMAND_MAIN_SUB_GIVE_PCI_UNIT_USE_ACC_TIME_VALUE,
	COMMAND_MAIN_SUB_GIVE_PCI_UNIT_USE_ACC_HOUR_VALUE,      // 130309lo01
	COMMAND_MAIN_SUB_INT_FAN_VOLUME,
	COMMAND_MAIN_SUB_INT_FUNCTION_CHECKER_MODE,	//130403le01
	COMMAND_MAIN_SUB_INT_SPEED_UP_MODE,
	COMMAND_MAIN_SUB_INT_WATCH_ZONE_STATUS_CHANGE,
	COMMAND_MAIN_SUB_INT_WARNING_BUZZER_START,	//130411le01
	COMMAND_MAIN_SUB_INT_WATCH_AUTO_FAN_STATUS_CHANGE,	//130418Ja01
	//COMMAND_MAIN_SUB_INT_PCI_CONNECTION_ERROR,//130309sh04***
	//COMMAND_MAIN_SUB_INT_PCI_DATA_ERROR,
	//COMMAND_MAIN_SUB_INT_WARNING_CLEANING_PCI_UNIT_ELECTRODE,
	//COMMAND_MAIN_SUB_INT_COVER_SWITCH_ERROR,
	//COMMAND_MAIN_SUB_INT_FAN_ROTA_ERROR,
	COMMAND_MAIN_SUB_INT_PCI_OVER_TIME,
	COMMAND_MAIN_SUB_INT_PCI_CRITICAL,
	//COMMAND_MAIN_SUB_INT_ERROR_HUM_TEMP,//130306sh01&&&
	COMMAND_MAIN_SUB_ERROR,//130309sh04&&&
	COMMAND_MAIN_SUB_INT_OSCILLATE_INITIAL_FINISH,	//130305Ke02
	COMMAND_MAIN_SUB_INT_LOUVER_INITIAL_FINISH,		//130328ro02
	COMMAND_MAIN_SUB_GIVE_FAN_MOTOR_ROTATION_VALUE,	//130314le01

	//Command about Display
	COMMAND_MAIN_SUB_LED_DISPLAY,
	COMMAND_MAIN_SUB_7_SEG_DISPLAY,
	COMMAND_MAIN_SUB_DISPLAY_ALL_ON,
	COMMAND_MAIN_SUB_DISPLAY_ALL_OFF,
/*	// 130325jac01***
	COMMAND_MAIN_SUB_LED_Blink_ON,				// 130301ja04***
	COMMAND_MAIN_SUB_LED_Blink_OFF,
	COMMAND_MAIN_SUB_7_SEG_DEC_Blink_ON,
	COMMAND_MAIN_SUB_7_SEG_HEX_Blink_ON,
	COMMAND_MAIN_SUB_7_SEG_MESSAGE_Blink_ON,
	COMMAND_MAIN_SUB_7_SEG_DEC_Blink_OFF,
	COMMAND_MAIN_SUB_7_SEG_HEX_Blink_OFF,
	COMMAND_MAIN_SUB_7_SEG_MESSAGE_Blink_OFF,
	COMMAND_MAIN_SUB_LED_AUTO_DISAPPEAR,	
	COMMAND_MAIN_SUB_7_SEG_DEC_AUTO_DISAPPEAR,
	COMMAND_MAIN_SUB_7_SEG_HEX_AUTO_DISAPPEAR,
	COMMAND_MAIN_SUB_7_SEG_MESSAGE_AUTO_DISAPPEAR,		// 130301ja04&&&
*/
	COMMAND_MAIN_SUB_7SEG_LED_0_1_ROW,
	COMMAND_MAIN_SUB_7SEG_LED_2_ROW,
	COMMAND_MAIN_SUB_7SEG_LED_3_4_ROW,	// 130325jac01&&&
	COMMAND_MAIN_SUB_LOUVER_MOTOR_ON,	//130424Me01
	EVENT_MAX
};


////////////////////////
//About Power Mode
////////////////////////
enum POWER_MODES
{
	POWER_MODE_OFF,
	POWER_MODE_ON,
	POWER_MODE_OFF_PROGRESS,
	POWER_MODE_ON_PROGRESS,
	POWER_MODE_SLEEP
};

////////////////////////
//About 7 segment and LED
////////////////////////
#define DISPLAY_TIME_UNIT			100		// unit: 100ms
#define DISPLAY_TIME_10_SECOND	(10000/DISPLAY_TIME_UNIT)	// 10000ms/x=count times
#define DISPLAY_TIME_9_SECOND		(9000/DISPLAY_TIME_UNIT)		// 9000ms/x=count times
#define DISPLAY_TIME_8_SECOND		(8000/DISPLAY_TIME_UNIT)		// 8000ms/x=count times
#define DISPLAY_TIME_7_SECOND		(7000/DISPLAY_TIME_UNIT)		// 7000ms/x=count times
#define DISPLAY_TIME_6_SECOND		(6000/DISPLAY_TIME_UNIT)		// 6000ms/x=count times
#define DISPLAY_TIME_5_SECOND		(5000/DISPLAY_TIME_UNIT)		// 5000ms/x=count times
#define DISPLAY_TIME_4_SECOND		(4000/DISPLAY_TIME_UNIT)		// 4000ms/x=count times
#define DISPLAY_TIME_3_SECOND		(3000/DISPLAY_TIME_UNIT)		// 3000ms/x=count times
#define DISPLAY_TIME_2_SECOND		(2000/DISPLAY_TIME_UNIT)		// 2000ms/x=count times
#define DISPLAY_TIME_1_2_SECOND	(1200/DISPLAY_TIME_UNIT)		// 900ms/x=count times
#define DISPLAY_TIME_1_SECOND		(1000/DISPLAY_TIME_UNIT)		// 1000ms/x=count times
#define DISPLAY_TIME_0_9_SECOND	(900/DISPLAY_TIME_UNIT)		// 900ms/x=count times
#define DISPLAY_TIME_0_8_SECOND	(800/DISPLAY_TIME_UNIT)		// 800ms/x=count times
#define DISPLAY_TIME_0_7_SECOND	(700/DISPLAY_TIME_UNIT)		// 700ms/x=count times
#define DISPLAY_TIME_0_6_SECOND	(600/DISPLAY_TIME_UNIT)		// 600ms/x=count times
#define DISPLAY_TIME_0_5_SECOND	(500/DISPLAY_TIME_UNIT)		// 500ms/x=count times
#define DISPLAY_TIME_0_4_SECOND	(400/DISPLAY_TIME_UNIT)		// 400ms/x=count times
#define DISPLAY_TIME_0_3_SECOND	(300/DISPLAY_TIME_UNIT)		// 300ms/x=count times 0.3s
#define DISPLAY_TIME_0_2_SECOND	(200/DISPLAY_TIME_UNIT)		// 200ms/x=count times 0.2s
#define DISPLAY_TIME_0_1_SECOND	(100/DISPLAY_TIME_UNIT)		// 100ms/x=count times 0.1s
#define DISPLAY_TIME_NONE				0	//130424Ke03

enum		// for 7Seg Command
{
	CMD_7SEG_NUM_DEC_SHOW
	,CMD_7SEG_NUM_HEX_SHOW
	,CMD_7SEG_MESSAGE_SHOW
	//,CMD_7SEG_CLEAR		// 130308ja03
};

enum		// for 7Seg Message CMD_7SEG_MESSAGE_SHOW
{
	MESSAGE_7SEG_HI
	,MESSAGE_7SEG_NO
	,MESSAGE_7SEG_P
	,MESSAGE_7SEG_LOW			// _ _
	,MESSAGE_7SEG_HORIZONTAL		// - -
	,MESSAGE_7SEG_UPPER			// 
	,MESSAGE_7SEG_LEFT	// Left			// 130306ja02&&&
	,MESSAGE_7SEG_LEFT_MIDDLE	// Left middle
	,MESSAGE_7SEG_RIGHT_MIDDLE	// Right middle
	,MESSAGE_7SEG_RIGHT	// Right
	,MESSAGE_7SEG_LO
	,MESSAGE_7SEG_U3
	,MESSAGE_7SEG_88
	,MESSAGE_7SEG_CLEAR			// 130306ja02***
};

enum		// for Led Message
{
	LED_FILTER_CLEAN						//LED36		// 130306ja02
	,LED_CHILD_LOCK_SIGN//=0X07				//LED53		// 130306ja02	// 130308ja01
	,LED_TIMER_ON//=0X10					//LED54		// 130306ja02		// 130308ja01
	,LED_TIMER_1H							//LED55
	,LED_TIMER_2H							//LED56
	,LED_TIMER_OFF							//LED57
	,LED_WATCH_RED							//LED58
	,LED_TIMER_4H							//LED59
	,LED_TIMER_6H							//LED67
	,LED_CLOTHING_DEODORANT				//LED68
	,LED_CHILD_LOCK_INDICATION//=0X21		//LED62		// 130306ja02	// 130308ja01
	,LED_PLASMACLUSTER_SHOWER			//LED64		// 130306ja02
	,LED_AIR_VOLUME_SETTING_INDICATION	//LED69
	,LED_WATCH_GREEN						//LED58
	,LED_TIMER_H							//LED71
	,LED_WARNING_BUZZER					//LED72
	,LED_ANGLE_SETTING_INDICATION			//LED70
	,LED_TUBE_WHITE						//LED7			// 130306ja02
};

/*
static unsigned char special_key_press	 @0x87: bank 1;
static bit key_vertival_press			 @0x87@0: bank 1;
static bit key_horizontal_press		 @0x87@1: bank 1;
// 0x5e ~ 0x65 for i2c buffer
static unsigned char ram_arr[6] @0x5e;
static unsigned char seg_ram_arr[5] @0x65;
*/
/////////////////////////////////////////////
//Data RAM Bank 0 50h~7Fh
/////////////////////////////////////////////
//Bank0 0x50~0x61 cannot be used.
//static unsigned char BYTE_AT_0X62 @0x62;
#define _AT_0X62	@0x62
#define _AT_0X63	@0x63
#define _AT_0X64	@0x64
#define _AT_0X65	@0x65
#define _AT_0X66	@0x66
#define _AT_0X67	@0x67
#define _AT_0X68	@0x68
#define _AT_0X69	@0x69
#define _AT_0X6A	@0x6A
#define _AT_0X6B	@0x6B
#define _AT_0X6C	@0x6C
#define _AT_0X6D	@0x6D
#define _AT_0X6E	@0x6E
#define _AT_0X6F	@0x6F

#define _AT_0X70	@0x70
#define _AT_0X71	@0x71
#define _AT_0X72	@0x72
#define _AT_0X73	@0x73
#define _AT_0X74	@0x74
#define _AT_0X75	@0x75
#define _AT_0X76	@0x76
#define _AT_0X77	@0x77
#define _AT_0X78	@0x78
#define _AT_0X79	@0x79
#define _AT_0X7A	@0x7A
#define _AT_0X7B	@0x7B
#define _AT_0X7C	@0x7C
#define _AT_0X7D	@0x7D
#define _AT_0X7E	@0x7E
#define _AT_0X7F	@0x7F




#define CPU_SOURCE_FS			(CPUS=0)
#define CPU_SOURCE_FM			(CPUS=1)

////////////////////////
//About Interrupt
////////////////////////
#define INT_DIS()	_asm{disi}	//窽ゎい耞
#define INT_EN()		_asm{eni} 	//す砛い耞
#define NOP()		_asm{nop}	//巨
#define SLEEP()		_asm{slep}	//sleep
#define vMovePCtoACC()	 _asm{MOV A,0x2}	
#define RETI()		_asm{reti}	//return from Interrupt
#define LJMP(proc)	{ _asm{ LJMP proc };}
#define JMP(proc)		{ _asm{ JMP proc };}
#define Function(proc)	{_asm{JMP  proc };}
#define Call(addr)				{_asm{ mov  a, %addr}; _asm{ add  %PC, a };}


#define CPU_OSCILLATOR_SOURCE_FS	(CPUS=0)
#define CPU_OSCILLATOR_SOURCE_FM	(CPUS=1)

//Idle Mode Enable Bit. This bit will determine as to which mode to proceed
//to after execution of the SLEP instruction.
// 0: ¨IDLE=0〃+ SLEP instruction △ sleep mode
// 1: ¨IDLE=1〃+ SLEP instruction △ idle mode
#define IDLE_MODE_SLEEP			(IDLE=0)
#define IDLE_MODE_IDLE				(IDLE=1)

//External Interrupt (P60)
#define EXTERNAL_INT_FALL_EDGE	(EIES =0)
#define EXTERNAL_INT_RISE_EDGE		(EIES =1)
#define EXTERNAL_INT_FLAG			(EXIF)

//Watch Dog Timer
#define WDT_CLEAR()	_asm{WDTC}	//wdtc
#define WDT_EN()			(WDTE=1)
#define WDT_DIS()			(WDTE=0)
// Prescaler Enable Bit for WDT
// 0: Prescaler disable, WDT rate is 1:1
#define WDT_PRESCALER_DISABLE		(PSWE=0)
// 1: Prescaler enable, WDT rate is set from Bits 2 ~ 0.
#define WDT_PRESCALER_ENABLE		(PSWE=1)
#define WDT_PRESCALE_1_2	{PSW2=0;PSW1=0;PSW0=0;}
#define WDT_PRESCALE_1_4	{PSW2=0;PSW1=0;PSW0=1;}
#define WDT_PRESCALE_1_8	{PSW2=0;PSW1=1;PSW0=0;}
#define WDT_PRESCALE_1_16	{PSW2=0;PSW1=1;PSW0=1;}
#define WDT_PRESCALE_1_32	{PSW2=1;PSW1=0;PSW0=0;}
#define WDT_PRESCALE_1_64	{PSW2=1;PSW1=0;PSW0=1;}
#define WDT_PRESCALE_1_128	{PSW2=1;PSW1=1;PSW0=0;}
#define WDT_PRESCALE_1_256	{PSW2=1;PSW1=1;PSW0=1;}


//interrupt enable flag.
// 0: interrupt masked by DISI or hardware interrupt
// 1: interrupt enabled by ENI/DISI instructions
#define INTERRUPT_DISI_HARDWARE_DISABLE	(EINT=0)
#define INTERRUPT_DISI_ENI_ENABLE			(EINT=1)

//8-bit real time clock/counter (TCC)
//Real Time Clock/Counter
#define TCC_INT_EN		(TCIE=1)
#define TCC_INT_DIS		(TCIE=0)
#define TCC_OVERFLOW_FLAG	TCIF 
#define TCC_DATA_REGISTER		TCC
#define TCC_CLOCK_SOURCE_FS	(TCCS=0)
#define TCC_CLOCK_SOURCE_FM	(TCCS=1)
//TCC Signal Source
// 0: Internal oscillator cycle clock. If P77 is used as I/O pin, TS must be 0.
#define TCC_SIGNAL_SOURCE_INTERNAL	(TS=0)
// 1: Transition on the TCC pin
#define TCC_SIGNAL_SOURCE_TCC_PIN		(TS=1)
//TCC Signal Edge
// 0: Increment if the transition from low to high takes place on the TCC pin.
#define TCC_SIGNAL_EDGE_RISE	(TE=0)
// 1: Increment if the transition from high to low takes place on the TCC pin.
#define TCC_SIGNAL_EDGE_FALL	(TE=1)
//Prescaler Enable Bit for TCC
// 0: prescaler disable, TCC rate is 1:1
#define TCC_PRESCALER_DIS		(PSTE=0)
// 1: prescaler enable, TCC rate is set from Bits 2~0.
#define TCC_PRESCALER_EN		(PSTE=1)
#define TCC_PRESCALER_1_2		{PST2=0;PST1=0;PST0=0;}
#define TCC_PRESCALER_1_4		{PST2=0;PST1=0;PST0=1;}
#define TCC_PRESCALER_1_8		{PST2=0;PST1=1;PST0=0;}
#define TCC_PRESCALER_1_16		{PST2=0;PST1=1;PST0=1;}
#define TCC_PRESCALER_1_32		{PST2=1;PST1=0;PST0=0;}
#define TCC_PRESCALER_1_64		{PST2=1;PST1=0;PST0=1;}
#define TCC_PRESCALER_1_128	{PST2=1;PST1=1;PST0=0;}
#define TCC_PRESCALER_1_256	{PST2=1;PST1=1;PST0=1;}

//Analog to Digital Conversion	Vref(P50)
#define ADC_INT_EN				(ADIE=1)
#define ADC_INT_DIS				(ADIE=0)
#define ADC_INPUT_SOURCE_VREF	(VREFS=1)
#define ADC_INPUT_SOURCE_VDD	(VREFS=0)
#define ADC_START				(ADRUN=1)
#define ADC_POWER_DOWN_EN	(ADPD=0)
#define ADC_POWER_DOWN_DIS	(ADPD=1)
#define ADC_OPERATING			(ADPD=1)
#define ADC_INPUT_P60	{ADIS2=0;ADIS1=0;ADIS0=0;}
#define ADC_INPUT_P61	{ADIS2=0;ADIS1=0;ADIS0=1;}
#define ADC_INPUT_P62	{ADIS2=0;ADIS1=1;ADIS0=0;}
#define ADC_INPUT_P63	{ADIS2=0;ADIS1=1;ADIS0=1;}
#define ADC_INPUT_P64	{ADIS2=1;ADIS1=0;ADIS0=0;}
#define ADC_INPUT_P65	{ADIS2=1;ADIS1=0;ADIS0=1;}
#define ADC_INPUT_P66	{ADIS2=1;ADIS1=1;ADIS0=0;}
#define ADC_INPUT_P67	{ADIS2=1;ADIS1=1;ADIS0=1;}
#define vSetADCChannel(channel)	{ADCR1&=0xF8;ADCR1|=channel;}
#define ADC_CALIBRATION_EN		(CALI=1)
#define ADC_CALIBRATION_DIS	(CALI=0)
#define ADC_CALIBRATION_ADD	(SIGN=1)
#define ADC_CALIBRATION_MINUS	(SIGN=0)
#define ADC_CALIBRATION_0LSB	{VOF2=0;VOF1=0;VOF0=0;}
#define ADC_CALIBRATION_2LSB	{VOF2=0;VOF1=0;VOF0=1;}
#define ADC_CALIBRATION_4LSB	{VOF2=0;VOF1=1;VOF0=0;}
#define ADC_CALIBRATION_6LSB	{VOF2=0;VOF1=1;VOF0=1;}
#define ADC_CALIBRATION_8LSB	{VOF2=1;VOF1=0;VOF0=0;}
#define ADC_CALIBRATION_10LSB	{VOF2=1;VOF1=0;VOF0=1;}
#define ADC_CALIBRATION_12LSB	{VOF2=1;VOF1=1;VOF0=0;}
#define ADC_CALIBRATION_14LSB	{VOF2=1;VOF1=1;VOF0=1;}
#define ADC_DATA_READ			(ADDH*16+ADDL)
#define ADC_WAKE_UP_EN		(ADWE=1)
#define ADC_WAKE_UP_DIS		(ADWE=0)
#define ADC_OSCILLATE_CLOKE_RATE_4		{CKR2=0;CKR1=0;CKR0=0;}
#define ADC_OSCILLATE_CLOKE_RATE_1		{CKR2=0;CKR1=0;CKR0=1;}
#define ADC_OSCILLATE_CLOKE_RATE_2		{CKR2=0;CKR1=1;CKR0=0;}
#define ADC_OSCILLATE_CLOKE_RATE_8		{CKR2=0;CKR1=1;CKR0=1;}
#define ADC_OSCILLATE_CLOKE_RATE_16		{CKR2=1;CKR1=0;CKR0=0;}
#define ADC_OSCILLATE_CLOKE_RATE_32		{CKR2=1;CKR1=0;CKR0=1;}
#define ADC_OSCILLATE_CLOKE_RATE_64		{CKR2=1;CKR1=1;CKR0=0;}
#define ADC_OSCILLATE_CLOKE_INTERNAL	{CKR2=1;CKR1=1;CKR0=1;}

//Low Voltage Detect
#define LVD_INT_EN			(LVDIE=1)
#define LVD_INT_DIS			(LVDIE=0)
#define LVD_WAKE_UP_EN		(LVDWE=1)
#define LVD_WAKE_UP_DIS	(LVDWE=0)

//SPI
#define SPI_INT_EN		(SPIE=1)
#define SPI_INT_DIS		(SPIE=0)

//PWM A
#define PWMA_INT_EN	(PWMAIE=1)
#define PWMA_INT_DIS	(PWMAIE=0)
#define PWMA_ENABLE	(PWMAE=1)	//PWM A is on, and its related pin is automatically set to output
#define PWMA_DISABLE	(PWMAE=0)	//PWM A is off (default value), and its related pin carries out the I/O pin function
#define PWMA_TIMER_ENABLE		(TAEN=1)
#define PWMA_TIMER_DISABLE	(TAEN=0)

//(TRCBA): Timer A Read Control Bit
// 0: When this bit is set to 0, the values of PRDA[9]~PRDA[0] in PRDAL and
//PRDxH are PWMA period data.
// 1: When this bit set to 1, Read values from PRDA[9]~PRDA[0] in PRDAL and
//PRDxH are PWMA timer data.
#define PWMA_PRDA_ARE_PERIOD_DATA	(TRCBA=0)
#define PWMA_PRDA_ARE_TIMER_DATA	(TRCBA=1)

#define TIMERA_CLOCK_SOURCE_FS	(TASS=0)
#define TIMERA_CLOCK_SOURCE_FM	(TASS=1)
#define PWMA_CLOCK_SOURCE_FS		(TASS=0)
#define PWMA_CLOCK_SOURCE_FM		(TASS=1)
#define PWMA_PRESCALER_1_2		{TAP2=0;TAP1=0;TAP0=0;}
#define PWMA_PRESCALER_1_4		{TAP2=0;TAP1=0;TAP0=1;}
#define PWMA_PRESCALER_1_8		{TAP2=0;TAP1=1;TAP0=0;}
#define PWMA_PRESCALER_1_16		{TAP2=0;TAP1=1;TAP0=1;}
#define PWMA_PRESCALER_1_32		{TAP2=1;TAP1=0;TAP0=0;}
#define PWMA_PRESCALER_1_64		{TAP2=1;TAP1=0;TAP0=1;}
#define PWMA_PRESCALER_1_128		{TAP2=1;TAP1=1;TAP0=0;}
#define PWMA_PRESCALER_1_256		{TAP2=1;TAP1=1;TAP0=1;}
#define vSetPWMAHighDuty(value)		{TADTH=(BYTE)(value>>2);DTxL&=0xFC;DTxL|=((BYTE)(value&0x03));}
#define vSetPWMAPeriod(value)		{TAPRDH=value>>2;PRDxL&=0xFC;PRDxL|=((BYTE)(value&0x03));}



//PWM B
#define PWMB_INT_EN	(PWMBIE=1)
#define PWMB_INT_DIS	(PWMBIE=0)
#define PWMB_ENABLE	(PWMBE=1)	//PWM B is on, and its related pin is automatically set to output.
#define PWMB_DISABLE	(PWMBE=0)	//PWM B is off (default value), and its related pin P52 carries out the I/O pin function.
#define PWMB_TIMER_ENABLE		(TBEN=1)
#define PWMB_TIMER_DISABLE	(TBEN=0)

//(TRCBB): Timer B Read Control Bit
//0: When this bit is set to 0, the values of PRDB[9]~PRDB[0] in PRDBL and
//PRDxH are PWMB period data
// 1: When this bit set to 1, the values of PRDB[9]~PRDB[0] in PRDBL and PRDxH
//are PWMB timer data
#define PWMB_PRDB_ARE_PERIOD_DATA	(TRCBB=0)
#define PWMB_PRDB_ARE_TIMER_DATA		(TRCBB=1)

#define TIMERB_CLOCK_SOURCE_FS	(TBSS=0)
#define TIMERB_CLOCK_SOURCE_FM	(TBSS=1)
#define PWMB_CLOCK_SOURCE_FS		(TBSS=0)
#define PWMB_CLOCK_SOURCE_FM		(TBSS=1)
#define PWMB_PRESCALER_1_2		{TBP2=0;TBP1=0;TBP0=0;}
#define PWMB_PRESCALER_1_4		{TBP2=0;TBP1=0;TBP0=1;}
#define PWMB_PRESCALER_1_8		{TBP2=0;TBP1=1;TBP0=0;}
#define PWMB_PRESCALER_1_16		{TBP2=0;TBP1=1;TBP0=1;}
#define PWMB_PRESCALER_1_32		{TBP2=1;TBP1=0;TBP0=0;}
#define PWMB_PRESCALER_1_64		{TBP2=1;TBP1=0;TBP0=1;}
#define PWMB_PRESCALER_1_128		{TBP2=1;TBP1=1;TBP0=0;}
#define PWMB_PRESCALER_1_256		{TBP2=1;TBP1=1;TBP0=1;}
#define vSetPWMBHighDuty(value)		{TBDTH=(BYTE)(value>>2);DTxL&=0xF3;DTxL|=(BYTE)((value&0x03)<<2);}
#define vSetPWMBPeriod(value)		{TBPRDH=value>>2;PRDxL&=0xF3;PRDxL|=(BYTE)((value&0x03)<<2);}



//Timer 3 Control
#define TC3_INT_EN		(TC3IE=1)
#define TC3_INT_DIS		(TC3IE=0)
#define TC3_FLIP_FLOP_CONTROL_CLEAR	{TC3FF1=0;TC3FF0=0;}
#define TC3_FLIP_FLOP_CONTROL_TOGGLE	{TC3FF1=0;TC3FF0=1;}
#define TC3_FLIP_FLOP_CONTROL_SET		{TC3FF1=1;TC3FF0=0;}
#define TC3_START						(TC3S=1)
#define TC3_STOP						(TC3S=0)
#define TC3_CLOCK_SOURCE_FC_DIVIDE_2048	{TC3CK2=0;TC3CK1=0;TC3CK0=0;}
#define TC3_CLOCK_SOURCE_FC_DIVIDE_128	{TC3CK2=0;TC3CK1=0;TC3CK0=1;}
#define TC3_CLOCK_SOURCE_FC_DIVIDE_32	{TC3CK2=0;TC3CK1=1;TC3CK0=0;}
#define TC3_CLOCK_SOURCE_FC_DIVIDE_8		{TC3CK2=0;TC3CK1=1;TC3CK0=1;}
#define TC3_CLOCK_SOURCE_FC_DIVIDE_4		{TC3CK2=1;TC3CK1=0;TC3CK0=0;}
#define TC3_CLOCK_SOURCE_FC_DIVIDE_2		{TC3CK2=1;TC3CK1=0;TC3CK0=1;}
#define TC3_CLOCK_SOURCE_FC				{TC3CK2=1;TC3CK1=1;TC3CK0=0;}
#define TC3_CLOCK_SOURCE_TC3				{TC3CK2=1;TC3CK1=1;TC3CK0=1;}
#define TC3_MODE_TIMER			{TC3M1=0;TC3M0=0;}
#define TC3_MODE_DIVIDER_OUT	{TC3M1=1;TC3M0=0;}
#define TC3_MODE_PWM_OUT		{TC3M1=1;TC3M0=1;}
#define TC3_DUTY_BUFFER		(TCR3D)
#define vSetTimer3Duty(value)		(TCR3D=value)
#define TC3_INT_FLAG		(TC3IF)
#define TC3_CLOCK_SOURCE_FS		(TC3SS=0)
#define TC3_CLOCK_SOURCE_FM		(TC3SS=1)

//Timer 2 Control
#define TC2_INT_EN				(TC2IE=1)
#define TC2_INT_DIS				(TC2IE=0)
#define TC2_SIGNAL_EDGE_RISE	(TC2ES=0)
#define TC2_SIGNAL_EDGE_FALL	(TC2ES=1)
#define TC2_MODE_TIMER			(TC2M=0)
#define TC2_MODE_WINDOW		(TC2M=1)
#define TC2_START				(TC2S=1)
#define TC2_STOP				(TC2S=0)
#define TC2_CLOCK_SOURCE_FC_DIVIDE_8388608	{TC2CK2=0;TC2CK1=0;TC2CK0=0;}
#define TC2_CLOCK_SOURCE_FC_DIVIDE_8192		{TC2CK2=0;TC2CK1=0;TC2CK0=1;}
#define TC2_CLOCK_SOURCE_FC_DIVIDE_256		{TC2CK2=0;TC2CK1=1;TC2CK0=0;}
#define TC2_CLOCK_SOURCE_FC_DIVIDE_8			{TC2CK2=0;TC2CK1=1;TC2CK0=1;}
#define TC2_CLOCK_SOURCE_FC					{TC2CK2=1;TC2CK1=0;TC2CK0=0;}
#define TC2_CLOCK_SOURCE_TC2					{TC2CK2=1;TC2CK1=1;TC2CK0=1;}
#define TC2_DATA_BUFFER_HIGH	(TCR2DH)
#define TC2_DATA_BUFFER_LOW	(TCR2DL)
#define vSetTimer2Duty(value)	{TCR2DH=(BYTE)(value>>8);TCR2DL=(BYTE)(value&0xff);}
#define TC2_CLOCK_SOURCE_FS	(TC2SS=0)
#define TC2_CLOCK_SOURCE_FM	(TC2SS=1)

//Timer 1 Control
#define TC1_INT_EN				(TC1IE=1)
#define TC1_INT_DIS				(TC1IE=0)
#define TC1_SOFT_CAPTURE_CONTROL_DIS	(TC1CAP=0)
#define TC1_SOFT_CAPTURE_CONTROL_EN	(TC1CAP=1)
#define TC1_START				(TC1S=1)
#define TC1_STOP				(TC1S=0)
#define TC1_CLOCK_SOURCE_FC_DIVIDE_4096	{TC1CK1=0;TC1CK0=0;}
#define TC1_CLOCK_SOURCE_FC_DIVIDE_1024	{TC1CK1=0;TC1CK0=1;}
#define TC1_CLOCK_SOURCE_FC_DIVIDE_128	{TC1CK1=1;TC1CK0=0;}
#define TC1_CLOCK_SOURCE_TC1				{TC1CK1=1;TC1CK0=1;}
#define TC1_MODE_TIMER			(TC1M=0)
#define TC1_MODE_CAPTURE		(TC1M=1)
#define TC1_SIGNAL_EDGE_RISE	(TC1ES=0)
#define TC1_SIGNAL_EDGE_FALL	(TC1ES=1)
#define TC1_DATA_BUFFER_A		(TCR1DA)
#define TC1_DATA_BUFFER_B		(TCR1DB)
#define vSetTimer1DataBufferA(value)	(TCR1DA=value)
#define vSetTimer1DataBufferB(value)	(TCR1DB=value)
#define TC1_CLOCK_SOURCE_FS	(TC1SS=0)
#define TC1_CLOCK_SOURCE_FM	(TC1SS=1)

//UART
#define UART_RECE_ERROR_INT_EN	(UERRIE=1)
#define UART_RECE_ERROR_INT_DIS	(UERRIE=0)
#define UART_RECE_INT_EN		(URIE=1)
#define UART_RECE_INT_DIS		(URIE=0)
#define UART_TRAN_INT_EN		(UTIE=1)
#define UART_TRAN_INT_DIS		(UTIE=0)

//I2C	I2C slave received data stop interrupt flag.
#define I2C_SLAVE_RECE_DATA_STOP_INT_EN	(I2CSTPIE=1)
#define I2C_SLAVE_RECE_DATA_STOP_INT_DIS	(I2CSTPIE=0)
#define I2C_RX_INT_EN	(I2CRIE=1)
#define I2C_RX_INT_DIS	(I2CRIE=0)
#define I2C_TX_INT_EN	(I2CTIE=1)
#define I2C_TX_INT_DIS	(I2CTIE=0)

#define I2C_MODE		{SBIM1=1;SBIM0=1;}
#define UART_MODE		{SBIM1=1;SBIM0=0;}
#define SPI_MODE		{SBIM1=0;SBIM0=1;}
#define IO_MODE			{SBIM1=0;SBIM0=0;}
#define I2C_STANDARD_MODE		ISS=0
#define I2C_FAST_MODE			ISS=1
#define I2C_FAST_CLOCK_FM_4		{I2CTS1=0;I2CTS0=0;}
#define I2C_FAST_CLOCK_FM_8		{I2CTS1=0;I2CTS0=1;}
#define I2C_FAST_CLOCK_FM_12	{I2CTS1=1;I2CTS0=0;}
#define I2C_FAST_CLOCK_FM_16	{I2CTS1=1;I2CTS0=1;}
#define I2C_STANDARD_CLOCK_FM_4		{I2CTS1=0;I2CTS0=0;}
#define I2C_STANDARD_CLOCK_FM_8		{I2CTS1=0;I2CTS0=1;}
#define I2C_STANDARD_CLOCK_FM_12	{I2CTS1=1;I2CTS0=0;}
#define I2C_STANDARD_CLOCK_FM_16	{I2CTS1=1;I2CTS0=1;}
#define I2C_ENABLE				I2CEN=1
#define I2C_DISABLE				I2CEN=0
#define I2C_SLAVE_MODE			IMS =0
#define I2C_MASTER_MODE			IMS = 1
#define I2C_START_STATUS		S_PEND
#define I2C_START_SEND_SCL_CLOCK	S_PEND=1
#define I2C_PENDING_SIGNAL		S_PEND=0
#define I2C_STOP_STATUS			STOP
#define I2C_MASTER_STOP		STOP=1
#define I2C_SLAVE_RETURN_NACK		STOP=1
#define I2C_SLAVE_ADDRESS		I2CSA
#define I2C_ACK				ACK
#define I2C_ZERO_FLAG		Z
#define I2C_DATA_BUFFER		I2CDB
       
//EEPROM
#define EEPROM_READ_START		(RDB=1)
#define EEPROM_WRITE_START	(WR=1)
#define EEPROM_WRITE_ENABLE	(EEWE=1)
#define EEPROM_WRITE_DISABLE	(EEWE=0)
#define EEPROM_POWER_DOWN	(EEPC=0)
#define EEPROM_POWER_OPERATE	(EEPC=1)
#define fgEEPROMWriteCycleIsCompleted()		(EEDF==0)
#define fgEEPROMWriteCycleIsNotCompleted()	(EEDF==1)
#define fgEEPROMReadCycleIsCompleted()		(EEDF==0)
#define fgEEPROMReadCycleIsNotCompleted()	(EEDF==1)
#define bEEPROMReadAddress()	(EEPA)
#define vEEPROMWriteAddress(addr)	(EEPA=addr)
#define bEEPROMReadData()		(EEPD)
#define vEEPROMWriteData(data)	(EEPD=data)

/////////////////////////////////
// Define all I/O pin Base Function
/////////////////////////////////
#define PP50	0x01
#define PP51	0x02
#define PP52	0x04
#define PP53	0x08
#define PP54	0x10
#define PP55	0x20
#define PP56	0x40
#define PP57	0x80
#define PP60	0x01
#define PP61	0x02
#define PP62	0x04
#define PP63	0x08
#define PP64	0x10
#define PP65	0x20
#define PP66	0x40
#define PP67	0x80
#define PP70	0x01
#define PP71	0x02
#define PP72	0x04
#define PP73	0x08
#define PP74	0x10
#define PP75	0x20
#define PP76	0x40
#define PP77	0x80
#define PP80 0x01		
#define PP81 0x02
#define PP82 0x04
#define PP83 0x08
#define PP84 0x10
#define PP85 0x20
#define PP86 0x40
#define PP87 0x80
#define PP90	0x01
#define PP91	0x02
#define PP92	0x04
#define PP93	0x08
#define PP94	0x10
#define PP95	0x20
#define PP96	0x40
#define PP97	0x80

#define P50_HIGH			(P50=1)
#define P50_LOW				(P50=0)
#define P50_READ			(P50)
#define P50_IO_INPUT		(P50CR=1)
#define P50_IO_OUTPUT		(P50CR=0)
#define P50_PULL_UP			(PH50=0)
#define P50_PULL_DOWN		(PL50=0)
#define P50_HIGH_DRIVE		(HD50=0)
#define P50_OPEN_DRAIN		(OD50=1)
#define P50_WAKE_UP		(WU_P50=1)
#define P50_WAKE_UP_EDGE_FALL	(WUE_P50=0)
#define P50_WAKE_UP_EDGE_RISE	(WUE_P50=1)

#define P51_HIGH			(P51=1)
#define P51_LOW				(P51=0)
#define P51_READ			(P51)
#define P51_IO_INPUT		(P51CR=1)
#define P51_IO_OUTPUT		(P51CR=0)
#define P51_PULL_UP			(PH51=0)
#define P51_PULL_DOWN		(PL51=0)
#define P51_HIGH_DRIVE		(HD51=0)
#define P51_OPEN_DRAIN		(OD51=1)
#define P51_WAKE_UP		(WU_P51=1)
#define P51_WAKE_UP_EDGE_FALL	(WUE_P51=0)
#define P51_WAKE_UP_EDGE_RISE	(WUE_P51=1)

#define P52_HIGH			(P52=1)
#define P52_LOW				(P52=0)
#define P52_READ			(P52)
#define P52_IO_INPUT		(P52CR=1)
#define P52_IO_OUTPUT		(P52CR=0)
#define P52_PULL_UP			(PH52=0)
#define P52_PULL_DOWN		(PL52=0)
#define P52_HIGH_DRIVE		(HD52=0)
#define P52_OPEN_DRAIN		(OD52=1)
#define P52_WAKE_UP		(WU_P52=1)
#define P52_WAKE_UP_EDGE_FALL	(WUE_P52=0)
#define P52_WAKE_UP_EDGE_RISE	(WUE_P52=1)

#define P53_HIGH			(P53=1)
#define P53_LOW				(P53=0)
#define P53_READ			(P53)
#define P53_IO_INPUT		(P53CR=1)
#define P53_IO_OUTPUT		(P53CR=0)
#define P53_PULL_UP			(PH53=0)
#define P53_PULL_DOWN		(PL53=0)
#define P53_HIGH_DRIVE		(HD53=0)
#define P53_OPEN_DRAIN		(OD53=1)
#define P53_WAKE_UP		(WU_P53=1)
#define P53_WAKE_UP_EDGE_FALL	(WUE_P53=0)
#define P53_WAKE_UP_EDGE_RISE	(WUE_P53=1)

#define P54_HIGH			(P54=1)
#define P54_LOW				(P54=0)
#define P54_READ			(P54)
#define P54_IO_INPUT		(P54CR=1)
#define P54_IO_OUTPUT		(P54CR=0)
#define P54_PULL_UP			(PH54=0)
#define P54_PULL_DOWN		(PL54=0)
#define P54_HIGH_DRIVE		(HD54=0)
#define P54_OPEN_DRAIN		(OD54=1)
#define P54_WAKE_UP		(WU_P54=1)
#define P54_WAKE_UP_EDGE_FALL	(WUE_P54=0)
#define P54_WAKE_UP_EDGE_RISE	(WUE_P54=1)

#define P54_HIGH			(P54=1)
#define P54_LOW				(P54=0)
#define P54_READ			(P54)
#define P54_IO_INPUT		(P54CR=1)
#define P54_IO_OUTPUT		(P54CR=0)
#define P54_PULL_UP			(PH54=0)
#define P54_PULL_DOWN		(PL54=0)
#define P54_HIGH_DRIVE		(HD54=0)
#define P54_OPEN_DRAIN		(OD54=1)
#define P54_WAKE_UP		(WU_P54=1)
#define P54_WAKE_UP_EDGE_FALL	(WUE_P54=0)
#define P54_WAKE_UP_EDGE_RISE	(WUE_P54=1)

#define P55_HIGH			(P55=1)
#define P55_LOW				(P55=0)
#define P55_READ			(P55)
#define P55_IO_INPUT		(P55CR=1)
#define P55_IO_OUTPUT		(P55CR=0)
#define P55_PULL_UP			(PH55=0)
#define P55_PULL_DOWN		(PL55=0)
#define P55_HIGH_DRIVE		(HD55=0)
#define P55_OPEN_DRAIN		(OD55=1)
#define P55_WAKE_UP		(WU_P55=1)
#define P55_WAKE_UP_EDGE_FALL	(WUE_P55=0)
#define P55_WAKE_UP_EDGE_RISE	(WUE_P55=1)

#define P56_HIGH			(P56=1)
#define P56_LOW				(P56=0)
#define P56_READ			(P56)
#define P56_IO_INPUT		(P56CR=1)
#define P56_IO_OUTPUT		(P56CR=0)
#define P56_PULL_UP			(PH56=0)
#define P56_PULL_DOWN		(PL56=0)
#define P56_HIGH_DRIVE		(HD56=0)
#define P56_OPEN_DRAIN		(OD56=1)
#define P56_WAKE_UP		(WU_P56=1)
#define P56_WAKE_UP_EDGE_FALL	(WUE_P56=0)
#define P56_WAKE_UP_EDGE_RISE	(WUE_P56=1)

#define P57_HIGH			(P57=1)
#define P57_LOW				(P57=0)
#define P57_READ			(P57)
#define P57_IO_INPUT		(P57CR=1)
#define P57_IO_OUTPUT		(P57CR=0)
#define P57_PULL_UP			(PH57=0)
#define P57_PULL_DOWN		(PL57=0)
#define P57_HIGH_DRIVE		(HD57=0)
#define P57_OPEN_DRAIN		(OD57=1)
#define P57_WAKE_UP		(WU_P57=1)
#define P57_WAKE_UP_EDGE_FALL	(WUE_P57=0)
#define P57_WAKE_UP_EDGE_RISE	(WUE_P57=1)

#define P6_INPUT_CHANGE_INT_EN		(ICIE=1)
#define P6_INPUT_CHANGE_INT_DIS		(ICIE=0)
#define P6_INPUT_CHANGE_WAKE_UP_EN	(ICWE=1)
#define P6_INPUT_CHANGE_WAKE_UP_DIS	(ICWE=0)

#define P60_HIGH			(P60=1)
#define P60_LOW				(P60=0)
#define P60_READ			(P60)
#define P60_IO_INPUT		(P60CR=1)
#define P60_IO_OUTPUT		(P60CR=0)
#define P60_PULL_UP			(PH60=0)
#define P60_PULL_DOWN		(PL60=0)
#define P60_HIGH_DRIVE		(HD60=0)
#define P60_OPEN_DRAIN		(OD60=1)
#define P60_AS_GPIO			(ADE0=0)
#define P60_AS_ADC0			(ADE0=1)
#define P60_INT_EN			(EXIE=1)		//External INT (P60)
#define P60_INT_DIS			(EXIE=0)		//External INT (P60)
#define P60_AS_EXTERNAL_INT	(EIS=1)
#define P60_AS_P60			(EIS=0)

#define P61_HIGH			(P61=1)
#define P61_LOW				(P61=0)
#define P61_READ			(P61)
#define P61_IO_INPUT		(P61CR=1)
#define P61_IO_OUTPUT		(P61CR=0)
#define P61_PULL_UP			(PH61=0)
#define P61_PULL_DOWN		(PL61=0)
#define P61_HIGH_DRIVE		(HD61=0)
#define P61_OPEN_DRAIN		(OD61=1)
#define P61_AS_GPIO			(ADE1=0)
#define P61_AS_ADC1			(ADE1=1)

#define P62_HIGH			(P62=1)
#define P62_LOW				(P62=0)
#define P62_READ			(P62)
#define P62_IO_INPUT		(P62CR=1)
#define P62_IO_OUTPUT		(P62CR=0)
#define P62_PULL_UP			(PH62=0)
#define P62_PULL_DOWN		(PL62=0)
#define P62_HIGH_DRIVE		(HD62=0)
#define P62_OPEN_DRAIN		(OD62=1)
#define P62_AS_GPIO			(ADE2=0)
#define P62_AS_ADC2			(ADE2=1)

#define P63_HIGH			(P63=1)
#define P63_LOW				(P63=0)
#define P63_READ			(P63)
#define P63_IO_INPUT		(P63CR=1)
#define P63_IO_OUTPUT		(P63CR=0)
#define P63_PULL_UP			(PH63=0)
#define P63_PULL_DOWN		(PL63=0)
#define P63_HIGH_DRIVE		(HD63=0)
#define P63_OPEN_DRAIN		(OD63=1)
#define P63_AS_GPIO			(ADE3=0)
#define P63_AS_ADC3			(ADE3=1)

#define P64_HIGH			(P64=1)
#define P64_LOW				(P64=0)
#define P64_READ			(P64)
#define P64_IO_INPUT		(P64CR=1)
#define P64_IO_OUTPUT		(P64CR=0)
#define P64_PULL_UP			(PH64=0)
#define P64_PULL_DOWN		(PL64=0)
#define P64_HIGH_DRIVE		(HD64=0)
#define P64_OPEN_DRAIN		(OD64=1)
#define P64_AS_GPIO			(ADE4=0)
#define P64_AS_ADC4			(ADE4=1)

#define P65_HIGH			(P65=1)
#define P65_LOW				(P65=0)
#define P65_READ			(P65)
#define P65_IO_INPUT		(P65CR=1)
#define P65_IO_OUTPUT		(P65CR=0)
#define P65_PULL_UP			(PH65=0)
#define P65_PULL_DOWN		(PL65=0)
#define P65_HIGH_DRIVE		(HD65=0)
#define P65_OPEN_DRAIN		(OD65=1)
#define P65_AS_GPIO			(ADE5=0)
#define P65_AS_ADC5			(ADE5=1)

#define P66_HIGH			(P66=1)
#define P66_LOW				(P66=0)
#define P66_READ			(P66)
#define P66_IO_INPUT		(P66CR=1)
#define P66_IO_OUTPUT		(P66CR=0)
#define P66_PULL_UP			(PH66=0)
#define P66_PULL_DOWN		(PL66=0)
#define P66_HIGH_DRIVE		(HD66=0)
#define P66_OPEN_DRAIN		(OD66=1)
#define P66_AS_GPIO			(ADE6=0)
#define P66_AS_ADC6			(ADE6=1)

#define P67_HIGH			(P67=1)
#define P67_LOW				(P67=0)
#define P67_READ			(P67)
#define P67_IO_INPUT		(P67CR=1)
#define P67_IO_OUTPUT		(P67CR=0)
#define P67_PULL_UP			(PH67=0)
#define P67_PULL_DOWN		(PL67=0)
#define P67_HIGH_DRIVE		(HD67=0)
#define P67_OPEN_DRAIN		(OD67=1)
#define P67_AS_GPIO			(ADE7=0)
#define P67_AS_ADC7			(ADE7=1)

#define P70_HIGH			(P70=1)
#define P70_LOW				(P70=0)
#define P70_READ			(P70)
#define P70_IO_INPUT		(P70CR=1)
#define P70_IO_OUTPUT		(P70CR=0)
#define P70_PULL_UP			(PH70=0)
#define P70_PULL_DOWN		(PL70=0)
#define P70_HIGH_DRIVE		(HD70=0)
#define P70_OPEN_DRAIN		(OD70=1)
#define P70_WAKE_UP		(WU_P70=1)
#define P70_WAKE_UP_EDGE_FALL	(WUE_P70=0)
#define P70_WAKE_UP_EDGE_RISE	(WUE_P70=1)

#define P71_HIGH			(P71=1)
#define P71_LOW				(P71=0)
#define P71_READ			(P71)
#define P71_IO_INPUT		(P71CR=1)
#define P71_IO_OUTPUT		(P71CR=0)
#define P71_PULL_UP			(PH71=0)
#define P71_PULL_DOWN		(PL71=0)
#define P71_HIGH_DRIVE		(HD71=0)
#define P71_OPEN_DRAIN		(OD71=1)
#define P71_WAKE_UP		(WU_P71=1)
#define P71_WAKE_UP_EDGE_FALL	(WUE_P71=0)
#define P71_WAKE_UP_EDGE_RISE	(WUE_P71=1)

#define P72_HIGH			(P72=1)
#define P72_LOW				(P72=0)
#define P72_READ			(P72)
#define P72_IO_INPUT		(P72CR=1)
#define P72_IO_OUTPUT		(P72CR=0)
#define P72_PULL_UP			(PH72=0)
#define P72_PULL_DOWN		(PL72=0)
#define P72_HIGH_DRIVE		(HD72=0)
#define P72_OPEN_DRAIN		(OD72=1)
#define P72_WAKE_UP		(WU_P72=1)
#define P72_WAKE_UP_EDGE_FALL	(WUE_P72=0)
#define P72_WAKE_UP_EDGE_RISE	(WUE_P72=1)

#define P73_HIGH			(P73=1)
#define P73_LOW				(P73=0)
#define P73_READ			(P73)
#define P73_IO_INPUT		(P73CR=1)
#define P73_IO_OUTPUT		(P73CR=0)
#define P73_PULL_UP			(PH73=0)
#define P73_PULL_DOWN		(PL73=0)
#define P73_HIGH_DRIVE		(HD73=0)
#define P73_OPEN_DRAIN		(OD73=1)
#define P73_WAKE_UP		(WU_P73=1)
#define P73_WAKE_UP_EDGE_FALL	(WUE_P73=0)
#define P73_WAKE_UP_EDGE_RISE	(WUE_P73=1)

#define P74_HIGH			(P74=1)
#define P74_LOW				(P74=0)
#define P74_READ			(P74)
#define P74_IO_INPUT		(P74CR=1)
#define P74_IO_OUTPUT		(P74CR=0)
#define P74_PULL_UP			(PH74=0)
#define P74_PULL_DOWN		(PL74=0)
#define P74_HIGH_DRIVE		(HD74=0)
#define P74_OPEN_DRAIN		(OD74=1)
#define P74_WAKE_UP		(WU_P74=1)
#define P74_WAKE_UP_EDGE_FALL	(WUE_P74=0)
#define P74_WAKE_UP_EDGE_RISE	(WUE_P74=1)

#define P75_HIGH			(P75=1)
#define P75_LOW				(P75=0)
#define P75_READ			(P75)
#define P75_IO_INPUT		(P75CR=1)
#define P75_IO_OUTPUT		(P75CR=0)
#define P75_PULL_UP			(PH75=0)
#define P75_PULL_DOWN		(PL75=0)
#define P75_HIGH_DRIVE		(HD75=0)
#define P75_OPEN_DRAIN		(OD75=1)
#define P75_WAKE_UP		(WU_P75=1)
#define P75_WAKE_UP_EDGE_FALL	(WUE_P75=0)
#define P75_WAKE_UP_EDGE_RISE	(WUE_P75=1)

#define P76_HIGH			(P76=1)
#define P76_LOW				(P76=0)
#define P76_READ			(P76)
#define P76_IO_INPUT		(P76CR=1)
#define P76_IO_OUTPUT		(P76CR=0)
#define P76_PULL_UP			(PH76=0)
#define P76_PULL_DOWN		(PL76=0)
#define P76_HIGH_DRIVE		(HD76=0)
#define P76_OPEN_DRAIN		(OD76=1)
#define P76_WAKE_UP		(WU_P76=1)
#define P76_WAKE_UP_EDGE_FALL	(WUE_P76=0)
#define P76_WAKE_UP_EDGE_RISE	(WUE_P76=1)

#define P77_HIGH			(P77=1)
#define P77_LOW				(P77=0)
#define P77_READ			(P77)
#define P77_IO_INPUT		(P77CR=1)
#define P77_IO_OUTPUT		(P77CR=0)
#define P77_PULL_UP			(PH77=0)
#define P77_PULL_DOWN		(PL77=0)
#define P77_HIGH_DRIVE		(HD77=0)
#define P77_OPEN_DRAIN		(OD77=1)
#define P77_WAKE_UP		(WU_P77=1)
#define P77_WAKE_UP_EDGE_FALL	(WUE_P77=0)
#define P77_WAKE_UP_EDGE_RISE	(WUE_P77=1)

#define P80_HIGH			(P80=1)
#define P80_LOW				(P80=0)
#define P80_READ			(P80)
#define P80_IO_INPUT		(P80CR=1)
#define P80_IO_OUTPUT		(P80CR=0)
#define P80_PULL_UP			(PH80=0)
#define P80_PULL_DOWN		(PL80=0)
#define P80_HIGH_DRIVE		(HD80=0)
#define P80_OPEN_DRAIN		(OD80=1)

#define P81_HIGH			(P81=1)
#define P81_LOW				(P81=0)
#define P81_READ			(P81)
#define P81_IO_INPUT		(P81CR=1)
#define P81_IO_OUTPUT		(P81CR=0)
#define P81_PULL_UP			(PH81=0)
#define P81_PULL_DOWN		(PL81=0)
#define P81_HIGH_DRIVE		(HD81=0)
#define P81_OPEN_DRAIN		(OD81=1)

#define P82_HIGH			(P82=1)
#define P82_LOW				(P82=0)
#define P82_READ			(P82)
#define P82_IO_INPUT		(P82CR=1)
#define P82_IO_OUTPUT		(P82CR=0)
#define P82_PULL_UP			(PH82=0)
#define P82_PULL_DOWN		(PL82=0)
#define P82_HIGH_DRIVE		(HD82=0)
#define P82_OPEN_DRAIN		(OD82=1)

#define P83_HIGH			(P83=1)
#define P83_LOW				(P83=0)
#define P83_READ			(P83)
#define P83_IO_INPUT		(P83CR=1)
#define P83_IO_OUTPUT		(P83CR=0)
#define P83_PULL_UP			(PH83=0)
#define P83_PULL_DOWN		(PL83=0)
#define P83_HIGH_DRIVE		(HD83=0)
#define P83_OPEN_DRAIN		(OD83=1)

#define P84_HIGH			(P84=1)
#define P84_LOW				(P84=0)
#define P84_READ			(P84)
#define P84_IO_INPUT		(P84CR=1)
#define P84_IO_OUTPUT		(P84CR=0)
#define P84_PULL_UP			(PH84=0)
#define P84_PULL_DOWN		(PL84=0)
#define P84_HIGH_DRIVE		(HD84=0)
#define P84_OPEN_DRAIN		(OD84=1)

#define P85_HIGH			(P85=1)
#define P85_LOW				(P85=0)
#define P85_READ			(P85)
#define P85_IO_INPUT		(P85CR=1)
#define P85_IO_OUTPUT		(P85CR=0)
#define P85_PULL_UP			(PH85=0)
#define P85_PULL_DOWN		(PL85=0)
#define P85_HIGH_DRIVE		(HD85=0)
#define P85_OPEN_DRAIN		(OD85=1)

#define P86_HIGH			(P86=1)
#define P86_LOW				(P86=0)
#define P86_READ			(P86)
#define P86_IO_INPUT		(P86CR=1)
#define P86_IO_OUTPUT		(P86CR=0)
#define P86_PULL_UP			(PH86=0)
#define P86_PULL_DOWN		(PL86=0)
#define P86_HIGH_DRIVE		(HD86=0)
#define P86_OPEN_DRAIN		(OD86=1)

#define P87_HIGH			(P87=1)
#define P87_LOW				(P87=0)
#define P87_READ			(P87)
#define P87_IO_INPUT		(P87CR=1)
#define P87_IO_OUTPUT		(P87CR=0)
#define P87_PULL_UP			(PH87=0)
#define P87_PULL_DOWN		(PL87=0)
#define P87_HIGH_DRIVE		(HD87=0)
#define P87_OPEN_DRAIN		(OD87=1)

#define P90_HIGH			(P90=1)
#define P90_LOW				(P90=0)
#define P90_READ			(P90)
#define P90_IO_INPUT		(P90CR=1)
#define P90_IO_OUTPUT		(P90CR=0)
#define P90_PULL_UP			(PH90=0)
#define P90_PULL_DOWN		(PL90=0)
#define P90_HIGH_DRIVE		(HD90=0)
#define P90_OPEN_DRAIN		(OD90=1)

#define P91_HIGH			(P91=1)
#define P91_LOW				(P91=0)
#define P91_READ			(P91)
#define P91_IO_INPUT		(P91CR=1)
#define P91_IO_OUTPUT		(P91CR=0)
#define P91_PULL_UP			(PH91=0)
#define P91_PULL_DOWN		(PL91=0)
#define P91_HIGH_DRIVE		(HD91=0)
#define P91_OPEN_DRAIN		(OD91=1)

#define P92_HIGH			(P92=1)
#define P92_LOW				(P92=0)
#define P92_READ			(P92)
#define P92_IO_INPUT		(P92CR=1)
#define P92_IO_OUTPUT		(P92CR=0)
#define P92_PULL_UP			(PH92=0)
#define P92_PULL_DOWN		(PL92=0)
#define P92_HIGH_DRIVE		(HD92=0)
#define P92_OPEN_DRAIN		(OD92=1)

#define P93_HIGH			(P93=1)
#define P93_LOW				(P93=0)
#define P93_READ			(P93)
#define P93_IO_INPUT		(P93CR=1)
#define P93_IO_OUTPUT		(P93CR=0)
#define P93_PULL_UP			(PH93=0)
#define P93_PULL_DOWN		(PL93=0)
#define P93_HIGH_DRIVE		(HD93=0)
#define P93_OPEN_DRAIN		(OD93=1)

#define P94_HIGH			(P94=1)
#define P94_LOW				(P94=0)
#define P94_READ			(P94)
#define P94_IO_INPUT		(P94CR=1)
#define P94_IO_OUTPUT		(P94CR=0)
#define P94_PULL_UP			(PH94=0)
#define P94_PULL_DOWN		(PL94=0)
#define P94_HIGH_DRIVE		(HD94=0)
#define P94_OPEN_DRAIN		(OD94=1)

#define P95_HIGH			(P95=1)
#define P95_LOW				(P95=0)
#define P95_READ			(P95)
#define P95_IO_INPUT		(P95CR=1)
#define P95_IO_OUTPUT		(P95CR=0)
#define P95_PULL_UP			(PH95=0)
#define P95_PULL_DOWN		(PL95=0)
#define P95_HIGH_DRIVE		(HD95=0)
#define P95_OPEN_DRAIN		(OD95=1)

#define P96_HIGH			(P96=1)
#define P96_LOW				(P96=0)
#define P96_READ			(P96)
#define P96_IO_INPUT		(P96CR=1)
#define P96_IO_OUTPUT		(P96CR=0)
#define P96_PULL_UP			(PH96=0)
#define P96_PULL_DOWN		(PL96=0)
#define P96_HIGH_DRIVE		(HD96=0)
#define P96_OPEN_DRAIN		(OD96=1)

#define P97_HIGH			(P97=1)
#define P97_LOW				(P97=0)
#define P97_READ			(P97)
#define P97_IO_INPUT		(P97CR=1)
#define P97_IO_OUTPUT		(P97CR=0)
#define P97_PULL_UP			(PH97=0)
#define P97_PULL_DOWN		(PL97=0)
#define P97_HIGH_DRIVE		(HD97=0)
#define P97_OPEN_DRAIN		(OD97=1)

#endif
