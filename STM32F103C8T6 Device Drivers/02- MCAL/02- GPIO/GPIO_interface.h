/*******************************************/
/* Author  : Mahmoud Ayman                 */
/* Date    : 17 NOV 2020                   */
/* Version : V01                           */
/*******************************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_config.h"
#include "GPIO_private.h"

#define HIGH      (1)
#define LOW       (0)
/* PORTS DEFINITIONS */
#define GPIOA     (0)
#define GPIOB     (1)
#define GPIOC     (2)

/* PINS DEFINITIONS */
#define PIN0      (0)
#define PIN1      (1)
#define PIN2      (2)
#define PIN3      (3)
#define PIN4      (4)
#define PIN5      (5)
#define PIN6      (6)
#define PIN7      (7)
#define PIN8      (8)
#define PIN9      (9)
#define PIN10     (10)
#define PIN11     (11)
#define PIN12     (12)
#define PIN13     (13)
#define PIN14     (14)
#define PIN15     (15)

/* MODES DEFINITIONS FOR EACH PIN */

/* INPUT MODES */
#define GPIO_INPUT_ANALOG          (0b0000)
#define GPIO_INPUT_FLOATING        (0b0100)
#define GPIO_INPUT_PULL            (0b1000)

/* OUTPUT MODES WITH 10 MHZ */
#define GPIO_OUTPUT_TEN_PP         (0b0001)
#define GPIO_OUTPUT_TEN_OD         (0b0101)
#define GPIO_AF_OUTPUT_TEN_PP      (0b1001)
#define GPIO_AF_OUTPUT_TEN_OD      (0b1101)

/* OUTPUT MODES WITH 2 MHZ */
#define GPIO_OUTPUT_TWO_PP         (0b0010)
#define GPIO_OUTPUT_TWO_OD         (0b0110)
#define GPIO_AF_OUTPUT_TOW_PP      (0b1010)
#define GPIO_AF_OUTPUT_TOW_OD      (0b1110)

/* OUTPUT MODES WITH 50 MHZ */
#define GPIO_OUTPUT_FIF_PP         (0b0011)
#define GPIO_OUTPUT_FIF_OD         (0b0111)
#define GPIO_AF_OUTPUT_FIF_PP      (0b1011)
#define GPIO_AF_OUTPUT_FIF_OD      (0b1111)

/* Functions Prototypes */

/* Initializing GPIO According to the configuration file */
void GPIO_voidGPIOInit(void);

void GPIO_voidSetPinDirection(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Mode);

void GPIO_voidSetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Value);

u8 GPIO_u8GetPinValue(u8 copy_u8Port, u8 copy_u8Pin );

#endif /* GPIO_INTERFACE_H */