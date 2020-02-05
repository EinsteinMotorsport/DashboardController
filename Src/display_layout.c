#include "display_layout.h"

void fill_region(display_region* region);


display_region lt1 = {0,0,0,100,100, &fill_region};
display_region first_page[] = {
	{0,   0, 0, 100, 100, &fill_region},
	{0, 100, 0, 100, 100, &fill_region},
};


static display_region* left_pages[] = {
	(display_region[]){{0,   0, 0, 100, 100, &fill_region},
		                 {0, 100, 0, 100, 100, &fill_region},},
};
static display_region* right_pages[] = {
	(display_region[]){{0,   0, 0, 100, 100, &fill_region},
		                 {0, 100, 0, 100, 100, &fill_region},},
};

static int amount_right_pages = sizeof(left_pages);
static int amount_left_pages = sizeof(right_pages);

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
	display_region* curr = left_pages[current_left_page];
	while (curr){
		curr->handler((struct display_region*) curr);
		curr++;
	}
	display_select(DISPLAY_ID_RIGHT);
	curr = right_pages[current_right_page];
	while (curr){
		curr->handler((struct display_region*) curr);
		curr++;
	}	
}

void display_update_layout(){
	display_select(DISPLAY_ID_LEFT);
	display_region* curr = left_pages[current_left_page];
	while (curr){
		if (curr->data_source->changed) curr->handler((struct display_region*) curr);
		curr++;
	}
	display_select(DISPLAY_ID_RIGHT);
	curr = right_pages[current_right_page];
	while (curr){
		if (curr->data_source->changed) curr->handler((struct display_region*) curr);
		curr++;
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

void fill_region(display_region* region){
	display_fill_rect(region->posx,region->posy,region->width, region->height, CYAN);
}

