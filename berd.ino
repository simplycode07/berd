// arduino-cli compile berd.ino -b esp8266:esp8266:nodemcuv2
// arduino-cli upload -b esp8266:esp8266:nodemcuv2 -p /dev/ttyUSB0

#include <TFT_eSPI.h>
#include "Free_Fonts.h"
#include "sprites.h"
#include "funcs.h"

int INPUT_PIN = 10;
int width = 240;
int height = 320;

TFT_eSPI tft = TFT_eSPI();
Berd berdie = Berd(50, 30, 20, 20, 300, TFT_BLUE);
Obstacle obs = Obstacle(1, 10, 100, width, height, TFT_YELLOW);
int score = 0;

int button_pressed, obs_px, berd_py, prev_score;

void setup() {
	pinMode(INPUT_PIN, INPUT_PULLUP);

	Serial.begin(9600);
	Serial.println("hello from esp8266");

	tft.begin();
	tft.fillScreen(TFT_BLACK);
	tft.setRotation(2);

	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.setTextSize(2);
}

void loop() {
	button_pressed = input(INPUT_PIN, &tft);
	obs_px = obs.x;
	berd_py = berdie.y;

	prev_score = score;
	score += obs.update();
	obs.push(obs_px, TFT_BLACK, &tft);

	berdie.update(button_pressed, width, height, 0.02);
	berdie.push(berd_py, TFT_BLACK, &tft);
	
	tft.setCursor(0,0);
	tft.println("Score: " + String(score));
	Serial.println(String(score));
	
	delay(20);
}

