

#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

#include "main.h"

#ifndef FONT_WIDTH
#define FONT_WIDTH (10)
#define FONT_HEIGHT (16)
#endif


#define COLORMAP(c) (((c & 0xF80000) >> 8) | ((c & 0xFC00) >> 5) | ((c & 0xF8) >> 3))

typedef enum {
	DISPLAY_ID_NONE  = 0x00,
	DISPLAY_ID_LEFT  = 0x01,
	DISPLAY_ID_RIGHT = 0x02,
	DISPLAY_ID_ALL   = DISPLAY_ID_LEFT \
                   | DISPLAY_ID_RIGHT,
} DISPLAY_ID;

typedef enum {
	BLACK  = 0x0000,
	WHITE  = 0xFFFF,
	RED    = COLORMAP(0xFF0000),
  GREEN  = COLORMAP(0x00FF00),
	BLUE   = COLORMAP(0x0000FF),

	YELLOW = COLORMAP(0xFFFF00),
	PINK   = COLORMAP(0xFF00FF),
	CYAN   = COLORMAP(0x00FFFF),
	
}COLOR;



typedef enum {
	D_CMD_SLPOUT  = 0x11,
	D_CMD_NORON   = 0x13,
	D_CMD_INVOFF  = 0x20,
	D_CMD_INVON   = 0x21,
	D_CMD_DISPOFF = 0x28,
	D_CMD_DISPON  = 0x29,
	D_CMD_CASET   = 0x2A,
	D_CMD_RASET   = 0x2B,
	D_CMD_RAMWR   = 0x2C,
	D_CMD_MADCTL  = 0x36,
	D_CMD_COLMOD  = 0x3A,
	
}DISPLAY_COMMAND;



void display_write_command(DISPLAY_COMMAND);
void display_write_data(uint16_t);
void display_select(DISPLAY_ID);
void display_init(void);
void display_fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void display_fill(uint16_t);
void display_print_string(char* str, uint16_t xpos, uint16_t ypos, int scale, uint16_t text_color, uint16_t background_color);
void display_print_char(char chr, uint16_t xpos, uint16_t ypos, int scale, uint16_t text_color, uint16_t background_color);

void display_invert(int);
void display_toggle_invert(void);


#endif
