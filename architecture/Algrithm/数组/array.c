#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 16

struct array {
        int data[ARRAY_SIZE];
        int last;
};


//初始化，创建空的顺序表
struct array *make_empty()
{
        struct array *ptr;
        ptr = (struct array *)malloc(sizeof(struct array));
        ptr->last = -1;
        return ptr;
}

//
//查找元素的值，返回元素的下标
int find_value(struct array *ptr, int value)
{
        int index = 0;

        while (index < ARRAY_SIZE-1 && ptr->data[index] != value)
                index++;

        if (index > ARRAY_SIZE-1)
                return -1;
        else
                return index;
}

//指定位置插入新值
//插入(第pos{1<= pos <=(n+1)}个位置上插入一个值为value的新元素)
void insert_value(struct array *ptr, int pos, int value)
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

        for (i = ptr->last; i >= pos-1; i--)
                ptr->data[i+1] = ptr->data[i];

        ptr->data[pos-1] = value;
        ptr->last++;

        return;
}

//指定位置删除元素
//删除表的第pos{1<= pos <=n}个位置上的元素)
void delete_pos(struct array *ptr, int pos)
{
        int i;

        if (pos < 1 || pos > ptr->last+1) {
                printf("不存在 %d 个元素\n", pos);
                return;
        }

        for (i = pos; pos <= ptr->last; i++)
                ptr->data[i-1] = ptr->data[i];

        ptr->last--;
        return;
}



int main(int argc, char *argv[])
{
        struct array *ptr;
        ptr = make_empty();
        
        printf("元素插入数组中开始...\n");
        insert_value(ptr, 10, 1616);
        printf("ptr->data[9] = %d   ptr->last = %d\n", ptr->data[9], ptr->last);
        insert_value(ptr, 1, 123);
        printf("ptr->data[0] = %d   ptr->last = %d\n", ptr->data[0], ptr->last);
        insert_value(ptr, 2, 456);
        printf("ptr->data[1] = %d   ptr->last = %d\n", ptr->data[1], ptr->last);
        insert_value(ptr, 3, 789);
        printf("ptr->data[2] = %d   ptr->last = %d\n", ptr->data[2], ptr->last);
        insert_value(ptr, 4, 111);
        printf("ptr->data[3] = %d   ptr->last = %d\n", ptr->data[3], ptr->last);
        printf("元素插入数组中结束...\n");
        
        printf("根据数组元素值查找，并返回数组元素下标\n");
        printf("iptr->data[9]: %d\n", find_value(ptr, 1616));
        return 0;
}
