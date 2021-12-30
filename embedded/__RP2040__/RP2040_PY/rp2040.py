/*******************************************************************************
        => RP2040
*******************************************************************************/
BOOTSEL //启动选择按钮
        按键未按下时，MCU复位或上电，则从Flash启动
        如果按键按下，MCU复位或上电，则进入UF2下载模式
        
        
        
/*******************************************************************************
        => RP2040-GPIO
*******************************************************************************/
|_________________________________________________________|
|  machine.Pin(id, mode=None, pull=None, value)           |
|_________________________________________________________|
Pin     //对象构造函数
id      //GPIO编号，数值为（0~29）
mode    //模式，可选( None, Pin.IN(0), Pin.OUT(1), Pin.OPEN_DRAIN(2) )
pull    //使用内部上拉或下拉，仅在输入模式下有效( None, Pin.PULL_UP(1), Pin.PULL_DOWN(2) )
value   //0(off), 1(on)



//RP2040-GPIO程序
___________________________________________________________
from machine import Pin
import utime
#//初始化GPIO15，配置为输入模式，使用上拉电阻
#//作为外部信号输入引脚，如果为低电平，打开led
button_num = 15
button = Pin(button_num, Pin.IN, Pin.PULL_UP)

#//配置GPIO16， 输出模式
external_led_num = 16;
external_led = Pin(external_led_num, Pin.OUT)

#//配置GPIO25，输出模式
led_num = 25
led = Pin(led_num, Pin.OUT)

print("button gpio={0}".format(button_num))

while True:
	#//打开led
	led.off()
	#//读取“button”的值， 延时10ms，使用软件消抖
	if (button.value() == 0):
		utime.sleep(0.01)
		if (button.value() == 0):
			#//Toggle led
			external_led.toggle()
			#//led turn on
			led.on()
			print("button is pressed")
			while (button.value() == 0):
				utime.sleep(0.01)
				
				
				
/*******************************************************************************
        => RP2040-PWM
*******************************************************************************/
 //其作用是指定GPIO重新初始化并设置为PWM输出
|_________________________________________________________|
|  machine.PWM(pin)                                       |
|_________________________________________________________|
  pin   
  
  
PWM.freq([value])       //为PWM频率设置函数
                        //根据参数“value”自动计算分频器参数和TOP寄存器参数
                        //“TOP寄存器”决定了计数器最大计数值
PWM.duty_u16([value])   //用于设置占空比
                        //通过参数“value”自动计算出相对应的数值并赋予给“CC寄存器”

PWM.duty_ns([value])    //设置一个周期输出高电平的时间
                        //其参数“value”为高电平时间，单位为ns
                        
                        
                        
//RP2040-PWM脉冲宽度调制
___________________________________________________________
from machine import Pin, PWM
import utime

#//配置GPIO25为PWM模式
LED = PWM(Pin(25))

#//配置PWM频率为 1000Hz
LED.freq(1000)

LDE_duty = 0
LED_drection = 1
while True:
	LED_duty += LED_direction
	if LED_duty >= 100:
		LED_duty = 100
		LED_direction = -1
	elif LED_duty <= 0:
		LED_duty = 0
		LED_direction = 1
	LED.duty_u16(int(LED_duty * 655.36))
	if LED_duty % 5 == 0:
		print(LED_duty)
	utime.sleep(0.01)
	
	
	
/*******************************************************************************
        => RP2040-ADC
*******************************************************************************/
1 逐次逼近型ADC
  //根据基准电压生成一系列电压，与输入电压逐个比较，获取最接近输入电压对应的编码值。
  //速度中等，精度较高，较为常见
2 并联比较型ADC
  //根据基准电压生成一系列电压，同时进行比较，获取最接近输入电压对应的编码值
  //速度较快，精度低，适用于高速，低分辨率的场合
3 RP2040 ADC
  //ADC类型：    逐次逼近型ADC
  //转换速率：    500KS/s（使用内部独立48MHz时钟）
  //分辨率：      12Bit
  //ADC输入通道： 通道0~3为GPIO通道（GPIO26~29）
  //            通道4为内部温度传感器通道
  //Pico上GPIO29并未引出至引脚，而是用于检测“VSYS”电压



|_________________________________________________________|
|  machine.ADC(id)                                        |
|_________________________________________________________|
  id    //可以为GPIO对象， 也可以为ADC通道
        //使用“Pin对象”时，指定的GPIO需要支持ADC功能，即GPIO26~29
        //使用“ADC通道”时，通道“0~3”对应“GPIO26~29”
        //“通道4”对应内部温度传感器

|  read_u16()   //函数的作用，读取对应通道ADC，并返回读取到的数值
|               //注意！ 该函数返回数值并不是直接返回ADC读取的数值
|               //而是经过处理的数值，数值范围为“0~65535”， ADC电压公式为：
|_______________________________________________________________________|
|          ADC_AVDD * ReadData            3.3 * ReadData                |
|  Vin = _______________________    =   ____________________V           |
|               分辨率                        65535                      |
|_______________________________________________________________________|
|
|
|  通道“4”     //“通道4”对应内部温度传感器， 其计算公式为
|_______________________________________________________________________|               
|                        ADC_voltage - 0.706                            |
|  Temperature = 27 - __________________________                        |
|                            0.001721                                   |
|_______________________________________________________________________|



#//这个程序实现每秒读取一次GPIO26上的电压，并使用片内温度传感器采集温度
_________________________________________________________________________                            
from machine import Pin, ADC
import utime
#//1->通过指定GPIO26初始化ADC通道“0”
#//选择RP2040—ADC通道“0”，使用此通道采集外部输入电压
ADC0 = ADC(Pin(26))

#//2->指定初始化ADC通道“4”，其对应片内温度传感器
#//选择RP2040—ADC通道“4”，此通道为内部温度传感器
sensor_temp = ADC(4)

while True:
	#//使用通道0，测量外部电压
	read_voltage = ADC0.read_u16() * 3.3 / 65535
	#//使用通道4，为内部温度传感器
	read_temp_voltage = sensor_temp.read_u16() * 3.3 / 65535
	temperature = 27 - (read_temp_voltage - 0.706) / 0.001721
	print("ADC0_voltage = {0:.2f}V \t\t temperature = \
	        {1:.2f}C \r\n".format(read_voltage, temperature))
	utime.sleep_ms(1000)
	
	
	
/*******************************************************************************
        => RP2040-UART
*******************************************************************************/
|_________________________________________________________|
|                                                         |
|_________________________________________________________|
1       //收发独立FIFO
2       //可编程波特率生成器
3       //标准异步通信位，在发送时添加，在接收时删除
4       //换行符检测
5       //可编程串行接口（5，6，7，8）数据位
6       //1位或2位停止位
7       //可编程的硬件流量控制（RTS， CTS）

machine.UART(
        id, baudrate=115200, bits=8, parity=None, stop=1, tx=None, rx=None)
_____________________________________________________________________________
  id              //使用UART通道，“0”或“1”
  baudrate        //使用波特率
  bits            //数据位长度
  parity          //奇偶校验位
  stop            //停止位长度
  tx              //TXD引脚，应为Pin对象
  rx              //RXD引脚，应为Pin对象
_____________________________________________________________________________

from machine import Pin, ADC
import utime

uart = UART(0, baudrate=115200, tx=Pin(0), rx=Pin(1))
led = Pin(25, Pin.OUT)

uart.write("Waveshare Uart Test\r\n")
uart.write("Plase enter charcter 0 or 1 to switch the LED on and off \r\n")

while True:
	if uart.any() == True:
		buf = uart.read(1)
		if buf == b'1':
			led.on()
			print("LED ON")
			uart.write("LED ON\r\n")
		elif buf == b'0':
			led.off()
			print("LED OFF")
			uart.write("LED OFF\r\n")
		else:
			print("Please enter character 0 or 1 switch the LED on an off")
			uart.write("Please enter character 0 or 1 switch the LED on and off\r\n")
	utime.sleep_ms(1)
	
	
	
/*******************************************************************************
        => RP2040-IIC
*******************************************************************************/
//RP2040-I2C主要参数
1 支持主模式和从模式(默认主模式)
2 支持标准模式，快速模式， 和快速模式+
3 默认从机地址为“0x55”
4 主模式下支持“10bit地址”
5 “16”位接收缓冲区
6 “16”位发送缓冲区
7 可以使用DMA驱动
8 可生成中断




 //I2C对象构造函数，作用为初始化对应的I2C通道和引脚
|_________________________________________________________|
|  machine.I2C(id, scl, sda, freq=400000)                 |
|_________________________________________________________|
  id    //参数id为使用I2C通道，可以为0或1
  scl   //使用I2C引脚，应为Pin对象
  sda   //使用I2C引脚，应为Pin对象
  freq  //freq，I2C频率，默认为400KHz


 //扫描从设备函数，将返回含有所有I2C总线上挂载从设备7位地址的列表
|_________________________________________________________|
|  I2C.scan()                                             |
|_________________________________________________________|


 //readfrom函数其作用为通过I2C总线从设备读取数据并返回字节串
|_________________________________________________________|
|  I2C.readfrom(addr, bytes, stop=Ture)                   |
|_________________________________________________________|
  addr    //从设备地址
  nbytes  //读取字符串长度
  stop    //是否在接收完成数据后发送结束信号




/*******************************************************************************
        => RP2040-SPI
*******************************************************************************/
MOSI    //主机发送，从机接收
MISO    //主机接收，从机发送
SCLK    //时钟信号
CS      //Chip select, 用来选择从设备

CPHA    //Clock Phase, 时钟相位
_______________________________
选择捕获数据的时钟边沿，如果时钟相位为低（CPHA=0），则数据在第一个时钟边沿捕获
反之则数据在第二个时钟边沿捕获

CPOL  //Clock polarity, 时钟极性
_______________________________
空闲时时钟信号电平，如果时钟极性为低（CPOL=0），则时钟信号引脚在空闲时输出低电平
反之时钟信号引脚在空闲时输出高电平


//RP2040-SPI参数
___________________________________________________________
1 支持主从模式
  支持摩托罗拉SPI接口
  支持德州仪器同步串口(SSI)
  支持美国国家半导体Microwire接口
2 8单位深度收发先进先出存储器(8 deep TX and TX FIFOs）
3 中断生成器可服务于先进先出存储器或者错误标识
4 可以使用DMA驱动
5 可编程时钟
6 可编程数据大小(4~16bit)



 //SPI对象构造函数
|_________________________________________________________|
|  machine.SPI(                                           |
|       id, baudrate=1000000,                             |
|       polarity=0, phase=0,                              |
|       bits=8, firstbit=SPI.MSB,                         |
|       sck=None, mosi=None, miso=None                    |
|  )                                                      |
|_________________________________________________________|
  id            //参数id为spi通道，可以为0或1
  baudrate      //spi通讯速率，也就是SCK引脚上的频率
  polarity      //时钟极性，若为0则总线空闲时SCK输出低电平，反之则输出高电平
  phase         //时钟相位，若为0则在第一个时钟边沿捕获数据，反之则在第二个时钟边没捕获数据
  bits          //每次传输数据的位数
  firsbit       //先传输高位，还是先传输低位
  sck           //SPI引脚，应为Pin对象
  mosi          //SPI引脚，应为Pin对象
  miso          //SPI引脚，应为Pin对象
  
  
  //read()函数，用于读取从设备并返回
|_________________________________________________________|
|  SPI.read(nbytes, write=0x00)                           |
|_________________________________________________________|
  nbytes        //参数“nbytes”为读取字节数
  write         //write读取数据时，“MOSI”输出数据


 //readinto()函数，用于读取从设备数据并存入指定字符数组中
|_________________________________________________________|
|  SPI.readinto(buf, write=0x00)                          |
|_________________________________________________________|
  buf           //字符数组，用于存放接收数据
  write         //write读取数据时，“MOSI”输出数据


 //read.write()函数，用于向从设备写入数据
|_________________________________________________________|
|  SPI.write(buf)                                         |
|_________________________________________________________|
  buf           //buf字符数组，用于存放传输数据


 //write_readinto()函数，用于同时发送和接收数据
|_________________________________________________________|
|  SPI.write_readinto(write_buf, read_buf)                |
|_________________________________________________________|
  write_buf     //字符数组，用于存放传输数据
  read_buf      //字符数组，用于存放接收数据
  //这里传输和接收的字符数组的长度要求一致
