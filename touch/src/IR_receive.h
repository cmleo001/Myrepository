#ifndef _IR_RECEIVE_H_
#define _IR_RECEIVE_H_
#ifdef IR_FUNCTION
extern BYTE bIRStateMachine;	//130412st01

extern BOOL fgIRFineNotPressContinue;	//130422le01
extern BYTE bIRFineKeyTimerCount;	//130422le01

#define IR_MAX_TCC_COUNT	180	//Max bit code is lead code 5060us/32us=158. Over 158 is not the normal IR bit.	//130412st01
void vISR_IR(void);
	#ifdef IR_COUNT_VALUE_USE_ARRAY_SAVE	//130306a01w
void vIRCheck(void);
	#else
#define vIRCheck()
	#endif	//130306a01w

#else
#define vISR_IR()
#define vIRCheck()

#endif

#endif

