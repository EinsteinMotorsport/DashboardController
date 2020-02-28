#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include "main.h"

#define TIMEOUT_ENABLE
#define USE_LED_UPDATE_FLAG
#define BLINKING_PRESCALER (1)


typedef enum {
	LEFT_SIDE_LED_0  = 1<<16,
	LEFT_SIDE_LED_1  = 1<<17,
	LEFT_SIDE_LED_2  = 1<<18,
	LEFT_SIDE_LED_3  = 1<<19,
	
	RIGHT_SIDE_LED_0 = 1<<20,
	RIGHT_SIDE_LED_1 = 1<<21,
	RIGHT_SIDE_LED_2 = 1<<22,
	RIGHT_SIDE_LED_3 = 1<<23,
		
	RGB_LED_0_R      = 1<<0,
	RGB_LED_1_R      = 1<<1,
	RGB_LED_2_R      = 1<<14,
	RGB_LED_3_R      = 1<<15,

	RGB_LED_0_G      = 1<<24,
	RGB_LED_1_G      = 1<<25,
	RGB_LED_2_G      = 1<<26,
	RGB_LED_3_G      = 1<<27,

	RGB_LED_0_B      = 1<<28,
	RGB_LED_1_B      = 1<<29,
	RGB_LED_2_B      = 1<<30,
	RGB_LED_3_B      = 1<<31,

	RGB_LED_0        = RGB_LED_0_R | RGB_LED_0_G | RGB_LED_0_B,
	RGB_LED_1        = RGB_LED_1_R | RGB_LED_1_G | RGB_LED_1_B,
	RGB_LED_2        = RGB_LED_2_R | RGB_LED_2_G | RGB_LED_2_B,
	RGB_LED_3        = RGB_LED_3_R | RGB_LED_3_G | RGB_LED_3_B,
	
	RGB_LED_R        = RGB_LED_0_R | RGB_LED_1_R | RGB_LED_2_R | RGB_LED_3_R,
	RGB_LED_G        = RGB_LED_0_G | RGB_LED_1_G | RGB_LED_2_G | RGB_LED_3_G,
	RGB_LED_B        = RGB_LED_0_B | RGB_LED_1_B | RGB_LED_2_B | RGB_LED_3_B,

	TOP_LED_0        = 1<<0,
	TOP_LED_1        = 1<<1,
	TOP_LED_2        = 1<<2,
	TOP_LED_3        = 1<<3,
	TOP_LED_4        = 1<<4,
	TOP_LED_5        = 1<<5,
	TOP_LED_6        = 1<<6,
	TOP_LED_7        = 1<<7,
	TOP_LED_8        = 1<<8,
	TOP_LED_9        = 1<<9,
	TOP_LED_10       = 1<<10,
	TOP_LED_11       = 1<<11,
	TOP_LED_12       = 1<<12,
	TOP_LED_13       = 1<<13,
	TOP_LED_14       = 1<<14,
	TOP_LED_15       = 1<<15,
	
	RPM_LEDS         = TOP_LED_2 | TOP_LED_3 | TOP_LED_4 | TOP_LED_5 | TOP_LED_6 | TOP_LED_7 | TOP_LED_8 | TOP_LED_9 | TOP_LED_10 | TOP_LED_11 | TOP_LED_12 | TOP_LED_13,
	
}LED_ID;


typedef enum{
	LED_UPDATE       = 1<<0,
	LED_ON           = 1<<1,
	LED_OFF          = 0,
	LED_BLINKING     = 1<<2,
	LED_TIMEOUT_MASK = 0xF0,
}LED_FLAGS;

typedef enum{
	LED_BLACK = 0,
	
	LED_RED   = 4,
	LED_GREEN = 2,
	LED_BLUE  = 1,
	
	LED_YELLOW = LED_RED   | LED_GREEN,
	LED_PINK   = LED_RED   | LED_BLUE,
	LED_CYAN   = LED_GREEN | LED_BLUE,
	
	LED_WHITE  = LED_RED   | LED_GREEN | LED_BLUE,
	
	
}LED_COLOR;




void led_init(void);
void led_update(void);

void led_set(uint32_t id, uint8_t flags);
void led_set_rgb(uint32_t id, uint8_t flags,LED_COLOR color);

#endif
