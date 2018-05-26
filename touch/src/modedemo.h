#ifndef _MODE_DEMO_H_
#define _MODE_DEMO_H_

#ifdef DEMO_MODE_FUNCTION
void vDemoModeInitial(void);
void vDemoModeKeyProcess(void);
void vDemoModeExit(void);
void vDemoModeTimer(void);	 //130124ma01
#else
#define vDemoModeInitial()
#define vDemoModeKeyProcess()
#define vDemoModeExit()
#define vDemoModeTimer()
#endif



#endif
