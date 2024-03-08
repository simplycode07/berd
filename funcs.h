//#include "TFT_eSPI.h"


int input(int input_pin, TFT_eSPI * tft) {

	static int prev_state = 0;
	int state = !digitalRead(input_pin);
	
	int button_pressed = 0;

	if ((prev_state == 0) && (state == 1)) {
		button_pressed = 1;
	}

	if ((prev_state == 1) && (state == 0))  {
		button_pressed = -1;
	}

	prev_state = state;
	return state;
}


