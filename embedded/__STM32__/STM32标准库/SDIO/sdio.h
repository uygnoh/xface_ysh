/*******************************************************************************
        => __BUS__MicroSD__线__
*******************************************************************************/
#define DATA0
#define DATA1
#define DATA2
#define DATA3
#define CLK
#define CMD

#define enume {
        FAILED = 0,
        PASSED = !FAILED
} TestStatus;

#define BLOCK_SIZE              512     //Block Size in Byte
#define NUMBER_OF_BLOCKS        10      //for multi blocks operation
#define MULTI_BUFFER_SIZE       (BLOCK_SIZE * NUMBER_OF_BLOCKS)
