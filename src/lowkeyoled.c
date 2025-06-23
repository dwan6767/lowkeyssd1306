#include "lowkeyoled.h"
#include <Wire.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <string.h>

#define H_OFFSET 4

static const uint8_t commands[] PROGMEM = {
  0xAE, 0xD5, 0x80, 0xA8, 0x3F,
  0xD3, 0x00, 0x40, 0x8D, 0x14,
  0x20, 0x00, 0xA1, 0xC8, 0xDA, 0x12,
  0x81, 0xCF, 0xD9, 0xF1, 0xDB, 0x40,
  0xA4, 0xA6, 0xAF
};

uint8_t oled_buffer[OLED_WIDTH * OLED_HEIGHT / 8];

void oled_send_command(uint8_t cmd) {
  Wire.beginTransmission(OLED_ADDR);
  Wire.write(0x00); // command mode
  Wire.write(cmd);
  Wire.endTransmission();
}

void oled_init(void) {
  Wire.begin();
  _delay_ms(50);
  for (uint8_t i = 0; i < sizeof(oled_init_cmds); i++) {
    uint8_t cmd = pgm_read_byte(&oled_init_cmds[i]);
    oled_send_command(cmd);
  }
  oled_clear();
  oled_update();
}

void oled_clear(void) {
  memset(oled_buffer, 0, sizeof(oled_buffer));
}

void oled_update(void) {
  for (uint8_t page = 0; page < 8; page++) {
    oled_send_command(0xB0 + page);
    oled_send_command(0x00);
    oled_send_command(0x10);

    for (uint8_t col = 0; col < OLED_WIDTH; col += 16) {
      Wire.beginTransmission(OLED_ADDR);
      Wire.write(0x40);  // data mode
      for (uint8_t i = 0; i < 16; i++) {
        Wire.write(oled_buffer[page * OLED_WIDTH + col + i]);
      }
      Wire.endTransmission();
    }
  }
}

void oled_draw_pixel(uint8_t x, uint8_t y, bool color) {
  if (x >= OLED_WIDTH || y >= OLED_HEIGHT) return;
  uint16_t index = x + (y / 8) * OLED_WIDTH + H_OFFSET;
  uint8_t bit = 1 << (y % 8);
  if (color)
    oled_buffer[index] |= bit;
  else
    oled_buffer[index] &= ~bit;
}

