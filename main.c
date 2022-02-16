#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
        int id;
        unsigned char name;
        void (*initial)();
        void (*process)(int id, unsigned char name);
} BOOK_STRUCT_T;

void initial()
{
        printf("initializtion ...\n");
}

void process(int id, unsigned char name)
{
        printf("processing ...\n");
        printf("id = %d, name = %d, processing ...\n", id, name);
}

void array_ptr(void)
{
// (&a+1) 取数组 a 的首地址, 该地址的值加上 sizeof(a) 的值,
// 即 (&a + 5*sizeof(int)), 也就是下一个数组的首地址,显然当前指针已经越过了数组的界限
// ((int *)(&a+1)) 则是把上一步计算出来的地址, 强制转换为 int * 类型, 赋值给 ptr
// { (a+1);  a;  &a; } 的值是一样的, 但意思不一样!!!
//      a   是数组首元素的首地址, 也就是 a[0]的首地址
//      &a  是整个数组的首地址
//      a+1 是数组下一元素的首地址
        int a[5] = {1, 2, 3, 4, 5};
        int *ptr = (int *)(&a + 1);
        printf("*(a+1) = %d, *(ptr-1) = %d\n", *(a+1), *(ptr-1));
        
        printf("数组的地址为 %x\n", &a);
        printf("数组首元素的地址为 %x\n",a);
        printf("数组（&a+1）地址为 %x\n",&a+1);
}

int main(void)
{
        printf("( 结构体与指针 )_____________________________________________\n");
        BOOK_STRUCT_T book;
        BOOK_STRUCT_T *HOS;
        HOS = &book;
        //如果不定义（HOS = &book;）结构体变量
        //必需要为（HOS）这个结构体指针申请内存空间
        //否则（HOS）这个结构体指针将指向一个未知的地址空间
        //HOS = (BOOK_STRUCT_T *)malloc(sizeof(BOOK_STRUCT_T));
        HOS->id = 100;
        HOS->name = 200;
        HOS->initial = initial;
        HOS->process = process;

        printf("%d, %d\n", HOS->id, HOS->name);

        HOS->initial();
        HOS->process(HOS->id, HOS->name);
        //如果为（HOS）这个结构体指针申请了内存空间，一定要释放它
        //free(HOS);
        printf("sizeof(void *) = %d\n", sizeof(void *));


        printf("( 数组与指针 )_______________________________________________\n");
        printf("sizeof(void *) = %d\n", sizeof(void *));
        array_ptr();

        
        return (0);
}



