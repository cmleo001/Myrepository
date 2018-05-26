#ifndef _MODE_SERVICE_MONITOR_H_
#define _MODE_SERVICE_MONITOR_H_

#ifdef SERVICE_MONITOR_MODE_FUNCTION
//130123ra01***
void vServiceMonitorModeInitial(void);
void vServiceMonitorModeKeyProcess(void);
//130123ra01&&&
#else
#define vServiceMonitorModeInitial()
#define vServiceMonitorModeKeyProcess()

#endif

#endif
