void spi_bus_init(void)
{
        //引脚配置
        P1SEL    |= (BIT1 | BIT2 | BIT34);
        P1SEL2   |= (BIT1 | BIT2 | BIT34);
        //SPI禁止，时钟源SMCLK
        UCA0CTL1 |= UCSWRST | UCSSEL_2;
        //SPI模式，MSB优先，Master模式
        UCA0CTL0 |= UCMSB | UCMST | UCSYNC;
        //SPI速率
        UCA0BR0   = 1;
        UCA)BR1   = 0;
        //SPI使能
        UCA0CTL1 &= ~UCSWRST;
}


void spi_bud_write(uint8_t data)
{
        UCA0TXBUF = data;               //将待发送的数据写入发送缓冲器
        while (!(IFG2 & UCA0TXIFG));    //等待数据发送成功
}


uint8_t spi_bus_read(void)
{
        while (!(IFG2 & UCA0RXIFG));    //等待收到数据
        return (UCA0RXBUF);             //返回收到数据
}


int main(void)
{
        WDTCTL = TDTPW | WDTHOLD;
        system_clock_init();            //1Mhz
        spi_bus_init();
        spi_bus_write(0xAA);
        rx_data = spi_bus_read();
        while (1) {
                __delay_cycles(1000000);
        }
        return (0);
}
