#include <stdio.h>

/*******************************************************************************
        => fun_ptr__函数指针__
*******************************************************************************/
int add(int a, int b)
{
        return (a+b);
}

#define fun_ptr_00_macro        1
#if fun_ptr_00_macro
void fun_ptr_00(void)
{
        int (*fun_ptr)(int, int);
        fun_ptr = add;
        printf("函数指针: %d\n", fun_ptr(9, 9));
        printf("函数指针: %d\n", (*fun_ptr)(9, 9));
        printf("函数指针: %d\n", (*add)(9, 9));
        printf("函数指针的地址为: %p\n", *fun_ptr);
        printf("函数的地址为: %p\n", add);
        printf("函数的地址为: %p\n", *add);
        printf("函数指针: %d\n", (*add)(3, 3));
}
#endif



/*******************************************************************************
        => main
*******************************************************************************/
int main(void)
{
        fun_ptr_00();
        printf("A+B =  %d\n", add(33, 33));
        printf("A+B =  %d\n", (*add)(13, 13));
}

