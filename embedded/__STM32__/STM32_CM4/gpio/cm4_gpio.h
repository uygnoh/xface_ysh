/*******************************************************************************
函数说明:
        配置GPIO端口模式
输入参数:
        prot  (GPIOA, GPIOB, GPIOC ...)
        mode  (0输入, 1输出, 2复用, 3模拟)
        pin   (0..15)     
*******************************************************************************/
#define INPUT           0       //输入模式
#define OUTPUT          1       //输出模式
#define ALTERNATE       2       //复用功能
#define ANALOG          3       //模拟输入
#define __gpio_port_mode(port, mode, pin) {             \
        (port)->MODER &= ~(3    << pin*2);              \
        (port)->MODER |=  (mode << pin*2);              \
}

/*******************************************************************************
函数说明:
        配置GPIO端口输出类型
输入参数:
        prot (GPIOA, GPIOB, GPIOC ...)
        type (0输出推挽, 1输出开漏)
        pin  (0..15)
*******************************************************************************/
#define OUTPUT_PUSHPULL         0
#define OUTPUT_OPENDRAIN        1
#define __gpio_port_output_type(port, type, pin) {      \
        (port)->OTYPER &= ~(1    << pin*2);             \
        (port)->OTYPER |=  (type << pin*2);             \
}

/*******************************************************************************
函数说明:
        配置GPIO端口速度
输入参数:
        prot  (GPIOA, GPIOB, GPIOC ...)
        speed (0低速, 1中速, 2快速, 3高速)
        pint  (0..15)
*******************************************************************************/
#define LOW             0       //00_2MHz  (低速)
#define MEDIUM          1       //01_25MHz (中速)
#define FAST            2       //10_50MHZ (快速)
#define HIGH            3       //11_80MHz (高速_15pF时)
                                //11_100MHz(高速_30pF时)
#define __gpio_port_output_speed(port, speed, pin) {    \
        (port)->OSPEEDR &= ~(3     << PIN*2);           \
        (port)->OSPEEDR |= ~(speed << PIN*2);           \
}

/*******************************************************************************
函数说明:
        配置GPIO端口（上拉，下拉，无上下拉）
输入参数:
        prot  (GPIOA, GPIOB, GPIOC ...)
        pull  (0无, 1上拉, 2下拉, 3保留)
        pin   (0..15)
*******************************************************************************/
#define NONE_PULL       0      //无上拉或下拉
#define PULLUP          1      //上拉
#define PULLDOWN        2      //下拉
#define RESERVE         3      //保留
#define __gpio_port_pullup_pulldown(port, pull, pin) {  \
        (port)->PUPDR &= ~(3    << PIN*2);              \
        (port)->PUPDR |=  (pull << PIN*2);              \
}

/*******************************************************************************
函数说明:
        1 置位GPIO端口位
        2 清零GPIO端口位
输入参数:
        prot  (GPIOA, GPIOB, GPIOC ...)
        pin   (0..15)
*******************************************************************************/
#define __gpio_port_set(port, pin) {                    \
        (port)->BSRR |=  (1 << PIN+16);                 \
}
#define __gpio_port_reset(port, pin) {                  \
        (port)->BSRR |=  (1 << PIN);                    \
}

/*******************************************************************************
函数说明:
        复用功能（AFIO）的低（32位数据）
输入参数:
        port    (GPIOA, GPIOB, GPIOC ...)
        af      (AF0 ~ AF15)
        pin_low (0..7)

*******************************************************************************/
#define afio_port_low(port, af, pin_low) {              \
        (port)->AFRL &= ~(15  << pin_low*4);            \
        (port)->AFRL |=  (af  << pin_low*4);            \
}

/*******************************************************************************
函数说明:
        复用功能（AFIO）的高（32位数据）
输入参数:
        port    (GPIOA, GPIOB, GPIOC ...)
        af      (AF0 ~ AF15)
        pin_low (8..15)

*******************************************************************************/
#define afio_port_high(port, af, pin_high) {            \
        (port)->AFRH &= ~(15  << pin_high*4);           \
        (port)->AFRH |=  (af  << pin_high*4);           \
}
