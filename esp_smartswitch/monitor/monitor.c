/*========================================== [EASS solutions] Smart Switch Board ==========================================*\
 * monitor.c

 * Summery:- this component is responsible for monitoring the switch status.
\*=========================================================================================================================*/

#include <stdbool.h>
#include "monitor.h"
#include "port.h"
#include "driver/timer.h"
#include "state_table.h"

/* timer configuration parameters */
#define TIMER_DIVIDER       40000uL  /* Hardware timer clock divider [ freq = 2 kHz | 1 tick = 0.5 ms ]  */
#define TIMER_SCALE         2uL      /* convert counter value to milliseconds */
#define TIMER_INTERVAL_MS   15uL     /* timer interval */

/* internal objects definitions */

/* switch type definition */
typedef enum SwitchTypeTag{
   SWTICH_TYPE_NORMAL, /* normal type switch */
   SWITCH_TYPE_REGL    /* regulator type switch */
}switch_type_t;

static bool timeout = false;
static bool timer_init_done = false;

int zero_cross = 0;  /* @TODO : zero crossing component to be implemented */

/* internal function definitions */

/**
 * @brief Timer interrupt callback handler impl
 * 
 * @param void
 * @return
 *     - interrupt to be YIELD or not
 */
bool IRAM_ATTR timer0_group0_isr_handler(void *arg)
{
   timeout = true;
   return true;
}

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
   if(!timer_init_done) /* timer must be initialized */
   { /* @TODO : create separate API for timer initialization */

      /* initialize basic parameters of the timer */
      timer_config_t config = { 
         .divider = TIMER_DIVIDER,
         .counter_dir = TIMER_COUNT_UP,
         .counter_en = TIMER_PAUSE,
         .alarm_en = TIMER_ALARM_DIS,
         .auto_reload = TIMER_AUTORELOAD_EN,
      }; /* timer is configured to tick at 2kz freq */

      timer_init(TIMER_GROUP_0, TIMER_0, &config); /* initialize the group0 timer0 hw */

      timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0uL); /* reset counter */

      /* Configure the alarm for timeout value TIMER_INTERVAL_MS  */
      timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, TIMER_INTERVAL_MS * TIMER_SCALE);
      timer_enable_intr(TIMER_GROUP_0, TIMER_0);

      /* register isr callback for group0 timer0 */
      timer_isr_callback_add(TIMER_GROUP_0, TIMER_0, timer0_group0_isr_handler,NULL, ESP_INTR_FLAG_IRAM); 
   }

   uint8_t ret_value = STATE_OFF;

   timer_set_alarm(TIMER_GROUP_0,TIMER_0,TIMER_ALARM_EN); /* enable alarm */

   if( SWITCH_TYPE_REGL == switch_type )
   {
      while(zero_cross); /* wait for zero cross before timer starts so that pulse can be read accurately */
      timer_start(TIMER_GROUP_0, TIMER_0);
   }
   else
   {
      timer_start(TIMER_GROUP_0, TIMER_0);
   }

   while(timeout)
   {
      if(gpio_get_level(switch_pin)) /* pulse change before timeout */
      {
         if( SWITCH_TYPE_REGL == switch_type )
         {
            timer_pause(TIMER_GROUP_0, TIMER_0);
            timer_get_counter_value(TIMER_GROUP_0, TIMER_0, (uint64_t *)&ret_value);
            ret_value = 10 - (ret_value/TIMER_SCALE); /* calculate speed of regulator switch */
         }
         else
         {
            ret_value = STATE_ON;
         }

         break;
      }
   }

   /* if no pulse change within timeout value, switch is off */

   /* disable and reset alarm */
   timer_set_alarm(TIMER_GROUP_0,TIMER_0,TIMER_ALARM_DIS);
   timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0uL);

   return ret_value;
}

bool Is_Any_Switch_Toggle( device_state_table_t *device_states_buff_ptr, device_state_table_t *switch_states_buff_ptr )
{
   return false;
}


bool Is_ReglSwitch_Toggle(void)
{
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
\*=========================================================================================================================*/