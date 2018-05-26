#ifndef _FAN_MOTOR_H_
#define _FAN_MOTOR_H_

#ifdef FAN_MOTOR_FUNCTION
//130119Ke01***
void vInitialPWMA(void);
void vFanTimer1S(void);		// 130427jac02
void vFanPower(BYTE PowerOn);
void vFanVolumeSet(BYTE value);
extern BYTE bFanSetRotationSpeedValue;	//130309Ke07
extern BYTE bFanSampleValue;			//130309Ke07
extern BYTE bCurrentSetValue;			//130309Ke07

//130119Ke01&&&
#define vFanVolumeAdd1()	//cannot over 32
#define vFanVolumeAdd4()	//cannot over 32
#define vFanVolumeMinus1()
#define vFanVolumeMinus4()

#else
#define  vInitialPWMA()
#define vFanTimer1S();		// 130427jac02
#define  vFanPower(PowerOn)
#define  vFanVolumeSet(value)

#define  bFanSetRotationSpeedValue	0
#define  bFanSampleValue	0
#define  bCurrentSetValue		0

#define vFanVolumeAdd1()
#define vFanVolumeAdd4()
#define vFanVolumeMinus1()
#define vFanVolumeMinus4()

#endif

#endif
