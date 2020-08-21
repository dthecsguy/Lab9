/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include "ThreeLEDsSM.h"
#include "BlinkingLEDSM.h"
#include "timer.h"
#include "output.h"

static unsigned char outtie = 0, outtie2 = 0;
const unsigned char taskNum = 2;
const unsigned long periodBlinkLED = 100;
const unsigned long periodThreeLEDs = 100;
const unsigned long tasksPeriodGCD = 100;

typedef struct task {
	int state;
	unsigned long period;
	unsigned long elapsedTime;
	int (*TickFct)(int)
} task;

task tasks[2];

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;	PORTB = 0x00;

	unsigned char i = 0;
	tasks[i].state = ON;
	tasks[i].period = periodBlinkLED;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &BL_tick;
	++i;
	tasks[i].state = ZERO;
	tasks[i].period = periodThreeLEDs;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &TL_tick;

	TimerSet(tasksPeriodGCD);
	TimerOn();
	
    /* Insert your solution below */
    while (1) {
		Sleep();
    }
    return 1;
}
