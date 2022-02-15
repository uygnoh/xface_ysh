#include <stdio.h>
#include <stdlib.h>
#include "LIST.h"

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
        
        struct node LHEAD    = {0};    //创建头节点，并初始化它
        //下面二行代码， 必须定义为(struct list_head *)
        struct list_head *list   = (struct list_head *)&LHEAD;   
        struct list_head *slider = NULL;
        
        INIT_LIST_HEAD(list);
        
        //插入操作
        //_____________________________________________________
        printf("Insert begin ...\n");
        for (i = 0; i < 5; i++) {
                struct node *new_node = (struct node *)malloc(sizeof(struct node));
                new_node->value = i;
                list_add_tail((struct list_head *)new_node, list);
        }
        list_for_each(slider, list) {
                printf("%d\n", ((struct node *)slider)->value);
        }
        printf("Insert end ...\n");
        
        //删除节点操作
        //_____________________________________________________
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
// list_entry() == container_of()
//_____________________________________________________________
void list_demo_2(void)
{       
        struct node {
                int value;              //互换位置
                struct list_head head;  //互换位置
        };
        
        int i;
        
        //创建头节点，并初始化它
        struct node LHEAD = {0};
        //这里就不能强制类型转换了！
        //（因为struct list_head head;）它不是在结构体的第一个元素
        struct list_head *list = &LHEAD.head;
        struct list_head *slider = NULL;
        
        INIT_LIST_HEAD(list);
        
        //插入操作
        printf("Insert begin ...\n");
        for (i = 0; i < 5; i++) {
                struct node *nnn = (struct node *)malloc(sizeof(struct node));
                nnn->value = i;
                list_add(&nnn->head, list);
        }
        list_for_each(slider, list) {
                //打印也不能进行强制类型转换了
                printf("%d\n",  list_entry(slider, struct node, head)->value);
        }
        printf("Insert end ...\n");
        
        
        //删除节点操作
        printf("Delete begin ...\n");
        list_for_each(slider, list) {
                //打印也不能进行强制类型转换了
                struct node *nnn = list_entry(slider, struct node, head);
                if (nnn->value == 3) {
                        list_del(slider);
                        free(nnn);
                        break;
                }
        }
        list_for_each(slider, list) {
                //打印也不能进行强制类型转换了
                printf("%d\n",  list_entry(slider, struct node, head)->value);
        }
        printf("Delete end ...\n");
        
        printf("%x\n%x\n%x\n", &list, list->prev, list->next);
}


int main(void)
{
        //list_demo_1();
        list_demo_2();
        return 0;
}

