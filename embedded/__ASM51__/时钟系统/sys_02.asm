/*******************************************************************************
        => 硬件初始化
*******************************************************************************/
RS      BIT     P2.5            ;//LCD1602_RS
RW      BIT     P2.6            ;//LCD1602_RW
EN      BIT     P2.7            ;//LCD1602_EN
KEY_FUN BIT     P1.0            ;//功能键
KEY_ADD BIT     P1.1            ;//加键
KEY_SUB BIT     P1.2            ;//减键
FUNCNT  EQU     38H             ;//功能键计数器

YEAR    EQU     31H             ;//年
MON     EQU     32H             ;//月
DAY     EQU     33H             ;//日
HOUR    EQU     34H             ;//时
MIN     EQU     35H             ;//分
SEC     EQU     36H             ;//秒
WEEK    EQU     37H             ;//周


        ORG     0000H           ;//程序起地址
        JMP     START           ;//跳转到START标号处
        ORG     000BH           ;//定时器0中断地址向量
        JMP     T0_INT          ;//定时器0中断服务程序入口
        ORG     0030H
START:
        MOV     SP, #60H        ;//初始化堆栈
        CALL    LCD1602_INIT    ;//初始化LCD1602液晶屏
        MOV     YEAR, #22       ;//2022年
        MOV     MON,  #12       ;//12月
        MOV     DAY,  #30       ;//30日
        MOV     HOUR, #23       ;//23时
        MOV     MIN,  #59       ;//59分
        MOV     SEC,  #55       ;//59秒
        MOV     WEEK, #7        ;//星期日（7）
        
        
        MOV     TMOD, #01H      ;//定时器（0），定时50ms
        MOV     TH0, #HIGH(65535-50000)
        MOV     TL0, #LOW(65535-50000)
        MOV     R1, #20         ;//设置定时器次数（20次）
        SETB    EA              ;//打开总中断
        SETB    ET0             ;//打开定时器0中断
        SETB    TR0             ;//启动定时器0
        
        
        CALL    DISPLAY_YEAR
        CALL    DISPLAY_MON
        CALL    DISPLAY_DAY
        CALL    DISPLAY_WEEK
        CALL    DISPLAY_HOUR
        CALL    DISPLAY_MIN
        CALL    DISPLAY_SEC



/*******************************************************************************
        => 主程序
*******************************************************************************/
MAIN:
        CALL    KEY_SCAN        ;//呼叫子程序
        JNB     TR0, MAIN       ;//JNB就是后边的位操作码为0则跳转到指定的行地址
        CALL    DISPLAY_SEC
        CALL    DISPLAY_MIN
        CALL    DISPLAY_HOUR
        CALL    DISPLAY_DAY
        CALL    DISPLAY_WEEK
        CALL    DISPLAY_MON
        CALL    DISPLAY_YEAR
        JMP     MAIN



/*******************************************************************************
        => 按键检测程序
*******************************************************************************/
KEY_SCAN:
        JNB     KEY_FUN, KEY_SCAN_F0    ;//判断功能键是否被按下，按下就转移
        JNB     KEY_ADD, KEY_SCAN_A0    ;//判断加键是否被按下，如果按下就转移
        JNB     KEY_SUB, KEY_SCAN_S0    ;//判断减键是否被按下，如果按下就转移
        RET
;//____________________________________________________________
;// 功能按键（如果功能键被按下，那么时钟就停止运行）
;//____________________________________________________________
KEY_SCAN_F0:
        CALL    DELAY_10MS
        JNB     KEY_FUN, $              ;//如果不松手，就停在本行（松手检测）
        CLR     TR0                     ;//关闭定时器（0），时钟停止
        INC     FUNCNT                  ;//功能键（加1）
        MOV     A, FUNCNT               ;//CJNE（只能使用寄存器操作）
        CJNE    A, #1, KEY_SCAN_F1      ;//if (FUNCNT != 1); goto ->KEY_SCAN_F1
        MOV     A, #0CAH                ;//LCD1602（把光标放到秒的个位）
        CALL    WRITE_CMD               ;//LCD1602（写命令）
        MOV     A, #0FH                 ;//LCD1602（光标显示并闪烁）
        CALL    WRITE_CMD               ;//LCD1602（写命令）
        RET
KEY_SCAN_F1:
        CJNE    A, #2, KEY_SCAN_F2      ;//if (FUNCNT != 2); goto ->KEY_SCAN_F2
        MOV     A, #0C7H                ;//LCD1602（把光标放到分的个位）
        CALL    WRITE_CMD               ;//LCD1602（写命令）
        RET
KEY_SCAN_F2:
        CJNE    A, #3, KEY_SCAN_F3      ;//if (FUNCNT != 3); goto ->KEY_SCAN_F3
        MOV     A, #0C4H                ;//LCD1602（把光标放到时的个位）
        CALL    WRITE_CMD               ;//LCD1602（写命令）
KEY_SCAN_F3:
        CJNE    A, #4, KEY_SCAN         ;//if (FUNCNT != 4); goto ->KEY_SCAN
        MOV     A, #0CH                 ;//LCD1602（光标不显示）
        CALL    WRITE_CMD               ;//LCD1602（写命令）
        MOV     FUN_KEY, #0             ;//标志位清零
        STEB    TR0                     ;//启动定时器（0）
        LJMP    MAIN
        RET
;//____________________________________________________________
;// 加按键
;//____________________________________________________________
KEY_SCAN_A0:    ;//秒钟加一
        JB      TR0, KEY_SCAN           ;//如果（TR0 = 1），则跳转到KEY_SCAN
        MOV     A, FUNCNT
        CJNE    A, #1, KEY_ADD_K1
        CALL    DELAY_10MS              ;//延时消抖
        JNB     KEY_ADD, $              ;//松手检测
        INC     SEC                     ;//秒钟（加一）
        MOV     A, SEC
        CJNE    A, #60, KEY_A0
        MOV     SEC, #0
        CALL    KEY_A0
        KEY_A0:
        CALL    DISPLAY_SEC
        MOV     A, #0CAH                ;//因为LCD1602初始化中有一句写（06H）的命令，
                                        ;//光标会自动后移一位，作用是把后移一位的光标拉回来
        CALL    WRITE_CMD               ;//LCD1602（写命令）
        MOV     A, #0FH
        CALL    WRITE_CMD
        RET
KEY_ADD_K1:     ;//分钟加一
        MOV     A, FUNCNT
        CJNE    A, #2, KEY_ADD_K2
        CALL    DELAY_10MS              ;//延时消抖
        JNB     KEY_ADD, $              ;//松手检测
        INC     MIN                     ;//分钟（加一）
        MOV     A, MIN
        CJNE    A, #60, KEY_A1
        MOV     MIN, #0
        CALL    KEY_A1
        KEY_A1:
        CALL    DISPLAY_MIN
        MOV     A, #0C7H                ;//因为LCD1602初始化中有一句写（06H）的命令，
                                        ;//光标会自动后移一位，作用是把后移一位的光标拉回来
        CALL    WRITE_CMD               ;//LCD1602（写命令）
        MOV     A, #0FH
        CALL    WRITE_CMD
        RET
KEY_ADD_K2:     ;//时钟加一
        MOV     A, FUNCNT
        CJNE    A, #3, KEY_ADD_K3
        CALL    DELAY_10MS              ;//延时消抖
        JNB     KEY_ADD, $              ;//松手检测
        INC     HOUR                    ;//时钟（加一）
        MOV     A, HOUR
        CJNE    A, #24, KEY_A2
        MOV     HOUR, #0
        CALL    KEY_A2
        KEY_A2:
        CALL    DISPLAY_HOUR
        MOV     A, #0C4H                ;//因为LCD1602初始化中有一句写（06H）的命令，
                                        ;//光标会自动后移一位，作用是把后移一位的光标拉回来
        CALL    WRITE_CMD               ;//LCD1602（写命令）
        MOV     A, #0FH
        CALL    WRITE_CMD
        RET
KEY_ADD_K3:
        RET
;//____________________________________________________________
;// 减按键
;//____________________________________________________________
KEY_SCAN_S0:    ;//秒钟减一
        JB      TR0, KEY_SCAN           ;//如果（TR0 = 1），则跳转到KEY_SCAN
        MOV     A, FUNCNT
        CJNE    A, #1, KEY_SUB_K1
        CALL    DELAY_10MS              ;//延时消抖
        JNB     KEY_SUB, $              ;//松手检测
        DEC     SEC                     ;//秒钟（减一）
        MOV     A, SEC
        CJNE    A, #-1, KEY_S0
        MOV     SEC, #59
        CALL    KEY_S0
        KEY_S0:
        CALL    DISPLAY_SEC
        MOV     A, #0CAH                ;//因为LCD1602初始化中有一句写（06H）的命令，
                                        ;//光标会自动后移一位，作用是把后移一位的光标拉回来
        CALL    WRITE_CMD               ;//LCD1602（写命令）
        MOV     A, #0FH
        CALL    WRITE_CMD
        RET
KEY_SUB_K1:     ;//分钟减一
        MOV     A, FUNCNT
        CJNE    A, #2, KEY_SUB_K2
        CALL    DELAY_10MS              ;//延时消抖
        JNB     KEY_SUB, $              ;//松手检测
        DEC     MIN                     ;//分钟（加一）
        MOV     A, MIN
        CJNE    A, #-1, KEY_S1
        MOV     MIN, #59
        CALL    KEY_S1
        KEY_S1:
        CALL    DISPLAY_MIN
        MOV     A, #0C7H                ;//因为LCD1602初始化中有一句写（06H）的命令，
                                        ;//光标会自动后移一位，作用是把后移一位的光标拉回来
        CALL    WRITE_CMD               ;//LCD1602（写命令）
        MOV     A, #0FH
        CALL    WRITE_CMD
        RET
KEY_SUB_K2:     ;//时钟减一
        MOV     A, FUNCNT
        CJNE    A, #3, KEY_SUB_K3
        CALL    DELAY_10MS              ;//延时消抖
        JNB     KEY_SUB, $              ;//松手检测
        DEC     HOUR                    ;//时钟（加一）
        MOV     A, HOUR
        CJNE    A, #-1, KEY_S2
        MOV     HOUR, #23
        CALL    KEY_S2
        KEY_S2:
        CALL    DISPLAY_HOUR
        MOV     A, #0C4H                ;//因为LCD1602初始化中有一句写（06H）的命令，
                                        ;//光标会自动后移一位，作用是把后移一位的光标拉回来
        CALL    WRITE_CMD               ;//LCD1602（写命令）
        MOV     A, #0FH
        CALL    WRITE_CMD
        RET
KEY_SUB_K3:
        RET



/*******************************************************************************
        => 定时器（0） 秒 分 时 日 星期 月 年
*******************************************************************************/
;//____________________________________________________________
;// 定时器（0）中断服务函数
;//____________________________________________________________
T0_INT:
        CLR     TR0                     ;//关闭定时器（0）
        MOV     TH0, #HIGH(65535-50000) ;//重新装载入初值
        MOV     TL0, #LOW(65535-50000)  ;//重新装载入初值
        SETB    TR0                     ;//打开定时器（0）
        DJNZ    R1, T0_END              ;//if (R0 != 0); goto ->T0_END
        MOV     R1, #20                 ;//1S到， （R1 = 20）
        INC     SEC                     ;//秒寄存器（加一）
        MOV     R2, SEC                 ;R2 = SEC
        CJNE    R2, #60, T0_INT         ;//if (R2 != 60); goto ->T0_INT
        MOV     SEC, #0                 ;//秒寄存器（加到60），清除秒寄存器
        JMP     LOOP_IMN                ;//跳转到分钟
LOOP_MIN:
        INC     MIN
        MOV     R2, MIN
        CJNE    R2, #60, T0_INT
        MOV     MIN, #0
        JMP     LOOP_HOUR
LOOP_HOUR:
        INC     HOUR
        MOV     R2, HOUR
        CJNZ    R2, #24, T0_INT
        MOV     HOUR, #0
        JMP     LOOP_WEEK
LOOP_WEEK:
        INC     DAY
        INC     WEEK
        MOV     R2, WEEK
        CJNZ    R2, #8, LOOP_DAY
        MOV     WEEK, #1
        JMP     LOOP_DAY
LOOP_DAY:
        MOV     R2, DAY
        CJNE    R2, #31, T0_INT
        MOV     DAY, #1
        JMP     LOOP_MON
LOOP_MON:
        INC     MON
        MOV     R2, MON
        CJNZ    R2, #13, T0_INT
        MOV     MON, #0
        JMP     LOOP_YEAR
LOOP_YEAR:
        INC     YEAR
        MOV     R2, YEAR
        CJNE    R2, #100, T0_INT
        MOV     YEAR, #0
        JMP     START    
T0_END:
        RETI



/*******************************************************************************
        => 年 月 日 时 分 秒（显示于LCD1602）
*******************************************************************************/
;//____________________________________________________________
;// 写年子函数
;//____________________________________________________________
DISPLAY_YEAR:
        MOV     A, YEAR
        MOV     B, #10
        DIV     AB              ;//A / B = （商存入A中， 余数存入B中）
        MOV     R0, A           ;//R0 = A
        MOV     A, #83H         ;//指出要向LCD1602液晶写入字符的起始位置地址
        CALL    WRITE_CMD       ;//向LCD1602液晶写入命令控制字
        MOV     A, R0           ;//A = R0
        ADD     A, #30H         ;//A = A+30H
        CALL    WRITE_DAT       ;//向LCD1602液晶写入数据（显示十位）
        MOV     A, B            ;//A = B
        ADD     A, #30H         ;//A = A+30H
        CALL    WRITE_DAT       ;//向LCD1602液晶写入数据（显示个位）
        RET
;//____________________________________________________________
;// 写月子函数
;//____________________________________________________________
DISPLAY_MON:
        MOV     A, MON
        MOV     B, #10
        DIV     AB              ;//A / B = （商存入A中， 余数存入B中）
        MOV     R0, A           ;//R0 = A
        MOV     A, #86H         ;//指出要向LCD1602液晶写入字符的起始位置地址
        CALL    WRITE_CMD       ;//向LCD1602液晶写入命令控制字
        MOV     A, R0           ;//A = R0
        ADD     A, #30H         ;//A = A+30H
        CALL    WRITE_DAT       ;//向LCD1602液晶写入数据（显示十位）
        MOV     A, B            ;//A = B
        ADD     A, #30H         ;//A = A+30H
        CALL    WRITE_DAT       ;//向LCD1602液晶写入数据（显示个位）
        RET
;//____________________________________________________________
;// 写日子函数
;//____________________________________________________________
DISPLAY_DAY:
        MOV     A, DAY
        MOV     B, #10
        DIV     AB              ;//A / B = （商存入A中， 余数存入B中）
        MOV     R0, A           ;//R0 = A
        MOV     A, #89H         ;//指出要向LCD1602液晶写入字符的起始位置地址
        CALL    WRITE_CMD       ;//向LCD1602液晶写入命令控制字
        MOV     A, R0           ;//A = R0
        ADD     A, #30H         ;//A = A+30H
        CALL    WRITE_DAT       ;//向LCD1602液晶写入数据（显示十位）
        MOV     A, B            ;//A = B
        ADD     A, #30H         ;//A = A+30H
        CALL    WRITE_DAT       ;//向LCD1602液晶写入数据（显示个位）
        RET
;//____________________________________________________________
;// 写星期子函数（因为星期，只有个位数，不需要拆分）
;//____________________________________________________________
DISPLAY_WEEK:
        MOV     A, #8CH
        CALL    WRITE_CMD
        MOV     R0, WEEK
        CJNE    R0, #1, DISPLAY_WEEK1
        MOV     DPTR, #STRING_00
        CALL    WRITE_STRING
        RET
DISPLAY_WEEK1:
        CJNE    R0, #2, DISPLAY_WEEK2
        MOV     DPTR, #STRING_01
        CALL    WRITE_STRING
        RET
DISPLAY_WEEK2:
        CJNE    R0, #3, DISPLAY_WEEK3
        MOV     DPTR, #STRING_02
        CALL    WRITE_STRING
        RET
DISPLAY_WEEK3:
        CJNE    R0, #4, DISPLAY_WEEK4
        MOV     DPTR, #STRING_03
        CALL    WRITE_STRING
        RET
DISPLAY_WEEK4:
        CJNE    R0, #5, DISPLAY_WEEK5
        MOV     DPTR, #STRING_04
        CALL    WRITE_STRING
        RET
DISPLAY_WEEK5:
        CJNE    R0, #6, DISPLAY_WEEK6
        MOV     DPTR, #STRING_05
        CALL    WRITE_STRING
        RET
DISPLAY_WEEK6:
        CJNE    R0, #7, DISPLAY_WEEK
        MOV     DPTR, #STRING_06
        CALL    WRITE_STRING
        RET

;//____________________________________________________________
;// 写小时子函数（更高效的写法）
;//____________________________________________________________
DISPLAY_HOUR:
        MOV     A, #0C3H        ;//先给出LCD1602液晶地址
        CALL    WRITE_CMD       ;//向LCD1602液晶写入命令控制字
        MOV     A, HOUR         ;//A     = HOUR
        DIV     AB              ;//A / B = （商存入A中， 余数存入B中）
        ADD     A, #30H         ;//A     = A+30H
        CALL    WRITE_DAT       ;//向LCD1602液晶写入数据（十位）
        MOV     A, B            ;//A     = B
        ADD     A, #30H         ;//A     = A+30H
        CALL    WRITE_DAT       ;///向LCD1602液晶写入数据（个位）
        RET
;//____________________________________________________________
;// 写分钟子函数（更高效的写法）
;//____________________________________________________________
DISPLAY_MIN:
        MOV     A, #0C6H        ;//先给出LCD1602液晶地址
        CALL    WRITE_CMD       ;//向LCD1602液晶写入命令控制字
        MOV     A, MIN          ;//A     = MIN
        DIV     AB              ;//A / B = （商存入A中， 余数存入B中）
        ADD     A, #30H         ;//A     = A+30H
        CALL    WRITE_DAT       ;//向LCD1602液晶写入数据（十位）
        MOV     A, B            ;//A     = B
        ADD     A, #30H         ;//A     = A+30H
        CALL    WRITE_DAT       ;///向LCD1602液晶写入数据（个位）
        RET
;//____________________________________________________________
;// 写秒钟子函数（更高效的写法）
;//____________________________________________________________
DISPLAY_SEC:
        MOV     A, #0C6H        ;//先给出LCD1602液晶地址
        CALL    WRITE_CMD       ;//向LCD1602液晶写入命令控制字
        MOV     A, SEC          ;//A     = SEC
        DIV     AB              ;//A / B = （商存入A中， 余数存入B中）
        ADD     A, #30H         ;//A     = A+30H
        CALL    WRITE_DAT       ;//向LCD1602液晶写入数据（十位）
        MOV     A, B            ;//A     = B
        ADD     A, #30H         ;//A     = A+30H
        CALL    WRITE_DAT       ;///向LCD1602液晶写入数据（个位）
        RET



/*******************************************************************************
        => LCD1602
*******************************************************************************/
;//____________________________________________________________
;//lcd1602初始化
;//____________________________________________________________
LCD1602_INIT:
        CALL    DELAY_LCD1602
        MOV     A, #38H         ;//
        CALL    WRITE_CMD
        MOV     A, #0CH         ;//
        CALL    WRITE_CMD
        MOV     A, #06H         ;//当读或写一个字符后，地址指针自动加（一）
        CALL    WRITE_CMD
        MOV     A, #01H         ;//
        CALL    WRITE_CMD
        
        
        MOV     A, #81H         ;//给出LCD1602地址
        CALL    WRITE_CMD
        MOV     A, #'2'
        CALL    WRITE_DAT
        MOV     A, #'0'
        CALL    WRITE_DAT
        MOV     A, #85H         ;//给出LCD1602地址
        CALL    WRITE_CMD
        MOV     A, #'_'
        CALL    WRITE_DAT
        MOV     A, #88H         ;//给出LCD1602地址
        CALL    WRITE_CMD
        MOV     A, #'_'
        CALL    WRITE_DAT
        
        MOV     A, #0C5H         ;//给出LCD1602地址
        CALL    WRITE_CMD
        MOV     A, #':'
        CALL    WRITE_DAT
        MOV     A, #0C8H         ;//给出LCD1602地址
        CALL    WRITE_CMD
        MOV     A, #':'
        CALL    WRITE_DAT
        RET
;//____________________________________________________________
;//lcd1602写命令
;//____________________________________________________________
WRTTE_CMD:
        CLR     RS
        CLR     RW
        CLR     EN
        MOV     P0, A
        CALL    DELAY_LCD1602
        SETB    EN
        CALL    DELAY_LCD1602
        CLR     EN
        CALL    DELAY_LCD1602
        RET
;//____________________________________________________________
;//lcd1602写数据
;//____________________________________________________________
WRTTE_DAT:
        SETB    RS
        CLR     RW
        CLR     EN
        MOV     P0, A
        CALL    DELAY_LCD1602
        SETB    EN
        CALL    DELAY_LCD1602
        CLR     EN
        CALL    DELAY_LCD1602
        RET      
;//____________________________________________________________      
;//lcd1602延时函数
;//____________________________________________________________
DELAY_LCD1602:
        MOV     R6, #14H
LOOP_80:
        MOV     R7, #19H
LOOP_90:
        DJNZ    R7, LOOP_90
        DJNZ    R6, LOOP_80
        RET        
;//____________________________________________________________           
;//lcd1602写一个字符串函数
;//____________________________________________________________
WRITE_STRING:
        MOV     R0, #3 ;//（#3）这个数字和（DB）定义的字符串相同
WRITE_STRING_80:
        CLR     A
        MOVC    A, @A+DPTR
        INC     DPTR
        CALL    WRITE_DAT
        DJNZ    R0, WRITE_STRING_80
        RET
STRING_00:      DB      "MON"           ;//星期一
STRING_01:      DB      "THU"           ;//星期二
STRING_02:      DB      "WEN"           ;//星期三
STRING_03:      DB      "THE"           ;//星期四
STRING_04:      DB      "MON"           ;//星期五
STRING_05:      DB      "MON"           ;//星期六
STRING_06:      DB      "MON"           ;//星期日
        END
