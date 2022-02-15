#include <stdio.h>


// 在（0地址处并没有(TYPE*)这个结构体变量），这们写并不会引发程序的崩溃
// 编译器清楚的知道结构体成员变量的偏移位置
// 通过结构体变量首地址与偏移量定位成员变量
struct ST {
        int i;          //偏移量为（0）
        int j;          //偏移量为（4）
        char c;         //偏移量为（8）
};
#ifndef offsetof
#define offsetof(TYPE, MEMBER)  ((size_t)&((TYPE*)0)->MEMBER)
#endif



#ifndef container_of
#define container_of(ptr, type, member) ({                      \
        const typeof(((type *)0)->member) *__mptr = (ptr);      \
        (type *)((char *)__mptr - offsetof(type, member));      \
})
#endif   



// c 标准语法（逗号表达式）
//_____________________________________________________________
void method_ccc(void)
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

// gnu_c 编译器的语法扩展__({ })__
//_____________________________________________________________
void method_gnu(void)
{
        int r = ({
                int a = 1;
                int b = 2;
                a + b;
        });
        printf("r = %d\n", r);
}



// __typeof__取得变量的数据类型（int char ...）
// 它是GNU_C编译器特有的关键字
// 它只在编译期生效，用于得到变量的类型
//_____________________________________________________________
void get_variable_typeof(void)
{
        int i              = 100;
        typeof(i) j        = i;         //int j = i;
        const typeof(j) *p = &j;        //const int *p = &j;
        
        printf("sizeof(j) = %d\n", sizeof(j));  //得到变量（j）的类型
        printf("j  = %d\n", j);
        printf("*p = %d\n", *p);
}

int main(void)
{
        //method_ccc();
        //method_gnu();
        //get_variable_typeof();
        
        struct ST s = {0};
        char *pc = &s.c;
        
        struct ST *pst = container_of(pc, struct ST, c);
        
        printf("&s  = %p\n", &s);
        printf("pst = %p\n", pst);
        
        return (0);
}
