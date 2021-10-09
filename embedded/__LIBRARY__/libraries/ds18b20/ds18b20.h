#ifndef __DS18B20_H__
#define __DS18B20_H__

#define DQ                      P1_2    //定义温度传感器信号线     

//      DS18B20_ROM_COMMANDS 宏定义
//_________________________________________________________
#define SEARCH_ROM              0xF0    //搜索ROM指令
#define READ_ROM                0x33    //读取ROM指令
#define MATH_ROM                0x55    //匹配ROM指令
#define SKIP_ROM                0xCC    //跳过ROM指令
#define ALARM_SEARCH            0xEC    //报警搜索指令

//      DS18B20_FUNCTION_COMMANDS_宏定义
//_________________________________________________________
#define CONVERT_TEMPERATURE     0x44    //温度转换指令
#define WRITE_REGISTER          0x4E    //写暂存器指令
#define READ_REGISTER           0xBE    //读暂存器指令
#define COPY_REGISTER           0x48    //拷贝暂存器指令
#define RECALL_EEPROM           0xB8    //召回EEPROM指令
#define READ_POWER_SUPPLY       0xB4    //读取电源模式指令

//      DS18B20_函数声明
//_________________________________________________________
uint8_t ds18b20_init(void);             //ds18b20初始化
void ds18b20_write_cmd(uint8_t cmd);    //向ds18b20中写入一个字节的命令
int8_t ds18b20_read_dat(void);          //从ds18b20中读取一个字节的数据
uint16_t ds18b20_read_temperature(void);//从ds18b20中读取温度数据

#endif
