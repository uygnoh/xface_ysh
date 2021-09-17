#include <8052.h>
typedef unsigned int size_t;
 
#define LED P0_0
 
void delay(size_t t)
{
    while(t--);
}
 
void main()
{
    while(1)
    {
        LED = 0;
        delay(20000);
        LED = 1;
        delay(20000);
    }
}
