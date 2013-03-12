#include<18f45k20.h>

#use delay(crystal = 15MHz, clock = 60MHz)
#use rs232(xmit = PIN_C6, baud = 9600)

#fuses H4

static int t0_config = T0_INTERNAL | T0_DIV_4 | 128;
static long t0_cont = 0xFFFF - 37500;
static long long tick, tempo;
static long nrDisparos;

//#INT_TIMER0
//void isr_timer0() {
//	clear_interrupt(INT_TIMER0);
//	set_timer0(t0_cont);
//	tick++;
//}

#INT_EXT
void isr_ext() {
	clear_interrupt(INT_EXT_H2L);
	set_timer0(t0_cont);
	nrDisparos++;
	tempo = tick;
	tick = 0;
}

int main(void) {
	delay_ms(1000);
	printf("Inicio");
//	setup_timer_0(t0_config);
//	clear_interrupt(INT_TIMER0);
	clear_interrupt(INT_EXT);
	enable_interrupts(INT_EXT_L2H);
//	enable_interrupts(INT_TIMER0);
	enable_interrupts(GLOBAL);
	printf("Ok");
	while (TRUE) {
		if (!nrDisparos)
			printf("Nenhum disparo");
		else {
			printf("Tempo: %.2fs", (float) tempo / 100);
			printf("\nnr: %Lu", nrDisparos);
		}
		delay_ms(500);
	}
	return 0;
}
