/*========================================== [EASS solutions] Smart Switch Board ==========================================*\
   state_table.h

 * Summery:- switch table breifs and APIs for switch state table handling
\*=========================================================================================================================*/

#ifndef _SWITCH_TABLE_H_
#define _SWITCH_TABLE_H_

#include <stdint.h>

/* MACRO definitions */
#define STATE_ON     ((uint8_t)1u)
#define STATE_OFF    ((uint8_t)0u)

/* Device State table type definition */
typedef struct DeiceTable_Tag{
   uint8_t dev_1:1;
   uint8_t dev_2:1;
   uint8_t dev_3:1;
   uint8_t dev_reg1:4;
#if ( 1 == BOARD_TYPE )
   uint8_t dev_5:1;
   uint8_t dev_6:1;
   uint8_t dev_7:1;
   uint8_t dev_reg2:4;
#endif
}device_state_table_t;

void DeviceStateTable_Load(device_state_table_t *);
void DeviceStateTable_Update(device_state_table_t);
#endif

/*================================================== Revision History =====================================================*\
   Developer       Rev Date       Comments
 * Shivam          27-11-2020     Initial Version
\*=========================================================================================================================*/