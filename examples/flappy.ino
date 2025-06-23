#include "lowkeyoled.h"

#define horizontal_offset 4
#define OLED_ADDR 0x3C
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

uint16_t pre = 0;
uint16_t now;
uint8_t count = 0;


void setup() {
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), Isr, FALLING);

  oled_clear();
  oled_init();
  oled_clear();

  flappy(3, 120);
  building1(0);
  oled_update();
}

void loop() {
  static bool u = false;
  static uint8_t y = 4;

  now = millis();
  oled_clear();

  if (!u) building1(0);
  if (u)  building2(0);

  flappy(3 - 2 * count + y, y);
  oled_update();

  if (now - pre >= 5) {
    y++;
    if (y >= 120) {
      y = 4;
      count = 0;
      u = !u;
    }
    pre = now;
  }
}

void Isr() {
  count++;
  if (count >= 255) count = 0;
}

void block(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
  for (uint8_t i = x1; i < x2; i++) {
    for (uint8_t j = y1; j < y2; j++) {
      oled_draw_pixel(i, j, true);
    }
  }
}

void flappy(uint8_t i, uint8_t j) {
  oled_draw_pixel(1 + j, 31 + i, true);
  oled_draw_pixel(2 + j, 30 + i, true);
  oled_draw_pixel(3 + j, 29 + i, true);
  oled_draw_pixel(2 + j, 28 + i, true);
 oled_draw_pixel(1 + j, 27 + i, true);
}

void building1(uint8_t i) {
  block(15 + i, 0, 28 + i, 25);
  block(40 + i, 0, 60 + i, 35);
  block(72 + i, 0, 85 + i, 40);
  block(97 + i, 0, 115 + i, 23);
  block(15 + i, 45, 28 + i, 64);
  block(40 + i, 55, 60 + i, 64);
  block(72 + i, 60, 85 + i, 64);
  block(97 + i, 43, 115 + i, 64);
}

void building2(uint8_t i) {
  block(13 + i, 0, 26 + i, 22);
  block(42 + i, 0, 60 + i, 33);
  block(72 + i, 0, 85 + i, 11);
  block(97 + i, 0, 115 + i, 32);
  block(15 + i, 42, 28 + i, 64);
  block(40 + i, 53, 60 + i, 64);
  block(72 + i, 31, 85 + i, 64);
  block(97 + i, 52, 115 + i, 64);
}