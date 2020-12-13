#include "state_table.h"

#define MAX_NORMAL_SWITCHES 3
bool Is_Any_Switch_Toggle( device_state_table_t *, device_state_table_t * );
bool Is_ReglSwitch_Toggle(void);
void Get_HardSwitch_Status(void);
void SwitchStates_Read( device_state_table_t * );