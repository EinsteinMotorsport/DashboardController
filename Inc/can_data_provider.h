#ifndef CAN_DATA_PROVIDER_H
#define CAN_DATA_PROVIDER_H
#include "main.h"


#define NUMBER_CAN_VALUES (48)

typedef enum {
	TMOT            = 0x00,
	TMOT2           = 0x01,
	TFUEL           = 0x02,
	TOIL            = 0x03,
	TECU_SYS        = 0x04,
	UB              = 0x05,
	B_ENGON         = 0x06,
	
	PBRAKE_F        = 0x07,
	PBRAKE_R        = 0x08,
	PCLUTCH         = 0x09,
	PFUEL           = 0x0A,
	POIL            = 0x0B,
	
	ATH             = 0x0C,
	APS             = 0x0D,
	CUTOFF_GC_EMS   = 0x0E,
	GEAR            = 0x0F,
	FAN_PWM_EMS     = 0x10,
	
	FUELCONS        = 0x11,
	DISTTRIP        = 0x12,
	
	DAM_FL          = 0x13,
	DAM_FR          = 0x14,
	DAM_RR          = 0x15,
	DAM_RL          = 0x16,
	
	ACCY            = 0x17,
	STEER           = 0x18,
	SPEED           = 0x19,
	ACCX            = 0x1A,
	
	NMOT            = 0x1B,
	LAMBDA          = 0x1C,
	FLC             = 0x1D,
	B_LSUOP         = 0x1E,
	//GEAR = 0x1F, //has id 0x0F
	//TMOT = 0x1F, //has id 0x00
	
	//NMOT = 0x1F, //has id 0x1B
	B_LAUNCHSW      = 0x1F,
	B_AUTOSHIFTSW   = 0x20,
	B_CLUTCH_OPEN   = 0x21,
	B_UPSHEVENT_EMS = 0x22,
	MI_LAUNCH       = 0x23,
	//GEAR = 0x24, //has id 0x0F
	
	VWHEEL_FL       = 0x24,
	VWHEEL_FR       = 0x25,
	VWHEEL_RL       = 0x26,
	VWHEEL_RR       = 0x27,
	
	//SPEED = 0x28, //has id 0x19
	SLIP_ACT        = 0x28,
	GC_STATE_EMS    = 0x29,
	//MI_LAUNCH = 0x2A, //has id 0x23
	XXXXX           = 0x2A,
	
	UPSHIFTERRCNT   = 0x2B,
	DNSHIFTERRCNT   = 0x2C,
	SHIFTUP_PWM_EMS = 0x2D,
	SHIFTDN_PWM_EMS = 0x2E,
	UGEARP          = 0x2F,
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



