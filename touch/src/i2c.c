#define _I2C_C_
#include "general.h"

#ifdef I2C_HARDWARE_FUNCTION
//130126sh01***
BYTE bI2CReadBuffer[4];	//Read from I2C put in here.
BYTE bI2CWriteBuffer[4];	
BYTE bI2CWriteIndex;
BYTE bI2CReadIndex;
BYTE bI2CWriteLength;
BYTE bI2CReadLength;
BYTE bI2CSlaveAddress;
BYTE bI2CCommand;
BYTE bI2CSendChecksum=0;
//BYTE bI2cData2;	//Register address Hi to bI2cData2 //130417gr01
BYTE bI2cData3;	//Register address Lo to bI2cData3
//BYTE bTouchRegAddHi; //130417gr01
BYTE bTouchRegAddLo;

BOOL fgI2CCommandBusy=FALSE;

//BYTE bTouchErrorCount=0;//130309sh02//130403sh01
//#define TOUCH_COMMUNICATION_ERROR_COUNT	5	//130309sh02//130403sh01
#define I2C_NO_ACK_RETRANSFER_COUNT	3
#define I2C_CHECKSUM_WRONG_COUNT	5

#if 0//130309sh01***
void vSetupI2CStartTransfer(BYTE bI2CSlaveAddress)
{	
	I2C_TX_INT_EN;
	I2C_SLAVE_ADDRESS = bI2CSlaveAddress;
	I2C_START_SEND_SCL_CLOCK;
}
void vSetupI2CStartReceive(BYTE bI2CSlaveAddress)
{
	I2C_SLAVE_ADDRESS = bI2CSlaveAddress|1;
	I2C_START_SEND_SCL_CLOCK;
}
#endif
void vSetupI2CStart(BYTE bI2CSlaveAddress)
{	
	I2C_TX_INT_EN;
	I2C_SLAVE_ADDRESS = bI2CSlaveAddress;
	I2C_START_SEND_SCL_CLOCK;
}//130309sh01&&&

//void vI2cSendCommand(BYTE bPara,BYTE bData1, BYTE bData2,BYTE bData3)//130309sh01
//{
//	vPutI2CCommandQueue(bPara,bData1,bData2,bData3);//130309sh01
	//vCheckI2CCommandQueue();
//}

void vI2CWriteCommand(BYTE bPara,BYTE bData1,BYTE bData2,BYTE bData3)//130309sh01
{
	bI2CSlaveAddress=SLAVE_ADDRESS_MAIN_MCU;
	bI2CCommand=bPara;
	bI2CSendChecksum=0;
	bI2CWriteBuffer[0]=bData1;
	bI2CWriteBuffer[1]=bData2;
	bI2CWriteBuffer[2]=bData3;
	//bI2CWriteBuffer[3]=bData4;//130309sh01
	switch(bI2CCommand)
		{
		case I2C_WRITE_TO_MAIN_MCU:
			bI2CWriteLength=3;//command+writedata+checksum
			bI2CReadLength=1;//checksum
			bI2CWriteBuffer[2]=~(bI2CWriteBuffer[0]+bI2CWriteBuffer[1]);
			bI2CSendChecksum=bI2CWriteBuffer[2];
			break;
		case I2C_READ_INT_FROM_MAIN_MCU:
			bI2CWriteLength=2;//0xff+checksum
			bI2CReadLength=4;//intcommand+2data+checksum
			break;
		case I2C_WRITE_TO_TOUCH:
			bI2CSlaveAddress=SLAVE_ADDRESS_TOUCH_IC;
			bI2CWriteLength=4;
			bI2CReadLength=0;
			bI2CWriteBuffer[0]=0x00;//130309sh01***
			bI2CWriteBuffer[1]=bData1;
			bI2CWriteBuffer[2]=bData2;
			bI2CWriteBuffer[3]=bData3;//130309sh01&&&
			break;
		case I2C_READ_FROM_TOUCH:
			bI2CSlaveAddress=SLAVE_ADDRESS_TOUCH_IC;
			bI2CWriteLength=2;
			bI2CReadLength=2;
			//bTouchRegAddHi=bData1; //130417gr01
			bTouchRegAddLo=bData2;
			break;
		default://130302sh01
			fgI2CCommandBusy=FALSE;
			vPinI2cBusyDisable();//130315sh01
			return;//130302sh01
		}
	bI2CWriteIndex=0;
	bI2CReadIndex=0;
	//vSetupI2CStartTransfer(bI2CSlaveAddress);//130309sh01
	vSetupI2CStart(bI2CSlaveAddress);//130309sh01
}


/////////////////////////////////////
//I2C interrupt
/////////////////////////////////////
void vISR_I2CTransmit(void)
{
	static BYTE bI2CNoAckRetransferCount=0;
	//INT_DIS();	//130320ha01
	I2CTIF = 0;
	if(I2C_ACK==0)//slave no respond
		{
		I2C_TX_INT_DIS;
		//I2C_STOP_STATUS = 1;//130403sh01 //no need to set STOP=1,when no ack, stop automatically
		bI2CNoAckRetransferCount++;
		if(bI2CNoAckRetransferCount<=I2C_NO_ACK_RETRANSFER_COUNT)
			{
			if(bI2CCommand==I2C_WRITE_TO_TOUCH)//130402sh02***
				{
				vI2CWriteCommand(bI2CCommand,bI2CWriteBuffer[1],bI2CWriteBuffer[2],bI2CWriteBuffer[3]);
				}
			else//130402sh02&&&
				{
				vI2CWriteCommand(bI2CCommand,bI2CWriteBuffer[0],bI2CWriteBuffer[1],bI2CWriteBuffer[2]);//retransfer//130309sh01;
				}
			}
		else//130302sh01
			{
			bI2CNoAckRetransferCount=0;//retransfer 3 times,still no ack,then send the next I2C command
			fgI2CCommandBusy=FALSE;//130311sh02
			vPinI2cBusyDisable();//130315sh01
			vPutEventQueue(COMMAND_MAIN_SUB_ERROR,ERROR_COMMUNICATION_WITH_TOUCH, TRUE);//130403sh01// communicaton error
			}
#if 0	//130403sh01
		if((fgIsInPowerOnMode()||fgIsInWatchMode())&&(bI2CSlaveAddress==SLAVE_ADDRESS_TOUCH_IC))//130309sh02***
			{
			bTouchErrorCount++;
			if(bTouchErrorCount>=TOUCH_COMMUNICATION_ERROR_COUNT)
				{
				bTouchErrorCount=0;
				vPutEventQueue(EVENT_COMMUNICATE_WITH_TOUCH_ERROR, TRUE, 0);
				//INT_EN();	//  Before initial the interrupt is disable.	//130320ha01
				//RETI();	//130320ha01
				goto END;
				}
			}//130309sh02&&&
#endif	//130403sh01
		//fgI2CCommandBusy=FALSE;//130311sh02
		//vCheckI2CCommandQueue();//130302sh01
		//INT_EN();	//  Before initial the interrupt is disable.	//130320ha01
		//RETI();	//130320ha01
		goto END;
		}
	//if(bI2CSlaveAddress==SLAVE_ADDRESS_MAIN_MCU)//main mcu answer ACK,then reset bI2CNoAckRetransferCount to 0//130302sh01***//130403sh01
		{
		bI2CNoAckRetransferCount=0;
		}//130302sh01&&&
#if 0//130403sh01
	if(bI2CSlaveAddress==SLAVE_ADDRESS_TOUCH_IC)//130309sh02***
		{
		bTouchErrorCount=0;
		}//130309sh02&&&
#endif//130403sh01
	if(bI2CWriteIndex<bI2CWriteLength)	
		{
		bI2CWriteIndex++;
		if(bI2CWriteIndex==bI2CWriteLength)
			{
			I2C_MASTER_STOP;
			}
		I2C_DATA_BUFFER=bI2CWriteBuffer[bI2CWriteIndex-1];
		I2C_START_SEND_SCL_CLOCK;
		}	
	else if(bI2CWriteIndex==bI2CWriteLength)
		{
#if 0//130311sh01***
		if(bI2CReadLength)	
			{
			switch(bI2CCommand)
				{
				case I2C_WRITE_TO_MAIN_MCU:
				case I2C_READ_INT_FROM_MAIN_MCU:
					//vSetupI2CStartReceive(SLAVE_ADDRESS_MAIN_MCU);//130309sh01
					vSetupI2CStart(SLAVE_ADDRESS_MAIN_MCU|1);//130309sh01
					break;
				case I2C_READ_FROM_TOUCH:
					//vSetupI2CStartReceive(SLAVE_ADDRESS_TOUCH_IC);//130309sh01
					vSetupI2CStart(SLAVE_ADDRESS_TOUCH_IC|1);//130309sh01
					break;
				default:
					break;
				}
			bI2CWriteIndex++;
			}
		else
			{
			I2C_TX_INT_DIS;
			fgI2CCommandBusy=FALSE;
			//vCheckI2CCommandQueue();//130302sh01
			}
#endif
		if(bI2CReadLength==0)
			{
			I2C_TX_INT_DIS;
			fgI2CCommandBusy=FALSE;
			vPinI2cBusyDisable();//130315sh01
			}
		else
			{
			bI2CWriteIndex++;
#if 0//130415sh01
			switch(bI2CCommand)
				{
				case I2C_WRITE_TO_MAIN_MCU:
				case I2C_READ_INT_FROM_MAIN_MCU:
					//vSetupI2CStartReceive(SLAVE_ADDRESS_MAIN_MCU);//130309sh01
					vSetupI2CStart(SLAVE_ADDRESS_MAIN_MCU|1);//130309sh01
					break;
				case I2C_READ_FROM_TOUCH:
					//vSetupI2CStartReceive(SLAVE_ADDRESS_TOUCH_IC);//130309sh01
					vSetupI2CStart(SLAVE_ADDRESS_TOUCH_IC|1);//130309sh01
					break;
				default:
					break;
				}
#else//130415sh01
			vSetupI2CStart(bI2CSlaveAddress|1);
#endif//130415sh01
			}//130311sh01&&&
		}
	else if(bI2CWriteIndex==bI2CWriteLength+1)//the interrupt after send the read slaveaddress
		{
		I2C_TX_INT_DIS;
		I2C_RX_INT_EN;
		if(bI2CReadLength==1)
			{
			I2C_MASTER_STOP;
			}
		I2C_START_SEND_SCL_CLOCK;//read back the first byte
		}
	//INT_EN();	//  Before initial the interrupt is disable.	//130320ha01
END:
	RETI();
}

void vISR_I2CReceive(void)
{
	static BYTE bI2CWriteRetransferCount=0;
	//INT_DIS();	//130320ha01
	I2CRIF=0;
	bI2CReadIndex++;//130311sh01
	bI2CReadBuffer[bI2CReadIndex-1]=I2C_DATA_BUFFER;//130311sh01
	//bI2CReadIndex++;//130311sh01
	if(bI2CReadIndex==(bI2CReadLength-1))
		{
		I2C_MASTER_STOP;
		}
	
	if(bI2CReadIndex<bI2CReadLength)
		{
		I2C_START_SEND_SCL_CLOCK;
		}
	else if(bI2CReadIndex==bI2CReadLength)
		{
		I2C_RX_INT_DIS;
		switch(bI2CCommand)
			{
			case I2C_WRITE_TO_MAIN_MCU:
				if(bI2CSendChecksum!=bI2CReadBuffer[0])//checksum wrong
					{
#if 0//130415sh01
					bI2CWriteRetransferCount++;
					if(bI2CWriteRetransferCount<=I2C_CHECKSUM_WRONG_COUNT)
						{
						vI2CWriteCommand(bI2CCommand,bI2CWriteBuffer[0],bI2CWriteBuffer[1],bI2CWriteBuffer[2]);//retransfer
						//INT_EN();	//  Before initial the interrupt is disable.	//130320ha01
						//RETI();//130311sh02	//130320ha01
						goto END;
						}
					else
						{	//Abort this command.
						bI2CWriteRetransferCount=0;
						}
#else//130415sh01***
					goto CHECKSUM_WRONG_PROCESS;
#endif//130415sh01&&&
					}
				else
					{
					bI2CWriteRetransferCount=0;
					}
				break;
			 case I2C_READ_INT_FROM_MAIN_MCU://one command + two data
			 	if(bI2CReadBuffer[3]+bI2CReadBuffer[2]+bI2CReadBuffer[0]+bI2CReadBuffer[1] ==0xff)//checksum right
			 		{
					vPutEventQueue(bI2CReadBuffer[0],bI2CReadBuffer[1],bI2CReadBuffer[2]);
					bI2CWriteRetransferCount=0;//130415sh01
			 		}
				else//checksum wrong//130315sh01***
					{
#if 0//130415sh01
					bI2CWriteRetransferCount++;
					if(bI2CWriteRetransferCount<=I2C_CHECKSUM_WRONG_COUNT)
						{
						vI2CWriteCommand((BYTE)I2C_READ_INT_FROM_MAIN_MCU,(BYTE)COMMAND_SUB_MAIN_REQUEST_INT_VALUE,(BYTE)(~COMMAND_SUB_MAIN_REQUEST_INT_VALUE),0);
						//INT_EN();	//130320ha01
						//RETI();
						goto END;
						}
					else
						{
						bI2CWriteRetransferCount=0;
						}
#else//130415sh01***
				goto CHECKSUM_WRONG_PROCESS;
#endif//130415sh01&&&
					}//130315sh01&&&
				break;
			 case I2C_READ_FROM_TOUCH:
			 	//bI2cData2=bTouchRegAddHi;	//Register address Hi to bI2cData2//130408sh01***
				//bI2cData3=bTouchRegAddLo;	//Register address Lo to bI2cData3
				vPutEventQueue(EVENT_TOUCH_READ_REGISTER_ADDRESS, bTouchRegAddLo,0);//130408sh01&&& //130417gr01
 				vPutEventQueue(EVENT_TOUCH_READ, bI2CReadBuffer[0],bI2CReadBuffer[1]);
				break;
			 default:
				break;
			}
		fgI2CCommandBusy=FALSE;
		vPinI2cBusyDisable();//130315sh01
		//vCheckI2CCommandQueue();
 		}
	//INT_EN();               //  Before initial the interrupt is disable.	//130320ha01
END:
	RETI();
CHECKSUM_WRONG_PROCESS://130415sh01***
	bI2CWriteRetransferCount++;
	if(bI2CWriteRetransferCount<=I2C_CHECKSUM_WRONG_COUNT)
		{
		vI2CWriteCommand(bI2CCommand,bI2CWriteBuffer[0],bI2CWriteBuffer[1],bI2CWriteBuffer[2]);//retransfer
		//INT_EN();	//  Before initial the interrupt is disable.	//130320ha01
		//RETI();//130311sh02	//130320ha01
		}
	else
		{	//Abort this command.
		bI2CWriteRetransferCount=0;
		fgI2CCommandBusy=FALSE;
		vPinI2cBusyDisable();//130315sh01
		}
	RETI();//130415sh01&&&
}
#if 0//130415sh01
void vISR_I2CStop(void)
{
	I2CSTPIF=0;
	RETI();
}
#endif//130415sh01
void vInitialI2C(void)
{
	I2CTIF = 0;
	I2CRIF=0;
	I2C_MODE;
	I2C_STANDARD_MODE;
	I2C_FAST_CLOCK_FM_8;	//100kHz
	I2C_MASTER_MODE;
	I2C_ENABLE;		
}
//130126sh01&&&
//130315Li01***
#if 0
void vPutI2CCommandQueue(BYTE bPara,BYTE bData1, BYTE bData2,BYTE bData3)//130309sh01
{
	if(bMixQueueRemain<5)
		return;
	//INT_DIS();	//130320ha01
	vPutMixQueue(QUEUE_TYPE_I2C);
	vPutMixQueue(bPara);
	vPutMixQueue(bData1);
	vPutMixQueue(bData2);
	vPutMixQueue(bData3);
	//INT_EN();	//130320ha01
}
#endif
#if 0//130415sh01
void vI2cSendCommandBuzzer(BYTE bBuzzer_Type)
{
	vPutI2CCommandQueue(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_BUZZER_MODE,bBuzzer_Type,0);
}
#endif//130415sh01
void vI2cSendCommand1Para(BYTE bData1)
{
	vPutI2CCommandQueue(I2C_WRITE_TO_MAIN_MCU,bData1,0,0);
}
void vI2cSendCommand2Para(BYTE bData1,BYTE bData2)
{
	vPutI2CCommandQueue(I2C_WRITE_TO_MAIN_MCU,bData1,bData2,0);
}
//130315Li01&&&

void vTouchICReadCommand(BYTE bAddrHigh,BYTE bAddrLow)//130419gr01***
{
vI2cSendCommand(I2C_READ_FROM_TOUCH,bAddrHigh,bAddrLow, 0 );
}//130419gr01&&&


#endif
