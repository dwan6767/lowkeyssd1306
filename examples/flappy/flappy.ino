/*
  lowkeyoled - Minimal SSD1306 I2C OLED driver for AVR/Arduino

  Written by Dwaipayan Shikari (https://github.com/dwan6767)
  License: MIT
*/
// hardware needed avr microcontroller , ssd1306 oled screen , push button , wires ,debouncing capacitor(100nf) etc
#include "lowkeyoled.h"

#define horizontal_offset 4
#define OLED_ADDR 0x3C
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

uint16_t pre = 0;   // i bet no one can play more than one minute all these to save some important RAM bro!you can change it it 32 bit if you are pro
uint16_t now;
uint8_t count = 0;


void setup() {
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), Isr, FALLING);
//using an interrupt for key detection
  oled_clear();
  oled_init();
  oled_clear();

  flappy(3, 120);  //our chill guy
  building1(0);
  oled_update();
}
// in these code you may be see random number numbers actually i didn't use any maths just some trail and error values 
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
} /// a simple block from the draw pixel function 

void flappy(uint8_t i, uint8_t j) {
  oled_draw_pixel(1 + j, 31 + i, true);
  oled_draw_pixel(2 + j, 30 + i, true);
  oled_draw_pixel(3 + j, 29 + i, true);
  oled_draw_pixel(2 + j, 28 + i, true);
 oled_draw_pixel(1 + j, 27 + i, true);
}
// flappy movable low key bird
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
//only using two buildings for the flappy universe switch intermediately
//most unproductive way to write games change and build on your way
