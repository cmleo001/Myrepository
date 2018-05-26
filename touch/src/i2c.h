#ifndef _I2C_H_
#define _I2C_H_

#ifdef I2C_HARDWARE_FUNCTION
//130126sh01***
enum{
	I2C_WRITE_TO_MAIN_MCU,
	I2C_READ_INT_FROM_MAIN_MCU,
	I2C_WRITE_TO_TOUCH,
	I2C_READ_FROM_TOUCH
};

typedef struct 
{	
	BYTE bPara;
	BYTE bData1;
	BYTE bData2;
	BYTE bData3;
	//BYTE bData4;//130309sh01
}i2c_command_queue;

void vPutI2CCommandQueue(BYTE bPara,BYTE bData1, BYTE bData2,BYTE bData3);
//void vI2cSendCommandBuzzer(BYTE bBuzzer_Type);//130415sh01
void vI2cSendCommand1Para(BYTE bData1);
void vI2cSendCommand2Para(BYTE bData1, BYTE bData2);
void vTouchICReadCommand(BYTE bAddrHigh,BYTE bAddrLow);//130419gr01

#define vI2cSendCommand(bPara,bData1, bData2,bData3)	{vPutI2CCommandQueue(bPara,bData1,bData2,bData3);}
extern BOOL fgI2CCommandBusy;
extern void vI2CWriteCommand(BYTE bPara,BYTE bData1,BYTE bData2,BYTE bData3);
#if 0		//130315Li01***	//130321ha03
//the macro of write command to Main MCU
#define vSubMcuSendPowerStatus(bstatus) 					vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_POWER_STATUS,bstatus,0)//130306sh01***//130309sh01***
#define vSubMcuSendWatchModeStatus(bstatus)				vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_WATCH_MODE_STATUS,bstatus,0)
#define vSubMcuSendIonModeStatus(bstatus)					vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_ION_MODE_STATUS,bstatus,0)
#define vSubMcuSendSpecialMode(bmode) 						vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_SPECIAL_MODE,bmode,0)
#define vSubMcuPinIonResetEnable(fgEnable)					vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_PIN_RESET_ENABLE,fgEnable,0)
#define vSubMcuPinCapsel40PEnable(fgEnable)					vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_PIN_CAPSEL_40P_ENABLE,fgEnable,0)
#define vSubMcuPinPciPowerEnable(fgEnable)					vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_PIN_PCI_POWER_ENABLE,fgEnable,0)
#define vSubMcuMonitorModeStatus(bstatus)					vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_MONITOR_MODE_STATUS, bstatus,0)		//130313Li01
#define vSubMcuFunctionCheckerModeStatus(bstatus)			vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_FUNCTION_CHECKER_MODE_STATUS, bstatus,0)		//130313Li01
//About Main MCU function

//the macro of read command from Main MCU
#define vSubMcuReadHumAdcValue()  					vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_HUM_ADC_VALUE,0,0)
#define vSubMcuReadTempAdcValue() 					vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_TEMP_ADC_VALUE,0,0)
#define vSubMcuReadTempRealValue() 					vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_TEMP_REAL_VALUE,0,0)
#define vSubMcuReadHumRealValue() 					vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_HUM_REAL_VALUE,0,0)
#define vSubMcuReadFanPwmValue()  							vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_FAN_PWM_VALUE,0,0)
#define vSubMcuReadFanRotaSetValue()						vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_FAN_ROTA_SET_VALUE,0,0)
#define vSubMcuReadFanRotaDetectValue()						vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_FAN_ROTA_DETECT_VALUE,0,0)
#define vSubMcuReadIonVoltageValue() 						vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_ION_VOLTAGE_VALUE,0,0)
//#define vSubMcuReadIonDeltaVOff()							vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_ION_DELTA_VOFF,0,0,0)//130309sh04
#define vSubMcuReadIonDeltaV()								vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_ION_DELTA_V,0,0)
#define vSubMcuReadIonLeakCurrentOkCount(bCount)			vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_ION_LEAK_CURRENT_OK_COUNT,bCount,0)//130309sh04
#define vSubMcuReadIonGenerationOkCount(bCount)			vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_ION_GENERATION_OK_COUNT,bCount,0)//130309sh04
#define vSubMcuReadIonErrorCountValue()						vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_ION_ERROR_COUNT_VALUE,0,0)
#define vSubMcuReadPciUnitUseAccTimeValue(bByte)			vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_PCI_UNIT_USE_ACC_TIME_VALUE,bByte,0)//130306sh01&&&
#define vSubMcuReadPciUnitUseAccHourValue()					vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_PCI_UNIT_USE_ACC_HOUR_VALUE,0,0)//130307lo01
#define vSubMcuReadFanMotorRotationValue()			vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_REQUEST_FAN_MOTOR_ROTATION_VALUE,0,0)//130306sh01&&&

//the macro of write command to Main MCU to get the Main MCU interrupt information.
#define vMainMCUInterruptRead()						vI2cSendCommand((BYTE)I2C_READ_INT_FROM_MAIN_MCU,(BYTE)COMMAND_SUB_MAIN_REQUEST_INT_VALUE,(BYTE)(~COMMAND_SUB_MAIN_REQUEST_INT_VALUE),0)

//the macro of write command to Touch IC
#define vTouchICWriteCommand(bAddr,wData)			vI2cSendCommand(I2C_WRITE_TO_TOUCH,bAddr,wData>>8,wData&0xFF)

//the macro of read command from Touch IC
#define vTouchICReadCommand(wAddr) 				vI2cSendCommand(I2C_READ_FROM_TOUCH,wAddr>>8,wAddr&0xFF, 0 )

//About Main MCU function
//#define vBuzzerOutput(bBuzzer_Type)					vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_BUZZER_MODE,bBuzzer_Type,0)
//#define vBuzzerOutput(bBuzzer_Type)					vI2cSendCommandBuzzer(bBuzzer_Type)
#define vBuzzerOutput(bBuzzer_Type)					{bBuzzerType=bBuzzer_Type;}	//130321ha02

#define vLouverModeSet(bmode)						vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_LOUVER_MODE,bmode,0)		//130315Li01
#define vOscillateModeSet(bmode)					vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_OSCILLATE_MODE,bmode,0)		//130315Li01
#define vOscillateMoveToCentral()							{fgOscillateInitialFinish=FALSE;vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_OSCILLATE_MODE,OSCILLATE_CENTRAL,0);}	//130305Ke02	//130315Li01
#define vFanVolumeSet(value)						vI2cSendCommand(I2C_WRITE_TO_MAIN_MCU,COMMAND_SUB_MAIN_FAN_VOLUME,value,0)
#define vFanPower(fgPowerOn)
#else
//the macro of write command to Main MCU
#define vSubMcuSendPowerStatus(bstatus) 					vI2cSendCommand2Para(COMMAND_SUB_MAIN_POWER_STATUS,bstatus)//130306sh01***//130309sh01***
#define vSubMcuSendWatchModeStatus(bstatus)				vI2cSendCommand2Para(COMMAND_SUB_MAIN_WATCH_MODE_STATUS,bstatus)
#define vSubMcuSendIonModeStatus(bstatus)					vI2cSendCommand2Para(COMMAND_SUB_MAIN_ION_MODE_STATUS,bstatus)
#define vSubMcuSendSpecialMode(bmode) 						vI2cSendCommand2Para(COMMAND_SUB_MAIN_SPECIAL_MODE,bmode)
#define vSubMcuPinIonResetEnable(fgEnable)					vI2cSendCommand2Para(COMMAND_SUB_MAIN_PIN_RESET_ENABLE,fgEnable)
#define vSubMcuPinCapsel40PEnable(fgEnable)					vI2cSendCommand2Para(COMMAND_SUB_MAIN_PIN_CAPSEL_40P_ENABLE,fgEnable)
#define vSubMcuPinPciPowerEnable(fgEnable)					vI2cSendCommand2Para(COMMAND_SUB_MAIN_PIN_PCI_POWER_ENABLE,fgEnable)
#define vSubMcuMonitorModeStatus(bstatus)					vI2cSendCommand2Para(COMMAND_SUB_MAIN_MONITOR_MODE_STATUS, bstatus)		//130313Li01
#define vSubMcuFunctionCheckerModeStatus(bstatus)			vI2cSendCommand2Para(COMMAND_SUB_MAIN_FUNCTION_CHECKER_MODE_STATUS, bstatus)		//130313Li01
//for abnormal mode
#define vSubMcuSendError(bErrorMode)						vI2cSendCommand2Para(COMMAND_SUB_MAIN_ERROR_PROCESS,bErrorMode)		//130326vi01

//About Main MCU function

//the macro of read command from Main MCU
#define vSubMcuReadHumAdcValue()  							vI2cSendCommand1Para(COMMAND_SUB_MAIN_REQUEST_HUM_ADC_VALUE)
#define vSubMcuReadTempAdcValue() 							vI2cSendCommand1Para(COMMAND_SUB_MAIN_REQUEST_TEMP_ADC_VALUE)
#define vSubMcuReadTempRealValue() 							vI2cSendCommand1Para(COMMAND_SUB_MAIN_REQUEST_TEMP_REAL_VALUE)
#define vSubMcuReadHumRealValue() 							vI2cSendCommand1Para(COMMAND_SUB_MAIN_REQUEST_HUM_REAL_VALUE)
#define vSubMcuReadFanPwmValue()  							vI2cSendCommand1Para(COMMAND_SUB_MAIN_REQUEST_FAN_PWM_VALUE)
#define vSubMcuReadFanRotaSetValue()						vI2cSendCommand1Para(COMMAND_SUB_MAIN_REQUEST_FAN_ROTA_SET_VALUE)
#define vSubMcuReadFanRotaDetectValue()						vI2cSendCommand1Para(COMMAND_SUB_MAIN_REQUEST_FAN_ROTA_DETECT_VALUE)
#define vSubMcuReadIonVoltageValue() 						vI2cSendCommand1Para(COMMAND_SUB_MAIN_REQUEST_ION_VOLTAGE_VALUE)
//#define vSubMcuReadIonDeltaVOff()							vI2cSendCommand1Para(COMMAND_SUB_MAIN_REQUEST_ION_DELTA_VOFF)//130309sh04
#define vSubMcuReadIonDeltaV()								vI2cSendCommand1Para(COMMAND_SUB_MAIN_REQUEST_ION_DELTA_V)
#define vSubMcuReadIonLeakCurrentOkCount(bCount)			vI2cSendCommand2Para(COMMAND_SUB_MAIN_REQUEST_ION_LEAK_CURRENT_OK_COUNT,bCount)//130309sh04
#define vSubMcuReadIonGenerationOkCount(bCount)			vI2cSendCommand2Para(COMMAND_SUB_MAIN_REQUEST_ION_GENERATION_OK_COUNT,bCount)//130309sh04
#define vSubMcuReadIonErrorCountValue()						vI2cSendCommand1Para(COMMAND_SUB_MAIN_REQUEST_ION_ERROR_COUNT_VALUE)
#define vSubMcuReadPciUnitUseAccTimeValue(bByte)			vI2cSendCommand2Para(COMMAND_SUB_MAIN_REQUEST_PCI_UNIT_USE_ACC_TIME_VALUE,bByte)//130306sh01&&&
#define vSubMcuReadPciUnitUseAccHourValue()					vI2cSendCommand1Para(COMMAND_SUB_MAIN_REQUEST_PCI_UNIT_USE_ACC_HOUR_VALUE)//130307lo01
#define vSubMcuReadFanMotorRotationValue()					vI2cSendCommand1Para(COMMAND_SUB_MAIN_REQUEST_FAN_MOTOR_ROTATION_VALUE)
//the macro of write command to Main MCU to get the Main MCU interrupt information.
#define vMainMCUInterruptRead()								vI2cSendCommand((BYTE)I2C_READ_INT_FROM_MAIN_MCU,(BYTE)COMMAND_SUB_MAIN_REQUEST_INT_VALUE,(BYTE)(~COMMAND_SUB_MAIN_REQUEST_INT_VALUE),0)

//the macro of write command to Touch IC
//#define vTouchICWriteCommand(bAddr,wData)					vI2cSendCommand(I2C_WRITE_TO_TOUCH,bAddr,wData>>8,wData&0xFF)//130415gr01
#define vTouchICWriteCommand(bAddr,bData1,bData2)					vI2cSendCommand(I2C_WRITE_TO_TOUCH,bAddr,bData1,bData2)//130415gr01

//the macro of read command from Touch IC
//#define vTouchICReadCommand(wAddr) 						vI2cSendCommand(I2C_READ_FROM_TOUCH,wAddr>>8,wAddr&0xFF, 0 )//130419gr01

//About Main MCU function
//#define vBuzzerOutput(bBuzzer_Type)							vI2cSendCommandBuzzer(bBuzzer_Type)
#define vBuzzerOutput(bBuzzer_Type)					{bBuzzerType=bBuzzer_Type;}	//130321ha02
//#define vLouverModeSet(bmode)								vI2cSendCommand2Para(COMMAND_SUB_MAIN_LOUVER_MODE,bmode)		//130315Li01
#define vLouverModeSet(bmode)								{bLouverType=bmode;}	//130325ha01
//#define vOscillateModeSet(bmode)								vI2cSendCommand2Para(COMMAND_SUB_MAIN_OSCILLATE_MODE,bmode)		//130315Li01
#define vOscillateModeSet(bmode)								{bOscillateType=bmode;}	//130325ha01
//#define vOscillateMoveToCentral()								{fgOscillateInitialProcess=TRUE;vI2cSendCommand2Para(COMMAND_SUB_MAIN_OSCILLATE_MODE,OSCILLATE_CENTRAL);}	//130315Li01	//130409Ke06	//130412Ke04
//#define vFanVolumeSet(bvalue)								vI2cSendCommand2Para(COMMAND_SUB_MAIN_FAN_VOLUME,bvalue)	//130424Ke03
#define  vFanVolumeSet(bvalue)								{bFanVolumeType=bvalue;}	//130424Ke03
#define vFanPower(fgPowerOn)
#endif		//130315Li01&&&

//extern BYTE bI2cData2;	//Register address Hi to bI2cData2//130417gr01
extern BYTE bI2cData3;	//Register address Lo to bI2cData3

extern BOOL fgI2CCommandQueuFull; //130305gr01

//void vCheckI2CCommandQueue(void);
#define vCheckI2CCommandQueue()
//void vI2cSendCommand(BYTE bPara,BYTE bData1, BYTE bData2,BYTE bData3);//130309sh01

void vISR_I2CTransmit(void);
void vISR_I2CReceive(void);
void vISR_I2CStop(void);
void vInitialI2C(void);

#else//130306sh01***
//the macro of write command to Main MCU
#define vSubMcuSendPowerStatus(bstatus) 
#define vSubMcuSendWatchModeStatus(bstatus)				
#define vSubMcuSendIonModeStatus(bstatus)					
#define vSubMcuSendSpecialMode(bmode) 						
#define vSubMcuPinIonResetEnable(fgEnable)					
#define vSubMcuPinCapsel40PEnable(fgEnable)					
#define vSubMcuPinPciPowerEnable(fgEnable)					
//About Main MCU function
#define vBuzzerOutput(bBuzzer_Type)							
#define vLouverModeSet(bmode)								
#define vOscillateModeSet(bmode)							
#define vOscillateMoveToCentral()					//130305Ke02
#define vFanVolumeSet(value)									

//the macro of read command from Main MCU
#define vSubMcuReadHumAdcValue()  					
#define vSubMcuReadTempAdcValue() 					
#define vSubMcuReadTempRealValue() 					
#define vSubMcuReadHumRealValue() 					
#define vSubMcuReadFanPwmValue()  							
#define vSubMcuReadFanRotaSetValue()						
#define vSubMcuReadFanRotaDetectValue()						
#define vSubMcuReadIonVoltageValue() 					
//#define vSubMcuReadIonDeltaVOff()//130309sh04							
#define vSubMcuReadIonDeltaV()								
#define vSubMcuReadIonLeakCurrentOkCount(bCount)	//130309sh04
#define vSubMcuReadIonGenerationOkCount(bCount)	//130309sh04
#define vSubMcuReadIonErrorCountValue()						
#define vSubMcuReadPciUnitUseAccTimeValue(bByte)			
#define vSubMcuReadPciUnitUseAccHourValue()	
#define vSubMcuMonitorModeStatus(bstatus)
#define vSubMcuFunctionCheckerModeStatus(bstatus)
#define vSubMcuReadFanMotorRotationValue()

//the macro of write command to Main MCU to get the Main MCU interrupt information.
#define vMainMCUInterruptRead()

//the macro of write command to Touch IC
//#define vTouchICWriteCommand(wAddr,wData)//130415gr01
#define vTouchICWriteCommand(wAddr,bData1,bData2)//130415gr01
//the macro of read command from Touch IC
//#define vTouchICReadCommand(wAddr) //130419gr01
#define vTouchICReadCommand(bAddrHigh,bAddrLow) //130419gr01
#define bI2cData2	0
#define bI2cData3	0

#define fgI2CCommandQueuFull	1	//130305gr01


#define vCheckI2CCommandQueue()
#define vI2cSendCommand(bPara,bData1,bData2,bData3)//130309sh01

#define vISR_I2CTransmit()
#define vISR_I2CReceive()
#define vISR_I2CStop()
#define vInitialI2C()
//130306sh01&&&

#define vBuzzerOutput(bBuzzer_Type)
#define vLouverModeSet(bmode)
#define vOscillateModeSet(bmode)
#define  vFanVolumeSet(value)
#define vFanPower(fgPowerOn)

#endif


#endif

