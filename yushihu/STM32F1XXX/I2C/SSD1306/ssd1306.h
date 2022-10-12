#ifndef __SSD1306_H__
#define __SSD1306_H__

#define LONG_TIMEOUT            1000    // 超时时间

void i2c_setup(void);
void ssd1306_setup(void);
void timeout_user_callback(void);
void ssd1306_write_command(uint8_t command);
void ssd1306_write_data(uint8_t data);
void ssd1306_clear(void);
void oled_put_char_8x16(uint8_t x, uint8_t y, char character);
void oled_put_string_8x16(uint8_t x, uint8_t y, const char *characters);

#endif
