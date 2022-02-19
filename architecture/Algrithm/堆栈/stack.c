#include <stdio.h>


#define MAX_SIZE        5
typedef struct __node {
    int data[MAX_SIZE];
    int top;
} STACK_STRUCT_T;


#define STACK_INIT              -1
#define STACK_FULL              -2
#define STACK_EMPTY             -3
#define ERROR                   -8
#define STACK_NOT_FULL          0
#define STACK_NOT_EMPTY         0
int stack_is_full(STACK_STRUCT_T *stack);
int stack_is_empty(STACK_STRUCT_T *stack);


void push(STACK_STRUCT_T *ptr, int item)
{
        if (stack_is_full(ptr) == STACK_FULL) {
                printf("STACK_FULL\n");
                return;
        } else {
                ptr->data[++(ptr->top)] = item;   
        }
        printf("PUSH SUCESS\n");
        return;
}

int pop(STACK_STRUCT_T *ptr)
{
        if (stack_is_empty(ptr) == STACK_EMPTY) {
                printf("STACK_EMPTY\n");
                return ERROR; /* ERROR是ElementType的特殊值,标志错误 */
        } else {
                return(ptr->data[(ptr->top)--]);
        }
}


void stack_init(STACK_STRUCT_T *stack)
{
        stack->top = STACK_INIT;
}

int stack_is_full(STACK_STRUCT_T *stack)
{
        if (stack->top >= MAX_SIZE) {
                return (STACK_FULL);
        }
        return (STACK_NOT_FULL);
}

int stack_is_empty(STACK_STRUCT_T *stack)
{
        if (stack->top == STACK_INIT) {
                return (STACK_EMPTY);
        }
        return (STACK_NOT_EMPTY);
}

int main(void)
{
        int res;
        STACK_STRUCT_T stack;
        stack_init(&stack);

        push(&stack, 14);
        push(&stack, 15);
        push(&stack, 16);
        push(&stack, 17);
        res = pop(&stack);
        printf("%d\n", res);
}

