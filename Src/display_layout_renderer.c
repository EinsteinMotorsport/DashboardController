#include "display_layout_renderer.h"
#include "display_layout.h"


void color_fill_renderer(display_region* region, void* data, uint16_t flags){s
	if (flags & LAYOUT_FLAG_REDRAW){
		color_fill_data* _data = (color_fill_data*) data;
		display_fill_rect(region->posx,region->posy,region->width, region->height, (flags & LAYOUT_FLAG_HIGHLIGHTED) ? _data->highlight_color : _data->color);
	}
}
