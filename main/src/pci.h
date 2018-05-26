#ifndef _PCI_H_
#define _PCI_H_

#ifdef PCI_FUNCTION
#define PCI_TIME_READ_ERROR	0xFFFFFFFF
#define PCI_EEPROM_SLAVE_ADDR	0xA0
#define PCI_TIME_FOR_SERVICE_MODE	60000	//For service monitor mode transfer the PCI time(Hours)/1000, but the dPciTime unit is minute, so dPciTime/60=hours/1000==>service monitor need time.
extern BOOL fgPCIPowerOn;  //130329lo02
//130122bi01***
static DWORD dPciTime  @0x80;	// 130420lo01
static BYTE bpcitemp[3] @0x80;	// 130420lo01
void  vInitialPCI(void);
void vPCITimer1s(void);
void vPCIPowerOnReadAndCheckTime(void);
void vCheckPciUnit(void);
void vPCIWriteTimeAndCheckTime(void);
void vPCIWriteService(void);
void vPCICheckApprovedUnitCode(void);
void vPCIErrorProcess(void);
void vPCIWriteByte(BYTE baddr,BYTE bdata);

//130122bi01&&&
#else

#define  vInitialPCI()
#define vPCITimer1s()
#define vPCIPowerOnReadAndCheckTime()
#define vCheckPciUnit()
#define vPCIWriteTimeAndCheckTime()
#define vPCIWriteService()
#define vPCICheckApprovedUnitCode()
#define vPCIErrorProcess()
#define vPCIWriteByte(baddr,bdata)

#endif


#endif
