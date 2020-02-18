
#ifndef DISPLAY_RENDERER_H
#define DISPLAY_RENDERER_H

#include "can_data_provider.h"
#include "stm32f4xx_hal.h"
/*
typedef struct{
	float value;
	uint8_t did_change;
}can_value_;
*/

typedef struct{
	char* str;
	can_value* can_value;
	uint16_t scale;
	uint16_t text_color;
	uint16_t background_color;
	uint16_t highlighted_text_color;
}text_renderer_data;

typedef struct{
	uint16_t color;
	uint16_t highlight_color;
}color_fill_data;


void text_renderer(uint16_t x,uint16_t y,uint16_t w,uint16_t h, void* data, uint16_t flags);
void color_fill_renderer(uint16_t x,uint16_t y,uint16_t w,uint16_t h, void* data, uint16_t flags);

#endif

