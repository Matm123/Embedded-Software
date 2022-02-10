#include "Can.h"
#include "Det.h"
#include "LPUART.h"
#include "S32_core_cm4.h"
static uint8 rx_count = 0; // For testing purposes
static Can_ModuleStateType CAN_MODULE_STATE = CAN_UNINIT;    /* Very important variable used to hold the current state of the can driver */
static Can_ControllerStateType CAN_CONTROLLERS_STATES[] = {CAN_CS_UNINIT,CAN_CS_UNINIT,CAN_CS_UNINIT};  /* An array used to hold the current state of each CanController */
static uint32 CAN_BASE_ADDRESSES[NUM_OF_CONTROLLERS] = {CAN_0_BASE_ADDRESS, CAN_1_BASE_ADDRESS, CAN_2_BASE_ADDRESS}; /* An array used to hold the base address of each CanController */
static Can_ConfigType* TempConfig = NULL_PTR;   /* Temporary configuration pointer to store the configuration for Can_SetControllerMode(CAN_CS_STARTED) usage */
static uint32* RAMn = NULL_PTR;
static uint32* RXIMRn = NULL_PTR;
static uint32 PCC_CAN_OFFSETS[NUM_OF_CONTROLLERS] = {0x90,0x94,0xAC}; /* An array used to hold the PCC register address for each CanController */
static uint8 TotalNumOfBuffers[NUM_OF_CONTROLLERS] = {NUM_OF_TX_BUFFERS_0 + NUM_OF_RX_BUFFERS_0, NUM_OF_TX_BUFFERS_1 + NUM_OF_RX_BUFFERS_1, NUM_OF_TX_BUFFERS_2 + NUM_OF_RX_BUFFERS_2}; /* An array used to hold the number of configured buffers for each CanController */
static uint8 MAXMB[NUM_OF_CONTROLLERS] = {64, 64, 64};   /* An array used to hold the size (in 4 bytes) of BufferRAM for each CanController */
static uint8 NumOfIntDis[NUM_OF_CONTROLLERS] = {1,1,1};   /* Number of calls of the Can_DisableControllerInterrupts() Function for each controller (1 because the interrupts are initially disabled) */
static uint8 BufferCounter = 0;   /* Counter to count inside the hardware object array */
static uint8 TxBufferCounter = 0; /* Counter to store tx buffers informations in Can_HTH_Array */
static uint8 RxBufferCounter = 0; /* Counter to store rx buffers informations in Can_HTH_Array */
static uint8 HOCounter = 0;       /* Hardware Object counter */

static uint8 i;
static uint32 j;
/* The following two types are implying that when the user wants to write any message on the can bus,
   he will choose the buffer from the Tx array, These 2 arrays are filled from the initialization function 
   according to the PBcfg.h file.
 */
static CanHardwareObject Can_HTH_Array[NUM_OF_TX_BUFFERS_0 + NUM_OF_TX_BUFFERS_1 + NUM_OF_TX_BUFFERS_2];    /* Array that will hold the Tx buffers informations */
static CanHardwareObject Can_HRH_Array[NUM_OF_RX_BUFFERS_0 + NUM_OF_RX_BUFFERS_1 + NUM_OF_RX_BUFFERS_2];    /* Array that will hold the Rx buffers informations */


void Can_Init( const Can_ConfigType* Config )
{
	DISABLE_INTERRUPTS()      /* Macro in S32_core_cm4.h */
																	uint8 Can_ControllerIndex = 0;  /* used for counting CanControllers */
	uint8 BufferConfigCounter = 0;  /* used for counting buffers */
	uint8 RAMCounter = 0;           /* used for accessing BuffersRAM */
	/* [SWS_Can_00174] If development error detection for the Can module is enabled: 
	The function Can_Init shall raise the error CAN_E_TRANSITION if the driver is not in state CAN_UNINIT */
	/* [SWS_Can_00408] If development error detection for the Can module is enabled: 
	The function Can_Init shall raise the error CAN_E_TRANSITION if the CAN controllers are not in state UNINIT */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
	if (NULL_PTR == Config)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x00U, CAN_E_PARAM_POINTER);
	}
	else if ( (CAN_UNINIT != CAN_MODULE_STATE) || (CAN_CS_UNINIT != CAN_CONTROLLERS_STATES[0]) || (CAN_CS_UNINIT != CAN_CONTROLLERS_STATES[1]) || (CAN_CS_UNINIT != CAN_CONTROLLERS_STATES[2]) )
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x00U, CAN_E_TRANSITION);
	}
	else
	{
		/* MISRA */
	}
#endif
	TempConfig = (Can_ConfigType*)Config;     /* Storing the configurations for future usage */

	/* [SWS_Can_00259] The function Can_Init shall set all CAN controllers in the state STOPPED */
	/* It will call the function Can_SetControllerMode(CAN_CS_STOPPED) which is not implemented yet */
	/* Looping on CanControllers */
	for (Can_ControllerIndex = 0 ; Can_ControllerIndex < NUM_OF_CONTROLLERS ; Can_ControllerIndex++)
	{
		/* Checking if the controller is used in the configuration */
		if (TRUE == (Config->CanController_ptr[Can_ControllerIndex].CanControllerActivation) )
		{
			/* We must enable the clock for the CAN controller through the PCC module */ 
			/* This must be done by the MCU driver */
			/* Until implementing the MCU driver, the Clock will be enabled manually */ 
			HW_Register(PCC_BASE_ADDRESS + PCC_CAN_OFFSETS[Can_ControllerIndex]) |= (1 << 30);

			/* MCR Initialization */
			HW_Register(Config->CanController_ptr[Can_ControllerIndex].CanControllerBaseAddress + MCR) |= (1 << MDIS);  /* Disable the Can Controller to select clock source */
			HW_Register((Config->CanController_ptr[Can_ControllerIndex].CanControllerBaseAddress)+CTRL1) &= ~(1 << CLKSRC);
			HW_Register(Config->CanController_ptr[Can_ControllerIndex].CanControllerBaseAddress + MCR) &= ~(1 << MDIS);  /* Enable the Can Controller */
			while(! ( (HW_Register((CAN_BASE_ADDRESSES[Can_ControllerIndex] + MCR) ) & (1 << FRZACK) )));
			HW_Register(Config->CanController_ptr[Can_ControllerIndex].CanControllerBaseAddress + MCR) |= ( (1 << AEN) | (1 << IRMQ) );   /* Enable Abort enable feature and individual masking*/
			CAN_CONTROLLERS_STATES[Can_ControllerIndex] = CAN_CS_STOPPED;

			HW_Register((Config->CanController_ptr[Can_ControllerIndex].CanControllerBaseAddress)+CTRL1) |= (1 << 12);

			/* Make RAMn points to the first BufferRAM location */ 
			RAMn = (uint32*) ( Config->CanController_ptr[Can_ControllerIndex].CanControllerBaseAddress + FIRSTOFFSET );
			/* Make RXIMRn points to the first Mask register */
			RXIMRn = (uint32*) ( Config->CanController_ptr[Can_ControllerIndex].CanControllerBaseAddress + MASKOFFSET );

			/* CTRL1 Initialization */
			/* if the CAN_SET_BAUDRATE_API is turned off, the driver will initialize each controller baud rate according to configuration */
			/* if the CAN_SET_BAUDRATE_API is turned on, the user must call CAN_SET_BAUDRATE After initialization to set the baud rate from baud rates array located in PBcfg.c */
#if (CAN_SET_BAUDRATE_API == STD_OFF)
			HW_Register((Config->CanController_ptr[Can_ControllerIndex].CanControllerBaseAddress)+CTRL1) |= ((Config->CanController_ptr[Can_ControllerIndex].CanControllerDefaultBaudrate->CanControllerPropSeg)<<PROPSEG) | ((Config->CanController_ptr[Can_ControllerIndex].CanControllerDefaultBaudrate->CanControllerSeg1)<<PSEG1) | ((Config->CanController_ptr[Can_ControllerIndex].CanControllerDefaultBaudrate->CanControllerSeg2)<<PSEG2) | ((Config->CanController_ptr[Can_ControllerIndex].CanControllerDefaultBaudrate->CanControllerSyncJumpWidth)<<RJW) | (1 << ERRMSK) | (1 << BOFFREC) ;
#endif

			/* Message Buffers Initialization :
			a. The control and status word of all message buffers must be initialized. 
			b. If Rx FIFO was enabled, the ID filter table must be initialized. 
			c. Other entries in each message buffer should be initialized as required
			 */
			/*test
			if(RAMn == NULL_PTR)
			HW_Register(0x400FF0C4) |= (1 << 16);
			 */
			for (RAMCounter = 0; RAMCounter < MAXMB[Can_ControllerIndex]; RAMCounter++)  /* FlexCAN0 32 MB, FlexCAN1,2 = 16 MB */
			{
				//RAMn[RAMCounter] = 0;
				*(RAMn++) = 0;    /* Clearing all message buffers */
			}
			/* Resetting RAMn to point to the first Buffer location */
			RAMn = (uint32*) ( Config->CanController_ptr[Can_ControllerIndex].CanControllerBaseAddress + FIRSTOFFSET );
			/* The FlexCan0 MAXMB bits (located in MCR register) were initialized as the reset value = 16 buffers */
			/* But we will be using 2 buffers for each module */
			/* The user can configure it through NUM_OF_TX_BUFFERS, NUM_OF_RX_BUFFERS located in Can.h */
			/* The number configured by the user must be consistent with the Can_PBcfg.c file */   
			/* The user must define the hardware objects in order of (0, 1, 2), means all hardware objects of FlexCan0 must be defined first */
			/* The hardware objects must be defined in CanHardwareObject_arr located in PBcfg.c */

			/* The following loop is used to initialize each buffer according to configuration file */
			/* CanFD is not enabled, we use the default MB size of (4*32) bits */
			/* BufferConfigCounter is Buffer Counter for each CanController */
			/* BufferCounter is a counter inside the CanHardwareObject_ptr */
			for (BufferConfigCounter = 0 ; BufferConfigCounter < (TotalNumOfBuffers[Can_ControllerIndex]) ; BufferConfigCounter++)
			{
				if (STANDARD == Config->CanHardwareObject_ptr[(BufferCounter) ].CanIdType)
				{
					/* Writing to MB IDE bit (21) */
					*(RAMn) |= (1 << 21);
					if (TRANSMIT == Config->CanHardwareObject_ptr[BufferCounter].CanObjectType)
					{
						/* Fill the Tx buffers array */ 
						Can_HTH_Array[TxBufferCounter++] = Config->CanHardwareObject_ptr[BufferCounter];

						/* Writing the MB code as TX INACTIVE */
						/* It is important to write the buffer as inactive as that will help checking if the buffer busy or not */
						*(RAMn) |= (8 << 24);	/* Code = 0b1000 in bits (24 - 27) */
						//HW_Register(0x400FF0C4) |= (1 << 16);
					}
					else if(RECEIVE == Config->CanHardwareObject_ptr[BufferCounter].CanObjectType)
					{
						/* Fill the Rx buffers array */
						Can_HRH_Array[RxBufferCounter++] = Config->CanHardwareObject_ptr[BufferCounter];
						/* Writing the MB code as RX EMPTY */
						*(RAMn) |= (4 << 24);	/* Code = 0b0100 in bits (24 - 27) */

						/* Writing the corresponding MASK */
						*(RXIMRn++) = Config->CanHardwareObject_ptr[BufferCounter].CanHWFilterRef->CanHwFilterMask;

						/* Writing the HWFilterCode to the ID of Rx Buffer */
						HW_Register ( (uint32*) (Config->CanHardwareObject_ptr[BufferCounter].CanControllerRef->CanControllerBaseAddress + FIRSTOFFSET + (Config->CanHardwareObject_ptr[BufferCounter].CanObjectId) * 16 ) + 1) |= Config->CanHardwareObject_ptr[BufferCounter].CanHWFilterRef->CanHwFilterCode << 18;
						//HW_Register(0x400FF0C8) |= (1 << 16);

					}
				}

				else /* The ID is extended */
				{

					/* Writing to MB IDE bit (21) */
					*(RAMn) &= ~(1 << 21);

					if (TRANSMIT == Config->CanHardwareObject_ptr[BufferCounter].CanObjectType)
					{
						/* Fill the Tx buffers array */ 
						Can_HTH_Array[TxBufferCounter++] = Config->CanHardwareObject_ptr[BufferCounter];

						/* Writing the MB code as TX INACTIVE */
						/* It is important to write the buffer as inactive as that will help checking if the buffer busy or not */
						*(RAMn) |= (8 << 24);	/* Code = 0b1000 in bits (24 - 27) */
					}
					else 
					{
						/* Fill the Rx buffers array */
						Can_HRH_Array[RxBufferCounter++] = Config->CanHardwareObject_ptr[BufferCounter];

						/* Writing the MB code as RX EMPTY */
						*(RAMn) |= (4 << 24);	/* Code = 0b0100 in bits (24 - 27) */

						/* Writing the corresponding MASK */
						*(RXIMRn++) = Config->CanHardwareObject_ptr[BufferCounter].CanHWFilterRef->CanHwFilterMask;

						/* Writing the HWFilterCode to the ID of Rx Buffer */
						HW_Register ( (uint32*) (Config->CanHardwareObject_ptr[BufferCounter].CanControllerRef->CanControllerBaseAddress + FIRSTOFFSET + (Config->CanHardwareObject_ptr[BufferCounter].CanObjectId * 16) ) + 1) |= Config->CanHardwareObject_ptr[BufferCounter].CanHWFilterRef->CanHwFilterCode << 18;

					}
				}
				BufferCounter++;
				RAMn += 4;       /* Pointing to the next MB */
			}
		}

		/* The Controller is not used in the configuration */
		/*else
		{
			// Disable the Controller
			HW_Register(Config -> CanController_ptr[Can_ControllerIndex].CanControllerBaseAddress + MCR) |= (1 << MDIS);
		}*/
	}
	CAN_MODULE_STATE = CAN_READY;   /* Change the state of the driver to CAN_READY */


	ENABLE_INTERRUPTS()
}

/* This function reads the version located in Can.h and saves it in Std_VersionInfoType */
void Can_GetVersionInfo( Std_VersionInfoType* versioninfo )
{	  
#if (CAN_DEV_ERROR_DETECT == STD_ON)
	if (NULL_PTR == versioninfo)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x07U, CAN_E_PARAM_POINTER);
	}
	else
	{
		/* MISRA */
	}
#endif      /* CAN_DEV_ERROR_DETECT */
	versioninfo->vendorID = CAN_VENDOR_ID;
	versioninfo->moduleID = CAN_MODULE_ID;
	versioninfo->sw_major_version = CAN_SW_MAJOR_VERSION;
	versioninfo->sw_minor_version = CAN_SW_MINOR_VERSION;
	versioninfo->sw_patch_version = CAN_SW_PATCH_VERSION;

	return;	
}

void Can_DeInit( void )
{
	DISABLE_INTERRUPTS()         /* Non-reentrant function */
																	uint8 Can_ControllerIndex = 0;
#if (CAN_DEV_ERROR_DETECT == STD_ON)
	if (CAN_READY != CAN_MODULE_STATE)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x10U,  CAN_E_TRANSITION );
	}
	else if ( (CAN_CS_STARTED == CAN_CONTROLLERS_STATES[0]) || (CAN_CS_STARTED == CAN_CONTROLLERS_STATES[1]) || (CAN_CS_STARTED == CAN_CONTROLLERS_STATES[2]) )
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x10U,  CAN_E_TRANSITION );
	}
	else
	{
		/* MISRA */
	}
#endif      /* CAN_DEV_ERROR_DETECT */
	for (Can_ControllerIndex = 0 ; Can_ControllerIndex < NUM_OF_CONTROLLERS ; Can_ControllerIndex++)
	{
		HW_Register(CAN_BASE_ADDRESSES[Can_ControllerIndex] + MCR) |= (1 << MDIS); /* Disable the controller */
		CAN_CONTROLLERS_STATES[Can_ControllerIndex] = CAN_CS_UNINIT;	
	}
	CAN_MODULE_STATE = CAN_UNINIT;
	ENABLE_INTERRUPTS()	
	return;
}



#if (CAN_BUSOFF_PROCESSING == POLLING)
/* Can_MainFunction_BusOff() implementation here */ 
#endif /*CAN_BUSOFF_PROCESSING*/

#if (CAN_TX_PROCESSING == POLLING)
/* Can_MainFunction_Write() implementation here */
#endif /*CAN_TX_PROCESSING*/

#if (CAN_RX_PROCESSING == POLLING)
/* Can_MainFunction_Read() implementation here */
#endif /*CAN_RX_PROCESSING*/ 


/* The user can select one of the baud rates from the baud rates array located in the PBcfg.c file */
/* I think the user supposed to initialize the CAN controller without writing the bit timing When this API is enabled */
/* When this API is enabled, after initialization the user supposed to Call this service to configure bit timing */
/* When this function is disabled, the initialization function will write bit timing as the element number zero (BaudrateConfigID=0) */
/* The Caller of this function must call first Can_SetControllerMode(CAN_CS_STOPPED) before calling this function or call it after initialization before starting the controller */
#if (CAN_SET_BAUDRATE_API == STD_ON)
Std_ReturnType Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID )
{
#if (CAN_DEV_ERROR_DETECT == STD_ON)
	if (CAN_READY != CAN_MODULE_STATE)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x0fU, CAN_E_UNINIT );
		return E_NOT_OK;
	}
	else if (BaudRateConfigID > 65535)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x0fU,  CAN_E_PARAM_BAUDRATE  );
		return E_NOT_OK;
	}
	else if (Controller > NUM_OF_CONTROLLERS)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x0fU, CAN_E_PARAM_CONTROLLER );
		return E_NOT_OK;

	}
	/* Need Discussion : [SWS_CAN_00500] If the requested baud rate change can not performed without a re-initialization of the CAN Controller E_NO_OK shall be returned */
	else if (CAN_CS_STOPPED != CAN_CONTROLLERS_STATES[Controller])
	{
		return E_NOT_OK;
	}
	else
	{
		/* MISRA */
	}
#endif /* CAN_DEV_ERROR_DETECT */
	/* Selecting Baudrate configuration from the array of configurations according to ConfigID */
	HW_Register(CAN_BASE_ADDRESSES[Controller]+CTRL1) |= (TempConfig->CanControllerBaudrateConfig_ptr[BaudRateConfigID].CanControllerPropSeg)<<PROPSEG | (TempConfig->CanControllerBaudrateConfig_ptr[BaudRateConfigID].CanControllerSeg1)<<PSEG1 | (TempConfig->CanControllerBaudrateConfig_ptr[BaudRateConfigID].CanControllerSeg2)<<PSEG2 | (TempConfig->CanControllerBaudrateConfig_ptr[BaudRateConfigID].CanControllerSyncJumpWidth)<<RJW | (1 << ERRMSK) | (1 << BOFFREC) ;
	return E_OK;
}
#endif   /* CAN_SET_BAUDRATE_API */


/* This function shall disable all interrupts of a CAN controller */
/* The default by the init function is that all the message buffer interrupts are disabled */
/* The user need to call Can_EnableControllerInterrupts to enable message buffers interrupts */
/* Types of interrupts in each Can Controller :
1) Message buffer interrupts (IMASK1 Register)
2) Warning interrupts (MCR_21, ESR1)
3) BusOff interrupt (CTRL1_15, ESR1_2)
4) Error interrupt (CTRL1_14, ESR1)
5) Tx warning interrupt (MCR_21, CTRL1_11, ESR1_17)
6) Rx warning interrupt (MCR_21, CTRL1_10, ESR1_16)
 */

void Can_DisableControllerInterrupts( uint8 Controller )
{
#if (CAN_DEV_ERROR_DETECT==STD_ON)
	if (CAN_READY != CAN_MODULE_STATE)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x04U, CAN_E_UNINIT );
	}
	else if (Controller > NUM_OF_CONTROLLERS)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x04U, CAN_E_PARAM_CONTROLLER );
	}
	else
	{
		/* MISRA */
	}

#endif    /* CAN_DEV_ERROR_DETECT */

	/* [SWS_Can_00049]: The function Can_DisableControllerInterrupts shall access the CAN controller registers to
	disable all interrupts for that CAN controller only, if interrupts for that CAN Controller are enabled */
	if ((NumOfIntDis[Controller]++) == 0)      /* This function has not been called before = interrupts enabled */
	{
		/* Disabling the controller interrupts */
		HW_Register((CAN_BASE_ADDRESSES[Controller] + IMASK1)) &= (0x0);   /* Clear all register bits */
		HW_Register((CAN_BASE_ADDRESSES[Controller]) + MCR) &= ~(1 << WRNEN);
		HW_Register((CAN_BASE_ADDRESSES[Controller]) + CTRL1) &= ~( (1 << BOFFMSK) | (1 << RWRNMSK) | (1 << TWRNMSK) ) ;
	}
	else
	{
		/* MISRA */
	}

	return;
}


void Can_EnableControllerInterrupts( uint8 Controller )
{
#if (CAN_DEV_ERROR_DETECT==STD_ON)
	if (CAN_READY != CAN_MODULE_STATE)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x04U, CAN_E_UNINIT );
	}
	else if (Controller > NUM_OF_CONTROLLERS)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x04U, CAN_E_PARAM_CONTROLLER );
	}
	else
	{
		/* MISRA */
	}
#endif    /* CAN_DEV_ERROR_DETECT */
	if ( 0 == (NumOfIntDis[Controller]) )
	{
		/* [SWS_Can_00208]: The function Can_EnableControllerInterrupts shall perform no action when
		Can_DisableControllerInterrupts has not been called before */
	}
	else if ( --(NumOfIntDis[Controller]) == 0)   /* The disable function has been called before */
	{
		/* Enabling the interrupts */
		HW_Register((CAN_BASE_ADDRESSES[Controller] + IMASK1)) |= 0xffffffff;   /* Set all register bits */
		/* Enable warning interrupts and the busoff interrupt */
		HW_Register((CAN_BASE_ADDRESSES[Controller])+MCR) |= (1 << WRNEN);
		HW_Register((CAN_BASE_ADDRESSES[Controller])+CTRL1) |= ( (1 << BOFFMSK) | (1 << RWRNMSK) | (1 << TWRNMSK) ) ;
	}
	else
	{
		/* MISRA */
	}
	return;
}





/* Only Can_DeInit() function can set the controller in the state CAN_CS_UNINIT */
/* The request of Can_SetControllerMode(CAN_CS_UNINIT) is an invalid request */

Std_ReturnType Can_SetControllerMode( uint8 Controller, Can_ControllerStateType Transition )
{
	DISABLE_INTERRUPTS()       /* This function is non-reentrant */
																	uint8 RAMCounter = 0;
	uint8 BufferConfigCounter = 0;
#if (CAN_DEV_ERROR_DETECT==STD_ON)
	if (CAN_READY != CAN_MODULE_STATE)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x03U, CAN_E_UNINIT );
		return E_NOT_OK;
	}
	else if (Controller > NUM_OF_CONTROLLERS)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x03U, CAN_E_PARAM_CONTROLLER );
		return E_NOT_OK;

	}
	else if (CAN_CS_STARTED != Transition && CAN_CS_STOPPED != Transition && CAN_CS_SLEEP != Transition && CAN_CS_UNINIT == Transition)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x03U,  CAN_E_TRANSITION  );
		return E_NOT_OK;
	}
	else
	{
		/* MISRA */
	}

#endif    /* CAN_DEV_ERROR_DETECT */
	switch ( Transition )
	{
	/* [SWS_Can_00384]: Each time the CAN controller state machine is triggered with the state transition value
		CAN_CS_STARTED, the function Can_SetControllerMode shall re-initialize the CAN controller with the same 
		controller configuration set previously used by functions Can_SetBaudrate or Can_Init */
	/* [SWS_Can_00196]: The function Can_SetControllerMode shall enable / disable interrupts that are needed in the new state */
	/* Interrupts needed in the state STARTED: message buffer interrupts, busoff, error so we will call Can_EnableControllerInterrupts() */
	/* Interrupts needed in the states SLEEP, STOPPED : none so we will call Can_DisableControllerInterrupts() */
	case CAN_CS_STARTED:
		if (TRUE == (TempConfig -> CanController_ptr[Controller].CanControllerActivation) )
		{
			RAMn = (uint32*)(TempConfig -> CanController_ptr[Controller].CanControllerBaseAddress + FIRSTOFFSET);       /* First element in the array is the first message buffer */
			RXIMRn = (uint32*)(TempConfig -> CanController_ptr[Controller].CanControllerBaseAddress + MASKOFFSET);
			/* Re-initialize the selected controller according to the original configuration */
			/* will use the configurations of Can_init() to re-initialize */

			/* Enabling of The Clock using the PCC Module */
			HW_Register(PCC_BASE_ADDRESS + PCC_CAN_OFFSETS[Controller]) |= (1 << 30);

			/* re-initialization of the MCR */
			HW_Register( (TempConfig ->CanController_ptr[Controller].CanControllerBaseAddress) + MCR) &= ~(1 << MDIS);  /* Enable the Can Controller */
			HW_Register( (TempConfig ->CanController_ptr[Controller].CanControllerBaseAddress) + MCR) |= ( (1 << AEN) | (1 << IRMQ) );   /* Enable Abort enable feature */


			/* re-initialization of the CTRL1 */
#if (CAN_SET_BAUDRATE_API == STD_OFF)
			HW_Register((TempConfig->CanController_ptr[Controller].CanControllerBaseAddress)+CTRL1) |= ((TempConfig->CanController_ptr[Controller].CanControllerDefaultBaudrate->CanControllerPropSeg)<<PROPSEG) | ((TempConfig->CanController_ptr[Controller].CanControllerDefaultBaudrate->CanControllerSeg1)<<PSEG1) | ((TempConfig->CanController_ptr[Controller].CanControllerDefaultBaudrate->CanControllerSeg2)<<PSEG2) | ((TempConfig->CanController_ptr[Controller].CanControllerDefaultBaudrate->CanControllerSyncJumpWidth)<<RJW) | (1 << ERRMSK) | (1 << BOFFREC) ;
#endif
			/* Enabling Controller Interrupts */
			Can_EnableControllerInterrupts(Controller);

			/* re-initialization of the message buffers */
			for (RAMCounter = 0; RAMCounter < MAXMB[Controller]; ++RAMCounter)  /* FlexCAN0 32 MB, FlexCAN1,2 = 16 MB */
			{
				*(RAMn++) = 0;    /* Clearing all message buffers */
			}
			RAMn = (uint32*)(TempConfig -> CanController_ptr[Controller].CanControllerBaseAddress + FIRSTOFFSET);       /* First element in the array is the first message buffer */

			/* Setting a counter for accessing the configuration array correctly */
			if (0 == Controller)
			{
				BufferCounter = 0;
			}
			else if (1 == Controller)
			{
				BufferCounter = TotalNumOfBuffers[0];
			}
			else
			{
				BufferCounter = TotalNumOfBuffers[0] + TotalNumOfBuffers[1];
			}

			for (BufferConfigCounter = 0 ; BufferConfigCounter < (TotalNumOfBuffers[Controller]) ; BufferConfigCounter++)
			{
				if (STANDARD == TempConfig->CanHardwareObject_ptr[(BufferCounter) ].CanIdType)
				{
					/* Writing to MB IDE bit (21) */
					*RAMn |= (1 << 21);

					if (TRANSMIT == TempConfig->CanHardwareObject_ptr[BufferCounter].CanObjectType)
					{
						/* Writing the MB code as TX INACTIVE */
						*RAMn |= (8 << 24);	/* Code = 0b1000 in bits (24 - 27) */
					}
					else
					{
						/* Writing the MB code as RX EMPTY */
						*RAMn |= (4 << 24);	/* Code = 0b0100 in bits (24 - 27) */

						/* Writing the corresponding MASK */
						*(RXIMRn++) = TempConfig->CanHardwareObject_ptr[BufferCounter].CanHWFilterRef->CanHwFilterMask;
						HW_Register ( (uint32*) (TempConfig->CanHardwareObject_ptr[BufferCounter].CanControllerRef->CanControllerBaseAddress + FIRSTOFFSET + (TempConfig->CanHardwareObject_ptr[BufferCounter].CanObjectId) * 16 ) + 1) |= TempConfig->CanHardwareObject_ptr[BufferCounter].CanHWFilterRef->CanHwFilterCode << 18;
						/* Writing the HWFilterCode to the ID of Rx Buffer */


					}
				}

				else /* The ID is extended */
				{
					/* Writing to MB IDE bit (21) */
					*RAMn &= ~(1 << 21);

					if (TRANSMIT == TempConfig->CanHardwareObject_ptr[BufferCounter].CanObjectType)
					{
						/* Writing the MB code as TX INACTIVE */
						*RAMn |= (8 << 24);	/* Code = 0b1000 in bits (24 - 27) */
					}
					else
					{
						/* Writing the MB code as RX EMPTY */
						*RAMn |= (4 << 24);	/* Code = 0b0100 in bits (24 - 27) */

						/* Writing the corresponding MASK */
						*(RXIMRn++) = TempConfig->CanHardwareObject_ptr[BufferCounter].CanHWFilterRef->CanHwFilterMask;

						/* Writing the HWFilterCode to the ID of Rx Buffer */
						HW_Register ( (uint32*) (TempConfig->CanHardwareObject_ptr[BufferCounter].CanControllerRef->CanControllerBaseAddress + FIRSTOFFSET + (TempConfig->CanHardwareObject_ptr[BufferCounter].CanObjectId * 4) ) + 1) |= TempConfig->CanHardwareObject_ptr[BufferCounter].CanHWFilterRef->CanHwFilterCode ;

					}
				}
				BufferCounter++;
				RAMn += 4;
			}
		}
		/*else
			{
				 //Disable the Controller
				HW_Register( (TempConfig ->CanController_ptr[Controller].CanControllerBaseAddress) + MCR) |= (1 << MDIS);
			}*/


		/* Negate MCR(HALT) To Exit freeze mode */
		HW_Register( (TempConfig -> CanController_ptr[Controller].CanControllerBaseAddress) + MCR) &= ~( (1 << HALT) | (1 << FRZ) );


		/* wait for module to exit freeze mode */
		while( (HW_Register( (TempConfig->CanController_ptr[Controller].CanControllerBaseAddress) + MCR )) & (1 << FRZACK) );

		/* wait for module to be ready */
		while( (HW_Register( (TempConfig->CanController_ptr[Controller].CanControllerBaseAddress) + MCR)) & (1 << NOTRDY) );

		CAN_CONTROLLERS_STATES[Controller] = CAN_CS_STARTED;
		break;

	case CAN_CS_STOPPED:      /* Freeze mode */
		HW_Register((CAN_BASE_ADDRESSES[Controller] + MCR)) |= ( (1 << FRZ));
		HW_Register((CAN_BASE_ADDRESSES[Controller] + MCR)) |= ( (1 << HALT));
		while(! ( (HW_Register((CAN_BASE_ADDRESSES[Controller] + MCR) ) & (1 << FRZACK) )));

		/* Disabling Controller interrupts */
		Can_DisableControllerInterrupts(Controller);

		CAN_CONTROLLERS_STATES[Controller] = CAN_CS_STOPPED;
		break;

	case CAN_CS_SLEEP:     /* Freeze mode */
		HW_Register((CAN_BASE_ADDRESSES[Controller] + MCR)) |= ( (1 << FRZ));
		HW_Register((CAN_BASE_ADDRESSES[Controller] + MCR)) |= ( (1 << HALT));
		while(! ( (HW_Register((CAN_BASE_ADDRESSES[Controller] + MCR) ) & (1 << FRZACK) )));

		/* Disabling Controller interrupts */
		Can_DisableControllerInterrupts(Controller);

		CAN_CONTROLLERS_STATES[Controller] = CAN_CS_SLEEP;

		break;
	}

	ENABLE_INTERRUPTS()
	return E_OK;
}



/* To get error state for each controller we must read the fault confinement bits in the ESR register */

Std_ReturnType Can_GetControllerErrorState( uint8 ControllerId, Can_ErrorStateType* ErrorStatePtr )
{
#if (CAN_DEV_ERROR_DETECT==STD_ON)
	if (CAN_READY != CAN_MODULE_STATE)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x11U, CAN_E_UNINIT );
		return E_NOT_OK;
	}
	else if (ControllerId > NUM_OF_CONTROLLERS)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x11U, CAN_E_PARAM_CONTROLLER );
		return E_NOT_OK;
	}
	else if (NULL_PTR == ErrorStatePtr)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x11U, CAN_E_PARAM_POINTER );
		return E_NOT_OK;
	}
	else
	{
		/* MISRA */
	}
#endif    /* CAN_DEV_ERROR_DETECT */
	if ( !(HW_Register((CAN_BASE_ADDRESSES[ControllerId]) + ESR1) & (48)) )    /* (4-5) bits in ESR1 */
	{
		*ErrorStatePtr = CAN_ERRORSTATE_ACTIVE;
	}
	else if ( 1 == (HW_Register((CAN_BASE_ADDRESSES[ControllerId]) + ESR1) & (48)) )
	{
		*ErrorStatePtr = CAN_ERRORSTATE_PASSIVE;
	}
	else 
	{
		*ErrorStatePtr = CAN_ERRORSTATE_BUSOFF;
	}	
	return E_OK;
}

Std_ReturnType Can_GetControllerMode( uint8 Controller, Can_ControllerStateType* ControllerModePtr )
{
#if (CAN_DEV_ERROR_DETECT==STD_ON)
	if (CAN_READY != CAN_MODULE_STATE)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x12U, CAN_E_UNINIT );
		return E_NOT_OK;
	}
	else if (Controller > NUM_OF_CONTROLLERS)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x12U, CAN_E_PARAM_CONTROLLER );
		return E_NOT_OK;
	}
	else if (NULL_PTR == ControllerModePtr)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x12U, CAN_E_PARAM_POINTER );
		return E_NOT_OK;
	}
	else
	{
		/* MISRA */
	}
#endif    /* CAN_DEV_ERROR_DETECT */

	*ControllerModePtr = CAN_CONTROLLERS_STATES[Controller];
	return E_OK;
}

/* We are gonna check the availability of the message buffer by checking the MB code */
/* If the buffer code is DATA, that means the buffer is BUSY */
/* This function will access the Can_HTH_Array according to the argument Hth */ 
/* We will know the address of the message buffer based on its position in Can_HTH_Array and the fact that they are 
   sorted as : Can0 MBs, Can1 MBs, Can2 MBs */
/* The design of this function is based on the previous comment, so the user configurations must be consistent with 
   this design before attempting to use this function */

/* [SWS_Can_00212]: The function Can_Write shall perform following actions if the hardware transmit object is free:
1) The mutex for that HTH is set to ‘signaled’
2) The ID, Data Length and SDU are put in a format appropriate for the hardware (if necessary) and copied in the appropriate hardware registers/buffers.
3) All necessary control operations to initiate the transmit are done
4) The mutex for that HTH is released
5) The function returns with E_OK (SRS_Can_01049)
 */
Std_ReturnType Can_Write( Can_HwHandleType Hth, const Can_PduType* PduInfo )
{
#if (CAN_DEV_ERROR_DETECT==STD_ON)
	if (CAN_READY != CAN_MODULE_STATE)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x06U, CAN_E_UNINIT );
		return E_NOT_OK;
	}
	else if (Hth < 0 || Hth > (NUM_OF_TX_BUFFERS_0 + NUM_OF_TX_BUFFERS_1 + NUM_OF_TX_BUFFERS_2 - 1) ) /* Hth is out of range */
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x06U, CAN_E_PARAM_HANDLE );
		return E_NOT_OK;
	}
	else if (PduInfo->length > 8)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x06U, CAN_E_PARAM_DATA_LENGTH );
		return E_NOT_OK;
	}
	else if (NULL_PTR == PduInfo)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INDEX, 0x06U, CAN_E_PARAM_POINTER );
		return E_NOT_OK;
	}
	/* This function must return an error if the requested buffer is inside a CanController has not been started yet */
	else if (CAN_CS_STARTED != CAN_CONTROLLERS_STATES[Can_HTH_Array[Hth].CanControllerRef->CanControllerId])
	{
		return E_NOT_OK;
	}
	else
	{
		/* MISRA */
	}
#endif    /* CAN_DEV_ERROR_DETECT */

	//IFLAG1_Reg = HW_Register(Can_HTH_Array[Hth].CanControllerRef->CanControllerBaseAddress + IFLAGOFFSET);
	/* Calculating the address of the requested message buffer */
	uint32 BufferAddress = 0;
	uint8* TempDataPtr = NULL_PTR;
	uint8* DataPtr = PduInfo->sdu ;
	uint8 length = PduInfo->length;

	BufferAddress = (Can_HTH_Array[Hth].CanControllerRef->CanControllerBaseAddress) + (FIRSTOFFSET) + (Can_HTH_Array[Hth].CanObjectId * 16);
	/* Checking if the message buffer is free (The code of the message buffer is INACTIVE)*/
	if (MB_CS_INACTIVE == ( HW_Register( BufferAddress ) & (0x0f000000) ) >> 24 )
	{
		TempDataPtr = (uint32*)BufferAddress + 2;         /* Pointing to the first byte of the Data */
		/* Proceed in the transmission process */

		/* Clear the corresponding IFLAG bit */ 
		HW_Register(Can_HTH_Array[Hth].CanControllerRef->CanControllerBaseAddress + IFLAGOFFSET) |= (1 << (Can_HTH_Array[Hth].CanObjectId) );
		/* Write the payload data */
		while (length--)
		{
			*(TempDataPtr++) = *( DataPtr++ );
		}

		/* Write the ID */
		/* The Can_IdType is 32 bit which the two most significant bits discriminate between StdCan and Canfd */
		/* Since we are not using CanFD we will ignore the two most significant bits */
		HW_Register ( (uint32*)(BufferAddress) + 1 ) |= (uint32)(PduInfo->id) << 18 ;

		/* Activate MB for transmitting and writing the DLC */
		/* SRR = 1 (Tx frame) */
		/* EDL,BRS,ESI=0: CANFD not used */
		/* RTR = 0: data, not remote tx request frame */
		HW_Register(BufferAddress) |= ( ( (PduInfo->length) << 16 ) | (MB_CS_DATA << 24) | (1 << 22));
		HW_Register(BufferAddress) &= ~( ( 7 << 29 ) | (1 << 20) );
	}
	else if ( MB_CS_DATA == ( HW_Register( BufferAddress ) & (0x0f000000) ) )
	{
		/* [SWS_Can_00213]: The function Can_Write shall perform no actions if the hardware transmit object is busy with another transmit request for an L-PDU:
		1. The transmission of the other L-PDU shall not be cancelled and the function Can_Write is left without any actions.
		2. The function Can_Write shall return CAN_BUSY */
		return CAN_BUSY;
	}
	else 
	{
		/* MISRA */
	}
	return E_OK;
}


/* The ISR is for both (Transmitting and receiving) */
void CAN0_ORed_0_15_MB_IRQHandler()
{

	/* Looping on Receiving Hardware Objects */ 
	for (HOCounter = 0 ; HOCounter < NUM_OF_RX_BUFFERS_0 ; HOCounter++)
	{
		/* Reception is successful */
		if ( ( (HW_Register (CAN_BASE_ADDRESSES[0] + IFLAGOFFSET)) >> (Can_HRH_Array[HOCounter].CanObjectId) ) & 1 )
		{
			rx_count++;
			if (HW_Register(0x400FF090) & (1<<17))
			{
				HW_Register(0x400FF0C4) |= 1<<15;
				LPUART1_transmit_char(0);
			}
			else
			{							 /* -If BTN0 was not pushed*/
				HW_Register(0x400FF0C8) |= 1<<15;       /*		Set Output on port D0 (LED off) */
				LPUART1_transmit_char(1);
			}
			for (i = 1; i <= 10; i++)
				for (j = 1; j <= 32767; j++)	//32767
				{}
			//HW_Register(0x400FF0C4) |= (1 << 16);
			/*
			Received_Mailbox[0] = HW_Register(CAN_BASE_ADDRESSES[0] + FIRSTOFFSET + (Can_HRH_Array[HOCounter].CanObjectId) * 0x16);
			Received_Mailbox[1] = HW_Register(CAN_BASE_ADDRESSES[0] + FIRSTOFFSET + (Can_HRH_Array[HOCounter].CanObjectId) * 0x16 + 1);
			Received_Mailbox[2] = HW_Register(CAN_BASE_ADDRESSES[0] + FIRSTOFFSET + (Can_HRH_Array[HOCounter].CanObjectId) * 0x16 + 2);
			Received_Mailbox[3] = HW_Register(CAN_BASE_ADDRESSES[0] + FIRSTOFFSET + (Can_HRH_Array[HOCounter].CanObjectId) * 0x16 + 3);
			 */
			HW_Register (CAN_BASE_ADDRESSES[0] + IFLAGOFFSET) |= (1 << Can_HRH_Array[HOCounter].CanObjectId);




			/*
			if(Received_Mailbox[2] >= 250 && Received_Mailbox[2] <= 1023)
				LPUART1_transmit_char('0');
			if(Received_Mailbox[2] >= 0 && Received_Mailbox[2] <= 10)
				LPUART1_transmit_char('1');
			*/



			/*
			UART_Ptr = &Received_Mailbox[2];
			for(i = 0; i < 4; i++)
			{
				UART_Data[i] = *(UART_Ptr++);
				LPUART1_transmit_char(UART_Data[i]);
			}

			for (i = 1; i <= 200; i++)
				for (j = 1; j <= 32767; j++)
				{}
			 */

			/*
			if (Received_Mailbox[2] < 0x100)
			{
				HW_Register(0x400FF0C4) |= (1 << 15);
			}
			 */
			/*
			 *  The Following reception steps to be followed:
			 *  1. Read the Control and Status word of that mailbox.
			 *	2. Check if the BUSY bit is deasserted, indicating that the mailbox is locked. Repeat
			 *	step 1) while it is asserted. See Mailbox lock mechanism.
			 *	3. Read the contents of the mailbox. After the mailbox is locked, its contents won't be
			 *	modified by FlexCAN move-in processes.
			 *	4. Acknowledge the proper flag at IFLAG registers. (Clear Flag)
			 *	5. Read the free running timer. It is optional but recommended to unlock the mailbox as
s			 *	oon as possible and make it available for reception.
			 */


		}
		else 
		{
			/* Do Nothing */
		}			
	}


	/* Looping on Transmitting Hardware Objects */ 
	/*
	for (HOCounter = 0 ; HOCounter < NUM_OF_TX_BUFFERS_0 ; HOCounter++)
	{
		if ( ( (HW_Register (CAN_BASE_ADDRESSES[0] + IFLAGOFFSET)) >> (Can_HTH_Array[HOCounter].CanObjectId) ) & 1 )
		{


		}
		else 
		{
		}			
	}
	 */
}

void FlexCan1_ISR()
{
	/* Looping on Receiving Hardware Objects */ 
	for (HOCounter = NUM_OF_RX_BUFFERS_0 ; HOCounter < (NUM_OF_RX_BUFFERS_0 + NUM_OF_RX_BUFFERS_1) ; HOCounter++)
	{
		/* Reception is successful */
		if ( ( (HW_Register (CAN_BASE_ADDRESSES[0] + IFLAGOFFSET)) >> (Can_HRH_Array[HOCounter].CanObjectId) ) & 1 )
		{



		}
		else 
		{
			/* Do Nothing */
		}			
	}

	/* Looping on Transmitting Hardware Objects */ 
	for (HOCounter = NUM_OF_TX_BUFFERS_0 ; HOCounter < (NUM_OF_TX_BUFFERS_0 + NUM_OF_TX_BUFFERS_1) ; HOCounter++)
	{
		/* Transmission is successful */
		if ( ( (HW_Register (CAN_BASE_ADDRESSES[0] + IFLAGOFFSET)) >> (Can_HTH_Array[HOCounter].CanObjectId) ) & 1 )
		{



		}
		else 
		{
			/* Do Nothing */
		}			
	}

}

void FlexCan2_ISR()
{
	/* Looping on Receiving Hardware Objects */ 
	for (HOCounter = (NUM_OF_RX_BUFFERS_0 + NUM_OF_RX_BUFFERS_1) ; HOCounter < (NUM_OF_RX_BUFFERS_0 + NUM_OF_RX_BUFFERS_1 + NUM_OF_RX_BUFFERS_2) ; HOCounter++)
	{
		/* Reception is successful */
		if ( ( (HW_Register (CAN_BASE_ADDRESSES[0] + IFLAGOFFSET)) >> (Can_HRH_Array[HOCounter].CanObjectId) ) & 1 )
		{



		}
		/* No message has been received on the MB */
		else 
		{
			/* Do Nothing */
		}			
	}

	/* Looping on Transmitting Hardware Objects */ 
	for (HOCounter = (NUM_OF_TX_BUFFERS_0 + NUM_OF_TX_BUFFERS_1) ; HOCounter < (NUM_OF_TX_BUFFERS_0 + NUM_OF_TX_BUFFERS_1 + NUM_OF_TX_BUFFERS_2) ; HOCounter++)
	{
		/* Transmission is successful */
		if ( ( (HW_Register (CAN_BASE_ADDRESSES[0] + IFLAGOFFSET)) >> (Can_HTH_Array[HOCounter].CanObjectId) ) & 1 )
		{



		}
		else 
		{
			/* Do Nothing */
		}			
	}
}
