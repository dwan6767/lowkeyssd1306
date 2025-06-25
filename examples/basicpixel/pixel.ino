#include <lowkeyoled.h>
uint8_t h_offset =2;  // change the h_offset for your purpose
void setup() {
  oled_init();
  oled_clear();
  oled_draw_pixel(64, 32, true);
  oled_update();
}

void loop() {}

