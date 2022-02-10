// this file contains the implementation of the DIO functions 


#include "DIO_int.h"

/*This function initialize the DIO as user configration*/
void DIO_Initialization()
{
	/*DIO_SetPortValue(&DDRA,conc(PINDA0,PINDA1,PINDA2,PINDA3,PINDA4,PINDA5,PINDA6,PINDA7));
	DIO_SetPortValue(&DDRB,conc(PINDB0,PINDB1,PINDB2,PINDB3,PINDB4,PINDB5,PINDB6,PINDB7));
	DIO_SetPortValue(&DDRC,conc(PINDC0,PINDC1,PINDC2,PINDC3,PINDC4,PINDC5,PINDC6,PINDC7));
	DIO_SetPortValue(&DDRD,conc(PINDD0,PINDD1,PINDD2,PINDD3,PINDD4,PINDD5,PINDD6,PINDD7));
	DIO_SetPortValue(&PORTA,conc(PINA0,PINA1,PINA2,PINA3,PINA4,PINA5,PINA6,PINA7));
	DIO_SetPortValue(&PORTB,conc(PINB0,PINB1,PINB2,PINB3,PINB4,PINB5,PINB6,PINB7));
	DIO_SetPortValue(&PORTC,conc(PINC0,PINC1,PINC2,PINC3,PINC4,PINC5,PINC6,PINC7));
	DIO_SetPortValue(&PORTD,conc(PIND0,PIND1,PIND2,PIND3,PIND4,PIND5,PIND6,PIND7));*/
	assignport(DDRA,conc(PINDA0,PINDA1,PINDA2,PINDA3,PINDA4,PINDA5,PINDA6,PINDA7));
	assignport(DDRB,conc(PINDB0,PINDB1,PINDB2,PINDB3,PINDB4,PINDB5,PINDB6,PINDB7));
	assignport(DDRC,conc(PINDC0,PINDC1,PINDC2,PINDC3,PINDC4,PINDC5,PINDC6,PINDC7));
	assignport(DDRD,conc(PINDD0,PINDD1,PINDD2,PINDD3,PINDD4,PINDD5,PINDD6,PINDD7));
	assignport(PORTA,conc(PINA0,PINA1,PINA2,PINA3,PINA4,PINA5,PINA6,PINA7));
	assignport(PORTB,conc(PINB0,PINB1,PINB2,PINB3,PINB4,PINB5,PINB6,PINB7));
	assignport(PORTC,conc(PINC0,PINC1,PINC2,PINC3,PINC4,PINC5,PINC6,PINC7));
	assignport(PORTD,conc(PIND0,PIND1,PIND2,PIND3,PIND4,PIND5,PIND6,PIND7));
}
/*U8 DIO_GetPortValue(U8 LOC_U8_port)
{
	return LOC_U8_port;
}*/

/*void DIO_SetPortValue(PU8 LOC_U8_port,U8 LOC_U8_Value)
{
	*(LOC_U8_port) = ((*(LOC_U8_port) >> port_ShftRef) | (LOC_U8_Value));
}*/

/*void DIO_SetPinValue_ByPort(PU8 LOC_U8_port,U8 LOC_U8_PinNum,U8 LOC_U8_value)
{
	if (!LOC_U8_value)
	{
		clrbit(*(LOC_U8_port),LOC_U8_PinNum);
	}
	else
	{
		setbit(*(LOC_U8_port),LOC_U8_PinNum);
	}
}*/

/*U8 DIO_GetPinValue_ByPort(U8 LOC_U8_port,U8 LOC_U8_PinNum)
{
	return ((LOC_U8_port >> LOC_U8_PinNum) & shift_ref);
}*/

void DIO_SetPinDir(U8 LOC_U8_PinNum,U8 LOC_U8_PinDir)
{
	U8 port = LOC_U8_PinNum / 8;
	U8 LOC_U8_PinNumPortPer = LOC_U8_PinNum % 8;
	switch(port)
	{
		case 0 :
			assignbit(DDRB,LOC_U8_PinNumPortPer,LOC_U8_PinDir);
			break;
		case 1 :
			assignbit(DDRD,LOC_U8_PinNumPortPer,LOC_U8_PinDir);
			break;
		case 2 :
			assignbit(DDRC,LOC_U8_PinNumPortPer,LOC_U8_PinDir);
			break;
		case 3 :
			assignbit(DDRA,LOC_U8_PinNumPortPer,LOC_U8_PinDir);
			break;

	}	
}
void DIO_SetPinValue(U8 LOC_U8_PinNum,U8 LOC_U8_Pinvalue)
{
	U8 port = LOC_U8_PinNum / 8;
	U8 LOC_U8_PinNumPortPer = LOC_U8_PinNum % 8;
	switch(port)
	{
		case 0 :
			assignbit(PORTB,LOC_U8_PinNumPortPer,LOC_U8_Pinvalue);
			break;
		case 1 :
			assignbit(PORTD,LOC_U8_PinNumPortPer,LOC_U8_Pinvalue);
			break;
		case 2 :
			assignbit(PORTC,LOC_U8_PinNumPortPer,LOC_U8_Pinvalue);
			break;
		case 3 :
			assignbit(PORTA,LOC_U8_PinNumPortPer,LOC_U8_Pinvalue);
			break;
	}	
}
U8 DIO_GetPinValue(U8 LOC_U8_PinNum)
{
	U8 port = LOC_U8_PinNum / 8;
	U8 LOC_U8_PinNumPortPer = LOC_U8_PinNum % 8;
	U8 LOC_U8_RetPin = 0;
	switch(port)
	{
		case 0 :
			LOC_U8_RetPin =  getbit(PORTB,LOC_U8_PinNumPortPer);
			break;
		case 1 :
			LOC_U8_RetPin =  getbit(PORTD,LOC_U8_PinNumPortPer);
			break;
		case 2 :
			LOC_U8_RetPin =  getbit(PORTC,LOC_U8_PinNumPortPer);
			break;
		case 3 :
			LOC_U8_RetPin =  getbit(PORTA,LOC_U8_PinNumPortPer);
			break;
	}	
	return LOC_U8_RetPin;
}
/*This function takes the pin number (0 To 31) and the delay time and blink the selected
pin with the chosen delay time */
// Note : You have to configure the selected pin as output in the configuration file
void LED_Blink(U8 LOC_U8_PinNum,F64 LOC_F64_time)
{
	DIO_SetPinValue(LOC_U8_PinNum,HIGH);
	_delay_ms(LOC_F64_time);
	DIO_SetPinValue(LOC_U8_PinNum,LOW);
	_delay_ms(LOC_F64_time);
}



