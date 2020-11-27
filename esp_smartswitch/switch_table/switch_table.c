/*========================================== [EASS solutions] Smart Switch Board ==========================================*\
   switch_table.c

 * Summery:- APIs for switch state table handling.
\*=========================================================================================================================*/

#include <stdio.h>
#include "switch_table.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

void SwitchTable_load(switchtable_t *switch_table_volatile_ptr)
{
   // Initialize NVS
   esp_err_t err = nvs_flash_init();
   if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      // NVS partition was truncated and needs to be erased
      // Retry nvs_flash_init
      ESP_ERROR_CHECK(nvs_flash_erase());
      err = nvs_flash_init();
   }
   ESP_ERROR_CHECK( err );

   // Open
   printf("\n");
   printf("Opening Non-Volatile Storage (NVS) handle... ");
   nvs_handle_t my_handle;
   err = nvs_open("storage", NVS_READONLY, &my_handle);
   if (err != ESP_OK)
   {
      printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
   } 
   else 
   {
   printf("Done\n");

   // Read
   printf("Reading restart counter from NVS ... ");
   size_t len = sizeof(*switch_table_volatile_ptr);
   err = nvs_get_blob(my_handle, "restart_counter", (void *)switch_table_volatile_ptr,&len);
   switch (err) {
      case ESP_OK:
            printf("Done\n");
            break;
      case ESP_ERR_NVS_NOT_FOUND:
            printf("The value is not initialized yet!\n");
            break;
      default :
            printf("Error (%s) reading!\n", esp_err_to_name(err));
   }

   // Close
   nvs_close(my_handle);
   }

   printf("\n");
   fflush(stdout);
}

void SwitchTable_Update(void)
{
}

/*================================================== Revision History =====================================================*\
   Developer       Rev Date       Comments
 * Shivam          27-11-2020     Initial Version, SwitchTable_load initial implementation.
\*=========================================================================================================================*/
