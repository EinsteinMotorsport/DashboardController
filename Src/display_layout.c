#include "display_layout.h"
#include <stdio.h>
#include "led_driver.h"



/*
extern void color_fill_renderer(struct display_region* region, void* data, uint16_t flags);
extern void text_renderer(struct display_region* region, void* data, uint16_t flags);

can_value test_data = {89.350f,1};

text_renderer_data test_5 = {"Tmot%.1f",&test_data,3,WHITE,BLACK,GREEN};
color_fill_data test_0 = {PINK,   BLUE};
color_fill_data test_1 = {CYAN,   BLUE};
color_fill_data test_2 = {YELLOW, BLUE};
color_fill_data test_3 = {GREEN,  BLUE};
color_fill_data test_4 = {RED,    BLUE};


static display_page page1 = {5,(display_region[]){
//														{&test_4, 0, 0, 320, 80, color_fill_renderer},
  													{&test_5, 0, 0, 320, 80, text_renderer},
														{&test_1, 5, 240 - 3*SCALING_FACTOR*16 - 10, NUMBER_CHARS*SCALING_FACTOR*10, SCALING_FACTOR*16, color_fill_renderer},
														{&test_2, 5, 240 - 2*SCALING_FACTOR*16 - 5, NUMBER_CHARS*SCALING_FACTOR*10, SCALING_FACTOR*16, color_fill_renderer},
														{&test_3, 5, 240 - 1*SCALING_FACTOR*16, NUMBER_CHARS*SCALING_FACTOR*10, SCALING_FACTOR*16, color_fill_renderer},
														{&test_2, 220,80,100,160,color_fill_renderer}}};
static display_page page2 = {2,(display_region[]){
														{&test_0,   0, 100, 100, 100, color_fill_renderer},
														{&test_0, 100, 100, 100, 100, color_fill_renderer}}};
*/
static display_page** left_pages;
static display_page** right_pages;

static int amount_right_pages;
static int amount_left_pages;

static int current_left_page = 0;
static int current_right_page = 0;


void display_layout_init(display_page** left,display_page** right, int amount_left, int amount_right){
	
	left_pages = left;
	right_pages = right;
	
	amount_left_pages = amount_left;
	amount_right_pages = amount_right;
	
	display_redraw_layout(DISPLAY_ID_ALL);
}

void display_draw_layout(DISPLAY_ID id,int flags){
	display_page* curr;
	if (id & DISPLAY_ID_LEFT){
		display_select(DISPLAY_ID_LEFT);
		display_fill(BLACK);
		curr = left_pages[current_left_page];
		for (int i = 0;i < curr->amount_regions; i++){
			uint16_t x,y,w,h;
			x = curr->regions[i].posx;
			y = curr->regions[i].posy;
			w = curr->regions[i].width;
			h = curr->regions[i].height;			
			uint8_t led = curr->regions[i].handler(x,y,w,h, curr->regions[i].data, LAYOUT_FLAG_REDRAW);
		}
	}
	if (id & DISPLAY_ID_RIGHT){
		display_select(DISPLAY_ID_RIGHT);
		display_fill(BLACK);
		curr = right_pages[current_right_page];
		for (int i = 0;i < curr->amount_regions; i++){
			uint16_t x,y,w,h;
			x = curr->regions[i].posx;
			y = curr->regions[i].posy;
			w = curr->regions[i].width;
			h = curr->regions[i].height;	
			uint8_t led_flags = curr->regions[i].handler(x,y,w,h, curr->regions[i].data, LAYOUT_FLAG_REDRAW);
			led_set(curr->regions[i].led_id,led_flags);
		}
	}
}

void display_redraw_layout(DISPLAY_ID id){
	display_draw_layout(id,LAYOUT_FLAG_REDRAW);
}

void display_update_layout(DISPLAY_ID id){
	display_draw_layout(id, 0);
}


void display_layout_next_page(DISPLAY_ID id){
	if(id & DISPLAY_ID_LEFT){
		current_left_page = (current_left_page + 1) % amount_left_pages;
	}
	if(id & DISPLAY_ID_RIGHT){
		current_right_page = (current_right_page + 1) % amount_right_pages;
	}
	display_redraw_layout(id);
}

void display_layout_prev_page(DISPLAY_ID id){
	if(id & DISPLAY_ID_LEFT){
		current_left_page = (current_left_page + amount_left_pages -1) % amount_left_pages;
	}
	if(id & DISPLAY_ID_RIGHT){
		current_right_page = (current_right_page + amount_right_pages - 1) % amount_right_pages;
	}
	display_redraw_layout(id);
}


/*
void text_renderer(struct display_region* region, void* data, uint16_t flags){
	
	
	text_renderer_data* _data = data;

	if (flags & LAYOUT_FLAG_REDRAW || _data->can_value->did_change){

		int chars = (region->width) / (FONT_WIDTH * _data->scale);
		int rows = region->height / (FONT_HEIGHT * _data->scale);
		char tmp[chars*rows + 1];
		int a = snprintf(tmp,chars*rows + 1,_data->str,_data->can_value->value);
		//char* tmp = _data->str;
		for (int j = 0; j<rows;j++){
			display_print_n_string(tmp+j*chars,region->posx,region->posy+j*_data->scale*FONT_HEIGHT,_data->scale,_data->text_color,_data->background_color,chars);
		}
		_data->can_value->did_change = 0;
	}
}*/



