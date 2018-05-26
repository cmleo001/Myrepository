#ifndef _EVENTQUEUE_H_
#define _EVENTQUEUE_H_

#ifdef MIX_QUEUE_FUNCTION

extern BOOL fgMixQueuEmpty;
extern BOOL fgMixQueueFull;
extern BYTE bMixQueueRemain;
void vPutMixQueue(BYTE bData);
BYTE bGetMixQueue(void);
void vPutEventQueue(BYTE bEvent, BYTE bData1, BYTE bData2);
#define QUEUE_SIZE_EVENT	4
#define QUEUE_SIZE_EEPROM	3
#define QUEUE_SIZE_I2C		5
#define QUEUE_SIZE_I2C_INT		4
#define QUEUE_SIZE_PCI_EEPROM	3


#endif


#endif

