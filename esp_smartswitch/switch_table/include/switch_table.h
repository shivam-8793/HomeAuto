/*========================================== [EASS solutions] Smart Switch Board ==========================================*\
   switch_table.h

 * Summery:- switch table breifs and APIs for switch state table handling
\*=========================================================================================================================*/
#ifndef _SWITCH_TABLE_H_
#define _SWITCH_TABLE_H_

#include <stdint.h>
/* switch table type definition */
typedef struct SwitchTable_Tag{
   uint8_t sw_1:1;
   uint8_t sw_2:1;
   uint8_t sw_3:1;
   uint8_t sw_4:1;
   uint8_t sw_reg1:4;
#if ( 1 == BOARD_TYPE )
   uint8_t sw_5:1;
   uint8_t sw_6:1;
   uint8_t sw_7:1;
   uint8_t sw_8:1;
   uint8_t sw_reg2:4;
#endif
}switchtable_t;

void SwitchTable_load(switchtable_t *);
void SwitchTable_Update(void);
#endif
/*================================================== Revision History =====================================================*\
   Developer       Rev Date       Comments
 * Shivam          27-11-2020     Initial Version
\*=========================================================================================================================*/