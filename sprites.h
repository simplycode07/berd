class Berd {
	public:
		double x;
		double y;
		int w;
		int h;
		double vel_x;
		double vel_y;
		double gravity;

		uint16_t color;
		
		Berd(int init_x, int init_y, int width, int height, float gravity_val, uint16_t berd_color) {
			x = init_x;
			y = init_y;
			
			w = width;
			h = height;

			color = berd_color;
			gravity = gravity_val;
		}

		void update(int input, int width, int height, double dt) {
			if (input == 1) {
				vel_y = -200;
				color = TFT_RED;
			}
			else {
				color = TFT_GREEN;
			}
			
			vel_y += gravity * dt;
			y += vel_y * dt;

			if (y < 0) y = 0;
			if (y > (height - h)) y = height - h;
		}

		void push(TFT_eSPI *tft) {
			tft -> fillRect((int)x, (int)y, w, h, color);
		}
};

