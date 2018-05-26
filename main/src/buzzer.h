#ifndef _BUZZER_H_
#define _BUZZER_H_

//130119Ja01***
//void vInitialBuzzer(void);
#define vPWMBActive()	{PWMB_ENABLE;PWMB_TIMER_ENABLE;}//130424Ad04
#define	vPWMBNonActive()	{PWMB_DISABLE;PWMB_TIMER_DISABLE;}//130424Ad04
void vBuzzerOutput(BYTE bBuzzer_Type);
void vBuzzerTimer(void);
//130119Ja01&&&

#endif
