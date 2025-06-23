#ifndef LOWKEYOLED_H
#define LOWKEYOLED_H

#include <stdint.h>
#include <stdbool.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR 0x3C

#ifdef __cplusplus
extern "C" {
#endif
void oled_init(void);
void oled_clear(void);
void oled_update(void);
void oled_draw_pixel(uint8_t x, uint8_t y, bool color);
void oled_send_command(uint8_t cmd);

extern uint8_t oled_buffer[OLED_WIDTH * OLED_HEIGHT / 8];

#ifdef __cplusplus
}
#endif

#endif