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
Berd berdie = Berd(50, 30, 20, 20, 200, TFT_BLUE);

void setup() {
	pinMode(INPUT_PIN, INPUT);

	Serial.begin(9600);
	Serial.println("hello from esp8266");

	tft.begin();
	tft.fillScreen(TFT_BLACK);
	tft.setRotation(2);
}

void loop() {
	int button_pressed = input(INPUT_PIN, &tft);
	int prev_x = berdie.x;
	int prev_y = berdie.y;

	berdie.update(button_pressed, width, height, 0.05);
	clear_rect(prev_x, prev_y, berdie.x, berdie.y, berdie.w, berdie.h, TFT_BLACK, &tft);

	Serial.println( String(berdie.y) + ", " + String(berdie.vel_y) + ", " + String(berdie.gravity));
	
	berdie.push(&tft);
	delay(50);
}

