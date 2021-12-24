RS      BIT     P1.0
RW      BIT     P1.1
EN      BIT     P1.2

        ORG     0000H
        JMP     START
        ORG     0030H
START:
        MOV     SP, #60H        ;//设置堆栈地址
        CALL    LCD1602_INIT    ;//初始化lcd1602
MAIN:
        MOV     A, #80H         ;//第一行的首地址
        CALL    WRITE_CMD       ;//写入指令
        MOV     A, #'A'         ;//显示字母（A）
        CALL    WRITE_DAT       ;//定入数据
        
        MOV     A, #C0H         ;//第二行的首地址
        MOV     DPTR, #STRING   ;//把字符串数据首地址存放到（DPTR）中
        CALL    WRITE_STRING    ;//调用写字符串函数
        JMP     $



;//lcd1602初始化
;//____________________________________________________________
LCD1602_INIT:
        CALL    DELAY_5MS
        MOV     A, #38H         ;//
        CALL    WRITE_CMD
        MOV     A, #0CH         ;//
        CALL    WRITE_CMD
        MOV     A, #06H         ;//当读或写一个字符后，地址指针自动加（一）
        CALL    WRITE_CMD
        MOV     A, #01H         ;//
        CALL    WRITE_CMD
        RET

;//lcd1602写命令
;//____________________________________________________________
WRTTE_CMD:
        CLR     RS
        CLR     RW
        CLR     EN
        MOV     P0, A
        CALL    DELAY_5MS
        SETB    EN
        CALL    DELAY_5MS
        CLR     EN
        CALL    DELAY_5MS
        RET
;//lcd1602写数据
;//____________________________________________________________
WRTTE_DAT:
        SETB    RS
        CLR     RW
        CLR     EN
        MOV     P0, A
        CALL    DELAY_5MS
        SETB    EN
        CALL    DELAY_5MS
        CLR     EN
        CALL    DELAY_5MS
        RET
        
        
;//lcd1602延时函数
;//____________________________________________________________
DELAY_5MS:
        MOV     R6, #14H
LOOP_80:
        MOV     R7, #19H
LOOP_90:
        DJNZ    R7, LOOP_90
        DJNZ    R6, LOOP_80
        RET
        
              
;//lcd1602写一个字符串函数
;//____________________________________________________________
WRITE_STRING:
        MOV     R0, #16
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
