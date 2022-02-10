/*******************************************/
/* Author  : Mahmoud Ayman                 */
/* Date    : 17 NOV 2020                   */
/* Version : V01                           */
/*******************************************/

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

/* Register Definitions for PORTA */
#define GPIO_PORTA_BASE_ADDRESS          (0x40010800) 
#define GPIO_PORTA_CRL                   *( (volatile u32*) (GPIO_PORTA_BASE_ADDRESS + 0x0)  )
#define GPIO_PORTA_CRH                   *( (volatile u32*) (GPIO_PORTA_BASE_ADDRESS + 0x04) )
#define GPIO_PORTA_IDR                   *( (volatile u32*) (GPIO_PORTA_BASE_ADDRESS + 0x08) )
#define GPIO_PORTA_ODR                   *( (volatile u32*) (GPIO_PORTA_BASE_ADDRESS + 0x0C) )
#define GPIO_PORTA_BSRR                  *( (volatile u32*) (GPIO_PORTA_BASE_ADDRESS + 0x10) )
#define GPIO_PORTA_BRR                   *( (volatile u32*) (GPIO_PORTA_BASE_ADDRESS + 0x14) )
#define GPIO_PORTA_LCKR                  *( (volatile u32*) (GPIO_PORTA_BASE_ADDRESS + 0x18) )

/* Register Definitions for PORTB */
#define GPIO_PORTB_BASE_ADDRESS          (0x40010C00) 
#define GPIO_PORTB_CRL                   *( (volatile u32*) (GPIO_PORTB_BASE_ADDRESS + 0x0)  )
#define GPIO_PORTB_CRH                   *( (volatile u32*) (GPIO_PORTB_BASE_ADDRESS + 0x04) )
#define GPIO_PORTB_IDR                   *( (volatile u32*) (GPIO_PORTB_BASE_ADDRESS + 0x08) )
#define GPIO_PORTB_ODR                   *( (volatile u32*) (GPIO_PORTB_BASE_ADDRESS + 0x0C) )
#define GPIO_PORTB_BSRR                  *( (volatile u32*) (GPIO_PORTB_BASE_ADDRESS + 0x10) )
#define GPIO_PORTB_BRR                   *( (volatile u32*) (GPIO_PORTB_BASE_ADDRESS + 0x14) )
#define GPIO_PORTB_LCKR                  *( (volatile u32*) (GPIO_PORTB_BASE_ADDRESS + 0x18) )





/* Register Definitions for PORTC */
#define GPIO_PORTC_BASE_ADDRESS          (0x40011000)
#define GPIO_PORTC_CRL                   *( (volatile u32*) (GPIO_PORTC_BASE_ADDRESS + 0x0)  )
#define GPIO_PORTC_CRH                   *( (volatile u32*) (GPIO_PORTC_BASE_ADDRESS + 0x04) )
#define GPIO_PORTC_IDR                   *( (volatile u32*) (GPIO_PORTC_BASE_ADDRESS + 0x08) )
#define GPIO_PORTC_ODR                   *( (volatile u32*) (GPIO_PORTC_BASE_ADDRESS + 0x0C) )
#define GPIO_PORTC_BSRR                  *( (volatile u32*) (GPIO_PORTC_BASE_ADDRESS + 0x10) )
#define GPIO_PORTC_BRR                   *( (volatile u32*) (GPIO_PORTC_BASE_ADDRESS + 0x14) )
#define GPIO_PORTC_LCKR                  *( (volatile u32*) (GPIO_PORTC_BASE_ADDRESS + 0x18) )



#endif /* GPIO_PRIVATE_H */