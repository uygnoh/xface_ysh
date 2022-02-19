#include <stdio.h>
#include <stdlib.h>

typedef struct {
        int *array;
        int size;
} ARRAY_STRUCT_T;


ARRAY_STRUCT_T array_create(int size)
{
        ARRAY_STRUCT_T a;
        a.array = NULL;
        a.size  = size;
        a.array = (int *)malloc(sizeof(int) * a.size);
        if (a.array != NULL) {
                printf("内存申请成功！\n");
        }
        return (a);
}

void array_free(ARRAY_STRUCT_T *a)
{
        free(a->array);
        a->array = NULL;
        a->size  = 0;   
}

int array_size(const ARRAY_STRUCT_T *a)
{
        return (a->size);
}

int *array_at(ARRAY_STRUCT_T *a, int index)
{
        return &(a->array[index]);
}
int array_get(const ARRAY_STRUCT_T *a, int index)
{
        return (a->array[index]);
}

void array_set(ARRAY_STRUCT_T *a, int index, int value)
{
        a->array[index] = value;
}
void array_inflate(ARRAY_STRUCT_T *a, int more_size)
{
}


int main(int argc, char const *argv[])
{
        ARRAY_STRUCT_T a = array_create(100);
        printf("array_size = %d\n", array_size(&a));
        //*array_at(&a, 0) = 10;
        //printf("*array_at(&a, 0) = %d\n", *array_at(&a, 0));
        array_set(&a, 1, 11);
        printf("array_get(&a, 1) = %d\n", array_get(&a, 1));
}
