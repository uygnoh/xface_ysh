/*******************************************************************************
        => 清除与平台无关的代码
                1. ({ })
                2. typeof
                3. __builtin_prefetch
                4. static inline
*******************************************************************************/
//_____________________________________________________________
//      => include/linux/types.h
//_____________________________________________________________
struct list_head {
        struct list_head *next;
        struct list_head *prev;
};

struct hlist_head {
        struct hlist_node *first;
};

struct hlist_node {
        struct hlist_node *next, **pprev;
};

//_____________________________________________________________
//      => include/linux/stddef.h
//_____________________________________________________________
#ifndef offsetof
#define offsetof(TYPE, MEMBER)          ((size_t)&((TYPE*)0)->MEMBER)
#endif

//其中offsetof()宏是通过把0地址转换为type类型的指针，
//然后去获取该结构体中member成员的指针，也就是获取了member在type结构体中的偏移量。
//最后用指针ptr减去offset，就得到type结构体的真实地址了。
#define list_entry(ptr, type, member)   \
        container_of(ptr, type, member)

#ifndef container_of
#define container_of(ptr, type, member) \
        ((type *)((char *)(ptr) - offsetof(type, member)))
#endif

//_____________________________________________________________
//      => include/linux/poison.h
//_____________________________________________________________
#define LIST_POISON1            (NULL)
#define LIST_POISON2            (NULL)

//_____________________________________________________________
//      => include/linux/prefetch.h
//_____________________________________________________________
//define prefetch(x)            __builtin_prefetch(x)
#define prefetch(x)             ((void)x)



/*******************************************************************************
        => 遍历
*******************************************************************************/
//链表节点初始化
//_____________________________________________________________
#define LIST_HEAD_INIT(name)    { &(name), &(name) }
#define LIST_HEAD(name) \
        struct list_head name = LIST_HEAD_INIT(name)
//LIST_HEAD(foo);
//struct list_head foo = { &(foo), &(foo) };
//相当于：
//      struct list_head foo;
//      foo.next = &foo;
//      foo.prev = &foo;

//正向遍历节点
//_____________________________________________________________
#define list_for_each(pos, head)                        \
        for (pos = (head)->next;                        \
                prefetch(pos->next), pos != (head);     \
                         pos = pos->next)

//反向遍历节点
//_____________________________________________________________
#define list_for_each_prev(pos, head)                   \
        for (pos = (head)->prev;                        \
                prefetch(pos->prev), pos != (head);     \
                        pos = pos->prev)

/*******************************************************************************
        => Linux内核__链表
*******************************************************************************/
/* 动态初始化 */
static void INIT_LIST_HEAD(struct list_head *list)
{
        list->next = list;
        list->prev = list;
}

//链表增加节（公共函数）
//new是要增加的节点，prev和next是相邻的节点
static void __list_add(struct list_head *new,
                               struct list_head *prev,
                               struct list_head *next)
{
        next->prev = new;
        new->next = next;
        new->prev = prev;
        prev->next = new;
}

//将新节点插入链表的头部（头插法）
//_____________________________________________________________
static void list_add(struct list_head *new, struct list_head *head)
{
        __list_add(new, head, head->next);
}

//将新节点插入链表的尾部（尾插法）
//_____________________________________________________________
static void list_add_tail(struct list_head *new, struct list_head *head)
{
        __list_add(new, head->prev, head);
}

//删除节点（公共函数）
//_____________________________________________________________
static void __list_del(struct list_head *prev, struct list_head *next)
{
        next->prev = prev;
        prev->next = next;
}

//删除节点（根据节点入口）
//_____________________________________________________________
static void list_del(struct list_head *entry)
{
        __list_del(entry->prev, entry->next);
        entry->next = LIST_POISON1;
        entry->prev = LIST_POISON2;
}
