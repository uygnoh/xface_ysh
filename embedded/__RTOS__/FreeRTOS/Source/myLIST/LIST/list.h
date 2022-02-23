#ifndef __LIST_H__
#define __LIST_H__
#include "stm32f1xx_hal.h"

#define MAX_VALUE		0x7fffffff

struct list_item {
	uint32_t item_value;	//辅助值，用于帮助节点做顺序排列
	struct list_item *next;	//指向链表下一个节点
	struct list_item *prev;	//指向链表前一个节点
	void *owner;		//指向拥有该节点的内核对象，通常是TCB
	void *container;	//指向该节点所在的链表，通常指向链表的根节点
};
typedef struct list_item list_item_t;

struct mini_list_item {
	uint32_t item_value;	//辅助值，用于帮助节点做顺序排列
	struct list_item *next;	//指向链表下一个节点
	struct list_item *prev;	//指向链表前一个节点
};
typedef struct mini_list_item mini_list_item_t;

struct list {
	uint32_t item_counter;	//链表节点计数器
	struct list_item *index;//链表节点索引指针
	struct mini_list_item end;//链表最后一个节点
};
typedef struct list list_t;

//设置节点的拥有者，通常是指任务控制块TCB
#define SET_LIST_ITEM_OWNER(item, owners)\
	((item)->owner = (void *)(owners))

//获得节点的拥有者
#define GET_LIST_ITEM_OWNER(item)\
	((item)->owner)

//设置节点排序辅助值
#define SET_LIST_ITEM_VALUE(item, value)\
	((item)->item_value = (value))

//获得节点排序辅助值 
#define GET_LIST_ITEM_VALUE(item)\
	((item)->item_value)

//获得链表节点头的排序辅助值
#define GET_ITEM_VALUE_OF_HEAD_ENTRY(list)\
	(((list)->end).next->item_value)

//获得链表的入口节点
#define GET_HEAD_ENTRY(list)\
	(((list)->end).next)

//获得节点的下一个节点
#define GET_NEXT(item)\
	((item)->next)

//获得链表最后一个节点
#define GET_END_MARKER(list)\
	((item_t const *)(&((list)->end)))

//判断链表是否为空
#define LIST_IS_EMPTY(list)\
	((uint32_t)((list)->item_counter == (uint32_t)0) ? TRUE : FALSE )

//获得链表的节点数
#define CURRENT_LIST_LENGTH(list)\
	((list)->item_counter)

//获得链表下一个节点的OWNER, 即TCB
#define GET_OWNER_OF_NEXT_ENTRY(tcb, list)					\
{										\
	list_t *const const_list = (list);					\
	(const_list)->index = (const_list)->index->next;			\
	if ((void *)(const_list)->index == (void *)&((const_list)->end))	\
		(const_list)->index = (const_list)->index->next;		\
	(tcb) = (const_list)->index->owner;					\
}

void list_item_initialize(list_item_t *const item);
void list_initialize(list_t *const list);
void list_insert_end(list_t *const list, list_item_t *const new_item);
void list_insert(list_t *const list, list_item_t *const new_item);
uint32_t list_remove(list_item_t *const remove_item);
#endif
