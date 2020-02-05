#include "display_layout.h"

#define SCALING_FACTOR (3)
#define NUMBER_CHARS (7)

typedef struct{
	uint16_t color;
}fill_region_data;

void fill_region(display_region* region, void* data);

fill_region_data test_0 = {PINK};
fill_region_data test_1 = {CYAN};
fill_region_data test_2 = {YELLOW};
fill_region_data test_3 = {GREEN};
fill_region_data test_4 = {RED};


static display_page page1 = {5,(display_region[]){
														{&test_4, 0, 0, NUMBER_CHARS*(SCALING_FACTOR+ 2)*10, (SCALING_FACTOR+2)*16, &fill_region},
														{&test_1, 5, 240 - 3*SCALING_FACTOR*16 - 10, NUMBER_CHARS*SCALING_FACTOR*10, SCALING_FACTOR*16, &fill_region},
														{&test_2, 5, 240 - 2*SCALING_FACTOR*16 - 5, NUMBER_CHARS*SCALING_FACTOR*10, SCALING_FACTOR*16, &fill_region},
														{&test_3, 5, 240 - 1*SCALING_FACTOR*16, NUMBER_CHARS*SCALING_FACTOR*10, SCALING_FACTOR*16, &fill_region},
														{&test_2, 220,80,100,160,&fill_region}}};
static display_page page2 = {2,(display_region[]){
														{&test_0,   0, 100, 100, 100, &fill_region},
														{&test_0, 100, 100, 100, 100, &fill_region}}};

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
		curr->regions[i].handler((struct display_region*) &curr->regions[i], curr->regions[i].data);
	}
	display_select(DISPLAY_ID_RIGHT);
	display_fill(BLACK);
	curr = right_pages[current_right_page];
	for (int i = 0;i < curr->amount_regions; i++){
		curr->regions[i].handler((struct display_region*) &curr->regions[i], curr->regions[i].data);
	}
}

void display_update_layout(){
	display_select(DISPLAY_ID_LEFT);
	display_page* curr = left_pages[current_left_page];
	for (int i = 0;i < curr->amount_regions; i++){
		curr->regions[i].handler((struct display_region*) &curr->regions[i], curr->regions[i].data);
	}
	display_select(DISPLAY_ID_RIGHT);
	curr = right_pages[current_right_page];
	for (int i = 0;i < curr->amount_regions; i++){
		curr->regions[i].handler((struct display_region*) &curr->regions[i], curr->regions[i].data);
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

void fill_region(display_region* region, void* data){
	
	fill_region_data* _data = (fill_region_data*) data;
	
	display_fill_rect(region->posx,region->posy,region->width, region->height, _data->color);
}

