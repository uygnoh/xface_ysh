        ORG     0000H
        LJMP    MAIN
        ORG     000BH                   ;//定时器0中断服务程序入口地址
        LJMP    T0_INT                  ;//定时器0
        ORG     0030H
MAIN:
        MOV     DPTR, #TABLE
        MOV     R0, #0
        MOV     A, R0
        MOVC    A, @A+DPTR
        MOV     P0, A
        
        MOV     TMOD, #01H              ;//设置定时器0的工作方式为（方式1）
        MOV     TH0, #HIGH(65535-50000) ;//设置定时器0（高8位初值）
        MOV     TL0, #LOW(65535-50000)  ;//设置定时器0（低8位初值）
        SETB    EA                      ;//打开总中断
        SETB    ET0                     ;//打开定时器0
        SETB    TR0                     ;//启动定时器0
        MOV     R1, #20
        JMP     $


T0_INT:
        CLR     TR0
        MOV     TH0, #HIGH(65535-50000) ;//设置定时器0（高8位初值）
        MOV     TL0, #LOW(65535-50000)  ;//设置定时器0（低8位初值）
        SETB    TR0
        DJNZ    R1, T0_END
        MOV     R1, #20
        
        INC     R0
        MOV     A, R0
        MOVC    A, @A+DPTR
        MOV     P0, A
        CJNE    R0, #10, T0_INT
        MOV     R0, #0
        MoV     A, R0
        MOVC    A, @A+DPTR
        MOV     P0, A
        JMP     T0_INT
T0_END:
        RETI         
