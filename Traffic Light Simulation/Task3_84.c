/*
 * Task3_84.c
 *
 *  Created on: Sep 23, 2019
 *      Author: MahmoudAyman
 */

#include <avr\delay.h>
#include "DIO_int.h"
#include "SEG_int.h"
#define F_CPU 8000000UL
typedef enum
{
	redState,
	greenState,
	yellowState
}colorState;
void Traffic_light(U8,colorState);
U8 green = 91;
U8 yellow = 16;
U8 red = 61;
U8 POVcount = 62;
int main()
{
	DIO_Initialization();
	SEG_Initialization();
	while(1)
	{
		setbit(PORTA,2);
		Traffic_light(green,greenState);
		clrbit(PORTA,2);
		setbit(PORTA,1);
		Traffic_light(yellow,yellowState);
		clrbit(PORTA,1);
		setbit(PORTA,0);
		Traffic_light(red,redState);
		clrbit(PORTA,0);
	}
	return 0;
}
void Traffic_light(U8 color,colorState state)
{
	U8 temp_color = color;
	while(1)
	{
		color--;
		while(POVcount--)
		{
			setbit(PORTD,0);
			SEG_WriteCmnAnd(color/10);
			_delay_ms(1);
			clrbit(PORTD,0);
			_delay_ms(1);
			setbit(PORTD,1);
	     	SEG_WriteCmnAnd(color%10);
			_delay_ms(1);
			clrbit(PORTD,1);
			_delay_ms(1);
		}
		if (color == 0 || (getbit(PINA,3) && state == greenState))
		{
			color = temp_color;
			POVcount = 62;
			break;
		}
	}
}
