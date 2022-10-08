#ifndef __I2C_H__
#define __I2C_H__
void i2c_is_busy(void);
void i2c_setup(void);
void i2c_send_byte(uint8_t addr, uint8_t sub_addr, uint8_t data);
void i2c_read(uint8_t addr, uint8_t sub_addr, uint8_t *pbuffer, uint8_t len);
void i2c_write(uint8_t addr, uint8_t sub_addr, uint8_t *pbuffer, uint8_t len);

#endif
