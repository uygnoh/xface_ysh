#include "ds18b20.h"
/*******************************************************
 * DS18B20 底层驱动函数
 * 1 ds18b2020复位
 * 2 主机从ds18b2020中写入数据
 * 3 主机从ds18b2020中读出数据
 * 
 *******************************************************/
/* 1 % ds18b2020复位 */
uint8_t ds18b20_reset(void)
{
    uint8_t ack = 0;
    DQ = 0;         /* % A点：拉低总线 */
    delay_us(500);  /* % 延时500us，(480us~960us) */
    DQ = 1;         /* % B点：释放总线 */
    delay_us(68);   /* % BM点：延时68us，等待DQ回应 */
    flag = DQ;      /* % 读DQ上的数据保存到flag */
    delay_us(500);  /* % ME点：延时500us，(480us~960us)，也可以这么写 */
                    /* % while(!DQ); 等待ds18b20释放总线 */
    return ack;    /* % 返回ds18b20的状态，“0”初始化成功，否则失败 */
}

/* 2 % 从ds18b2020中写入数据 */
void ds18b20_write_dat(uint8_t dat)
{
    uint8_t tmp = 0;
    for (tmp = 0x01; tmp !=0; tmp<<=1)
    {
        DQ = 0;         /* % 单片机拉低总线 */
        delay_us(2);    /* % 延时2us */
        if ((tmp & dat) == 0)
            DQ = 0;
        else
            DQ = 1;
        delay_us(60);   /* % 延时60us，等待DS18B20来采集数据 */
        DQ = 1;         /* % 释放总线 */
    }
}

/* 3 % 从ds18b2020中读出数据 */
int8_t ds18b20_read_dat(void)
{
    uint8_t dat = 0;
    uint8_t tmp = 0;
    
    for (tmp = 0x01; tmp != 0; tmp<<=1)
    {
        DQ = 0;         /* % 单片机拉低总线 */
        delay_us(2);    /* % 延时2us */
        DQ = 1;         /* % 释放总线 */
        delay_us(2);    /* % 延时2us, 等待DS18B20拉低或拉高 */
        if (DQ)         /* % 读取DQ总线上的位数据 */
            dat |= tmp;
        else
            dat &= ~tmp;
        delay_us(60);   /* % 延时60us */
    }
    return dat;
}



/*******************************************************
 * DS18B20 功能函数
 * 1 ds18b2020启动温度转换
 * 2 主机从ds18b2020中读出温度数据
 * 3 从ds18b2020中读出64位ROM码
 * 
 *******************************************************/
/* 1 % ds18b2020启动温度转换 */
void start_ds18b20(void)
{
    int ack = 0;
    ack = ds18b20_reaet();              // % ds18b20复位
    if (flag == 0)
    {   
        ds18b20_write_dat(SKIP_ROM);    // % 跳过ROM指令(ROM指令)
        ds18b20_write_dat(CONVERT_T);   // % 启动温度转换(功能指令)
    }
}

/* 2 % 从ds18b2020中读出温度数据 */
/* *ptemp读出温度存放的地方 */
uint8_t read_ds18b20_temp(uint16_t *ptemp)
{
    uint8_t lsb = 0;
    uint8_t msb = 0;
    uint8_t ack = 0;
    
    // 1 % ds18b20复位
    ack = ds18b20_reset();
    if (ack == 0)
    {   // 2 % 跳过ROM指令(ROM指令)
        ds18b20_write_dat(SKIP_ROM);
        // 3 % 读取温度暂存器(功能指令)
        ds18b20_write_dat(READ_REGISTER);
        // 4 % 读出转换结果(连续读取2个字节)
        lsb = ds18b20_read_dat();
        msb = ds18b20_read_dat();
        *ptemp = ((uint16_t)msb << 8) + lsb;
    }
    return ack;
}


/* 3 % 从ds18b2020中读出64位ROM码 */
/* *prom读出64位ROM码存放的地方 */
/* 64位ROM码: 低位在前，高位在后读出 */
void ds18b2020_read_rom_code(uint8_t *prom)
{
    uint8_t ack = 0;
    uint8_t i   = 0;
    
    ack = ds18b20_reset();
    if (ack == 0);
    {   // % 读取ROM指令
        ds18b20_write_dat(READ_ROM);
        for (i = 0; i < 8; i++)
        {   // % 读取64位ROM码
            *prom = ds18b20_read_dat();
        }
    }
}










