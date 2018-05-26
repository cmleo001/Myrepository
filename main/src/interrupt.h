#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_


void vISR_Port6PinChange(void);
void vISR_LVD(void);
void vISR_Comparator1(void);
void vISR_SPI(void);
void vISR_Comparator2(void);
void vISR_PWMA(void);
void vISR_PWMB(void);
void vInitialPWMB(void);


#endif

