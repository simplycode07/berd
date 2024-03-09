class Berd {
	public:
		int width;
		int height;

		int x;
		int y;
		float vel_x;
		float vel_y;
		float gravity;

		uint16_t color;
		
		Berd(int x, int y, int width, int height, float gravity, uint16_t color) {
			this->x = x;
			this->y = y;
			
			this->width = width;
			this->height = height;

			this->color = color;
			this->gravity = gravity;
		}

		void update(int input, int screen_width, int screen_height, double dt) {
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
			if (y > (screen_height - height)) {
				y = screen_height - height;
				vel_y = 0;
			}

		}

		void push(int py, uint16_t background, TFT_eSPI *tft) {
			if (y > py) 
				tft->fillRect(x, py, width, (y - py), background);
			

			if (py > y) 
				tft->fillRect(x, (y + height), width, (py - y), background);
			

			tft -> fillRect(x, y, width, height, color);
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

			randomize();
		}

		void randomize(){
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

		bool check_collision(Berd *berdie, TFT_eSPI *tft) {
			return (x < berdie->x + berdie->width &&
					x + width > berdie->x &&
				(
					// check for collisoin with upper part
					(y < berdie->y + berdie->height &&
					y + height > berdie->y) ||

					//check for collisoin with lower part
					((height+gap) < berdie->y + berdie->height &&
					(screen_height) > berdie->y)
				)
			);
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
