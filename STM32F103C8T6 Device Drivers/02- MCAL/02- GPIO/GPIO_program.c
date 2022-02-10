/*******************************************/
/* Author  : Mahmoud Ayman                 */
/* Date    : 17 NOV 2020                   */
/* Version : V01                           */
/*******************************************/
#include "GPIO_interface.h"



void GPIO_voidGPIOInit(void)
{
	
	
	return;
}

void GPIO_voidSetPinDirection(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Mode)
{
	switch (copy_u8Port)
	{
		case GPIOA :
			if (copy_u8Pin <= 7)
			{
				/* Write the Mode to CRL */ 
				GPIO_PORTA_CRL &= ~( (0b1111)    << (4 * copy_u8Pin) ) ;
				GPIO_PORTA_CRL |= ( (copy_u8Mode << (4 * copy_u8Pin) ) ; 
			}
			else
			{
				/* Write the Mode to CRH */
				copy_u8Pin -= 8;
				GPIO_PORTA_CRH &= ~( (0b1111)    << (4 * copy_u8Pin) ) ;
				GPIO_PORTA_CRH |= ( (copy_u8Mode << (4 * copy_u8Pin) ) ; 
			}
			break;
			
		case GPIOB :
			if (copy_u8Pin <= 7)
			{
				/* Write the Mode to CRL */ 
				GPIO_PORTB_CRL &= ~( (0b1111)    << (4 * copy_u8Pin) ) ;
				GPIO_PORTB_CRL |= ( (copy_u8Mode << (4 * copy_u8Pin) ) ; 
			}
			else
			{
				/* Write the Mode to CRH */ 
				copy_u8Pin -= 8;
				GPIO_PORTB_CRH &= ~( (0b1111)    << (4 * copy_u8Pin) ) ;
				GPIO_PORTB_CRH |= ( (copy_u8Mode << (4 * copy_u8Pin) ) ; 
			}
			break;

		case GPIOC :
			if (copy_u8Pin <= 7)
			{
				/* Write the Mode to CRL */ 
				GPIO_PORTC_CRL &= ~( (0b1111)    << (4 * copy_u8Pin) ) ;
				GPIO_PORTC_CRL |= ( (copy_u8Mode << (4 * copy_u8Pin) ) ; 
			}
			else
			{
				/* Write the Mode to CRH */ 
				copy_u8Pin -= 8;
				GPIO_PORTC_CRH &= ~( (0b1111)    << (4 * copy_u8Pin) ) ;
				GPIO_PORTC_CRH |= ( (copy_u8Mode << (4 * copy_u8Pin) ) ; 
			}
			break;
		
	}
	
	
	return;
}

void GPIO_voidSetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Value)
{
	if (copy_u8Pin <= 15)
	{
		switch ( copy_u8Port )
		{
			case GPIOA :
			if (HIGH == copy_u8Value)
				SET_BIT(GPIO_PORTA_ODR, copy_u8Pin);
			else if (LOW == copy_u8Value)
				CLR_BIT(GPIO_PORTA_ODR, copy_u8Pin);
			break;

			case GPIOB :
			if (HIGH == copy_u8Value)
				SET_BIT(GPIO_PORTB_ODR, copy_u8Pin);
			else if (LOW == copy_u8Value)
				CLR_BIT(GPIO_PORTB_ODR, copy_u8Pin);
			break;

			case GPIOC :
			if (HIGH == copy_u8Value)
				SET_BIT(GPIO_PORTC_ODR, copy_u8Pin);
			else if (LOW == copy_u8Value)
				CLR_BIT(GPIO_PORTC_ODR, copy_u8Pin);
			break;
			
		}
		
	}
	else 
	{
		/* Error */
		
	}
	return;
}

u8 GPIO_u8GetPinValue(u8 copy_u8Port, u8 copy_u8Pin )
{
	u8 local_u8PinValue = 0;
	if ( copy_u8Pin > 15)
	{
		/* Error */
	}
	else 
	{
		switch ( copy_u8Port )
		{
			case GPIOA : 
			local_u8PinValue = GET_BIT(GPIO_PORTA_IDR,copy_u8Pin);
			break;

			case GPIOB : 
			local_u8PinValue = GET_BIT(GPIO_PORTB_IDR,copy_u8Pin);
			break;

			case GPIOC : 
			local_u8PinValue = GET_BIT(GPIO_PORTC_IDR,copy_u8Pin);
			break;
			
		}
		
		
	}
	return local_u8PinValue;
	
}
