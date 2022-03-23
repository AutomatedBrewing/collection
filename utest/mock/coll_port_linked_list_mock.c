/**
 * \file        coll_port_linked_list_mock.c
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */
/* Private includes ----------------------------------------------------------*/
#include "collection_port_linked_list.h"
#include "collection_port_mem.h"

#include "slist.h"
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static sys_slist_t slist;    /* List for list of files.*/

/* Private function prototypes -----------------------------------------------*/

/* Private function bodies ---------------------------------------------------*/

/* Public function bodies ----------------------------------------------------*/
void * coll_ll_create(void)
{
    sys_slist_init(&slist);
    return (void *)&slist;
}

void coll_ll_free(void *list)
{
    sys_snode_t *node  = NULL;
    sys_snode_t *ploop = NULL;

    SYS_SLIST_FOR_EACH_NODE_SAFE(list, node, ploop)
    {
        coll_free(node);
    }
}

void coll_ll_append(void *list, void *node)
{
    sys_slist_append(list, (sys_snode_t *)node);
}

void * coll_ll_peek_head(void *list)
{
    return sys_slist_peek_head((sys_slist_t *)list);
}

void * coll_ll_peek_next(void *node)
{
    return (void *)sys_slist_peek_next((void *)node);
}
