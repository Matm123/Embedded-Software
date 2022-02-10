/*******************************************/
/* Author  : Mahmoud Ayman                 */
/* Date    : 29 OCT 2020                   */
/* Version : V01                           */
/*******************************************/

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

/* Bus Identifiers */
#define RCC_AHB                     (0)
#define RCC_APB1                    (1)
#define RCC_APB2                    (2)

/* Microcontroller Clock Output Selection (0:No clock, 1:SYSCLK, 2:HSI, 3:HSE, 4:PLL/2)*/ 
#define RCC_MCO    

/* AHB Peripherals Enable Bits (AHB Peripherals cannot be reseted) */ 
#define RCC_SDIO_ENABLE_BIT         (10)
#define RCC_FSMC_ENABLE_BIT         (8)
#define RCC_CRC_ENABLE_BIT          (6)
#define RCC_FLITF_ENABLE_BIT        (4)    /* ENABLE / DISABLE DURING SLEEP MODE */
#define RCC_SRAM_ENABLE_BIT         (2)    /* ENABLE / DISABLE DURING SLEEP MODE */
#define RCC_DMA2_ENABLE_BIT         (1)
#define RCC_DMA1_ENABLE_BIT         (0)

/* ABP2 Peripherals Enable Bits */
#define RCC_TIM11_ENABLERST_BIT        (21)
#define RCC_TIM10_ENABLERST_BIT        (20)
#define RCC_TIM9_ENABLERST_BIT         (19)
#define RCC_ADC3_ENABLERST_BIT         (15)
#define RCC_USART1_ENABLERST_BIT       (14)
#define RCC_TIM8_ENABLERST_BIT         (13)
#define RCC_SPI1_ENABLERST_BIT         (12)
#define RCC_TIM1_ENABLERST_BIT         (11)
#define RCC_ADC2_ENABLERST_BIT         (10)
#define RCC_ADC1_ENABLERST_BIT         (9)
#define RCC_IOPG_ENABLERST_BIT         (8)    /* IO PORT G CLOCK */
#define RCC_IOPF_ENABLERST_BIT         (7)
#define RCC_IOPE_ENABLERST_BIT         (6)
#define RCC_IOPD_ENABLERST_BIT         (5)
#define RCC_IOPC_ENABLERST_BIT         (4)
#define RCC_IOPB_ENABLERST_BIT         (3)
#define RCC_IOPA_ENABLERST_BIT         (2)
#define RCC_AFIO_ENABLERST_BIT         (0)   /* ALTERNATIVE FUNCTION IO CLOCK */

/* ABP1 Peripherals Enable Bits */
#define RCC_DAC_ENABLERST_BIT          (29)
#define RCC_PWR_ENABLERST_BIT          (28)
#define RCC_BKP_ENABLERST_BIT          (27)
#define RCC_CAN_ENABLERST_BIT          (25)
#define RCC_I2C2_ENABLERST_BIT         (22)
#define RCC_I2C1_ENABLERST_BIT         (21)
#define RCC_USART5_ENABLERST_BIT       (20)
#define RCC_USART4_ENABLERST_BIT       (19)
#define RCC_USART3_ENABLERST_BIT       (18)
#define RCC_USART2_ENABLERST_BIT       (17)
#define RCC_SPI3_ENABLERST_BIT         (15)
#define RCC_SPI2_ENABLERST_BIT         (14)
#define RCC_WWD_ENABLERST_BIT          (11)    /* WINDOW WATCHDOG */
#define RCC_TIM14_ENABLERST_BIT        (8)
#define RCC_TIM13_ENABLERST_BIT        (7)
#define RCC_TIM12_ENABLERST_BIT        (6)
#define RCC_TIM7_ENABLERST_BIT         (5)
#define RCC_TIM6_ENABLERST_BIT         (4)
#define RCC_TIM5_ENABLERST_BIT         (3)
#define RCC_TIM4_ENABLERST_BIT         (2)
#define RCC_TIM3_ENABLERST_BIT         (1)
#define RCC_TIM2_ENABLERST_BIT         (0)


/* Public functions prototypes */ 

/* The following two functions take the bus type (selected from bus identifiers),
   peripheral id (selected from above definitions) and enable/disable the clock for 
   the selected peripheral */
void RCC_voidEnableClock  (u8 Copy_u8BusId, u8 Copy_u8PerId);
void RCC_voidDisableClock (u8 Copy_u8BusId, u8 Copy_u8PerId);

/* The following function selects the CPU clock source according to the configuration file */
/* The user must make sure that the SYSCLK parameter is selected from clocks that configured 
   to be enabled */
void RCC_voidInitSysClock (void) ;

/* The following functions set prescalar for different buses and peripherals according to configurations */
void RCC_voidSetADCPrescalar  (u8 Copy_u8ADCPre);
void RCC_voidSetABP2Prescalar (u8 Copy_u8ABP2Pre);
void RCC_voidSetABP1Prescalar (u8 Copy_u8ABP1Pre);
void RCC_voidSetAHPPrescalar  (u8 Copy_u8AHPPre);

/* The following function takes the bus type (selected from bus identifiers),
   peripheral id (selected from above definitions) and software resets the
   selected peripheral */
void RCC_voidResetPer  (u8 Copy_u8BusId, u8 Copy_u8PerId);

#endif    /* RCC_INTERFACE_H */ 