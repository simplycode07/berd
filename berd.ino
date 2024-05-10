// arduino-cli compile berd.ino -b esp8266:esp8266:nodemcuv2
// arduino-cli upload -b esp8266:esp8266:nodemcuv2 -p /dev/ttyUSB0

#include <TFT_eSPI.h>
#include <EEPROM.h>

#include "Free_Fonts.h"
#include "sprites.h"
#include "funcs.h"

int push_button = 10;
int width = 240;
int height = 320;

TFT_eSPI tft = TFT_eSPI();
Berd berdie = Berd(50, 30, 20, 20, 500, TFT_BLUE);
Obstacle obs = Obstacle(3, 10, 100, width, height, TFT_YELLOW);
int score = 0;
int amplitude = 0;
int button_pressed, obs_px, berd_py, prev_score;
int high_score;

void setup() {
	pinMode(push_button, INPUT_PULLUP);
	Serial.begin(9600);
	Serial.println("hello from esp8266");

	EEPROM.begin(12);

	tft.begin();
	tft.fillScreen(TFT_BLACK);
	tft.setRotation(2);

	tft.setTextColor(TFT_WHITE);
	tft.setTextSize(2);
	EEPROM.get(0, high_score);

}


void loop() {
	button_pressed = input(push_button);
	obs_px = obs.x;
	berd_py = berdie.y;

	prev_score = score;

	if (!obs.check_collision(&berdie, &tft)){
		score += obs.update();
		berdie.update(button_pressed, width, height, 0.02);
	} else {
		// reset game if collision is detected
		//obs = Obstacle(1, 10, 100, width, height, TFT_YELLOW);
		if (score > high_score) {
			EEPROM.put(0, score);
			EEPROM.commit();
			high_score = score;
		}

		// reset obstacle
		obs.randomize();
		obs.x = width;
		
		tft.fillScreen(TFT_BLACK);

		tft.setCursor(0,0);
		tft.println("Score: " + String(score));

		tft.setCursor(0,20);
		tft.println("High Score: " + String(high_score));

		tft.setTextColor(TFT_RED);
		tft.drawCentreString("Game Over", width/2, height/2 - 30, 2);

		tft.setTextColor(TFT_WHITE);
		tft.setTextSize(1);
		tft.drawCentreString("Press the button to play again", width/2, height/2 + 5, 1);

		// reset text size to 2
		tft.setTextSize(2);

		while (!input(push_button)) delay(10);

		score = 0;
		tft.fillScreen(TFT_BLACK);
	}

	if (prev_score != score) {
		tft.fillRect(0, 0, width, 15, TFT_BLACK);
	}

	obs.push(obs_px, TFT_BLACK, &tft);
	berdie.push(berd_py, TFT_BLACK, &tft);

	tft.setCursor(0,0);
	tft.println("Score: " + String(score));
	
	delay(20);
}

