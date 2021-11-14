#include <stdio.h>
#include <stdlib.h>

struct list {
        int data;
        struct list *next;
};

/* 静态链表创建实现方法
int main()
{
    struct list list1 = {1, NULL};
    struct list list2 = {2, NULL};
    struct list list3 = {1, NULL};
    
    list1.next = &list2;
    list2.next = &list3;
}
*/

//创建一个链表的头部
//它不存放任何数据
struct list *create_list()
{
        struct list *head = (struct list*)malloc(sizeof(struct list));
        head->next = NULL;
        return head;
}


//创建新的节点
struct list * create_node(int data)
{
        struct list *new_node = (struct list*)malloc(sizeof(struct list));
        new_node->data = data;
        new_node->next = NULL;
        return new_node;
}


//打印链表的数据
void print_list(struct list *head)
{
        struct list *ptr_mov = head->next;
        while (ptr_mov) {
                printf("%d", ptr_mov->data);
                ptr_mov = ptr_mov->next;
                printf("\n");
        }
}


//在链表的头节点处插入
void insert_head(struct list *head, int data)
{
        struct list *new_list = create_node(data);
        new_list->next = head->next;
        head->next = new_list;
}



//指定位置删除
void del_pos(struct list *head, int pos_dat)
{
        struct list *pos_node = head->next;
        struct list *pos_node_front = head;
        
        if (pos_node == NULL) {
                printf("无法删除链表，链表为空\n");
                return;
        }
        
        while (pos_node->data != pos_dat) {
                pos_node_front = pos_node;
                //也可以这么写pos_node = pos_node_front->next
                pos_node = pos_node->next; 
                if (pos_node == NULL) {
                        printf("未找到指定位置，无法删除\n");
                        return;
                }
        }

        pos_node_front->next = pos_node->next;
        free(pos_node);
}



int main()
{
        struct list *head = create_list();
        
        printf("链表头插法开始 ...\n");
        insert_head(head, 1);
        insert_head(head, 2);
        insert_head(head, 777);
        insert_head(head, 3);
        insert_head(head, 3);
        insert_head(head, 3);
        print_list(head);
        printf("链表头插法结束 ...\n");
        
        printf("链表删除开始 ...\n");
        del_pos(head, 3);
        print_list(head);
        printf("链表删除结束 ...\n");

}




