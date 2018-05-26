#define _PCI_C_
#include "general.h"

#ifdef PCI_FUNCTION
//130125bin01***

//Address is 0X10, 0001 0000, for marking the public queue data is PCI data,
//so change the highest bit is 1. The address become to 1001 0000, 0x90.
#define PCI_TIME_DEFAULT_ADDR	0x10

#define PCI_TIME_BACKUP_ADDR	0x60

#define PCI_TIME_LENGTH		8
#define PCI_TIME_19000H			1140000	//1140000=19000*60min	// 130420lo01
#define PCI_TIME_17500H			1050000	//1050000=17500*60min	// 130420lo01
#define PCI_APPROVED_UNIT_CODE_DATA			0xAA
#define PCI_APPROVED_UNIT_CODE_ADDR			0x7E
#define PCI_CHECK_AA_RETRY_TIMES		3
#define PCI_CHECK_NONE_RETRY_TIMES	16
#define PCI_30MIN		1800	// 1800second=0.5hour
#define PCI_1MIN        60                // 130312lo01
#define PCI_QUEUE_MAX_NUMBER		5   // 130307lo01***

BOOL fgPCIPowerOn=FALSE;
BOOL fgRunPCIAdd30MinAndCheckTime=FALSE;		// 130316lo01***
BOOL fgPciTime17500HStatus=FALSE;  //130423lo01
BOOL fgPciTime19000HStatus=FALSE;  //130423lo01

BYTE bPciCheckNoneRetryCount=0;
//BYTE bPciTimeQuotientMin;		//130423lo01
BYTE bPciError=PCI_ERROR_NONE;
BYTE bPciTimerCountSec=0;  		//130423lo01	
BYTE bPciTimerCountMin=0;   	//130423lo01
//WORD wPciTimerCount=PCI_30MIN;		//130423lo01
		

///////////////////////////////////////////////////////////////////
//Function:		void vPCIErrorProcess(void)
//Description:	Write PCI Error process;
//Parameter:	None
//Return:		None
///////////////////////////////////////////////////////////////////
void vPCIErrorProcess(void)
{
	if(bPciError==PCI_ERROR_NONE)
		return;

	switch(bPciError)	
		{
		case PCI_ERROR_TIME_17500H:
			{
			if((bSpecialFunctionMode!=MODE_MONITOR)&&(bSpecialFunctionMode!=MODE_SERVICE_MONITOR))  //130425lo01***
				{
				vIntPciCriticalStatusError(TRUE);	// 130309lo03
				}
			}
			break;
		case PCI_ERROR_TIME_19000H:
			{
			if((bSpecialFunctionMode!=MODE_MONITOR)&&(bSpecialFunctionMode!=MODE_SERVICE_MONITOR)) 
				{
				vIntPciOverTimeStatusError(TRUE);    // 130309lo04
				vPCIPowerOff();
				fgPCIPowerOn=FALSE;
				fgIonGenerationJudgmentControl=FALSE;
				}	//130425lo01&&&
			}
			break;
		case PCI_ERROR_CONNECTION:			// 130309lo02***
			{
			vIntMainMCUError(ERROR_PCI_UNIT_CONNECTION, TRUE);	//130322lo01
			}
			break;
		case PCI_ERROR_DATA:
			{ 
			vIntMainMCUError(ERROR_PCI_UNIT_DATA, TRUE);
			}
			break;							// 130309lo02&&&
		}
	bPciError=PCI_ERROR_NONE;
}
//130125bin01&&&

///////////////////////////////////////////////////////////////////
//Function:		void vPCICheckApprovedUnitCode(void)
//Description:	Check the PCI unit is approved or not;If the value of ox7E is AA,
//			the PCI unit is approve,else the PCI unit is unapproved.
//Parameter:	none
//Return:		none
///////////////////////////////////////////////////////////////////
void vPCICheckApprovedUnitCode(void)						
{
	BYTE i,btemp;
	bPciError=PCI_ERROR_NONE;
	for(i=0;i<PCI_CHECK_AA_RETRY_TIMES;i++)
		{
		INT_DIS();	// 130420lo01
		btemp=bEepromI2CReadByte(PCI_APPROVED_UNIT_CODE_ADDR);
		INT_EN();	// 130420lo01
		if((btemp==PCI_APPROVED_UNIT_CODE_DATA)||(btemp==0xFF))		//130329lo03	//If 0x7E is AA ,it's OK. If not, retry 3 times;
			{
			return;
			}
		}
	bPciError=PCI_ERROR_DATA;
	vPCIErrorProcess();		
}

///////////////////////////////////////////////////////////////////
//Function:		void vPCIPowerOnReadAndCheckTime(void)	
//Description:	1,Read PCI acc time from PCI EEprom and check the time is proper 
//			   or not.
//			2,Set the PCI acc time in MCU Ram.
//			3,Turn on PCI Power.
//Parameter:	none
//Return:		none
///////////////////////////////////////////////////////////////////
void vPCIPowerOnReadAndCheckTime(void)					
{
	BYTE bcheck_sum=0;	// 130420lo01***
	dPciTime=0;	
	bPciTimerCountMin=0;	//130423lo01
	bPciTimerCountSec=0;	//130423lo01

	vPCIPowerOff();
	
	INT_DIS();
	bpcitemp[0] = bEepromI2CReadByte(PCI_TIME_DEFAULT_ADDR+0);
	bpcitemp[1] = bEepromI2CReadByte(PCI_TIME_DEFAULT_ADDR+1);
	bpcitemp[2] = bEepromI2CReadByte(PCI_TIME_DEFAULT_ADDR+2);
	bcheck_sum =bEepromI2CReadByte(PCI_TIME_DEFAULT_ADDR+7);
	INT_EN();
	
	if((bpcitemp[2]==0xFF)&&fgPCINoneIsError())  //130329lo03*** 
		{
		return;
		}	//130329lo03&&&

	if(bcheck_sum==(BYTE)(bpcitemp[0]+bpcitemp[1]+bpcitemp[2]))
		{
		if(dPciTime>PCI_TIME_19000H)  	//130409lo01
			{
			goto PCI_BACKUP_READ;
			}					
		}
	// If the checksum of acctime read is NG;
	else
		{
PCI_BACKUP_READ:		
		INT_DIS();
		bpcitemp[0] = bEepromI2CReadByte(PCI_TIME_BACKUP_ADDR+0);
		bpcitemp[1] = bEepromI2CReadByte(PCI_TIME_BACKUP_ADDR+1);
		bpcitemp[2] = bEepromI2CReadByte(PCI_TIME_BACKUP_ADDR+2);
		bcheck_sum = bEepromI2CReadByte(PCI_TIME_BACKUP_ADDR+7);
		INT_EN();
		
		if(bcheck_sum==(BYTE)(bpcitemp[0]+bpcitemp[1]+bpcitemp[2]))
			{						
			if(dPciTime>PCI_TIME_19000H)  	//130409lo01
				{
				goto DATA_ERROR;
				}							
			}
		else
			{
DATA_ERROR:
			bPciError=PCI_ERROR_DATA;
			vPCIErrorProcess();
			return;
			}			
		 }

	//vReadPciTime() end./////////////////////////////////////
	
	if(dPciTime==PCI_TIME_19000H)
		{
		bPciError=PCI_ERROR_TIME_19000H;
		fgPciTime19000HStatus=TRUE; 	//130423lo01
		vPCIErrorProcess();		
		return;
		}
	else if((dPciTime>=PCI_TIME_17500H)&&(dPciTime<PCI_TIME_19000H))
		{
		bPciError=PCI_ERROR_TIME_17500H;
		fgPciTime17500HStatus=TRUE;  	//130423lo01
		vPCIErrorProcess();		
		goto PCIpoweron;
		}
	else
		{
PCIpoweron:

		vPCIPowerOn();
		fgPCIPowerOn=TRUE;
		}

}	
// 130420lo01&&&

///////////////////////////////////////////////////////////////////
//Function:		void vCheckPciUnit(void)
//Description:	Check PCI unit is connected or not.
//			put this functin in 25ms timer. 
//Parameter:	none
//Return:		none
///////////////////////////////////////////////////////////////////
void vCheckPciUnit(void)
{
	if(fgIsInPowerOnMode()||fgIsInWatchMode())
//	if(fgIsInPowerOnMode()||(fgIsInPowerOffMode()&&fgIsInWatchMode()))
		{
		if(fgPCINoneIsError())	//When the PCI unit is not connected.			
			{
			if(bPciCheckNoneRetryCount<=PCI_CHECK_NONE_RETRY_TIMES)
				{
				bPciCheckNoneRetryCount++;				//Recheck 16 times;
				if(bPciCheckNoneRetryCount==PCI_CHECK_NONE_RETRY_TIMES)
					{
					bPciError=PCI_ERROR_CONNECTION;
					vPCIErrorProcess();
					bPciCheckNoneRetryCount=0;
					}
				}
			}
		else
			{
			bPciCheckNoneRetryCount=0;
			}
		}
}

///////////////////////////////////////////////////////////////////
//Function:		void vPCIWriteTimeAndCheckTime(void)
//Description:	1,Write PCI acc time to PCI EEprom every 30 minuts.
//			2,After writing ,read the acc time and check it is proper or not.
//			every 25ms run once.
//Parameter:	none
//Return:		none
///////////////////////////////////////////////////////////////////
void vPCIWriteTimeAndCheckTime(void)
{
	static BYTE bStateMechinePCI=0;
	static BYTE bcheck_sum;

	if(fgRunPCIAdd30MinAndCheckTime==FALSE)	// 130420lo01***
		{
		return;
		}

	switch(bStateMechinePCI)
		{
		case 0:
			vPCIPowerOff();
			goto StateMechinePCI;
		case 1:
			bcheck_sum=(BYTE)(bpcitemp[0]+bpcitemp[1]+bpcitemp[2]);
			goto StateMechinePCI;
		case 2:
			INT_DIS();
			vPCIWriteByte(PCI_TIME_DEFAULT_ADDR+0,bpcitemp[0]);
			vPCIWriteByte(PCI_TIME_DEFAULT_ADDR+1,bpcitemp[1]);	
			vPCIWriteByte(PCI_TIME_DEFAULT_ADDR+2,bpcitemp[2]);	
			vPCIWriteByte(PCI_TIME_DEFAULT_ADDR+7,bcheck_sum);	
			INT_EN();
			goto StateMechinePCI;
		case 3:
			goto StateMechinePCI;
		case 4:
			INT_DIS();
			vPCIWriteByte(PCI_TIME_BACKUP_ADDR+0,bpcitemp[0]);	
			vPCIWriteByte(PCI_TIME_BACKUP_ADDR+1,bpcitemp[1]);	
			vPCIWriteByte(PCI_TIME_BACKUP_ADDR+2,bpcitemp[2]);	
			vPCIWriteByte(PCI_TIME_BACKUP_ADDR+7,bcheck_sum);	
			INT_EN();
			goto StateMechinePCI;
		case 5:
			if(dPciTime==PCI_TIME_19000H)
				{
				bPciError=PCI_ERROR_TIME_19000H;
				vPCIErrorProcess();		
				}
			else if(dPciTime>=PCI_TIME_17500H)
				{
				bPciError=PCI_ERROR_TIME_17500H;
				vPCIErrorProcess();
				}	
			goto StateMechinePCI;	
		case 6:
			vPCIPowerOn();
			fgRunPCIAdd30MinAndCheckTime=FALSE;
			bStateMechinePCI=0;
			break;
StateMechinePCI:			
			bStateMechinePCI++;
			break;
		}			// 130420lo01&&&
}
// 130307lo04&&&

///////////////////////////////////////////////////////////////////
//Function:		void vPCITimer1s(void) 
//Description:	This functin is started by 1s timer to write acc time every 30 minutes.
//Parameter:	none
//Return:		none
///////////////////////////////////////////////////////////////////
void vPCITimer1s(void)  		//130423lo01***	
{
	if(fgPCIPowerOn==TRUE)
		{
		if(fgIsInSpeedUpMode())
			{
			bPciTimerCountSec++;
			dPciTime=dPciTime+60;		// 1s*3600=60min
			if(dPciTime>=PCI_TIME_19000H)
				{
				if(fgPciTime19000HStatus==FALSE)
					{
					dPciTime=PCI_TIME_19000H;
					fgPciTime19000HStatus=TRUE;
					fgRunPCIAdd30MinAndCheckTime=TRUE;
					}
				}
			else if(dPciTime>=PCI_TIME_17500H)
				{
				if(fgPciTime17500HStatus==FALSE)
					{
					dPciTime=PCI_TIME_17500H;
					bPciTimerCountSec=0;
					fgPciTime17500HStatus=TRUE;
					fgRunPCIAdd30MinAndCheckTime=TRUE;
					}

				if(bPciTimerCountSec>=60)
					{
					bPciTimerCountSec=0;
					fgRunPCIAdd30MinAndCheckTime=TRUE;
					}
				}
			else
				{
				if(bPciTimerCountSec>=60)
					{
					bPciTimerCountSec=0;
					fgRunPCIAdd30MinAndCheckTime=TRUE;
					}
				}
			}
		else
			{
			bPciTimerCountSec++;
			if(bPciTimerCountSec>=60)
				{
				bPciTimerCountMin++;
				bPciTimerCountSec=0;
				dPciTime++;
				if(dPciTime>=PCI_TIME_19000H)
					{
					if(fgPciTime19000HStatus==FALSE)
						{
						dPciTime=PCI_TIME_19000H;
						fgPciTime19000HStatus=TRUE;
						fgRunPCIAdd30MinAndCheckTime=TRUE;
						}
					return;
					}
				else if(dPciTime==PCI_TIME_17500H)
					{
					dPciTime=PCI_TIME_17500H;
					fgPciTime17500HStatus=TRUE;
					fgRunPCIAdd30MinAndCheckTime=TRUE;
					bPciTimerCountMin=0;
					}

				if(bPciTimerCountMin==30)
					{
					bPciTimerCountMin=0;
					fgRunPCIAdd30MinAndCheckTime=TRUE;
					}
				}
			}
		}		
}
	//130423lo01&&&
#endif


