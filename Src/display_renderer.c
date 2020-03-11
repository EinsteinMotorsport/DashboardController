
#include "display_driver.h"
#include "display_renderer.h"
#include <stdio.h>
#include "einstein_binary_8.h"

uint8_t text_renderer(uint16_t x,uint16_t y,uint16_t w,uint16_t h, void* data, uint16_t flags){
	text_renderer_data* _data = data;

	if (flags & 0x1 || _data->can_value->flags){

		uint16_t bgc = _data->background_color;
		uint16_t fgc = _data->text_color;
		if (_data->can_value->flags & 0x4) bgc = YELLOW,fgc = BLACK;
		if (_data->can_value->flags & 0x2) bgc = RED, fgc = WHITE;
		
		int chars = (w) / (FONT_WIDTH * _data->scale);
		int rows =  h / (FONT_HEIGHT * _data->scale);
		int yoff = (h - (rows*FONT_HEIGHT* _data->scale))/2;
		
		display_fill_rect(x,y,w,yoff,bgc);
		//display_fill_rect(x,rows*FONT_HEIGHT+y+yoff,w,h-(rows*FONT_HEIGHT)-yoff,bgc);
		
		
		char tmp[chars*rows + 1];
		int a = snprintf(tmp,chars*rows + 1,_data->str,_data->can_value->value);
		//char* tmp = _data->str;
		for (int j = 0; j<rows;j++){
			display_print_n_string(tmp+j*chars,x,y+yoff+j*_data->scale*FONT_HEIGHT,_data->scale,fgc,bgc,chars);
		}
		_data->can_value->flags &= ~1;
		display_fill_rect(x,rows*FONT_HEIGHT*_data->scale+y+yoff,w,(h -(rows*FONT_HEIGHT*_data->scale))- yoff,bgc);
		//display_fill_rect(x,y,w,yoff,RED);


	}
	return _data->can_value->flags;
}


uint8_t color_fill_renderer(uint16_t x,uint16_t y,uint16_t w,uint16_t h, void* data, uint16_t flags){
	if (flags & 0x1){
		color_fill_data* _data = (color_fill_data*) data;
		display_fill_rect(x,y,w,h, (flags & 0x2) ? _data->highlight_color : _data->color);
	}
	return 0;
}

uint8_t logo_renderer(uint16_t x, uint16_t y, uint16_t w, uint16_t h, void* data, uint16_t flags){
	if (flags & 1){
		display_set_rect(200,0,120,80);
		for (int i = 0; i<1200;i++){
			char a = einstein_logo[i];
			for (int i = 7; i>= 0; i--)display_write_data(a & 1<<i ? YELLOW : BLACK);
		}
	}
	return 0;

}


