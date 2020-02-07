
#include "display_driver.h"
#include "stm32f4xx_hal.h"

#ifndef FONT_WIDTH
#define FONT_WIDTH (10)
#define FONT_HEIGHT (16)
#endif
#include "font/10x16_horizontal_LSB_1.h"



static int inverted = 0;



void display_invert(int a){
	display_write_command(a ? D_CMD_INVON : D_CMD_INVOFF);
	inverted = a;
}

void display_toggle_invert(void){
	display_invert(!inverted);
}

void display_write_command(DISPLAY_COMMAND command){
	GPIOE->BSRR = (uint32_t)(DisplayC_D_Pin | DisplayRW_Pin) << 16  | (uint32_t)DisplayRD_Pin;
	GPIOD->BSRR = ((uint32_t) ~(command & 0xFF)) << 16 | (uint32_t)(command & 0xFF);	
//	HAL_Delay(1);
	GPIOE->BSRR = DisplayRW_Pin;
//	HAL_Delay(1);
}


void display_write_data(uint16_t data){
	
	GPIOE->BSRR = (uint32_t)(DisplayRW_Pin) << 16  | (uint32_t)(DisplayRD_Pin | DisplayC_D_Pin);
	GPIOD->BSRR = ((uint32_t)~data) << 16 | (uint32_t)data;
//	HAL_Delay(1);
	GPIOE->BSRR = DisplayRW_Pin;
//	HAL_Delay(1);
}



void display_fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color){
	display_write_command(D_CMD_CASET);
	display_write_data(x >> 8);
	display_write_data(x & 0xFF);//X address set
	x += width - 1;
	display_write_data(x >> 8);
	display_write_data(x & 0xFF);//X address set

	display_write_command(D_CMD_RASET);
	display_write_data(y >> 8);
	display_write_data(y & 0xFF);//Y address set
	y += height - 1;
	display_write_data(y >> 8);
	display_write_data(y & 0xFF);//Y address set
	display_write_command(D_CMD_RAMWR);
	
	for(int i = width*height; i > 0; i--){
		display_write_data(color);
	}
}

void display_fill(uint16_t color){
	display_fill_rect(0,0,320,240,color);
}




void display_select(DISPLAY_ID displayID){
	if (displayID & DISPLAY_ID_LEFT) {
		GPIOE->BSRR = DisplayCS1_Pin << 16;
	}else {
		GPIOE->BSRR = DisplayCS1_Pin;
	}

	if (displayID & DISPLAY_ID_RIGHT) {
		GPIOE->BSRR = DisplayCS2_Pin << 16;
	}else {
		GPIOE->BSRR = DisplayCS2_Pin;
	}
}




void display_print_char(char chr, uint16_t xpos, uint16_t ypos, int scale, uint16_t text_color, uint16_t background_color){
	
	display_write_command(D_CMD_CASET);
	display_write_data(xpos >> 8);
	display_write_data(xpos & 0xFF);//X address set
	xpos += scale * FONT_WIDTH - 1;
	display_write_data(xpos >> 8);
	display_write_data(xpos & 0xFF);//X address set

	display_write_command(D_CMD_RASET);
	display_write_data(ypos >> 8);
	display_write_data(ypos & 0xFF);//Y address set
	ypos += scale * FONT_HEIGHT - 1;
	display_write_data(ypos >> 8);
	display_write_data(ypos & 0xFF);//Y address set
	display_write_command(D_CMD_RAMWR);
	
	for(int i = 0; i < FONT_HEIGHT; i++){
		#if FONT_WIDTH > 8
			uint16_t pxrow = ((uint16_t)font[chr][2 * i]) << 8 | (uint16_t)font[chr][2*i + 1];
		#else
			uint16_t pxrow = (uint16_t) font[chr][i];
		#endif
		for(int k = 0; k < scale; k++){
			for(int j = 16 - FONT_WIDTH; j < 16; j++){
				for(int l = 0; l< scale; l++){
					display_write_data(((((uint16_t)1)<<j) & pxrow) ? text_color : background_color);
				}
			}
		}
	}
}

void display_print_string(char* str, uint16_t xpos, uint16_t ypos, int scale, uint16_t text_color, uint16_t background_color){
	int i = 0;
	while(str[i]){
		display_print_char(str[i++], xpos, ypos, scale, text_color, background_color);
		xpos += scale * FONT_WIDTH;
	}
}

void display_print_n_string(char* str, uint16_t xpos, uint16_t ypos, int scale, uint16_t text_color, uint16_t background_color, int n){
	char _str[n+1];
	int i=0;
	while (str[i] && i<n){
		_str[i] = str[i];
		i++;
	}
	while (i < n)_str[i++] = 0x20;
	_str[n] = 0;
	display_print_string(_str,xpos,ypos,scale,text_color,background_color);
}


void display_init(){	
	display_select(DISPLAY_ID_ALL);
	GPIOE->BSRR = ((uint32_t)(DisplayRW_Pin | DisplayRST_Pin) << 16 | (uint32_t)DisplayRD_Pin);
	HAL_Delay(100);
	GPIOE->BSRR = (uint32_t) DisplayRST_Pin;
	HAL_Delay(150);
	display_write_command(D_CMD_SLPOUT);
	HAL_Delay(500);
	display_write_command(D_CMD_COLMOD);
	display_write_data(0x55);
	HAL_Delay(10);
	display_write_command(D_CMD_MADCTL);
	display_write_data(0xA0);
	
	display_write_command(D_CMD_RASET);
	display_write_data(0x0000);
	display_write_data(0x0000);
	display_write_data(0x0000);
	display_write_data(0x00EF);//X address set
	display_write_command(D_CMD_CASET);
	display_write_data(0x0000);
	display_write_data(0x0000);
	display_write_data(0x0001);
	display_write_data(0x003F);//Y address set
	
	display_write_command(D_CMD_INVOFF);
	HAL_Delay(10);
	display_write_command(D_CMD_NORON);
	HAL_Delay(10);
	display_write_command(D_CMD_DISPON);
	HAL_Delay(500);
	
	display_write_command(D_CMD_RAMWR);
	HAL_Delay(10);
}

