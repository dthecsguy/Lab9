static unsigned char outtie = 0, outtie2 = 0;

void set_out(){
	PORTB = outtie | outtie2;
}