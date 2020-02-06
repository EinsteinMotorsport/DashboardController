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
	int scale;
	uint16_t text_color;
	uint16_t background_color;
	uint16_t highlighted_text_color;
}text_renderer_data;



extern void color_fill_renderer(struct display_region* region, void* data, uint16_t flags);
extern void text_renderer(struct display_region* region, void* data, uint16_t flags);

text_renderer_data test_5 = {"Tmot %f",1.0,3,YELLOW,RED,GREEN};
color_fill_data test_0 = {PINK,   BLUE};
color_fill_data test_1 = {CYAN,   BLUE};
color_fill_data test_2 = {YELLOW, BLUE};
color_fill_data test_3 = {GREEN,  BLUE};
color_fill_data test_4 = {RED,    BLUE};


static display_page page1 = {5,(display_region[]){
//														{&test_4, 0, 0, NUMBER_CHARS*(SCALING_FACTOR+ 2)*10, (SCALING_FACTOR+2)*16, color_fill_renderer},
														{&test_5, 0, 0, NUMBER_CHARS*(SCALING_FACTOR+ 2)*10, (SCALING_FACTOR+2)*16, text_renderer},
														{&test_1, 5, 240 - 3*SCALING_FACTOR*16 - 10, NUMBER_CHARS*SCALING_FACTOR*10, SCALING_FACTOR*16, color_fill_renderer},
														{&test_2, 5, 240 - 2*SCALING_FACTOR*16 - 5, NUMBER_CHARS*SCALING_FACTOR*10, SCALING_FACTOR*16, color_fill_renderer},
														{&test_3, 5, 240 - 1*SCALING_FACTOR*16, NUMBER_CHARS*SCALING_FACTOR*10, SCALING_FACTOR*16, color_fill_renderer},
														{&test_2, 220,80,100,160,color_fill_renderer}}};
static display_page page2 = {2,(display_region[]){
														{&test_0,   0, 100, 100, 100, color_fill_renderer},
														{&test_0, 100, 100, 100, 100, color_fill_renderer}}};

static display_page* left_pages[] = {
	&page1,
	&page1,
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
	int chars = region->width / (FONT_WIDTH * _data->scale);
	int rows = region->height / (FONT_HEIGHT * _data->scale);
//	int i = 0;
	char* tmp;
	int k = snprintf(tmp ,chars * rows,_data->str, _data->value);
	int index = 0;
	for (int j = 0; j<rows;j++){
		for (int i = 0; i<chars;i++){
			if (index++ < k) display_print_char(tmp[index],
																					region->posx + i*FONT_WIDTH*_data->scale,
																					region->posy + j*FONT_HEIGHT*_data->scale,
																					_data->scale,flags & LAYOUT_FLAG_HIGHLIGHTED ? _data->highlighted_text_color :_data->text_color,
																					_data->background_color);
		}
	}
}



