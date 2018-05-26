#ifndef _GPIO_H_
#define _GPIO_H_

void vInitialGPIO(void);
//void vPollingPCINone(void);//130418sh02
void vPollingCoverSwitch(void);
void vPollingTouchMcuBusy(void);//130315sh01
void vPollingSpeedUpMode(void);	//130407ra01
void vPollingFG(void);	//130411Ke01




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

//P51		SDA_OTP, Hardware I2C

//P52		//For PCI power Supply  
#define		PIN_PCI_POWER						PP52
#define		PIN_PCI_POWER_IO_OUTPUT			P52_IO_OUTPUT
#define		PIN_PCI_POWER_IO_INPUT			P52_IO_INPUT
#define		vPCIPowerOn()						{P52_HIGH;} 
#define		vPCIPowerOff()						{P52_LOW;}

//P53		SCK_OTP, Hardware I2C

//P54
		//XIN

//P55
		//XOUT

//P56		//For Fan FG
#define		PIN_FAN_FG							PP56
#define		PIN_FAN_FG_IO_INPUT				P56_IO_INPUT
#define		PIN_FAN_FG_IO_OUTPUT				P56_IO_OUTPUT
#define		PIN_TC2_INPUT						TC2_CLOCK_SOURCE_TC2   //Timer2 Clocck input
#define		PIN_FAN_FG_READ					P56_READ
#define		fgFanFGIsON()						(P56_READ==1)
#define		fgFanFGIsOFF()						(P56_READ==0)	

//P57
#define		PIN_P57					PP57
#define		PIN_P57_IO_OUTPUT		{P57_IO_OUTPUT;}
#define		PIN_P57_IO_INPUT		{P57_IO_INPUT;}
#define		PIN_P57_READ			P57_READ
#define		vP57Low()				{P57_LOW;}
#define		vP57High()				{P57_HIGH;}
#define		vP57Flash()				{PORT5^=PP57;}
#define		vP57Pulse()				{P57_HIGH;P57_LOW;}

//P60
#define		PIN_P60					PP60
#define		PIN_P60_IO_OUTPUT		{P60_IO_OUTPUT;}
#define		PIN_P60_IO_INPUT		{P60_IO_INPUT;}
#define		PIN_P60_READ			P60_READ
#define		vP60Low()				{P60_LOW;}
#define		vP60High()				{P60_HIGH;}
#define		vP60Flash()				{PORT6^=PP60;}
#define		vP60Pulse()				{P60_HIGH;P60_LOW;}

//P61		//For mcu with mcu i2c OTP Interrupt output
#define		PIN_OTP_INT						PP61
#define		PIN_OTP_INT_IO_INPUT				{P61_AS_GPIO;P61_IO_INPUT;}
#define		PIN_OTP_INT_IO_OUTPUT			{P61_AS_GPIO;P61_IO_OUTPUT;}
#define		vOTPIntEn()							{P61_LOW;}
#define		vOTPIntDis()							{P61_HIGH;}

//P62		//For humidity ADC input
#define		PIN_TH_OUT							PP62
#define		PIN_TH_OUT_IN_ALT_FUNC_EN		{P62_AS_ADC2;}

//P63		//For temperature ADC input
#define		PIN_NTC							PP63
#define		PIN_NTC_IN_ALT_FUNC_EN			{P63_AS_ADC3;}

//P64		//Function Checker Mode (1:Enable). Plug in check one time.
#define		PIN_FUNCTION_CHECKER					PP64	//130403le01
#define		PIN_FUNCTION_CHECKER_IO_OUTPUT		{P64_IO_OUTPUT;}	//130403le01
#define		PIN_FUNCTION_CHECKER_IO_INPUT		{P64_IO_INPUT;}	//130403le01
#define		PIN_FUNCTION_CHECKER_READ			P64_READ	//130403le01
#define		PIN_FUNCTION_CHECKER_PULL_DOWN		P64_PULL_DOWN	//130403le01

//P65
#define		PIN_P65					PP65
#define		PIN_P65_IO_OUTPUT		{P65_IO_OUTPUT;}
#define		PIN_P65_IO_INPUT		{P65_IO_INPUT;}
#define		PIN_P65_READ			P65_READ
#define		vP65Low()				{P65_LOW;}
#define		vP65High()				{P65_HIGH;}

//P66		//For ION sensor ADC input
#define		PIN_ION_IN							PP66
#define		PIN_ION_IN_ALT_FUNC_EN			{P66_AS_ADC6;}

//P67		//For PCI detect
#define		PIN_PCI_NONE						PP67
#define		PIN_PCI_NONE_IO_INPUT				{P67_AS_GPIO;P67_IO_INPUT;}
#define		PIN_PCI_NONE_IO_OUTPUT			{P67_AS_GPIO;P67_IO_OUTPUT;}
#define		PIN_PCI_NONE_READ					P67_READ
#define		fgPCINoneIsNormal()					(P67_READ==1)
#define		fgPCINoneIsError()					(P67_READ==0)

//P70		//For rotation motor1
#define		PIN_ROTATION_MOTOR1				PP70		
#define		PIN_ROTATION_MOTOR1_IO_OUTPUT	P70_IO_OUTPUT
#define		PIN_ROTATION_MOTOR1_IO_INPUT	P70_IO_INPUT
#define		vRotationMotor1EN()					{P70_HIGH;}
#define		vRotationMotor1DIS()				{P70_LOW;}

//P71		//For rotation motor4
#define		PIN_ROTATION_MOTOR4				PP71
#define		PIN_ROTATION_MOTOR4_IO_OUTPUT	P71_IO_OUTPUT
#define		PIN_ROTATION_MOTOR4_IO_INPUT	P71_IO_INPUT
#define		vRotationMotor4EN()					{P71_HIGH;}
#define		vRotationMotor4DIS()				{P71_LOW;}

//P72		//For rotation motor5
#define		PIN_ROTATION_MOTOR5				PP72
#define		PIN_ROTATION_MOTOR5_IO_OUTPUT	P72_IO_OUTPUT
#define		PIN_ROTATION_MOTOR5_IO_INPUT	P72_IO_INPUT
#define		vRotationMotor5EN()					{P72_HIGH;}
#define		vRotationMotor5DIS()				{P72_LOW;}

//P73		//For buzzer voice control
#define		PIN_BUZZER_VOICE_CONTROL			PP73
#define		PIN_BUZZER_VOICE_CONTROL_IO_OUTPUT	P73_IO_OUTPUT
#define		PIN_BUZZER_VOICE_CONTROL_IO_INPUT	P73_IO_INPUT
#define		vBuzzerVoiceLoud()					{P73_LOW;}                 
#define		vBuzzerVoiceNormal()				{P73_HIGH;}  

//P74		//For switch detect		//?
#define		PIN_COVER_SWITCH					PP74
#define		PIN_COVER_SWITCH_READ			P74_READ
#define		PIN_COVER_SWITCH_IO_INPUT		P74_IO_INPUT
#define		fgCoverSwitchIsOpen()				(P74_READ==1)
#define		fgCoverSwitchIsNormal()				(P74_READ==0)

//P75		//For FAN motor pwm control	PWMA
#define		PIN_FAN_MOTOR							PP75
#define		PIN_FAN_MOTOR_IO_OUTPUT			P75_IO_OUTPUT
#define		PIN_FAN_MOTOR_IO_INPUT			P75_IO_INPUT
#define		PIN_FAN_MOTOR_OUT_LOW			{P75_LOW;}
//#define		vFanMotorDIS()					{P75_HIGH;}
#define		vSetFanMotorHighDuty(value)			vSetPWMAHighDuty(value)
#define		vSetFanMotorPeriod(value)			vSetPWMAPeriod(value)

//P76		//For buzzer pwm control	PWMB
#define		PIN_BUZZER							PP76
#define		PIN_BUZZER_IO_OUTPUT				P76_IO_OUTPUT
#define		PIN_BUZZER_IO_INPUT				P76_IO_INPUT
#define		PIN_BUZZER_OUT_LOW				{P76_LOW;}
//#define		vBuzzerDIS()						{P76_HIGH;}
#define		vSetBuzzerHighDuty(value)			vSetPWMBHighDuty(value)
#define		vSetBuzzerPeriod(value)				vSetPWMBPeriod(value)

//P77
#define		PIN_P77					PP77
#define		PIN_P77_IO_OUTPUT		{P77_IO_OUTPUT;}
#define		PIN_P77_IO_INPUT		{P77_IO_INPUT;}
#define		PIN_P77_READ			P77_READ
#define		vP77Low()				{P77_LOW;}
#define		vP77High()				{P77_HIGH;}

//P80	//DATA1 for programmer

//P81	//CLK1 for programmer

//P82		//1:Enter Speed Up mode. Power on check one time.
#define		PIN_P82					PP82
#define		PIN_P82_IO_OUTPUT		{P82_IO_OUTPUT;}
#define		PIN_P82_IO_INPUT		{P82_IO_INPUT;}
//#define		PIN_P82_READ			P82_READ
#define		PIN_SPEED_UP_MODE		P82_READ	//130407ra01
#define		fgSpeedUpModeEntry()		(P82_READ==1)	//130407ra01
#define		vP82Low()				{P82_LOW;}
#define		vP82High()				{P82_HIGH;}

//P83		RST, for debug tool

//P84		//For rotation motor2
#define		PIN_ROTATION_MOTOR2				PP84
#define		PIN_ROTATION_MOTOR2_IO_OUTPUT	P84_IO_OUTPUT
#define		PIN_ROTATION_MOTOR2_IO_INPUT	P84_IO_INPUT
#define		vRotationMotor2EN()					{P84_HIGH;}
#define		vRotationMotor2DIS()				{P84_LOW;}

//P85		//For mcu with mcu i2c busy output
#define		PIN_BUSY							PP85
#define		PIN_BUSY_IO_OUTPUT				P85_IO_OUTPUT
#define		PIN_BUSY_IO_INPUT					P85_IO_INPUT
#define		vI2CBusy()							{P85_HIGH;}
#define		vI2CFree()							{P85_LOW;}
#define		PIN_BUSY_READ						P85_READ//130315sh01
#define		fgTouchMCUIsBusy()					(P85_READ==0)
#define 		fgTouchMCUIsNotBusy()				(P85_READ==1)//130418sh02

//P86		//For mcu with PCI i2c communication SDA bus
#define		PIN_SDA							PP86
#define		PIN_SDA_READ						P86_READ
#define		PIN_SDA_IO_INPUT					P86_IO_INPUT
#define		PIN_SDA_IO_OUTPUT					P86_IO_OUTPUT
#define		PIN_SDA_OPEN_DRAIN				P86_OPEN_DRAIN
#define		vSDALow()							{P86_LOW;}
#define		vSDAHigh()							{P86_HIGH;}

//P87		//For mcu with PCI i2c communication SCL bus
#define		PIN_SCL								PP87
#define		PIN_SCL_IO_INPUT					P87_IO_INPUT
#define		PIN_SCL_IO_OUTPUT					P87_IO_OUTPUT
#define		PIN_SCL_OPEN_DRAIN				P87_OPEN_DRAIN
#define		vSCLLow()							{P87_LOW;}
#define		vSCLHigh()							{P87_HIGH;}

//P90		//For ion reset 
#define		PIN_ION_RESET						PP90
#define		PIN_ION_RESET_IO_OUTPUT			P90_IO_OUTPUT
#define		PIN_ION_RESET_IO_INPUT			P90_IO_INPUT
#define		vIONResetEN()						{P90_LOW;}		//130306Ad01
#define		vIONResetDIS()						{P90_HIGH;}		//130306Ad01

//P91		//For ION capacitance control
#define		PIN_CAP40F							PP91
#define		PIN_CAP40F_IO_OUTPUT				P91_IO_OUTPUT
#define		PIN_CAP40F_IO_INPUT				P91_IO_INPUT
#define		vCapacitance4PF()					{P91_HIGH;}
#define		vCapacitance40PF()					{P91_LOW;}

//P92
#define		PIN_P92					PP92
#define		PIN_P92_IO_OUTPUT		{P92_IO_OUTPUT;}
#define		PIN_P92_IO_INPUT		{P92_IO_INPUT;}
#define		PIN_P92_READ			P92_READ
#define		vP92Low()				{P92_LOW;}
#define		vP92High()				{P92_HIGH;}

//P93
#define		PIN_P93					PP93
#define		PIN_P93_IO_OUTPUT		{P93_IO_OUTPUT;}
#define		PIN_P93_IO_INPUT		{P93_IO_INPUT;}
#define		PIN_P93_READ			P93_READ
#define		vP93Low()				{P93_LOW;}
#define		vP93High()				{P93_HIGH;}

//P94		//For louver motor4
#define		PIN_LOUVER_MOTOR4				PP94
#define		PIN_LOUVER_MOTOR4_IO_OUTPUT		P94_IO_OUTPUT
#define		PIN_LOUVER_MOTOR4_IO_INPUT		P94_IO_INPUT
#define		vLouverMotor4EN()					{P94_HIGH;}
#define		vLouverMotor4DIS()					{P94_LOW;}

//P95		//For louver motor3
#define		PIN_LOUVER_MOTOR3				PP95
#define		PIN_LOUVER_MOTOR3_IO_OUTPUT		P95_IO_OUTPUT
#define		PIN_LOUVER_MOTOR3_IO_INPUT		P95_IO_INPUT
#define		vLouverMotor3EN()					{P95_HIGH;}
#define		vLouverMotor3DIS()					{P95_LOW;}

//P96		//For louver motor2
#define		PIN_VERT_MOTOR2					PP96
#define		PIN_LOUVER_MOTOR2_IO_OUTPUT		P96_IO_OUTPUT
#define		PIN_LOUVER_MOTOR2_IO_INPUT		P96_IO_INPUT
#define		vLouverMotor2EN()					{P96_HIGH;}
#define		vLouverMotor2DIS()					{P96_LOW;}

//P97		//For louver motor1
#define		PIN_LOUVER_MOTOR1				PP97
#define		PIN_LOUVER_MOTOR1_IO_OUTPUT		P97_IO_OUTPUT
#define		PIN_LOUVER_MOTOR1_IO_INPUT		P97_IO_INPUT
#define		vLouverMotor1EN()					{P97_HIGH;}
#define		vLouverMotor1DIS()					{P97_LOW;}
//130118M01&&&

#endif
