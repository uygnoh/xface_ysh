#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRUCT_POINTER          1
#define ARRAY_POINTER           0

/*******************************************************************************
        => __结构体__指针__
*******************************************************************************/
typedef struct usart {
        int id;
        unsigned char name;
        void (*init)();
        void (*usart_setup)(int id, unsigned char name);
} USART_STRUCT_T;
void init(void)
{
        printf("initializtion ...\n");
}
void usart_setup(int id, unsigned char name)
{
        printf("usart ...\n");
        printf("id = %d, name = %d, usart ...\n", id, name);
}



/*******************************************************************************
        => __数组__指针__
*******************************************************************************/
void array_pointer(void)
{
// (&a+1) 取数组 a 的首地址, 该地址的值加上 sizeof(a) 的值,
// 即 (&a + 5*sizeof(int)), 也就是下一个数组的首地址,显然当前指针已经越过了数组的界限
// ((int *)(&a+1)) 则是把上一步计算出来的地址, 强制转换为 int * 类型, 赋值给 ptr
// { (a+1);  a;  &a; } 的值是一样的, 但意思不一样!!!
//      a   是数组首元素的首地址, 也就是 a[0]的首地址
//      &a  是整个数组的首地址
//      a+1 是数组下一元素的首地址
  /*    int a[5] = {1, 2, 3, 4, 5};
        int *ptr = (int *)(&a + 1);
        printf("*(a+1) = %d, *(ptr-1) = %d\n", *(a+1), *(ptr-1));
        printf("数组的地址为 %x\n", &a);
        printf("数组首元素的地址为 %x\n",a);
        printf("数组（&a+1）地址为 %x\n",&a+1);
   */
   
        int a[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        int (*p)[4];
        p = a;
        printf("  p      == %d\n",  (  p  ));
        printf(" *p      == %d\n",  ( *p  ));
        printf("**p      == %d\n",  (**p  ));
        printf(" *(*p+0) == %d\n", *( *p+0));
        printf(" *(*p+1) == %d\n", *( *p+1));
        printf(" *(*p+2) == %d\n", *( *p+2));
        printf(" *(*p+3) == %d\n", *( *p+3));
        
        
        
        printf("*(*(p + 0) + 0 ) == %d\n", *(*(p + 0) + 0 ));
        printf("*(*(p + 1) + 0 ) == %d\n", *(*(p + 1) + 0 ));
        printf("*(*(p + 2) + 0 ) == %d\n", *(*(p + 2) + 0 ));
        
        printf("*(*(a + 0) + 0 ) == %d\n", *(*(a + 0) + 0 ));
        printf("*(*(a + 1) + 0 ) == %d\n", *(*(a + 1) + 0 ));
        printf("*(*(a + 2) + 0 ) == %d\n", *(*(a + 2) + 0 ));
}



int main(void)
{
#if (STRUCT_POINTER)
        printf("( 结构体与指针 )_____________________________________________\n");
        USART_STRUCT_T  bps;
        USART_STRUCT_T *HOS;
        HOS = &bps;
        //如果不定义（HOS = &bps;）结构体变量
        //必需要为（HOS）这个结构体指针申请内存空间
        //否则（HOS）这个结构体指针将指向一个未知的地址空间
        //HOS = (USART_STRUCT_T *)malloc(sizeof(USART_STRUCT_T));
        HOS->id          = 100;
        HOS->name        = 200;
        HOS->init        = init;
        HOS->usart_setup = usart_setup;

        printf("%d, %d\n", HOS->id, HOS->name);

        HOS->init();
        HOS->usart_setup(HOS->id, HOS->name);
        //如果为（HOS）这个结构体指针申请了内存空间，一定要释放它
        //free(HOS);
        printf("sizeof(void *) = %d\n", sizeof(void *));
#endif



#if ARRAY_POINTER
        printf("( 数组与指针 )_______________________________________________\n");
        printf("sizeof(void *) = %d\n", sizeof(void *));
        array_pointer();
#endif
        
        return (0);
}



