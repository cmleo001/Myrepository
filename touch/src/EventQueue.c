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
	//INT_DIS();
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
	//INT_EN();
	return bdata;
}

void vPutEventQueue(BYTE bEvent, BYTE bData1, BYTE bData2)
{
	if(bMixQueueRemain<QUEUE_SIZE_EVENT)
		return;
	//INT_DIS();	//130320ha01
#if 1
	vPutMixQueue(QUEUE_TYPE_EVENT);
	vPutMixQueue(bEvent);
	vPutMixQueue(bData1);
	vPutMixQueue(bData2);
#else
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
	bMixQueueRemain-=4;
#endif

	//INT_EN();	//130320ha01
}


void vMcuEepromWriteByte(BYTE baddr,BYTE bdata)
{
	if(bMixQueueRemain<QUEUE_SIZE_EEPROM)
		return;
	//INT_DIS();	//130320ha01
#if 1
	vPutMixQueue(QUEUE_TYPE_EEPROM);
	vPutMixQueue(baddr);
	vPutMixQueue(bdata);
#else
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
	bMixQueueRemain-=3;
#endif
	//INT_EN();	//130320ha01
}

void vPutI2CCommandQueue(BYTE bPara,BYTE bData1, BYTE bData2,BYTE bData3)//130309sh01
{
	if(bMixQueueRemain<QUEUE_SIZE_I2C)
		return;
	//INT_DIS();	//130320ha01
#if 1
	vPutMixQueue(QUEUE_TYPE_I2C);
	vPutMixQueue(bPara);
	vPutMixQueue(bData1);
	vPutMixQueue(bData2);
	vPutMixQueue(bData3);
#else
	bMixQueue[bMixQueueEndIndex]=QUEUE_TYPE_I2C;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;

	bMixQueue[bMixQueueEndIndex]=bPara;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
	
	bMixQueue[bMixQueueEndIndex]=bData1;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
	
	bMixQueue[bMixQueueEndIndex]=bData2;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
	
	bMixQueue[bMixQueueEndIndex]=bData3;
	bMixQueueEndIndex=(bMixQueueEndIndex+1)%MIX_QUEUE_MAX_NUMBER;
	
	fgMixQueuEmpty=FALSE;
	if(bMixQueueStartIndex==bMixQueueEndIndex)				
		{
		fgMixQueueFull=TRUE;
		}
	bMixQueueRemain-=5;
#endif
	//INT_EN();	//130320ha01
}











#endif


