int input(int input_pin) {

	static int prev_state = 0;
	int state = !digitalRead(input_pin);
	
	// plan to use this button_pressed later
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


