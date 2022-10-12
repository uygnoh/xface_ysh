#ifndef __YSH_USART_H__
#define __YSH_SUART_H__


void usart_setup(void);
void usart_send_string(void)
#endif



// USART-TX 配置步骤:
// ____________________________________________________________
//      UE[13]  : 通过在USART_CR1寄存器上置位UE位来激活USART
//
//      M[12]   : 编程USART_CR1的M位来定义字长
//
//      在USART_CR2中编程停止位的位数。
//
//      如果采用多缓冲器通信,配置USART_CR3中的DMA使能
//      位(DMAT)。按多缓冲器通信中的描述配置DMA寄存器。
//
//      利用USART_BRR寄存器选择要求的波特率。
//
//      设置USART_CR1中的TE位,发送一个空闲帧作为第一次数据发送。
//
//      把要发送的数据写进USART_DR寄存器(此动作清除TXE位)。
//      在只有一个缓冲器的情况下,对每个待发送的数据重复步骤7。
//
//      在USART_DR寄存器中写入最后一个数据字后, 要等待TC=1,
//      它表示最后一个数据帧的传输结束。 当需要关闭USART或需要
//      进入停机模式之前,需要确认传输结束,避免破坏最后一次传输
