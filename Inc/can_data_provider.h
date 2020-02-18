#ifndef CAN_DATA_PROVIDER_H
#define CAN_DATA_PROVIDER_H
#include "main.h"


#define NUMBER_CAN_VALUES (8)

typedef enum {
	TMOT     = 0x0,
	TMOT2    = 0x1,
	TFUEL    = 0x2,
	TOIL     = 0x3,
	TECU_SYS = 0x4,
	UB       = 0x5,
	B_ENGON  = 0x6,
	
	PBRAKE_F = 0x7,
	/* ... */
}CAN_VALUE_ID;

typedef struct {
	float value;
	uint8_t did_change;
}can_value;


void can_data_init(CAN_HandleTypeDef* hcan);
void can_data_update(void);

can_value* can_data_get_value(CAN_VALUE_ID);


#endif



