#ifndef CAN_DATA_PROVIDER_H
#define CAN_DATA_PROVIDER_H
#include "main.h"


#define NUMBER_CAN_VALUES (49)

typedef enum {
	NO_VALUE				= 0x00,
	TMOT            = 0x01,
	TMOT2           = 0x02,
	TFUEL           = 0x03,
	TOIL            = 0x04,
	TECU_SYS        = 0x05,
	UB              = 0x06,
	B_ENGON         = 0x07,
	
	PBRAKE_F        = 0x08,
	PBRAKE_R        = 0x09,
	PCLUTCH         = 0x0A,
	PFUEL           = 0x0B,
	POIL            = 0x0C,
	
	ATH             = 0x0D,
	APS             = 0x0E,
	CUTOFF_GC_EMS   = 0x0F,
	GEAR            = 0x10,
	FAN_PWM_EMS     = 0x11,
	
	FUELCONS        = 0x12,
	DISTTRIP        = 0x13,
	
	DAM_FL          = 0x14,
	DAM_FR          = 0x15,
	DAM_RR          = 0x16,
	DAM_RL          = 0x17,
	
	ACCY            = 0x18,
	STEER           = 0x19,
	SPEED           = 0x1A,
	ACCX            = 0x1B,
	
	NMOT            = 0x1C,
	LAMBDA          = 0x1D,
	FLC             = 0x1E,
	B_LSUOP         = 0x1F,
	//GEAR = 0x1F, //has id 0x0F
	//TMOT = 0x1F, //has id 0x00
	
	//NMOT = 0x1F, //has id 0x1B
	B_LAUNCHSW      = 0x20,
	B_AUTOSHIFTSW   = 0x21,
	B_CLUTCH_OPEN   = 0x22,
	B_UPSHEVENT_EMS = 0x23,
	MI_LAUNCH       = 0x24,
	//GEAR = 0x24, //has id 0x0F
	
	VWHEEL_FL       = 0x25,
	VWHEEL_FR       = 0x26,
	VWHEEL_RL       = 0x27,
	VWHEEL_RR       = 0x28,
	
	//SPEED = 0x28, //has id 0x19
	SLIP_ACT        = 0x29,
	GC_STATE_EMS    = 0x2A,
	//MI_LAUNCH = 0x2A, //has id 0x23
	XXXXX           = 0x2B,

	UPSHIFTERRCNT   = 0x2C,
	DNSHIFTERRCNT   = 0x2D,
	SHIFTUP_PWM_EMS = 0x2E,
	SHIFTDN_PWM_EMS = 0x2F,
	UGEARP          = 0x30,
	/* ... */
}CAN_VALUE_ID;

typedef struct {
	float value;
	uint8_t flags;
}can_value;


void can_data_init(CAN_HandleTypeDef* hcan);
void can_data_update(void);

can_value* can_data_get_value(CAN_VALUE_ID);


#endif



