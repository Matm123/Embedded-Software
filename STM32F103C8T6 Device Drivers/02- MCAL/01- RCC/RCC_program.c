/*******************************************/
/* Author  : Mahmoud Ayman                 */
/* Date    : 29 OCT 2020                   */
/* Version : V01                           */
/*******************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"
 

void RCC_voidEnableClock (u8 Copy_u8BusId, u8 Copy_u8PerId)
{
	if ( Copy_u8PerId <= 31)
	{
		switch ( Copy_u8BusId )
		{
			case RCC_AHB  : SET_BIT(RCC_AHBENR , Copy_u8PerId);       break;	
			case RCC_APB1 : SET_BIT(RCC_APB1ENR , Copy_u8PerId);      break;
			case RCC_APB2 : SET_BIT(RCC_APB2ENR , Copy_u8PerId);      break;
			default       :       return;    /* Error */              break;
		}				
	}
	else 
	{
		/* Error */
		return;
	}	
}


void RCC_voidDisableClock (u8 Copy_u8BusId, u8 Copy_u8PerId)
{
	if ( Copy_u8PerId <= 31)
	{
		switch ( Copy_u8BusId )
		{
			case RCC_AHB  : CLR_BIT(RCC_AHBENR , Copy_u8PerId);       break;	
			case RCC_APB1 : CLR_BIT(RCC_APB1ENR , Copy_u8PerId);      break;
			case RCC_APB2 : CLR_BIT(RCC_APB2ENR , Copy_u8PerId);      break;
			default       :       return;    /* Error */              break;
		}				
	}
	else 
	{
		/* Error */
		return;
	}	
}

void RCC_voidResetPer  (u8 Copy_u8BusId, u8 Copy_u8PerId)
{
	if ( Copy_u8PerId <= 31)
	{
		switch ( Copy_u8BusId )
		{
			case RCC_APB1RSTR : CLR_BIT(RCC_APB1ENR , Copy_u8PerId);      break;
			case RCC_APB2RSTR : CLR_BIT(RCC_APB2ENR , Copy_u8PerId);      break;
			default       :       return;    /* Error */                  break;
		}				
	}
	else 
	{
		/* Error */
		return;
	}	
	
}
void RCC_voidInitSysClock (void) 
{
	/* ENABLING AND CONFIGURING THE SELECTED CLOCKS ACCORDING TO THE CONFIGURATIONS */
	/* PLL and HSE clocks are disabled by default */
	#if (!RCC_PLLON && !RCC_HSEON && !RCC_HSION)
		/* This case is forbidden */
		/* Do nothing (HSI Selected) */
	#elif (!RCC_PLLON && !RCC_HSEON && RCC_HSION)  
		/* Do nothing (HSI Selected) */
	#elif (!RCC_PLLON && RCC_HSEON && !RCC_HSION)  
		#if (RCC_HSEBYP == TRUE)
			SET_BIT(RCC_CR, 18);
		#else 
			CLR_BIT(RCC_CR, 18);
		#endif
		SET_BIT(RCC_CR ,16);
		while (!GET_BIT(RCC_CR, 17));
		
		CLR_BIT(RCC_CR, 0);
	#elif (!RCC_PLLON && RCC_HSEON && RCC_HSION)  
		#if (RCC_HSEBYP == TRUE)
			SET_BIT(RCC_CR, 18);
		#else 
			CLR_BIT(RCC_CR, 18);
		#endif
		SET_BIT(RCC_CR ,16);
		while (!GET_BIT(RCC_CR, 17));
	#elif (RCC_PLLON && !RCC_HSEON && !RCC_HSION)
		/* This case is forbidden */ 
		/* PLL must be enabled with Internal or External clock */
	#elif (RCC_PLLON && !RCC_HSEON && RCC_HSION)  
		/* Set the PLL Multiplication Factor */
		RCC_CFGR |= ((RCC_PLLMUL - 2) << 18 );
		/* Set the PLL input source */
		CLR_BIT(RCC_CFGR, 16);
		SET_BIT(RCC_CR, 24);
		while (!GET_BIT(RCC_CR, 24));
		
	#elif (RCC_PLLON && RCC_HSEON && !RCC_HSION)
		/* Enable the HSE */
		#if (RCC_HSEBYP == TRUE)
			SET_BIT(RCC_CR, 18);
		#else 
			CLR_BIT(RCC_CR, 18);
		#endif
		SET_BIT(RCC_CR ,16);
		while (!GET_BIT(RCC_CR, 17));
		
		/* Set the PLL Multiplication Factor */
		RCC_CFGR |= ((RCC_PLLMUL - 2) << 18 );
		/* Set the PLL input source */
		#if (!RCC_PLLSRC) 
			CLR_BIT(RCC_CFGR, 16);
		#else 
			SET_BIT(RCC_CFGR, 16);
			#if (!RCC_PLLXTPRE)
				CLR_BIT(RCC_CFGR, 17);
			#else 
				SET_BIT(RCC_CFGR, 17);
			#endif
		#endif
		SET_BIT(RCC_CR, 24);
		while (!GET_BIT(RCC_CR, 24));
		
		CLR_BIT(RCC_CR, 0);

	#else   
		/* Enable the HSE */
		#if (RCC_HSEBYP == TRUE)
			SET_BIT(RCC_CR, 18);
		#else 
			CLR_BIT(RCC_CR, 18);
		#endif
		SET_BIT(RCC_CR ,16);
		while (!GET_BIT(RCC_CR, 17));
		
		/* Set the PLL Multiplication Factor */
		RCC_CFGR |= ((RCC_PLLMUL - 2) << 18 );
		/* Set the PLL input source */
		#if (!RCC_PLLSRC) 
			CLR_BIT(RCC_CFGR, 16);
		#else 
			SET_BIT(RCC_CFGR, 16);
			#if (!RCC_PLLXTPRE)
				CLR_BIT(RCC_CFGR, 17);
			#else 
				SET_BIT(RCC_CFGR, 17);
			#endif
		#endif
		SET_BIT(RCC_CR, 24);
		while (!GET_BIT(RCC_CR, 24));
	
	#endif
	
	/* ENABLE / DISABLE CLOCK SECURITY SYSTEM */
	#if (RCC_CSSON == TRUE)
		SET_BIT(RCC_CR ,19);
	#else 
		CLR_BIT(RCC_CR ,19);
	#endif
	
	/* SELECT THE SYSTEM CLOCK */
	RCC_CFGR |= SYSCLK;
	
	/* Set MCO */
	#if (!RCC_MCO_SELECTION)
		RCC_CFGR |= 0;
	#else 
		RCC_CFGR |= ( (RCC_MCO_SELECTION + 3) << 24 );
	#endif
		
	return; 
}
