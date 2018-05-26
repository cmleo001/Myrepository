#ifndef _OSCILLATE_MOTOR_H_
#define _OSCILLATE_MOTOR_H_

#define HORIZONTAL_ANGLE_60_HIGH	0x07
#define HORIZONTAL_ANGLE_60_LOW	0xF8

#ifdef OSCILLATE_MOTOR_FUNCTION
extern BYTE bOscillateStep;
void vOscillateModeSet(BYTE bmode);
void vOscillateMotorTimer(void);
void vHorizontalMotorGoStep(BYTE bstep);
#else
#define bOscillateStep	0
#define vOscillateModeSet(bmode)
#define vOscillateMotorTimer()
#define vHorizontalMotorGoStep(bstep)

#endif

#endif
