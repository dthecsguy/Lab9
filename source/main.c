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

#include "timer.h"

static unsigned char outtie = 0, outtie2 = 0;
const unsigned char tasksNum = 2;
const unsigned long periodBlinkLED = 1000;
const unsigned long periodThreeLEDs = 300;
const unsigned long tasksPeriodGCD = 100;

typedef struct task {
	int state;
	unsigned long period;
	unsigned long elapsedTime;
	int (*TickFct)(int)
} task;

task tasks[2];

void set_out(){
	PORTB = outtie | outtie2;
}

void TimerISR() {
	TimerFlag = 1;
}

enum TL_State {ZERO, ONE, TWO};
enum BL_State {OFF, ON};

int TL_tick(int state){
	switch(state){ //transitions
		case ZERO:
			state = ONE;
			break;
			
		case ONE:
			state = TWO;
			break;
		
		case TWO:
			state = ZERO;
			break;
	}
	
	switch(state){ //actions
		case ZERO:
			outtie = 1;
			break;
			
		case ONE:
			outtie = 2;
			break;
		
		case TWO:
			outtie = 4;
			break;
	}
	
	return state;
}

int BL_tick(int state){
	switch(state){ //transitions
		case OFF:
			state = ON;
			break;
			
		case ON:
			state = OFF;
			break;
	}
	
	switch(state){ //actions
		case OFF:
			outtie2 = 0x00;
			break;
			
		case ON:
			outtie2 = 0x08;
			break;
	}
	
	return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;	PORTB = 0x00;

	unsigned char i = 0;
	tasks[i].state = OFF;
	tasks[i].period = periodBlinkLED;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &BL_tick;
	++i;
	tasks[i].state = TWO;
	tasks[i].period = periodThreeLEDs;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &TL_tick;

	TimerSet(tasksPeriodGCD);
	TimerOn();
	
    /* Insert your solution below */
    while (1) {
		for(unsigned char i = 0; i < tasksNum; ++i){
			if (tasks[i].elapsedTime >= tasks[i].period){
				tasks[i].state = tasks[i].TickFct(tasks[i].state);
				tasks[i].elapsedTime = 0;
			}
			
			tasks[i].elapsedTime += tasksPeriodGCD;
		}
		
		set_out();
		
		while(!TimerFlag){}
		TimerFlag = 0;
	}
    return 1;
}
