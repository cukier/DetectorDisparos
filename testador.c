/*
 * testador.c
 *
 *  Created on: 12/03/2013
 *      Author: cuki
 */
#include<18F452.h>

#use delay(crystal = 8MHz, clock = 32MHz)
#use rs232(xmit = PIN_C6, baud = 9600)

#fuses H4

#INT_TIMER0
void timer0_isr() {
	clear_interrupt(INT_TIMER0);
	set_timer0(10000);
	output_toggle(PIN_C3);
}

int main(void) {
	set_timer0(45535);
	setup_timer_0(T0_INTERNAL | T0_DIV_8);
	clear_interrupt(INT_TIMER0);
	enable_interrupts(INT_TIMER0);
	enable_interrupts(GLOBAL);
	while (TRUE)
		;
	return 0;
}
