// 链表节点数据结构
struct xLIST_ITEM {   
        struct xLIST_ITEM       *pxNext;
        struct xLIST_ITEM       *pxPrevious;
        void                    *pvOwner; 
        struct xLIST            *pxContainer;
};
typedef struct xLIST_ITEM ListItem_t;


// Mini链表节点数据结构
struct xMINI_LIST_ITEM {
        TickType_t              xItemValue;
        struct xLIST_ITEM       *pxNext;
        struct xLIST_ITEM       *pxPrevious;
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;


// 链表数据结构
typedef struct xLIST {

        UBaseType_t             uxNumberOfItems;
        ListItem_t              *pxIndex; 
        MiniListItem_t          xListEnd;

} List_t;



//      => 
//_____________________________________________________________
#define listSET_LIST_ITEM_OWNER(pxListItem, pxOwner)          \
                ((pxListItem)->pvOwner = (void *)(pxOwner))


//      =>
//_____________________________________________________________
#define listGET_LIST_ITEM_OWNER(pxListItem)                   \
                ((pxListItem)->pvOwner)


//      =>
//_____________________________________________________________
#define listSET_LIST_ITEM_VALUE(pxListItem, xValue)           \
                ((pxListItem)->xItemValue = (xValue))


//      =>
//_____________________________________________________________
#define listGET_LIST_ITEM_VALUE(pxListItem)                   \
                ((pxListItem)->xItemValue)

//_____________________________________________________________
//      =>
//_____________________________________________________________
#define listGET_ITEM_VALUE_OF_HEAD_ENTRY(pxList)              \
                (((pxList)->xListEnd).pxNext->xItemValue)


//      =>
//_____________________________________________________________
#define listGET_HEAD_ENTRY( pxList )                          \
                (((pxList)->xListEnd).pxNext)

//_____________________________________________________________
//      =>
//_____________________________________________________________
#define listGET_NEXT(pxListItem)                              \
                ((pxListItem)->pxNext)


//      =>
//_____________________________________________________________
#define listGET_END_MARKER(pxList)                            \
                ((ListItem_t const *)(&((pxList)->xListEnd)))


//      =>
//_____________________________________________________________
#define listLIST_IS_EMPTY(pxList)                             \
             (((pxList)->uxNumberOfItems == (UBaseType_t)0) ? pdTRUE : pdFALSE)


//      =>
//_____________________________________________________________
#define listCURRENT_LIST_LENGTH(pxList)                       \
                ((pxList)->uxNumberOfItems)

//_____________________________________________________________
//      =>
//_____________________________________________________________
#define listGET_OWNER_OF_HEAD_ENTRY(pxList)                   \
                ((&((pxList)->xListEnd))->pxNext->pvOwner)


//      =>
//_____________________________________________________________
#define listIS_CONTAINED_WITHIN(pxList, pxListItem)           \
                (((pxListItem)->pxContainer == (pxList)) ? (pdTRUE) : (pdFALSE))


//      =>
//_____________________________________________________________
#define listLIST_ITEM_CONTAINER(pxListItem)                   \
                ((pxListItem)->pxContainer)


//      =>
//_____________________________________________________________
#define listLIST_IS_INITIALISED(pxList)                       \
                ((pxList)->xListEnd.xItemValue == portMAX_DELAY)




//      =>
//_____________________________________________________________
#define listINSERT_END(pxList, pxNewListItem)                 \
{                                                               \
        ListItem_t * const pxIndex = (pxList)->pxIndex;         \
                                                                \
        listTEST_LIST_INTEGRITY((pxList));                      \
        listTEST_LIST_ITEM_INTEGRITY((pxNewListItem));          \
                                                                \
        (pxNewListItem)->pxNext = pxIndex;                      \
        (pxNewListItem)->pxPrevious = pxIndex->pxPrevious;      \
                                                                \
        pxIndex->pxPrevious->pxNext = (pxNewListItem);          \
        pxIndex->pxPrevious = (pxNewListItem);                  \
                                                                \
        (pxNewListItem)->pxContainer = (pxList);                \
                                                                \
        ((pxList)->uxNumberOfItems)++;                          \
}


//      =>
//_____________________________________________________________
#define listREMOVE_ITEM( pxItemToRemove )                     \
{                                                                              \
        List_t * const pxList = (pxItemToRemove)->pxContainer;                 \
        (pxItemToRemove)->pxNext->pxPrevious = (pxItemToRemove)->pxPrevious;   \
        (pxItemToRemove)->pxPrevious->pxNext = (pxItemToRemove)->pxNext;       \
        if (pxList->pxIndex == (pxItemToRemove))                               \
        {                                                                      \
                pxList->pxIndex = (pxItemToRemove)->pxPrevious;                \
        }                                                                      \
                                                                               \
        (pxItemToRemove)->pxContainer = NULL;                                  \
        (pxList->uxNumberOfItems)--;                                           \
}


//      =>
//_____________________________________________________________
#define listGET_OWNER_OF_NEXT_ENTRY(pxTCB, pxList)            \
{                                                                                 \
        List_t * const pxConstList = (pxList);                                    \
        (pxConstList)->pxIndex = (pxConstList)->pxIndex->pxNext;                  \
        if ((void *)(pxConstList)->pxIndex == (void *)&((pxConstList)->xListEnd)) \
        {                                                                         \
                (pxConstList)->pxIndex = (pxConstList)->pxIndex->pxNext;          \
        }                                                                         \
        (pxTCB) = (pxConstList)->pxIndex->pvOwner;                                \
}
