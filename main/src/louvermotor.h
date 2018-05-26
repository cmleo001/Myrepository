#ifndef _LOUVER_MOTOR_H_
#define _LOUVER_MOTOR_H_

#define VERTICAL_ANGLE_20_HIGH	0x01		// (20/5.625)*64 puls=227.55556	228+40 //130426Me01
#define VERTICAL_ANGLE_20_LOW	0x0c		// (20/5.625)*64 puls=227.55556	228+40//130426Me01

#ifdef LOUVER_MOTOR_FUNCTION
extern BYTE bLouverStep;
void vLouverModeSet(BYTE bmode);
void vLouverMotorTimer(void);
void vVerticalMotorGoStep(BYTE bStep);
#define _RAM_VERTICAL_MEMORIZE_POSITION @0x84//130425Me02***
static BYTE bVerticalMemorizedPosition[2] _RAM_VERTICAL_MEMORIZE_POSITION;
static WORD wVerticalMemorizedPosition _RAM_VERTICAL_MEMORIZE_POSITION;//130425Me02&&&

#else
#define bLouverStep	0
#define vLouverModeSet(bmode)
#define vLouverMotorTimer()
#define vVerticalMotorGoStep(bStep)

#endif

/*
#define VERT_ANGLEU90	0
#define VERT_ANGLEU60	341//75  ;the calculate way:(90-60)/5.625*64
#define VERT_ANGLEU40	569//100
#define VERT_ANGLEHOR	1023//153
#define VERT_ANGLEL20	1252//190
#define VERT_ANGLEL25	1308

typedef enum VERT_MODE
{
	VERT_MODE_POWERON,
	VERT_MODE_CLOSE,
	VERT_MODE_ON,
	VERT_MODE_OFF,
	VERT_MODE_U40,
	VERT_MODE_HOR,
	VERT_MODE_L20,
}

extern BOOL fgVertMotorEvt;
extern BYTE bVerticalMode;//record the current mode for vertical

void vLouverMotorTimer(void);
void vVerticalMotorTask(void);
void vLouverModeSet(uint8 mode);
void vSetVerticalPosition(WORD wVertPos);
*/
#endif
