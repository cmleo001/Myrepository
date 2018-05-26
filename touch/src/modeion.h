#ifndef _MODE_ION_H_
#define _MODE_ION_H_
#ifdef ION_MODE_FUNCTION
extern BOOL fgIonSetAngle;			// 130423jac02
void vIONModeKey(void);
void vIONModeKeyProcess(void);
//void vIonModeTimer(void);	//130129ja01
//#define vIonModeTimer()	//130129ja01
void vIonClothingDeodorantInit(void);
void vModeIonManualInit(void);
void vSetIONMode(BYTE bmode);		//130306a03v
void vIONModeSetting(void);	//130413lo01

#else
#define fgIonSetAngle 0			// 130423jac02
#define vIONModeKey()
#define vIONModeKeyProcess()
//#define vIonModeTimer()	//130129ja01
#define vIonClothingDeodorantInit()
#define vModeIonManualInit()
#define vSetIONMode(bmode)
#define vIONModeSetting(void)	//130413lo01

#endif



#endif
