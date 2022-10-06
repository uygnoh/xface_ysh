#include "IIC_2.h"
#include "DELAY.h"

#define TIMEOUT         1000
// https://bbs.csdn.net/topics/396439443?list=lz
// 解决BUSY死锁问题--但是注意--这里没有超时机制-等于不能保证多主机处理稳定性
//_____________________________________________________________________
void i2c_is_busy(void)
{
        uint8_t i;
        
        while ((I2C2->SR2 & (1 << 1)) != 0) {           // 总线忙BUSY !=0 就在这里循环等待
                RCC->APB2ENR    |= (1 << 3);            // GPIOB 时钟使能
                GPIOB->CRH      &= 0xFFFF00FF;          // 这里只针对IIC2引脚初始化
                GPIOB->CRH      |= 0x00007700;          // PB10-SCK PB11-SDA 开漏输出
                for (i = 0; i < 10; i++) {              // 解决BUSY死锁问题
                        __PB_OUT(10) = ~__PB_OUT(10);   
                        delay_us(20);
                }

                PCout(13) = ~PCout(13);                 // led闪起来
                i2c_setup();

        }
}


void i2c_setup(void)
{
        // 注意！！AFIO时钟无所谓开启，只有操作
        // AF(复用功能)的IO重新映射，AFIO时钟才需要开启，并非属于普通IO时钟管理
        RCC->APB2ENR    |= (1 << 3);            // GPIOB 时钟使能
        GPIOB->CRH      &= (0XFFFF00FF);        // 这里只针对IIC2引脚初始化
        GPIOB->CRH      |= (0X0000FF00);        // PB10-SCK PB11-SDA 开漏复用输出


        // 以下是IIC2的寄存器配置
        RCC->APB1RSTR   |=  (1 << 22);  // 复位IIC2寄存器
        RCC->APB1RSTR   &= ~(1 << 22);  // 停止复位IIC2寄存器
        RCC->APB1ENR    |=  (1 << 22);  // I2C2  时钟使能


        I2C2->CR1       |=  (1 << 15);  // 复位IIC2
        I2C2->CR1       &= ~(1 << 15);
        delay_us(5);

        I2C2->CR1       &= ~(1 << 1);   // SMBUS[1]  
                                        // 0 : I2C模式   1 : SMBus模式
        I2C2->CR1       |=  (1 << 10);  // ACK[10]       0：无应答返回
                                        // 1:接受到一个字节后返回一个应答（匹配的地址或数据）


        //I2C2->CR2     |= (1 << 10);   // ITBUFEN[10] ---缓冲器中断使能
        //I2C2->CR2     |= (1 << 9);    // ITEVTEN[9]  ---事件中断使能
        I2C2->CR2       |= (1 << 8);    // ITERREN[8]  ---出错中断使能
        I2C2->CR2       |= (0x24);      // FREQ[5:0]   ---配置为输入时钟36M


        I2C2->OAR1      &= ~(1 << 15);  // ADDMODE[15] ---寻址模式(从模式)  
                                        // 0： 7位从地址    1: 10位从地址
        I2C2->OAR1      |=  (1 << 14);  // [14]        ---要求必须软件保持‘1’
        I2C2->OAR1      |=  (0x00);     // [7:1]       ---7位从模式地址设为0X00-接收主机信号使用
        I2C2->OAR2      &= ~(1);        // [0] 0: 7位地址模式只识别OAR1 
                                        // [0] 1: 7位地址模式下识别OAR1 -2双地址--7位地址模式只识别OAR1。


        I2C2->CCR       |= (1 << 15);   // F/S[15]     ---I2C主模式选项
                                        // 0: 标准模式      1: 快速模式
        I2C2->CCR&       = ~(1 << 14);  // DUTY[14]    ---快速模式时的占空比
                                        // 0: 快速模式下:T low /T high = 2;
                                        // 1: 快速模式下:T low /T high = 16/9
        I2C2->CCR       |= 0x1F;        // CCR[11:0] : 快速 / 标准模式下的时钟控制分频系数 (主模式 )，
                                        // 2*31*27ns+1*31*27ns=2511ns一个周期，398.24771kHZ 无法达到400khz
        I2C2->TRISE      = 0xC;         // TRISE[5:0] : 在快速 / 标准模式下的最大上升时间 (主模式)
                                        //  配置最大上升时间为324ns


        // IIC2 NVIC 中断优先级配置
        //_______________________
        // 使能错误中断
        NVIC_Init(0,0,I2C2_ER_IRQn,2);  // 组2，最高先级-分组不能变
        I2C2->CR1       |= 1;           // bit-0位--所有配置寄存器配置妥当后开启PE位---使能IIC2
        delay_us(5);

}




void I2C_SingleWrite(uint8_t address, uint8_t subAddress, uint8_t data)
{
        u16 SR2_STATE=0, i=0;

        i2c_is_busy();

        I2C2->CR1 |= 1<<8;      // 产生起始条件 START=1;
        i = TIMEOUT;
        while ((I2C2->SR1 & (0x0001)) != 0x0001) {
                if (i == 0) {
                        I2C2->CR1 |= 1<<9;
                        return;
                } else {
                        i--;
                }
        } //SB=1 起始条件已发--读取SR1+写DR可清除。
          //IIC_Start();


        I2C2->DR = ((address<<1) | 0);
        // IIC_Send_Byte((address<<1)|0);//发送器件地址+写命令


        i = TIMEOUT;
        while ((I2C2->SR1 & (0x0002)) != 0x0002) {
                if (i == 0) {
                        I2C2->CR1 |= 1<<9;
                        return;
                } else {
                        i--;
                }
        } // 等待地址发送成功。ADDR=1代表地址发送成功,收到从机发出的接收
          // 地址完成ACK后置位1//IIC_Wait_Ack(); //等待应答


        
        SR2_STATE = I2C2->SR2;    //已读SR1-再读-SR2清除ADDR。
        SR2_STATE = SR2_STATE;
        /*注意，手册说在发送地址阶段不会设置TxE,所以这里TxE=0，不要通过
        判断TxE=1来确定收到ACK*/


        I2C2->DR = subAddress;  //发出第一个DATA,这时候一写入DR马上进入移
        // 位寄存器，TxE还是为1   //IIC_Send_Byte(subAddress); //写寄存器地址-DATA1


        i = TIMEOUT;
        while ((I2C2->SR1 & (0x0080)) != 0x0080) {
                if (i == 0) {
                        I2C2->CR1 |= 1<<9;
                        return;
                } else {
                        i--;
                }
        } // 这里等待TxE=1是为了判断DR是否为空。
          // IIC_Wait_Ack(); //等待应答


        I2C2->DR = data;        //发送数据--如果不行就考虑连续写2次DR测试下。


        i = TIMEOUT;
        while ((I2C2->SR1 & (0x0084)) != 0x0084) {
                if (i == 0) {
                        I2C2->CR1 |= 1<<9;
                        return;
                } else {
                        i--;
                }
        }
        //TxE=1且BTF=1 数据寄存器空--移位寄存器已经排空
        //IIC_Wait_Ack();       //等待应答

        I2C2->CR1 |= 1<<9;      // 产生停止条件 STOP=1;

}


void I2C_MultipleRead(  uint8_t address, 
                        uint8_t subAddress, 
                        uint8_t *pBuf, 
                        uint8_t len)
{
        u16 SR2_STATE = 0, i = 0;

        i2c_is_busy();

        I2C2->CR1|=1<<8; //产生起始条件 START=1;
        i = TIMEOUT;
        while ((I2C2->SR1 & (0x0001)) != 0x0001) {
                if (i == 0) {
                        I2C2->CR1 |= 1<<9;
                        return;
                } else {
                        i--;
                }
        }// SB=1 起始条件已发--读取SR1+写DR可清除。
         // IIC_Start();



        I2C2->DR = ((address<<1) | 0);
        // IIC_Send_Byte((address<<1)|0);
        // 发送器件地址+写命令



        i = TIMEOUT;
        while ((I2C2->SR1 & (0x0002)) != 0x0002) { 
                if(i==0) {
                        I2C2->CR1 |= 1<<9;
                        return;
                } else {
                        i--;
                }
        }// 等待地址发送成功。ADDR=1代表地址发送成功,
         // 收到从机发出的接收地址完成ACK后置位1
         // IIC_Wait_Ack(); 等待应答


        SR2_STATE=I2C2->SR2; // 已读SR1-再读-SR2清除ADDR。
        SR2_STATE=SR2_STATE;
        /*注意，手册说在发送地址阶段不会设置TxE,所以这里TxE=0，不要通过
        判断TxE=1来确定收到ACK*/


        I2C2->DR = subAddress;  // 发出第一个DATA,这时候一写入DR马上进入移位寄存器，TxE还是为1 
                                // IIC_Send_Byte(subAddress); //写寄存器地址-DATA1


        i = TIMEOUT;
        while ((I2C2->SR1 & (0x0084)) != 0x0084) {
                if (i == 0) {
                        I2C2->CR1 |= 1<<9;
                        return;
                } else {
                        i--;
                }
        } // TxE=1且BTF=1 数据寄存器空--移位寄存器已经排空 
          // IIC_Wait_Ack(); 等待应答


        /*RESTART-中间插入重开始信号-手册只说10位地址有效-存在错误*/


        I2C2->CR1 |= 1<<8;      //重开始信号-起始条件 START=1;
        i = TIMEOUT;
        while ((I2C2->SR1 & (0x0001)) != 0x0001) {
                if ( i==0 ) {
                        I2C2->CR1 |= 1<<9;
                        return;
                } else {
                        i--;
                }
        } //SB=1 起始条件已发--读取SR1+写DR可清除。
          //IIC_Start();


        I2C2->DR = ((address<<1) | 1);  //发送器件地址+读命令


        I2C2->CR1 |= 1<<10;             //开启应答-------->>
        i = TIMEOUT;
        while((I2C2->SR1 & (0x0002)) != 0x0002) {
                if (i == 0) {
                        I2C2->CR1 |= 1<<9;
                        return;
                } else {
                        i--;
                }
        }//等待地址发送成功。 ADDR=1代表地址发送成功,收到从机发出的接收地址完成ACK后置位1
         //IIC_Wait_Ack(); //等待应答


        SR2_STATE = I2C2->SR2; //已读SR1-再读-SR2清除ADDR-代表收到地址ACK


        while (len) {
                if (len == 1) {
                        I2C2->CR1& = ~(1<<10);//NACK

                        I2C2->CR1 |= 1<<9; // 请求产生停止条件STOP=1,
                        // 注意位置-手册所需要当前字节传输完成ACK之前----执行停止请求后不要
                        // 设置CR1---->>

                        i = TIMEOUT;
                        while ((I2C2->SR1 & (0x0040)) != 0x0040) {
                                if (i == 0) { 
                                        I2C2->CR1|=1<<9;
                                        return;
                                } else { 
                                        i--;
                                }
                        }// RxNE=1 数据寄存器接收到数据

                        *pBuf = I2C2->DR;       //读数据,发送nACK

                } else {

                        i = TIMEOUT;
                        while ((I2C2->SR1 & (0x0040)) != 0x0040) {
                                if(i == 0) {
                                        I2C2->CR1 |= 1<<9;
                                        return;
                                } else {
                                        i--;
                                }
                        }// RxNE=1 数据寄存器接收到数据

                        *pBuf = I2C2->DR; //读数据,发送ACK

                }

                len--;
                pBuf++;
        }
}



void I2C_MultipleWrite(
                uint8_t address, 
                uint8_t subAddress, 
                uint8_t *pBuf, 
                uint8_t len)
{
        u16 SR2_STATE = 0, i = 0;

        i2c_is_busy();

        I2C2->CR1 |= 1<<8;      //产生起始条件 START=1;
        i = TIMEOUT;
        while ((I2C2->SR1 & (0x0001)) != 0x0001) {
                if (i == 0) {
                        I2C2->CR1 |= 1<<9;
                        return;
                } else {
                        i--;
                }
        }       // SB=1 起始条件已发--读取SR1+写DR可清除。
                // IIC_Start();


        I2C2->DR = ((address<<1) | 0);
        //IIC_Send_Byte((address<<1)|0);//发送器件地址+写命令


        i = TIMEOUT;
        while ((I2C2->SR1 & (0x0002)) != 0x0002) { 
                if (i == 0) {
                        I2C2->CR1 |= 1<<9;
                        return;
                } else {
                        i--;
                }
        }//等待地址发送成功。 ADDR=1代表地址发送成功,
         //收到从机发出的接收地址完成ACK后置位1
         //IIC_Wait_Ack(); //等待应答


        SR2_STATE=I2C2->SR2;//已读SR1-再读-SR2清除ADDR。
        SR2_STATE=SR2_STATE;
        /*注意，手册说在发送地址阶段不会设置TxE,所以这里TxE=0，不要通过
        判断TxE=1来确定收到ACK*/


        I2C2->DR=subAddress;    // 发出第一个DATA,这时候一写入DR马上进入移
                                // 位寄存器，TxE还是为1 
                                // IIC_Send_Byte(subAddress); //写寄存器地址-DATA1


        i = TIMEOUT;
        while ((I2C2->SR1 & (0x0080)) != 0x0080) {
                if (i == 0) {
                        I2C2->CR1 |= 1<<9;
                        return;
                } else {
                        i--;
                }
        } //这里等待TxE=1是为了判断DR是否为空。
          //IIC_Wait_Ack(); //等待应答


        while (len) {
                if (len == 1) {
                        I2C2->DR = *pBuf;       //发送最后一个Buf的数据

                        i = TIMEOUT;
                        while ((I2C2->SR1 & (0x0084)) != 0x0084) {
                                if (i == 0) {
                                        I2C2->CR1 |= 1<<9;
                                        return;
                                } else i--;
                        } //TxE=1且BTF=1 数据寄存器空--移位寄存器已经排空 
                          //IIC_Wait_Ack(); //等待应答


                        // 请求产生停止条件STOP=1--执行停止请求后不要设置CR1---->>
                        I2C2->CR1 |= 1<<9; 

                } else {

                        I2C2->DR = *pBuf;       //发送buff的数据

                        i = TIMEOUT;
                        while ((I2C2->SR1 & (0x0080)) != 0x0080) {
                                if (i == 0) {
                                        I2C2->CR1|=1<<9;
                                        return;
                                } else {
                                        i--;
                                }
                        }//这里等待TxE=1是为了判断DR是否为空。 
                         //IIC_Wait_Ack(); //等待应答

                }

                len--;
                pBuf++;
        }
}



// I2C错误中断服务
//_____________________________________________________________________
void I2C2_ER_IRQHandler(void)
{
        u8 i;

        RCC->APB2ENR |= 1<<3; //PORTB时钟使能
        //这里只针对IIC2引脚初始化
        GPIOB->CRH &= 0XFFFF00FF;
        GPIOB->CRH |= 0X00007700;
        for (i=0; i<10; i++) {
                PBout(10) = ~PBout(10);//解决BUSY死锁问题
                delay_us(20);
        }

        PCout(13) = ~PCout(13);//led闪起来
        delay_ms(200);
        IIC_init();

        I2C2->SR1 &= 0x00FF;//软件写0清除
}
