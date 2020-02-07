#include "display_layout.h"
//#include "display_layout_renderer.h"

#include <stdio.h>

#define SCALING_FACTOR (3)
#define NUMBER_CHARS (7)


typedef struct{
	uint16_t color;
	uint16_t highlight_color;
}color_fill_data;

typedef struct{
	char* str;
	float value;
	uint16_t scale;
	uint16_t text_color;
	uint16_t background_color;
	uint16_t highlighted_text_color;
}text_renderer_data;



extern void color_fill_renderer(struct display_region* region, void* data, uint16_t flags);
extern void text_renderer(struct display_region* region, void* data, uint16_t flags);

text_renderer_data test_5 = {"Tmot%.1f",89.350f,3,WHITE,BLACK,GREEN};
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

static display_page* left_pages[] = {
	&page1,
	//&page2,
};
static display_page* right_pages[] = {
	&page1,
	&page2,
};

static int amount_right_pages = sizeof(right_pages)/sizeof(display_page*);
static int amount_left_pages = sizeof(left_pages)/sizeof(display_page*);

static int current_left_page;
static int current_right_page;


void display_layout_init(int left_page, int right_page){
	//while (left_pages[amount_left_pages]) amount_left_pages++;
	//while (right_pages[amount_right_pages]) amount_right_pages++;
	current_left_page = left_page % amount_left_pages;
	current_right_page = right_page % amount_right_pages;
	display_redraw_layout();
}

void display_redraw_layout(){
	display_select(DISPLAY_ID_LEFT);
	display_fill(BLACK);
	display_page* curr = left_pages[current_left_page];
	for (int i = 0;i < curr->amount_regions; i++){
		curr->regions[i].handler((struct display_region*) &curr->regions[i], curr->regions[i].data, LAYOUT_FLAG_REDRAW);
	}
	display_select(DISPLAY_ID_RIGHT);
	display_fill(BLACK);
	curr = right_pages[current_right_page];
	for (int i = 0;i < curr->amount_regions; i++){
		curr->regions[i].handler((struct display_region*) &curr->regions[i], curr->regions[i].data, LAYOUT_FLAG_REDRAW);
	}
}

void display_update_layout(){
	display_select(DISPLAY_ID_LEFT);
	display_page* curr = left_pages[current_left_page];
	for (int i = 0;i < curr->amount_regions; i++){
		curr->regions[i].handler((struct display_region*) &curr->regions[i], curr->regions[i].data, 0);
	}
	display_select(DISPLAY_ID_RIGHT);
	curr = right_pages[current_right_page];
	for (int i = 0;i < curr->amount_regions; i++){
		curr->regions[i].handler((struct display_region*) &curr->regions[i], curr->regions[i].data, 0);
	}
}


void display_layout_next_page(DISPLAY_ID id){
	if(id & DISPLAY_ID_LEFT){
		current_left_page = (current_left_page + 1) % amount_left_pages;
	}
	if(id & DISPLAY_ID_RIGHT){
		current_right_page = (current_right_page + 1) % amount_right_pages;
	}
	display_redraw_layout();
}

void display_layout_prev_page(DISPLAY_ID id){
	if(id & DISPLAY_ID_LEFT){
		current_left_page = (current_left_page + amount_left_pages -1) % amount_left_pages;
	}
	if(id & DISPLAY_ID_RIGHT){
		current_right_page = (current_right_page + amount_right_pages - 1) % amount_right_pages;
	}
	display_redraw_layout();
}

void color_fill_renderer(struct display_region* region, void* data, uint16_t flags){
	
	//color_fill_renderer(region,data,flags);
	if (flags & LAYOUT_FLAG_REDRAW){
		color_fill_data* _data = (color_fill_data*) data;
		display_fill_rect(region->posx,region->posy,region->width, region->height, (flags & LAYOUT_FLAG_HIGHLIGHTED) ? _data->highlight_color : _data->color);
	}
}

void text_renderer(struct display_region* region, void* data, uint16_t flags){
	text_renderer_data* _data = data;
	int chars = (region->width) / (FONT_WIDTH * _data->scale);
	int rows = region->height / (FONT_HEIGHT * _data->scale);
	char tmp[chars*rows + 1];
	int a = snprintf(tmp,chars*rows + 1,_data->str,_data->value);
	//char* tmp = _data->str;
	for (int j = 0; j<rows;j++){
		display_print_n_string(tmp+j*chars,region->posx,region->posy+j*_data->scale*FONT_HEIGHT,_data->scale,_data->text_color,_data->background_color,chars);
	}
}



