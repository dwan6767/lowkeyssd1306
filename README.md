# lowkeyoled
A minimal Diy oled display(ssd1306)driver.

Uses main 1024 bytes of RAM as frame buffer; lower flash usage

Compatible with Avr Microcontroller and ssd1306 oled display
# functionality
For users it has oled_clear(), oled_update(); oled_draw_pixel() functions 

oled_clear() : clears the buffer

oled_update() : updates the screen with new value in the buffer

oled_draw_pixel() : draws a single pixel in a specific coordinate

* It has no text support ,everything the user has to do from scratch 

* While displaying static stuff it is good to store that in PROGMEM rather than RAM
#examples
   There is a Comprehensive example of a flappy-bird game in examples 
 Chill bro ..

## Usage

```c
#include <lowkeyoled.h>

void setup() {
  oled_init();
  oled_clear();
  oled_draw_pixel(64, 32, true);
  oled_update();
}

void loop() {}

