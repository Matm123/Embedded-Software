/*!
 * Description:
 * ============================================================================================================
 * A FlexCAN module is initialized for 500 KHz (2 usec period) bit time based on an 8 MHz crystal.
 * Message buffer 0 and message buffer 1 transmit 8 byte messages over the can bus
 * Message buffer 2 is configured to receive from message buffer 0
 * Message buffer 3 is configured to receive from message buffer 1
 *
 * The following terms are to be discussed !!
 * To enable signals to the CAN bus, the SBC must be powered with external 12 V. EVBs with SBC
 * MC33903 require CAN transceiver configuration with SPI. EVBs with SBC UJA1169 do not require configuration.
 *
 */

#include "device_registers.h" /* include peripheral declarations S32K144 */
#include "Can.h"
#include "clocks_and_modes.h"
#include "LPUART.h"
#include "ADC.h"
void WDOG_disable (void)
{
	WDOG->CNT=0xD928C520;     /* Unlock watchdog 		*/
	WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value 	*/
	WDOG->CS = 0x00002100;    /* Disable watchdog 		*/
}

/* This function only initializes the pins needed for FlexCan0 */
void PORT_init (void)
{
	/*!
	 * Pins definitions
	 * ===================================================
	 *
	 * Pin number        | Function
	 * ----------------- |------------------
	 * PTE4              | CAN0_RX
	 * PTE5              | CAN0_TX
	 * PTD16			 | GPIO [GREEN LED]
	 */
	PCC->PCCn[PCC_PORTE_INDEX] |= PCC_PCCn_CGC_MASK;	/* Enable clock for PORTE */
	PORTE->PCR[4] |= PORT_PCR_MUX(5);	/* Port E4: MUX = ALT5, CAN0_RX */
	PORTE->PCR[5] |= PORT_PCR_MUX(5); /* Port E5: MUX = ALT5, CAN0_TX */

	PORTE->PCR[1] |= PORT_PCR_MUX(1);	/* Port E4: MUX = ALT1, Trigger */
	PORTE->PCR[3] |= PORT_PCR_MUX(1); /* Port E5: MUX = ALT1, Echo */
	PTE->PDDR |= (1 << 1);
	PTE->PDDR &= ~(1 << 3);

	PCC->PCCn[PCC_PORTD_INDEX]|=PCC_PCCn_CGC_MASK;   /* Enable clock for PORTD */
	//PORTD->PCR[0]  = PORT_PCR_MUX(1);	/*blue*/	/* Port D0: MUX = GPIO  */
	//PORTD->PCR[15] = PORT_PCR_MUX(1);	/*red*/  	/* Port D15: MUX = GPIO */
	PORTD->PCR[15] = PORT_PCR_MUX(1);	/*green*/  /* Port D16: MUX = GPIO 				*/
	//PTD->PDDR |= 1<<0;            	 /* Port D0: Data direction = output  */
	//PTD->PDDR |= 1<<15;            	 /* Port D15: Data direction = output  */
	PTD->PDDR |= 1<<15;            	 /* Port D16: Data direction = output  */
	/****************************************************************************/
	PCC->PCCn[PCC_PORTC_INDEX ]|=PCC_PCCn_CGC_MASK; /* Enable clock for PORTC */
	PORTC->PCR[6]|=PORT_PCR_MUX(2);	/* Port C6: MUX = ALT2, UART1 TX */
	PORTC->PCR[7]|=PORT_PCR_MUX(2);   /* Port C7: MUX = ALT2, UART1 RX */

	PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK;/* Enable clocks to peripherals (PORT modules) */
	PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK;/* Enable clock to PORT C*/
	/* Enable clock to PORT D*/

	/* Configure port C12 as GPIO input (BTN 0 [SW2] on EVB) */
	//PTC->PDDR &= ~(1<<PTC17);   /* Port C12: Data Direction= input (default) */
	PORTC->PCR[17] = PORT_PCR_MUX(1)
								 |PORT_PCR_PFE_MASK; /* Port C12: MUX = GPIO, input filter enabled */

}

void NVIC_init_IRQs (void)
{
	S32_NVIC->ICPR[2] = 1 << (81 % 32);  
	S32_NVIC->ISER[2] = 1 << (81 % 32);  
	S32_NVIC->IP[81] = 0xA;              
}

int main(void)
{
	/*!
	 * Initialization:
	 * =======================
	 */
	
	/* Project Description: 
	 1) Proximity Sensor was connected to IO Channel.
	 2) We have used the self-loop capability of the Can controller for testing the functionality of the code
	 3) Once the message is received in the mailbox, another message is transfered to the serial port of the computer using UART 
	 4) You can find this sequence handled in the ISR located in Can.c 
	 5) S32 Design Studio for ARM Version 2.2 was used for testing 
	*/
	
	Can_PduType msg1;
	extern const Can_ConfigType Can_ConfigType_Handle;
	uint32 Message = 0;

	msg1.length = 4;
	msg1.id = 0x111;
	/**********************************************************************************/

	/* Hardware Initializations */
	WDOG_disable();		 /* Disable WDOG */
	SOSC_init_8MHz();      /* Initialize system oscillator for 8 MHz xtal */
	SPLL_init_160MHz();    /* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz(); /* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */
	NVIC_init_IRQs();       /* Enable desired interrupts and priorities */
	PORT_init();             /* Configure ports */
	Can_Init(&Can_ConfigType_Handle);          /* Initialization of CanDriver */
	LPUART1_init();        /* Initialize LPUART @ 9600*/
	ADC_init();            /* Init ADC resolution 12 bit*/


	if (E_OK == Can_SetControllerMode(0, CAN_CS_STARTED))    /* Starting of FlexCan0 */
	{
		/* Do nothing */
		/* Controller 0 has been started successfully */
	}
	else
	{
		/* the starting is failed */
		return 0;
	}
	/***********************************************************************************/

	/* Continuously send msg1 (MB0) over the can bus */
	while (1)
	{
		msg1.sdu = &Message;
		/* Begin transmitting */
		if ( E_OK == Can_Write(0, &msg1) )
		{
			/* Do nothing */
			/* Write function has been executed successfully */
		}

	}


}
