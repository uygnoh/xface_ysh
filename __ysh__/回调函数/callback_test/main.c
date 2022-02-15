#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
//回调函数是一种在定义的模块不运行，交给另一个模块运行的函数
//回调函数的适用条件：
//      1 模块之间互相独立， 存在着相互调用关系
//      2 两个模块处在不同的层次，为了确保单向依赖（单向调用）
//        通常在下层设置函数指针，然后在上层设置回调函数。
//回调安装函数
void callback_install(int (*ptr)(int));
void run(void);

int my_function(int i) {
        printf("记秒到时, i=%d\n", i);
        return (1024);
}


//gcc -Wall -pthread -g -o call.out main.c run.c
int main(void)
{
        callback_install(my_function);
        run();
}
