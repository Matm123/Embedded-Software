/*******************************************/
/* Author  : Mahmoud Ayman                 */
/* Date    : 17 NOV 2020                   */
/* Version : V01                           */
/*******************************************/

#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "NVIC_config.h"
#include "NVIC_private.h"

/* Positions Definitions (USE THESE DEFINITIONS IN FUNCTIONS CALLS) */
#define   NVIC_WWDG_INT_ENABLE_BIT                         (0)
#define   NVIC_PVD_INT_ENABLE_BIT                          (1)
#define   NVIC_TAMPER_INT_ENABLE_BIT                       (2)
#define   NVIC_RTC_INT_ENABLE_BIT                          (3)
#define   NVIC_FLASH_INT_ENABLE_BIT                        (4)
#define   NVIC_RCC_INT_ENABLE_BIT                          (5)
#define   NVIC_EXTI0_INT_ENABLE_BIT                        (6)
#define   NVIC_EXTI1_INT_ENABLE_BIT                        (7)
#define   NVIC_EXTI2_INT_ENABLE_BIT                        (8)
#define   NVIC_EXTI3_INT_ENABLE_BIT                        (9)
#define   NVIC_EXTI4_INT_ENABLE_BIT                        (10)
#define   NVIC_DMA1_CHANNEL1_INT_ENABLE_BIT                (11)
#define   NVIC_DMA1_CHANNEL2_INT_ENABLE_BIT                (12)
#define   NVIC_DMA1_CHANNEL3_INT_ENABLE_BIT                (13)
#define   NVIC_DMA1_CHANNEL4_INT_ENABLE_BIT                (14)
#define   NVIC_DMA1_CHANNEL5_INT_ENABLE_BIT                (15)
#define   NVIC_DMA1_CHANNEL6_INT_ENABLE_BIT                (16)
#define   NVIC_DMA1_CHANNEL7_INT_ENABLE_BIT                (17)
#define   NVIC_ADC1_2_INT_ENABLE_BIT                       (18)
#define   NVIC_USB_HP_CAN_TX_INT_ENABLE_BIT                (19)
#define   NVIC_USB_LP_CAN_RX0_INT_ENABLE_BIT               (20)
#define   NVIC_CAN_RX1_INT_ENABLE_BIT                      (21)
#define   NVIC_CAN_SCE_INT_ENABLE_BIT                      (22)
#define   NVIC_EXTI9_5_INT_ENABLE_BIT                      (23)
#define   NVIC_TIM1_BRK_INT_ENABLE_BIT                     (24)
#define   NVIC_TIM1_UP_INT_ENABLE_BIT                      (25)
#define   NVIC_TIM1_TRG_COM_INT_ENABLE_BIT                 (26)
#define   NVIC_TIM1_CC_INT_ENABLE_BIT                      (27)
#define   NVIC_TIM2_INT_ENABLE_BIT                         (28)
#define   NVIC_TIM3_INT_ENABLE_BIT                         (29)
#define   NVIC_TIM4_INT_ENABLE_BIT                         (30)
#define   NVIC_I2C1_EV_INT_ENABLE_BIT                      (31)
#define   NVIC_I2C1_ER_INT_ENABLE_BIT                      (32)
#define   NVIC_I2C2_EV_INT_ENABLE_BIT                      (33)
#define   NVIC_I2C2_ER_INT_ENABLE_BIT                      (34)
#define   NVIC_SPI1_INT_ENABLE_BIT                         (35)
#define   NVIC_SPI2_INT_ENABLE_BIT                         (36)
#define   NVIC_USART1_INT_ENABLE_BIT                       (37)
#define   NVIC_USART2_INT_ENABLE_BIT                       (38)
#define   NVIC_USART3_INT_ENABLE_BIT                       (39)
#define   NVIC_EXTI15_10_INT_ENABLE_BIT                    (40)
#define   NVIC_RTCAlarm_INT_ENABLE_BIT                     (41)
#define   NVIC_USBWakeup_INT_ENABLE_BIT                    (42)
#define   NVIC_TIM8_BRK_INT_ENABLE_BIT                     (43)
#define   NVIC_TIM8_UP_INT_ENABLE_BIT                      (44)
#define   NVIC_TIM8_TRG_COM_INT_ENABLE_BIT                 (45)
#define   NVIC_TIM8_CC_INT_ENABLE_BIT                      (46)
#define   NVIC_ADC3_INT_ENABLE_BIT                         (47)
#define   NVIC_FSMC_INT_ENABLE_BIT                         (48)
#define   NVIC_SDIO_INT_ENABLE_BIT                         (49)
#define   NVIC_TIM5_INT_ENABLE_BIT                         (50)
#define   NVIC_SPI3_INT_ENABLE_BIT                         (51)
#define   NVIC_UART4_INT_ENABLE_BIT                        (52)
#define   NVIC_UART5_INT_ENABLE_BIT                        (53)
#define   NVIC_TIM6_INT_ENABLE_BIT                         (54)
#define   NVIC_TIM7_INT_ENABLE_BIT                         (55)
#define   NVIC_DMA2_Channel1_INT_ENABLE_BIT                (56)
#define   NVIC_DMA2_Channel2_INT_ENABLE_BIT                (57)
#define   NVIC_DMA2_Channel3_INT_ENABLE_BIT                (58)
#define   NVIC_DMA2_Channel4_5_INT_ENABLE_BIT              (59)

/* Grouping Types */
#define   GROUP3               (0x05FA0300)
#define   GROUP4               (0x05FA0400)
#define   GROUP5               (0x05FA0500)
#define   GROUP6               (0x05FA0600)
#define   GROUP7               (0x05FA0700)

/* INTERNAL INTERRUPTS POSITIONS ( Use in setting priority for internal interrupts )*/
#define   MemManageFault       ( -1 )
#define   BusFault             ( -2 )
#define   UsageFault           ( -3 )
#define   SVCall               ( -4 )
#define   PendSV               ( -5 )
#define   SysTick              ( -6 )

void NVIC_voidEnableInterrupt  ( u8 copy_u8INTPosition );
void NVIC_voidDisableInterrupt ( u8 copy_u8INTPosition );
void NVIC_voidSetPendingFlag   ( u8 copy_u8INTPosition );
void NVIC_voidClearPendingFlag ( u8 copy_u8INTPosition );
u8   NVIC_u8GetActiveFlag      ( u8 copy_u8INTPosition );
void NVIC_voidSetPriority      ( s8 copy_s8INTPosition, u8 copy_u8GroupPriority, u8 copy_u8SubPriority, u32 copy_u32GroupType );

#endif  /* NVIC_INTERFACE_H */