#ifndef LCD_int
#define LCD_int
#include "std_functions.h"
#include "std_types.h"
#include "DIO_int.h"
#include "LCD_cfg.h"
#include "../DIO Driver ATmega16/DIO_int.h"
#include <util/delay.h>
// functions prototypes
void LCD_WriteData(U8 copy_data);
void LCD_WriteCmd(U8 copy_cmd);
void LCD_SetCursor(U8 copy_byte_hori,U8 copy_byte_vert);
void LCD_Initialization(void);
void LCD_Clear(void);
void LCD_ShiftDisplay(U8 copy_direction, U8 copy_step);
void LCD_ShiftCursor(U8 copy_direction, U8 copy_step);
void LCD_Print(PU8 copy_string);
#endif
