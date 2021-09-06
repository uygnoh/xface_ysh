#include <stdio.h>
#include <stdlib.h>

typedef void (*PtrFunA)(void);  /* 声明一个函数指针类型 */
typedef void (*PtrFunB)(int);   /* 声明一个函数指针类型 */

void FunA();
void FunB(int n);
void usePtrFunA(PtrFunA p);
void usePtrFunB(PtrFunB p, int n);

void FunA(void) { printf("call FunA\n"); }

void FunB(int n) { printf("call FunB. n is : %d\n", n); }

/* 函数指针作为函数参数使用 */
void usePtrFunA(PtrFunA p) { p(); }

/* 函数指针作为函数参数使用 */
void usePtrFunB(PtrFunB p, int n) { p(n); }


int main(int argc, const char *argv[]) 
{
    int i;
    for (i = 0; i < argc; i++) {
		printf("%d\n", i);
    }
	
	printf("%d\n", argc);
	printf("%s\n", argv[i-1]);
	
	
        usePtrFunA(FunA);
	usePtrFunB(FunB, 80);
	
	return 0;
}




