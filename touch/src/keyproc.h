#ifndef _KEYPROC_H_
#define _KEYPROC_H_

extern BYTE _bKeyState;
extern INT8 bAirVolumeStore;	//130426Ja01
extern BYTE bee_air_volume;	//130427Ja01
//extern BOOL fgAngleLEDOn;//130305Ke01
//power key is allowed only 0.5s past since the last power key is executed.


#define bKeyState()			(_bKeyState )
//#define bKeyState()			(_bKeyState & 0xf)
#define bKeyOldState()		((_bKeyState & 0xf0) >> 4)

#define vSetKeyState(bState)	(_bKeyState = bState )
//#define vSetKeyState(bState)	(_bKeyState = ((_bKeyState & 0x0f) << 4) + bState)
#define vRestorKeyState()		(_bKeyState = (_bKeyState & 0xf0) >> 4 )


void vEventKeyProcess(void);
void vNormalModeKeyProcess(void);
void vDigitalIndicationShowTimer(void);//130305Ke02
void vOscillateMoveToCentral(void);	//130412Ke04
#endif

