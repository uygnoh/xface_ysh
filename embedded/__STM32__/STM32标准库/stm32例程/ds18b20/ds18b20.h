#ifndef __DS18B20_H__
#define __DS18B20_H__

#define DS18B20_DQ         GPIO_Pin_0
#define DS18B20_PORT       GPIOF
#define DS18B20_PORT_CLK   RCC_APB2Periph_GPIO_F
#define DS18B20_HIGH()     do{GPIO_SetBits(DS18B20_GPIO,   DS18B20_DQ);}while(0)
#define DS18B20_LOW()      do{GPIO_ResetBits(DS18B20_GPIO, DS18B20_DQ);}while(0)
#define IN                 0
#define OUT                1

void ds18b20_conf(void);
void ds18b20_pin_mode(uint8_t opt);
uint8_t ds18b20_reset(void);
void ds18b20_write_byte(uint8_t cmd);
uint8_t ds18b20_read_byte(void);
float ds18b20_read_temperature(void);

#endif
