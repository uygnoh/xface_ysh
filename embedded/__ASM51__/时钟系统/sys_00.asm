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
        CALL    DISPLAY_YEAR
        CALL    DISPLAY_MON
        CALL    DISPLAY_DAY
        CALL    DISPLAY_WEEK
        CALL    DISPLAY_HOUR
        CALL    DISPLAY_MIN
        CALL    DISPLAY_SEC
MAIN:
        JMP     $







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
        MOV     A, WEEK
        ADD     A, #30H
        CALL    WRITE_DAT
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
        MOV     R0, #16 ;//（#16）这个数字和（DB）定义的字符串相同
WRITE_STRING_00:
        CLR     A
        MOVC    A, @A+DPTR
        INC     DPTR
        CALL    WRITE_DAT
        DJNZ    R0, WRITE_STRING_00
        RET
STRING:
        DB      "0123456789ABCDEF"
        END
