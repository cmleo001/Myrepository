#ifndef _TOUCH_SENSOR_H_
#define _TOUCH_SENSOR_H_

#ifdef TOUCH_SENSOR_FUNCTION

#define SO3G2020_ADDR 0x59
//130314gr01***
#define LED_AIR_VOLUME_1 0x01	// 0x0F bit 0
#define	LED_AIR_VOLUME_2 0x80	// 0x0E bit 7
#define	LED_AIR_VOLUME_3 0x40		// 0x0E bit 6
#define	LED_AIR_VOLUME_4 0x20		// 0x0E bit 5
#define	LED_AIR_VOLUME_5 0x10		// 0x0E bit 4
#define	LED_AIR_VOLUME_6 0x08		// 0x0E bit 3
#define	LED_AIR_VOLUME_7 0x04		// 0x0E bit 2
#define	LED_AIR_VOLUME_8 0x02		// 0x0E bit 1
#define	LED_AIR_VOLUME_9 0x01		// 0x0E bit 0

//#define	LED_AIR_VOLUME_1_TO_1 0x0100	
//#define	LED_AIR_VOLUME_2_TO_2 0x0080
#define	LED_AIR_VOLUME_2_TO_3 0xc0
#define	LED_AIR_VOLUME_2_TO_4 0xe0
#define	LED_AIR_VOLUME_2_TO_5 0xf0
#define	LED_AIR_VOLUME_2_TO_6 0xf8
#define	LED_AIR_VOLUME_2_TO_7 0xfc
#define	LED_AIR_VOLUME_2_TO_8 0xfe
#define	LED_AIR_VOLUME_2_TO_9 0xff

#define	LED_AIR_VOLUME_ODD 0x54 //LED3,LED5&LED7 are on;LED1 is controled by another register //130413gr01
#define	LED_AIR_VOLUME_EVEN 0xaa //LED2 ,LED4,LED6&LED8 are on //130413gr01

#define	LED_PCI_REPLACING 		0x04		// 0x0F bit 2
#define	LED_TUBE_WHITE 		0x80
#define	LED_TUBE_PCI_LED1		0x85

//130314gr01&&&

#define POWER_UP_5S			50	// 100ms*50=5000ms=5second//130123gr03

//#define TOUCH_REGISTER_INTERFACE_CONFIGURATION 0x0000 //130326gr02 //130417gr01 //130419gr01
#define TOUCH_REGISTER_INTERFACE_CONFIGURATION_HIGH 0x00 //130326gr02 //130417gr01//130419gr01
#define TOUCH_REGISTER_INTERFACE_CONFIGURATION_LOW 0x00 //130326gr02 //130417gr01//130419gr01

#define READ_TOUCH_REGISTER_INTERFACE_CONFIGURATION 0x00 //130326gr02 //130417gr01

extern BOOL fgTouchInitial; //130307gr01
extern BOOL fgTouchIsFirstPress; //130326gr01

//extern BYTE bLEDShowData1; //130314gr01***//130328gr01
//extern BYTE bLEDShowData2; 

extern BYTE bLEDBlinkTime;	// unit:0.1s	
extern BYTE bLEDBlinkCount;	// unit:0.1s	
//extern BYTE bLEDBlinkData1;	//130328gr01
//extern BYTE bLEDBlinkData2;	//130328gr01

//extern BYTE bLEDAutoOffData1; //130328gr01
//extern BYTE bLEDAutoOffData2; //130328gr01
extern BYTE bLEDOnTime; 
//extern BYTE bLEDOnTimeCount; //130314gr01&&&					// 130315ja01

void vInitialTouchSensor(void);//130123gr02
void vEventTouchRead(BYTE bAddrLow, BYTE bDataHigh,BYTE bDataLow);//130417gr01

void vEventTouchSensorInterrupt(void);//130123gr02
void vTouchMultiKeyCount(void);//130123gr02
void vHotKeyInput(void); //130123gr03***

void TouchLEDBrightnessAdjust(BYTE fgLEDIsBright);
void vLEDDisplay(void);//130314gr01
void vDisplayLEDAirVolumeIndicationTimer(void);
void vAirVolumeLEDControl(BYTE bLEDNum  );
void vLEDBlink(BYTE bLEDNum,BYTE bTime);
void vAirVolumeLEDAutoOff (BYTE bLEDNum,BYTE bTime);//130328gr02
void vDisplayLEDAirVolumeOn(BYTE bLEDNUM );//130415gr01
void vDisplayLEDAirVolumeAutoOff(BYTE bLEDNum,BYTE bTime);//130415gr01
void vDisplayLEDAirVolume1to9Off(void); ///130416gr01

//130417gr01***
#define _RAM_TOUCH_READ_DATA	@0x96
static BYTE bTouchDataRegister[3] _RAM_TOUCH_READ_DATA ;
static WORD wTouchStripsRegister _RAM_TOUCH_READ_DATA ;
//130417gr01&&&

//130328gr01***
#define _RAM_ADDR_TOUCH_SHOW_DATA1		@0x90
#define _RAM_ADDR_TOUCH_SHOW_DATA2		@0x91

#define _RAM_ADDR_TOUCH_BLINK_DATA1		@0x92
#define _RAM_ADDR_TOUCH_BLINK_DATA2		@0x93

#define _RAM_ADDR_TOUCH_AUTOOFF_DATA1	@0x94
#define _RAM_ADDR_TOUCH_AUTOOFF_DATA2	@0x95

static BYTE bLEDShowData1			_RAM_ADDR_TOUCH_SHOW_DATA1;  

static BOOL LED_AIR_VOLUME_2_BIT	_RAM_ADDR_TOUCH_SHOW_DATA1@7;  //led2
static BOOL LED_AIR_VOLUME_3_BIT	_RAM_ADDR_TOUCH_SHOW_DATA1@6;  //led3
static BOOL LED_AIR_VOLUME_4_BIT	_RAM_ADDR_TOUCH_SHOW_DATA1@5;  //led4
static BOOL LED_AIR_VOLUME_5_BIT	_RAM_ADDR_TOUCH_SHOW_DATA1@4;  //led5 
static BOOL LED_AIR_VOLUME_6_BIT	_RAM_ADDR_TOUCH_SHOW_DATA1@3;  //led6 
static BOOL LED_AIR_VOLUME_7_BIT	_RAM_ADDR_TOUCH_SHOW_DATA1@2;  //led7 
static BOOL LED_AIR_VOLUME_8_BIT	_RAM_ADDR_TOUCH_SHOW_DATA1@1;  //led8 
static BOOL LED_AIR_VOLUME_9_BIT	_RAM_ADDR_TOUCH_SHOW_DATA1@0;  //led9 

static BYTE bLEDShowData2			_RAM_ADDR_TOUCH_SHOW_DATA2; 

static BOOL LED_AIR_VOLUME_1_BIT	_RAM_ADDR_TOUCH_SHOW_DATA2@0;  //led1
static BOOL LED_PCI_REPLACING_BIT	_RAM_ADDR_TOUCH_SHOW_DATA2@2;  //led pci
//static BOOL LED_TUBE_BIT			_RAM_ADDR_TOUCH_SHOW_DATA2@7;  //led tube		// 130401jac01

static BYTE bLEDBlinkData1			_RAM_ADDR_TOUCH_BLINK_DATA1;

static BOOL LED_AIR_VOLUME_2_BLINK_BIT	_RAM_ADDR_TOUCH_BLINK_DATA1@7;  //led2
static BOOL LED_AIR_VOLUME_3_BLINK_BIT	_RAM_ADDR_TOUCH_BLINK_DATA1@6;  //led3
static BOOL LED_AIR_VOLUME_4_BLINK_BIT	_RAM_ADDR_TOUCH_BLINK_DATA1@5;  //led4
static BOOL LED_AIR_VOLUME_5_BLINK_BIT	_RAM_ADDR_TOUCH_BLINK_DATA1@4;  //led5 
static BOOL LED_AIR_VOLUME_6_BLINK_BIT	_RAM_ADDR_TOUCH_BLINK_DATA1@3;  //led6 
static BOOL LED_AIR_VOLUME_7_BLINK_BIT	_RAM_ADDR_TOUCH_BLINK_DATA1@2;  //led7 
static BOOL LED_AIR_VOLUME_8_BLINK_BIT	_RAM_ADDR_TOUCH_BLINK_DATA1@1;  //led8 
static BOOL LED_AIR_VOLUME_9_BLINK_BIT	_RAM_ADDR_TOUCH_BLINK_DATA1@0;  //led9 

static BYTE bLEDBlinkData2					_RAM_ADDR_TOUCH_BLINK_DATA2;  
static BOOL LED_AIR_VOLUME_1_BLINK_BIT	_RAM_ADDR_TOUCH_BLINK_DATA2@0;  //led1
static BOOL LED_PCI_REPLACING_BLINK_BIT	_RAM_ADDR_TOUCH_BLINK_DATA2@2;  //led pci
//static BOOL LED_TUBE_BLINK_BIT			_RAM_ADDR_TOUCH_BLINK_DATA2@7;  //led tube		// 130401jac01

static BYTE bLEDAutoOffData1					_RAM_ADDR_TOUCH_AUTOOFF_DATA1; 
static BOOL LED_AIR_VOLUME_2_AUTO_OFF_BIT	_RAM_ADDR_TOUCH_AUTOOFF_DATA1@7;  //led2
static BOOL LED_AIR_VOLUME_3_AUTO_OFF_BIT	_RAM_ADDR_TOUCH_AUTOOFF_DATA1@6;  //led3
static BOOL LED_AIR_VOLUME_4_AUTO_OFF_BIT	_RAM_ADDR_TOUCH_AUTOOFF_DATA1@5;  //led4
static BOOL LED_AIR_VOLUME_5_AUTO_OFF_BIT	_RAM_ADDR_TOUCH_AUTOOFF_DATA1@4;  //led5 
static BOOL LED_AIR_VOLUME_6_AUTO_OFF_BIT	_RAM_ADDR_TOUCH_AUTOOFF_DATA1@3;  //led6 
static BOOL LED_AIR_VOLUME_7_AUTO_OFF_BIT	_RAM_ADDR_TOUCH_AUTOOFF_DATA1@2;  //led7 
static BOOL LED_AIR_VOLUME_8_AUTO_OFF_BIT	_RAM_ADDR_TOUCH_AUTOOFF_DATA1@1;  //led8 
static BOOL LED_AIR_VOLUME_9_AUTO_OFF_BIT	_RAM_ADDR_TOUCH_AUTOOFF_DATA1@0;  //led9 

static BYTE bLEDAutoOffData2					_RAM_ADDR_TOUCH_AUTOOFF_DATA2;  
static BOOL LED_AIR_VOLUME_1_AUTO_OFF_BIT	_RAM_ADDR_TOUCH_AUTOOFF_DATA2@0;  //led1
static BOOL LED_PCI_REPLACING_AUTO_OFF_BIT	_RAM_ADDR_TOUCH_AUTOOFF_DATA2@2;  //led pci
//static BOOL LED_TUBE_AUTO_OFF_BIT				_RAM_ADDR_TOUCH_AUTOOFF_DATA2@7;  //led tube		// 130401jac01

//130328gr01&&&
//#define vDisplayLEDAirVolumeOn( bLEDNUM )			{vAirVolumeLEDControl((bLEDNUM+3)/4);}	// 1~9 is LED1~LED9	//130306a04v//130415gr01
//#define vDisplayLEDAirVolumeBlinkOn( bLEDNUM, bTime)	{vLEDBlink((bLEDNUM+3)/4,bTime);}             //130306a04v//130415gr01
//#define vDisplayLEDAirVolumeAutoOff( bLEDNUM, bTime )		{vAirVolumeLEDAutoOff((bLEDNUM+3)/4,bTime);}	//130328gr02//130415gr01
//130314gr01***//130328gr01***
#define vDisplayLEDAirVolume1On()					{LED_AIR_VOLUME_1_BIT=1;}
#define vDisplayLEDAirVolume2On()					{LED_AIR_VOLUME_2_BIT=1;}
#define vDisplayLEDAirVolume3On()					{LED_AIR_VOLUME_3_BIT=1;}
#define vDisplayLEDAirVolume4On()					{LED_AIR_VOLUME_4_BIT=1;}
#define vDisplayLEDAirVolume5On()					{LED_AIR_VOLUME_5_BIT=1;}
#define vDisplayLEDAirVolume6On()					{LED_AIR_VOLUME_6_BIT=1;}
#define vDisplayLEDAirVolume7On()					{LED_AIR_VOLUME_7_BIT=1;}
#define vDisplayLEDAirVolume8On()					{LED_AIR_VOLUME_8_BIT=1;}
#define vDisplayLEDAirVolume9On()					{LED_AIR_VOLUME_9_BIT=1;}

#define vDisplayLEDAirVolume1to1On()				{LED_AIR_VOLUME_1_BIT=1;bLEDShowData1=0;}
#define vDisplayLEDAirVolume1to2On()				{LED_AIR_VOLUME_1_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2;}
#define vDisplayLEDAirVolume1to3On()				{LED_AIR_VOLUME_1_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_3;}
#define vDisplayLEDAirVolume1to4On()				{LED_AIR_VOLUME_1_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_4;}
#define vDisplayLEDAirVolume1to5On()				{LED_AIR_VOLUME_1_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_5;}
#define vDisplayLEDAirVolume1to6On()				{LED_AIR_VOLUME_1_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_6;}
#define vDisplayLEDAirVolume1to7On()				{LED_AIR_VOLUME_1_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_7;}
#define vDisplayLEDAirVolume1to8On()				{LED_AIR_VOLUME_1_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_8;}
#define vDisplayLEDAirVolume1to9On()				{LED_AIR_VOLUME_1_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_9;}

#define vDisplayLEDAirVolumeOddOn()					{bLEDShowData1=LED_AIR_VOLUME_ODD;LED_AIR_VOLUME_1_BIT=1;} //130413gr01 //130416gr02
#define vDisplayLEDAirVolumeEvenOn()				{bLEDShowData1=LED_AIR_VOLUME_EVEN;LED_AIR_VOLUME_1_BIT=0;} //130413gr01 //130416gr02

#define vDisplayLEDPCIReplacingOn()					{LED_PCI_REPLACING_BIT=1;}

//#define vDisplayLEDTubeWhiteOn()					{LED_TUBE_BIT=1;}			// 130401jac01

#define vDisplayLEDAirVolume1Off()					{LED_AIR_VOLUME_1_BIT=0;}
#define vDisplayLEDAirVolume2Off()					{LED_AIR_VOLUME_2_BIT=0;}
#define vDisplayLEDAirVolume3Off()					{LED_AIR_VOLUME_3_BIT=0;}
#define vDisplayLEDAirVolume4Off()					{LED_AIR_VOLUME_4_BIT=0;}
#define vDisplayLEDAirVolume5Off()					{LED_AIR_VOLUME_5_BIT=0;}
#define vDisplayLEDAirVolume6Off()					{LED_AIR_VOLUME_6_BIT=0;}
#define vDisplayLEDAirVolume7Off()					{LED_AIR_VOLUME_7_BIT=0;}
#define vDisplayLEDAirVolume8Off()					{LED_AIR_VOLUME_8_BIT=0;}
#define vDisplayLEDAirVolume9Off()					{LED_AIR_VOLUME_9_BIT=0;}

#define vDisplayLEDAirVolume1to1Off()				{LED_AIR_VOLUME_1_BIT=0;bLEDShowData1=0;}
#define vDisplayLEDAirVolume1to2Off()				{LED_AIR_VOLUME_1_BIT=0;bLEDShowData1=0;}
#define vDisplayLEDAirVolume1to3Off()				{LED_AIR_VOLUME_1_BIT=0;bLEDShowData1=0;}
#define vDisplayLEDAirVolume1to4Off()				{LED_AIR_VOLUME_1_BIT=0;bLEDShowData1=0;}
#define vDisplayLEDAirVolume1to5Off()				{LED_AIR_VOLUME_1_BIT=0;bLEDShowData1=0;}
#define vDisplayLEDAirVolume1to6Off()				{LED_AIR_VOLUME_1_BIT=0;bLEDShowData1=0;}
#define vDisplayLEDAirVolume1to7Off()				{LED_AIR_VOLUME_1_BIT=0;bLEDShowData1=0;}
#define vDisplayLEDAirVolume1to8Off()				{LED_AIR_VOLUME_1_BIT=0;bLEDShowData1=0;}
//#define vDisplayLEDAirVolume1to9Off()				{LED_AIR_VOLUME_1_BIT=0;bLEDShowData1=0;} //130416gr01

#define vDisplayLEDPCIReplacingOff()				{LED_PCI_REPLACING_BIT=0;}

//#define vDisplayLEDTubeWhiteOff()					{LED_TUBE_BIT=0;}			// 130401jac01

#define vDisplayLEDAirVolume1BlinkOn(bTime)			{bLEDBlinkCount=0;LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_BLINK_BIT=1;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume2BlinkOn(bTime)			{bLEDBlinkCount=0;LED_AIR_VOLUME_2_BIT=1;LED_AIR_VOLUME_2_BLINK_BIT=1;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume3BlinkOn(bTime)			{bLEDBlinkCount=0;LED_AIR_VOLUME_3_BIT=1;LED_AIR_VOLUME_3_BLINK_BIT=1;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume4BlinkOn(bTime)			{bLEDBlinkCount=0;LED_AIR_VOLUME_4_BIT=1;LED_AIR_VOLUME_4_BLINK_BIT=1;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume5BlinkOn(bTime)			{bLEDBlinkCount=0;LED_AIR_VOLUME_5_BIT=1;LED_AIR_VOLUME_5_BLINK_BIT=1;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume6BlinkOn(bTime)			{bLEDBlinkCount=0;LED_AIR_VOLUME_6_BIT=1;LED_AIR_VOLUME_6_BLINK_BIT=1;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume7BlinkOn(bTime)			{bLEDBlinkCount=0;LED_AIR_VOLUME_7_BIT=1;LED_AIR_VOLUME_7_BLINK_BIT=1;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume8BlinkOn(bTime)			{bLEDBlinkCount=0;LED_AIR_VOLUME_8_BIT=1;LED_AIR_VOLUME_8_BLINK_BIT=1;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume9BlinkOn(bTime)			{bLEDBlinkCount=0;LED_AIR_VOLUME_9_BIT=1;LED_AIR_VOLUME_9_BLINK_BIT=1;bLEDBlinkTime=bTime;}

#define vDisplayLEDAirVolume1to1BlinkOn(bTime)		{bLEDBlinkCount=0;LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_BLINK_BIT=1;bLEDShowData1=0;bLEDBlinkData1=0;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume1to2BlinkOn(bTime)		{bLEDBlinkCount=0;LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_BLINK_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2;bLEDBlinkData1=LED_AIR_VOLUME_2;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume1to3BlinkOn(bTime)		{bLEDBlinkCount=0;LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_BLINK_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_3;bLEDBlinkData1=LED_AIR_VOLUME_2_TO_3;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume1to4BlinkOn(bTime)		{bLEDBlinkCount=0;LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_BLINK_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_4;bLEDBlinkData1=LED_AIR_VOLUME_2_TO_4;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume1to5BlinkOn(bTime)		{bLEDBlinkCount=0;LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_BLINK_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_5;bLEDBlinkData1=LED_AIR_VOLUME_2_TO_5;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume1to6BlinkOn(bTime)		{bLEDBlinkCount=0;LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_BLINK_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_6;bLEDBlinkData1=LED_AIR_VOLUME_2_TO_6;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume1to7BlinkOn(bTime)		{bLEDBlinkCount=0;LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_BLINK_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_7;bLEDBlinkData1=LED_AIR_VOLUME_2_TO_7;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume1to8BlinkOn(bTime)		{bLEDBlinkCount=0;LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_BLINK_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_8;bLEDBlinkData1=LED_AIR_VOLUME_2_TO_8;bLEDBlinkTime=bTime;}
#define vDisplayLEDAirVolume1to9BlinkOn(bTime)		{bLEDBlinkCount=0;LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_BLINK_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_9;bLEDBlinkData1=LED_AIR_VOLUME_2_TO_9;bLEDBlinkTime=bTime;}

#define vDisplayLEDPCIReplacingBlinkOn(bTime)		{bLEDBlinkCount=0;LED_PCI_REPLACING_BIT=1;LED_PCI_REPLACING_BLINK_BIT=1;bLEDBlinkTime=bTime;}
//#define vDisplayLEDTubeWhiteBlinkOn(bTime)			{bLEDBlinkCount=0;LED_TUBE_BIT=1;LED_TUBE_BLINK_BIT=1;bLEDBlinkTime=bTime;}		// 130401jac01

#define vDisplayLEDAirVolume1BlinkOff()		{LED_AIR_VOLUME_1_BIT=0;LED_AIR_VOLUME_1_BLINK_BIT=0;}
#define vDisplayLEDAirVolume2BlinkOff()		{LED_AIR_VOLUME_2_BIT=0;LED_AIR_VOLUME_2_BLINK_BIT=0;}
#define vDisplayLEDAirVolume3BlinkOff()		{LED_AIR_VOLUME_3_BIT=0;LED_AIR_VOLUME_3_BLINK_BIT=0;}
#define vDisplayLEDAirVolume4BlinkOff()		{LED_AIR_VOLUME_4_BIT=0;LED_AIR_VOLUME_4_BLINK_BIT=0;}
#define vDisplayLEDAirVolume5BlinkOff()		{LED_AIR_VOLUME_5_BIT=0;LED_AIR_VOLUME_5_BLINK_BIT=0;}
#define vDisplayLEDAirVolume6BlinkOff()		{LED_AIR_VOLUME_6_BIT=0;LED_AIR_VOLUME_6_BLINK_BIT=0;}
#define vDisplayLEDAirVolume7BlinkOff()		{LED_AIR_VOLUME_7_BIT=0;LED_AIR_VOLUME_7_BLINK_BIT=0;}
#define vDisplayLEDAirVolume8BlinkOff()		{LED_AIR_VOLUME_8_BIT=0;LED_AIR_VOLUME_8_BLINK_BIT=0;}
#define vDisplayLEDAirVolume9BlinkOff()		{LED_AIR_VOLUME_9_BIT=0;LED_AIR_VOLUME_9_BLINK_BIT=0;}

#define vDisplayLEDAirVolume1to1BlinkOff()	{LED_AIR_VOLUME_1_BIT=0;LED_AIR_VOLUME_1_BLINK_BIT=0;bLEDShowData1=0;bLEDBlinkData1=0;}
#define vDisplayLEDAirVolume1to2BlinkOff()	{LED_AIR_VOLUME_1_BIT=0;LED_AIR_VOLUME_1_BLINK_BIT=0;bLEDShowData1=0;bLEDBlinkData1=0;}
#define vDisplayLEDAirVolume1to3BlinkOff()	{LED_AIR_VOLUME_1_BIT=0;LED_AIR_VOLUME_1_BLINK_BIT=0;bLEDShowData1=0;bLEDBlinkData1=0;}
#define vDisplayLEDAirVolume1to4BlinkOff()	{LED_AIR_VOLUME_1_BIT=0;LED_AIR_VOLUME_1_BLINK_BIT=0;bLEDShowData1=0;bLEDBlinkData1=0;}
#define vDisplayLEDAirVolume1to5BlinkOff()	{LED_AIR_VOLUME_1_BIT=0;LED_AIR_VOLUME_1_BLINK_BIT=0;bLEDShowData1=0;bLEDBlinkData1=0;}
#define vDisplayLEDAirVolume1to6BlinkOff()	{LED_AIR_VOLUME_1_BIT=0;LED_AIR_VOLUME_1_BLINK_BIT=0;bLEDShowData1=0;bLEDBlinkData1=0;}
#define vDisplayLEDAirVolume1to7BlinkOff()	{LED_AIR_VOLUME_1_BIT=0;LED_AIR_VOLUME_1_BLINK_BIT=0;bLEDShowData1=0;bLEDBlinkData1=0;}
#define vDisplayLEDAirVolume1to8BlinkOff()	{LED_AIR_VOLUME_1_BIT=0;LED_AIR_VOLUME_1_BLINK_BIT=0;bLEDShowData1=0;bLEDBlinkData1=0;}
#define vDisplayLEDAirVolume1to9BlinkOff()	{LED_AIR_VOLUME_1_BIT=0;LED_AIR_VOLUME_1_BLINK_BIT=0;bLEDShowData1=0;bLEDBlinkData1=0;}

#define vDisplayLEDPCIReplacingBlinkOff()	{LED_PCI_REPLACING_BIT=0;LED_PCI_REPLACING_BLINK_BIT=0;}
//#define vDisplayLEDTubeWhiteBlinkOff()		{LED_TUBE_BIT=0;LED_TUBE_BLINK_BIT=0;}		// 130401jac01

#define vDisplayLEDAirVolume1AutoOff(bTime)		{LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_AUTO_OFF_BIT=1;bLEDOnTime=bTime;}					// 130315ja01***
#define vDisplayLEDAirVolume2AutoOff(bTime)		{LED_AIR_VOLUME_2_BIT=1;LED_AIR_VOLUME_2_AUTO_OFF_BIT=1;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume3AutoOff(bTime)		{LED_AIR_VOLUME_3_BIT=1;LED_AIR_VOLUME_3_AUTO_OFF_BIT=1;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume4AutoOff(bTime)		{LED_AIR_VOLUME_4_BIT=1;LED_AIR_VOLUME_4_AUTO_OFF_BIT=1;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume5AutoOff(bTime)		{LED_AIR_VOLUME_5_BIT=1;LED_AIR_VOLUME_5_AUTO_OFF_BIT=1;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume6AutoOff(bTime)		{LED_AIR_VOLUME_6_BIT=1;LED_AIR_VOLUME_6_AUTO_OFF_BIT=1;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume7AutoOff(bTime)		{LED_AIR_VOLUME_7_BIT=1;LED_AIR_VOLUME_7_AUTO_OFF_BIT=1;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume8AutoOff(bTime)		{LED_AIR_VOLUME_8_BIT=1;LED_AIR_VOLUME_8_AUTO_OFF_BIT=1;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume9AutoOff(bTime)		{LED_AIR_VOLUME_9_BIT=1;LED_AIR_VOLUME_9_AUTO_OFF_BIT=1;bLEDOnTime=bTime;}

#define vDisplayLEDAirVolume1to1AutoOff(bTime)	{LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_AUTO_OFF_BIT=1;bLEDShowData1=0;bLEDAutoOffData1=0;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume1to2AutoOff(bTime)	{LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_AUTO_OFF_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2;bLEDAutoOffData1=LED_AIR_VOLUME_2;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume1to3AutoOff(bTime)	{LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_AUTO_OFF_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_3;bLEDAutoOffData1=LED_AIR_VOLUME_2_TO_3;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume1to4AutoOff(bTime)	{LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_AUTO_OFF_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_4;bLEDAutoOffData1=LED_AIR_VOLUME_2_TO_4;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume1to5AutoOff(bTime)	{LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_AUTO_OFF_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_5;bLEDAutoOffData1=LED_AIR_VOLUME_2_TO_5;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume1to6AutoOff(bTime)	{LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_AUTO_OFF_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_6;bLEDAutoOffData1=LED_AIR_VOLUME_2_TO_6;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume1to7AutoOff(bTime)	{LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_AUTO_OFF_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_7;bLEDAutoOffData1=LED_AIR_VOLUME_2_TO_7;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume1to8AutoOff(bTime)	{LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_AUTO_OFF_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_8;bLEDAutoOffData1=LED_AIR_VOLUME_2_TO_8;bLEDOnTime=bTime;}
#define vDisplayLEDAirVolume1to9AutoOff(bTime)	{LED_AIR_VOLUME_1_BIT=1;LED_AIR_VOLUME_1_AUTO_OFF_BIT=1;bLEDShowData1=LED_AIR_VOLUME_2_TO_9;bLEDAutoOffData1=LED_AIR_VOLUME_2_TO_9;bLEDOnTime=bTime;}

#define vDisplayLEDPCIReplacingAutoOff(bTime)	{LED_PCI_REPLACING_BIT=1;LED_PCI_REPLACING_AUTO_OFF_BIT=1;bLEDOnTime=bTime;}
//#define vDisplayLEDTubeWhiteAutoOff(bTime)		{LED_TUBE_BIT=1;LED_TUBE_AUTO_OFF_BIT=1;bLEDOnTime=bTime;}					// 130315ja01&&&		// 130401jac01
//130328gr01&&&
#define vDisplayLEDAllOff()					{bLEDShowData2=0;bLEDShowData1=0;bLEDBlinkData1=0;bLEDBlinkData2=0;}	//130322gr01
#define vDisplayLEDAllOn()					{bLEDShowData2=0xff;bLEDShowData1=0xff;}


//130314gr01&&&
#define vDisplayLEDBright()								{TouchLEDBrightnessAdjust(TRUE);}
#define vDisplayLEDDim()									{TouchLEDBrightnessAdjust(FALSE);}
#else
#define fgTouchInitial		1

#define vInitialTouchSensor()
#define vAirVolumeLEDControl( bLEDNUM, fgLEDOn)
#define vEventTouchRead(BYTE bAddrLow, BYTE bDataHigh,BYTE bDataLow)//130417gr01
#define vEventTouchSensorInterrupt()
#define vTouchMultiKeyCount()
#define vHotKeyInput()
#define TouchLEDBrightnessAdjust(fgLEDIsBright) //130314gr01
#define vLEDDisplay() //130314gr01
#define vDisplayLEDAirVolumeIndicationTimer()

#define vModeKeyInput()

#define vLEDBlinkShow()
#define vLEDBlink( bLEDNUM, bTime)
//130314gr01***
#define vDisplayLEDAirVolume1On()					
#define vDisplayLEDAirVolume2On()					
#define vDisplayLEDAirVolume3On()					
#define vDisplayLEDAirVolume4On()					
#define vDisplayLEDAirVolume5On()					
#define vDisplayLEDAirVolume6On()					
#define vDisplayLEDAirVolume7On()					
#define vDisplayLEDAirVolume8On()					
#define vDisplayLEDAirVolume9On()					

#define vDisplayLEDAirVolume1to2On()				
#define vDisplayLEDAirVolume1to3On()				
#define vDisplayLEDAirVolume1to4On()				
#define vDisplayLEDAirVolume1to5On()				
#define vDisplayLEDAirVolume1to6On()				
#define vDisplayLEDAirVolume1to7On()				
#define vDisplayLEDAirVolume1to8On()				
#define vDisplayLEDAirVolume1to9On()				

#define vDisplayLEDPCIReplacingOn()					

#define vDisplayLEDTubeWhiteOn()					

#define vDisplayLEDAirVolume1Off()				
#define vDisplayLEDAirVolume2Off()					
#define vDisplayLEDAirVolume3Off()					
#define vDisplayLEDAirVolume4Off()					
#define vDisplayLEDAirVolume5Off()					
#define vDisplayLEDAirVolume6Off()					
#define vDisplayLEDAirVolume7Off()					
#define vDisplayLEDAirVolume8Off()					
#define vDisplayLEDAirVolume9Off()					

#define vDisplayLEDAirVolume1to2Off()				
#define vDisplayLEDAirVolume1to3Off()				
#define vDisplayLEDAirVolume1to4Off()				
#define vDisplayLEDAirVolume1to5Off()				
#define vDisplayLEDAirVolume1to6Off()				
#define vDisplayLEDAirVolume1to7Off()				
#define vDisplayLEDAirVolume1to8Off()				
#define vDisplayLEDAirVolume1to9Off()				

#define vDisplayLEDPCIReplacingOff()			

#define vDisplayLEDTubeWhiteOff()					

#define vDisplayLEDAirVolume1BlinkOn(bTime)			
#define vDisplayLEDAirVolume2BlinkOn(bTime)			
#define vDisplayLEDAirVolume3BlinkOn(bTime)			
#define vDisplayLEDAirVolume4BlinkOn(bTime)			
#define vDisplayLEDAirVolume5BlinkOn(bTime)			
#define vDisplayLEDAirVolume6BlinkOn(bTime)			
#define vDisplayLEDAirVolume7BlinkOn(bTime)			
#define vDisplayLEDAirVolume8BlinkOn(bTime)			
#define vDisplayLEDAirVolume9BlinkOn(bTime)			

#define vDisplayLEDAirVolume1to2BlinkOn(bTime)		
#define vDisplayLEDAirVolume1to3BlinkOn(bTime)		
#define vDisplayLEDAirVolume1to4BlinkOn(bTime)		
#define vDisplayLEDAirVolume1to5BlinkOn(bTime)		
#define vDisplayLEDAirVolume1to6BlinkOn(bTime)		
#define vDisplayLEDAirVolume1to7BlinkOn(bTime)		
#define vDisplayLEDAirVolume1to8BlinkOn(bTime)		
#define vDisplayLEDAirVolume1to9BlinkOn(bTime)		

#define vDisplayLEDPCIReplacingBlinkOn(bTime)		
#define vDisplayLEDTubeWhiteBlinkOn(bTime)				

#define vDisplayLEDAirVolume1BlinkOff()		
#define vDisplayLEDAirVolume2BlinkOff()		
#define vDisplayLEDAirVolume3BlinkOff()		
#define vDisplayLEDAirVolume4BlinkOff()		
#define vDisplayLEDAirVolume5BlinkOff()		
#define vDisplayLEDAirVolume6BlinkOff()		
#define vDisplayLEDAirVolume7BlinkOff()		
#define vDisplayLEDAirVolume8BlinkOff()		
#define vDisplayLEDAirVolume9BlinkOff()		

#define vDisplayLEDAirVolume1to2BlinkOff()		
#define vDisplayLEDAirVolume1to3BlinkOff()		
#define vDisplayLEDAirVolume1to4BlinkOff()		
#define vDisplayLEDAirVolume1to5BlinkOff()		
#define vDisplayLEDAirVolume1to6BlinkOff()		
#define vDisplayLEDAirVolume1to7BlinkOff()		
#define vDisplayLEDAirVolume1to8BlinkOff()		
#define vDisplayLEDAirVolume1to9BlinkOff()		

#define vDisplayLEDPCIReplacingBlinkOff()		
#define vDisplayLEDTubeWhiteBlinkOff()				

#define vDisplayLEDAirVolume1AutoOff(bTime)			
#define vDisplayLEDAirVolume2AutoOff(bTime)			
#define vDisplayLEDAirVolume3AutoOff(bTime)			
#define vDisplayLEDAirVolume4AutoOff(bTime)			
#define vDisplayLEDAirVolume5AutoOff(bTime)			
#define vDisplayLEDAirVolume6AutoOff(bTime)			
#define vDisplayLEDAirVolume7AutoOff(bTime)			
#define vDisplayLEDAirVolume8AutoOff(bTime)			
#define vDisplayLEDAirVolume9AutoOff(bTime)			

#define vDisplayLEDAirVolume1to2AutoOff(bTime)		
#define vDisplayLEDAirVolume1to3AutoOff(bTime)		
#define vDisplayLEDAirVolume1to4AutoOff(bTime)		
#define vDisplayLEDAirVolume1to5AutoOff(bTime)		
#define vDisplayLEDAirVolume1to6AutoOff(bTime)		
#define vDisplayLEDAirVolume1to7AutoOff(bTime)		
#define vDisplayLEDAirVolume1to8AutoOff(bTime)		
#define vDisplayLEDAirVolume1to9AutoOff(bTime)		

#define vDisplayLEDPCIReplacingAutoOff(bTime)		
#define vDisplayLEDTubeWhiteAutoOff(bTime)			

#define vDisplayLEDAirVolumeOn( bLEDNUM )
#define vDisplayLEDAirVolumeBlinkOn( bLEDNUM, bTime)

#define vDisplayLEDAllOff()
#define vDisplayLEDAllOn()

#define vDisplayLEDBright()
#define vDisplayLEDDim()
//130314gr01&&&

#endif


#endif

