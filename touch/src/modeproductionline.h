#ifndef _MODE_PRODUCTION_LINE_H_
#define _MODE_PRODUCTION_LINE_H_

#ifdef PRODUCTION_LINE_MODE_FUNCTION
extern BOOL fgProductModeBlue3State;//130309ma01
extern BOOL fgProductModeBlue6State;//130309ma01
extern BOOL fgProductModeTimeStatus;//130313ma02
extern BYTE bProductIonCount;   //130415ma01
/*   //130312ma01***
extern BOOL fgProductModeIonDeltaVoff;//130309ma01
extern BOOL fgProductModeIonDeltaV;//130309ma01	
*/  //130312ma01&&&
void vProductionLineModeInitial(void);
void vProductionLineModeKeyProcess(void);

//130123ma01***
void vProductModeTimer25ms(void); 
//130123ma01&&&
#else
#define vProductionLineModeInitial()
#define vProductionLineModeKeyProcess()
#define vProductModeTimer25ms()
#define fgProductModeTimeStatus	0	//130313ma02

#endif



#endif
