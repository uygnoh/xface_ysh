/*******************************************************************************
        => 硬件初始化
*******************************************************************************/
RS      BIT     P2.5            ;//LCD1602_RS
RW      BIT     P2.6            ;//LCD1602_RW
EN      BIT     P2.7            ;//LCD1602_EN
YEAR    EQU     31H             ;//年
MON     EQU     32H             ;//月
DAY     EQU     33H             ;//日
HOUR    EQU     34H             ;//时
MIN     EQU     35H             ;//分
SEC     EQU     36H             ;//秒
WEEK    EQU     37H             ;//周


        ORG     0000H
        JMP     START
        ORG     000BH
        JMP     T0_INT
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
        SETB    EA
        SETB    ET0
        SETB    TR0
        
        
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
        CALL    DISPLAY_SEC
        CALL    DISPLAY_MIN
        CALL    DISPLAY_HOUR
        CALL    DISPLAY_DAY
        CALL    DISPLAY_WEEK
        CALL    DISPLAY_MON
        CALL    DISPLAY_YEAR
        JMP     MAIN



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
