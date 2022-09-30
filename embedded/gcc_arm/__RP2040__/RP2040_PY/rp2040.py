/*******************************************************************************
        => RP2040
*******************************************************************************/
        BOOTSEL         // 启动选择按钮
                        // 按键未按下时，MCU复位或上电，则从Flash启动
                        // 如果按键按下，MCU复位或上电，则进入UF2下载模式
        
        
        
/*******************************************************************************
        => RP2040-GPIO
*******************************************************************************/

        machine.Pin(id, mode=None, pull=None, value)
//_____________________________________________________________
        Pin     // 对象构造函数
        id      // GPIO编号，数值为（0~29）
        mode    // 模式，可选( None, Pin.IN(0), Pin.OUT(1), Pin.OPEN_DRAIN(2) )
        pull    // 使用内部上拉或下拉，仅在输入模式下有效( None, Pin.PULL_UP(1), Pin.PULL_DOWN(2) )
        value   // 0(off), 1(on)



// RP2040-GPIO程序
//_____________________________________________________________
from machine import Pin
import utime
#// 初始化GPIO15，配置为输入模式，使用上拉电阻
#// 作为外部信号输入引脚，如果为低电平，打开led
button_num = 15
button = Pin(button_num, Pin.IN, Pin.PULL_UP)

#// 配置GPIO16， 输出模式
external_led_num = 16;
external_led = Pin(external_led_num, Pin.OUT)

#// 配置GPIO25，输出模式
led_num = 25
led = Pin(led_num, Pin.OUT)

print("button gpio={0}".format(button_num))

while True:
	#// 打开led
	led.off()
	#// 读取“button”的值， 延时10ms，使用软件消抖
	if (button.value() == 0):
		utime.sleep(0.01)
		if (button.value() == 0):
			#// Toggle led
			external_led.toggle()
			#// led turn on
			led.on()
			print("button is pressed")
			while (button.value() == 0):
				utime.sleep(0.01)
				
				
				
/*******************************************************************************
        => RP2040-PWM
*******************************************************************************/

        machine.PWM(pin)
//_____________________________________________________________
//其作用是指定GPIO重新初始化并设置为PWM输出
  
  
  
PWM.freq([value])       //为PWM频率设置函数
                        //根据参数“value”自动计算分频器参数和TOP寄存器参数
                        //“TOP寄存器”决定了计数器最大计数值
PWM.duty_u16([value])   //用于设置占空比
                        //通过参数“value”自动计算出相对应的数值并赋予给“CC寄存器”

PWM.duty_ns([value])    //设置一个周期输出高电平的时间
                        //其参数“value”为高电平时间，单位为ns
                        
                        
                        
// RP2040-PWM脉冲宽度调制
//_____________________________________________________________
from machine import Pin, PWM
import utime

# //配置GPIO25为PWM模式
LED = PWM(Pin(25))

# //配置PWM频率为 1000Hz
LED.freq(1000)

LDE_duty = 0
LED_drection = 1
while True :
	LED_duty += LED_direction
	if LED_duty >= 100 :
		LED_duty = 100
		LED_direction = -1
	elif LED_duty <= 0 :
		LED_duty = 0
		LED_direction = 1
	LED.duty_u16(int(LED_duty * 655.36))
	if LED_duty % 5 == 0 :
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




        machine.ADC(id)
//_____________________________________________________________
  id    //可以为GPIO对象， 也可以为ADC通道
        //使用“Pin对象”时，指定的GPIO需要支持ADC功能，即GPIO26~29
        //使用“ADC通道”时，通道“0~3”对应“GPIO26~29”
        //“通道4”对应内部温度传感器


        read_u16()
//_____________________________________________________________
//函数的作用，读取对应通道ADC，并返回读取到的数值
//注意！ 该函数返回数值并不是直接返回ADC读取的数值
//而是经过处理的数值，数值范围为“0~65535”， ADC电压公式为：
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



// 这个程序实现每秒读取一次GPIO26上的电压，并使用片内温度传感器采集温度
//_____________________________________________________________
from machine import Pin, ADC
import utime
# //1-> 通过指定GPIO26初始化ADC通道“0”
# //    选择RP2040—ADC通道“0”，使用此通道采集外部输入电压
ADC0 = ADC(Pin(26))

# //2-> 指定初始化ADC通道“4”，其对应片内温度传感器
# //    选择RP2040—ADC通道“4”，此通道为内部温度传感器
sensor_temp = ADC(4)

while True:
	# //使用通道0，测量外部电压
	read_voltage = ADC0.read_u16() * 3.3 / 65535
	# //使用通道4，为内部温度传感器
	read_temp_voltage = sensor_temp.read_u16() * 3.3 / 65535
	temperature = 27 - (read_temp_voltage - 0.706) / 0.001721
	print("ADC0_voltage = {0:.2f}V \t\t temperature = \
	        {1:.2f}C \r\n".format(read_voltage, temperature))
	utime.sleep_ms(1000)
	
	
	
/*******************************************************************************
        => RP2040-UART
*******************************************************************************/
        1       //收发独立FIFO
        2       //可编程波特率生成器
        3       //标准异步通信位，在发送时添加，在接收时删除
        4       //换行符检测
        5       //可编程串行接口（5，6，7，8）数据位
        6       //1位或2位停止位
        7       //可编程的硬件流量控制（RTS， CTS）
RTS(Require ToSend)发送请求，为输出信号，用于指示本设备准备好可接收数据，低电平有效
CTS(Clear ToSend)发送允许，为输入信号，用于判断是否可以向对方发送数据，低电平有效




        machine.UART(
                id, baudrate=115200, bits=8, 
                parity=None, stop=1, tx=None, rx=None)
//_____________________________________________________________
// UART构造函数
        id              //使用UART通道，“0”或“1”
        baudrate        //使用波特率
        bits            //数据位长度
        parity          //奇偶校验位
        stop            //停止位长度
        tx              //TXD引脚，应为Pin对象
        rx              //RXD引脚，应为Pin对象


        UART.any()
//_____________________________________________________________
//用于检测当前接收缓冲区是否有数据
//有数据返回（1），否则返回（0）


        UART.read([nbytes])
//_____________________________________________________________
//如果指定了“nbytes”，则最多读取这么多字节，否则尽可能多的读取数据


        UART.readline()
//_____________________________________________________________
//读取一行，以换行符为结束标志


        UART.readinto(buf[,nbytes])
//_____________________________________________________________
//将读取的字符串存入指定缓存中. 参数buf，用于指定缓存
//nbytes:如果指定了“nbytes”, 则最多读取这么多字节，否则读取尽可能多的数据


        UART.write(buf)
//_____________________________________________________________
//用于发送字符串，返回值（发送的字节数）


        UART.sendbreak()
//_____________________________________________________________
//往总线上发送停止状态，拉低总线13Bit时间



from machine import Pin, ADC
import utime

//初始化了UART通道（0），波特率（115200），GPIO0（TX），GPIO1（RX）
uart = UART(0, baudrate=115200, tx=Pin(0), rx=Pin(1))

//初始化GPIO25作为输出引脚，用于驱动板载LED灯
led = Pin(25, Pin.OUT)

uart.write("Waveshare Uart Test\r\n")
uart.write("Plase enter charcter 0 or 1 to switch the LED on and off \r\n")

while True:
	if uart.any() == True:
		buf = uart.read(1)
		if buf == b'1':                 //判断读取的数据是否为字符“1”
			led.on()
			print("LED ON")
			uart.write("LED ON\r\n")
		elif buf == b'0':               //判断读取的数据是否为字符“0”
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
//      RP2040-I2C主要参数
//_____________________________________________________________
        1 支持主模式和从模式(默认主模式)
        2 支持标准模式，快速模式， 和快速模式+
        3 默认从机地址为“0x55”
        4 主模式下支持“10bit地址”
        5 “16”位接收缓冲区
        6 “16”位发送缓冲区
        7 可以使用DMA驱动
        8 可生成中断



        machine.I2C(id, scl, sda, freq=400000)
//_____________________________________________________________
//I2C对象构造函数，作用为初始化对应的I2C通道和引脚
        id    //参数id为使用I2C通道，可以为0或1
        scl   //使用I2C引脚，应为Pin对象
        sda   //使用I2C引脚，应为Pin对象
        freq  //freq，I2C频率，默认为400KHz


        I2C.scan()
//_____________________________________________________________
//扫描从设备函数，将返回含有所有I2C总线上挂载从设备7位地址的列表



        I2C.readfrom(addr, bytes, stop=Ture)
//_____________________________________________________________
//readfrom函数其作用为通过I2C总线从设备读取数据并返回字节串
        addr    //从设备地址
        nbytes  //读取字符串长度
        stop    //是否在接收完成数据后发送结束信号


        I2C.readfrom_into(addr, buf, stop=Ture)
//_____________________________________________________________
//可以将读取数据存放指定的字符数组中
        buf     //字符数组，用于存放数据
        addr    //从设备地址
        stop    //是否在接收完成数据后发送结束信号

        
        I2C.writeto(addr, buf, stop=True)
//_____________________________________________________________
//向从设备写入数据
        addr    //从设备地址
        buf     //发送字符串
        stop    //是否在接收完成后发送结束信号
        
    
        I2C.readform_mem(addr, memaddr, nbytes, *, addrsize=8)    
//_____________________________________________________________
//读取从设备的寄存器中的数据
        addr    //从设备地址
        memaddr //寄存器地址
        nbytes  //读取字节长度
        addrsize//寄存器地址长度
    
    
        I2C.readform_mem_into(addr, memaddr, buf, *, addrsize=8)
        I2C.writeto_mem(addr, memaddr, buf, *, addrsize=8)    
//_____________________________________________________________
//readfrom_mem_into函数作用为从设备的寄存中读取数据到指定字符数组中
//writeto_mem函数作用为将数据写入从设备的寄存器



from machine import I2C, Pin

# //初始化I2C通道（1），使用GPIO（6）和GPIO（7）分别作为SDA和SCL引脚，频率为（100KHz）
i2c = I2c(id=1, scl=Pin(7) sda=Pin(6), freq=100_000)

# //使用扫描函数，扫描I2C总线下所有设备地址，并返回对应的列表
addr_list = i2c.scan()

if len(addr_list) == 1 :
        # //读取该设备的（0x00）寄存器
        who = i2c.readfrom_mem(addr_list[0], 0x00, 1)
        # //Identify ICM20948
        if who[0] == 0xEA :
                printf("Just a ICM20948 connected")
        else :
                printf("Have a device connected but it is not ICM20948")
elif len(addr_list) == 0 :
        printf("Nothing connected")
else :
        printf("More than one device is connected")



/*******************************************************************************
        => RP2040-SPI
*******************************************************************************/
        MOSI    //主机发送，从机接收
        MISO    //主机接收，从机发送
        SCLK    //时钟信号
        CS      //Chip select, 用来选择从设备
        CPHA    //Clock Phase, 时钟相位
                选择捕获数据的时钟边沿，如果时钟相位为低（CPHA=0），
                则数据在第一个时钟边沿捕获,反之则数据在第二个时钟边沿捕获
        CPOL    //Clock polarity, 时钟极性
                空闲时时钟信号电平，如果时钟极性为低（CPOL=0），
                则时钟信号引脚在空闲时输出低电平,反之时钟信号引脚在空闲时输出高电平


//      RP2040-SPI参数
//_____________________________________________________________
        1 支持主从模式
          //支持摩托罗拉SPI接口
          //支持德州仪器同步串口(SSI)
          //支持美国国家半导体Microwire接口
        2 8单位深度收发先进先出存储器(8 deep TX and TX FIFOs）
        3 中断生成器可服务于先进先出存储器或者错误标识
        4 可以使用DMA驱动
        5 可编程时钟
        6 可编程数据大小(4~16bit)


        machine.SPI(
                id, baudrate=1000000,
                polarity=0, phase=0,
                bits=8, firstbit=SPI.MSB,
                sck=None, mosi=None, miso=None
        ) 
//_____________________________________________________________
//SPI对象构造函数
  id            //参数id为spi通道，可以为0或1
  baudrate      //spi通讯速率，也就是SCK引脚上的频率
  polarity      //时钟极性，若为0则总线空闲时SCK输出低电平，反之则输出高电平
  phase         //时钟相位，若为0则在第一个时钟边沿捕获数据，反之则在第二个时钟边没捕获数据
  bits          //每次传输数据的位数
  firsbit       //先传输高位，还是先传输低位
  sck           //SPI引脚，应为Pin对象
  mosi          //SPI引脚，应为Pin对象
  miso          //SPI引脚，应为Pin对象


        SPI.read(nbytes, write=0x00)
//_____________________________________________________________
//read()函数，用于读取从设备并返回
        nbytes        //参数“nbytes”为读取字节数
        write         //write读取数据时，“MOSI”输出数据


        SPI.readinto(buf, write=0x00)
//_____________________________________________________________
//readinto()函数，用于读取从设备数据并存入指定字符数组中
        buf           //字符数组，用于存放接收数据
        write         //write读取数据时，“MOSI”输出数据


        SPI.write(buf) 
//_____________________________________________________________
//read.write()函数，用于向从设备写入数据
        buf           //buf字符数组，用于存放传输数据


        SPI.write_readinto(write_buf, read_buf) 
//_____________________________________________________________
//write_readinto()函数，用于同时发送和接收数据
        write_buf     //字符数组，用于存放传输数据
        read_buf      //字符数组，用于存放接收数据
        //这里传输和接收的字符数组的长度要求一致


//初始化SPI，使用通道（1），频率为（5MHz），分别使用GPIO（10，11，12）作为（SCK, MOSI, MISO）
spi = SPI(1, baudrate=5_000_000, sck=Pin(10),
                                 mosi=Pin(11),
                                 miso=Pin(12));
//初始化GPIO（17，16），并将GPIO（16）设置为高电平
IRQ   = Pin(17, Pin.IN)
TP_CS = Pin(16, Pin.OUT)
TP_CS(1)

//当（XPT2046）检测到触摸，则会在IRQ引脚输出中断信号，用于表示检测到触摸
while True :
        if IRQ() == 0 :
                TP_CS(0)
                spi.write(bytearry([0xD0]))
                Read_date = spi_read(2)
                time.sleep_us(10)
                X_Point = ((Read_date[0] << 8) + Read_date[1]) >> 3
                
                spi.write(bytearry([0x90]))
                Read_date = spi_read(2)
                time.sleep_us(10)
                X_Point = ((Read_date[0] << 8) + Read_date[1]) >> 3
                TP_CS(1)
                
                printf("*******************************************")
                printf("*************** TP_Read_ADC ***************")
                printf("*******************************************")
                printf("X_Point = {} ".format(X_Point))
                printf("Y_Point = {} ".format(Y_Point))
        time.sleep(0.5)            
                
                

/*******************************************************************************
        => RP2040-PIO
*******************************************************************************/
// RP2040有（30）个GPIO引脚， 30，31称为消失的引脚
//_____________________________________________________________
 0       1       2       3     ...       29    (  30,   31)


// 输入映射
//_____________________________________________________________
我们可以指定输入（GPIO）的初始引脚，这个初始引脚在（PIO）的输入映射中将
会被视为（引脚0）, 并将其它引脚按照顺序进行（循环）计数，这里就会遇到“消失的引脚”
// 如果设置（GP29）为初始引脚
// 经过GPIO30和GPIO31，引脚（3）对应（GPIO0）
//_____________________________________________________________
 0       1       2       3     ...       29    (  30,   31)
 |       |       |       |       |       |        |     |
GP29    GP30    GP31    GP0     ...     GP26    GP27   GP28


//输出映射和输入映射接近，但需要设置输出引脚的数量，最高可为（32）
//设置和侧置映射与输出映射工作相同，但最多映射（5个IO），设置和侧置映射引脚允许重叠的


        
        JMP     (condition) target
//_____________________________________________________________
target          //允许数值（0~31），因此PIO只有32条指令空间
condition       //条件


        WAIT    Polarity  Source  Index
//_____________________________________________________________
Poalrity        //极性，是指等待目标出现（0或者1）
Source          //源，等待目标类型
                  GPIO: 绝对GPIO
                  PIN:  引脚映射后的引脚
                  IRQ:  中断标志
Index           //指针，对应等待的目标编码
                  WAIT Polarity GPIO num
                  WAIT Polarity PIN  num
                  WAIT Polarity IRQ  num (rel)


        IN      Source, Bitcount
//_____________________________________________________________
//IN指令作用将数据存入（ISR）寄存器中
Source          //源指对应数据的源类型
                  PINS, X, Y, NULL, ISR, OSR
Bitcont         //读取数据的位数


        OUT      destination, Bitcount
//_____________________________________________________________
//OUT指令和IN指令功能相反，指令作用是将（OSR）输出到目标
destination     //目标
                  PINS, X, Y, NULL, PINDIRS, PC, ISR, OSR
Bitcount        //位数，对应输出位数

        
        PUSH
//_____________________________________________________________
//将（ISR）中内容推送到（RX_FIFO）和清空（ISR）


        PULL
//_____________________________________________________________
//将从（TX_FIFO）数据读出到（OSR）寄存器


        MOV     destination, source, (Operation)
//_____________________________________________________________
destination     //目标
                PINS:   引脚，映射后的引脚
                X:      暂存寄存器
                Y:      暂存寄存器
                EXEC:   解码寄存器
                PC:     PC寄存器
                IRQ:    中断标志
source          //源
                PINS:   引脚，映射后的引脚
                X:      暂存寄存器
                Y:      暂存寄存器
                NULL:   空，用于清零
                STATUS: 表示不同的状态，如FIFO满或者空
                ISR:    
                OSR:    移位寄存器
Operation       //操作    
        00      不改变
        01      位取反
        10      位翻转（高低位互换）


        IRQ     (optinon) irq_num (_rel)
//_____________________________________________________________
//设置或清空中断标识
option          //选项
        set     设置
        nowait  不等待清除
        wait    等待清除后，运行
        clear   清除
irq_num         //中断标志位（0~7）
        (sm_id + irq_num) % 4 = irq_flag
        sm_id   //状态机编码
        irq_num //中断标识
REL             //


        SET     destination, data
//_____________________________________________________________
data            //(0~31)



// RP2040-PIO 汇编程序
//_____________________________________________________________
.program spi_tx_fast
.side_set 1             //声明侧置功能的位数（1）
                        //它会占用(Side-set/Delay)字段的高一位
                        //那么Delay只能占用（4位），数值范围为（0~15）
loop:
out pins, 1     side 0
jmp loop        side 1



//_____________________________________________________________
@asm_pio(
        out_init=None,          //输出引脚初始化
        set_init=None,          //设置引脚初始化
        sideset_init=None,      //侧置引脚初始化
        in_shiftdir=0,          //数据输入方向
        out_shiftdir=0,         //数据输出方向
        autopush=False,         //自动推送
        autopull=False,         //自动拉取
        push_thresh=32,         //推送阈值
        pull_thresh=32,         //拉取阈值
        fifo_join=0             //指定FIFO


rp2.StateMachine(sm_id, program, freq=-1, *, in_base=None, out_base=None,
                 set_base=None, jmp_pin=None, sideset_base=None, in_shiftdir=None,
                 out_shitdir=None, push_thresh=None, pull_thresh=None)
        sm_id           //使用状态机ID， 0-3为PIO0， 4-7为PIO1
        program         //状态机运行程序
        freq            //状态机运行频率，默认为系统时钟频率
                        时钟分步因子计算公式为：系统时钟频率 / 频率， 存在一点误差
        out_base        //用于out()指令的第一个引脚
        set_base        //用于set()指令的第一个引脚
        jmp_pin         //用于jmp()指令的第一个引脚
        sideset_base    //用于sideset()指令的第一个引脚
        in_shitfdir     //ISR将移动的方向，可为PIO.SHIFT_LEFT或者PIO.SHIFT_RIGHT
        out_shitdir     //OSR将移动的方向，可为PIO.SHIFT_LEFT或者PIO.SHIFT_RIGHT



        StateMachine.active([value])
//_____________________________________________________________
//获取或设置状态机当前是否正在运行
//当value不为空，设置状态机，反之获取运行状态

        
        StateMachine.restart()
//_____________________________________________________________
//重新启动状态机，并跳转到程序的开头

        
        StateMacine.exec(instr)
//_____________________________________________________________
//exec 执行单个PIO指令
//instr为指令字符串


        StateMachine.get(but=None,shitf=0)
//_____________________________________________________________
//从状态机的（RX_FIFO）中提取一个字
//如果FIFO为空，它会阻塞直到数据到达（即状态机推一个字）


        StateMachine.put(value, shitf=0)
//_____________________________________________________________
//将一个字推送到状态机的（TX_FIFO）
//如果FIFO已满，它将阻塞直到有空间（即状态机拉一个字）
//shift，在推送之前左移位数


        StateMachine.rx_fifo()
        StateMachine.tx_fifo()
//_____________________________________________________________






import time
from machine import Pin
import rp2

max_lum = 100
r       = 0
g       = 0
b       = 0
//WS2812B 单总线控制电路
//_____________________________________________________________
@rq2.asm_pio(   sideset_init=rp2.PIO.OUT_LOW,           //一个初始化信息，说明侧置引脚数量为（1）
                out_shiftdir=rp2.PIO.SHIFT_LEFT,        //数据输出移方向（从右向左移动）
                sutopull=True,                          //开启自动拉取
                pull_thresh=24)                         //拉取阈值为24位（发送数据长度）
def ws2812():
        T1 = 2
        T2 = 5
        T3 = 3
        wrqp_target()
        label("bitloop")
        out(x, 1)               .side(0)        [T3 - 1]
        jmp(not_x, "do_zero")   .side(1)        [T1 - 1]        //如果（x）中的数值为（0），则跳转到（do_zero）
        jmp("bitloop")          .side(1)        [T2 - 1]
        label("do_zero")
        nop()                   .side(0)        [T2 - 1]
        wrap()

//创建状态机（0），使用ws2812程序，时钟频率为（8MHz），基础侧置引脚为（4）
sm = rp2.StateMachine(0, ws2812, freq=8_000_000, sideset_base=Pin(4))


//在循环中，我们不断改变RGB数值，并通过sm.put()函数将数值传输给（TX_FIFO）
while True :
        for i in range(0, max_lum):
                r   = i
                b   = max_lum-i
                rgb = (g << 24) | (r << 16) | (b << 8)
                sm.put(rgb)
                time.sleep_ms(10)
        time.sleep_ms(300)

        for i in range(0, max_lum):
                g   = i
                r   = max_lum-i
                rgb = (g << 24) | (r << 16) | (b << 8)
                sm.put(rgb)
                time.sleep_ms(10)
        time.sleep_ms(300)

        for i in range(0, max_lum):
                b   = i
                g   = max_lum-i
                rgb = (g << 24) | (r << 16) | (b << 8)
                sm.put(rgb)
                time.sleep_ms(10)
        time.sleep_ms(300)



