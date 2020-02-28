#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include "main.h"

#define TIMEOUT_ENABLE
#define USE_LED_UPDATE_FLAG
#define BLINKING_PRESCALER (1)

#define	LEFT_SIDE_LED_0  (0x00010000)
#define	LEFT_SIDE_LED_1  (0x00020000)
#define	LEFT_SIDE_LED_2  (0x00040000)
#define	LEFT_SIDE_LED_3  (0x00080000)
	
#define	RIGHT_SIDE_LED_0 (0x00100000)
#define	RIGHT_SIDE_LED_1 (0x00200000)
#define	RIGHT_SIDE_LED_2 (0x00400000)
#define	RIGHT_SIDE_LED_3 (0x00800000)
		
#define	RGB_LED_0_R      (0x00000001)
#define	RGB_LED_1_R      (0x00000002)
#define	RGB_LED_2_R      (0x00004000)
#define	RGB_LED_3_R      (0x00008000)

#define	RGB_LED_0_G      (0x01000000)
#define	RGB_LED_1_G      (0x02000000)
#define	RGB_LED_2_G      (0x04000000)
#define	RGB_LED_3_G      (0x08000000)

#define	RGB_LED_0_B      (0x10000000)
#define	RGB_LED_1_B      (0x20000000)
#define	RGB_LED_2_B      (0x40000000)
#define	RGB_LED_3_B      (0x80000000)

#define	RGB_LED_0        (RGB_LED_0_R | RGB_LED_0_G | RGB_LED_0_B)
#define	RGB_LED_1        (RGB_LED_1_R | RGB_LED_1_G | RGB_LED_1_B)
#define	RGB_LED_2        (RGB_LED_2_R | RGB_LED_2_G | RGB_LED_2_B)
#define	RGB_LED_3        (RGB_LED_3_R | RGB_LED_3_G | RGB_LED_3_B)
	
#define	RGB_LED_R        (RGB_LED_0_R | RGB_LED_1_R | RGB_LED_2_R | RGB_LED_3_R)
#define	RGB_LED_G        (RGB_LED_0_G | RGB_LED_1_G | RGB_LED_2_G | RGB_LED_3_G)
#define	RGB_LED_B        (RGB_LED_0_B | RGB_LED_1_B | RGB_LED_2_B | RGB_LED_3_B)

#define	TOP_LED_0        (0x00000001)
#define	TOP_LED_1        (0x00000002)
#define	TOP_LED_2        (0x00000004)
#define	TOP_LED_3        (0x00000008)
#define	TOP_LED_4        (0x00000010)
#define	TOP_LED_5        (0x00000020)
#define	TOP_LED_6        (0x00000040)
#define	TOP_LED_7        (0x00000080)
#define	TOP_LED_8        (0x00000100)
#define	TOP_LED_9        (0x00000200)
#define	TOP_LED_10       (0x00000400)
#define	TOP_LED_11       (0x00000800)
#define	TOP_LED_12       (0x00001000)
#define	TOP_LED_13       (0x00002000)
#define	TOP_LED_14       (0x00004000)
#define	TOP_LED_15       (0x00008000)
	
#define	RPM_LEDS         (TOP_LED_2 | TOP_LED_3 | TOP_LED_4 | TOP_LED_5 | TOP_LED_6 | TOP_LED_7 | TOP_LED_8 | TOP_LED_9 | TOP_LED_10 | TOP_LED_11 | TOP_LED_12 | TOP_LED_13)


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
