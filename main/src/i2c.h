#ifndef _I2C_H_
#define _I2C_H_

extern BOOL fgI2CIntBusy;
extern BYTE fgI2CIntTransferOver;//130328sh01

//If INT pin low over 30ms, it will let it '1'-->5ms-->'0' again.
//It will let the touch MCU read the interrupt again.
extern BYTE bI2CIntRetransferCount;//130418sh01
#define I2C_INT_RETRANSFER_LOW_COUNT	30	//30*1ms=30ms	//130418sh01
#define I2C_INT_RETRANSFER_HIGH_COUNT	5	//5*1ms=5ms	//130418sh01
#define I2C_INT_RETRANSFER_COUNT_MAX		0xFE

#ifdef I2C_HARDWARE_FUNCTION
void vISR_I2CTransmit(void);
void vISR_I2CReceive(void);
void vISR_I2CStop(void);
void vInitialI2C(void);

//130126sh01***
void vIntDataQueuePut(BYTE bIntCommand, BYTE bIntData1, BYTE bIntData2);	
void vCheckI2CIntQueue(void);
void vISR_I2CReceive(void);
void vISR_I2CSend(void);
void vISR_I2CStop(void);

extern BYTE bI2CSendBuffer[4];	// 1command+2data+1checksum

//Event about MAIN MCU to TOUCH MCU.
//Command about MAIN to SUB.
#define vIntHumiAdc(bvalue)					{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_HUM_ADC_VALUE,bvalue,0);}//130306sh01***
#define vIntTempAdc(bvalue) 					{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_TEMP_ADC_VALUE,bvalue,0);}
#define vIntTempReal(bvalue) 				{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_TEMP_REAL_VALUE,bvalue,0);}
#define vIntHumiReal(bvalue) 					{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_HUM_REAL_VALUE,bvalue,0);}
#define vIntFanPwm(bvalue) 					{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_FAN_PWM_VALUE,bvalue,0);}
#define vIntFanRotaSet(bvalue)				{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_FAN_ROTA_SET_VALUE,bvalue,0);}
#define vIntFanRotaDetectValue(bvalue)		{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_FAN_ROTA_DETECT_VALUE,bvalue,0);}
#define vIntIonVolValue(bvalue) 				{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_ION_VOLTAGE_VALUE,bvalue,0);}
//#define vIntIonDeltaVOff(bvalue)		{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_ION_DELTA_VOFF,bvalue,0);}//130309sh04
#define vIntIonDeltaV(bvalue)					{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_ION_DELTA_V,bvalue,0);}
#define vIntIonLeakCurrentOkCount(bCount)			{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_ION_LEAK_CURRENT_OK_COUNT,bCount,0);}//130309sh04
#define vIntIonGenerationOkCount(bCount)			{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_ION_GENERATION_OK_COUNT,bCount,0);}//130309sh04
#define vIntIonErrorCnt(bvalue) 				{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_ION_ERROR_COUNT_VALUE,bvalue,0);}
#define vIntPciAccTime(bByte,bvalue) 			{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_PCI_UNIT_USE_ACC_TIME_VALUE,bByte,bvalue);}
#define vIntPciAccHour(bvalue)                                 {vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_PCI_UNIT_USE_ACC_HOUR_VALUE,bvalue,0);}   // 130309lo01
#define vIntOscillateInitialFinish(bvalue)		{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_OSCILLATE_INITIAL_FINISH,bvalue,0);}	//130305Ke02
#define vIntLouverInitialFinish(bvalue)              {vIntDataQueuePut(COMMAND_MAIN_SUB_INT_LOUVER_INITIAL_FINISH, bvalue, 0);}   //130329ro02
#define vIntFanMotorRotationValue(bvalue)	{vIntDataQueuePut(COMMAND_MAIN_SUB_GIVE_FAN_MOTOR_ROTATION_VALUE,bvalue,0);}	//130314le01
//Main MCU INT
#define vIntFanVolume(bvalue) 				{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_FAN_VOLUME,bvalue,0);}
#define vIntSpeedUpMode(bvalue)				{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_SPEED_UP_MODE,bvalue,0);}		//130329Li01
#define vIntFunctionCheckerMode(bvalue)			{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_FUNCTION_CHECKER_MODE,bvalue,0);}	//130329Li01	//130403le01
#define vIntWatchZoneStatusChange(bvalue) 	{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_WATCH_ZONE_STATUS_CHANGE,bvalue,0);}
#define vIntWarningBuzzerStart(bvalue)	{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_WARNING_BUZZER_START,bvalue,0);}	//130411le01
#define vIntWatchAutoFanStatusChange(bstatus,bvolume) 	{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_WATCH_AUTO_FAN_STATUS_CHANGE,bstatus,bvolume);} //130418Ja01
#define vIntLouverMotorOn(bvalue) 	{vIntDataQueuePut(COMMAND_MAIN_SUB_LOUVER_MOTOR_ON,bvalue,0);}	//130424Me01
//error int
#if 0//130309sh04***
#define vIntPciConnetcionError(fgError)					{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_PCI_CONNECTION_ERROR,fgError,0);}
#define vIntPciDataError(fgError)							{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_PCI_DATA_ERROR,fgError,0);}
#define vIntWarningForCleaningPciUnitElectrode(fgError)	{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_WARNING_CLEANING_PCI_UNIT_ELECTRODE,fgError,0);}
#define vIntCoverSwitchError(fgError)						{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_COVER_SWITCH_ERROR,fgError,0);}
#define vIntFanRotaError(fgError)							{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_FAN_ROTA_ERROR,fgError,0);}
#define vIntHumTempError(fgError)						{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_ERROR_HUM_TEMP,fgError,0);}//130306sh01&&&
#endif//130309sh04&&&
#define vIntPciOverTimeStatusError(fgError)				{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_PCI_OVER_TIME,fgError,0);}
#define vIntPciCriticalStatusError(fgError)					{vIntDataQueuePut(COMMAND_MAIN_SUB_INT_PCI_CRITICAL,fgError,0);}
#define vIntMainMCUError(bErrorMode,fgError)				{vIntDataQueuePut(COMMAND_MAIN_SUB_ERROR,bErrorMode,fgError);}//130306sh01&&&//130309sh04
//130126sh01&&&

//130325jac01***
#define vIntSend7SegLEDRow0_1(bRow0, bRow1)		{vIntDataQueuePut(COMMAND_MAIN_SUB_7SEG_LED_0_1_ROW, bRow0, bRow1);}
#define vIntSend7SegLEDRow2(bRow2)					{vIntDataQueuePut(COMMAND_MAIN_SUB_7SEG_LED_2_ROW, bRow2,0x00);}
#define vIntSend7SegLEDRow3_4(bRow3, bRow4)		{vIntDataQueuePut(COMMAND_MAIN_SUB_7SEG_LED_3_4_ROW, bRow3, bRow4);}
//130325jac01&&&


#else
#define vISR_I2CTransmit()
#define vISR_I2CReceive()
#define vISR_I2CStop()
#define vInitialI2C()

#define vIntDataQueuePut( bIntCommand, bIntData1, bIntData2)
#define vCheckI2CIntQueue()
#define vISR_I2CReceive()
#define vISR_I2CSend()
#define vISR_I2CStop()

#define vIntHumiAdc(bvalue)	//130306sh01***
#define vIntTempAdc(bvalue) 	
#define vIntTempReal(bvalue) 	
#define vIntHumiReal(bvalue) 	
#define vIntFanPwm(bvalue) 	
#define vIntFanRotaSet(bvalue) 	
#define vIntFanRotaDetectValue(bvalue) 	
#define vIntIonVolValue(bvalue) 	
//#define vIntIonDeltaVOff(bvalue)//130309sh04
#define vIntIonDeltaV(bvalue)
#define vIntIonLeakCurrentOkCount(bCount)	//130309sh04
#define vIntIonGenerationOkCount(bCount)		//130309sh04
#define vIntIonErrorCnt(bvalue) 
#define vIntPciAccTime(bByte,bvalue) 
#define vIntOscillateInitialFinish(bvalue)
#define vIntFanVolume(bvalue) 	
#define vIntSpeedUpMode(void)	
#define vIntFunctionCheckerMode(bvalue)	//130403le01

#define vIntWatchZoneStatusChange(bvalue) 
#define vIntWarningBuzzerStart(bvalue)	//130411le01

#if 0//130309sh04***
#define vIntPciConnetcionError(fgError)					
#define vIntPciDataError(fgError)							
#define vIntWarningForCleaningPciUnitElectrode(fgError)	
#define vIntCoverSwitchError(fgError)						
#define vIntFanRotaError(fgError)							
#define vIntHumTempError(fgError)	//130306sh01&&&
#endif
#define vIntPciOverTimeStatusError(fgError)				
#define vIntPciCriticalStatusError(fgError)					
#define vIntMainMCUError(bErrorMode,fgError)//130309sh04&&&
#endif



#endif

