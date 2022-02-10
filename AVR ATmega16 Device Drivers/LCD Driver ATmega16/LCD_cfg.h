#ifndef LCD_cfg
#define LCD_cfg
/* Set Pin number that will be used */
#define RS    0
#define RW    1
#define E     2
#define D0    16
#define D1    17
#define D2    18
#define D3    19
#define D4    20
#define D5    21
#define D6    22
#define D7    23
// Set options for initializations
#define ID	  1			 /* Set cursor moving direction */
#define SH	  0			 /* Set display shifting */
#define D	  1   		 /* Set display ON or OFF */
#define C	  1			 /* Cursor appears or not */
#define B	  0  		 /* Blinking of the cursor */
#define DL	  1			 /* Set Interface Data length */ 
#define N	  1   		 /* Number of line used */
#define F	  0			 /* Size of font */
// Entry mode set definition 
#if (!ID && !SH)
	#define EntryModeSet   0b00000100
#elif (!ID && SH)
	#define EntryModeSet   0b00000101
#elif (ID && !SH)
	#define EntryModeSet   0b00000110
#else 
	#define EntryModeSet   0b00000111
#endif
// Display control definition 
#if (!D && !C && !B) 
	#define DisplayControl 0b00001000         /* No display */
#elif (!D && !C && B) 
	#define DisplayControl 0b00001001		  /* No display */
#elif (!D && C && !B) 
	#define DisplayControl 0b00001010		  /* No display */
#elif (!D && C && B) 
	#define DisplayControl 0b00000011		  /* No display */
#elif (D && !C && !B) 
	#define DisplayControl 0b00001100  		  /* Display on, No cursor */
#elif (D && !C && B) 
	#define DisplayControl 0b00001101		  /* Display on, No cursor */
#elif (D && C && !B) 
	#define DisplayControl 0b00001110		  /* Display on, cursor on, No blinking */
#else 
	#define DisplayControl 0b00001111		  /* Display on, cursor on, blinking on */
#endif
// Function Set definition 
#if (!DL && !N && !F)
	#define FunctionSet    0b00100000         /* Data length : 4 bit, one line, small font */
#elif (!DL && !N && F)
	#define FunctionSet    0b00100100		  /* Data length : 4 bit, one line, large font */
#elif (!DL && N && !F)
	#define FunctionSet    0b00101000		  /* Data length : 4 bit, Two lines, small font */
#elif (!DL && N && F)
	#define FunctionSet    0b00101100		  /* Data length : 4 bit, Two lines, large font */
#elif (DL && !N && !F)
	#define FunctionSet    0b00110000		  /* Data length : 8 bit, one line, small font */
#elif (DL && !N && F)
	#define FunctionSet    0b00110100         /* Data length : 8 bit, one line, large font */
#elif (DL && N && !F)
	#define FunctionSet    0b00111000         /* Data length : 8 bit, Two lines, small font */
#else 
	#define FunctionSet    0b00111100         /* Data length : 8 bit, Two lines, large font */
#endif


#endif
