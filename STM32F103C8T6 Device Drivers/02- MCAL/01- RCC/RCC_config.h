/*******************************************/
/* Author  : Mahmoud Ayman                 */
/* Date    : 29 OCT 2020                   */
/* Version : V01                           */
/*******************************************/

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H
#define TRUE         (1)
#define FALSE        (0)
/* HSI (HIGH SPEED INTERNAL CLOCK = 8 MHZ) CONFIGURATIONS (SELECTED BY DEFAULT) */
#define RCC_HSION    (TRUE)
/* Trimming is 16 by default. step = 40 kHz */ 
#define RCC_HSITRIM  

/* HSE (HIGH SPEED EXTERNAL CLOCK) (CRYSTAL - FROM 4 TO 16 MHZ) (RC - UP TO 25 MHZ) CONFIGURATIONS */
#define RCC_HSEON    (FALSE)
#if (RCC_HSEON == TRUE)			/* Configure the external clock source iff the external clock is enabled */
	#define RCC_HSEBYP	 (FALSE)
#endif

/* PLL (PHASE LOCKED LOOP) CONFIGURATIONS */ 
#define RCC_PLLON    (TRUE)

#if (RCC_PLLON == TRUE)
    /* Select the multiplier for PLL circuit (from 2 to 16) */
	#define RCC_PLLMUL   (2)
	/* Select the PLL input source. 0: HSI/2, 1:HSE. */
	#define RCC_PLLSRC   (0)
	/* Select whether the HSE input is divided by 2 (1) or not (0) */
	#if (RCC_PLLSRC == 1)
		#define RCC_PLLXTPRE (0)
	#endif
#endif 

/* BUSES AND PERIPHERALS PRESCALARS */


/* SYSCLK SELECTION (0:HSI, 1:HSE, 2:PLL)*/
#define SYSCLK      (0)

/* MCO SELCTION (0:No clock, 1:SYSCLK, 2:HSI, 3:HSE, 4:PLL/2) */
#define RCC_MCO_SELECTION (0)

/* CLOCK SECURITY SYSTEM ENABLE/DISABLE */
#define RCC_CSSON    (TRUE)

/* CLOCK INTERRUPTS OPTIONS */

 

#endif    /* RCC_CONFIG_H */ 