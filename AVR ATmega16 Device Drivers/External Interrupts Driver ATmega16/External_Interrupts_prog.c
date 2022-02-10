#include "External_Interrupts_int.h"

void External_Interrupts_SEI(void)
{
	setbit(SREG,7);
}
void External_Interrupts_init(void)
{
	/* Initializing MCUCR According to the configuration file */
	#if (!ISC11 && !ISC10 && !ISC00 && !ISC01)
		clrnibblelow(MCUCR);
	#elif (!ISC11 && !ISC10 && !ISC00 && ISC01)
	{
		clrbit(MCUCR,0);
		setbit(MCUCR,1);
		clrbit(MCUCR,2);
		clrbit(MCUCR,3);
	}
	#elif (!ISC11 && !ISC10 && ISC00 && !ISC01)
	{
		setbit(MCUCR,0);
		clrbit(MCUCR,1);
		clrbit(MCUCR,2);
		clrbit(MCUCR,3);
	}
	#elif (!ISC11 && !ISC10 && ISC00 && ISC01)
	{
		setbit(MCUCR,0);
		setbit(MCUCR,1);
		clrbit(MCUCR,2);
		clrbit(MCUCR,3);
	}
	#elif (!ISC11 && ISC10 && !ISC00 && !ISC01)
	{
		clrbit(MCUCR,0);
		clrbit(MCUCR,1);
		setbit(MCUCR,2);
		clrbit(MCUCR,3);
	}
	#elif (!ISC11 && ISC10 && !ISC00 && ISC01)
	{
		clrbit(MCUCR,0);
		setbit(MCUCR,1);
		setbit(MCUCR,2);
		clrbit(MCUCR,3);
	}
	#elif (!ISC11 && ISC10 && ISC00 && !ISC01)
	{
		setbit(MCUCR,0);
		clrbit(MCUCR,1);
		setbit(MCUCR,2);
		clrbit(MCUCR,3);
	}
	#elif (!ISC11 && ISC10 && ISC00 && ISC01)
	{
		setbit(MCUCR,0);
		setbit(MCUCR,1);
		setbit(MCUCR,2);
		clrbit(MCUCR,3);
	}
	#elif (ISC11 && !ISC10 && !ISC00 && !ISC01)
	{
		clrbit(MCUCR,0);
		clrbit(MCUCR,1);
		clrbit(MCUCR,2);
		setbit(MCUCR,3);
	}
	#elif (ISC11 && !ISC10 && !ISC00 && ISC01)
	{
		clrbit(MCUCR,0);
		setbit(MCUCR,1);
		clrbit(MCUCR,2);
		setbit(MCUCR,3);
	}
	#elif (ISC11 && !ISC10 && ISC00 && !ISC01)
	{
		setbit(MCUCR,0);
		clrbit(MCUCR,1);
		clrbit(MCUCR,2);
		setbit(MCUCR,3);
	}
	#elif (ISC11 && !ISC10 && ISC00 && ISC01)
	{
		setbit(MCUCR,0);
		setbit(MCUCR,1);
		clrbit(MCUCR,2);
		setbit(MCUCR,3);
	}
	#elif (ISC11 && ISC10 && !ISC00 && !ISC01)
	{
		clrbit(MCUCR,0);
		clrbit(MCUCR,1);
		setbit(MCUCR,2);
		setbit(MCUCR,3);
	}
	#elif (ISC11 && ISC10 && !ISC00 && ISC01)
	{
		clrbit(MCUCR,0);
		setbit(MCUCR,1);
		setbit(MCUCR,2);
		setbit(MCUCR,3);
	}
	#elif (ISC11 && ISC10 && ISC00 && !ISC01)
	{
		setbit(MCUCR,0);
		clrbit(MCUCR,1);
		setbit(MCUCR,2);
		setbit(MCUCR,3);
	}
	#elif (ISC11 && ISC10 && ISC00 && ISC01)
	{
		setnibblelow(MCUCR);
	}
	#endif

	/* Initializing MCUCSR According to the configuration file */
	#if (!ISC2)
		setbit(MCUCSR,6);
	#else
		clrbit(MCUCSR,6);
	#endif

	/* Initializing GICR According to the configuration file */
	#if (GICR_INT0)
		setbit(GICR,6);
	#else
		clrbit(GICR,6);
	#endif

	#if (GICR_INT1)
		setbit(GICR,7);
	#else
		clrbit(GICR,7);
	#endif

	#if (GICR_INT2)
		setbit(GICR,5);
	#else
		clrbit(GICR,5);
	#endif
	External_Interrupts_SEI();
}

void External_Interrupts_CLI(void)
{
	clrbit(SREG,7);
}

void External_Interrupts_CallBack_0 (void (*ptr_0) (void))
{
	ptr_INT0 = ptr_0;
}

void External_Interrupts_CallBack_1 (void (*ptr_1) (void))
{
	ptr_INT1 = ptr_1;
}

void External_Interrupts_CallBack_2 (void (*ptr_2) (void))
{
	ptr_INT2 = ptr_2;
}
ISR (__vector_1)
{
	(*ptr_INT0)();
}
ISR(__vector_2)
{
	(*ptr_INT1)();
}
ISR(__vector_18)
{
	(*ptr_INT2)();
}
