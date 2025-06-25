/*
  lowkeyoled - Minimal SSD1306 I2C OLED driver for AVR/Arduino

  Written by Dwaipayan Shikari (https://github.com/dwan6767)
  License: MIT
*/

#include "lowkeyoled.h"
#include<Arduino.h>
#include <Wire.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <string.h>

uint8_t h_offset=4;  // came due some faulty hardware may not be in your case so change it by assinging it a different value

static const uint8_t oled_init_cmds[] PROGMEM = {
  0xAE, 0xD5, 0x80, 0xA8, 0x3F,
  0xD3, 0x00, 0x40, 0x8D, 0x14,
  0x20, 0x00, 0xA1, 0xC8, 0xDA, 0x12,
  0x81, 0xCF, 0xD9, 0xF1, 0xDB, 0x40,
  0xA4, 0xA6, 0xAF
};  //These are some commands which help to initialize the display driver , GDDRAM , Charge pump for the led driver ,charge pumps are capacitive circuit which gives boost in voltage to overcome led forward drop , also setting display clock , display on-off ,offsets,contrast control and many more settings more more information refer datasheet 

uint8_t oled_buffer[OLED_WIDTH * OLED_HEIGHT / 8];  // Main RAM consumer. there is another way which stores it in progmem , but those are really good for static display , for dynamic update RAM method is faster  

void oled_send_command(uint8_t cmd) {
  Wire.beginTransmission(OLED_ADDR);
  Wire.write(0x00); // this let's driver to read data as commands
  Wire.write(cmd);
  Wire.endTransmission();
}

void oled_init(void) {
  Wire.begin();
  _delay_ms(50); //small delay may not be necessary but useful 
  for (uint8_t i = 0; i < sizeof(oled_init_cmds); i++) {
    uint8_t cmd = pgm_read_byte(&oled_init_cmds[i]);  // using the avr flash read access
    oled_send_command(cmd);
  }
  oled_clear();
  oled_update();
}

void oled_clear(void) {
  memset(oled_buffer, 0, sizeof(oled_buffer)); //clear the information from the buffer to all zero 
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
//the ssd 1306 driver uses this kind of addressing modes for their data sending , they use 64/8 =8 pages , in this snippet they address pages by these fashion then after addressing , switched to data mode then it will be easy for us to send the data from the buffer , well i2c hardware limitation has 16bytes (2pages fair enough) thus the infromation goes to their RAM 
void oled_draw_pixel(uint8_t x, uint8_t y, bool color) {
  if (x >= OLED_WIDTH || y >= OLED_HEIGHT) return;
  uint16_t index = x + (y / 8) * OLED_WIDTH + h_offset;
  uint8_t bit = 1 << (y % 8);
  if (color)
    oled_buffer[index] |= bit;
  else
    oled_buffer[index] &= ~bit;
}
// only added a draw pixel function for minimality , only two possible states true means led on ,false means off , suppose you want to draw pixel at (10,20) then it is in page (20%8) page 2 the position will be (the ram fills in page by page fashion so it must have gone through 10+2*64 =138 pages first before reaching to your desired pixel , then a 1byte bitmasked buffer holds the information of that single page
 
