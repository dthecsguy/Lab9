enum BL_State {OFF, ON};

int BL_tick(int state){
	swtich(state){ //transitions
		case OFF:
			state = ON;
			break;
			
		case ON:
			state = OFF;
			break;
	}
	
	swtich(state){ //actions
		case OFF:
			outtie2 = 0x08;
			break;
			
		case ON:
			outtie2 = 0x00;
			break;
	}
}