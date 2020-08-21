enum TL_State {ZERO, ONE, TWO};

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
	
	swtich(state){ //actions
		case ZERO:
			outtie = 0;
			break;
			
		case ONE:
			outtie = 1;
			break;
		
		case TWO:
			outtie = 2;
			break;
	}
	
	return state;
}