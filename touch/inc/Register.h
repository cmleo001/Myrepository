/****************************************************************************
 *	Title:       EM78F668N.H												*
 *	Target MCU:  EM78F668N					         	                    *
 *	Description: Register/bit definitions									*
 *	Company:     ELAN MICROELECTRONICS (SZ) LTD.       	                    *
 * 	Date:        2009-10-28                             	                *
 *	Version:     v1.0                                  	                    *
 ***************************************************************************/
//#ifndef __EM78F668N_H__
//#define	__EM78F668N_H__
#define  R0                 @0x00:rpage 0;//Indirect Address Register
#define  IAR                @0x00:rpage 0;//Indirect Address Register
#define  BSR                @0x01:rpage 0;//Bank selection control register
#define  PC                 @0x02:rpage 0;//Program Counter & Stack
#define  STATUS             @0x03:rpage 0;//Process Status Register
#define  RSR                @0x04:rpage 0;//RAM Select Register
#define  PORT5              @0x05:rpage 0;//I/O Port Address
#define  PORT6              @0x06:rpage 0;//I/O Port Address
#define  PORT7              @0x07:rpage 0;//I/O Port Address
#define  PORT8              @0x08:rpage 0;//I/O Port Address
#define  PORT9              @0x09:rpage 0;//I/O Port Address
#define  OMCR               @0x0B:rpage 0;//Operating mode control register
#define  ISR1               @0x0C:rpage 0;//Interrrupt status register1
#define  ISR2               @0x0D:rpage 0;//Interrrupt status register2
#define  ISR3               @0x0E:rpage 0;//Interrrupt status register3
#define  EIESCR             @0x10:rpage 0;//External interrupt edge select control register       
#define  WDTCR              @0x11:rpage 0;//WDT Control Register
#define  LVDCR              @0x12:rpage 0;//low voltage detector control regsiter
#define  TCCCR              @0x13:rpage 0;//Timer 2 Control Register
#define  TCC                @0x14:rpage 0;//TCC Data Buffer
#define  P5CR               @0x15:rpage 0;//Port5 control register
#define  P6CR               @0x16:rpage 0;//Port6 control register
#define  P7CR               @0x17:rpage 0;//Port7 control register
#define  P8CR               @0x18:rpage 0;//Port8 control register
#define  P9CR               @0x19:rpage 0;//Port9 control register
#define  IMR1               @0x1C:rpage 0;//Interrupt mask Register 1                 0
#define  IMR2               @0x1D:rpage 0;//Interrupt mask Register 2
#define  IMR3               @0x1E:rpage 0;//Interrupt mask Register 3
#define  P5WUCR             @0x20:rpage 0;//Port5 wake up control register
#define  P5WUECR            @0x21:rpage 0;//Port5 wake up EDGE control register
#define  P7WUCR             @0x22:rpage 0;//Port7 wake up control register
#define  P7WUECR            @0x23:rpage 0;//Port7 wake up EDGE control register
#define  ADCR1              @0x24:rpage 0;//ADC control register 1
#define  ADCR2              @0x25:rpage 0;//ADC control register 2
#define  ADICL              @0x26:rpage 0;//ADC input select low byte register
#define  ADDH               @0x29:rpage 0;//AD High 8-Bit Data Buffer
#define  ADDL               @0x2A:rpage 0;//AD Low 4-Bit Data Buffer
#define  SPICR              @0x2B:rpage 0;//SPI control register
#define  SPIS               @0x2C:rpage 0;//SPI Status register
#define  SPIRB              @0x2D:rpage 0;//SPI read buffer register
#define  SPIWB              @0x2E:rpage 0;//SPI writer buffer register
#define  WUCR1              @0x2F:rpage 0;//Wake up control register1
#define  URCR1              @0x32:rpage 0;//UART control regsiter1
#define  URCR2              @0x33:rpage 0;//UART control regsiter2
#define  URS                @0x34:rpage 0;//UART status regsiter
#define  URRD               @0x35:rpage 0;//UART receive data buffer regsiter
#define  URTD               @0x36:rpage 0;//UART transmit data buffer regsiter
#define  TBPTL              @0x37:rpage 0;//Table point register
#define  TBPTH              @0x38:rpage 0;//Table point register
#define  CMP1CR             @0x39:rpage 0;//Comparator 1 control register
#define  CMP2CR             @0x3C:rpage 0;//Comparator 2 control register
#define  CPIRLCON           @0x43:rpage 0;//Comparator internal reference level control register
#define  TC1CR              @0x48:rpage 0;//timer 1 control register
#define  TCR1DA             @0x49:rpage 0;//Timer 1 data buffer A
#define  TCR1DB             @0x4A:rpage 0;//Timer 1 data buffer B
#define  TC2CR              @0x4B:rpage 0;//Timer 2 control register
#define  TCR2DH             @0x4C:rpage 0;//Timer 2 high byte data buffer register
#define  TCR2DL             @0x4D:rpage 0;//Timer 2 low byte data buffer register
#define  TC3CR              @0x4E:rpage 0;//Timer 3 control register
#define  TCR3D              @0x4F:rpage 0;//Timer 3 duty buffer register
// bank 1
#define  P5PHCR             @0x05:rpage 1;//Port5 pull high control register
#define  P6PHCR             @0x06:rpage 1;//Port6 pull high control register
#define  P7PHCR             @0x07:rpage 1;//Port7 pull high control register
#define  P8PHCR             @0x08:rpage 1;//Port8 pull high control register
#define  P9PHCR             @0x09:rpage 1;//Port9 pull high control register
#define  P5PLCR             @0x0B:rpage 1;//Port5 pull low control register
#define  P6PLCR             @0x0C:rpage 1;//Port6 pull low control register
#define  P7PLCR             @0x0D:rpage 1;//Port7 pull low control register
#define  P8PLCR             @0x0E:rpage 1;//Port8 pull low control register
#define  P9PLCR             @0x0F:rpage 1;//Port9 pull low control register
#define  P5PHD              @0x11:rpage 1;//Port5 pull high drive/sink control register
#define  P6PHD              @0x12:rpage 1;//Port6 pull high drive/sink control register
#define  P7PHD              @0x13:rpage 1;//Port7 pull high drive/sink control register
#define  P8PHD              @0x14:rpage 1;//Port8 pull high drive/sink control register
#define  P9PHD              @0x15:rpage 1;//Port9 pull high drive/sink control register
#define  P5ODCR             @0x17:rpage 1;//Port5 open drain control register
#define  P6ODCR             @0x18:rpage 1;//Port6 open drain control register
#define  P7ODCR             @0x19:rpage 1;//Port7 open drain control register
#define  P8ODCR             @0x1A:rpage 1;//Port8 open drain control register
#define  P9ODCR             @0x1B:rpage 1;//Port9 open drain control register
#define  IRCS               @0x1D:rpage 1;//IRC frequency selection register
#define  EEPCR              @0x1F:rpage 1;//EEPROM control register
#define  EEPA               @0x20:rpage 1;//EEPROM ADDR
#define  EEPD               @0x21:rpage 1;//EEPROM DATA
#define  I2CCR1             @0x23:rpage 1;//I2C status and control register1
#define  I2CCR2             @0x24:rpage 1;//I2C status and control register2
#define  I2CSA              @0x25:rpage 1;//I2C Slave address register
#define  I2CDA              @0x26:rpage 1;//I2C Device address register
#define  I2CDB              @0x27:rpage 1;//I2C data buffer register
#define  I2CA               @0x28:rpage 1;//I2C data buffer register
#define  PWMER              @0x2A:rpage 1;//PWM enable control register
#define  TIMEN              @0x2B:rpage 1;//Timer/PWM enable control register
#define  PWMACR             @0x2F:rpage 1;//PWM A control register
#define  PWMBCR             @0x30:rpage 1;//PWM B control register
#define  TACR               @0x32:rpage 1;//Timer A control register
#define  TBCR               @0x33:rpage 1;//Timer B control register
#define  TAPRDH             @0x35:rpage 1;//Timer A Period buffer register
#define  TBPRDH             @0x36:rpage 1;//Timer B Period buffer register
#define  TADTH              @0x38:rpage 1;//Timer A duty buffer register
#define  TBDTH              @0x39:rpage 1;//Timer B duty buffer register
#define  PRDxL              @0x3B:rpage 1;//PWM A/B/C Period buffer low bits register
#define  DTxL               @0x3C:rpage 1;//PWM1/2 duty buffer low bits register

//;---------------------------------------------------------------------------------------
/*BSR Bits*/
#define      SBS0    @0x01@4:rpage 0;
#define      GBS0    @0x01@0:rpage 0;
/*R3 Bits*/
#define      T       @0x03@4:rpage 0;
#define      P       @0x03@3:rpage 0;
#define      Z       @0x03@2:rpage 0;        
#define      DC      @0x03@1:rpage 0;
#define      C       @0x03@0:rpage 0;
/*R4 Bits*/
#define      RSR7    @0x04@7:rpage 0;
#define      RSR6    @0x04@6:rpage 0;
#define      RSR5    @0x04@5:rpage 0;
#define      RSR4    @0x04@4:rpage 0;
#define      RSR3    @0x04@3:rpage 0;
#define      RSR2    @0x04@2:rpage 0;
#define      RSR1    @0x04@1:rpage 0;
#define      RSR0    @0x04@0:rpage 0;
/*R5 Bits*/
#define      P57     @0x05@7:rpage 0;
#define      P56     @0x05@6:rpage 0;
#define      P55     @0x05@5:rpage 0;
#define      P54     @0x05@4:rpage 0;
#define      P53     @0x05@3:rpage 0;
#define      P52     @0x05@2:rpage 0;
#define      P51     @0x05@1:rpage 0;
#define      P50     @0x05@0:rpage 0;
/*R6 Bits*/
#define      P67     @0x06@7:rpage 0;
#define      P66     @0x06@6:rpage 0;
#define      P65     @0x06@5:rpage 0;
#define      P64     @0x06@4:rpage 0;
#define      P63     @0x06@3:rpage 0;
#define      P62     @0x06@2:rpage 0;
#define      P61     @0x06@1:rpage 0;
#define      P60     @0x06@0:rpage 0;
/*R7  Bits*/
#define      P77     @0x07@7:rpage 0;
#define      P76     @0x07@6:rpage 0;
#define      P75     @0x07@5:rpage 0;
#define      P74     @0x07@4:rpage 0;
#define      P73     @0x07@3:rpage 0;
#define      P72     @0x07@2:rpage 0;
#define      P71     @0x07@1:rpage 0;
#define      P70     @0x07@0:rpage 0;
/*R8  Bits*/
#define      P87     @0x08@7:rpage 0;
#define      P86     @0x08@6:rpage 0;
#define      P85     @0x08@5:rpage 0;
#define      P84     @0x08@4:rpage 0;
#define      P83     @0x08@3:rpage 0;
#define      P82     @0x08@2:rpage 0;
#define      P81     @0x08@1:rpage 0;
#define      P80     @0x08@0:rpage 0;
/*R9  Bits*/                            
#define      P97     @0x09@7:rpage 0;
#define      P96     @0x09@6:rpage 0;
#define      P95     @0x09@5:rpage 0;
#define      P94     @0x09@4:rpage 0;
#define      P93     @0x09@3:rpage 0;
#define      P92     @0x09@2:rpage 0;
#define      P91     @0x09@1:rpage 0;
#define      P90     @0x09@0:rpage 0;
/*OMCR Bits */
#define      CPUS    @0x0B@7:rpage 0;
#define      IDLE    @0x0B@6:rpage 0;
#define      TC1SS   @0x0B@5:rpage 0;
#define      TC2SS   @0x0B@4:rpage 0;
#define      TC3SS   @0x0B@3:rpage 0; 
#define      TASS    @0x0B@2:rpage 0;
#define      TBSS    @0x0B@1:rpage 0;    
/*ISR1 Bits*/
#define      LVDIF   @0x0C@7:rpage 0;
#define      ADIF    @0x0C@6:rpage 0;
#define      SPIF    @0x0C@5:rpage 0;
#define      PWMBIF  @0x0C@4:rpage 0;     
#define      PWMAIF  @0x0C@3:rpage 0;     
#define      EXIF    @0x0C@2:rpage 0;     
#define      ICIF    @0x0C@1:rpage 0;     
#define      TCIF    @0x0C@0:rpage 0; 
/*ISR2 Bits*/
#define      CMP2IF  @0x0D@7:rpage 0;
#define      CMP1IF  @0x0D@6:rpage 0;
#define      TC3IF   @0x0D@5:rpage 0;
#define      TC2IF   @0x0D@4:rpage 0;
#define      TC1IF   @0x0D@3:rpage 0;
#define      UERRIF  @0x0D@2:rpage 0;     
#define      RBFF    @0x0D@1:rpage 0; 
#define      TBEF    @0x0D@0:rpage 0;
/*ISR3 Bits*/
#define      I2CSTPIF   @0x0E@3:rpage 0;  
#define      I2CRIF     @0x0E@1:rpage 0;  
 #define     I2CTIF     @0x0E@0:rpage 0;
/*EIESCR Bits*/
#define      EIES    @0x10@0:rpage 0;
/*WDTCR Bits*/                               
#define      WDTE    @0x11@7:rpage 0;    
#define      EIS     @0x11@6:rpage 0;
#define      EINT    @0x11@5:rpage 0;    
#define      PSWE    @0x11@3:rpage 0;    
#define      PSW2    @0x11@2:rpage 0;    
#define      PSW1    @0x11@1:rpage 0;    
#define      PSW0    @0x11@0:rpage 0;    
/*LVDCR Bits*/                              
#define      LVDEN   @0x12@3:rpage 0;    
#define      LVD     @0x12@2:rpage 0;    
#define      LVD1    @0x12@1:rpage 0;    
#define      LVD2    @0x12@0:rpage 0;    
/*TCCCR Bits*/                               
#define      TCCS    @0x13@6:rpage 0;     
#define      TS      @0x13@5:rpage 0;    
#define      TE      @0x13@4:rpage 0;    
#define      PSTE    @0x13@3:rpage 0;    
#define      PST2    @0x13@2:rpage 0;    
#define      PST1    @0x13@1:rpage 0;    
#define      PST0    @0x13@0:rpage 0;   
/*P5CR Bits*/                               
#define      P57CR    @0x15@7:rpage 0;     
#define      P56CR    @0x15@6:rpage 0;     
#define      P55CR    @0x15@5:rpage 0;     
#define      P54CR    @0x15@4:rpage 0;     
#define      P53CR    @0x15@3:rpage 0;     
#define      P52CR    @0x15@2:rpage 0;     
#define      P51CR    @0x15@1:rpage 0;
#define      P50CR    @0x15@0:rpage 0;     
/*P6CR Bits*/                              
#define      P67CR    @0x16@7:rpage 0;  
#define      P66CR    @0x16@6:rpage 0;  
#define      P65CR    @0x16@5:rpage 0;  
#define      P64CR    @0x16@4:rpage 0;  
#define      P63CR    @0x16@3:rpage 0;  
#define      P62CR    @0x16@2:rpage 0;  
#define      P61CR    @0x16@1:rpage 0;  
#define      P60CR    @0x16@0:rpage 0;  
/*P7CR Bits*/                              
#define      P77CR    @0x17@7:rpage 0;  
#define      P76CR    @0x17@6:rpage 0;  
#define      P75CR    @0x17@5:rpage 0;  
#define      P74CR    @0x17@4:rpage 0;  
#define      P73CR    @0x17@3:rpage 0;  
#define      P72CR    @0x17@2:rpage 0;  
#define      P71CR    @0x17@1:rpage 0;  
#define      P70CR    @0x17@0:rpage 0;  
/*P8CR Bits*/                              
#define      P87CR    @0x18@7:rpage 0;  
#define      P86CR    @0x18@6:rpage 0;  
#define      P85CR    @0x18@5:rpage 0;  
#define      P84CR    @0x18@4:rpage 0;  
#define      P83CR    @0x18@3:rpage 0;  
#define      P82CR    @0x18@2:rpage 0;  
#define      P81CR    @0x18@1:rpage 0;  
#define      P80CR    @0x18@0:rpage 0;  
/*P9CR Bits*/                              
#define      P97CR    @0x19@7:rpage 0;  
#define      P96CR    @0x19@6:rpage 0;  
#define      P95CR    @0x19@5:rpage 0;  
#define      P94CR    @0x19@4:rpage 0;  
#define      P93CR    @0x19@3:rpage 0;  
#define      P92CR    @0x19@2:rpage 0;  
#define      P91CR    @0x19@1:rpage 0;  
#define      P90CR    @0x19@0:rpage 0;  
/*IMR1 Bits*/                              
#define      LVDIE    @0x1C@7:rpage 0;  
#define      ADIE     @0x1C@6:rpage 0;  
#define      SPIE     @0x1C@5:rpage 0;  
#define      PWMBIE   @0x1C@4:rpage 0;  
#define      PWMAIE   @0x1C@3:rpage 0;  
#define      EXIE     @0x1C@2:rpage 0;  
#define      ICIE     @0x1C@1:rpage 0;  
#define      TCIE     @0x1C@0:rpage 0;  
/*IMR2 Bits*/                              
#define      CMP2IE   @0x1D@7:rpage 0;  
#define      CMP1IE   @0x1D@6:rpage 0;  
#define      TC3IE    @0x1D@5:rpage 0;  
#define      TC2IE    @0x1D@4:rpage 0;  
#define      TC1IE    @0x1D@3:rpage 0;  
#define      UERRIE   @0x1D@2:rpage 0;  
#define      URIE     @0x1D@1:rpage 0;  
#define      UTIE     @0x1D@0:rpage 0;   
/*IMR3 Bits*/                              
#define      I2CSTPIE @0x1E@3:rpage 0;  
#define      I2CRIE   @0x1E@1:rpage 0;  
#define      I2CTIE   @0x1E@0:rpage 0;  
/*P5WUCR Bits*/                              
#define      WU_P57   @0x20@7:rpage 0;  
#define      WU_P56   @0x20@6:rpage 0;  
#define      WU_P55   @0x20@5:rpage 0;  
#define      WU_P54   @0x20@4:rpage 0;  
#define      WU_P53   @0x20@3:rpage 0;  
#define      WU_P52   @0x20@2:rpage 0;  
#define      WU_P51   @0x20@1:rpage 0;  
#define      WU_P50   @0x20@0:rpage 0;   
/*P5WUECR Bits*/                              
#define      WUE_P57  @0x21@7:rpage 0;  
#define      WUE_P56  @0x21@6:rpage 0;  
#define      WUE_P55  @0x21@5:rpage 0;  
#define      WUE_P54  @0x21@4:rpage 0;  
#define      WUE_P53  @0x21@3:rpage 0;  
#define      WUE_P52  @0x21@2:rpage 0;  
#define      WUE_P51  @0x21@1:rpage 0;  
#define      WUE_P50  @0x21@0:rpage 0;    
/*P7WUCR Bits*/                              
#define      WU_P77   @0x22@7:rpage 0;  
#define      WU_P76   @0x22@6:rpage 0;  
#define      WU_P75   @0x22@5:rpage 0;  
#define      WU_P74   @0x22@4:rpage 0;  
#define      WU_P73   @0x22@3:rpage 0;  
#define      WU_P72   @0x22@2:rpage 0;  
#define      WU_P71   @0x22@1:rpage 0;  
#define      WU_P70   @0x22@0:rpage 0;   
/*P7WUECR Bits*/                              
#define      WUE_P77  @0x23@7:rpage 0;  
#define      WUE_P76  @0x23@6:rpage 0;  
#define      WUE_P75  @0x23@5:rpage 0;  
#define      WUE_P74  @0x23@4:rpage 0;  
#define      WUE_P73  @0x23@3:rpage 0;  
#define      WUE_P72  @0x23@2:rpage 0;  
#define      WUE_P71  @0x23@1:rpage 0;  
#define      WUE_P70  @0x23@0:rpage 0;   
/*ADCR1 Bits*/                             
#define      VREFS    @0x24@7:rpage 0;       
#define      ADRUN	 @0x24@6:rpage 0;      
#define      ADPD     @0x24@5:rpage 0;      
#define      ADIS2    @0x24@2:rpage 0;      
#define      ADIS1    @0x24@1:rpage 0;      
#define      ADIS0    @0x24@0:rpage 0;      
/*ADCR2 Bits*/                              
#define      CALI     @0x25@7:rpage 0;   
#define      SIGN     @0x25@6:rpage 0;   
#define      VOF2     @0x25@5:rpage 0;   
#define      VOF1     @0x25@4:rpage 0;   
#define      VOF0     @0x25@3:rpage 0;   
#define      CKR2     @0x25@2:rpage 0;   
#define      CKR1     @0x25@1:rpage 0;   
#define      CKR0     @0x25@0:rpage 0;   
/*ADICL Bits*/                           
#define      ADE7     @0x26@7:rpage 0;
#define      ADE6     @0x26@6:rpage 0;
#define      ADE5     @0x26@5:rpage 0;
#define      ADE4     @0x26@4:rpage 0;
#define      ADE3     @0x26@3:rpage 0;
#define      ADE2     @0x26@2:rpage 0;
#define      ADE1     @0x26@1:rpage 0;
#define      ADE0     @0x26@0:rpage 0;
/*SPICR Bits*/                           
#define      CES      @0x2B@7:rpage 0;
#define      SPI_E    @0x2B@6:rpage 0;
#define      SRO      @0x2B@5:rpage 0;
#define      SSE      @0x2B@4:rpage 0;
#define      SDOC     @0x2B@3:rpage 0;
#define      SBRS2    @0x2B@2:rpage 0;
#define      SBRS1    @0x2B@1:rpage 0;
#define      SBRS0    @0x2B@0:rpage 0;
/*SPIS Bits*/                           
#define      DORD     @0x2C@7:rpage 0;
#define      TD1      @0x2C@6:rpage 0;
#define      TD0      @0x2C@5:rpage 0;
#define      OD3      @0x2C@3:rpage 0;
#define      OD4      @0x2C@2:rpage 0;
#define      RBF      @0x2C@0:rpage 0;
/*WUCR1 Bits*/                           
#define      SPIWE    @0x2F@6:rpage 0;
#define      LVDWE    @0x2F@5:rpage 0;
#define      ICWE     @0x2F@4:rpage 0;
#define      ADWE     @0x2F@3:rpage 0;
#define      CMP2WE   @0x2F@2:rpage 0;
#define      CMP1WE   @0x2F@1:rpage 0;
#define      EXWE     @0x2F@0:rpage 0;
/*URCR1 Bits*/                           
#define      URTD8    @0x32@7:rpage 0;
#define      UMODE1   @0x32@6:rpage 0;
#define      UMODE0   @0x32@5:rpage 0;
#define      BRATE2   @0x32@4:rpage 0;
#define      BRATE1   @0x32@3:rpage 0;
#define      BRATE0   @0x32@2:rpage 0;
#define      UTBE     @0x32@1:rpage 0;
#define      TXE      @0x32@0:rpage 0;
/*URCR2 Bits*/                           
#define      SBIM1    @0x33@5:rpage 0;
#define      SBIM0    @0x33@4:rpage 0;
#define      UINVEN   @0x33@3:rpage 0;
/*URS Bits*/                           
#define      URRD8    @0x34@7:rpage 0;
#define      EVEN     @0x34@6:rpage 0;
#define      PRE      @0x34@5:rpage 0;
#define      PRERR    @0x34@4:rpage 0;
#define      OVERR    @0x34@3:rpage 0;
#define      FMERR    @0x34@2:rpage 0;
#define      URBF     @0x34@1:rpage 0;
#define      RXE      @0x34@0:rpage 0;
/*CMP1CR Bits*/                           
#define      C1RS     @0x39@7:rpage 0;
#define      CP1OUT   @0x39@6:rpage 0;
#define      CMP1COS1 @0x39@5:rpage 0;
#define      CMP1COS0 @0x39@4:rpage 0;
#define      CP1NS    @0x39@3:rpage 0;
#define      CP1PS    @0x39@2:rpage 0;
#define      CP1NRE   @0x39@1:rpage 0;
#define      CP1NRDT  @0x39@0:rpage 0;
/*CMP2CR Bits*/                                 
#define      C2RS     @0x3C@7:rpage 0;       
#define      CP2OUT   @0x3C@6:rpage 0;       
#define      CMP2COS1 @0x3C@5:rpage 0;       
#define      CMP2COS0 @0x3C@4:rpage 0;       
#define      CP2NS    @0x3C@3:rpage 0;       
#define      CP2PS    @0x3C@2:rpage 0;       
#define      CP2NRE   @0x3C@1:rpage 0;       
#define      CP2NRDT  @0x3C@0:rpage 0;       
/*CPIRLCON Bits*/                                 
#define      BG2OUT   @0x43@7:rpage 0;       
#define      C2IRL2   @0x43@6:rpage 0;       
#define      C2IRL1   @0x43@5:rpage 0;       
#define      C2IRL0   @0x43@4:rpage 0;       
#define      BG1OUT   @0x43@3:rpage 0;       
#define      C1IRL2   @0x43@2:rpage 0;       
#define      C1IRL1   @0x43@1:rpage 0;       
#define      C1IRL0   @0x43@0:rpage 0;       
/*TC1CR Bits*/                          
#define      TC1CAP   @0x48@7:rpage 0;  
#define      TC1S     @0x48@6:rpage 0;  
#define      TC1CK1   @0x48@5:rpage 0;  
#define      TC1CK0   @0x48@4:rpage 0;  
#define      TC1M     @0x48@3:rpage 0;  
#define      TC1ES    @0x48@2:rpage 0;  
 /*TC2CR Bits*/                            
#define      TC2ES    @0x4B@5:rpage 0;  
#define      TC2M     @0x4B@4:rpage 0;  
#define      TC2S     @0x4B@3:rpage 0;  
#define      TC2CK2   @0x4B@2:rpage 0;  
#define      TC2CK1   @0x4B@1:rpage 0;  
#define      TC2CK0   @0x4B@0:rpage 0;  
/*TC3CR Bits*/                          
#define      TC3FF1   @0x4E@7:rpage 0;  
#define      TC3FF0   @0x4E@6:rpage 0;  
#define      TC3S     @0x4E@5:rpage 0;  
#define      TC3CK2   @0x4E@4:rpage 0;  
#define      TC3CK1   @0x4E@3:rpage 0;  
#define      TC3CK0   @0x4E@2:rpage 0;  
#define      TC3M1    @0x4E@1:rpage 0;  
#define      TC3M0    @0x4E@0:rpage 0;  
//BANK 1
/*P5PHCR Bits*/                          
#define      PH57     @0x05@7:rpage 1;  
#define      PH56     @0x05@6:rpage 1;  
#define      PH55     @0x05@5:rpage 1;  
#define      PH54     @0x05@4:rpage 1;  
#define      PH53     @0x05@3:rpage 1;  
#define      PH52     @0x05@2:rpage 1;  
#define      PH51     @0x05@1:rpage 1;  
#define      PH50     @0x05@0:rpage 1;  
/*P6PHCR Bits*/                              
#define      PH67     @0x06@7:rpage 1;    
#define      PH66     @0x06@6:rpage 1;    
#define      PH65     @0x06@5:rpage 1;    
#define      PH64     @0x06@4:rpage 1;    
#define      PH63     @0x06@3:rpage 1;    
#define      PH62     @0x06@2:rpage 1;    
#define      PH61     @0x06@1:rpage 1;    
#define      PH60     @0x06@0:rpage 1;    
/*P7PHCR Bits*/                              
#define      PH77     @0x07@7:rpage 1;    
#define      PH76     @0x07@6:rpage 1;    
#define      PH75     @0x07@5:rpage 1;    
#define      PH74     @0x07@4:rpage 1;    
#define      PH73     @0x07@3:rpage 1;    
#define      PH72     @0x07@2:rpage 1;    
#define      PH71     @0x07@1:rpage 1;    
#define      PH70     @0x07@0:rpage 1;    
/*P8PHCR Bits*/                              
#define      PH87     @0x08@7:rpage 1;    
#define      PH86     @0x08@6:rpage 1;    
#define      PH85     @0x08@5:rpage 1;    
#define      PH84     @0x08@4:rpage 1;    
#define      PH83     @0x08@3:rpage 1;    
#define      PH82     @0x08@2:rpage 1;    
#define      PH81     @0x08@1:rpage 1;    
#define      PH80     @0x08@0:rpage 1;    
/*P9PHCR Bits*/                              
#define      PH97     @0x09@7:rpage 1;    
#define      PH96     @0x09@6:rpage 1;    
#define      PH95     @0x09@5:rpage 1;    
#define      PH94     @0x09@4:rpage 1;    
#define      PH93     @0x09@3:rpage 1;    
#define      PH92     @0x09@2:rpage 1;    
#define      PH91     @0x09@1:rpage 1;    
#define      PH90     @0x09@0:rpage 1;
/*P5PLCR Bits*/                              
#define      PL57     @0x0B@7:rpage 1;    
#define      PL56     @0x0B@6:rpage 1;    
#define      PL55     @0x0B@5:rpage 1;    
#define      PL54     @0x0B@4:rpage 1;    
#define      PL53     @0x0B@3:rpage 1;    
#define      PL52     @0x0B@2:rpage 1;    
#define      PL51     @0x0B@1:rpage 1;    
#define      PL50     @0x0B@0:rpage 1;    
/*P6PLCR Bits*/                            
#define      PL67     @0x0C@7:rpage 1;  
#define      PL66     @0x0C@6:rpage 1;  
#define      PL65     @0x0C@5:rpage 1;  
#define      PL64     @0x0C@4:rpage 1;  
#define      PL63     @0x0C@3:rpage 1;  
#define      PL62     @0x0C@2:rpage 1;  
#define      PL61     @0x0C@1:rpage 1;  
#define      PL60     @0x0C@0:rpage 1;  
/*P7PLCR Bits*/                            
#define      PL77     @0x0D@7:rpage 1;  
#define      PL76     @0x0D@6:rpage 1;  
#define      PL75     @0x0D@5:rpage 1;  
#define      PL74     @0x0D@4:rpage 1;  
#define      PL73     @0x0D@3:rpage 1;  
#define      PL72     @0x0D@2:rpage 1;  
#define      PL71     @0x0D@1:rpage 1;  
#define      PL70     @0x0D@0:rpage 1;  
/*P8PLCR Bits*/                            
#define      PL87     @0x0E@7:rpage 1;  
#define      PL86     @0x0E@6:rpage 1;  
#define      PL85     @0x0E@5:rpage 1;  
#define      PL84     @0x0E@4:rpage 1;  
#define      PL83     @0x0E@3:rpage 1;  
#define      PL82     @0x0E@2:rpage 1;  
#define      PL81     @0x0E@1:rpage 1;  
#define      PL80     @0x0E@0:rpage 1;  
/*P9PLCR Bits*/                            
#define      PL97     @0x0F@7:rpage 1;  
#define      PL96     @0x0F@6:rpage 1;  
#define      PL95     @0x0F@5:rpage 1;  
#define      PL94     @0x0F@4:rpage 1;  
#define      PL93     @0x0F@3:rpage 1;  
#define      PL92     @0x0F@2:rpage 1;  
#define      PL91     @0x0F@1:rpage 1;  
#define      PL90     @0x0F@0:rpage 1;  
/*P5HD Bits*/                            
#define      HD57     @0x11@7:rpage 1;  
#define      HD56     @0x11@6:rpage 1;  
#define      HD55     @0x11@5:rpage 1;  
#define      HD54     @0x11@4:rpage 1;  
#define      HD53     @0x11@3:rpage 1;  
#define      HD52     @0x11@2:rpage 1;  
#define      HD51     @0x11@1:rpage 1;  
#define      HD50     @0x11@0:rpage 1;  
/*P6HD Bits*/                            
#define      HD67     @0x12@7:rpage 1;
#define      HD66     @0x12@6:rpage 1;
#define      HD65     @0x12@5:rpage 1;
#define      HD64     @0x12@4:rpage 1;
#define      HD63     @0x12@3:rpage 1;
#define      HD62     @0x12@2:rpage 1;
#define      HD61     @0x12@1:rpage 1;
#define      HD60     @0x12@0:rpage 1;
/*P7HD Bits*/                            
#define      HD77     @0x13@7:rpage 1;
#define      HD76     @0x13@6:rpage 1;
#define      HD75     @0x13@5:rpage 1;
#define      HD74     @0x13@4:rpage 1;
#define      HD73     @0x13@3:rpage 1;
#define      HD72     @0x13@2:rpage 1;
#define      HD71     @0x13@1:rpage 1;
#define      HD70     @0x13@0:rpage 1;
/*P8HD Bits*/                            
#define      HD87     @0x14@7:rpage 1;
#define      HD86     @0x14@6:rpage 1;
#define      HD85     @0x14@5:rpage 1;
#define      HD84     @0x14@4:rpage 1;
#define      HD83     @0x14@3:rpage 1;
#define      HD82     @0x14@2:rpage 1;
#define      HD81     @0x14@1:rpage 1;
#define      HD80     @0x14@0:rpage 1;
/*P9HD Bits*/                            
#define      HD97     @0x15@7:rpage 1;
#define      HD96     @0x15@6:rpage 1;
#define      HD95     @0x15@5:rpage 1;
#define      HD94     @0x15@4:rpage 1;
#define      HD93     @0x15@3:rpage 1;
#define      HD92     @0x15@2:rpage 1;
#define      HD91     @0x15@1:rpage 1;
#define      HD90     @0x15@0:rpage 1;
/*P5ODCR Bits*/                            
#define      OD57     @0x17@7:rpage 1; 
#define      OD56     @0x17@6:rpage 1; 
#define      OD55     @0x17@5:rpage 1; 
#define      OD54     @0x17@4:rpage 1; 
#define      OD53     @0x17@3:rpage 1; 
#define      OD52     @0x17@2:rpage 1; 
#define      OD51     @0x17@1:rpage 1; 
#define      OD50     @0x17@0:rpage 1; 
/*P6ODCR Bits*/                           
#define      OD67     @0x18@7:rpage 1; 
#define      OD66     @0x18@6:rpage 1; 
#define      OD65     @0x18@5:rpage 1; 
#define      OD64     @0x18@4:rpage 1; 
#define      OD63     @0x18@3:rpage 1; 
#define      OD62     @0x18@2:rpage 1; 
#define      OD61     @0x18@1:rpage 1; 
#define      OD60     @0x18@0:rpage 1; 
/*P7ODCR Bits*/                           
#define      OD77     @0x19@7:rpage 1; 
#define      OD76     @0x19@6:rpage 1; 
#define      OD75     @0x19@5:rpage 1; 
#define      OD74     @0x19@4:rpage 1; 
#define      OD73     @0x19@3:rpage 1; 
#define      OD72     @0x19@2:rpage 1; 
#define      OD71     @0x19@1:rpage 1; 
#define      OD70     @0x19@0:rpage 1; 
/*P8ODCR Bits*/                          
#define      OD87     @0x1A@7:rpage 1; 
#define      OD86     @0x1A@6:rpage 1; 
#define      OD85     @0x1A@5:rpage 1; 
#define      OD84     @0x1A@4:rpage 1; 
#define      OD83     @0x1A@3:rpage 1; 
#define      OD82     @0x1A@2:rpage 1; 
#define      OD81     @0x1A@1:rpage 1; 
#define      OD80     @0x1A@0:rpage 1; 
/*P9ODCR Bits*/                         
#define      OD97     @0x1B@7:rpage 1; 
#define      OD96     @0x1B@6:rpage 1; 
#define      OD95     @0x1B@5:rpage 1; 
#define      OD94     @0x1B@4:rpage 1; 
#define      OD93     @0x1B@3:rpage 1; 
#define      OD92     @0x1B@2:rpage 1; 
#define      OD91     @0x1B@1:rpage 1; 
#define      OD90     @0x1B@0:rpage 1; 
/*IRCS Bits*/                          
#define      RCM1     @0x1D@5:rpage 1; 
#define      RCM0     @0x1D@4:rpage 1; 
/*EEPCR Bits*/                         
#define      RDB      @0x1F@7:rpage 1; 
#define      WR       @0x1F@6:rpage 1; 
#define      EEWE     @0x1F@5:rpage 1; 
#define      EEDF     @0x1F@4:rpage 1; 
#define      EEPC     @0x1F@3:rpage 1; 
/*I2CCR1 Bits*/                         
#define      S_PEND   @0x23@7:rpage 1; 
#define      IMS      @0x23@6:rpage 1; 
#define      ISS      @0x23@5:rpage 1; 
#define      STOP     @0x23@4:rpage 1; 
#define      S_EMPTY  @0x23@3:rpage 1; 
#define      ACK      @0x23@2:rpage 1; 
#define      FULL     @0x23@1:rpage 1; 
#define      EMPTY    @0x23@0:rpage 1;
/*I2CCR2 Bits*/                         
#define      I2CBF    @0x24@7:rpage 1; 
#define      GCEN     @0x24@6:rpage 1;  
#define      I2CTS1   @0x24@3:rpage 1; 
#define      I2CTS0   @0x24@2:rpage 1;  
#define      I2CEN    @0x24@0:rpage 1;
/*PWMER Bits*/                         
#define      PWMBE    @0x2A@1:rpage 1; 
#define      PWMAE    @0x2A@0:rpage 1;    
/*TIMEN Bits*/                         
#define      TBEN     @0x2B@1:rpage 1; 
#define      TAEN     @0x2B@0:rpage 1; 
/*PWMACR Bits*/                         
#define      TRCBA    @0x2F@3:rpage 1; 
/*PWMBCR Bits*/                         
#define      TRCBB    @0x30@3:rpage 1; 
/*TACR Bits*/                         
#define      TAP2     @0x32@2:rpage 1; 
#define      TAP1     @0x32@1:rpage 1;  
#define      TAP0     @0x32@0:rpage 1;
/*TBCR Bits*/                         
#define      TBP2     @0x33@2:rpage 1; 
#define      TBP1     @0x33@1:rpage 1;  
#define      TBP0     @0x33@0:rpage 1;
/*DTxL Bits*/      
#define      DTB1     @0x3C@3:rpage 1;       
#define      DTB0     @0x3C@2:rpage 1;       
#define      DTA1     @0x3C@1:rpage 1;       
#define      DTA0     @0x3C@0:rpage 1;




