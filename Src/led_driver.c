#include "led_driver.h"
#include "stm32f4xx_hal.h"


static uint32_t led_status;
static uint32_t led_blinking;
static uint8_t blinking_on;
static uint32_t blink_counter;

#ifdef TIMEOUT_ENABLE

static char led_timeout[32]; 

#endif

void led_init(void){
	blink_counter = 0;
	led_status = ~0;
	led_blinking = 0;
	#ifdef TIMEOUT_ENABLE
		for (int i = 0; i<32;i++) led_timeout[i] = 0;
	#endif
}

void led_update(void){

	if (++blink_counter == BLINKING_PRESCALER){
		blink_counter = 0;
		blinking_on = !blinking_on;
	}

	uint32_t output = led_status & (blinking_on ? ~led_blinking : ~0);	
	
	#ifdef TIMEOUT_ENABLE
	if (!blink_counter){ 
		for (int i = 0; i<32;i++){
			if (led_timeout[i] && !(--led_timeout[i])) led_status &= ~(1<<i);
		}
	}
	#endif

	uint32_t gpioa_leds = output & 0x00FF;
	uint32_t gpioc_leds = output & 0xF000 >> 24;
	uint32_t gpioe_leds = output & 0x0F00 >> 16; 
	GPIOA->BSRR = ((~gpioa_leds << 16) & 0xFF00) | gpioa_leds;
	GPIOC->BSRR = ((~gpioc_leds << 16) & 0x0F00) | gpioc_leds;
	GPIOE->BSRR = ((~gpioe_leds << 16) & 0x0F00) | gpioe_leds;
}

void led_set(uint32_t id, uint8_t flags){
#ifdef USE_LED_UPDATE_FLAG
	if (flags & LED_UPDATE){
#endif
		if (flags & LED_ON){
			led_status |= id;
		}else{
			led_status &= ~id;
		}
		
		if (flags & LED_BLINKING){
			led_blinking |= id;
		}else{
			led_blinking &= ~id;
		}
		#ifdef TIMEOUT_ENABLE
		uint32_t _id = id;
		int i = 0;
		do {
			if (_id & 1) led_timeout[i] = (flags & LED_TIMEOUT_MASK) >> 4;
		}while (i++,_id >>= 1);
		#endif
		
		
#ifdef USE_LED_UPDATE_FLAG		
	}
#endif
}

void led_set_rgb(uint32_t id, uint8_t flags, LED_COLOR color){
	led_set(id & RGB_LED_R, flags & (color & LED_RED   ? ~0 : ~LED_ON));
	led_set(id & RGB_LED_G, flags & (color & LED_GREEN ? ~0 : ~LED_ON));
	led_set(id & RGB_LED_B, flags & (color & LED_BLUE  ? ~0 : ~LED_ON));	
}






