/*========================================== [EASS solutions] Smart Switch Board ==========================================*\
   main app

 * Summery:- cyclic running main state machine of smart switch board
\*=========================================================================================================================*/

#include <stdint.h>
#include <stdbool.h>
#include "port.h"
#include "comm.h"
#include "monitor.h"
#include "control.h"
#include "state_table.h"
#include <stdio.h>
#include "esp_wifi.h"

typedef enum AppStateTag{
   IDL,
   MONITOR,
   CONTROL
}app_state_t;

static void app_task(void);

void app_main(void)
{
   port_init();
   while (1)
   {
      app_task();
   }
}

/**
 * Main cyclic task
 * 
 * @param void
 * @return
 */
static void app_task(void)
{
   static app_state_t state = IDL;
   static device_state_table_t device_states_buff = { 0 };
   static device_state_table_t switch_states_buff = { 0 };    /* volatile storage for switch states. */

   switch (state)
   {
      case IDL:
         {
            DeviceStateTable_Load( &device_states_buff ); /* loading Device State table from Non Volatile Storage */
            SwitchStates_Read( &switch_states_buff );     /* reading initial states of switches */
            state = MONITOR;
            break;
         }

      case MONITOR:
         {

            if( Monitor_Switches( &device_states_buff, &switch_states_buff ) )
            {
               DeviceStateTable_Update(device_states_buff); /* update the device table in NVS */
               Send_DeviceTable_ToNw(device_states_buff);
            }

            state = CONTROL;
            break;
         }

      case CONTROL:
         {
            if( Is_Automation_on() )
            {
               Control_Devices(device_states_buff);
            }
            state = MONITOR;
            break;
         }

      default:
         break;
   }

return;
}

/*================================================== Revision History =====================================================*\
   Author       Rev Date       Comments
 * Shivam          08-11-2020     Initial Version
\*=========================================================================================================================*/