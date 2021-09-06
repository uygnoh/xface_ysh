#include <stdio.h>

#ifndef offsetof
#define offsetof(TYPE, MEMBER)                                  \
        (size_t)(&((TYPE*)0)->MEMBER)
#endif

#ifndef container_of
#define container_of(ptr, type, member) ({                      \
        const typeof(((type *)0)->member) *__mptr = (ptr);      \
        (type *)((char *)__mptr - offsetof(type, member));      \
})
#endif   

struct stu {
        int x;
        int y;
        int z;
};

//c标准语法
void method_1(void)
{
        int a = 0;
        int b = 0;
        int r = (
                a = 1, 
                b = 2, 
                a + b
        );
        printf("r = %d\n", r);
}

//gnu_c扩展语法
void method_2(void)
{
        int r = ({
                int a = 1;
                int b = 2;
                a + b;
        });
        printf("r = %d\n", r);
}

//typeof取得变量的类型
void type_of(void)
{
        int i = 100;
        typeof(i) j = i;
        const typeof(j) *p = &j;
        
        printf("sizeof(j) = %d\n", sizeof(j));
        printf("j = %d\n", j);
        printf("*p = %d\n", *p);
}

int main(void)
{
        //method_1();
        //method_2();
        //type_of();
        
        struct stu s = {0};
        int *p = &s.y;
        
        // 取“struct stu”这个结构体的地址
        struct stu *ps = (container_of(p, struct stu, y));
        printf("&s = %p\n", &s);
        printf("ps = %p\n", ps);
        return 0;
}
