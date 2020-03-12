#include "can_data_provider.h"
#include <stdlib.h>
#include <math.h>

static can_value* values; 
static float* min_val;
static float* max_val;

static void can_data_handle_10(uint8_t* data);
static void can_data_handle_11(uint8_t* data);
static void can_data_handle_12(uint8_t* data);
static void can_data_handle_13(uint8_t* data);
static void can_data_handle_14(uint8_t* data);
static void can_data_handle_15(uint8_t* data);
static void can_data_handle_16(uint8_t* data);
static void can_data_handle_17(uint8_t* data);
static void can_data_handle_18(uint8_t* data);
static void can_data_handle_19(uint8_t* data);
static void can_data_handle_20(uint8_t* data);



static CAN_HandleTypeDef* hcan;

static void init_min_max_vals(){
	for(int i = 0; i< NUMBER_CAN_VALUES;i++) min_val[i] = -INFINITY, max_val[i] = INFINITY;
	min_val[TMOT]     = 70.0f; max_val[TMOT]     = 110.0f;
	min_val[TMOT2]    = 60.0f; max_val[TMOT2]    = 105.0f;
	min_val[TFUEL]    =  5.0f; max_val[TFUEL]    =  55.0f;
	min_val[TOIL]     = 60.0f; max_val[TOIL]     = 130.0f;
	min_val[PFUEL]    =  4.0f; max_val[PFUEL]    =   5.5f;
	min_val[POIL]     =  0.4f; max_val[POIL]     =   2.0f;
	min_val[UB]       =  9.0f; max_val[UB]       =  14.4f;
	min_val[LAMBDA]   =  0.8f; max_val[LAMBDA]   =   1.3f;
	min_val[TECU_SYS] =  0.0f; max_val[TECU_SYS] =  55.0f;
}

void can_data_init(CAN_HandleTypeDef* _hcan){
	hcan = _hcan;
	values = malloc(sizeof(can_value) * NUMBER_CAN_VALUES);
	min_val = malloc(sizeof(float) * NUMBER_CAN_VALUES);
	max_val = malloc(sizeof(float) * NUMBER_CAN_VALUES);
	init_min_max_vals();
}

static inline uint8_t check_range(int id, float val){
	return (val > max_val[id] ? 0x2 : 0) | (val < min_val[id] ? 0x4 : 0); 
}

static inline void update(int id, float val){
	if (values[id].value != val) values[id].value = val, values[id].flags = 1 | check_range(id,val);
}


void can_data_update(){
	/*
	values[TMOT].value++;
	values[TMOT].did_change = 1;
	*/
	
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
	
	//HAL_CAN_GetRxFifoFillLevel liest die Anzahl an Nachrichten aus, die im CAN-Eingangspuffer CAN_RX_FIFO0 gespeichert sind und speichert sie in numberCanMessages ab
		uint32_t numberCanMessages = HAL_CAN_GetRxFifoFillLevel(hcan, CAN_RX_FIFO0);
		CAN_RxHeaderTypeDef rxHeader;
		uint8_t can_data[8];
	
		//Jenachdem, wie viele Nachrichten im CAN-Eingangspuffer gespeichdert sind, wird die Laenge der for-Schleife veraendert
		for(;numberCanMessages>0; numberCanMessages--){
			//HAL_IWDG_Refresh(&hiwdg);
			//HAL_CAN_GetRxMessage versucht, eine Nachricht aus dem CAN-Eingangspuffer CAN_RX_FIFO0 zu lesen. 
			//Schlaegt der Lesevorgang fehl, liefert die Funktion als Rueckgabewert HAL_ERROR und die if-Bedingung wird nicht ausgefuehrt
			//Gelingt der Lesevorgang, liefert die Funktion als Rueckgabewert HAL_OK. Die Statusinformationen der CAN-Nachricht werden in rxHeader gespeichert.
			//Die Nutzdaten der CAN-Nachricht werden in rxDataCan gespeichert.
			if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeader, can_data) == HAL_OK){

				switch(rxHeader.StdId){
					case 0x10:
						can_data_handle_10(can_data);
						break;
					case 0x11:
						can_data_handle_11(can_data);
						break;
					case 0x12:
						can_data_handle_12(can_data);
						break;
					case 0x13:
						can_data_handle_13(can_data);
						break;
					case 0x14:
						can_data_handle_14(can_data);
						break;
					case 0x15:
						can_data_handle_15(can_data);
						break;
					case 0x16:
						can_data_handle_16(can_data);
						break;
					case 0x17:
						can_data_handle_17(can_data);
						break;
					case 0x18:
						can_data_handle_18(can_data);
						break;
					case 0x19:
						can_data_handle_19(can_data);
						break;
					case 0x20:
						can_data_handle_20(can_data);
						break;
				}
				/*
				//Die eintreffenden CAN-Nachrichten werden nach ihrem Identifier gefiltert. Soll die ID an das Funkmodul weitergeleitet werden, liefert das if true.
				if(idsToSend[rxHeader.StdId - OFFSET_OF_LOWEST_ID] == true)
				{					
					//Die Standard-ID der CAN-Nachricht und die Nutzdaten werden an die Funktion PackData uebergeben.
					PackData(rxDataCan, rxHeader.StdId);
				}*/
			}
		}
		/*
		//Wenn eine bestimmte Anzahl an Nachrichten versendet wurde (NUMBER_OF_CAN_MESSAGES_UNTIL_PAUSE), liefert das if true.
		if(counterSendPackages > NUMBER_OF_RADIO_MODULE_MESSAGES_UNTIL_PAUSE)
		{
			osDelay(WAIT_TIME);
			counterSendPackages = 0;
		}
	*/

}


can_value* can_data_get_value(CAN_VALUE_ID id){
	return values + id;
}

static void can_data_handle_10(uint8_t* data){
	update(TMOT,((float)data[0]) - 40.0f);
	update(TMOT2,((float)data[1]) - 40.0f);
	update(TFUEL,((float)data[2]) - 40.0f);
	update(TOIL,((float)data[3]) - 40.0f);
	update(TECU_SYS,((float)data[4]) - 40.0f);
	update(UB,((float)data[5]) * 0.001f);
	update(B_ENGON,(float)data[6]);
}

static void can_data_handle_11(uint8_t* data){
	float tmp = ((float)(((uint16_t)data[1]) << 8 | data[0])) * 0.005f;
	update(PBRAKE_F,tmp);
	tmp = ((float)(((uint16_t)data[3]) << 8 | data[2])) * 0.005f;
	update(PBRAKE_R,tmp);
  tmp = ((float)(((uint16_t)data[5]) << 8 | data[4])) * 0.005f;
	update(PCLUTCH,tmp);
	update(PFUEL,((float)data[6])*0.05f);
	update(POIL,((float)data[7])*0.05f);
}

static void can_data_handle_12(uint8_t* data){
	float tmp = ((float)(((uint16_t)data[1]) << 8 | data[0])) * 0.01f;
	update(ATH, tmp);
	tmp = ((float)(((uint16_t)data[3]) << 8 | data[2])) * 0.01f;
	update(APS, tmp);
	tmp = ((float)(((uint16_t)data[5]) << 8 | data[4]));
	update(CUTOFF_GC_EMS, tmp);
	update(GEAR, (float)data[6]);
	update(FAN_PWM_EMS, (float)data[7]);
}

static void can_data_handle_13(uint8_t* data){ //TODO check endianess
	float tmp = (float)(((double)*((uint32_t*)data)) * 0.01);
	update(FUELCONS, tmp);
	tmp = (float)(((double)*(((uint32_t*)data))+1) * 0.001);
	update(DISTTRIP, tmp);
}

static void can_data_handle_14(uint8_t* data){
	update(DAM_FL, ((float)(((uint16_t)data[1]) << 8 | data[0])) * 0.02f);
	update(DAM_FR, ((float)(((uint16_t)data[3]) << 8 | data[2])) * 0.02f);
	update(DAM_RR, ((float)(((uint16_t)data[5]) << 8 | data[4])) * 0.02f);
	update(DAM_RL, ((float)(((uint16_t)data[7]) << 8 | data[6])) * 0.02f);
}

static void can_data_handle_15(uint8_t* data){
	int16_t* _data = (int16_t*) data;
	update(ACCY,((float)(((uint16_t)data[1]) << 8 | data[0])) * 0.001f);
	update(STEER,((float)(_data[1]) )* 0.01f);
	update(SPEED,((float)(((uint16_t)data[5]) << 8 | data[4])) * 0.01f);
	update(ACCX,((float)(((uint16_t)data[7]) << 8 | data[6])) * 0.001f);
}

static void can_data_handle_16(uint8_t* data){
	update(NMOT,((float)(((uint16_t)data[1]) << 8 | data[0])));
	update(LAMBDA,((float)(((uint16_t)data[3]) << 8 | data[2])) * 0.01f);
	update(FLC, ((float)data[4])*0.005f + 72.0f);
	update(B_LSUOP,((float)data[5]));
	update(GEAR, (float)data[6]);
	update(TMOT,((float)data[7]) - 40.0f);
}

static void can_data_handle_17(uint8_t* data){
	update(NMOT,((float)(((uint16_t)data[1]) << 8 | data[0])));
	update(B_LAUNCHSW,(float)data[2]);
	update(B_AUTOSHIFTSW,(float)data[3]);
	update(B_CLUTCH_OPEN,(float)data[4]);
	update(B_UPSHEVENT_EMS,(float)data[5]);
	update(MI_LAUNCH,((float)data[6])*0.5f);
	update(GEAR, (float)data[7]);
}

static void can_data_handle_18(uint8_t* data){
	update(VWHEEL_FL,((float)(((uint16_t)data[1]) << 8 | data[0])) * 0.01f);
	update(VWHEEL_FR,((float)(((uint16_t)data[3]) << 8 | data[2])) * 0.01f);
	update(VWHEEL_RL,((float)(((uint16_t)data[5]) << 8 | data[4])) * 0.01f);
	update(VWHEEL_RR,((float)(((uint16_t)data[7]) << 8 | data[6])) * 0.01f);
}

static void can_data_handle_19(uint8_t* data){
	update(SPEED,((float)(((uint16_t)data[1]) << 8 | data[0])) * 0.01f);
	update(SLIP_ACT,((float)(((uint16_t)data[3])<<8| data[2])) * 0.1f);
	update(GC_STATE_EMS, (float) data[4]);
	update(MI_LAUNCH,((float)data[5])*0.5f);
	update(XXXXX,((float)data[6]));
}

static void can_data_handle_20(uint8_t* data){
	update(UPSHIFTERRCNT, (float)(((uint16_t)data[1]) << 8 | data[2]));
	update(DNSHIFTERRCNT, (float)(((uint16_t)data[3]) << 8 | data[4]));
	update(SHIFTUP_PWM_EMS,((float)data[4]));
	update(SHIFTDN_PWM_EMS,((float)data[5]));
	update(DNSHIFTERRCNT, ((float)(((uint16_t)data[7]) << 8 | data[6])) * 0.001f);
}





