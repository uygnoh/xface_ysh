//SRAM__写时序
ADDSET+1+DATAST+1  > 55ns
DATAST+1           > 40ns
ADDSET+1           > 0ns


//SRAM__读时序
ADDSET+1+DATAST+1 +2  > 55ns
DATAST+1           > 40ns
ADDSET+1           > 0ns


void FSMC_INIT(void)
{
        FSMC_NORSRAMTimingInitTypeDef read;             //读时序
        
        read.FSMC_AccessMode = FSMC_AccessMode_A;       //模式——A
}
