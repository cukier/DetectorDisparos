#include<18F452.h>

#use delay(crystal = 10MHz, clock = 40MHz)
#use rs232(xmit = PIN_C6, baud = 9600)

#fuses H4

static long long tick, tempo;
static long nrDisparos;

#INT_EXT
void ext_isr() {
	clear_interrupt(INT_EXT);
	nrDisparos++;
	tempo = tick;
	tick = 0;
}

#INT_TIMER0
void timer0_isr() {
	clear_interrupt(INT_TIMER0);
	set_timer0(55535);
	tick++;
}

int main(void) {
	set_timer0(55535);
	setup_timer_0(T0_INTERNAL);
	clear_interrupt(INT_TIMER0);
	clear_interrupt(INT_EXT);
	enable_interrupts(INT_EXT_H2L);
	enable_interrupts(INT_TIMER0);
	enable_interrupts(GLOBAL);
	while (true) {
		printf("\fDisparos: %Lu", nrDisparos);
		printf("\n\rTempo: %.3f", (float) tempo / 1000);
		delay_ms(500);
	}
}
