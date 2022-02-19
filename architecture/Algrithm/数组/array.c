#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 16

typedef struct {
        int data[ARRAY_SIZE];
        int last;
} ARRAY_STRUCT_T;


//初始化，创建空的顺序表
ARRAY_STRUCT_T *make_empty()
{
        ARRAY_STRUCT_T *ptr;
        ptr = (ARRAY_STRUCT_T *)malloc(sizeof(ARRAY_STRUCT_T));
        ptr->last = -1;
        return ptr;
}

//查找元素的值，返回元素的下标
int find_value(ARRAY_STRUCT_T *ptr, int value)
{
        int index = 0;
        while (index < ARRAY_SIZE-1 && ptr->data[index] != value) {
                index++;
        }    
        if (index > ARRAY_SIZE-1) {
                return -1;
        } else {
                return index;
        }           
}

//指定位置插入新值(1...)
//插入(第pos{1<= pos <= (n+1)}个位置上插入一个值为value的新元素)
void insert_value(ARRAY_STRUCT_T *ptr, int pos, int value)
{
        int i;

        if (ptr->last == ARRAY_SIZE-1) {
                printf("这个数组已满");
                return;
        }
        if (pos < 1 || pos > ARRAY_SIZE) {
                printf("插入的位置不合法");
                return;
        }

        for (i = ptr->last; i >= pos-1; i--) {
                ptr->data[i+1] = ptr->data[i];
        }
                
        ptr->data[pos-1] = value;
        ptr->last++;
        return;
}

//指定位置删除元素
//删除表的第pos{1<= pos <=n}个位置上的元素)
void delete_pos(ARRAY_STRUCT_T *ptr, int pos)
{
        int i;
        if (pos < 1 || pos > ptr->last+1) {
                printf("不存在 %d 个元素\n", pos);
                return;
        }
        for (i = pos; pos <= ptr->last; i++) {
                ptr->data[i-1] = ptr->data[i];
        }
        ptr->last--;
        return;
}



int main(int argc, char *argv[])
{
        ARRAY_STRUCT_T *ptr;
        ptr = make_empty();
        insert_value(ptr, 1, 123);
        insert_value(ptr, 2, 456);
        insert_value(ptr, 3, 789);
        delete_pos(ptr, 3);
        return 0;
}
