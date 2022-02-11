//_____________________________________________________________
// 链表节点数据结构
//_____________________________________________________________
struct xLIST_ITEM {
        uint32_t                xItemValue;
        struct xLIST_ITEM       *pxNext;	
        struct xLIST_ITEM       *pxPrevious;
        void                    *pvOwner;
        void                    *pvContainer;
};
typedef struct xLIST_ITEM ListItem_t;
//_____________________________________________________________
// 链表Mini节点数据结构
//_____________________________________________________________
struct xMINI_LIST_ITEM {
        uint32_t                xItemValue;
        struct                  xLIST_ITEM *pxNext;
        struct                  xLIST_ITEM *pxPrevious;
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;
//_____________________________________________________________
// 链表数据结构
//_____________________________________________________________
typedef struct xLIST {
        uint32_t                uxNumberOfItems;
        ListItem_t              *pxIndex;
        MiniListItem_t          xListEnd;
} List_t;




//
#define listSET_LIST_ITEM_OWNER( pxListItem, pxOwner )          \
        ( ( pxListItem )->pvOwner = ( void * ) ( pxOwner ) )

//
#define listGET_LIST_ITEM_OWNER( pxListItem )                   \
        ( ( pxListItem )->pvOwner )

//
#define listSET_LIST_ITEM_VALUE( pxListItem, xValue )           \
        ( ( pxListItem )->xItemValue = ( xValue ) )

//
#define listGET_LIST_ITEM_VALUE( pxListItem )                   \
        ( ( pxListItem )->xItemValue )

//
#define listGET_ITEM_VALUE_OF_HEAD_ENTRY( pxList )              \
        ( ( ( pxList )->xListEnd ).pxNext->xItemValue )

//
#define listGET_HEAD_ENTRY( pxList )                            \
        ( ( ( pxList )->xListEnd ).pxNext )

//
#define listGET_NEXT( pxListItem )                              \
        ( ( pxListItem )->pxNext )

//
#define listGET_END_MARKER( pxList )                            \
        ( ( ListItem_t const * ) ( &( ( pxList )->xListEnd ) ) )

//
#define listLIST_IS_EMPTY( pxList )                             \
        ( ( BaseType_t ) ( ( pxList )->uxNumberOfItems == ( UBaseType_t ) 0 ) )

//
#define listCURRENT_LIST_LENGTH( pxList )                       \
        ( ( pxList )->uxNumberOfItems )

//
#define listGET_OWNER_OF_HEAD_ENTRY( pxList )                   \
        ( (&( ( pxList )->xListEnd ))->pxNext->pvOwner )

//
#define listIS_CONTAINED_WITHIN( pxList, pxListItem )           \
        ( ( BaseType_t ) ( ( pxListItem )->pvContainer == ( void * ) ( pxList ) ) )

//
#define listLIST_ITEM_CONTAINER( pxListItem )                   \
        ( ( pxListItem )->pvContainer )

//
#define listLIST_IS_INITIALISED( pxList )                       \
        ( ( pxList )->xListEnd.xItemValue == portMAX_DELAY )


//
#define listGET_OWNER_OF_NEXT_ENTRY( pxTCB, pxList )                           \
{                                                                              \
    List_t * const pxConstList = (pxList);                                     \
    (pxConstList)->pxIndex = (pxConstList)->pxIndex->pxNext;                   \
    if ((void *)(pxConstList)->pxIndex == (void *)&(( pxConstList )->xListEnd))\
    {                                                                          \
        (pxConstList)->pxIndex = (pxConstList)->pxIndex->pxNext;               \
    }                                                                          \
    (pxTCB) = (pxConstList)->pxIndex->pvOwner;                                 \
}
void vListInitialise( List_t * const pxList ) PRIVILEGED_FUNCTION;
void vListInitialiseItem( ListItem_t * const pxItem ) PRIVILEGED_FUNCTION;
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem ) PRIVILEGED_FUNCTION;
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem ) PRIVILEGED_FUNCTION;
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove ) PRIVILEGED_FUNCTION;
