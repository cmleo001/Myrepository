#define _SOFTI2C_C_

#include "general.h"

//130128sh01***
//System clock = 8MHz, 1 clock cycle=125ns, 1 instruction cycle=250ns
//Jump , Call , Ret, Reti instruction need 2 instruction cycle=500ns.
//NOP()*16*250ns + Call*500ns + ret*500ns=5000ns=5us
void vDelay4d7us(void)
{
	NOP();	// 250ns
	NOP();
	NOP();
	NOP();	// 1us
	NOP();
	NOP();
	NOP();
	NOP();	// 2us
	NOP();
	NOP();
	NOP();
	NOP();	// 3us
	NOP();
	NOP();
	NOP();
	NOP();	// 4us
}

#ifdef PCI_FUNCTION
void vSoftI2CWriteByte(BYTE bData)
{
	BYTE bloop;
	PIN_SDA_IO_OUTPUT;
	for(bloop=0x80; bloop>=1; bloop>>=1)
		{
		if(bData & bloop)
			{
			vSDAHigh();
			}
		else
			{
			vSDALow();
			}
		vSCLHigh();
		//delay Thigh=1us//SCL high time
		//NOP();			// 130311lo01***
		//NOP();			
		//NOP();			
		vDelay4d7us();    // 130311lo01&&&
		vSCLLow();
		}
}

BYTE fgSoftI2CReadAck(void)
{	
	BOOL fgSoftI2CAck=0;
	PIN_SDA_IO_INPUT;
	vSCLHigh();
	//NOP();				// 130311lo01***
	//NOP();
	vDelay4d7us();		 // 130311lo01&&&
	fgSoftI2CAck=PIN_SDA_READ;
	vSCLLow();
	return fgSoftI2CAck;
}
BYTE bSoftI2CReadByte(void)
{
	BYTE bI2CReadData=0;
	BYTE bloop;
	PIN_SDA_IO_INPUT;
	for(bloop=0; bloop<8; bloop++)
		{
		//NOP();	//delay Tlow=1us//SCL low time
		vDelay4d7us();
		vSCLHigh();
		bI2CReadData <<=1;
		if(PIN_SDA_READ)
			{
			bI2CReadData|=0x01;
			}
		vDelay4d7us();		 // 130311lo01
		vSCLLow();
		}
	return bI2CReadData;
}

void vSoftI2CSendAck(void)
{
	PIN_SDA_IO_OUTPUT;
	vSDALow();
	vSCLHigh();
	vDelay4us();
	vSCLLow();
}

void vSoftI2CSendLastAck(void)
{
	PIN_SDA_IO_OUTPUT;
	vSDAHigh();
	vSCLHigh();
	vDelay4us();		
	vSCLLow();
}
void vSoftI2CStart(void)
{
	PIN_SDA_IO_OUTPUT;
	vSDAHigh();
	vSCLHigh();
	//delay Tsu.sta=0.6us//start condition setup time
	//NOP();					// 130311lo01***
	//NOP();
	vDelay4d7us();
	vSDALow();
	//delay Thd.sta=0.6us//start condition hold time
	//NOP();
	//NOP();
	vDelay4d7us();			 // 130311lo01&&&
	vSCLLow();
}

void vSoftI2CStop(void)
{
	PIN_SDA_IO_OUTPUT;
	vSDALow();
	vSCLHigh();
	//delay Tsu.sto=0.6us//stop condition setup time
	//NOP();					// 130311lo01***
	//NOP();
	vDelay4d7us();			 // 130311lo01&&&
	vSDAHigh();
}

BYTE fgEepromI2CWriteByte(BYTE bAddr,BYTE bData)
{
	vSoftI2CStart();
	vSoftI2CWriteByte(PCI_EEPROM_SLAVE_ADDR);
	if(fgSoftI2CReadAck())
		{
		vSoftI2CStop();
		return RESULT_FAIL;
		}
	vSoftI2CWriteByte(bAddr);
	if(fgSoftI2CReadAck())
		{
		vSoftI2CStop();
		return RESULT_FAIL;
		}
	vSoftI2CWriteByte(bData);
	if(fgSoftI2CReadAck())
		{
		vSoftI2CStop();
		return RESULT_FAIL;
		}
	vSoftI2CStop();
	return RESULT_SUCCESS;
}

BYTE fgEepromCheckReady(void)
{
	vSoftI2CStart();
	vSoftI2CWriteByte(PCI_EEPROM_SLAVE_ADDR);
	if(fgSoftI2CReadAck())
		{
		vSoftI2CStop();
		return FALSE;
		}
	vSoftI2CStop();
	return TRUE;
}

BYTE bEepromI2CReadByte(BYTE bAddr)
{
	BYTE bReadData;
	vSoftI2CStart();
	vSoftI2CWriteByte(PCI_EEPROM_SLAVE_ADDR);
	if(fgSoftI2CReadAck())
		{
		vSoftI2CStop();
		return 0xFF;
		}
	vSoftI2CWriteByte(bAddr);
	if(fgSoftI2CReadAck())
		{
		vSoftI2CStop();
		return 0xFF;
		}
	vSoftI2CStop();
	
	vSoftI2CStart();
	vSoftI2CWriteByte(PCI_EEPROM_SLAVE_ADDR|0x01);
	if(fgSoftI2CReadAck())
		{
		vSoftI2CStop();
		return 0xFF;
		}
	bReadData=bSoftI2CReadByte();
	vSoftI2CSendLastAck();
	vSoftI2CStop();
	return bReadData;
}
//130128sh01&&&
#endif





