/*
 * gerador.c
 *
 *  Created on: 05/04/2013
 *      Author: cuki
 */
#include <18F452.h>

#fuses H4,NOWDT,PROTECT,NOLVP
#use delay(crystal=10MHz, clock=40MHz)

short ctrl;

#INT_CCP1
void isr_ccp1(void) {
	clear_interrupt(INT_CCP1);
	set_timer1(0);
	if (ctrl++)
		setup_ccp1(CCP_COMPARE_CLR_ON_MATCH);
	else
		setup_ccp1(CCP_COMPARE_SET_ON_MATCH);
}

int main(void) {
	clear_interrupt(INT_CCP1);
	enable_interrupts(INT_CCP1);
	enable_interrupts(GLOBAL);
	setup_timer_1(T1_INTERNAL | T1_DIV_BY_2);
	CCP_1 = 50000;
	set_timer1(0);
	setup_ccp1(CCP_COMPARE_CLR_ON_MATCH);
	while (TRUE)
		;
	return 0;
}

