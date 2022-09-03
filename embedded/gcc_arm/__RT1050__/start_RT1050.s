        // 指令，指定当前文件保持堆栈8字节对齐
        PRESEVRVE8
        
        // 告诉汇编器下面是32位的Thumb指令
        THUMB
        
        
        // 定义一个数据段（RESET）
        // 中断向量表定义，实际上是在CODE区（假设RT1050从norFLASH启动，则
        // 中断向量表起始地址为FLASH指定的起始地址）
        // Vector Table Mapped to Address 0 at Reset
        // 定义一块块数据段<DATA>，只可读<READONLY>，默认是<READWRITE>，段名“RESET”
        AREA            RESET, DATA, READONLY
        
        
        // EXPORT 在程序中声明一个全局的标号_Vectors，标号可在其它文件中引用
        EXPORT          __Vectors
        // EXPORT 在程序中声明一个全局的标号_Vectors_End，标号可在其它文件中引用
        EXPORT          __Vectors_End
        // EXPORT 在程序中声明一个全局的标号_Vectors_Size，标号可在其它文件中引用
        EXPORT          __Vectors_Size
        
        
        // IMPORT 伪指令用于通知编译器要使用的标号在其它的源文件定义，
        // 这里导入的是栈地址（在分散加载文件中）
        IMPORT          |Image$$ARM_LIB_STACK$$ZI$$Limit|
        
        
        
        // 中断向量表入口地址
        // DCD 用于分配一片连续的字存储单元并用指定的数据初始化
        // 该物理地址值存储__initial_sp所表示的地址值，即 __Vectors 标号所表示的值
        __Vectors
                DCD     |Image$$ARM_LIB_STACK$$ZI$$Limit|       // Top of Stack
                DCD     Reset_Handler                           // 复位向量地址
                DCD     NMI_Handler                             // 不可屏蔽中断
                DCD     HardFault_Handler                       // 
                ......
                DCD     DefaultISR                              // 253
                DCD     DefaultISR                              // 254
                DCD     0xFFFFFFFF                              // Reserved for user
        __Vectors_End                                           // 中断向量表结束地址
        
        
        
        // 得到中断向量表大小
        __Vectors_Size  EQU     __Vectors_End - __Vectors
        
        
        
        // 定义一个代码段，只读，段名是 .text
        // |.text| 用于表示由 C编译程序产生的代码段，或用于以某种方式与C库关联的代码段
        AREA            |.text|, CODE, READONLY
        
        
        
        // Reset_Handler
        // 利用 PROC ENDP 这一对伪指令标记程序开始，结束，把程序分为若干个过程
        // 【WEAK】声明其它的同名标号优先于该标号，如果外部声明了这个标号，调用外部对应的函数
        // SystemInit   系统初始化
        // __main       为运行时提供的函数，完成栈，堆的初始化等工作
        Reset_Handler   PROC
                EXPRORT         Reset_Handler           [WEAR]
                IMPORT          SystemInit
                IMPORT          __main
                CPSID           I
                
                
                // 中断向量表偏移地址默认为【0x00000000】
                // 加载中断向量表偏移寄存器地址到R0中-VTOR
                LDR             R0, =0xE000ED08
                // 加载向量表起始地址到R1中
                LDR             R1, =__Vectors
                // 存储中断向量表的起始地址到中断向量表的偏移寄存器中
                STR             R1, [R0]
                
                
                // 加载栈指针到R2
                // 更新MSP栈地址为R2的值
                LDR             R2, [R1]
                MSR             MSP, R2
                
                
                // SystemInit()
                LDR             R0, =SystemInit
                BLX             R0
                // 打开中断
                CPSIE           I
                
                
                // 调用__main不需要返回，最终调用 main
                LDR             R0, =__main
                BX              R0 
        ENDP
        
        
        
        
        // __main 解密
                // C Library初始化经及分散加载的工作是在__main()中完成的
                // __main()中运行的具体代码会根据不同的工程配置以及用户程序的不同有细微改变
                // Keil版本的变更也会导致__main()中运行代码发生改变，但很细微
        // C程序的内存排布
                // 栈的作用是：局部变量，函数调用，函数形参等的开销
                // 堆的作用是：动态内存分配
                // C语言运行必须要有堆栈的环境，因此需要在程序一开始设置好堆栈，以便运行C
                        __main()
                            |
                            |________scatterload()      // 分散加载
                                        |
                                        |
                                        |
                                        V
__scatterload_copy() <------> __scatterload_null() <------> __scatterload_zeroinit()
                                        |
                                        |
                                        |
                                        V               // C运行环境以及C Library初始化
                                  __rt_entry()  ------> __rt_entry_li()
                                                                |
                                                                |
                                                                |
                   ._____________ __rt_lib_init() <--------------
                   |
                   |
                   |
                   V
        __rt_lib_init_fp_1() ------> _fp_init() ------> __fplib_config_fpu_vfp()
                                                                |
                                                                |
                                                                |
                                                                V
                           __rt_entry_main() <------ __rt_lib_init_alloca
                                    |
                                    |
                                    |
                                    V
                                  main()

                
                
                
