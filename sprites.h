class Berd {
	public:
		int w;
		int h;

		int x;
		int y;
		float vel_x;
		float vel_y;
		float gravity;

		uint16_t color;
		
		Berd(int x, int y, int width, int height, float gravity, uint16_t color) {
			this->x = x;
			this->y = y;
			
			this->w = width;
			this->h = height;

			this->color = color;
			this->gravity = gravity;
		}

		void update(int input, int width, int height, double dt) {
			if (input == 1) {
				vel_y = -150;
				color = TFT_RED;
			}
			else {
				color = TFT_GREEN;
			}
			
			vel_y += gravity * dt;
			y += vel_y * dt;

			if (y < 0) {
				y = 0;
				vel_y = 0;
			}
			if (y > (height - h)) {
				y = height - h;
				vel_y = 0;
			}

		}

		void push(int py, uint16_t background, TFT_eSPI *tft) {
			if (y > py) 
				tft->fillRect(x, py, w, (y - py), background);
			

			if (py > y) 
				tft->fillRect(x, (y + h), w, (py - y), background);
			

			tft -> fillRect(x, y, w, h, color);
		}
};


class Obstacle {
	public:
		int x, y=0;
		int speed;

		int width;
		int gap;
		
		int screen_width;
		int screen_height;

		int height ;

		uint16_t color;

		Obstacle(int speed, int width, int gap, int screen_width, int screen_height, uint16_t color) {
			this->speed = speed;
			this->width = width;
			this->gap = gap;

			this->screen_width = screen_width;
			this->screen_height = screen_height;
			
			this->x = screen_width;

			this->color = color;

			this->height = random(screen_height - gap);
		}


		int update(){
			if ((x + width) > 0) {
				x -= speed;
			} else {
				x = screen_width;
				height = random(screen_height - gap);
				return 1;
			}

			return 0;
		}

		void push(int px, uint16_t background, TFT_eSPI *tft) {
			//if (x > px) 
				//tft->fillRect(px, y, (x - px), height, background);
			if (px > x) {
				tft->fillRect((x + width), 0, (px - x), height, background);
				tft->fillRect((x + width), (height + gap), (px - x), (screen_height - (height + gap)), background);

			} 
			
			tft->fillRect(x, 0, width, height, color);
			tft->fillRect(x, (height + gap), width, (screen_height - (height + gap)), color);
		}


};
