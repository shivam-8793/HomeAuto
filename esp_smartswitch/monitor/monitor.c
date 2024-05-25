/*========================================== [EASS solutions] Smart Switch Board ==========================================*\
 * monitor.c

 * Summery:- this component is responsible for monitoring the switch status.
\*=========================================================================================================================*/

#include <stdbool.h>
#include "monitor.h"
#include "port.h"
#include "state_table.h"
#include "control.h"


/* =================== Local objects definitions ====================== */

/* switch type definition */
typedef enum SwitchTypeTag{
   SWTICH_TYPE_NORMAL, /* normal type switch */
   SWITCH_TYPE_REGL    /* regulator type switch */
}switch_type_t;



/* ================= Local function definitions ======================== */

/**
 * @brief Reads switch status as per switch type
 * 
 * @param switch_pin pin no of the switch to be read.
 * @param switch_type type of the switch (NORMAL/REGULATOR)
 * @return
 *     - STATUS_ON/STATUS_OFF in case of NORMAL switch
 *     - speed value [0-5] in case of REGULATOR switch
 */
static uint8_t read_switch_status(gpio_num_t switch_pin, switch_type_t switch_type)
{
   uint8_t ret_value = STATE_OFF;

   if( SWITCH_TYPE_REGL == switch_type )
   {
      /* read pot value/ read from regl unit */
   }
   else
   {
      ret_value = gpio_get_level(switch_pin);
   }

return ret_value;
}


bool Monitor_Switches( device_state_table_t *device_states_buff_ptr, device_state_table_t *switch_states_buff_ptr )
{  /* test code to read switch_1 pulse continuously */
   //printf("%d\n",gpio_get_level(SWITCH_1));
   /*end of test code */
   
   device_state_table_t current_switch_states; /* temporary buffer to read current switch statuses */
   SwitchStates_Read(&current_switch_states);

   if( Is_Automation_on() )
   {
      if( current_switch_states.dev_1 != switch_states_buff_ptr->dev_1 )
      {
         device_states_buff_ptr->dev_1 = ~(device_states_buff_ptr->dev_1);
      }

      if( current_switch_states.dev_2 != switch_states_buff_ptr->dev_2 )
      {
         device_states_buff_ptr->dev_2 = ~(device_states_buff_ptr->dev_2);
      }

      if( current_switch_states.dev_3 != switch_states_buff_ptr->dev_3 )
      {
         device_states_buff_ptr->dev_3 = ~(device_states_buff_ptr->dev_3);
      }

      if( current_switch_states.dev_reg1 != switch_states_buff_ptr->dev_reg1 )
      {
      }

   }
   else
   {
      *device_states_buff_ptr = current_switch_states;
   }

   *switch_states_buff_ptr = current_switch_states;

   return false;
}



/**
 * @brief Reads status of all switches
 *
 * @param switch_states_buff_ptr pointer to the switch state table read buffer.
 * @return void
 */
void SwitchStates_Read( device_state_table_t *switch_states_buff_ptr )
{
   /* read switches status */
   switch_states_buff_ptr -> dev_1 = read_switch_status(SWITCH_1, SWTICH_TYPE_NORMAL);
   switch_states_buff_ptr -> dev_2 = read_switch_status(SWITCH_2, SWTICH_TYPE_NORMAL);
   switch_states_buff_ptr -> dev_3 = read_switch_status(SWITCH_3, SWTICH_TYPE_NORMAL);
   switch_states_buff_ptr -> dev_reg1 = read_switch_status(SWITCH_REGL_1, SWITCH_TYPE_REGL);
#if ( 1 == BOARD_TYPE )
   switch_states_buff_ptr -> dev_4 = read_switch_status(SWITCH_4, SWTICH_TYPE_NORMAL);
   switch_states_buff_ptr -> dev_5 = read_switch_status(SWITCH_5, SWTICH_TYPE_NORMAL);
   switch_states_buff_ptr -> dev_6 = read_switch_status(SWITCH_6, SWTICH_TYPE_NORMAL);
   switch_states_buff_ptr -> dev_reg2 = read_switch_status(SWITCH_REGL_2, SWITCH_TYPE_REGL);
#endif

}

/*================================================== Revision History =====================================================*\
   Author         Rev Date       Comments
 * Shivam         12-12-2020     Initial Version. switch state read implementation.
 * Shivam         02-01-2021      Changes as per new design (DC switch Design).
\*=========================================================================================================================*/