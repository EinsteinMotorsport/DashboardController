#ifndef DISPLAY_LAYOUT_H
#define DISPLAY_LAYOUT_H

#include "stm32f4xx_hal.h"
#include "display_driver.h"


void display_layout_init(int left_page, int right_page);
void display_redraw_layout(void);
void display_update_layout(void);
void display_layout_next_page(DISPLAY_ID);
void display_layout_prev_page(DISPLAY_ID);

enum VALUE_TYPE{
	VALUE_TYPE_FLOAT,
	VALUE_TYPE_UCHAR,
	VALUE_TYPE_USHORT,
	VALUE_TYPE_SCHAR,
	VALUE_TYPE_SSHORT,	
};

enum LAYOUT_FLAGS{
	LAYOUT_FLAG_REDRAW = 0x01,
	LAYOUT_FLAG_HIGHLIGHTED = 0x02,
};


typedef union {
	uint8_t uchar;
	int8_t schar;
	uint16_t ushort;
	int16_t sshort;
	float _float;
}display_value;


typedef struct {
	display_value value;
	display_value offset;
	display_value factor;
	char* description;
	uint8_t changed;
	enum VALUE_TYPE type;
}display_data;



typedef struct display_region{
	void* data;
	uint16_t posx, posy;
	uint16_t width, height;
	void (*handler)(struct display_region*, void*, uint16_t);
}display_region;

typedef struct{
	uint8_t amount_regions;
	display_region* regions;
}display_page;


#endif

