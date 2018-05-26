#define _INTERRUPT_C_
#include "general.h"

extern int IntVecIdx; //occupied 0x50:rpage 0
void _intcall ALLint(void) @ int
{
	switch(IntVecIdx)
		{
		//External Interrupt.
		case 0x4:
			//vISR_IR();
			LJMP(_vISR_IR);
			break;
#if 0
		//Port 6 pin status change Interrupt.
		case 0x7:
			vISR_Port6PinChange();
			break;

		//TCC overflow interrupt.
		case 0xA:
			vISR_TCC();
			break;
			
		//LVD interrupt.
		case 0xD:
			vISR_LVD();
			break;   
			
		//Comparator 1 interrupt.
		case 0x10:
			vISR_Comparator1();
			break;

		//SPI interrupt.
		case 0x13:
			vISR_SPI();
			break;

		//Comparator 2 interrupt.
		case 0x16:
			vISR_Comparator2();
			break;

		//Timer1 interupt.
		case 0x19:
			vISR_Timer1();
			break;

		//UART Transmit complete interrupt.
		case 0x1C:
			vISR_UARTTransmit();
			break;

		//UART Receive data buffer full interrupt.
		case 0x1F:
			vISR_UARTReceive();
			break;    

		//UART Receive error interrupt.
		case 0x22:
			vISR_UARTReceiveError();
			break;  

		//Timer2 interupt.
		case 0x25:
			vISR_Timer2();
			break;   
#endif
		//Timer3 interupt.
		case 0x28:
			//vISR_Timer3();
			LJMP(_vISR_Timer3);
			break;    
#if 0
		//PWMA interupt.
		case 0x2B:
			vISR_PWMA();
			break;        

		//PWMB interupt.
		case 0x2E:
			vISR_PWMB();
			break;      
#endif
		//ADC interupt.
		case 0x31:
			//vISR_ADC();
			ADIF=0;	//130419ha01
			vPutEventQueue(EVENT_ADC,0,0);	//130419ha01
//			LJMP(_vISR_ADC);	//130419ha01
			break;         

		//I2C Transmit interupt.
		case 0x37:
			//vISR_I2CTransmit();
			LJMP(_vISR_I2CTransmit);
			break;   

		//I2C Receive interupt.
		case 0x3A:
			//vISR_I2CReceive();
			LJMP(_vISR_I2CReceive);
			break;
#if 0//130415sh01			
		//I2C stop interupt.
		case 0x40:
			//vISR_I2CStop();
			LJMP(_vISR_I2CStop);
			break;
#endif//130415sh01		
		} 	
}


void _intcall ext_interrupt_l(void) @ 0x03:low_int 0
{
	_asm{MOV A,0x2};
}
void _intcall port6pinchange_l(void) @ 0x06:low_int 1
{
	_asm{MOV A,0x2};
}
void _intcall tccint_l(void) @ 0x09:low_int 2
{
	_asm{MOV A,0x2};
}

void _intcall LVD_l(void) @ 0x0C:low_int 3
{
	_asm{MOV A,0x2};
}
void _intcall CMP1_l(void) @ 0x0F:low_int 4
{
	_asm{MOV A,0x2};
}

void _intcall spi_l(void) @ 0x12:low_int 5
{
	_asm{MOV A,0x2};
}

void _intcall CMP2_l(void) @ 0x15:low_int 6
{
	_asm{MOV A,0x2};
}

void _intcall TC1_l(void) @ 0x18:low_int 7
{
	_asm{MOV A,0x2};
}

void _intcall UARTT_l(void) @ 0x1B:low_int 8
{
	_asm{MOV A,0x2};
}

void _intcall UARTR_l(void) @ 0x1E:low_int 9
{
	_asm{MOV A,0x2};
}

void _intcall UARTRE_l(void) @ 0x21:low_int 10
{
	_asm{MOV A,0x2};
}

void _intcall TC2_l(void) @ 0x24:low_int 11
{
	_asm{MOV A,0x2};
}

void _intcall TC3_l(void) @ 0x27:low_int 12
{
	_asm{MOV A,0x2};
}

void _intcall PWMA_l(void) @ 0x2A:low_int 13
{
	_asm{MOV A,0x2};
}

void _intcall PWMB_l(void) @ 0x2D:low_int 14
{
	_asm{MOV A,0x2};
}

void _intcall AD_l(void) @ 0x30:low_int 15
{
	_asm{MOV A,0x2};
}

void _intcall I2CT_l(void) @ 0x36:low_int 16
{
	_asm{MOV A,0x2};
}

void _intcall I2CR_l(void) @ 0x39:low_int 17
{
	_asm{MOV A,0x2};
}

void _intcall I2CSTOP_l(void) @ 0x3F:low_int 18
{
	_asm{MOV A,0x2};
}
#if 0
void vISR_Port6PinChange(void)
{
	ICIF=0;

}

void vISR_LVD(void)
{
	LVDIF=0;

}

void vISR_Comparator1(void)
{
	CMP1IF=0;


}

void vISR_SPI(void)
{
	SPIF=0;


}

void vISR_Comparator2(void)
{
	CMP2IF=0;


}

void vISR_PWMA(void)
{
	PWMAIF=0;


}

void vISR_PWMB(void)
{
	PWMBIF=0;


}

void vInitialPWMA(void)
{

}

void vInitialPWMB(void)
{

}
#endif
