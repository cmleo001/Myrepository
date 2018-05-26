#ifndef _MODE_FUNCTION_CHECKER_H_
#define _MODE_FUNCTION_CHECKER_H_

#define FAN_ROTATIONAL_SPEED_MIN	0
#define FAN_ROTATIONAL_SPEED_MAX	40

#define ION_SENSOR_RESET_ON_VOLEGE_MIN	4
#define ION_SENSOR_RESET_ON_VOLEGE_MAX	5
#define ION_SENSOR_RESET_OFF_VOLEGE_MIN	2
#define ION_SENSOR_RESET_OFF_VOLEGE_MAX	3

#define HUMIDITY_VALUE_50		0x53	 //50	//130328le01***
#define HUMIDITY_VALUE_55		0x5c 	 //55	
#define TEMPERATURE_VALUE_25	0x7F	 //25
#define TEMPERATURE_VALUE_30	0x73	 //30	//130328le01&&&
#define ION_SENSOR_RESET_ON_4v	0xcc
#define ION_SENSOR_RESET_ON_5v	0xFF
#define ION_SENSOR_RESET_OFF_2v	0x66
#define ION_SENSOR_RESET_OFF_3v	0x99

//extern BYTE bFanSetValue;	//130313le01
#ifdef FUNCTION_CHECKER_MODE_FUNCTION

void vFunctionCheckerModeInitial(void);
void vFunctionCheckerModeKeyProcess(void);

#else
#define vFunctionCheckerModeInitial()
#define vFunctionCheckerModeKeyProcess()

#endif



#endif
