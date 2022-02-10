#include "LCD_int.h"

// functions implementation
void LCD_WriteCmd(U8 LOC_cmd)    // This function writes command to LCD due to LCD_cfg.h
{
	DIO_SetPinValue(RS,0);
	DIO_SetPinValue(RW,0);
	DIO_SetPinValue(D0,getbit(LOC_cmd,0));
	DIO_SetPinValue(D1,getbit(LOC_cmd,1));
	DIO_SetPinValue(D2,getbit(LOC_cmd,2));
	DIO_SetPinValue(D3,getbit(LOC_cmd,3));
	DIO_SetPinValue(D4,getbit(LOC_cmd,4));
	DIO_SetPinValue(D5,getbit(LOC_cmd,5));
	DIO_SetPinValue(D6,getbit(LOC_cmd,6));
	DIO_SetPinValue(D7,getbit(LOC_cmd,7));
	DIO_SetPinValue(E,1);
	_delay_ms(2);
	DIO_SetPinValue(E,0);	
}
void LCD_WriteData(U8 LOC_data)  // This function writes data to LCD due to LCD_cfg.h
{
	DIO_SetPinValue(RS,1);
	DIO_SetPinValue(RW,0);
	DIO_SetPinValue(D0,getbit(LOC_data,0));
	DIO_SetPinValue(D1,getbit(LOC_data,1));
	DIO_SetPinValue(D2,getbit(LOC_data,2));
	DIO_SetPinValue(D3,getbit(LOC_data,3));
	DIO_SetPinValue(D4,getbit(LOC_data,4));
	DIO_SetPinValue(D5,getbit(LOC_data,5));
	DIO_SetPinValue(D6,getbit(LOC_data,6));
	DIO_SetPinValue(D7,getbit(LOC_data,7));
	DIO_SetPinValue(E,1);
	_delay_ms(2);
	DIO_SetPinValue(E,0);		
}
void LCD_SetCursor(U8 LOC_byte_hori,U8 LOC_byte_vert)
{
	U8 LOC_Start[] = {0x80,0xC0};
	LCD_WriteCmd(LOC_Start[LOC_byte_hori] + LOC_byte_vert);
}
void LCD_Clear()
{
	LCD_WriteCmd(0b00000001);
	_delay_ms(2);
}
void LCD_Initialization(void)   // Manipulates the initialization from LCD_cfg.h file
{
	_delay_ms(50);
	LCD_WriteCmd(FunctionSet);            
	_delay_ms(2);
	LCD_WriteCmd(DisplayControl);            
	_delay_ms(2);
	LCD_WriteCmd(EntryModeSet);
	_delay_ms(2);
	LCD_Clear();  
	_delay_ms(2);
	
}
void LCD_ShiftDisplay(U8 LOC_direction, U8 LOC_step)
{
	if (LOC_direction == 'R')
	{
		for (int i=0;i<LOC_step;++i)
		{
			LCD_WriteCmd(0b00011100);
			_delay_us(39);
		}
	}
	else if (LOC_direction == 'L')
	{
		for (int i=0;i<LOC_step;++i)
		{
			LCD_WriteCmd(0b00011000);
			_delay_us(39);
		}			
	}
}

void LCD_ShiftCursor(U8 LOC_direction, U8 LOC_step)
{
	if (LOC_direction == 'R')
	{
		for (int i=0;i<LOC_step;++i)
		{
			LCD_WriteCmd(0b00010100);
			_delay_us(39);
		}
	}
	else if (LOC_direction == 'L')
	{
		for (int i=0;i<LOC_step;++i)
		{
			LCD_WriteCmd(0b00010000);	
			_delay_us(39);
		}
	}
	
}
void LCD_Print(PU8 LOC_string)
{
	U8 i = 0;
	while(LOC_string[i] != '\0')
	{
		LCD_WriteData(LOC_string[i]);
		_delay_us(43);
		++i;
	}
}
