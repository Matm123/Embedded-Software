#ifndef External_Interrupts_cfg
#define External_Interrupts_cfg

/* Initializing the interrupts :
   1) Triggered on Rising / Falling Edge
   2) Enabled / Disabled
*/

/* Interrupt Sense Control (INT1) */
#define ISC11 1
#define ISC10 0

/* Interrupt Sense Control (INT0) */
#define ISC00 0
#define ISC01 0

/* Interrupt Sense Control (INT2) */
#define ISC2 0

/* Interrupts Enabling */
#define GICR_INT0 1
#define GICR_INT1 0
#define GICR_INT2 0


#endif
