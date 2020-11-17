/*========================================== [EASS solutions] Smart Switch Board ==========================================*\
   main app

 * Summery:- cyclic running main state machine of smart switch board feature
\*=========================================================================================================================*/

#include "port.h"
#include "comm.h"
#include "monitor.h"
#include "control.h"
#include "switch_table.h"

typedef enum{
   IDL,
   MONITOR,
   CONTROL
}app_state_t;

static void app_task(void);

void app_main(void)
{
   while (1)
   {
      app_task();
   }
}

/**
 * app_task
   -- main cyclic task
*/
static void app_task(void)
{
   static app_state_t state = IDL;

   switch (state)
   {
      case IDL:
         {
            SwitchTable_load();
            state = MONITOR;
            break;
         }

      case MONITOR:
         {
            Get_HardSwitch_Status();

            if(Is_Any_Toggle_Detected())
            {
               SwitchTable_Update();
               SendUpdate_ToNw();
               if(Is_HardRegl_Toggle())
               {
                  SendUpdate_ToReglMicro();
               }
            }

            state = CONTROL;
            break;
         }

      case CONTROL:
         {
            if(Is_Automation_on())
            {
               Control_Switches();
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
   Developer       Rev Date       Comments
 * Shivam          08-11-2020     Initial Version
\*=========================================================================================================================*/