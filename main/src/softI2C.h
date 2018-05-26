#ifndef _SOFTI2C_H_
#define _SOFTI2C_H_

void vDelay4d7us(void);
#define vDelay4us()	vDelay4d7us()
#define vDelay5us()	vDelay4d7us()

#ifdef PCI_FUNCTION
//130128sh01***
BYTE fgEepromI2CWriteByte(BYTE bAddr,BYTE bData);
BYTE bEepromI2CReadByte(BYTE bAddr);
BYTE fgEepromCheckReady(void);
//130128sh01&&&
#else
#define fgEepromI2CWriteByte(bAddr,bData)
#define bEepromI2CReadByte(bAddr)
#define fgEepromCheckReady()
#endif

#endif //__SOFTI2C_H__
