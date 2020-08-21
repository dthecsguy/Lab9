enum BL_State {OFF, ON};

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
			outtie2 = 0x08;
			break;
			
		case ON:
			outtie2 = 0x00;
			break;
	}
}
