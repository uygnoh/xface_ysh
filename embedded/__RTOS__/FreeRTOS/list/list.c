// 初始化链表
//______________________________________________________________________________
void vListInitialise( List_t * const pxList )
{
        //将链表索引指针指向最后一个节点
        pxList->pxIndex             = (ListItem_t *)&(pxList->xListEnd);

        //将链表最后一个节点的辅助排序值设置为最大，确保该节点就是链表的最后节点
        pxList->xListEnd.xItemValue = portMAX_DELAY;

        //将最后一个节点的next和prev指针均指向节点自身，表示链表为空
        pxList->xListEnd.pxNext     = (ListItem_t *)&(pxList->xListEnd);
        pxList->xListEnd.pxPrevious = (ListItem_t *)&(pxList->xListEnd);

        //初始化链表节点计数器为0， 表示链表为空
        pxList->uxNumberOfItems     = (UBaseType_t) 0U;
}

// 初始化链表节点
//______________________________________________________________________________
void vListInitialiseItem(ListItem_t * const pxItem)
{
        //初始化该节点所在的链表为空，表示节点还没有插入任何链表
	pxItem->pvContainer = NULL;
}

// 将节点插入链表的尾部
//______________________________________________________________________________
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem )
{
        ListItem_t * const pxIndex = pxList->pxIndex;

        pxNewListItem->pxNext       = pxIndex;
        pxNewListItem->pxPrevious   = pxIndex->pxPrevious;
        pxIndex->pxPrevious->pxNext = pxNewListItem;
        pxIndex->pxPrevious         = pxNewListItem;

        //记住该节点所在的链表
        pxNewListItem->pvContainer = (void *)pxList;
        //链表节点计数器++
        (pxList->uxNumberOfItems)++;
}

//将新节点插入指定的（链表中）
//______________________________________________________________________________
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem )
{
        ListItem_t *pxIterator;
        
        //获取插入节点的排序辅助值
        const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;
        
        //寻找节点要插入的位置
        if (xValueOfInsertion == portMAX_DELAY) {
                pxIterator = pxList->xListEnd.pxPrevious;
        } else {
                for( pxIterator = ( ListItem_t * ) &( pxList->xListEnd ); 
                        pxIterator->pxNext->xItemValue <= xValueOfInsertion; 
                                pxIterator = pxIterator->pxNext);
        }

        //根据升序排序，将节点插入
        pxNewListItem->pxNext             = pxIterator->pxNext;
        pxNewListItem->pxNext->pxPrevious = pxNewListItem;
        pxNewListItem->pxPrevious         = pxIterator;
        pxIterator->pxNext                = pxNewListItem;

        //记住该节点所在链表
        pxNewListItem->pvContainer = ( void * ) pxList;
        //链表节点计数器++
        (pxList->uxNumberOfItems)++;
}

//从节点中移出链表
//______________________________________________________________________________
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove )
{
        List_t * const pxList = (List_t *)pxItemToRemove->pvContainer;

        pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
        pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;


        if (pxList->pxIndex == pxItemToRemove) {
                pxList->pxIndex = pxItemToRemove->pxPrevious;
        }

        pxItemToRemove->pvContainer = NULL;
        (pxList->uxNumberOfItems)--;

        return pxList->uxNumberOfItems;
}


