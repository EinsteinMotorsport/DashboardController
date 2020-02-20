#include "can_data_provider.h"
#include <stdlib.h>

static can_value* values; 

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

void can_data_init(CAN_HandleTypeDef* _hcan){
	hcan = _hcan;
	values = malloc(sizeof(can_value) * NUMBER_CAN_VALUES);
}

void can_data_update(){
	
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
/*					case 0x11:
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
						break;*/
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
	float tmp;
	if (values[TMOT].value     !=(tmp = ((float)data[0]) - 40.0f))  values[TMOT].value     = tmp, values[TMOT].did_change     = 1;
	if (values[TMOT2].value    !=(tmp = ((float)data[1]) - 40.0f))  values[TMOT2].value    = tmp, values[TMOT2].did_change    = 1;
	if (values[TFUEL].value    !=(tmp = ((float)data[2]) - 40.0f))  values[TFUEL].value    = tmp, values[TFUEL].did_change    = 1;
	if (values[TOIL].value     !=(tmp = ((float)data[3]) - 40.0f))  values[TOIL].value     = tmp, values[TOIL].did_change     = 1;
	if (values[TECU_SYS].value !=(tmp = ((float)data[4]) - 40.0f))  values[TECU_SYS].value = tmp, values[TECU_SYS].did_change = 1;
	if (values[UB].value       !=(tmp = ((float)data[5]) * 0.001f)) values[UB].value       = tmp, values[UB].did_change       = 1;
	if (values[B_ENGON].value  !=(tmp =  (float)data[6]))           values[B_ENGON].value  = tmp, values[B_ENGON].did_change  = 1;
}
static void can_data_handle_11(uint8_t* data){
}
static void can_data_handle_12(uint8_t* data){
}
static void can_data_handle_13(uint8_t* data){
}
static void can_data_handle_14(uint8_t* data){
}
static void can_data_handle_15(uint8_t* data){
}
static void can_data_handle_16(uint8_t* data){
}
static void can_data_handle_17(uint8_t* data){
}
static void can_data_handle_18(uint8_t* data){
}
static void can_data_handle_19(uint8_t* data){
}
static void can_data_handle_20(uint8_t* data){
}





