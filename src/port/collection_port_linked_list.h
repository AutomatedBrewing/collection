/**
 * \file        collection_port_linked_list.h
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

#ifndef SRC_PORT_COLLECTION_PORT_LINKED_LIST_H_
#define SRC_PORT_COLLECTION_PORT_LINKED_LIST_H_

/* Private includes ----------------------------------------------------------*/
#include <stdint.h>

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Function used to create the linked list.
 *
 * @param list Pointer to the list of the files.
 *
 * @retval Pointer to the node in case of success.
 *         NULL in case of failure.
 */
void * coll_ll_create(void);

/**
 * @brief Function used to free list of the files.
 *
 * @param list Pointer to the list of the files.
 *
 * @retval 0 on success;
 * @retval -COLL_FS_ERR_INVAL when a bad file name is given;
 * @retval <0 an other negative errno code on error.
 */
void coll_ll_free(void *list);

/**
 * @brief Function used to retrieve first node from the linked list.
 *
 * @param list Pointer to the list of the files.
 *
 * @retval Pointer to the node in case of success.
 *         NULL in case of failure.
 */
void coll_ll_append(void *list, void *node);

/**
 * @brief Function used to retrieve first node from the linked list.
 *
 * @param list Pointer to the list of the files.
 *
 * @retval Pointer to the node in case of success.
 *         NULL in case of failure.
 */
void * coll_ll_peek_head(void *list);

/**
 * @brief Function used to retrieve first node from the linked list.
 *
 * @param list Pointer to the list of the files.
 *
 * @retval Pointer to the node in case of success.
 *         NULL in case of failure.
 */
void * coll_ll_peek_next(void *node);

#endif /* SRC_PORT_COLLECTION_PORT_LINKED_LIST_H_ */
