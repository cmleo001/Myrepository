#ifndef _TIMER_H_
#define _TIMER_H_

void vISR_TCC(void);
void vISR_Timer1(void);
void vISR_Timer2(void);
void vISR_Timer3(void);
void vInitialTCC(void);
void vInitialTimer1(void);
void vInitialTimer2(void);
void vInitialTimer3(void);

void vTimer1ms(void);	//130114sh01
void vTimer25ms(void);	//130114sh01
void vTimer1s(void);	//130114sh01
extern BYTE bTimerReach1ms;	//130114sh01
extern BOOL fgTimerReach25ms;	//130114sh01
extern BOOL fgTimerReach1s;	//130114sh01



#endif
