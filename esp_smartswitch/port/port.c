/*========================================== [EASS solutions] Smart Switch Board ==========================================*\
 * port.c

 * Summery:- this module has GPIO port pins definitions and related interfaces.
\*=========================================================================================================================*/

#include <stdio.h>
#include "port.h"

void port_init(void)
{
   gpio_set_direction(DEVICE_1, GPIO_MODE_OUTPUT);
   gpio_set_direction(DEVICE_2, GPIO_MODE_OUTPUT);
   gpio_set_direction(DEVICE_3, GPIO_MODE_OUTPUT);
#if ( 1 == BOARD_TYPE )
   gpio_set_direction(DEVICE_4, GPIO_MODE_OUTPUT);
   gpio_set_direction(DEVICE_5, GPIO_MODE_OUTPUT);
   gpio_set_direction(DEVICE_6, GPIO_MODE_OUTPUT);
#endif

   gpio_set_direction(SWITCH_1, GPIO_MODE_INPUT);
   gpio_set_direction(SWITCH_2, GPIO_MODE_INPUT);
   gpio_set_direction(SWITCH_3, GPIO_MODE_INPUT);
   gpio_set_direction(SWITCH_REGL_1, GPIO_MODE_INPUT);
#if ( 1 == BOARD_TYPE )
   gpio_set_direction(SWITCH_4, GPIO_MODE_INPUT);
   gpio_set_direction(SWITCH_5, GPIO_MODE_INPUT);
   gpio_set_direction(SWITCH_6, GPIO_MODE_INPUT);
   gpio_set_direction(SWITCH_REGL_2, GPIO_MODE_INPUT);
#endif

}


/*================================================== Revision History =====================================================*\
   Author         Rev Date       Comments
 * Shivam         12-12-2020     Initial Version
\*=========================================================================================================================*/