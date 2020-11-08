#include <stdio.h>
#include "port.h"
#include "comm.h"
#include "app_types.h"
#include "monitor.h"
#include "control.h"
#include "switch_table.h"

void app_main(void)
{
   while (1)
   {
      app_task();
   }
}

void app_task(void)
{
   static APP_STATE_T state = IDL;

   switch (state)
   {
      case IDL:
         SwitchTable_load();
         state = MONITOR;
         break;

      case MONITOR:
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
      
      case CONTROL:
         if(Is_Automation_on())
         {
            Control_Switches();
         }
         state = MONITOR;
         break;

      default:
         break;
   }

return;
}