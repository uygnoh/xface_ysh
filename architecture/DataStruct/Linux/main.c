//kernel/include/linux/list.h
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//_____________________________________________________________
//第1种方法
//_____________________________________________________________
void list_demo_1(void)
{
        struct node {
                struct list_head head;
                int value;
        };
        
        int i;
        
        //创建头节点，并初始化它
        struct node l = {0};
        struct list_head *list = (struct list_head *)&l;
        struct list_head *slider = NULL;
        INIT_LIST_HEAD(list);
        
        //插入操作
        printf("Insert begin ...\n");
        for (i = 0; i < 5; i++) {
                struct node *n = (struct node *)malloc(sizeof(struct node));
                n->value = i;
                list_add_tail((struct list_head *)n, list);
        }
        list_for_each(slider, list) {
                printf("%d\n", ((struct node *)slider)->value);
        }
        printf("Insert end ...\n");
        
        //删除节点操作
        printf("Delete begin ...\n");
        list_for_each(slider, list) {
                if (((struct node *)slider)->value == 3) {
                        list_del(slider);
                        free(slider);
                        break;
                }
        }
        list_for_each(slider, list) {
                printf("%d\n", ((struct node *)slider)->value);
        }
        printf("Delete end ...\n");
}

//_____________________________________________________________
//第2种方法
//_____________________________________________________________
void list_demo_2(void)
{       
        struct node {
                int value;              //互换位置
                struct list_head head;  //互换位置
        };
        
        int i;
        
        //创建头节点，并初始化它
        struct node l = {0};
        struct list_head *list = &l.head;
        struct list_head *slider = NULL;
        INIT_LIST_HEAD(list);
        
        //插入操作
        printf("Insert begin ...\n");
        for (i = 0; i < 5; i++) {
                struct node *n = (struct node *)malloc(sizeof(struct node));
                n->value = i;
                list_add(&n->head, list);
        }
        list_for_each(slider, list) {
                printf("%d\n",  list_entry(slider, struct node, head)->value);
        }
        printf("Insert end ...\n");
        
        
        //删除节点操作
        printf("Delete begin ...\n");
        list_for_each(slider, list) {
                struct node *n = list_entry(slider, struct node, head);
                if (n->value == 3) {
                        list_del(slider);
                        free(n);
                        break;
                }
        }
        list_for_each(slider, list) {
                printf("%d\n",  list_entry(slider, struct node, head)->value);
        }
        printf("Delete end ...\n");
}


int main(void)
{
        //list_demo_1();
        list_demo_2();
        struct list_head header = {&header, &header};
        //LIST_HEAD(header);
        return 0;
}

