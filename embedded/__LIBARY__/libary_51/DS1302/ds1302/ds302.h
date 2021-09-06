#ifndef __DS1302_H__
#define __DS1302_H__

#define BURST_WRITE     0xBE    /* % Burst模式写 */
#define BURST_READ      0xBF    /* % Burst模式读 */
#define BURST_RAM_WRITE 0xFE    /* % BurstRAM模式写 */
#define BURST_RAM_READ  0xFF    /* % BurstRAM模式读 */

/* % DS1302__IO__定义 */
sbit DS1302_IO          = P3^3  /* % 串行数据输入输出端口 */
sbit SCLK               = P3^4  /* % 串行时钟 */
sbit CE                 = P3^5  /* % 使能端口 */


/* % DS1302读寄存器指令地址 */
uchar code read_rtc_cmd[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
/* % DS1302写寄存器指令地址 */
uchar code write_rtc_cmd[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
/* % DS1302时钟初始化: 2013年1月1日星期二12点00分00秒*/
/* % 存储顺序是: [秒-分-时-日-月-周-年-None], 存储格式是用BCD码 */
/* % 最后一个字节为：0x00 */
uchar ds1302_time[8] = {0, 0, 0x12, 0x01, 0x01, 0x02, 0x13, 0x00};


void ds1302_write_byte(uint8_t dat);
uint8_t ds1302_read_byte(void);

void ds1302_write_register(uint8_t cmd, uint8_t dat);
uint8_t ds1302_read_register(uint8_t cmd);
void ds1302_init(void);
void ds1302_read_time(void);

void ds1302_write_ram(uint8_t addr, uint8_t dat);
uint8_t ds1302_read_ram(uint8_t addr);

void ds1302_burst_write(void);
void ds1302_burst_read(uint8_t *pbuf);
void ds1302_burst_init(void);

void ds1302_burst_write_ram(uint8_t *pbuf, uint8_t len);
void ds1302_burst_read_ram(uint8_t *pbuf, uint8_t len);
#endif



