/*******************************************************************************
  函数名称: dht11_init()
  输入参数: 无
  输出参数: 无
  函数功能: dht11温度温度传感器初始化
*******************************************************************************/
void dht11_init(void)
{
        DHT = 1;                //A点
        DHT = 0;                //B点
        delay_ms(20);           //B-C
        DHT = 1;                //C点
        delay_us(50);           //40us <C-M点 <100us
        if (DHT == 0) {         //读到“0”，表示检测到响应信号
                while(!DHT);    //跳过ME
                while(DHT);     //跳过EF
                LED_01 = ON;     //LED_01亮
        } else {                //读到“1”，表示未检测到响应信号(模块损坏/未连接)
                LED_01 = OFF;   //LED_01灭
        }
}

/*******************************************************************************
  函数名称: dht11_read()
  输入参数: 无
  输出参数: 返回1个字节的dht11温度温度传感器数据
  函数功能: 从dht11温度温度传感器中读取一个字节数据
*******************************************************************************/
uint8_t dht11_read(void)
{
        uint8_t i; 
        uint8_t tmp;
        uint8_t read_byte = 0;
        for (i = 0; i < 8; i++) {
                while (!DHT);           //跳过50us
                delay_us(33);           //延时33us
                if (DHT == 1) {         //读到“1”
                        tmp = 1;
                        while(DHT);
                } else {                //读到“0”
                        tmp = 0;
                }
                read_byte <<= 1;
                read_byte |= tmp;
        }
        return read_byte;
}

/*******************************************************************************
  函数名称: dht11_data()
  输入参数: 无
  输出参数: 返回1个字节的dht11温度温度传感器数据
  函数功能: 从dht11温度温度传感器中读取一个字节数据
*******************************************************************************/
void dht11_data(void)
{
        delay_ms(20000);        //DHT11模块上电后需要延时2秒，跳过不稳定状态
        dth11_init();           //LED_1亮表示检测到模块响应信号
        byte1 = dht11_read();   //湿度的整数
        byte2 = dht11_read();   //湿度的小数
        byte3 = dht11_read();   //温度的整数
        byte4 = dht11_read();   //温度的小数
        byte5 = dht11_read();   //校验和
}
