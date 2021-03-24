#include "delay.h"

uint32_t tick;
void delay_ms(int time){
	tick = time*3600;
	while(tick--){
	}
}

void delay_us(int time){
	tick = time*3.6;
	while(tick--){
	}
}


