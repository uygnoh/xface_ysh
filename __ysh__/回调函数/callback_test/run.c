#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//定义一个函数指针，在循环中运行
int (*step)(int) = NULL;

void run(void) {
        int cnt = 0;
        int result;
        while (1) {
                //有赋值才运行，（避免乱运行）
                if ((cnt) != 0) {
                        result = step(cnt);
                        printf("result = %d\n", result);
                }
                cnt++;
                sleep(1);
        }
}
//安装函数
void callback_install(int (*ptr)(int)) {
        step = ptr;
}
