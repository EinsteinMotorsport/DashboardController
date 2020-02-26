
#include "display_driver.h"
#include "display_renderer.h"
#include <stdio.h>

void text_renderer(uint16_t x,uint16_t y,uint16_t w,uint16_t h, void* data, uint16_t flags){
	text_renderer_data* _data = data;

	if (flags & 0x1 || _data->can_value->did_change){

		int chars = (w) / (FONT_WIDTH * _data->scale);
		int rows =  h / (FONT_HEIGHT * _data->scale);
		display_fill_rect(x,rows*FONT_HEIGHT+y,w,h-rows*FONT_HEIGHT,_data->background_color);
		char tmp[chars*rows + 1];
		int a = snprintf(tmp,chars*rows + 1,_data->str,_data->can_value->value);
		//char* tmp = _data->str;
		for (int j = 0; j<rows;j++){
			display_print_n_string(tmp+j*chars,x,y+j*_data->scale*FONT_HEIGHT,_data->scale,_data->text_color,_data->background_color,chars);
		}
		_data->can_value->did_change = 0;
	}
}


void color_fill_renderer(uint16_t x,uint16_t y,uint16_t w,uint16_t h, void* data, uint16_t flags){
	if (flags & 0x1){
		color_fill_data* _data = (color_fill_data*) data;
		display_fill_rect(x,y,w,h, (flags & 0x2) ? _data->highlight_color : _data->color);
	}
}
