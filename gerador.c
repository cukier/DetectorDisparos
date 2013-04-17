/*
 * gerador.c
 *
 *  Created on: 05/04/2013
 *      Author: cuki
 */
#include <18F452.h>

#fuses H4,NOWDT,PROTECT,NOLVP
#use delay(crystal=10MHz, clock=40MHz)

static short ctrl, ctrl2;

#INT_CCP1
void isr_ccp1(void) {
	clear_interrupt(INT_CCP1);
	set_timer1(0);
	if (ctrl++)
		setup_ccp1(CCP_COMPARE_CLR_ON_MATCH);
	else
		setup_ccp1(CCP_COMPARE_SET_ON_MATCH);
}

#INT_CCP2
void isr_ccp2(void) {
	clear_interrupt(INT_CCP2);
	set_timer3(0);
	if (ctrl2++)
		setup_ccp2(CCP_COMPARE_CLR_ON_MATCH);
	else
		setup_ccp2(CCP_COMPARE_SET_ON_MATCH);
}

int main(void) {
	clear_interrupt(INT_CCP1);
	enable_interrupts(INT_CCP1);
	clear_interrupt(INT_CCP2);
	enable_interrupts(INT_CCP2);
	enable_interrupts(GLOBAL);
	setup_timer_3(T3_INTERNAL | T3_DIV_BY_8 | T3_CCP2);
	setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
	CCP_2 = 10000;
	CCP_1 = 20000;
	set_timer1(0);
	set_timer3(0);
	setup_ccp1(CCP_COMPARE_CLR_ON_MATCH);
	setup_ccp2(CCP_COMPARE_CLR_ON_MATCH);
	while (TRUE)
		;
	return 0;
}

