#ifndef External_Interrupts_int
#define External_Interrupts_int
#include "External_Interrupts_priv.h"
#include "std_types.h"
#include "std_functions.h"
#include "External_Interrupts_cfg.h"
#include "Regs.h"

/* For Callback Settings */
static void (*ptr_INT0)(void);
static void (*ptr_INT1)(void);
static void (*ptr_INT2)(void);

void External_Interrupts_init(void); /* Settings for MCUCR, MCUCSR, SREG and GICR */

/* Callback Setters */
void External_Interrupts_CallBack_0(void(*ptr_0)(void));
void External_Interrupts_CallBack_1(void(*ptr_1)(void));
void External_Interrupts_CallBack_2(void(*ptr_2)(void));

void External_Interrupts_SEI(void);    /* Global Interrupts Enable */
void External_Interrupts_CLI(void);    /* Global Interrupts Disable */

#endif
