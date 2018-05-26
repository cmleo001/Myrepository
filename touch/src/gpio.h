#ifndef _GPIO_H_
#define _GPIO_H_





/////////////////////////////////
// Define all Function I/O pin
/////////////////////////////////

//P50
#define		PIN_P50					PP50
#define		PIN_P50_IO_OUTPUT		{P50_IO_OUTPUT;}
#define		PIN_P50_IO_INPUT		{P50_IO_INPUT;}
#define		PIN_P50_READ			P50_READ
#define		vP50Low()				{P50_LOW;}
#define		vP50High()				{P50_HIGH;}

//P51	//SDA_OTP, Hardware I2C

//P52
#define		PIN_P52					PP52
#define		PIN_P52_IO_OUTPUT		{P52_IO_OUTPUT;}
#define		PIN_P52_IO_INPUT		{P52_IO_INPUT;}
#define		PIN_P52_READ			P52_READ
#define		vP52Low()				{P52_LOW;}
#define		vP52High()				{P52_HIGH;}

//P53	//SCK_OTP, Hardware I2C

//P54
		//XIN
//P55
		//XOUT
//P56
#define		PIN_P56					PP56
#define		PIN_P56_IO_OUTPUT		{P56_IO_OUTPUT;}
#define		PIN_P56_IO_INPUT		{P56_IO_INPUT;}
#define		PIN_P56_READ			P56_READ
#define		vP56Low()				{P56_LOW;}
#define		vP56High()				{P56_HIGH;}
#define		vP56Flash()				{PORT5^=PP56;}
#define		vP56Pulse()				{P56_HIGH;P56_LOW;}

//P57
#define		PIN_P57					PP57
#define		PIN_P57_IO_OUTPUT		{P57_IO_OUTPUT;}
#define		PIN_P57_IO_INPUT		{P57_IO_INPUT;}
#define		PIN_P57_READ			P57_READ
#define		vP57Low()				{P57_LOW;}
#define		vP57High()				{P57_HIGH;}
	
//P60		//For IR 
#define		PIN_IR						PP60
#define		PIN_IR_READ				P60_READ
#define		PIN_IR_INT_EN				P60_INT_EN
#define		PIN_IR_INT_DIS				P60_INT_DIS
#define		PIN_IR_FALL_EDGE_INT		EXTERNAL_INT_FALL_EDGE
#define		PIN_IR_AS_INT				P60_AS_EXTERNAL_INT

//P61		//For mcu with mcu i2c OTP Interrupt intput
#define		PIN_OTP_INT				PP61
#define		PIN_OTP_INT_IO_OUTPUT	{P61_AS_GPIO;P61_IO_OUTPUT;}
#define		PIN_OTP_INT_IO_INPUT		{P61_AS_GPIO;P61_IO_INPUT;}
#define		PIN_OTP_INT_READ			P61_READ
#define		fgOTPIntEN()				(P61_READ==0)
#define		fgOTPIntDIS()				P61_READ

//P62		//For mcu with mcu i2c busy input
#define		PIN_BUSY					PP62
#define		PIN_BUSY_IO_OUTPUT		{P62_AS_GPIO;P62_IO_OUTPUT;}
#define		PIN_BUSY_IO_INPUT			{P62_AS_GPIO;P62_IO_INPUT;}
#define		PIN_BUSY_READ				P62_READ
#define		fgBusy()					P62_READ
#define		fgFree()					(P62_READ==0)
#define		vPinI2cBusyEnable()		{P62_LOW;}//130315sh01
#define		vPinI2cBusyDisable()		{P62_HIGH;}//130315sh01

//P63		//For tube LED output
#define		PIN_TUBE_LED				PP63 
#define		PIN_TUBE_LED_IO_OUTPUT	{P63_AS_GPIO;P63_IO_OUTPUT;}
#define		PIN_TUBE_LED_IO_INPUT		{P63_AS_GPIO;P63_IO_INPUT;}
#define		PIN_TUBE_LED_HIGH_DRIVE	{P63_HIGH_DRIVE;}
#define		vTubeLedON()				{P63_LOW;}
#define		vTubeLedOFF()				{P63_HIGH;}

//P64
#define		PIN_P64					PP64
#define		PIN_P64_IO_OUTPUT		{P64_IO_OUTPUT;}
#define		PIN_P64_IO_INPUT		{P64_IO_INPUT;}
#define		PIN_P64_READ			P64_READ
#define		vP64Low()				{P64_LOW;}
#define		vP64High()				{P64_HIGH;}

//P65		//For light sensor ADC input
#define		PIN_LIGHT_IN				PP65
#define		PIN_LIGHT_IN_ALT_FUNC_EN	{P65_AS_ADC5;}

//P66
#define		PIN_P66					PP66
#define		PIN_P66_IO_OUTPUT		{P66_IO_OUTPUT;}
#define		PIN_P66_IO_INPUT		{P66_IO_INPUT;}
#define		PIN_P66_READ			P66_READ
#define		vP66Low()				{P66_LOW;}
#define		vP66High()				{P66_HIGH;}
#define		vP66Flash()				{PORT6^=PP66;}
#define		vP66Pulse()				{P66_HIGH;P66_LOW;}

//P67
#define		PIN_P67					PP67
#define		PIN_P67_IO_OUTPUT		{P67_IO_OUTPUT;}
#define		PIN_P67_IO_INPUT		{P67_IO_INPUT;}
#define		PIN_P67_READ			P67_READ
#define		vP67Low()				{P67_LOW;}
#define		vP67High()				{P67_HIGH;}
#define		vP67Flash()				{PORT6^=PP67;}
#define		vP67Pulse()				{P67_HIGH;P67_LOW;}

//P70		// For touch interrupt input
#define		PIN_TOUCH_INT				PP70
#define		PIN_TOUCH_INT_IO_INPUT	P70_IO_INPUT
#define		PIN_TOUCH_INT_IO_OUTPUT	P70_IO_OUTPUT
#define		PIN_TOUCH_INT_READ		P70_READ //130305gr01
#define		fgTouchIntEN()				(P70_READ==0)
#define		fgTouchIntDIS()				P70_READ

//P71
#define		PIN_P71					PP71
#define		PIN_P71_IO_OUTPUT		{P71_IO_OUTPUT;}
#define		PIN_P71_IO_INPUT		{P71_IO_INPUT;}
#define		PIN_P71_READ			P71_READ
#define		vP71Low()				{P71_LOW;}
#define		vP71High()				{P71_HIGH;}

//P72
#define		PIN_P72					PP72
#define		PIN_P72_IO_OUTPUT		{P72_IO_OUTPUT;}
#define		PIN_P72_IO_INPUT		{P72_IO_INPUT;}
#define		PIN_P72_READ			P72_READ
#define		vP72Low()				{P72_LOW;}
#define		vP72High()				{P72_HIGH;}

//P73		//Row1 output(same as digital1)(PMOS, low enable)(Total 5 digital / 7 segment)
#define		PIN_ROW1					PP73
#define		PIN_ROW1_IO_OUTPUT		P73_IO_OUTPUT
#define		PIN_ROW1_IO_INPUT			P73_IO_INPUT
#define		vRow1High()					{P73_HIGH;}
#define		vRow1Low()					{P73_LOW;}
#define		vRow1Disable()				{P73_HIGH;}
#define		vRow1Enable()				{P73_LOW;}

//P74
#define		PIN_P74					PP74
#define		PIN_P74_IO_OUTPUT		{P74_IO_OUTPUT;}
#define		PIN_P74_IO_INPUT		{P74_IO_INPUT;}
#define		PIN_P74_READ			P74_READ
#define		vP74Low()				{P74_LOW;}
#define		vP74High()				{P74_HIGH;}

//P75
#define		PIN_P75					PP75
#define		PIN_P75_IO_OUTPUT		{P75_IO_OUTPUT;}
#define		PIN_P75_IO_INPUT		{P75_IO_INPUT;}
#define		PIN_P75_READ			P75_READ
#define		vP75Low()				{P75_LOW;}
#define		vP75High()				{P75_HIGH;}

//P76
#define		PIN_P76					PP76
#define		PIN_P76_IO_OUTPUT		{P76_IO_OUTPUT;}
#define		PIN_P76_IO_INPUT		{P76_IO_INPUT;}
#define		PIN_P76_READ			P76_READ
#define		vP76Low()				{P76_LOW;}
#define		vP76High()				{P76_HIGH;}

//P77
#define		PIN_P77					PP77
#define		PIN_P77_IO_OUTPUT		{P77_IO_OUTPUT;}
#define		PIN_P77_IO_INPUT		{P77_IO_INPUT;}
#define		PIN_P77_READ			P77_READ
#define		vP77Low()				{P77_LOW;}
#define		vP77High()				{P77_HIGH;}

//P80	//DATA1 for programmer

//P81	//CLK1 for programmer

//P82
#define		PIN_P82					PP82
#define		PIN_P82_IO_OUTPUT		{P82_IO_OUTPUT;}
#define		PIN_P82_IO_INPUT		{P82_IO_INPUT;}
#define		PIN_P82_READ			P82_READ
#define		vP82Low()				{P82_LOW;}
#define		vP82High()				{P82_HIGH;}

//P83		//RST1, for debug tool.

//P84		//Row5 output(same as digital5)(PMOS, low enable)(Total 5 digital / 7 segment)
#define		PIN_ROW5					PP84
#define		PIN_ROW5_IO_OUTPUT		P84_IO_OUTPUT
#define		PIN_ROW5_IO_INPUT			P84_IO_INPUT
#define		vRow5High()					{P84_HIGH;}
#define		vRow5Low()					{P84_LOW;}
#define		vRow5Disable()				{P84_HIGH;}
#define		vRow5Enable()				{P84_LOW;}

//P85		//Row4 output(same as digital4)(PMOS, low enable)(Total 5 digital / 7 segment)
#define		PIN_ROW4					PP85
#define		PIN_ROW4_IO_OUTPUT		P85_IO_OUTPUT
#define		PIN_ROW4_IO_INPUT			P85_IO_INPUT
#define		vRow4High()					{P85_HIGH;}
#define		vRow4Low()					{P85_LOW;}
#define		vRow4Disable()				{P85_HIGH;}
#define		vRow4Enable()				{P85_LOW;}

//P86		//Row3 output(same as digital3)(PMOS, low enable)(Total 5 digital / 7 segment)
#define		PIN_ROW3					PP86
#define		PIN_ROW3_IO_OUTPUT		P86_IO_OUTPUT
#define		PIN_ROW3_IO_INPUT			P86_IO_INPUT
#define		vRow3High()					{P86_HIGH;}
#define		vRow3Low()					{P86_LOW;}
#define		vRow3Disable()				{P86_HIGH;}
#define		vRow3Enable()				{P86_LOW;}

//P87		//Row2 output(same as digital2)(PMOS, low enable)(Total 5 digital / 7 segment)
#define		PIN_ROW2					PP87
#define		PIN_ROW2_IO_OUTPUT			P87_IO_OUTPUT
#define		PIN_ROW2_IO_INPUT			P87_IO_INPUT
#define		vRow2High()					{P87_HIGH;}
#define		vRow2Low()					{P87_LOW;}
#define		vRow2Disable()				{P87_HIGH;}
#define		vRow2Enable()				{P87_LOW;}

//P8        
#define		PIN_ROW_PORT				PORT8
#define		P8_IO_OUTPUT				P8CR=0x00
#define		P8_IO_INPUT					P8CR=0xff
#define		PIN_ROW_PORT_IO_OUTPUT		P8_IO_OUTPUT
#define		PIN_ROW_PORT_IO_INPUT		P8_IO_INPUT
#define		vRow2To5Disable()					PORT8|=0xF0
#define		vRow2To5Enable()						PORT8&=0x0F
#define		vRow2To5Output()						P8CR&=0x0F
#define		vRow2To5Input()						P8CR|=0xF0	//130314ja01


//P90		//Colume1 output(same as segment1)(NMOS, high enable)(Total 5 digital / 7 segment)
#define		PIN_COLUMN1					PP90
#define		PIN_COLUMN1_IO_OUTPUT		P90_IO_OUTPUT	
#define		PIN_COLUMN1_IO_INPUT		P90_IO_INPUT
#define		vColumn1High()				{P90_HIGH;}
#define		vColumn1Low()				{P90_LOW;}
#define		vColumn1Enable()			{P90_HIGH;}
#define		vColumn1Disable()			{P90_LOW;}

//P91		//Colume2 output(same as segment2)(NMOS, high enable)(Total 5 digital / 7 segment)
#define		PIN_COLUMN2					PP91
#define		PIN_COLUMN2_IO_OUTPUT		P91_IO_OUTPUT
#define		PIN_COLUMN2_IO_INPUT		P91_IO_INPUT
#define		vColumn2High()				{P91_HIGH;}
#define		vColumn2Low()				{P91_LOW;}
#define		vColumn2Enable()			{P91_HIGH;}
#define		vColumn2Disable()			{P91_LOW;}

//P92		//Colume3 output(same as segment3)(NMOS, high enable)(Total 5 digital / 7 segment)
#define		PIN_COLUMN3					PP92
#define		PIN_COLUMN3_IO_OUTPUT		P92_IO_OUTPUT
#define		PIN_COLUMN3_IO_INPUT		P92_IO_INPUT
#define		vColumn3High()				{P92_HIGH;}
#define		vColumn3Low()				{P92_LOW;}
#define		vColumn3Enable()			{P92_HIGH;}
#define		vColumn3Disable()			{P92_LOW;}

//P93		//Colume4 output(same as segment4)(NMOS, high enable)(Total 5 digital / 7 segment)
#define		PIN_COLUMN4					PP93
#define		PIN_COLUMN4_IO_OUTPUT		P93_IO_OUTPUT
#define		PIN_COLUMN4_IO_INPUT		P93_IO_INPUT
#define		vColumn4High()				{P93_HIGH;}
#define		vColumn4Low()				{P93_LOW;}
#define		vColumn4Enable()			{P93_HIGH;}
#define		vColumn4Disable()			{P93_LOW;}

//P94		//Colume5 output(same as segment5)(NMOS, high enable)(Total 5 digital / 7 segment)
#define		PIN_COLUMN5					PP94
#define		PIN_COLUMN5_IO_OUTPUT		P94_IO_OUTPUT
#define		PIN_COLUMN5_IO_INPUT		P94_IO_INPUT
#define		vColumn5High()				{P94_HIGH;}
#define		vColumn5Low()				{P94_LOW;}
#define		vColumn5Enable()			{P94_HIGH;}
#define		vColumn5Disable()			{P94_LOW;}

//P95		//Colume6 output(same as segment6)(NMOS, high enable)(Total 5 digital / 7 segment)
#define		PIN_COLUMN6					PP95
#define		PIN_COLUMN6_IO_OUTPUT		P95_IO_OUTPUT
#define		PIN_COLUMN6_IO_INPUT		P95_IO_INPUT
#define		vColumn6High()				{P95_HIGH;}
#define		vColumn6Low()				{P95_LOW;}
#define		vColumn6Enable()			{P95_HIGH;}
#define		vColumn6Disable()			{P95_LOW;}

//P96		//Colume7 output(same as segment7)(NMOS, high enable)(Total 5 digital / 7 segment)
#define		PIN_COLUMN7					PP96
#define		PIN_COLUMN7_IO_OUTPUT		P96_IO_OUTPUT
#define		PIN_COLUMN7_IO_INPUT		P96_IO_INPUT
#define		vColumn7High()				{P96_HIGH;}
#define		vColumn7Low()				{P96_LOW;}
#define		vColumn7Enable()			{P96_HIGH;}
#define		vColumn7Disable()			{P96_LOW;}

//P97		//Colume8 output(same as segment8)(NMOS, high enable)(Total 5 digital / 7 segment)
#define		PIN_COLUMN8					PP97
#define		PIN_COLUMN8_IO_OUTPUT		P97_IO_OUTPUT
#define		PIN_COLUMN8_IO_INPUT		P97_IO_INPUT
#define		vColumn8High()				{P97_HIGH;}
#define		vColumn8Low()				{P97_LOW;}
#define		vColumn8Enable()			{P97_HIGH;}
#define		vColumn8Disable()			{P97_LOW;}

//P9
#define		PIN_COLUMN_PORT			PORT9	
#define		P9_IO_OUTPUT				(P9CR=0x00)
#define		P9_IO_INPUT				(P9CR=0xFF)
#define		PIN_COLUMN_IO_OUTPUT		P9_IO_OUTPUT
#define		PIN_COLUMN_IO_INPUT		P9_IO_INPUT
#define		vLedColumnOutValue(bdata)	{PIN_COLUMN_PORT=bdata;}
//130118M01&&&



void vInitialGPIO(void);
void vPollingOTP_INT(void);//130302sh01
void vPollingTouchINT(void); //130305gr01


#endif

