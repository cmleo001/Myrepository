#ifndef _EEPROM_H_
#define _EEPROM_H_

#ifdef EEPROM_FUNCTION

enum
{
	EEPROM_MAGIC_ADDR0,
	EEPROM_MAGIC_ADDR1,

#ifdef TOUCH_MCU
////////////////////////////////////////////////
//Only For Touch MCU
////////////////////////////////////////////////
	//the accumulated time for cleaning Filter
	EE_CLEANING_FILTER_TIME_HOUR_LOW,
	EE_CLEANING_FILTER_TIME_HOUR_HIGH,
	
	//Error Counter of Ion Generation
	EE_ERROR_COUNTER_ION,
	
	// History of "Warning for Cleaning PCI UNIT Electrode"
	EE_CLEARN_PCI_ELECTRODE,

	//Error Mode" which occurred last
	EE_ERROR_MODE_LAST,

	//Auto Restart function is valid or invalid
	//If "Auto Restart function" is valid, the following items are memorized.

	// Watch Mode
	EE_WATCH_MODE,

	// Child Lock
	EE_CHILD_LOCK,

	//Light OFF Function
	EE_LIGHT_OFF,
	
	//Auto Start Function
	EE_AUTO_START,
	
	//Ion Mode
	EE_ION_MODE,	//130306le04

	//On/Off Timer
	EE_ON_OFF_TIMER,

	// Power
	EE_POWER_MODE,
	
	// Air Volume
	EE_AIR_VOLUME,
	
	// Rotation Mode
	EE_OSCILLATE_MODE_ON_OFF,		//Only record On or Off.
	EE_OSCILLATE_MODE_ANGLE,	//Record 15,30,60,90,120 degreess
	EE_OSCILLATE_INITIAL_PROCESS,//130409Ke06
	
	//Louver Mode
	EE_LOUVER_MODE,		//record STOP, SWING
	EE_LOUVER_ANGLE,		//record LOUVER_HORIZONTAL_1,	LOUVER_UPPER40D,	LOUVER_HORIZONTAL_3,	LOUVER_LOWER20D, LOUVER_OFF_MEMORIZED
	
	
#endif

#ifdef MAIN_MCU
////////////////////////////////////////////////
//Only For Main MCU
////////////////////////////////////////////////
	// Rotation Mode
	EE_OSCILLATE_MODE_ON_OFF,		//Only record On or Off.
	EE_OSCILLATE_MODE_ANGLE,	//Record 15,30,60,90,120 degreess
	EE_OSCILLATE_MEMORIZED_POSITION_LOW,	//0xF8
	EE_OSCILLATE_MEMORIZED_POSITION_HIGH,	//0x07

	//Louver Mode
	//If "Louver Mode" is "STOP", the stopped position is memorized.
	EE_LOUVER_MEMORIZED_POSITION_LOW,	//0xE4
	EE_LOUVER_MEMORIZED_POSITION_HIGH,	//0x00

	EE_ION_GENERATION_ERROR_COUNT,

#endif
	
	EE_MAX
};

//void vInitialEEPROM(void);
#define vInitialEEPROM()	{ vMcuEepromCheckMagic(); }
void vMcuEepromCheckMagic(void);

BYTE bMcuEepromReadByte(BYTE baddr);
void vMcuEepromRealWrite(BYTE baddr,BYTE bdata);
void vMcuEepromWriteByte(BYTE baddr,BYTE bdata);



#else	//EEPROM_FUNCTION
#define vInitialEEPROM()
#define bMcuEepromReadByte(baddr)		0
#define vMcuEepromRealWrite(baddr, bdata)
#define vMcuEepromWriteByte(baddr,bdata)

#endif

#endif
