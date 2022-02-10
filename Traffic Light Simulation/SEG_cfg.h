#ifndef SEG_cfg
#define SEG_cfg

#include "DIO_int.h"
// Initial pins for 7 - SEG 
#define pa      16
#define pb		17
#define pc		18
#define pd		19
#define pe		20
#define pf		21
#define pg		 22
#define pDP		 23
#define pEnable1   8
#define pEnable2   9
// Initial values for 7 - SEG
#define a        DIO_SetPinValue(pa,0)
#define b		 DIO_SetPinValue(pb,0)
#define c		 DIO_SetPinValue(pc,0)
#define d		 DIO_SetPinValue(pd,0)
#define e		 DIO_SetPinValue(pe,0)
#define f		 DIO_SetPinValue(pf,0)
#define g		 DIO_SetPinValue(pg,0)
#define DP		 DIO_SetPinValue(pDP,1)
#define Enable1  DIO_SetPinValue(pEnable1,0)
#define Enable2  DIO_SetPinValue(pEnable2,0)

#endif
