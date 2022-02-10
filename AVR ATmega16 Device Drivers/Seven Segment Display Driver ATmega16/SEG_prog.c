#include "DIO_int.h"
#include "SEG_int.h"
void SEG_Initialization()
{
	DIO_SetPinValue(pa, a);
	DIO_SetPinValue(pb, b);
	DIO_SetPinValue(pc, c);
	DIO_SetPinValue(pd, d);
	DIO_SetPinValue(pe, e);
	DIO_SetPinValue(pf, f);
	DIO_SetPinValue(pg, g);
	DIO_SetPinValue(pDP, DP);
	DIO_SetPinValue(pEnable1, Enable1);
	DIO_SetPinValue(pEnable2, Enable2);
}

/* This function write a certain digit in the enabled display(s) */
/* This function is used for common anode displays only (0 for turn on) */
void SEG_WriteCmnAnd(U8 LOC_U8_num) 
{
	switch (LOC_U8_num)
	{
		case 0: 
		{
			DIO_SetPinValue(pa,0);
			DIO_SetPinValue(pb,0);
			DIO_SetPinValue(pc,0);
			DIO_SetPinValue(pd,0);
			DIO_SetPinValue(pe,0);
			DIO_SetPinValue(pf,0);
			DIO_SetPinValue(pg,1);
			DIO_SetPinValue(pDP,1);
		break;
		}
		case 1: 
		{
			DIO_SetPinValue(pa,1);
			DIO_SetPinValue(pb,0);
			DIO_SetPinValue(pc,0);
			DIO_SetPinValue(pd,1);
			DIO_SetPinValue(pe,1);
			DIO_SetPinValue(pf,1);
			DIO_SetPinValue(pg,1);
			DIO_SetPinValue(pDP,1);	
		break;
		}
		case 2: 
		{
			DIO_SetPinValue(pa,0);
			DIO_SetPinValue(pb,0);
			DIO_SetPinValue(pc,1);
			DIO_SetPinValue(pd,0);
			DIO_SetPinValue(pe,0);
			DIO_SetPinValue(pf,1);
			DIO_SetPinValue(pg,0);
			DIO_SetPinValue(pDP,1);	
		break;
		}
		// 0b0010010;
		case 3: 
		{
			DIO_SetPinValue(pa,0);
			DIO_SetPinValue(pb,0);
			DIO_SetPinValue(pc,0);
			DIO_SetPinValue(pd,0);
			DIO_SetPinValue(pe,1);
			DIO_SetPinValue(pf,1);
			DIO_SetPinValue(pg,0);
			DIO_SetPinValue(pDP,1);	
		break;
		} 
		// 0b0000110;
		case 4: 
		{
			DIO_SetPinValue(pa,1);
			DIO_SetPinValue(pb,0);
			DIO_SetPinValue(pc,0);
			DIO_SetPinValue(pd,1);
			DIO_SetPinValue(pe,1);
			DIO_SetPinValue(pf,0);
			DIO_SetPinValue(pg,0);
			DIO_SetPinValue(pDP,1);
		break;
		}
		// 0b1001100;
		case 5:
		{
			DIO_SetPinValue(pa,0);
			DIO_SetPinValue(pb,1);
			DIO_SetPinValue(pc,0);
			DIO_SetPinValue(pd,0);
			DIO_SetPinValue(pe,1);
			DIO_SetPinValue(pf,0);
			DIO_SetPinValue(pg,0);
			DIO_SetPinValue(pDP,1);
		break;
		}
		// 0b0100100;
		case 6:
		{
			DIO_SetPinValue(pa,0);
			DIO_SetPinValue(pb,1);
			DIO_SetPinValue(pc,0);
			DIO_SetPinValue(pd,0);
			DIO_SetPinValue(pe,0);
			DIO_SetPinValue(pf,0);
			DIO_SetPinValue(pg,0);
			DIO_SetPinValue(pDP,1);
		break;
		}
		// 0b0100000;
		case 7:
		{
			DIO_SetPinValue(pa,0);
			DIO_SetPinValue(pb,0);
			DIO_SetPinValue(pc,0);
			DIO_SetPinValue(pd,1);
			DIO_SetPinValue(pe,1);
			DIO_SetPinValue(pf,1);
			DIO_SetPinValue(pg,1);
			DIO_SetPinValue(pDP,1);
		break;
		}
		case 8:
		{
			DIO_SetPinValue(pa,0);
			DIO_SetPinValue(pb,0);
			DIO_SetPinValue(pc,0);
			DIO_SetPinValue(pd,0);
			DIO_SetPinValue(pe,0);
			DIO_SetPinValue(pf,0);
			DIO_SetPinValue(pg,0);
			DIO_SetPinValue(pDP,1);
		break;
		}
		case 9:
		{
			DIO_SetPinValue(pa,0);
			DIO_SetPinValue(pb,0);
			DIO_SetPinValue(pc,0);
			DIO_SetPinValue(pd,0);
			DIO_SetPinValue(pe,1);
			DIO_SetPinValue(pf,0);
			DIO_SetPinValue(pg,0);
			DIO_SetPinValue(pDP,1);
		break;
		}
	}
}
