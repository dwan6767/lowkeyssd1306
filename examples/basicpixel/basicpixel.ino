include <lowkeyoled.h>

void setup() {
  h_offset =2; // change the h_offset for your purpose
  oled_init();
  oled_clear();
  oled_draw_pixel(64, 32, true);
  oled_update();
}

void loop() {}

