/*
 * detector.c
 *
 *  Created on: 05/04/2013
 *      Author: cuki
 */

#include <18F452.h>

#fuses H4,NOWDT,PROTECT,NOLVP
#use delay(crystal=10MHz, clock=40MHz)
#use rs232(xmit = PIN_C6, baud = 9600)

static long aux, tempo[256], cont, addr;
int *ptr;
static short ctrl;

#INT_CCP1
void irc_ccp1(void) {
	clear_interrupt(INT_CCP1);
	tempo[cont++] = CCP_1 - aux;
	aux = CCP_1;
	if (cont == 256) {
		ctrl = 1;
		setup_ccp1(CCP_OFF);
	}
}

int main(void) {
	clear_interrupt(INT_CCP1);
	enable_interrupts(INT_CCP1);
	enable_interrupts(GLOBAL);
	setup_ccp1(CCP_CAPTURE_RE);
	setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
	while (TRUE) {
		if (ctrl) {
			delay_ms(50);
			if (ctrl) {
				printf("\fEscrevendo");
				for (ptr = (int *) tempo; *ptr; ptr++) {
					write_eeprom(addr++, *ptr);
				}
				printf("Pronto");
				sleep();
			}
		}
		printf("\f%.2f\n%lu", (float) tempo[cont - 1] * 8 / 10000, cont);
		delay_ms(500);
	}
}
