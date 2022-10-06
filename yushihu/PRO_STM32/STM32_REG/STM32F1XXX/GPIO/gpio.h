#ifndef __GPIO_H__
#define __GPIO_H__


/*******************************************************************************
        => GPIO模式配置相关寄存器
*******************************************************************************/
// 
// ____________________________________________________________
// GPIOx_CRL    -> 7   6   5   4   3   2   1   0   //  0~7 管脚
// GPIOx_CRH    -> 15  14  13  12  11  10  9   8   // 8~16 管脚
//
//      在输入模式下(MODE[1:0] = 00)
//      在输出模式下(MODE[1:0] > 00)
//      -------------------------------------------------------
//              配置    模式
//      || CONF[1:0]   MODE[1:0]
//      ||      0 0     0 0     |  0  | 模拟输入
//      ||      0 1     0 0     |  4  | 浮空输入(复位后的状态) 
//      ||      1 0     0 0     |  8  | 下拉输入(如果 PxODR = 0)
//      ||      1 0     0 0     |  8  | 上拉输入(如果 PxODR = 1)
//      ||      1 1     0 0     |  C  | 保留
//      -------------------------------------------------------
//      ||      0 0     0 1     |  1  | 推挽输出(10MHz)
//      ||      0 0     1 0     |  2  | 推挽输出(02MHz)
//      ||      0 0     1 1     |  3  | 推挽输出(50MHz)
//              
//      ||      0 1     0 1     |  5  | 开漏输出(10MHz)
//      ||      0 1     1 0     |  6  | 开漏输出(02MHz)
//      ||      0 1     1 1     |  7  | 开漏输出(02MHz)
//      -------------------------------------------------------
//      ||      1 0     0 1     |  9  | 复用推挽输出(10MHz)
//      ||      1 0     1 0     |  A  | 复用推挽输出(02MHz)
//      ||      1 0     1 1     |  B  | 复用推挽输出(50MHz)
//     
//      ||      1 1     0 1     |  D  | 复用开漏输出(10MHz)
//      ||      1 1     1 0     |  E  | 复用开漏输出(02MHz)
//      ||      1 1     1 1     |  F  | 复用开漏输出(50MHz)
//      -------------------------------------------------------
#define GPIO_MODE_INPUT_ANALOG                  (0)     // 模拟输入
#define GPIO_MODE_INPUT_FLOATING                (4)     // 浮空输入 (复位后的状态)
#define GPIO_MODE_INPUT_PULLUP                  (8)     // Px->ODR = 1 上拉输入
#define GPIO_MODE_INPUT_PULLDOWN                (8)     // Px->ODR = 0 下拉输入
#define GPIO_MODE_OUTPUT_PUSHPULL_50MHZ         (3)     // 推挽输出_50MHz
#define GPIO_MODE_OUTPUT_OPENDRAIN_50MHZ        (7)     // 开漏输出_50MHz
#define GPIO_MODE_ALTERNATE_PUSHPULL_50MHZ      (11)    // 复用功能 推挽输出_50MHz
#define GPIO_MODE_ALTERNATE_OPENDRAIN_50MHZ     (15)    // 复用功能 开漏输出_50MHz



/*******************************************************************************
        => 位设置和位清除相关寄存器
*******************************************************************************/
// 
                // 高16位（写1）， 清除GPIOx->ODR相关的位
// GPIOx->BSRR  // 低16位（写1）， 设置GPIOx->ODR相关的位
                // 高16位（保留）
// GPIOx->BRR   // 低16位（写1）， 清除GPIOx->ODR相关的位



/*******************************************************************************
        => 复用重映射和调试I/O配置寄存器
*******************************************************************************/
// AF remap and debug I/O configuration register (AFIO_MAPR)
//
//      SWJ_CFG[26:24]  // 串行线JTAG配置 (Serial wire JTAG configuration)
//           000        // 完全SWJ(JTAG-DP + SW-DP)： 复位状态
//           001        // 完全SWJ(JTAG-DP + SW-DP)， 但没有NJTRST;
//           010        // 关闭JTAG-DP， 启用SW-DP;
//           100        // 关闭JTAG-DP， 关闭SW-DP;



#endif
