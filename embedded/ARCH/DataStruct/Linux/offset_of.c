#include <stdio.h>

//这里利用了编译器在此时不会真的访问“0”地址处的，这里仅作了个加法
#ifndef offsetof
#define offsetof(TYPE, MEMBER)                          \
        (size_t)(&((TYPE*)0)->MEMBER)
#endif

struct stu {
        int  i;                 //偏移为 0
        int  j;                 //偏移为 4
        char c;                 //偏移为 8
};

void demo1(struct stu *ps)
{
        int  *pi = &(ps->i);    //(unsigned int)&s + 0
        int  *pj = &(ps->j);    //(unsigned int)&s + 4
        char *pc = &(ps->c);    //(unsigned int)&s + 8
        
        printf("ps = %p\n", ps);
        printf("pi = %p\n", pi);
        printf("pj = %p\n", pj);
        printf("pc = %p\n", pc);
}


//计算结构体成员在结构体中的偏移量
int main(void)
{
        struct stu s   = {0};
        demo1(&s);
        demo1(NULL);
        
        printf("offset i: %d\n", offsetof(struct stu, i));
        printf("offset j: %d\n", offsetof(struct stu, j));
        printf("offset c: %d\n", offsetof(struct stu, c));
        return 0;
}
