#define _EVENTQUEUE_C_

#include "general.h"


#ifdef MIX_QUEUE_FUNCTION
BYTE bMixQueue[MIX_QUEUE_MAX_NUMBER];
BOOL fgMixQueuEmpty=TRUE;
BOOL fgMixQueueFull=FALSE;
BYTE bMixQueueEndIndex=0;
BYTE bMixQueueStartIndex=0;
BYTE bMixQueueRemain=MIX_QUEUE_MAX_NUMBER;
void vPutMixQueue(BYTE bData)
{
	if(!fgMixQueueFull)
		{
		bMixQueue[bMixQueueEndIndex]=bData;
		bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
		fgMixQueuEmpty=FALSE;
		if(bMixQueueStartIndex==bMixQueueEndIndex)				
			{
			fgMixQueueFull=TRUE;
			}
		bMixQueueRemain--;
		}
}

BYTE bGetMixQueue(void)
{
	BYTE bdata=0xFF;
	INT_DIS();
	if(!fgMixQueuEmpty)
		{
		bdata=bMixQueue[bMixQueueStartIndex];
		bMixQueueStartIndex=(bMixQueueStartIndex+1)%MIX_QUEUE_MAX_NUMBER;
		fgMixQueueFull=FALSE;  
		
		if(bMixQueueStartIndex==bMixQueueEndIndex)
			{
			fgMixQueuEmpty=TRUE;
			}
		bMixQueueRemain++;
		}
	//INT_EN();//130326sh01
	return bdata;
}

void vPutEventQueue(BYTE bEvent, BYTE bData1, BYTE bData2)
{
	if(bMixQueueRemain<QUEUE_SIZE_EVENT)
		return;
	INT_DIS();	//130320ha01
	
//	vPutMixQueue(QUEUE_TYPE_EVENT);
//	vPutMixQueue(bEvent);
//	vPutMixQueue(bData1);
//	vPutMixQueue(bData2);
	
	bMixQueue[bMixQueueEndIndex]=QUEUE_TYPE_EVENT;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;

	bMixQueue[bMixQueueEndIndex]=bEvent;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
	
	bMixQueue[bMixQueueEndIndex]=bData1;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
	
	bMixQueue[bMixQueueEndIndex]=bData2;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
	
	fgMixQueuEmpty=FALSE;
	if(bMixQueueStartIndex==bMixQueueEndIndex)				
		{
		fgMixQueueFull=TRUE;
		}
	bMixQueueRemain-=QUEUE_SIZE_EVENT;

//	INT_EN();	//130320ha01
}

void vMcuEepromWriteByte(BYTE baddr,BYTE bdata)
{
	//vPutEEPROMQueue(baddr,bdata);
	if(bMixQueueRemain<QUEUE_SIZE_EEPROM)
		return;
	INT_DIS();	//130320ha01

//	vPutMixQueue(QUEUE_TYPE_EEPROM);
//	vPutMixQueue(baddr);
//	vPutMixQueue(bdata);

	bMixQueue[bMixQueueEndIndex]=QUEUE_TYPE_EEPROM;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;

	bMixQueue[bMixQueueEndIndex]=baddr;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
	
	bMixQueue[bMixQueueEndIndex]=bdata;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
	
	fgMixQueuEmpty=FALSE;
	if(bMixQueueStartIndex==bMixQueueEndIndex)				
		{
		fgMixQueueFull=TRUE;
		}
	bMixQueueRemain-=QUEUE_SIZE_EEPROM;

//	INT_EN();	//130320ha01
}

void vIntDataQueuePut(BYTE bIntCommand, BYTE bIntData1, BYTE bIntData2)	
{	
	if(bMixQueueRemain<QUEUE_SIZE_I2C_INT)
		return;
	INT_DIS();	//130320ha01
	
//	vPutMixQueue(QUEUE_TYPE_I2C);
//	vPutMixQueue(bIntCommand);
//	vPutMixQueue(bIntData1);
//	vPutMixQueue(bIntData2);

	bMixQueue[bMixQueueEndIndex]=QUEUE_TYPE_I2C;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;

	bMixQueue[bMixQueueEndIndex]=bIntCommand;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
	
	bMixQueue[bMixQueueEndIndex]=bIntData1;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
	
	bMixQueue[bMixQueueEndIndex]=bIntData2;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
	
	fgMixQueuEmpty=FALSE;
	if(bMixQueueStartIndex==bMixQueueEndIndex)				
		{
		fgMixQueueFull=TRUE;
		}
	bMixQueueRemain-=QUEUE_SIZE_I2C_INT;

	
//	INT_EN();	//130320ha01
}

void vPCIWriteByte(BYTE baddr,BYTE bdata)
{
	if(bMixQueueRemain<QUEUE_SIZE_PCI_EEPROM)
		{
		return;
		}
	INT_DIS();	//130320ha01

//	vPutMixQueue(QUEUE_TYPE_PCI_EEPROM);
//	vPutMixQueue(baddr);
//	vPutMixQueue(bdata);

	bMixQueue[bMixQueueEndIndex]=QUEUE_TYPE_PCI_EEPROM;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;

	bMixQueue[bMixQueueEndIndex]=baddr;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
	
	bMixQueue[bMixQueueEndIndex]=bdata;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
	
	fgMixQueuEmpty=FALSE;
	if(bMixQueueStartIndex==bMixQueueEndIndex)				
		{
		fgMixQueueFull=TRUE;
		}
	bMixQueueRemain-=QUEUE_SIZE_PCI_EEPROM;

//	INT_EN();	//130320ha01

}


#endif


