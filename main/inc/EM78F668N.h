/****************************************************************************
 *	Title:       EM78F668N.H												*
 *	Target MCU:  EM78F668N					         	                    *
 *	Description: Register/bit definitions									*
 *	Company:     ELAN MICROELECTRONICS (SZ) LTD.       	                    *
 * 	Date:        2009-10-28                             	                *
 *	Version:     v1.0                                  	                    *
 ***************************************************************************/
/*#ifndef __EM78F668N_H__
#define	__EM78F668N_H__*/
static unsigned int  R0                 @0x00:rpage 0;//Indirect Address Register
static unsigned int  IAR                @0x00:rpage 0;//Indirect Address Register
static unsigned int  BSR                @0x01:rpage 0;//Bank selection control register
static unsigned int  PC                 @0x02:rpage 0;//Program Counter & Stack
static unsigned int  STATUS             @0x03:rpage 0;//Process Status Register
static unsigned int  RSR                @0x04:rpage 0;//RAM Select Register
static unsigned int  PORT5              @0x05:rpage 0;//I/O Port Address
static unsigned int  PORT6              @0x06:rpage 0;//I/O Port Address
static unsigned int  PORT7              @0x07:rpage 0;//I/O Port Address
static unsigned int  PORT8              @0x08:rpage 0;//I/O Port Address
static unsigned int  PORT9              @0x09:rpage 0;//I/O Port Address
static unsigned int  OMCR               @0x0B:rpage 0;//Operating mode control register
static unsigned int  ISR1               @0x0C:rpage 0;//Interrrupt status register1
static unsigned int  ISR2               @0x0D:rpage 0;//Interrrupt status register2
static unsigned int  ISR3               @0x0E:rpage 0;//Interrrupt status register3
static unsigned int  EIESCR             @0x10:rpage 0;//External interrupt edge select control register       
static unsigned int  WDTCR              @0x11:rpage 0;//WDT Control Register
static unsigned int  LVDCR              @0x12:rpage 0;//low voltage detector control regsiter
static unsigned int  TCCCR              @0x13:rpage 0;//Timer 2 Control Register
static unsigned int  TCC                @0x14:rpage 0;//TCC Data Buffer
static unsigned int  P5CR               @0x15:rpage 0;//Port5 control register
static unsigned int  P6CR               @0x16:rpage 0;//Port6 control register
static unsigned int  P7CR               @0x17:rpage 0;//Port7 control register
static unsigned int  P8CR               @0x18:rpage 0;//Port8 control register
static unsigned int  P9CR               @0x19:rpage 0;//Port9 control register
static unsigned int  IMR1               @0x1C:rpage 0;//Interrupt mask Register 1                 0
static unsigned int  IMR2               @0x1D:rpage 0;//Interrupt mask Register 2
static unsigned int  IMR3               @0x1E:rpage 0;//Interrupt mask Register 3
static unsigned int  P5WUCR             @0x20:rpage 0;//Port5 wake up control register
static unsigned int  P5WUECR            @0x21:rpage 0;//Port5 wake up EDGE control register
static unsigned int  P7WUCR             @0x22:rpage 0;//Port7 wake up control register
static unsigned int  P7WUECR            @0x23:rpage 0;//Port7 wake up EDGE control register
static unsigned int  ADCR1              @0x24:rpage 0;//ADC control register 1
static unsigned int  ADCR2              @0x25:rpage 0;//ADC control register 2
static unsigned int  ADICL              @0x26:rpage 0;//ADC input select low byte register
static unsigned int  ADDH               @0x29:rpage 0;//AD High 8-Bit Data Buffer
static unsigned int  ADDL               @0x2A:rpage 0;//AD Low 4-Bit Data Buffer
static unsigned int  SPICR              @0x2B:rpage 0;//SPI control register
static unsigned int  SPIS               @0x2C:rpage 0;//SPI Status register
static unsigned int  SPIRB              @0x2D:rpage 0;//SPI read buffer register
static unsigned int  SPIWB              @0x2E:rpage 0;//SPI writer buffer register
static unsigned int  WUCR1              @0x2F:rpage 0;//Wake up control register1
static unsigned int  URCR1              @0x32:rpage 0;//UART control regsiter1
static unsigned int  URCR2              @0x33:rpage 0;//UART control regsiter2
static unsigned int  URS                @0x34:rpage 0;//UART status regsiter
static unsigned int  URRD               @0x35:rpage 0;//UART receive data buffer regsiter
static unsigned int  URTD               @0x36:rpage 0;//UART transmit data buffer regsiter
static unsigned int  TBPTL              @0x37:rpage 0;//Table point register
static unsigned int  TBPTH              @0x38:rpage 0;//Table point register
static unsigned int  CMP1CR             @0x39:rpage 0;//Comparator 1 control register
static unsigned int  CMP2CR             @0x3C:rpage 0;//Comparator 2 control register
static unsigned int  CPIRLCON           @0x43:rpage 0;//Comparator internal reference level control register
static unsigned int  TC1CR              @0x48:rpage 0;//timer 1 control register
static unsigned int  TCR1DA             @0x49:rpage 0;//Timer 1 data buffer A
static unsigned int  TCR1DB             @0x4A:rpage 0;//Timer 1 data buffer B
static unsigned int  TC2CR              @0x4B:rpage 0;//Timer 2 control register
static unsigned int  TCR2DH             @0x4C:rpage 0;//Timer 2 high byte data buffer register
static unsigned int  TCR2DL             @0x4D:rpage 0;//Timer 2 low byte data buffer register
static unsigned int  TC3CR              @0x4E:rpage 0;//Timer 3 control register
static unsigned int  TCR3D              @0x4F:rpage 0;//Timer 3 duty buffer register
// bank 1
static unsigned int  P5PHCR             @0x05:rpage 1;//Port5 pull high control register
static unsigned int  P6PHCR             @0x06:rpage 1;//Port6 pull high control register
static unsigned int  P7PHCR             @0x07:rpage 1;//Port7 pull high control register
static unsigned int  P8PHCR             @0x08:rpage 1;//Port8 pull high control register
static unsigned int  P9PHCR             @0x09:rpage 1;//Port9 pull high control register
static unsigned int  P5PLCR             @0x0B:rpage 1;//Port5 pull low control register
static unsigned int  P6PLCR             @0x0C:rpage 1;//Port6 pull low control register
static unsigned int  P7PLCR             @0x0D:rpage 1;//Port7 pull low control register
static unsigned int  P8PLCR             @0x0E:rpage 1;//Port8 pull low control register
static unsigned int  P9PLCR             @0x0F:rpage 1;//Port9 pull low control register
static unsigned int  P5PHD              @0x11:rpage 1;//Port5 pull high drive/sink control register
static unsigned int  P6PHD              @0x12:rpage 1;//Port6 pull high drive/sink control register
static unsigned int  P7PHD              @0x13:rpage 1;//Port7 pull high drive/sink control register
static unsigned int  P8PHD              @0x14:rpage 1;//Port8 pull high drive/sink control register
static unsigned int  P9PHD              @0x15:rpage 1;//Port9 pull high drive/sink control register
static unsigned int  P5ODCR             @0x17:rpage 1;//Port5 open drain control register
static unsigned int  P6ODCR             @0x18:rpage 1;//Port6 open drain control register
static unsigned int  P7ODCR             @0x19:rpage 1;//Port7 open drain control register
static unsigned int  P8ODCR             @0x1A:rpage 1;//Port8 open drain control register
static unsigned int  P9ODCR             @0x1B:rpage 1;//Port9 open drain control register
static unsigned int  IRCS               @0x1D:rpage 1;//IRC frequency selection register
static unsigned int  EEPCR              @0x1F:rpage 1;//EEPROM control register
static unsigned int  EEPA               @0x20:rpage 1;//EEPROM ADDR
static unsigned int  EEPD               @0x21:rpage 1;//EEPROM DATA
static unsigned int  I2CCR1             @0x23:rpage 1;//I2C status and control register1
static unsigned int  I2CCR2             @0x24:rpage 1;//I2C status and control register2
static unsigned int  I2CSA              @0x25:rpage 1;//I2C Slave address register
static unsigned int  I2CDA              @0x26:rpage 1;//I2C Device address register
static unsigned int  I2CDB              @0x27:rpage 1;//I2C data buffer register
static unsigned int  I2CA               @0x28:rpage 1;//I2C data buffer register
static unsigned int  PWMER              @0x2A:rpage 1;//PWM enable control register
static unsigned int  TIMEN              @0x2B:rpage 1;//Timer/PWM enable control register
static unsigned int  PWMACR             @0x2F:rpage 1;//PWM A control register
static unsigned int  PWMBCR             @0x30:rpage 1;//PWM B control register
static unsigned int  TACR               @0x32:rpage 1;//Timer A control register
static unsigned int  TBCR               @0x33:rpage 1;//Timer B control register
static unsigned int  TAPRDH             @0x35:rpage 1;//Timer A Period buffer register
static unsigned int  TBPRDH             @0x36:rpage 1;//Timer B Period buffer register
static unsigned int  TADTH              @0x38:rpage 1;//Timer A duty buffer register
static unsigned int  TBDTH              @0x39:rpage 1;//Timer B duty buffer register
static unsigned int  PRDxL              @0x3B:rpage 1;//PWM A/B/C Period buffer low bits register
static unsigned int  DTxL               @0x3C:rpage 1;//PWM1/2 duty buffer low bits register

//;---------------------------------------------------------------------------------------
/*BSR Bits*/
static bit      SBS0    @0x01@4:rpage 0;
static bit      GBS0    @0x01@0:rpage 0;
/*R3 Bits*/
static bit      T       @0x03@4:rpage 0;
static bit      P       @0x03@3:rpage 0;
static bit      Z       @0x03@2:rpage 0;        
static bit      DC      @0x03@1:rpage 0;
static bit      C       @0x03@0:rpage 0;
/*R4 Bits*/
static bit      RSR7    @0x04@7:rpage 0;
static bit      RSR6    @0x04@6:rpage 0;
static bit      RSR5    @0x04@5:rpage 0;
static bit      RSR4    @0x04@4:rpage 0;
static bit      RSR3    @0x04@3:rpage 0;
static bit      RSR2    @0x04@2:rpage 0;
static bit      RSR1    @0x04@1:rpage 0;
static bit      RSR0    @0x04@0:rpage 0;
/*R5 Bits*/
static bit      P57     @0x05@7:rpage 0;
static bit      P56     @0x05@6:rpage 0;
static bit      P55     @0x05@5:rpage 0;
static bit      P54     @0x05@4:rpage 0;
static bit      P53     @0x05@3:rpage 0;
static bit      P52     @0x05@2:rpage 0;
static bit      P51     @0x05@1:rpage 0;
static bit      P50     @0x05@0:rpage 0;
/*R6 Bits*/
static bit      P67     @0x06@7:rpage 0;
static bit      P66     @0x06@6:rpage 0;
static bit      P65     @0x06@5:rpage 0;
static bit      P64     @0x06@4:rpage 0;
static bit      P63     @0x06@3:rpage 0;
static bit      P62     @0x06@2:rpage 0;
static bit      P61     @0x06@1:rpage 0;
static bit      P60     @0x06@0:rpage 0;
/*R7  Bits*/
static bit      P77     @0x07@7:rpage 0;
static bit      P76     @0x07@6:rpage 0;
static bit      P75     @0x07@5:rpage 0;
static bit      P74     @0x07@4:rpage 0;
static bit      P73     @0x07@3:rpage 0;
static bit      P72     @0x07@2:rpage 0;
static bit      P71     @0x07@1:rpage 0;
static bit      P70     @0x07@0:rpage 0;
/*R8  Bits*/
static bit      P87     @0x08@7:rpage 0;
static bit      P86     @0x08@6:rpage 0;
static bit      P85     @0x08@5:rpage 0;
static bit      P84     @0x08@4:rpage 0;
static bit      P83     @0x08@3:rpage 0;
static bit      P82     @0x08@2:rpage 0;
static bit      P81     @0x08@1:rpage 0;
static bit      P80     @0x08@0:rpage 0;
/*R9  Bits*/                            
static bit      P97     @0x09@7:rpage 0;
static bit      P96     @0x09@6:rpage 0;
static bit      P95     @0x09@5:rpage 0;
static bit      P94     @0x09@4:rpage 0;
static bit      P93     @0x09@3:rpage 0;
static bit      P92     @0x09@2:rpage 0;
static bit      P91     @0x09@1:rpage 0;
static bit      P90     @0x09@0:rpage 0;
/*OMCR Bits */
static bit      CPUS    @0x0B@7:rpage 0;
static bit      IDLE    @0x0B@6:rpage 0;
static bit      TC1SS   @0x0B@5:rpage 0;
static bit      TC2SS   @0x0B@4:rpage 0;
static bit      TC3SS   @0x0B@3:rpage 0; 
static bit      TASS    @0x0B@2:rpage 0;
static bit      TBSS    @0x0B@1:rpage 0;    
/*ISR1 Bits*/
static bit      LVDIF   @0x0C@7:rpage 0;
static bit      ADIF    @0x0C@6:rpage 0;
static bit      SPIF    @0x0C@5:rpage 0;
static bit      PWMBIF  @0x0C@4:rpage 0;     
static bit      PWMAIF  @0x0C@3:rpage 0;     
static bit      EXIF    @0x0C@2:rpage 0;     
static bit      ICIF    @0x0C@1:rpage 0;     
static bit      TCIF    @0x0C@0:rpage 0; 
/*ISR2 Bits*/
static bit      CMP2IF  @0x0D@7:rpage 0;
static bit      CMP1IF  @0x0D@6:rpage 0;
static bit      TC3IF   @0x0D@5:rpage 0;
static bit      TC2IF   @0x0D@4:rpage 0;
static bit      TC1IF   @0x0D@3:rpage 0;
static bit      UERRIF  @0x0D@2:rpage 0;     
static bit      RBFF    @0x0D@1:rpage 0; 
static bit      TBEF    @0x0D@0:rpage 0;
/*ISR3 Bits*/
static bit      I2CSTPIF   @0x0E@3:rpage 0;  
static bit      I2CRIF     @0x0E@1:rpage 0;  
 static bit     I2CTIF     @0x0E@0:rpage 0;
/*EIESCR Bits*/
static bit      EIES    @0x10@0:rpage 0;
/*WDTCR Bits*/                               
static bit      WDTE    @0x11@7:rpage 0;    
static bit      EIS     @0x11@6:rpage 0;
static bit      EINT    @0x11@5:rpage 0;    
static bit      PSWE    @0x11@3:rpage 0;    
static bit      PSW2    @0x11@2:rpage 0;    
static bit      PSW1    @0x11@1:rpage 0;    
static bit      PSW0    @0x11@0:rpage 0;    
/*LVDCR Bits*/                              
static bit      LVDEN   @0x12@3:rpage 0;    
static bit      LVD     @0x12@2:rpage 0;    
static bit      LVD1    @0x12@1:rpage 0;    
static bit      LVD2    @0x12@0:rpage 0;    
/*TCCCR Bits*/                               
static bit      TCCS    @0x13@6:rpage 0;     
static bit      TS      @0x13@5:rpage 0;    
static bit      TE      @0x13@4:rpage 0;    
static bit      PSTE    @0x13@3:rpage 0;    
static bit      PST2    @0x13@2:rpage 0;    
static bit      PST1    @0x13@1:rpage 0;    
static bit      PST0    @0x13@0:rpage 0;   
/*P5CR Bits*/                               
static bit      P57CR    @0x15@7:rpage 0;     
static bit      P56CR    @0x15@6:rpage 0;     
static bit      P55CR    @0x15@5:rpage 0;     
static bit      P54CR    @0x15@4:rpage 0;     
static bit      P53CR    @0x15@3:rpage 0;     
static bit      P52CR    @0x15@2:rpage 0;     
static bit      P51CR    @0x15@1:rpage 0;
static bit      P50CR    @0x15@0:rpage 0;     
/*P6CR Bits*/                              
static bit      P67CR    @0x16@7:rpage 0;  
static bit      P66CR    @0x16@6:rpage 0;  
static bit      P65CR    @0x16@5:rpage 0;  
static bit      P64CR    @0x16@4:rpage 0;  
static bit      P63CR    @0x16@3:rpage 0;  
static bit      P62CR    @0x16@2:rpage 0;  
static bit      P61CR    @0x16@1:rpage 0;  
static bit      P60CR    @0x16@0:rpage 0;  
/*P7CR Bits*/                              
static bit      P77CR    @0x17@7:rpage 0;  
static bit      P76CR    @0x17@6:rpage 0;  
static bit      P75CR    @0x17@5:rpage 0;  
static bit      P74CR    @0x17@4:rpage 0;  
static bit      P73CR    @0x17@3:rpage 0;  
static bit      P72CR    @0x17@2:rpage 0;  
static bit      P71CR    @0x17@1:rpage 0;  
static bit      P70CR    @0x17@0:rpage 0;  
/*P8CR Bits*/                              
static bit      P87CR    @0x18@7:rpage 0;  
static bit      P86CR    @0x18@6:rpage 0;  
static bit      P85CR    @0x18@5:rpage 0;  
static bit      P84CR    @0x18@4:rpage 0;  
static bit      P83CR    @0x18@3:rpage 0;  
static bit      P82CR    @0x18@2:rpage 0;  
static bit      P81CR    @0x18@1:rpage 0;  
static bit      P80CR    @0x18@0:rpage 0;  
/*P9CR Bits*/                              
static bit      P97CR    @0x19@7:rpage 0;  
static bit      P96CR    @0x19@6:rpage 0;  
static bit      P95CR    @0x19@5:rpage 0;  
static bit      P94CR    @0x19@4:rpage 0;  
static bit      P93CR    @0x19@3:rpage 0;  
static bit      P92CR    @0x19@2:rpage 0;  
static bit      P91CR    @0x19@1:rpage 0;  
static bit      P90CR    @0x19@0:rpage 0;  
/*IMR1 Bits*/                              
static bit      LVDIE    @0x1C@7:rpage 0;  
static bit      ADIE     @0x1C@6:rpage 0;  
static bit      SPIE     @0x1C@5:rpage 0;  
static bit      PWMBIE   @0x1C@4:rpage 0;  
static bit      PWMAIE   @0x1C@3:rpage 0;  
static bit      EXIE     @0x1C@2:rpage 0;  
static bit      ICIE     @0x1C@1:rpage 0;  
static bit      TCIE     @0x1C@0:rpage 0;  
/*IMR2 Bits*/                              
static bit      CMP2IE   @0x1D@7:rpage 0;  
static bit      CMP1IE   @0x1D@6:rpage 0;  
static bit      TC3IE    @0x1D@5:rpage 0;  
static bit      TC2IE    @0x1D@4:rpage 0;  
static bit      TC1IE    @0x1D@3:rpage 0;  
static bit      UERRIE   @0x1D@2:rpage 0;  
static bit      URIE     @0x1D@1:rpage 0;  
static bit      UTIE     @0x1D@0:rpage 0;   
/*IMR3 Bits*/                              
static bit      I2CSTPIE @0x1E@3:rpage 0;  
static bit      I2CRIE   @0x1E@1:rpage 0;  
static bit      I2CTIE   @0x1E@0:rpage 0;  
/*P5WUCR Bits*/                              
static bit      WU_P57   @0x20@7:rpage 0;  
static bit      WU_P56   @0x20@6:rpage 0;  
static bit      WU_P55   @0x20@5:rpage 0;  
static bit      WU_P54   @0x20@4:rpage 0;  
static bit      WU_P53   @0x20@3:rpage 0;  
static bit      WU_P52   @0x20@2:rpage 0;  
static bit      WU_P51   @0x20@1:rpage 0;  
static bit      WU_P50   @0x20@0:rpage 0;   
/*P5WUECR Bits*/                              
static bit      WUE_P57  @0x21@7:rpage 0;  
static bit      WUE_P56  @0x21@6:rpage 0;  
static bit      WUE_P55  @0x21@5:rpage 0;  
static bit      WUE_P54  @0x21@4:rpage 0;  
static bit      WUE_P53  @0x21@3:rpage 0;  
static bit      WUE_P52  @0x21@2:rpage 0;  
static bit      WUE_P51  @0x21@1:rpage 0;  
static bit      WUE_P50  @0x21@0:rpage 0;    
/*P7WUCR Bits*/                              
static bit      WU_P77   @0x22@7:rpage 0;  
static bit      WU_P76   @0x22@6:rpage 0;  
static bit      WU_P75   @0x22@5:rpage 0;  
static bit      WU_P74   @0x22@4:rpage 0;  
static bit      WU_P73   @0x22@3:rpage 0;  
static bit      WU_P72   @0x22@2:rpage 0;  
static bit      WU_P71   @0x22@1:rpage 0;  
static bit      WU_P70   @0x22@0:rpage 0;   
/*P7WUECR Bits*/                              
static bit      WUE_P77  @0x23@7:rpage 0;  
static bit      WUE_P76  @0x23@6:rpage 0;  
static bit      WUE_P75  @0x23@5:rpage 0;  
static bit      WUE_P74  @0x23@4:rpage 0;  
static bit      WUE_P73  @0x23@3:rpage 0;  
static bit      WUE_P72  @0x23@2:rpage 0;  
static bit      WUE_P71  @0x23@1:rpage 0;  
static bit      WUE_P70  @0x23@0:rpage 0;   
/*ADCR1 Bits*/                             
static bit      VREFS    @0x24@7:rpage 0;       
static bit      ADRUN	 @0x24@6:rpage 0;      
static bit      ADPD     @0x24@5:rpage 0;      
static bit      ADIS2    @0x24@2:rpage 0;      
static bit      ADIS1    @0x24@1:rpage 0;      
static bit      ADIS0    @0x24@0:rpage 0;      
/*ADCR2 Bits*/                              
static bit      CALI     @0x25@7:rpage 0;   
static bit      SIGN     @0x25@6:rpage 0;   
static bit      VOF2     @0x25@5:rpage 0;   
static bit      VOF1     @0x25@4:rpage 0;   
static bit      VOF0     @0x25@3:rpage 0;   
static bit      CKR2     @0x25@2:rpage 0;   
static bit      CKR1     @0x25@1:rpage 0;   
static bit      CKR0     @0x25@0:rpage 0;   
/*ADICL Bits*/                           
static bit      ADE7     @0x26@7:rpage 0;
static bit      ADE6     @0x26@6:rpage 0;
static bit      ADE5     @0x26@5:rpage 0;
static bit      ADE4     @0x26@4:rpage 0;
static bit      ADE3     @0x26@3:rpage 0;
static bit      ADE2     @0x26@2:rpage 0;
static bit      ADE1     @0x26@1:rpage 0;
static bit      ADE0     @0x26@0:rpage 0;
/*SPICR Bits*/                           
static bit      CES      @0x2B@7:rpage 0;
static bit      SPI_E    @0x2B@6:rpage 0;
static bit      SRO      @0x2B@5:rpage 0;
static bit      SSE      @0x2B@4:rpage 0;
static bit      SDOC     @0x2B@3:rpage 0;
static bit      SBRS2    @0x2B@2:rpage 0;
static bit      SBRS1    @0x2B@1:rpage 0;
static bit      SBRS0    @0x2B@0:rpage 0;
/*SPIS Bits*/                           
static bit      DORD     @0x2C@7:rpage 0;
static bit      TD1      @0x2C@6:rpage 0;
static bit      TD0      @0x2C@5:rpage 0;
static bit      OD3      @0x2C@3:rpage 0;
static bit      OD4      @0x2C@2:rpage 0;
static bit      RBF      @0x2C@0:rpage 0;
/*WUCR1 Bits*/                           
static bit      SPIWE    @0x2F@6:rpage 0;
static bit      LVDWE    @0x2F@5:rpage 0;
static bit      ICWE     @0x2F@4:rpage 0;
static bit      ADWE     @0x2F@3:rpage 0;
static bit      CMP2WE   @0x2F@2:rpage 0;
static bit      CMP1WE   @0x2F@1:rpage 0;
static bit      EXWE     @0x2F@0:rpage 0;
/*URCR1 Bits*/                           
static bit      URTD8    @0x32@7:rpage 0;
static bit      UMODE1   @0x32@6:rpage 0;
static bit      UMODE0   @0x32@5:rpage 0;
static bit      BRATE2   @0x32@4:rpage 0;
static bit      BRATE1   @0x32@3:rpage 0;
static bit      BRATE0   @0x32@2:rpage 0;
static bit      UTBE     @0x32@1:rpage 0;
static bit      TXE      @0x32@0:rpage 0;
/*URCR2 Bits*/                           
static bit      SBIM1    @0x33@5:rpage 0;
static bit      SBIM0    @0x33@4:rpage 0;
static bit      UINVEN   @0x33@3:rpage 0;
/*URS Bits*/                           
static bit      URRD8    @0x34@7:rpage 0;
static bit      EVEN     @0x34@6:rpage 0;
static bit      PRE      @0x34@5:rpage 0;
static bit      PRERR    @0x34@4:rpage 0;
static bit      OVERR    @0x34@3:rpage 0;
static bit      FMERR    @0x34@2:rpage 0;
static bit      URBF     @0x34@1:rpage 0;
static bit      RXE      @0x34@0:rpage 0;
/*CMP1CR Bits*/                           
static bit      C1RS     @0x39@7:rpage 0;
static bit      CP1OUT   @0x39@6:rpage 0;
static bit      CMP1COS1 @0x39@5:rpage 0;
static bit      CMP1COS0 @0x39@4:rpage 0;
static bit      CP1NS    @0x39@3:rpage 0;
static bit      CP1PS    @0x39@2:rpage 0;
static bit      CP1NRE   @0x39@1:rpage 0;
static bit      CP1NRDT  @0x39@0:rpage 0;
/*CMP2CR Bits*/                                 
static bit      C2RS     @0x3C@7:rpage 0;       
static bit      CP2OUT   @0x3C@6:rpage 0;       
static bit      CMP2COS1 @0x3C@5:rpage 0;       
static bit      CMP2COS0 @0x3C@4:rpage 0;       
static bit      CP2NS    @0x3C@3:rpage 0;       
static bit      CP2PS    @0x3C@2:rpage 0;       
static bit      CP2NRE   @0x3C@1:rpage 0;       
static bit      CP2NRDT  @0x3C@0:rpage 0;       
/*CPIRLCON Bits*/                                 
static bit      BG2OUT   @0x43@7:rpage 0;       
static bit      C2IRL2   @0x43@6:rpage 0;       
static bit      C2IRL1   @0x43@5:rpage 0;       
static bit      C2IRL0   @0x43@4:rpage 0;       
static bit      BG1OUT   @0x43@3:rpage 0;       
static bit      C1IRL2   @0x43@2:rpage 0;       
static bit      C1IRL1   @0x43@1:rpage 0;       
static bit      C1IRL0   @0x43@0:rpage 0;       
/*TC1CR Bits*/                          
static bit      TC1CAP   @0x48@7:rpage 0;  
static bit      TC1S     @0x48@6:rpage 0;  
static bit      TC1CK1   @0x48@5:rpage 0;  
static bit      TC1CK0   @0x48@4:rpage 0;  
static bit      TC1M     @0x48@3:rpage 0;  
static bit      TC1ES    @0x48@2:rpage 0;  
 /*TC2CR Bits*/                            
static bit      TC2ES    @0x4B@5:rpage 0;  
static bit      TC2M     @0x4B@4:rpage 0;  
static bit      TC2S     @0x4B@3:rpage 0;  
static bit      TC2CK2   @0x4B@2:rpage 0;  
static bit      TC2CK1   @0x4B@1:rpage 0;  
static bit      TC2CK0   @0x4B@0:rpage 0;  
/*TC3CR Bits*/                          
static bit      TC3FF1   @0x4E@7:rpage 0;  
static bit      TC3FF0   @0x4E@6:rpage 0;  
static bit      TC3S     @0x4E@5:rpage 0;  
static bit      TC3CK2   @0x4E@4:rpage 0;  
static bit      TC3CK1   @0x4E@3:rpage 0;  
static bit      TC3CK0   @0x4E@2:rpage 0;  
static bit      TC3M1    @0x4E@1:rpage 0;  
static bit      TC3M0    @0x4E@0:rpage 0;  
//BANK 1
/*P5PHCR Bits*/                          
static bit      PH57     @0x05@7:rpage 1;  
static bit      PH56     @0x05@6:rpage 1;  
static bit      PH55     @0x05@5:rpage 1;  
static bit      PH54     @0x05@4:rpage 1;  
static bit      PH53     @0x05@3:rpage 1;  
static bit      PH52     @0x05@2:rpage 1;  
static bit      PH51     @0x05@1:rpage 1;  
static bit      PH50     @0x05@0:rpage 1;  
/*P6PHCR Bits*/                              
static bit      PH67     @0x06@7:rpage 1;    
static bit      PH66     @0x06@6:rpage 1;    
static bit      PH65     @0x06@5:rpage 1;    
static bit      PH64     @0x06@4:rpage 1;    
static bit      PH63     @0x06@3:rpage 1;    
static bit      PH62     @0x06@2:rpage 1;    
static bit      PH61     @0x06@1:rpage 1;    
static bit      PH60     @0x06@0:rpage 1;    
/*P7PHCR Bits*/                              
static bit      PH77     @0x07@7:rpage 1;    
static bit      PH76     @0x07@6:rpage 1;    
static bit      PH75     @0x07@5:rpage 1;    
static bit      PH74     @0x07@4:rpage 1;    
static bit      PH73     @0x07@3:rpage 1;    
static bit      PH72     @0x07@2:rpage 1;    
static bit      PH71     @0x07@1:rpage 1;    
static bit      PH70     @0x07@0:rpage 1;    
/*P8PHCR Bits*/                              
static bit      PH87     @0x08@7:rpage 1;    
static bit      PH86     @0x08@6:rpage 1;    
static bit      PH85     @0x08@5:rpage 1;    
static bit      PH84     @0x08@4:rpage 1;    
static bit      PH83     @0x08@3:rpage 1;    
static bit      PH82     @0x08@2:rpage 1;    
static bit      PH81     @0x08@1:rpage 1;    
static bit      PH80     @0x08@0:rpage 1;    
/*P9PHCR Bits*/                              
static bit      PH97     @0x09@7:rpage 1;    
static bit      PH96     @0x09@6:rpage 1;    
static bit      PH95     @0x09@5:rpage 1;    
static bit      PH94     @0x09@4:rpage 1;    
static bit      PH93     @0x09@3:rpage 1;    
static bit      PH92     @0x09@2:rpage 1;    
static bit      PH91     @0x09@1:rpage 1;    
static bit      PH90     @0x09@0:rpage 1;
/*P5PLCR Bits*/                              
static bit      PL57     @0x0B@7:rpage 1;    
static bit      PL56     @0x0B@6:rpage 1;    
static bit      PL55     @0x0B@5:rpage 1;    
static bit      PL54     @0x0B@4:rpage 1;    
static bit      PL53     @0x0B@3:rpage 1;    
static bit      PL52     @0x0B@2:rpage 1;    
static bit      PL51     @0x0B@1:rpage 1;    
static bit      PL50     @0x0B@0:rpage 1;    
/*P6PLCR Bits*/                            
static bit      PL67     @0x0C@7:rpage 1;  
static bit      PL66     @0x0C@6:rpage 1;  
static bit      PL65     @0x0C@5:rpage 1;  
static bit      PL64     @0x0C@4:rpage 1;  
static bit      PL63     @0x0C@3:rpage 1;  
static bit      PL62     @0x0C@2:rpage 1;  
static bit      PL61     @0x0C@1:rpage 1;  
static bit      PL60     @0x0C@0:rpage 1;  
/*P7PLCR Bits*/                            
static bit      PL77     @0x0D@7:rpage 1;  
static bit      PL76     @0x0D@6:rpage 1;  
static bit      PL75     @0x0D@5:rpage 1;  
static bit      PL74     @0x0D@4:rpage 1;  
static bit      PL73     @0x0D@3:rpage 1;  
static bit      PL72     @0x0D@2:rpage 1;  
static bit      PL71     @0x0D@1:rpage 1;  
static bit      PL70     @0x0D@0:rpage 1;  
/*P8PLCR Bits*/                            
static bit      PL87     @0x0E@7:rpage 1;  
static bit      PL86     @0x0E@6:rpage 1;  
static bit      PL85     @0x0E@5:rpage 1;  
static bit      PL84     @0x0E@4:rpage 1;  
static bit      PL83     @0x0E@3:rpage 1;  
static bit      PL82     @0x0E@2:rpage 1;  
static bit      PL81     @0x0E@1:rpage 1;  
static bit      PL80     @0x0E@0:rpage 1;  
/*P9PLCR Bits*/                            
static bit      PL97     @0x0F@7:rpage 1;  
static bit      PL96     @0x0F@6:rpage 1;  
static bit      PL95     @0x0F@5:rpage 1;  
static bit      PL94     @0x0F@4:rpage 1;  
static bit      PL93     @0x0F@3:rpage 1;  
static bit      PL92     @0x0F@2:rpage 1;  
static bit      PL91     @0x0F@1:rpage 1;  
static bit      PL90     @0x0F@0:rpage 1;  
/*P5HD Bits*/                            
static bit      HD57     @0x11@7:rpage 1;  
static bit      HD56     @0x11@6:rpage 1;  
static bit      HD55     @0x11@5:rpage 1;  
static bit      HD54     @0x11@4:rpage 1;  
static bit      HD53     @0x11@3:rpage 1;  
static bit      HD52     @0x11@2:rpage 1;  
static bit      HD51     @0x11@1:rpage 1;  
static bit      HD50     @0x11@0:rpage 1;  
/*P6HD Bits*/                            
static bit      HD67     @0x12@7:rpage 1;
static bit      HD66     @0x12@6:rpage 1;
static bit      HD65     @0x12@5:rpage 1;
static bit      HD64     @0x12@4:rpage 1;
static bit      HD63     @0x12@3:rpage 1;
static bit      HD62     @0x12@2:rpage 1;
static bit      HD61     @0x12@1:rpage 1;
static bit      HD60     @0x12@0:rpage 1;
/*P7HD Bits*/                            
static bit      HD77     @0x13@7:rpage 1;
static bit      HD76     @0x13@6:rpage 1;
static bit      HD75     @0x13@5:rpage 1;
static bit      HD74     @0x13@4:rpage 1;
static bit      HD73     @0x13@3:rpage 1;
static bit      HD72     @0x13@2:rpage 1;
static bit      HD71     @0x13@1:rpage 1;
static bit      HD70     @0x13@0:rpage 1;
/*P8HD Bits*/                            
static bit      HD87     @0x14@7:rpage 1;
static bit      HD86     @0x14@6:rpage 1;
static bit      HD85     @0x14@5:rpage 1;
static bit      HD84     @0x14@4:rpage 1;
static bit      HD83     @0x14@3:rpage 1;
static bit      HD82     @0x14@2:rpage 1;
static bit      HD81     @0x14@1:rpage 1;
static bit      HD80     @0x14@0:rpage 1;
/*P9HD Bits*/                            
static bit      HD97     @0x15@7:rpage 1;
static bit      HD96     @0x15@6:rpage 1;
static bit      HD95     @0x15@5:rpage 1;
static bit      HD94     @0x15@4:rpage 1;
static bit      HD93     @0x15@3:rpage 1;
static bit      HD92     @0x15@2:rpage 1;
static bit      HD91     @0x15@1:rpage 1;
static bit      HD90     @0x15@0:rpage 1;
/*P5ODCR Bits*/                            
static bit      OD57     @0x17@7:rpage 1; 
static bit      OD56     @0x17@6:rpage 1; 
static bit      OD55     @0x17@5:rpage 1; 
static bit      OD54     @0x17@4:rpage 1; 
static bit      OD53     @0x17@3:rpage 1; 
static bit      OD52     @0x17@2:rpage 1; 
static bit      OD51     @0x17@1:rpage 1; 
static bit      OD50     @0x17@0:rpage 1; 
/*P6ODCR Bits*/                           
static bit      OD67     @0x18@7:rpage 1; 
static bit      OD66     @0x18@6:rpage 1; 
static bit      OD65     @0x18@5:rpage 1; 
static bit      OD64     @0x18@4:rpage 1; 
static bit      OD63     @0x18@3:rpage 1; 
static bit      OD62     @0x18@2:rpage 1; 
static bit      OD61     @0x18@1:rpage 1; 
static bit      OD60     @0x18@0:rpage 1; 
/*P7ODCR Bits*/                           
static bit      OD77     @0x19@7:rpage 1; 
static bit      OD76     @0x19@6:rpage 1; 
static bit      OD75     @0x19@5:rpage 1; 
static bit      OD74     @0x19@4:rpage 1; 
static bit      OD73     @0x19@3:rpage 1; 
static bit      OD72     @0x19@2:rpage 1; 
static bit      OD71     @0x19@1:rpage 1; 
static bit      OD70     @0x19@0:rpage 1; 
/*P8ODCR Bits*/                          
static bit      OD87     @0x1A@7:rpage 1; 
static bit      OD86     @0x1A@6:rpage 1; 
static bit      OD85     @0x1A@5:rpage 1; 
static bit      OD84     @0x1A@4:rpage 1; 
static bit      OD83     @0x1A@3:rpage 1; 
static bit      OD82     @0x1A@2:rpage 1; 
static bit      OD81     @0x1A@1:rpage 1; 
static bit      OD80     @0x1A@0:rpage 1; 
/*P9ODCR Bits*/                         
static bit      OD97     @0x1B@7:rpage 1; 
static bit      OD96     @0x1B@6:rpage 1; 
static bit      OD95     @0x1B@5:rpage 1; 
static bit      OD94     @0x1B@4:rpage 1; 
static bit      OD93     @0x1B@3:rpage 1; 
static bit      OD92     @0x1B@2:rpage 1; 
static bit      OD91     @0x1B@1:rpage 1; 
static bit      OD90     @0x1B@0:rpage 1; 
/*IRCS Bits*/                          
static bit      RCM1     @0x1D@5:rpage 1; 
static bit      RCM0     @0x1D@4:rpage 1; 
/*EEPCR Bits*/                         
static bit      RDB      @0x1F@7:rpage 1; 
static bit      WR       @0x1F@6:rpage 1; 
static bit      EEWE     @0x1F@5:rpage 1; 
static bit      EEDF     @0x1F@4:rpage 1; 
static bit      EEPC     @0x1F@3:rpage 1; 
/*I2CCR1 Bits*/                         
static bit      S_PEND   @0x23@7:rpage 1; 
static bit      IMS      @0x23@6:rpage 1; 
static bit      ISS      @0x23@5:rpage 1; 
static bit      STOP     @0x23@4:rpage 1; 
static bit      S_EMPTY  @0x23@3:rpage 1; 
static bit      ACK      @0x23@2:rpage 1; 
static bit      FULL     @0x23@1:rpage 1; 
static bit      EMPTY    @0x23@0:rpage 1;
/*I2CCR2 Bits*/                         
static bit      I2CBF    @0x24@7:rpage 1; 
static bit      GCEN     @0x24@6:rpage 1;  
static bit      I2CTS1   @0x24@3:rpage 1; 
static bit      I2CTS0   @0x24@2:rpage 1;  
static bit      I2CEN    @0x24@0:rpage 1;
/*PWMER Bits*/                         
static bit      PWMBE    @0x2A@1:rpage 1; 
static bit      PWMAE    @0x2A@0:rpage 1;    
/*TIMEN Bits*/                         
static bit      TBEN     @0x2B@1:rpage 1; 
static bit      TAEN     @0x2B@0:rpage 1; 
/*PWMACR Bits*/                         
static bit      TRCBA    @0x2F@3:rpage 1; 
/*PWMBCR Bits*/                         
static bit      TRCBB    @0x30@3:rpage 1; 
/*TACR Bits*/                         
static bit      TAP2     @0x32@2:rpage 1; 
static bit      TAP1     @0x32@1:rpage 1;  
static bit      TAP0     @0x32@0:rpage 1;
/*TBCR Bits*/                         
static bit      TBP2     @0x33@2:rpage 1; 
static bit      TBP1     @0x33@1:rpage 1;  
static bit      TBP0     @0x33@0:rpage 1;
/*DTxL Bits*/      
static bit      DTB1     @0x3C@3:rpage 1;       
static bit      DTB0     @0x3C@2:rpage 1;       
static bit      DTA1     @0x3C@1:rpage 1;       
static bit      DTA0     @0x3C@0:rpage 1;
