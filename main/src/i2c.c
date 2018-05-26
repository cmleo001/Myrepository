#define _I2C_C_
#include "general.h"

BOOL fgI2CIntBusy=FALSE;
BYTE fgI2CIntTransferOver=TRUE;	//130328sh01
#ifdef I2C_HARDWARE_FUNCTION
//130126sh01***
BYTE bI2CReceiveCnt=0;
BYTE bI2CSendCnt=0;
BYTE bI2CSendCntMax;
BYTE bI2CCheckSum=0;
BYTE bReceivedCommand;
BYTE bReceivedData;
BYTE bI2CSendBuffer[4];	// 1command+2data+1checksum
BYTE bI2CIntRetransferCount=I2C_INT_RETRANSFER_COUNT_MAX;	// 1ms count once.//130418sh01
void vISR_I2CTransmit(void)
{
	//INT_DIS();	//130320ha01
	I2CTIF=0;
#if 0//130302sh01***	
	if(bI2CSendCnt>=bI2CSendCntMax)
		{
		I2C_SLAVE_RETURN_NACK;
		}
#endif//130302sh01&&&
#if 0//130311sh04***
	I2C_DATA_BUFFER=bI2CSendBuffer[bI2CSendCnt];
	I2C_PENDING_SIGNAL;
	bI2CSendCnt++;
	
	if((bReceivedCommand==COMMAND_SUB_MAIN_REQUEST_INT_VALUE)&&(bI2CSendCnt==bI2CSendCntMax))		//all int data is send 
		{
		fgI2CIntBusy=FALSE;
		}
#endif
	if(bI2CSendCnt==bI2CSendCntMax)
		{
		#if 0//130315sh01***
		if(bReceivedCommand==COMMAND_SUB_MAIN_REQUEST_INT_VALUE)
			{
			fgI2CIntBusy=FALSE;
			}
		#endif//130315sh01&&&
		//I2C_PENDING_SIGNAL;
		//INT_EN();               //  Before initial the interrupt is disable.	//130320ha01
		//RETI();	//130320ha01
		goto END;	//130320ha01
		}
	bI2CSendCnt++;
	if(bReceivedCommand==COMMAND_SUB_MAIN_REQUEST_INT_VALUE)//130326sh01***
		{
		I2C_DATA_BUFFER=bI2CSendBuffer[bI2CSendCnt-1];
		}
	else
		{
		I2C_DATA_BUFFER=bI2CCheckSum;
		bI2CCheckSum=0;
		}//130326sh01&&&
END:
	I2C_PENDING_SIGNAL;	//130311sh04&&&
	//INT_EN();               //  Before initial the interrupt is disable.	//130320ha01
	RETI();
}

void vISR_I2CReceive(void)
{
	BYTE bI2CReceiveData;
	//INT_DIS();	//130320ha01
	I2CRIF=0;

	bI2CReceiveCnt++;
	bI2CReceiveData=I2C_DATA_BUFFER;
	switch(bI2CReceiveCnt)
		{
		case 1://slave address
			bI2CCheckSum=0;
			break;
		case 2://command
			bReceivedCommand=bI2CReceiveData;
			bI2CCheckSum+=bReceivedCommand;
			break;
		case 3://data
			if(bReceivedCommand==COMMAND_SUB_MAIN_REQUEST_INT_VALUE)
				{
				if(~bI2CCheckSum==bI2CReceiveData)
					{	//checksum correct.
					//bI2CSendCnt=0;
					bI2CSendCntMax=4;
					vOTPIntDis();
					fgI2CIntTransferOver=TRUE;//130328sh01
					bI2CIntRetransferCount=I2C_INT_RETRANSFER_COUNT_MAX;//130418sh01
					}
				else
					{	//checksum error.
					}
				break;
				}
			
			bReceivedData=bI2CReceiveData;	
			bI2CCheckSum+=bReceivedData;
			bI2CCheckSum=~bI2CCheckSum;
			break;
		case 4://checksum
			if(bI2CCheckSum==bI2CReceiveData)//checksum right
				{
				vPutEventQueue(bReceivedCommand,bReceivedData,0);
				}
			else//checksum wrong//130315sh01***
				{
				bI2CCheckSum=~bI2CCheckSum;//answer the wrong checksum
				}//130315sh01&&&
			//bI2CSendBuffer[0]=bI2CCheckSum;//130326sh01
			//bI2CCheckSum=0;//130326sh01
			bI2CSendCnt=0;
			bI2CReceiveCnt=0;
			bI2CSendCntMax=1;
			break;
		}
	I2C_PENDING_SIGNAL;
	//INT_EN();               //  Before initial the interrupt is disable.	//130320ha01
	RETI();
}

void vISR_I2CStop(void)
{
	I2CSTPIF=0;
	bI2CReceiveCnt=0;
	bI2CSendCnt=0;
	RETI();
}

#if 0
void vIntDataQueuePut(BYTE bIntCommand, BYTE bIntData1, BYTE bIntData2)	
{	
	if(bMixQueueRemain<4)
		return;
	INT_DIS();	//130320ha01
	vPutMixQueue(QUEUE_TYPE_I2C);
	vPutMixQueue(bIntCommand);
	vPutMixQueue(bIntData1);
	vPutMixQueue(bIntData2);
	INT_EN();	//130320ha01
}
#endif


void vInitialI2C(void)
{
	I2C_MODE; 	// Select i2c mode
	I2C_STANDARD_MODE;		//standard mode
	I2C_FAST_CLOCK_FM_8;	//choose 100khz 
	I2C_SLAVE_MODE;		// Slave mode
	I2CDA = (SLAVE_ADDRESS_MAIN_MCU>>1);	// Slave address 0xa0
	I2CA = 0;
	I2C_RX_INT_EN;//receive int enable
	I2C_TX_INT_EN;//transfer int enable
	I2C_SLAVE_RECE_DATA_STOP_INT_EN;//stop int enable
	I2C_ENABLE;// Enable I2C
}
#endif
