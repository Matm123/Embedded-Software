#ifndef SEG_int
#define SEG_int 
#include "../DIO Driver ATmega16/DIO_int.h"
#include "SEG_priv.h"
#include "SEG_int.h"
#include "SEG_cfg.h"
#include <util/delay.h>

void SEG_WriteCmnAnd(U8 copy_U8_num);
void SEG_WriteCmnCthd(U8 copy_U8_num); used for common cathode
void SEG_Initialization(void);

#endif