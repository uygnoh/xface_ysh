/*******************************************************************************
        => STM32F407__SDIO__PIN__
*******************************************************************************/
+_______________________________________+
| Pin# | Name    | Description          |
|______|_________|______________________|
| 1    | CD/DAT3 | Card Detect/         |
|      |         | Data Line [Bit 3]    |
|______|_________|______________________|______PC11
| 2    | CMD     | Command/Response     |
|______|_________|______________________|______PD2
| 3    | VSS1    | Supply voltage groud |
|______|_________|______________________|
| 4    | VDD     | Supply voltage       |
|______|_________|______________________|
| 5    | CLK     | Clock                |
|______|_________|______________________|______PC12
| 6    | VSS2    | Supply voltage groud |
|______|_________|______________________|
| 7    | DAT0    | Data Line [Bit 0]    |
|______|_________|______________________|______PC8
| 8    | DAT1    | Data Line [Bit 1]    |
|______|_________|______________________|______PC9
| 9    | DAT2    | Data Line [Bit 2]    |
|______|_________|______________________|______PC10



/*******************************************************************************
        => STM32F407__SDIO__INIT__
*******************************************************************************/
1) 打开（SDIO）时钟
2) 打开（GPIOC | GPIOD）时钟
3) 设置GPIOC（8, 9, 10, 11, 12） | GPIOD（2）为复用IO功能

//Bit[10]       __SDIO__时钟分频系数控制位（0-启用时钟分频系数）
//Bit[8]        __SDIO__时钟打开（1）
//Bit[7:0]      __SDIO__时钟分频系数（0x76）__SDIOCLK/[CLKDIV+2]
//此时SDIO时钟频率为： 48000000 / (0x76 = (118+2) = 120) = 400000(400K)
*(volatile uint32_t *)(0x40012C00 + 0x04) = 0x00000176;

//Bit[1:0]      __SDIO__上电
*(volatile uint32_t *)(0x40012C00 + 0x04) |= 0x00000003;

delay_us(1000 * 10);


//发送命令__0__ (GO_IDLE_STATE bc)
sd_progress = 1;
result = send_command(0, 0, 0);
if (result != 0) return (result);


//发送命令__8__ (SEND_IF_COND bcr R7)
sd_progress = 2;
result = send_command(8, 0x155, 1);
if (result != 0) return (result);


//SD_CARD初始化
sd_progress = 3;
while (1) {
        result = card_init();
        if (result == 0) {
                printf("初始化成功\n");
                break;
        }
}


//发送命令__2__ (ALL_SEND_CTD bcr R2)
//它返回一个（128bit）的数据，
sd_progress = 4;
result = send_command(2, 0, 3);
if (result != 0) return (result);


//发送命令__3__ (SEND_RELATIVE_ADDR bcr R6)，它是一个短响应
sd_progress = 5;
result = send_command(3, 0, 1);
if (result != 0) return (result);
//save card addr（保存SD_CARD的地址信息）
tmp = *(volatile uint32_t *)(0x40012C00 + 0x14);
card_addr = tmp >> 16;


//发送命令__7__ (SELECT_CARD ac R1b)
//选择__SD_CARD__卡
sd_progress = 6;
tmp = card_addr << 16;
result = send_command(7, tmp, 1);
if (result != 0) return (result);


//发送命令__6__ (SET_BLOCKEN ac R1)
//设置块的大小（高容量SD卡，无论设置还是不设置都是（512Byte））
sd_progress = 7;
//result = send_command(16, 8, 1);
//if (result != 0) return (result);


/*_____________________________________________使用一根数据线传输数据，所以下面的不执行
//发送命令__55__ (APP_CMD ac R1)
sd_progress = 8;
tmp = card_addr << 16;
result = send_command(55, tmp, 1);
if (result != 0) return (result);

//Set data control
//SDIO_DTIMER
*(volatile uint32_t *)(0x40012C00 + 0x24) = 0xFFFFFFFF;
//SDIO_DLEN
*(volatile uint32_t *)(0x40012C00 + 0x28) = 0x08;
//SDIO_DCTRL
tmp = 0;
tmp |= (3 << 4);        //data block size 8
tmp |= (1 << 1);        //data transfer direction
tmp |= (1 << 0);        //data transfer enable
*(volatile uint32_t *)(0x40012C00 + 0x2C) = tmp


//Send application commasn__51__ (SEND_SCR adtc R1)
sd_progress = 9;
result = send_command(51, 0, 1);
if (result != 0) return (result);

//read data
sd_progress = 10;
i = 0;
while (1) {
        tmp = *(volatile uint32_t *)(0x40012C00 + 0x34);
        if ((tmp & (0x1 << 21)) != 0) {
                scr_buf[i] = *(volatile uint32_t *)(0x40012C00 + 0x80);
                i += 1;
        }
        if (i == 2) {
                break;
        }
}


//set bus width
sd_progress = 11;
tmp = card_addr << 16;
result = send_command(55, tmp, 1);
if (result != 0) return (result);


//send application command__6__ (SET_BUS_WIDTH ac R1)
sd_progress = 12;
result = send_command(6, 0x00, 1);
if (result != 0) return (result);
//____________________________________________________________________________*/


//设置__SDIO__时钟为： 24MHz
sd_progress = 13;
*(volatile uint32_t *)(0x40012C00 + 0x04) &= 0xFFFFFF00;
sd_progress = 14;
return (result);



/*******************************************************************************
                => STM32F407__SDIO__BSP__
*******************************************************************************/
//参数1：要发送命令的编号
//参数2：要发送命令的参数
//参数3：返回响应的类型（0, 2无响应， 1短响应， 3长响应）
int send_command(uint32_t index, uint32_t arg, uint32_t exp_resp)
{
        int       result = 0;
        uint32_t tmp    = 0;
        
        //SDIO_设置命令参数
        *(volatile uint32_t *)(0x40012C00 + 0x08) = arg;
        //SDIO_配置命令
        tmp  = *(volatile uint32_t *)(0x40012C00 + 0x0C);
        tmp &= 0xFFFFF800;
        
        //CPSMEN[10]__启动命令状态机__
        tmp |= (0x01 << 10);
        
        //WAITRESP[7:6]__设置命令响应的类型__
        tmp |= (exp_resp << 6);
        
        //设置命令的编号
        tmp |= (index & 0x3F);
        
        *(volatile uint32_t *)(0x40012C00 + 0x0C) = tmp;
        
        
        //等待__SD_CARD__卡返回的响应（循环读取状态寄存器的标志位）
        while (1) {
                //读取__SDIO__状态寄存器
                tmp = *(volatile uint32_t *)(0x40012C00 + 0x34)
                
                //如果这个标志位被置“1” (CTIMEOUT)
                //表示在等待响应的过程中超时
                if ((tmp & (0x01 << 2)) != 0) {
                        result = 2;
                        break;
                }
                
                //如果这个标志位被置“1” (CMDSEND)
                //表示命令传输完成，并且不带响应类型的
                if ((tmp & (0x01 << 7) != 0) {
                        result = 0;
                        break;
                }
                
                //如果这个标志位被置“1” (CMDREND)
                //成功接收到了响应，并且通过了CRC校验
                if ((tmp & (0x01 << 6) != 0) {
                        result = 0;
                        break;
                }
                
                //如果这个标志位被置“1” (CRCFAILD)
                //表示SD_Card卡返回的响应里面CRC校验失败
                if ((tmp & (0x01 << 0)) != 0) {
                        if (index == 41) {      //the CRC is always "1111111"
                                result = 0;
                        } else {
                                result = 1;
                        }
                        break;
                }
        }
        
        //Clear CMDSENT SDIO_ICR
        tmp = (0x01 << 0) | (0x01 << 2) | (0x01 << 6) | (0x01 << 7);
        *(volatile uint32_t *)(0x40012C00 + 0x38) = tmp;
        
        return (result);
}


// SD_CARD初始化
//_________________________________________________________
int card_init(void)
{
        int result = 0;
        uint32_t tmp = 0;
        
        //发送命令__55__ (APP_CMD ac R1)
        reault = send_command(55, 0, 1);
        if (result != 0) return (result);
        
        //发送应用命令__41__ (SD_SEND_OP_COND bcr R3)
        tmp |= (0x01 << 30);    //HCS(SDHC or SHXC)
        tmp |= (0x01 << 28);    //no power saving
        tmp |= 0x00FF8000;      //voltage window
        result = send_command(41, tmp, 1);
        if (result != 0) return (result);
        
        //read resp
        tmp = *(volatile uint32_t *)(0x40012C00 + 0x14);
        if ((tmp & 0x80000000) == 0) {
                result = 1;
                printf("初始化失败\n");
                return (result);
        }
        return (result);
}


//写单个数据块
//参数1：扇区的地址
//参数2：
//_________________________________________________________
int sd_write_block(uint32_t addr, unsigned char *buf)
{
        uint32_t tmp;
        int i;
        int result;
        
        //*(volatile uint32_t *)(0x40012C00 + 0x2C) = 0x00;
        
        //Clear bit(DBCKEND | DATAEND | DTIMEOUT)
        //Write 1 to (SDIO_ICR)
        //*(volatile uint32_t *)(0x40012C00 + 0x38) |= 0x01 << 8;
        *(volatile uint32_t *)(0x40012C00 + 0x38) |= 0x01 << 10;
        *(volatile uint32_t *)(0x40012C00 + 0x38) |= 0x01 << 3;
        
        //Set SDIO_DTIMER（超时时间）
        *(volatile uint32_t *)(0x40012C00 + 0x24) = 0xFFFFFFFF;
        //SDIO_DLEN（数据块长度）512Byte
        *(volatile uint32_t *)(0x40012C00 + 0x28) = 0x200;
        //SDIO_DCTRL
        tmp  = 0;
        tmp |= (9 << 4);        //data block size 512
        tmp |= (0 << 1);        //data transfer direction host to card
        tmp |= (1 << 0);        //data transfer enable
        *(volatile uint32_t *)(0x40012C00 + 0x2C) = tmp;
        
        //Send command__24__ （WRITE_BLOCK adtc R1）
        result = send_command(24, addr, 1);
        if (result != 0) return (result);
        
        for (i = 0; i < 512;) {
                //read SDIO_STA
                tmp = *(volatile uint32_t *)(0x40012C00 + 0x34);
                //test TXFIFOHE (transmit FIFO half empty)
                if ((tmp & (0x1 << 14)) != 0) {
                        *(volatile uint32_t *)(0x40012C00 + 0x80) = *(uint32_t *)(&(buf[i]));
                        i += 4;
                }
        }
        
        while (1) {
                //read SDIO_STA
                tmp = *(volatile uint32_t *)(0x40012C00 + 0x34);
                
                //DBCKEND 已发送/接收数据块(CRC校验通过)
                if ((tmp & (0x1 << 10)) != 0) {
                        break;
                }
                //DTIMEOUT
                if ((tmp & (0x1 << 3)) != 0) {
                        return (1);
                }
        }
        return (0);
}



//读单个数据块的函数
//_________________________________________________________
int sd_read_block(uint32_t addr, unsigned char *buf)
{
        int result = 0;
        int n = 0;
        int i;
        uint32_t tmp;
        
        //*(volatile uint32_t *)(0x40012C00 + 0x2C) = 0x00;
        //delay_us(1000);
        
        //Clear bit(DBCKEND | DATAEND | DTIMEOUT)
        //Write 1 to (SDIO_ICR)
        //*(volatile uint32_t *)(0x40012C00 + 0x38) |= 0x01 << 8;
        *(volatile uint32_t *)(0x40012C00 + 0x38) |= 0x01 << 10;
        *(volatile uint32_t *)(0x40012C00 + 0x38) |= 0x01 << 3;
        
        //Set SDIO_DTIMER（超时时间）
        *(volatile uint32_t *)(0x40012C00 + 0x24) = 0xFFFFFFFF;
        //SDIO_DLEN（数据块长度）512Byte
        *(volatile uint32_t *)(0x40012C00 + 0x28) = 0x200;
        //SDIO_DCTRL
        tmp  = 0;
        tmp |= (9 << 4);        //data block size 512
        tmp |= (1 << 1);        //data transfer direction card to host
        tmp |= (1 << 0);        //data transfer enable
        *(volatile uint32_t *)(0x40012C00 + 0x2C) = tmp;
        
        //Send command__17__ 
        result = send_command(17, addr, 1);
        if (result != 0) return (result);
        
        for (i = 0; i < 512;) {
                //read SDIO_STA
                tmp = *(volatile uint32_t *)(0x40012C00 + 0x34);
                if ((tmp & (0x1 << 21)) != 0) {
                        *(uint32_t *)(&(buf[i])) = *(volatile uint32_t *)(0x40012C00 + 0x80);
                        i += 4;
                }
        }
        
        while (1) {
                //read SDIO_STA
                tmp = *(volatile uint32_t *)(0x40012C00 + 0x34);
                
                //DBCKEND
                if ((tmp & (0x01 << 10)) != 0) {
                        break;
                }
                //DTIMEOUT
                if ((tmp & (0x1 << 3)) != 0) {
                        return (1);
                }
        }
        return (0);
}
