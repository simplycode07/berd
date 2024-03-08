//#include "TFT_eSPI.h"


int input(int input_pin, TFT_eSPI * tft) {

	static int prev_state = 0;
	int state = digitalRead(input_pin);
	
	int button_pressed = 0;

	if ((prev_state == 0) && (state == 1)) {
		tft->setTextSize(2);
		tft->setTextColor(TFT_RED);
		tft->setCursor(0,0);
		tft->fillRect(0, 0, 240, 15, TFT_BLACK);
		tft->println("Button Pressed");
		button_pressed = 1;
	}

	if ((prev_state == 1) && (state == 0))  {
		tft->setTextSize(2);
		tft->setCursor(0,0);
		tft->setTextColor(TFT_GREEN);
		tft->fillRect(0, 0, 240, 15, TFT_BLACK);
		tft->println("Button Released");
		button_pressed = -1;
	}

	prev_state = state;
	return state;
}


void clear_rect(int px, int py, int nx, int ny, int h, int w, uint16_t background, TFT_eSPI *tft){
	if (nx > px) {
		tft->fillRect(px, py, (nx - px), h, background);
	}

	if (px > nx) {
		//tft->fillRect(px, (ny + h), w, abs(py-ny), background);
		tft->fillRect((nx + w), py, (px - nx), h, background);
	}

	if (ny > py) {
		tft->fillRect(px, py, w, (ny - py), background);
	}

	if (py > ny) {
		tft->fillRect(px, (ny + h), w, (py - ny), background);
	}
}
