/**
 * \file        collection.h
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

#ifndef SRC_COLLECTION_H_
#define SRC_COLLECTION_H_

/* Private includes ----------------------------------------------------------*/
#include <stdint.h>

/* Private define ------------------------------------------------------------*/
#define COLL_FS_FNAME_SIZE    (32)     /* Size of the file name. */

/* Private typedef -----------------------------------------------------------*/
/** @brief Definition of the error types. */
typedef enum
{
    COLL_OK,                      /* Operation succesful.*/
    COLL_ERR_INVAL = -1,          /* Invalid parameter.
                                   * Treat it as negative one to force compiler
                                   * treating coll_err_t as signed instead
                                   * of unsigned. */
    COLL_ERR_NOTSUP,              /* Operation not supported. */
    COLL_ERR_NOSPC,               /* No space left on device */
    COLL_ERR_NOMEM,               /* No more memory available */
    COLL_ERR_NOENT,               /* No directory entry */
    COLL_ERR_EXIST,               /* Entry already exists */
    COLL_ERR_FBIG,                /* File too large */
} coll_err_t;

typedef const char    *elem_id_t;   /* Element ID type. */
typedef void          *elem_list_t; /* Element list type. */

typedef struct
{
    void *next;
    char f_name[COLL_FS_FNAME_SIZE];
} coll_node_t;

/** @brief Collection type. */
typedef struct
{
    const char *path;          /* Path to the filesystem dir, where
                                * collection is stored. */
    const void *p_serializer;  /* Pointer to the serializer structure. */
} coll_t;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Function used to add element to the collection.
 *        As a result new file will be created.
 *        Running this operation on file that already exist has no effect.
 *        Such file will not be modified.
 *
 * @param collection Pointer to desired collection.
 * @param elem_id    Element ID.
 * @param content    Pointer to the structure that user has provided (if
 *                   serializer has been registered.
 *                   Raw data buffer if serializer has not been registered.
 * @param size       Size of the @ref content buffer. This value will be
 *                   overwritten by number of bytes written to the @ref content.
 *
 * @retval COLL_OK         In case of success.
 *         -COLL_ERR_EXIST Element already exist.
 *         -COLL_ERR_INVAL Incorrect input values.
 *         -COLL_ERR_NOSPC Not enough disk space to create file.
 *         -COLL_ERR_FBIG  File too big to create.
 */
coll_err_t collection_elem_add(coll_t  * collection,
                               elem_id_t elem_id,
                               void    * content,
                               uint32_t  size);

/**
 * @brief Function used to get element from the collection.
 *
 * @param collection Pointer to desired collection.
 * @param elem_id    Element ID.
 * @param content    Pointer to the structure that user has provided (if
 *                   serializer has been registered.
 *                   Raw data buffer if serializer has not been registered.
 * @param size       Size of the @ref content buffer. This value will be
 *                   overwritten by number of bytes actually read.
 *
 * @retval COLL_OK         In case of success.
 *         -COLL_ERR_NOENT No such file.
 *         -COLL_ERR_INVAL Incorrect input values.
 *         -COLL_ERR_NOMEM Provided buffer is too small.
 */
coll_err_t collection_elem_get(coll_t   * collection,
                               elem_id_t  elem_id,
                               void     * content,
                               uint32_t * size);

/**
 * @brief Function used to remove element from the collection.
 *
 * @param collection Pointer to desired collection.
 * @param elem_id    Element ID.
 *
 * @retval COLL_OK         In case of success.
 *         -COLL_ERR_NOENT No such file.
 *         -COLL_ERR_INVAL Incorrect input values.
 */
coll_err_t collection_elem_remove(coll_t *collection, elem_id_t elem_id);

/**
 * @brief Function used to create new empty list.
 *
 * @param None.
 *
 * @retval Pointer to the list.
 *         NULL if not enough memory.
 */
elem_list_t * collection_elem_list_create(void);

/**
 * @brief Function used to free list of the files.
 *
 * @param list Pointer to the list of the files.
 *
 * @retval COLL_OK on success;
 *         -COLL_ERR_INVAL Incorrect input values.
 */
coll_err_t collection_elem_list_free(elem_list_t *list);

/**
 * @brief Function used to retrieve list of the files in desired collection.
 *        This function can dynamically allocate memory.
 *        Every list has to be freed by calling @ref collection_elem_list_free
 *        when it is not needed anymore.
 *
 * @param collection Pointer to desired collection.
 * @param list       Pointer to the list of the files.
 *
 * @retval COLL_OK on success;
 *         -COLL_ERR_NOENT No such file.
 *         -COLL_ERR_INVAL Incorrect input values.
 */
coll_err_t collection_elem_list_get(coll_t *collection, elem_list_t *list);

/**
 * @brief Function used to retrieve first node from the linked list.
 *
 * @param list Pointer to the list of the files.
 *
 * @retval Pointer to the node in case of success.
 *         NULL in case of failure.
 */
coll_node_t * collection_elem_list_peek_head(elem_list_t *list);

/**
 * @brief Function used to retrieve next node from the linked list.
 *
 * @param list Pointer to the list of the files.
 *
 * @retval Pointer to the node in case of success.
 *         NULL in case of failure.
 */
coll_node_t * collection_elem_list_peek_next(coll_node_t *node);

/**
 * @brief Function used to get number of elements in the collection.
 *
 * @param collection Pointer to desired collection.
 *
 * @retval >=0 Number of elements in the collection.
 *         -COLL_ERR_INVAL Incorrect input values.
 */
int32_t collection_elem_cnt_get(coll_t *collection);

/**
 * @brief Function used to get abslute path of element in the collection.
 *        This function does NOT check if element really exist.
 *
 * @param collection Pointer to desired collection.
 * @param elem_id    Element ID.
 * @param path       Absolute path to the element. Buffer must be provided
 *                   by the user.
 *
 * @retval COLL_OK         In case of success.
 *         -COLL_ERR_INVAL Incorrect input values.
 */
coll_err_t collection_elem_path_get(coll_t  * collection,
                                    elem_id_t elem_id,
                                    char    * path);

#endif /* SRC_COLLECTION_H_ */
