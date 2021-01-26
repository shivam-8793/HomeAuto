/*========================================== [EASS solutions] Smart Switch Board ==========================================*\
   state_table.c

 * Summery:- APIs for handling switch table in NVS (Non Volatile Storage).
\*=========================================================================================================================*/

#include <stdio.h>
#include "state_table.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"


/**
 * Load Device state table from NVS.
 * 
 * @param out pointer to device state table read buffer
 * @return void
 */
void DeviceStateTable_Load(device_state_table_t *state_table_read_ptr)
{
   /* Initialize NVS */
   esp_err_t err = nvs_flash_init();
   if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      /* NVS partition was truncated and needs to be erased */
      /* Retry nvs_flash_init */
      ESP_ERROR_CHECK(nvs_flash_erase());
      err = nvs_flash_init();
   }
   ESP_ERROR_CHECK( err );

   /* Open */
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

   /* Read */
   printf("Reading state table from NVS ... ");
   size_t len = sizeof(*state_table_read_ptr);
   err = nvs_get_blob(my_handle, "DeviceStates", (void *)state_table_read_ptr,&len);
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

   /* Close */
   nvs_close(my_handle);
   }

   printf("\n");
   fflush(stdout);
}

void DeviceStateTable_Update(device_state_table_t state_table_write)
{
   /* Open */
   printf("\n");
   printf("Opening Non-Volatile Storage (NVS) handle... ");
   nvs_handle_t my_handle;
   esp_err_t err = nvs_open("storage", NVS_READWRITE, &my_handle);
   if (err != ESP_OK)
   {
      printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
   } 
   else
   {
   printf("Done\n");

   /* Read */
   printf("writing state table to NVS ... ");
   err = nvs_set_blob(my_handle, "DeviceStates", (void *)&state_table_write,sizeof(state_table_write));
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

   /* Close */
   nvs_close(my_handle);
   }

   printf("\n");
   fflush(stdout);
}

/*================================================== Revision History =====================================================*\
   Developer       Rev Date       Comments
 * Shivam          27-11-2020     Initial Version, SwitchTable_load initial implementation.
\*=========================================================================================================================*/