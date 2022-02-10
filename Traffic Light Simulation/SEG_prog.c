#include "DIO_int.h"
#include "SEG_int.h"
void SEG_Initialization()
{
	a;
	b;
	c;
	d;
	e;
	f;
	g;
	DP;
	Enable1;
	Enable2;
}
void SEG_WriteCmnAnd(U8 LOC_U8_num) // This function write the number on 8 pins according to initialization file
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
			// return 0b0000001;
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
		// 0b0001111;
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
		// 0b0000000;
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
		// 0b0000100;
	}
}
