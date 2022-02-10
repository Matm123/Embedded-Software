/*******************************************/
/* Author  : Mahmoud Ayman                 */
/* Date    : 17 NOV 2020                   */
/* Version : V01                           */
/*******************************************/

#include "NVIC_interface.h"

void NVIC_voidEnableInterrupt  ( u8 copy_u8INTPosition )
{
	if ( copy_u8INTPosition <= 31 )
	{
		NVIC_ISER0 = (1 << copy_u8INTPosition);  // Writing 0 has no effect 
	}
	else if ( copy_u8INTPosition <= 63 )
	{
		copy_u8INTPosition -= 32;
		NVIC_ISER1 = (1 << copy_u8INTPosition);  // Writing 0 has no effect 
	}
	else 
	{
		/* Error */
	}
	return;
}

void NVIC_voidDisableInterrupt ( u8 copy_u8INTPosition )
{
	if ( copy_u8INTPosition <= 31 )
	{
		NVIC_ICER0 = (1 << copy_u8INTPosition);  // Writing 0 has no effect 
	}
	else if ( copy_u8INTPosition <= 63 )
	{
		copy_u8INTPosition -= 32;
		NVIC_ICER1 = (1 << copy_u8INTPosition);  // Writing 0 has no effect 
	}
	else 
	{
		/* Error */
	}
	return;
}

void NVIC_voidSetPendingFlag   ( u8 copy_u8INTPosition )
{
	if ( copy_u8INTPosition <= 31 )
	{
		NVIC_ISPR0 = (1 << copy_u8INTPosition);  // Writing 0 has no effect 
	}
	else if ( copy_u8INTPosition <= 63 )
	{
		copy_u8INTPosition -= 32;
		NVIC_ISPR1 = (1 << copy_u8INTPosition);  // Writing 0 has no effect 
	}
	else 
	{
		/* Error */
	}
	return;
}

void NVIC_voidClearPendingFlag ( u8 copy_u8INTPosition )
{
	if ( copy_u8INTPosition <= 31 )
	{
		NVIC_ICPR0 = (1 << copy_u8INTPosition);  // Writing 0 has no effect 
	}
	else if ( copy_u8INTPosition <= 63 )
	{
		copy_u8INTPosition -= 32;
		NVIC_ICPR1 = (1 << copy_u8INTPosition);  // Writing 0 has no effect 
	}
	else 
	{
		/* Error */
	}
	return;
}

u8   NVIC_u8GetActiveFlag      ( u8 copy_u8INTPosition )
{
	u8 local_u8ActiveFlag = 0;
	if ( copy_u8INTPosition <= 31 )
	{
		local_u8ActiveFlag = GET_BIT(NVIC_IABR0, copy_u8INTPosition) ; 
	}
	else if ( copy_u8INTPosition <= 63 )
	{
		copy_u8INTPosition -= 32;
		local_u8ActiveFlag = GET_BIT(NVIC_IABR1, copy_u8INTPosition) ; 
	}
	else 
	{
		/* Error */
	}
	return local_u8ActiveFlag;
}


void NVIC_voidSetPriority ( s8 copy_s8INTPosition, u8 copy_u8GroupPriority, u8 copy_u8SubPriority, u32 copy_u32GroupType )
{
	if ( copy_s8INTPosition >= 0 )
		NVIC_IPR[copy_u8INTPosition] = ( (copy_u8SubPriority) | (copy_u8GroupPriority) << ( ( copy_u32GroupType - GROUP3 ) / 256 ) ) << 4;
	else
	{
		// Internal Peripherals */
		/*
		switch ( copy_s8INTPosition )
		{
			case MemManageFault : 
			SCB_SHPR1 &= ~( 0b1111 << 4 );
			SCB_SHPR1 |= 
			
			
			
			
		}
		*/
	}
	SCB_AIRCR = copy_u32GroupType;
	return;
}

