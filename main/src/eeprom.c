#define _EEPROM_C_
#include "general.h"

#ifdef EEPROM_FUNCTION

//eeprom magic value
#define EEPROM_MAGIC_VALUE0 'E'
#define EEPROM_MAGIC_VALUE1 'I'


/**************************************************************  
Function:		static void vMcuEepromDefaultValueSet(void)
Description:	mcu eeprom set default value
Parameter:	none
Return:		none
***************************************************************/
static void vMcuEepromDefaultValueSet(void)
{
	BYTE i;
	//eeprom magic default value
	vMcuEepromRealWrite(EEPROM_MAGIC_ADDR0,EEPROM_MAGIC_VALUE0);
	vMcuEepromRealWrite(EEPROM_MAGIC_ADDR1,EEPROM_MAGIC_VALUE1);

	//default value
#ifdef TOUCH_MCU
	for(i=EE_CLEANING_FILTER_TIME_HOUR_LOW;i<=EE_POWER_MODE;i++)
		{
		vMcuEepromRealWrite(i,0);	//130430le01
		}
	
	vMcuEepromRealWrite(EE_AIR_VOLUME,AIR_VOLUME_DEFAULT_VALUE);
	vMcuEepromRealWrite(EE_OSCILLATE_MODE_ON_OFF,OSCILLATE_OFF);
	vMcuEepromRealWrite(EE_OSCILLATE_MODE_ANGLE,OSCILLATE_15D);
	vMcuEepromRealWrite(EE_LOUVER_MODE,LOUVER_STOP);
	vMcuEepromRealWrite(EE_LOUVER_ANGLE,LOUVER_HORIZONTAL_1);
#endif

#ifdef MAIN_MCU
	vMcuEepromRealWrite(EE_OSCILLATE_MODE_ON_OFF,OSCILLATE_OFF);
	vMcuEepromRealWrite(EE_OSCILLATE_MODE_ANGLE,OSCILLATE_15D);
	vMcuEepromRealWrite(EE_OSCILLATE_MEMORIZED_POSITION_LOW, HORIZONTAL_ANGLE_60_LOW);	//Oscillate memory position low 8 bit
	vMcuEepromRealWrite(EE_OSCILLATE_MEMORIZED_POSITION_HIGH,HORIZONTAL_ANGLE_60_HIGH);	//Oscillate memory position high 8 bit

	vMcuEepromRealWrite(EE_LOUVER_MEMORIZED_POSITION_LOW,VERTICAL_ANGLE_20_LOW);	//Louver memory position low 8 bit
	vMcuEepromRealWrite(EE_LOUVER_MEMORIZED_POSITION_HIGH,VERTICAL_ANGLE_20_HIGH);	//Louver memory position high 8 bit
	vMcuEepromRealWrite(EE_ION_GENERATION_ERROR_COUNT,0);	
#endif
}

/**************************************************************  
Function:		static void vMcuEepromCheckMagic(void)
Description:	mcu eeprom check magic
Parameter:	none
Return:		none
***************************************************************/
void vMcuEepromCheckMagic(void)
{
	if((bMcuEepromReadByte(EEPROM_MAGIC_ADDR0)!=EEPROM_MAGIC_VALUE0)||(bMcuEepromReadByte(EEPROM_MAGIC_ADDR1)!=EEPROM_MAGIC_VALUE1))
		{
		vMcuEepromDefaultValueSet();
		return;
		}
}


/**************************************************************  
Function:		void vInitialEEPROM(void)
Description:	initial mcu eeprom
Parameter:	none
Return:		none
***************************************************************/
/*	//130425Ja01
void vInitialEEPROM(void)
{
	vMcuEepromCheckMagic();		//check eeprom magic
}
*/	//130425Ja01

/**************************************************************  
Function:		BYTE bMcuEepromReadByte(BYTE addr)
Description:	read  BYTE data from the addr of mcu eeprom
Parameter:	addr which will be read int mcu eeprom
Return:		BYTE
***************************************************************/
BYTE bMcuEepromReadByte(BYTE baddr)
{
	BYTE bdata;
	EEPROM_POWER_OPERATE;
 	vEEPROMWriteAddress(baddr);
	EEPROM_READ_START;
	while(fgEEPROMReadCycleIsNotCompleted());	//check complete
	EEPROM_POWER_DOWN;
	bdata = bEEPROMReadData();
	return bdata;
}


/**************************************************************  
Function:		void vMcuEepromRealWrite(BYTE addr,BYTE data)
Description:	write BYTE data to the addr of Mcu Eeprom
Parameter:	data/addr is the data/addr which will be writen
Return:		none
***************************************************************/

void vMcuEepromRealWrite(BYTE baddr,BYTE bdata)
{
	while(fgEEPROMWriteCycleIsNotCompleted());	//idle	
	EEPROM_POWER_OPERATE;
  	EEPROM_WRITE_ENABLE;
 	vEEPROMWriteAddress(baddr);
	vEEPROMWriteData(bdata);
	EEPROM_WRITE_START;
}



#endif

