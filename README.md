# lowkeyoled

Minimal SSD1306 OLED driver written in C.  
No classes. No dependencies. Just pixels.

## Features

- Works with 128x64 SSD1306 OLED over I2C
- Lightweight, Arduino-compatible C library
- Uses `Wire.h` for I2C
- Just `oled_init()`, `oled_clear()`, `oled_draw_pixel()`, `oled_update()`

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

