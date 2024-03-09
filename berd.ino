// arduino-cli compile berd.ino -b esp8266:esp8266:nodemcuv2
// arduino-cli upload -b esp8266:esp8266:nodemcuv2 -p /dev/ttyUSB0

#include <TFT_eSPI.h>
#include "Free_Fonts.h"
#include "sprites.h"
#include "funcs.h"

int INPUT_PIN = 10;
int buzzer = D0;
int width = 240;
int height = 320;

TFT_eSPI tft = TFT_eSPI();
Berd berdie = Berd(50, 30, 20, 20, 300, TFT_BLUE);
Obstacle obs = Obstacle(2, 10, 100, width, height, TFT_YELLOW);
int score = 0;
int amplitude = 0;
int button_pressed, obs_px, berd_py, prev_score;

void setup() {
	pinMode(INPUT_PIN, INPUT_PULLUP);

	Serial.begin(9600);
	Serial.println("hello from esp8266");

	tft.begin();
	tft.fillScreen(TFT_BLACK);
	tft.setRotation(2);

	tft.setTextColor(TFT_WHITE);
	tft.setTextSize(2);
}

void loop() {

	button_pressed = input(INPUT_PIN);
	obs_px = obs.x;
	berd_py = berdie.y;

	prev_score = score;

	if (!obs.check_collision(&berdie, &tft)){
		score += obs.update();
		berdie.update(button_pressed, width, height, 0.02);
	}
	else {
		score = 0;
		//obs = Obstacle(1, 10, 100, width, height, TFT_YELLOW);
		obs.randomize();
		obs.x = width;
		tft.fillScreen(TFT_BLACK);

		tft.setTextColor(TFT_RED);
		tft.drawCentreString("Game Over", width/2, height/2 - 20, 1);

		tft.setTextColor(TFT_WHITE);
		tft.setTextSize(1);
		tft.drawCentreString("Press the button to play again", width/2, height/2, 1);
		tft.setTextSize(2);

		while (!input(INPUT_PIN)) delay(10);

		tft.fillScreen(TFT_BLACK);
	}
	if (prev_score != score) tft.fillRect(0, 0, width, 15, TFT_BLACK);
	obs.push(obs_px, TFT_BLACK, &tft);
	berdie.push(berd_py, TFT_BLACK, &tft);

	tft.setCursor(0,0);
	tft.println("Score: " + String(score));
	
	delay(20);
}

