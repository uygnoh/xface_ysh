#include "ds18b20.h"

//定义(low_byte, high_byte)为ds18b20温度变量
uint8_t low_byte;
uint8_t high_byte;

/*******************************************************************************
  函数名称: ds18b20_init()
  输入参数: 无
  输出参数: ds18b20初始化状态（“0” 成功，否则失败）
  函数功能: 单总线，ds18b20初始化
*******************************************************************************/
uint8_t ds18b20_init(void)
{
        uint8_t flag = 0;
        DQ = 1;         //释放总线
        DQ = 0;         //A点：拉低总线
        delay_us(500);  //延时500us，(480us~960us)
        DQ = 1;         //B点：释放总线
        delay_us(68);   //BM点：延时68us，等待DQ回应
        if (DQ == 0) {  //判断“DQ线上的数据”
                flag = 0x00;
        } else {
                flag = 0x01;
        }
        delay_us(500);  //ME点：延时500us，(480us~960us)，
                        //也可以这么写while(!DQ); 等待ds18b20释放总线
        return flag;   //返回ds18b20的状态，“0”初始化成功，否则失败
}

/*******************************************************************************
  函数名称: ds18b20_write_dat()
  输入参数: cmd，要写入的命令字节
  输出参数: 无
  函数功能: 向ds18b20写入一个字节的 COMMANDS，读写都是从最低位开始
*******************************************************************************/
void ds18b20_write_cmd(uint8_t cmd)
{
        uint8_t tmp;
        for (tmp = 0x01; tmp != 0; tmp <<= 1) {
                DQ = 0;         //单片机拉低总线
                delay_us(2);    //延时2us
                if ((tmp & cmd) == 0) {
                        DQ = 0;
                } else {
                        DQ = 1;
                }
                delay_us(60);   //延时60us，等待DS18B20来采集数据
                DQ = 1;         //释放总线
        }
}

/*******************************************************************************
  函数名称: ds18b20_read_dat()
  输入参数: 无
  输出参数: 返回读出的一个字节的数据
  函数功能: 从ds18b20中读取一个字节的数据，读写都是从最低位开始
*******************************************************************************/
int8_t ds18b20_read_dat(void)
{
        uint8_t dat = 0;
        uint8_t tmp;
        for (tmp = 0x01; tmp != 0; tmp <<= 1) {
                DQ = 0;         //单片机拉低总线
                delay_us(2);    //延时2us
                DQ = 1;         //释放总线
                delay_us(2);    //延时2us, 等待DS18B20拉低或拉高
                if (DQ) {       //读取DQ总线上的位数据 
                        dat |= tmp;
                } else {
                        dat &= ~tmp;
                }
                delay_us(60);   //延时60us
        }
        return dat;
}

/*******************************************************************************
  函数名称: ds18b20_read_temperature()
  输入参数: 无
  输出参数: 返回“16位的温度数据”
  函数功能: 从scratchpad中读取温度数据并保存到全局变量中
  _________________________________________________________
  ds18b20单总线器件驱动程序编写流程(总线中只有一只ds18b20的情况下)
  _________________________________________________________
  第一步: 初始化(对总线上的器件进行初始化)
  第二步: ROM命令(指令寻找和匹配，指定待操作器件)
  第三步: 功能命令(进行具体操作或传输数据)
*******************************************************************************/
uint16_t ds18b20_read_temperature(void)
{
        uint8_t low_byte, high_byte;
        uint16_t temperature;
        if (ds18b20_init()) {                   //判断ds18b20是否初始化成功
                ds18b20_write_cmd(0xCC);        //skip rom
                ds18b20_write_cmd(0x44);        //启动温度转换
        }
        delay_ms(750);                          //延时750毫秒
        if (ds18b20_init()) {                   //判断ds18b20是否初始化成功
                ds18b20_write_cmd(0xCC);        //skip rom
                ds18b20_write_cmd(0xBE);        //read scratchpad
                low_byte   = ds18b20_read_dat();//read byte0
                high_byte  = ds18b20_read_dat();//read byte1
                temperature= ((uint16_t)high_byte << 8) + low_byet;
        }
        return(temperature);
}



//uint8_t ROM[8];
//从ds18b2020中读出64位ROM码
//*prom读出64位ROM码存放的地方
//64位ROM码: 低位在前，高位在后读出
void ds18b20_read_rom_code(uint8_t *prom)
{
        uint8_t falg = 0;
        uint8_t i    = 0;
        if (ds18b20_init()) {
                ds18b20_write_cmd(READ_ROM);    //读取ROM指令
                for (i = 0; i < 8; i++) {       //读取64位ROM码
                        *prom++ = ds18b20_read_dat();
                }
        }
}
