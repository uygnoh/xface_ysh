/*******************************************************************************
        => DS18B20（单总线__数字温度传感器）
*******************************************************************************/
TEMP_FLAG       EQU     24H     ;//判断温度正负标志位
TEMP_LOW        EQU     25H     ;//
TEMP_HIGH       EQU     26H     ;//
ZUHE_HI         EQU     27H     ;//	
ZUHE_LO         EQU     28H     ;//

LCD1602_RS      BIT     P1.0    ;//
LCD1602_RW      BIT     P1.1    ;//
LCD1602_EN      BIT     P1.2    ;//
DS18B20_DQ      BIT     P1.6    ;//



/*******************************************************************************
        => DS18B20（主程序）
*******************************************************************************/
        ORG     0000H
        LJMP    START
        ORG     0030H
START:
        MOV     SP, #60H
        MOV     A, #00H
        LCALL   LCD1602_INIT    ;//LCD1602初始化
MAIN:
        LCALL   DS18B20_RESET   ;//调用DS18B20复位子程序
        MOV     A, #0CCH        ;//跳过ROM匹配命令
        LCALL   DS18B20_WRITE   ;//向DS18B20写入命令字
        MOV     A, #44H         ;//温度转换命令
        LCALL   DS18B20_WRITE   ;//向DS18B20写入命令字
        LCALL   DS18B20_RESET   ;//调用DS18B20复位子程序
        MOV     A, #0CCH        ;//跳过ROM匹配命令
        LCALL   DS18B20_WRITE   ;//向DS18B20写入命令字
        MOV     A, #0BEH        ;//读取DS18B20温度数值
        LCALL   DS18B20_WRITE   ;//向DS18B20写入命令字
        LCALL   DS18B20_READ    ;//调用DS18B20数据读取子程序
        LCALL   CONVERT_TEMP    ;//调用温度BCD码处理子程序
        LCALL   LCD1602_DISPLAY ;//调用温度显示子程序
        SJMP    MAIN



/*******************************************************************************
        => LCD1602
*******************************************************************************/
;//____________________________________________________________
;// LCD1602（初始化）
;//____________________________________________________________
LCD1602_INIT:
        ACALL   DELAY_1MS
        MOV     A,#38H                  ;//16*2显示； 5*7点阵； 8位数据
        ACALL   LCD1602_WRITE_CMD
        ACALL   DELAY_1MS
        MOV     A,#06H                  ;//移动光标
        ACALL   LCD1602_WRITE_CMD
        MOV     A,#0CH                  ;//显示开，光标关
        ACALL   LCD1602_WRITE_CMD
        MOV     A,#01H                  ;//清屏
        ACALL   LCD1602_WRITE_CMD
        MOV     A, #80H                 ;//给出LCD1602第一行的首地址
        ACALL   LCD1602_WRITE_CMD
        MOV     DPTR, #CHAR_DATA        ;//给出字符串地址
        ACALL   WRITE_STRING            ;//写字符串数据
        RET
;//____________________________________________________________
;// LCD1602（写命令）
;// LCD1602_RS=Low; LCD1602_RW=Low; D0~D7为指令码; LCD1602_EN=高脉冲有效
;//____________________________________________________________
LCD1602_WRITE_CMD:
        CLR     LCD1602_RS
        CLR     LCD1602_RW
        CLR     LCD1602_EN
        MOV     P0, A
        LCALL   DELAY_1MS
        SETB    LCD1602_EN
        LCALL   DELAY_1MS
        CLR     LCD1602_EN
        RET
;//____________________________________________________________
;// LCD1602（写数据）
;// LCD1602_RS=Hight; LCD1602_RW=Low; D0~D7为数据码; LCD1602_EN=高脉冲有效
;//____________________________________________________________
LCD1602_WRITE_DAT:
        SETB    LCD1602_RS
        CLR     LCD1602_RW
        CLR     LCD1602_EN
        MOV     P0, A
        LCALL   DELAY_1MS
        SETB    LCD1602_EN
        LCALL   DELAY_1MS
        CLR     LCD1602_EN
        RET
;//____________________________________________________________
;// LCD1602（显示温度值）
;//____________________________________________________________
LCD1602_DISPLAY:
        MOV     A, #0C6H                ;//给出显示地址
        ACALL   LCD1602_WRITE_CMD       ;//写入地址

        MOV     A, ZUHE_HI
        SWAP    A
        ANL     A, #0FH
        DA      A
        ADD     A, #30H
        ACALL   LCD1602_WRITE_DAT       ;//写入百位

        MOV     A, ZUHE_HI
        ANL     A, 0FH
        DA      A
        ADD     A, #30H
        ACALL   LCD1602_WRITE_DAT       ;//写入十位

        MOV     A, ZUHE_LO
        SWAP    A
        ANL     A, 0FH
        DA      A
        ADD     A, #30H
        ACALL   LCD1602_WRITE_DAT       ;//写入个位

        MOV     A, '.'
        ACALL   LCD1602_WRITE_DAT       ;//显示“.”

        MOV     A, ZUHE_LO
        ANL     A, #0FH
        DA      A
        ADD     A, #30H
        ACALL   LCD1602_WRITE_DAT       ;//显示小数位
        RET
	
;//____________________________________________________________
;// LCD1602（发送字符串）
;//____________________________________________________________
WRITE_STRING:
        MOV     R0, #16
STRING_00:
        CLR     A
        MOVC    A, @A+DPTR
        INC     DPTR
        ACALL   LCD1602_WRITE_DAT
        DJNZ    R0, STRING_00
        RET
CHAR_DATA:
        DB"WELCOME TO 51MCU"


	
/*******************************************************************************
        => DS18B20
*******************************************************************************/
;//____________________________________________________________
;// DS18B20（复位）
;//第零阶段： 首先主机拉高DS18B20_DQ线
;//第一阶段： 主机拉低DS18B20_DQ线（480us），呼叫DS18B20
;//第二阶段： 主机拉高DS18B20_DQ线（15us）
;//第三阶段： 等待DS18B20拉低DS18B20_DQ线
;//____________________________________________________________
DS18B20_RESET:
        SETB    DS18B20_DQ
        NOP
        CLR     DS18B20_DQ
        MOV     R0, #6BH
        MOV     R1, #04H
TSR1:	
        DJNZ    R0, $
        MOV     R0, #6BH
        DJNZ    R1, TSR1
        SETB    DS18B20_DQ
        NOP
        NOP
        NOP
        MOV     R0, #32H
TSR2:
        JNB     DS18B20_DQ, TSR3
        DJNZ    R0, TSR2
        JMP     TSR4
TSR3:
        MOV     R0, #06BH
        JMP     TSR1
TSR4:
        JMP     TSR6
TSR5:
        DJNZ    R0, $
TSR6:
        SETB    DS18B20_DQ
        RET
;//____________________________________________________________
;// DS18B20（写）
;//____________________________________________________________
DS18B20_WRITE:
        MOV     R2, #8          ;//一共8位数据
        CLR     C               ;//清零CY位（C就是CY位）
WRITE_BIT:
        CLR	DS18B20_DQ      ;//开始写入DS18B20总线要处于（复位，低电平状态）	
        MOV	R3,#07
        DJNZ	R3,$            ;//总线复位保持（16us）以上
        RRC	A               ;//把一个字节数据分成8个位循环移给（CY）
        MOV	DS18B20_DQ, C   ;//写入一位数据
        MOV	R3, #3CH
        DJNZ	R3,$            ;//等待100us
        SETB	DS18B20_DQ      ;//重新释放总线
        NOP
        DJNZ	R2, WRITE_BIT   ;//写入一下位
        SETB	DS18B20_DQ
        RET
;//____________________________________________________________
;// DS18B20（读）
;//____________________________________________________________
DS18B20_READ:
        MOV     R4, #2          ;//将温度（低位，高位）TH，TL从DS18B20中读出
        MOV     R1, #TEMP_LOW   ;//存入25H单元，26H单元
RE00:	
        MOV     R2, #8
RE01:
        CLR     CY
        SETB    DS18B20_DQ
        NOP
        NOP
        NOP
        CLR     DS18B20_DQ	
        NOP
        NOP
        NOP
        SETB    DS18B20_DQ      ;//开始释放总线
        MOV     R3, #09         ;//延时18us
        DJNZ    R3, $
        MOV     C, DS18B20_DQ   ;//从DS18B20总线读出一位
        MOV     R3, #3CH
        DJNZ    R3, $           ;//等待100us
        RRC     A               ;//把读到的数据循环移给（A）
        DJNZ    R2, RE01        ;//读下一位
        MOV     @R1, A          ;//间接寻址（R1=TEMP_LOW）
        INC     R1              ;//间接寻址（R1=TEMP_HIGHT）
        DJNZ    R4, RE00        ;//TEMP_LOW, TEMP_HIGHT已经存储了温度16位二进制值
        RET



	
	
	
/*******************************************************************************
        => BCD（码）
*******************************************************************************/
;//____________________________________________________________
;//  0    0    0    0    1    0    0    0
;//____________________________________________________________
;// 负温度是以补码的形式存储的（它要对各个位取反，然后再加一）
;//____________________________________________________________
CONVERT_TEMP:
        MOV     A, TEMP_HIGHT   ;//判断温度是否为零下
        ANL     A, #08H         ;//判断高温度值TEMP_HIGHT（第3位）
        JZ      TEMP_POSITIVE   ;//（JZ），累加器（A）为0， 则温度为正
        CLR     C
        MOV     A, TEMP_LOW     ;//TEMP_LOW二进制补码（取反，加一）
        CPL     A 
        ADD     A, #01H
        MOV     TEMP_LOW, A
        MOV     A, TEMP_HIGHT   ;//TEMP_HIGHT二进制补码（取反，加一）
        CPL     A               ;//取反就可以了，因为它是（16位同时操作）
                                ;//所以对最低位加一就可以了，因为它的低8位不可能全为1
        MOV     TEMP_FLAG, #0BH ;//负温度标志
        SJMP    TEMP_NEGATIVE
TEMP_POSITIVE:
        MOV     TEMP_FLAG, #0AH ;//正温度标志
TEMP_NEGATIVE:
        SWAP    A               ;//高4位和低4位交换
        MOV     ZUHE_HI, A      ;//ZUHE_HI中的高4位（存储了温度的高位）
        MOV     A, TEMP_LOW     ;//
        ANL	A, #0FH         ;//取出温度（低4位的小数部分）
        MOV     DPTR, #TEMPTAB  ;//使用查表法（显示小数位）
        MOVC    A, @A+DPTR
        MOV     ZUHE_LO, A       ;//ZUHE_LO的低4位 = 温度的小数部分（BCD码）
        ;//TEMP_LOW（高4位） + TEMP_HIGHT（低4位） = （温度的整数部分）
        ;//下面进行重新组合
        ;//ZUHE_HI（高4位是温度的百位，低4位是温度的十位）
        ;//ZUHE_LO（高4位是温度的个位，低4位是温度的小数位）
        MOV     A, TEMP_LOW     ;//整数部分
        ANL     A, #0F0H        ;//取出高4位（低4位移出）
        SWAP    A               ;//高4位与低4位交换
        MOV     TEMP_LOW, A     ;//
        
        MOV     A, TEMP_HIGHT   ;//取出低4位
        ANL     A, #0FH         ;//
        SWAP    A               ;//重新组合这时（A中）温度的整数部分
        ORL     A, TEMP_LOW     ;//这时（A中是温度的整数部分了）
        
        LCALL   HEX2BCD         ;//16进制转换为BCD码
        
        MOV     TEMP_LOW, A     ;//A中高4位是（十位），低4位是（个位）
        ANL     A, #0F0H        ;//取出高4位（十位）
        SWAP    A               ;//交换到低4位
        ORL     A, ZUHE_HI
        MOV     ZUHE_HI,A       ;//ZUHE_HI（低4位为“十位数的BCD码”）
        MOV     A, TEMP_LOW
        ANL     A, #0FH
        SWAP    A
        ORL     A, ZUHE_LO      
        MOV     ZUHE_LO, A      ;//ZUHE_LO（高4位为“个位数的BCD码”）
        MOV     A, R4           ;//百位存储在（R4）中
        ANL     A, #0FH
        SWAP    A
        MOV     R4, A
        MOV     A, ZUHE_HI
        ANL     A, #0FH
        ORL     A, R4
        MOV     ZUHE_HI, A      ;//ZUHE_HI（高4位为“百位数的BCD码”）
        RET
;//____________________________________________________________
;// 小数部分码表（平均划分）
;//____________________________________________________________
TEMPTAB:
	DB	00H, 00H, 01H, 01H, 02H, 03H, 03H, 04H
	DB	05H, 05H, 06H, 06H, 07H, 08H, 08H, 09H
;//____________________________________________________________
;// HEXBCD（16进制转换成BCD码）
;//____________________________________________________________
HEX2BCD:
        MOV     B, #100
        DIV     AB
        MOV     R4, A           ;//百位存储到（R4）中，余数十位和个位在（B中）
        MOV     A, #0AH         ;//0AH（十进制的10）
        XCH     A, B            ;//把A和B交换
        DIV     AB
        SWAP    A
        ORL     A,B             ;//A中高4位是十位，低4位是个位
        RET




/*******************************************************************************
        => 
*******************************************************************************/
;//____________________________________________________________
;//  延时1MS子程序
;//____________________________________________________________
DELAY_1MS:
        MOV     R6,#14H
DL8:
        MOV     R7,#19H
DL9:
        DJNZ    R7,DL9
        DJNZ    R6,DL8
        RET
        END

