#define _IR_RECEIVE_C
#include "general.h"
#ifdef IR_FUNCTION

//130115st01***
const BYTE IRKeyTbl[0x10] =
{
  /* 0x00 */ IR_NONE,		
  /* 0x01 */ IR_NONE,	
  /* 0x02 */ IR_LOUVER_ANGLE,
  /* 0x03 */ IR_HORIZONTAL_OSCILLATING,	//130307a01w
  /* 0x04 */ IR_WATCH_MODE,		
  /* 0x05 */ IR_POWER,
  /* 0x06 */ IR_AIR_VOLUME_CONTROL_HI,
  /* 0x07 */ IR_FINE_CONTROL_HI,	
  /* 0x08 */ IR_NONE,		
  /* 0x09 */IR_TIMER,  
  /* 0x0a */IR_ION_MODE,
  /* 0x0b */ IR_VERTICAL_DIRECTION,
  /* 0x0c */ IR_OSCILLATING_ANGLE,	//130304a01w	//130307a01w
  /* 0x0d */ IR_NONE,
  /* 0x0e */IR_AIR_VOLUME_CONTROL_LO,
  /* 0x0f */ IR_FINE_CONTROL_LO
};	//130115st01&&&



#define IR_FINE_KEY_RELEASE_TIME_COUNT 22		//If over 550ms, we can say user release this key.	//550ms=22*25ms	//130422le01
BOOL fgIRFineNotPressContinue;		//130422le01
BYTE bIRFineKeyTimerCount=0;	//130422le01


BYTE	bIRStateMachine=0;
#ifdef IR_COUNT_VALUE_USE_ARRAY_SAVE	//130306a01w
BOOL	fgIRReceiveFinish=FALSE;
BYTE	bIRReceiveBuffer[66];		//130228st01
#endif	//130306a01w
BYTE	ulIRCodeData[8];		
BYTE	bIRKeyBuf;

//For Sharp remote control protocol.Total 64bits.	
#define IR_USER_RELEASE_KEY_TIME		100				
#define IR_LEADER_CODE_LENGTH			5060		// 5060us
#define IR_ZERO_CODE_LENGTH			860			// 860us
#define IR_ONE_CODE_LENGTH				1665		//1665us
#define IR_TIMER_OFFSET 					320

#define IR_COUNTER_TIMER				32			//32us

#define IR_SYSTEM_CODE_C1					0x5A			
#define IR_SYSTEM_CODE_C0					0xAA	

#define IR_SYSTEM_CODE_D1					0x17			
#define IR_SYSTEM_CODE_D0_P0					0xCF

#define IR_DATA_CODE_D2_1					0x09			
#define IR_DATA_CODE_D2					0x01

#define IR_DATA_CODE_D3					0x00			
#define IR_DATA_CODE_D2_2					0x20	

//For Sharp remote control protocol.Total 64bits.
//	+---------------------	+--------------------	+--------------------	+
//	|00 01 02 03 04 05 06 07		|08 09 10 11 12 13 14 15 	|16 17 18  19 20 21 22 23	 |24 25 26 27 28 29 30 31 	
//+------------------------------------------System code----------------------------------------------+

//	|32 33 34 35 36 37 38 39 		|40  41 42 43 44 45 46 47 	|48  49 50 51 52  53 54 55 	 |56 57 58 59 60 61 62 63 
//+------------------------------------------Data code-------------------------------------------------+
#ifdef IR_COUNT_VALUE_USE_ARRAY_SAVE	//130306a01w
void  vISR_IR()
{
	BYTE bIRCycleCount;		//recode the TCC count value.
	EXIF = 0;
	bIRCycleCount = TCC;	 
	TCC = 0;

	switch(bIRStateMachine)
		{
		case 0:
			bIRStateMachine++;
			break;
		case 65:
			bIRReceiveBuffer[bIRStateMachine]=bIRCycleCount;	//130228st01
			fgIRReceiveFinish=TRUE;
			bIRStateMachine=0;
			break;
		default:
			bIRReceiveBuffer[bIRStateMachine]=bIRCycleCount;
			bIRStateMachine++;
			break;
		}	
	RETI();
}

void vIRCheck(void)
{
//	static BYTE bLastKey=0XFF;
//	static BYTE repeat_key_timer=0; 
	BYTE	 i;
	BYTE 	bIRTimerCount; 
	BYTE 	 IRCodeDataHighData;
	BYTE  	IRCodeDataLowData;
	
	
	if(!fgIRReceiveFinish)
		return;
	
	fgIRReceiveFinish=FALSE;
	for(i=1;i<=66;i++)
		{
		bIRTimerCount=bIRReceiveBuffer[i];
		switch(i)
			{
			case 1:
				if( (bIRTimerCount>((IR_LEADER_CODE_LENGTH-IR_TIMER_OFFSET)/IR_COUNTER_TIMER))&&(bIRTimerCount<((IR_LEADER_CODE_LENGTH+IR_TIMER_OFFSET)/IR_COUNTER_TIMER)) )
					{
					}
				else
					{
					return;
					}
				break;
			case 66:
				//ulIRCodeData[0] /ulIRCodeData[1]/ulIRCodeData[2]/ulIRCodeData[3] stand for system code  total 32 bits
				//ulIRCodeData[4] /ulIRCodeData[5]/ulIRCodeData[6]/ulIRCodeData[7] stand for Data code  total 32 bits
				if(((ulIRCodeData[7]&0x0f)==IR_DATA_CODE_D3) && (ulIRCodeData[6]==IR_DATA_CODE_D2_2)
					&&((ulIRCodeData[5]&0x0f)==IR_DATA_CODE_D2_1)&&(ulIRCodeData[4]==IR_DATA_CODE_D2)
					&&(ulIRCodeData[3]==IR_SYSTEM_CODE_D1)&&(ulIRCodeData[2]==IR_SYSTEM_CODE_D0_P0)
					&&(ulIRCodeData[1]==IR_SYSTEM_CODE_C1)&&(ulIRCodeData[0]==IR_SYSTEM_CODE_C0))
					{	//Get data code ulIRCodeData[7] and ulIRCodeData[5] high 4bits
					IRCodeDataHighData=((ulIRCodeData[7]&0xf0)>>4);					
					IRCodeDataLowData=((ulIRCodeData[5]&0xf0)>>4);	
					
					bIRKeyBuf=IRKeyTbl[IRCodeDataHighData];
						
					if(IRCodeDataHighData==IRCodeDataLowData)		//Check if high 4bits equal
						{
						switch(bIRKeyBuf)
							{
							/*case IR_FINE_CONTROL_HIIGHT_MODE:
							case IR_FINE_CONTROL_LOW_MODE:
								if((ulIRCodeData[7]&0xf0)!=bLastKey)
									{	//Key change.
									//vPutEventQueue(EVENT_IR,bIRKeyBuf ,0 ,0);						
									bLastKey = (ulIRCodeData[7]&0xf0);
									repeat_key_timer=0;
									}
								else if(wSharpIRTimer>=IR_USER_RELEASE_KEY_TIME)
									{	//Key not change,but user release and press key.		
									//vPutEventQueue(EVENT_IR,bIRKeyBuf ,0 ,0);						
									repeat_key_timer=0;
									}
								else
									{	//Key not change and user press key continue.
									repeat_key_timer++;
									if(repeat_key_timer>=USER_KEEP_PRESS_KEY_TIME)
										{
										//vPutEventQueue(EVENT_IR,_bIRKeyBuf ,0 ,0);					
										repeat_key_timer-=USER_KEEP_PRESS_KEY_REPEAT_TIME;
										}

									break;
									}*/
							default:
								vPutEventQueue(EVENT_IR,bIRKeyBuf ,0);						
								break;
								}
						}
					}
				break;
			default:
				if( (bIRTimerCount>((IR_ZERO_CODE_LENGTH-IR_TIMER_OFFSET)/IR_COUNTER_TIMER))&&(bIRTimerCount<((IR_ZERO_CODE_LENGTH+IR_TIMER_OFFSET)/IR_COUNTER_TIMER)))
					{
					//Bit 0. Put this bit to data.
					C=0;
					}
				else if( (bIRTimerCount>((IR_ONE_CODE_LENGTH-IR_TIMER_OFFSET)/IR_COUNTER_TIMER))&&(bIRTimerCount<((IR_ONE_CODE_LENGTH+IR_TIMER_OFFSET)/IR_COUNTER_TIMER)))
					{
					//Bit 1. Put this bit to data.
					C=1;
					}
				else
					{
					return;
					}
				//Sharp remote control is 64 bits,need 8 registers.
				_asm("RRC	%ulIRCodeData+7");
				_asm("RRC	%ulIRCodeData+6");
				_asm("RRC	%ulIRCodeData+5");
				_asm("RRC	%ulIRCodeData+4");
				_asm("RRC	%ulIRCodeData+3");
				_asm("RRC	%ulIRCodeData+2");	
				_asm("RRC	%ulIRCodeData+1");	
				_asm("RRC	%ulIRCodeData+0");	
				break;	
			}
		}
}//130115st01&&&
#else	//IR receive use the interrupt directly.	//130306a01w***
void  vISR_IR() 
{
	BYTE bIRCycleCount;		//recode the TCC count value.
	BYTE IRCodeDataHighData;
	BYTE IRCodeDataLowData;
	static BYTE bIROldKeyBuf;	//130424le01

	EXIF = 0;
	bIRCycleCount = TCC;	 
	TCC = 0;

	switch(bIRStateMachine)
		{
		case 0:
			bIRStateMachine++;
			break;
		case 1:
			//Leader code 
			if( (bIRCycleCount>((IR_LEADER_CODE_LENGTH-IR_TIMER_OFFSET)/IR_COUNTER_TIMER))&&(bIRCycleCount<((IR_LEADER_CODE_LENGTH+IR_TIMER_OFFSET)/IR_COUNTER_TIMER)) )
				{
				bIRStateMachine++;
				}
			else
				{
				bIRStateMachine=0;
				}
			bIRCycleCount=0;
			break;
		default:	////130307a01w
			//Eighth register
			if( (bIRCycleCount>((IR_ZERO_CODE_LENGTH-IR_TIMER_OFFSET)/IR_COUNTER_TIMER))&&(bIRCycleCount<((IR_ZERO_CODE_LENGTH+IR_TIMER_OFFSET)/IR_COUNTER_TIMER)))
				{
				//Bit 0. Put this bit to data.
				bIRStateMachine++;
				C=0;
				}
			else if( (bIRCycleCount>((IR_ONE_CODE_LENGTH-IR_TIMER_OFFSET)/IR_COUNTER_TIMER))&&(bIRCycleCount<((IR_ONE_CODE_LENGTH+IR_TIMER_OFFSET)/IR_COUNTER_TIMER)))
				{
				//Bit 1. Put this bit to data.
				bIRStateMachine++;
				C=1;
				}
			else
				{
				bIRStateMachine=0;
				break;
				}
			bIRCycleCount=0;
			//Write bit to register
			_asm("RRC	%ulIRCodeData+7");	//130307a01w***
			_asm("RRC	%ulIRCodeData+6");
			_asm("RRC	%ulIRCodeData+5");
			_asm("RRC	%ulIRCodeData+4");
			_asm("RRC	%ulIRCodeData+3");
			_asm("RRC	%ulIRCodeData+2");	
			_asm("RRC	%ulIRCodeData+1");	
			_asm("RRC	%ulIRCodeData+0");	//130307a01w&&&
			if(bIRStateMachine>=66)
				{
				bIRStateMachine=0;
				//ulIRCodeData[0] /ulIRCodeData[1]/ulIRCodeData[2]/ulIRCodeData[3] stand for system code  total 32 bits
				//ulIRCodeData[4] /ulIRCodeData[5]/ulIRCodeData[6]/ulIRCodeData[7] stand for Data code  total 32 bits
				if(((ulIRCodeData[7]&0x0f)==IR_DATA_CODE_D3) && (ulIRCodeData[6]==IR_DATA_CODE_D2_2)
					&&((ulIRCodeData[5]&0x0f)==IR_DATA_CODE_D2_1)&&(ulIRCodeData[4]==IR_DATA_CODE_D2)
					&&(ulIRCodeData[3]==IR_SYSTEM_CODE_D1)&&(ulIRCodeData[2]==IR_SYSTEM_CODE_D0_P0)
					&&(ulIRCodeData[1]==IR_SYSTEM_CODE_C1)&&(ulIRCodeData[0]==IR_SYSTEM_CODE_C0))
					{	//Get data code ulIRCodeData[7] and ulIRCodeData[5] high 4bits
					IRCodeDataHighData=((ulIRCodeData[7]&0xf0)>>4);					
					IRCodeDataLowData=((ulIRCodeData[5]&0xf0)>>4);	

					bIRKeyBuf=IRKeyTbl[IRCodeDataHighData];

					fgIRFineNotPressContinue=TRUE;	//buzzer sound
					if(IRCodeDataHighData==IRCodeDataLowData)		//Check if high 4bits equal
						{
						if((bIRKeyBuf==IR_FINE_CONTROL_HI)||(bIRKeyBuf==IR_FINE_CONTROL_LO))	//130422le01***
							{
							//if(bIRFineKeyTimerCount<IR_FINE_KEY_RELEASE_TIME_COUNT)	//130424le01
							if((bIROldKeyBuf==bIRKeyBuf)&&(bIRFineKeyTimerCount<IR_FINE_KEY_RELEASE_TIME_COUNT))	//130424le01
								{
								fgIRFineNotPressContinue=FALSE;	//buzzer not sound
								}
							}
						bIRFineKeyTimerCount=0;	//130422le01&&&
						bIROldKeyBuf=bIRKeyBuf;	//130424le01
						vPutEventQueue(EVENT_IR,bIRKeyBuf ,0);	//send key code to queue					
						}
					}

				}
			break;
		}
	RETI();
}
#endif	//130306a01w&&&

#endif




int getSubStringNumber(char *string,char *substring,int *ncount)
{
	int ret=0;
	int temCount=0;
	char *my_string=string;
	char *my_substring=substring;

	if((string==NULL)||(substring==NULL)||(ncount==NULL))
		{
		ret=-1;
		printf("\n",ret);
		return ret;
		}
	
	do
		{
		my_string=strstr(my_string,my_substring);
		if(my_string!=NULL)
			{
			temCount++;
			my_string=my_string+strlen(my_substring);
			}
		else
			{
			break;
			}

		}while(*my_string!='\0')

	*ncount=temCount;	//間接賦值的最大意義
	return ret;
}




char getStringNumCount(char *string,char *ncount)
{	
	int temCount=0;
	int ret=0;
	int i=0;
	int j=0;
	j=strlen(string)-1;
	char *p=string;
	//char *my_ncount=ncount;
	
	if((string==NULL)||(ncount==NULL))
		{
		ret=-1;
		printf("error: %d \n");
		}

	while(isspace(p[i])&&(p[i]!='\0'))
		{
		i++;
		}
	
	while(isspace(p[j])&&(p[j]!='\0'))
		{
		j--;
		}
	temCount=j-i+1;

	strncopy();
	*ncount=temCount;
}

char trinSpace(char *string,char *newstring)
{	
	int ncount=0;
	int ret=0;
	int i=0;
	int j=0;
	j=strlen(string)-1;
	char *p=string;
	//char *my_newstring=newstring;
	
	if((string==NULL)||(newstring==NULL))
		{
		ret=-1;
		printf("error: %d \n");
		}

	while(isspace(p[i])&&(p[i]!='\0'))
		{
		i++;
		}
	
	while(isspace(p[j])&&(p[j]!='\0'))
		{
		j--;
		}
	ncount=j-i+1;

	strncopy(newstring,string+i,ncount);
	newstring[ncount]='\0';
}


void main()
{
	char *p="    adcdefg       ";
	int ncount=0;
	getStringNumCount(p, &ncount);
}

void inverse(char *p)
{
	if(p==NULL)
		{
		return;
		}
	if(*p=='\0')
		{
		return;
		}

	inverse(p+1);	//遞歸調用
	printf("%c",*p);

}

typedef struct teacher
{
	char name[];
	int age;
	int id;
}teacher;


struct teacher
{

}s1,s2;

struct
{

}s3,s4;

void main()
{
	teacher AA;
	AA.name=;
}

class Point
{
public:

	

};


void main1()
{
	int ret=0;
	int ncount=0;
	char *string="abcd1111abcdasflslaf111abcd";
	char buf[]="abcd";
	ret=getSubStringNumber(string, buf,&ncount);
	if(ret!=0)
		{
		printf();
		return ret;
		}
	printf("ncount=%d \n",ncount);
}

char *strCopy(char *strDest, const char *strSrc)
{
	if(strDest==NULL ||strSrc==NULL)
		{
		return -1;
		}
	char *p=strDest;
	while((*strDest++=*strSrc++)!='\0')
		{
		;
		}
}


void strCopy01(char *strDest, const char *strSrc)
{
	if(strSrc==NULL ||strDest==NULL)
		{
		return;
		}
	for(;strSrc!='\0';strSrc++,strDest++)
		{
		*strDest=*strSrc;
		}
	*strDest='\0';
}
void strCopy02(char *strDest, const char *strSrc)
{
	if(strSrc==NULL ||strDest==NULL)
		{
		return;
		}
	for(;strSrc!='\0';)
		{
		*strDest++=*strSrc++;
		}
	*strDest='\0';
}

void strCopy03(char *strDest, const char *strSrc)
{
	if(strSrc==NULL ||strDest==NULL)
		{
		return;
		}
	while((*strDest=*strSrc)!='\0')
		{
		strDest++;
		strSrc++;
		}
}

void strCopy04(char *strDest, const char *strSrc)
{
	if(strSrc==NULL ||strDest==NULL)
		{
		return;
		}
	while((*strDest++=*strSrc++)!='\0')
		{
		;
		}
}

void strCopy05(char *strDest, const char *strSrc)
{
	if(strSrc==NULL ||strDest==NULL)
		{
		return;
		}
	while(*strDest++=*strSrc++)
		{
		;
		}
}


void main()
{
	int i=0;
	int j=0;
	char *temp=NULL;
	char tempbuf[100];
	int num=5;
	char **p=NULL;
	//分配內存空間
	p=(char**)malloc((sizeof(char*))*num);

	for(i=0;i<num;i++)
		{
		p[i]=(char *)malloc(sizeof(char)*100);
		sprintf(p[i],"%d%d%d",i+1,i+1,i+1);
		}

	//排序//交換的指針
	for(i=0,i<num,i++)
		{
		for(j=i+1,j<num,j++)
			{
			if(strcmp(p[i],p[j])>0)
				{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
				}
			}
		}

	//排序 交換內存塊
	for(i=0,i<num,i++)
		{
		for(j=i+1,j<num,j++)
			{
			if(strcmp(p[i],p[j])>0)
				{
				strcpy(tempbuf,p[i]);
				strcpy(p[i],p[j]);
				strcpy(p[j],tempbuf);
				}
			}
		}

	
	//釋放內存
	for(i=0,i<num,i++)
		{
		if(p[i]!=NULL)
			{
			free(p[i]);
			}
		}

	if(p!=NULL)
		{
		free(p);
		}
}

void main()
{
	int i=0;
	int j=0;
	char *temp=NULL;
	char tempbuf[100];
	int num=5;
	char **p=NULL;
	p=getMem(num);	//函數調用
	

}
//產生內存
char **getMem(int num)
{
	int i=0;
	char **p=NULL;
	//分配內存空間
	p=(char**)malloc((sizeof(char*))*num);
	if(p==NULL)
		{
		return NULL;
		}

	for(i=0;i<num;i++)
		{
		p[i]=(char *)malloc(sizeof(char)*100);
		sprintf(p[i],"%d%d%d",i+1,i+1,i+1);
		}

	return p;

}

typedef struct Queue
{
	int *base;
	int front;
	int rear;
	int full;
}Queue;


#define MAX_SIZE 1024

int creat_queue(Queue *q)
{
	if(q->base!==NULL)
		{
		return 0;
		}
	q->base=(int*)malloc(MAX_SIZE*sizeof(int));
	q->front=q->rear=0;
	q->full=0;
	return 1;	
}


int en_queue(Queue *q, int num)
{
	if(q==NULL)
		{
		return 0;
		}
	if(q->base==NULL)//判斷隊列是否存在
		{
		return -1;
		}
	if((q->full==1) && (q->front==q->rear))//判斷隊列是否滿
		{
		return 0;
		}
	q->base[q->rear]=num;
	q->rear=(q->rear+1)%MAX_SIZE;
	if (q->rear==q->front)
		{
		q->full=1;
		}
	return -1;
}


int out_queue(Queue *q, int *num)
{
	if(q->base==NULL)
		{
		return 0;
		}
	if((q->full==0) && (q->front==q->rear))//判斷隊列是否空
		{
		return 0;
		}
	*num=q->base[q->front];
	q->front=(q->front+1)%MAX_SIZE;
	if (q->rear==q->front)
		{
		q->full=0;
		}
	return 1;
}

int destory_queue(Queue *q)
{
	if(q->base==NULL)
		{
		return 0;
		}
	free(q->base);
	q->base=NULL;
	return 1;
}

int length_queue(Queue *q)
{
	if(q->base==NULL)
		{
		return 0;
		}
	if((q->full==0) && (q->front==q->rear))//判斷隊列是否滿了
		{
		return MAX_SIZE;
		}
	else
		{
		return (q->rear-q->front+MAX_SIZE)%MAX_SIZE;//如果rear比front小時,要加上整個隊列Queue的長度 MAX_SIZE.
		}
	return 1;
}

