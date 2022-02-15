#include <stdio.h>

//这里利用了编译器在此时不会真的访问“0”地址处的，这里仅作了个加法
// 在（0地址处并没有(TYPE*)这个结构体变量），这们写并不会引发程序的崩溃
// 编译器清楚的知道结构体成员变量的偏移位置
// 通过结构体变量首地址与偏移量定位成员变量
//我们假设结构体起始地址就是0，这样其成员的地址取出来再强制类型转换为(size_t)
//便可以表示结构体中某个成员相对于起始位置的偏移量，这是一种很巧妙的思考方式
#ifndef offsetof
#define offsetof(TYPE, MEMBER)          ((size_t)&((TYPE *)0)->MEMBER)
#endif

struct OFFSET {
        int i;                  //偏移量为（0）
        char j;                 //偏移量为（4）
        char c;                 //偏移量为（5）
        
};

void function_00(struct OFFSET *ps)
{//这里利用了编译器在此时不会真的访问“0”地址处的，这里仅作了个加法
        int   *pi = &(ps->i);   //(unsigned int)&ps + 0(偏移量)
        char  *pj = &(ps->j);   //(unsigned int)&ps + 4(偏移量)
        char  *pc = &(ps->c);   //(unsigned int)&ps + 5(偏移量)
        
        printf("ps = %p\n", ps);
        printf("pi = %p\n", pi);
        printf("pj = %p\n", pj);
        printf("pc = %p\n", pc);
}


//计算结构体成员在结构体中的偏移量
int main(void)
{
        struct OFFSET pst   = {0};
        function_00(&pst);
        printf("__________________________________________________\n");
        function_00(NULL);
        printf("______________offsetof_macro_______________________\n");
        printf("offset i: %d\n", offsetof(struct OFFSET, i));
        printf("offset j: %d\n", offsetof(struct OFFSET, j));
        printf("offset c: %d\n", offsetof(struct OFFSET, c));
        return 0;
}
