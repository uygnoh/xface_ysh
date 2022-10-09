
#include <stdio.h>

struct bit {
        int a:1;
        signed int b:1;
        unsigned int c:1;
        char d:1;
        signed char e:1;
        unsigned char f:1;
} data_a;

struct bit_b {
        unsigned char a:1;
        unsigned char b:8;
} data_b;


int main(void)
{
        printf("sizeof(data_a) = %d\n", sizeof(data_a));
        printf("sizeof(data_b) = %d\n", sizeof(data_b));
}
