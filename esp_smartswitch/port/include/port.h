/*========================================== [EASS solutions] Smart Switch Board ==========================================*\
 * port.h

 * Summery:- this module has GPIO port pins definitions and related interfaces.
\*=========================================================================================================================*/

#ifndef _PORT_H_
#define _PORT_H_
#include <stdint.h>
#include "driver/gpio.h"

/* device pins definitions (these pins are used to control the devices ) */
#define DEVICE_1   GPIO_NUM_12
#define DEVICE_2   GPIO_NUM_14
#define DEVICE_3   GPIO_NUM_16
#if ( 1 == BOARD_TYPE )
#define DEVICE_4_OUT_PIN   GPIO_NUM_18
#define DEVICE_5_OUT_PIN   GPIO_NUM_20
#define DEVICE_6_OUT_PIN   GPIO_NUM_22
#endif

/* switches pins definitions (these pins are used to read the switch status ) */
#define SWITCH_1          GPIO_NUM_13
#define SWITCH_2          GPIO_NUM_15
#define SWITCH_3          GPIO_NUM_17
#define SWITCH_REGL_1     GPIO_NUM_19
#if ( 1 == BOARD_TYPE )
#define SWITCH_4          GPIO_NUM_21
#define SWITCH_5          GPIO_NUM_23
#define SWITCH_6          GPIO_NUM_25
#define SWITCH_REGL_2     GPIO_NUM_27
#endif

void port_init(void);
#endif

/*================================================== Revision History =====================================================*\
   Author         Rev Date       Comments
 * Shivam         12-12-2020     Initial Version
\*=========================================================================================================================*/
