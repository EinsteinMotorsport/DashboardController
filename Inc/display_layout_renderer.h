#ifndef DISPLAY_LAYOUT_RENDERER_H
#define DISPLAY_LAYOUT_RENDERER_H

#include "display_driver.h"


typedef struct{
	uint16_t color;
	uint16_t highlight_color;
}color_fill_data;


void text_renderer(struct display_region* region, void* data, uint16_t flags);
void color_fill_renderer(struct display_region* region, void* data, uint16_t flags);

#endif


