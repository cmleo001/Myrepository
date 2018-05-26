#define _UART_C_
#include "general.h"



void vISR_UARTTransmit(void)
{
	TBEF=0;

}

void vISR_UARTReceive(void)
{
	RBFF=0;

}

void vISR_UARTReceiveError(void)
{
	UERRIF=0;


}

void vInitialUART(void)
{


}


