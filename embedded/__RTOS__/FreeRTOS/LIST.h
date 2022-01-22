
struct xLIST_ITEM {
        uint32_t xItemValue;
        struct xLIST_ITEM *pxNext;	
        struct xLIST_ITEM *pxPrevious;
        void *pvOwner;
        void *pvContainer;
};
typedef struct xLIST_ITEM ListItem_t;

struct xMINI_LIST_ITEM {
        uint32_t xItemValue;
        struct xLIST_ITEM *pxNext;
        struct xLIST_ITEM *pxPrevious;
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;


typedef struct xLIST {
        uint32_t uxNumberOfItems;
        ListItem_t *pxIndex;
        MiniListItem_t xListEnd;
} List_t;
