#include "Can_PBcfg.h"
/* Contains Initial values for the containers */

/* All the Nodes participating in the network will have the same baud rate configuration */

CanControllerBaudrateConfig CanControllerBaudrateConfig_arr[] =
{
	/* Fill the configurations with time quantas */
	{
		500,
		0,
		7,
		4,
		4,
		1
		/* Baud rate configuration */
		/* ConfigID = 0 (Default of initialization if SetBaudrate is disabled) */
	},
	{



	},
	{




	}
};


CanController CanController_arr[] =
{
    {
		TRUE,
		CAN_0_BASE_ADDRESS,
		CAN_0_ID,
		&CanControllerBaudrateConfig_arr[0]
		/* Reference to system clock */
    },
	{
		FALSE,
		CAN_1_BASE_ADDRESS,
		CAN_1_ID,
		&CanControllerBaudrateConfig_arr[1]
		/* Reference to system clock */
	},
	{
		FALSE,
		CAN_2_BASE_ADDRESS,
		CAN_2_ID,
		&CanControllerBaudrateConfig_arr[2]
        /* Reference to system clock */
	}
};



CanHwFilter CanHwFilterHTH[] = {

    {
		/* There is no hardware filter for transmission, It needed to be exist for standard purposes */

    }
};

CanHwFilter CanHwFilterHRH[] = {
	{
		/* ID */
		0x111,
		/* Mask for Buffer 1 */
		0xFFFFFFFF
	},
	{
		/* ID */
		0x222,
		/* Mask for Buffer 2 */
		0xFFFFFFFF
	}
};


CanHardwareObject CanHardwareObject_arr[] =
{
  /* Receiving and transmitting buffers for Controller 0 */
  {
	  FULL,
	  FALSE,
	  1,
	  STANDARD,
	  0,
	  TRANSMIT,
	  //TRANSMIT,
	  FALSE,
	  &CanController_arr[0],
	  &CanHwFilterHTH[0]
  },
  /*{
	  FULL,
	  FALSE,
	  1,
	  STANDARD,
	  1,
	  TRANSMIT,
	  FALSE,
	  &CanController_arr[0],
	  &CanHwFilterHTH[0]
  },*/
  {
	  FULL,
	  FALSE,
	  1,
	  STANDARD,
	  1,
	  RECEIVE,
	  FALSE,
	  &CanController_arr[0],
	  &CanHwFilterHRH[0]
  }
  /*{
	  FULL,
	  FALSE,
	  1,
	  STANDARD,
	  3,
	  RECEIVE,
	  FALSE,
	  &CanController_arr[0],
	  &CanHwFilterHRH[1]

  }*/


  /* Configurations for Controller1 Message Buffers */












  /* Configurations for Controller2 Messgae Buffers */








};



Can_ConfigType Can_ConfigType_Handle =
{
	CanController_arr,
	CanHardwareObject_arr,
	CanControllerBaudrateConfig_arr
};
