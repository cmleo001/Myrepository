#define _MODE_SPEED_UP_C_
#include "general.h"

#if 0	//def SPEED_UP_MODE_FUNCTION	//130407ra02
void vSpeedUpModeInitial(void)
{
	bSpecialFunctionMode=MODE_SPEED_UP;
	vSetKeyState(KEY_SPEED_UP_MODE);
	vOnOffTimerSetAtSpeedUp();	//130312Ti02

}

#if 0
void vSpeedUpModeInitialKeyProcess(void)
{
	switch(bIRKey)
		{
		case IR_POWER:
			break;
		default:
			break;
		}
}
#endif
#endif

