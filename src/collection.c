/**
 * \file        collection.c
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

/* Private includes ----------------------------------------------------------*/
#include <stddef.h>

#include "collection.h"

#include "collection_port_fs.h"
#include "collection_port_linked_list.h"
#include "collection_port_serializer.h"
#include "coll_utils.h"

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function bodies ---------------------------------------------------*/

/* Public function bodies ----------------------------------------------------*/
coll_err_t collection_elem_add(coll_t    *collection,
                               elem_id_t elem_id,
                               void      *content,
                               uint32_t  size)
{
    COLL_CHECKIF(  (NULL == collection)
                || (NULL == elem_id)
                || (NULL == content)
                || (size == 0))
    {
        return -COLL_ERR_INVAL;
    }
    uint32_t write_size = 0;
    void     *buffer    = NULL;

    /* Check if serializer is provided. */
    if(NULL != collection->p_serializer)
    {
        /* Serialize the data. */
        const coll_ser_t *serializer =
            (const coll_ser_t *)collection->p_serializer;
        buffer = serializer->get_buff(content);
        coll_ser_err_t ret = serializer->encode(content,
                                                buffer,
                                                &write_size);

        if(ret != COLL_SER_OK)
        {
            return -COLL_ERR_NOTSUP;
        }
    }
    else
    {
        /* Configure write params to write raw data
         * (without serializer). */
        write_size = size;
        buffer     = content;
    }
    /* Data can be written to the file now. */
    char path[COLL_FS_FNAME_SIZE] = { 0 };

    coll_fs_path_build(path, collection->path, elem_id);

    int32_t written = coll_f_write(path, buffer, write_size);

    if(written != (int32_t)write_size)
    {
        /* Different in numbers means error. */
        return written;
    }
    return COLL_OK;
}

coll_err_t collection_elem_get(coll_t    *collection,
                               elem_id_t elem_id,
                               void      *content,
                               uint32_t  *size)
{
    COLL_CHECKIF(  (NULL == collection)
                || (NULL == elem_id)
                || (NULL == content)
                || (size == 0))
    {
        return -COLL_ERR_INVAL;
    }
    /* Data can be read from the file now. */
    char path[COLL_FS_FNAME_SIZE] = { 0 };

    coll_fs_path_build(path, collection->path, elem_id);

    int32_t fsize = coll_f_size_get(path);

    if(fsize < 0)
    {
        /* fsize carries error code. */
        return fsize;
    }

    /* Check if provided buffer has enough space. */
    if((int32_t)*size < fsize)
    {
        return -COLL_ERR_NOMEM;
    }
    /* Check if serializer is provided. */
    int32_t read = 0;

    if(NULL != collection->p_serializer)
    {
        const coll_ser_t *serializer =
            (const coll_ser_t *)collection->p_serializer;
        void             *buffer = serializer->get_buff(content);
        read = coll_f_read(path, buffer, (uint32_t)fsize);

        /* Deserialize the data. */
        coll_ser_err_t ret = serializer->decode(buffer,
                                                (uint32_t)fsize,
                                                content);

        if(ret != COLL_SER_OK)
        {
            return -COLL_ERR_NOTSUP;
        }
    }
    else
    {
        read = coll_f_read(path, content, (uint32_t)fsize);
    }

    if(read != fsize)
    {
        /* Different in numbers means error. */
        return read;
    }
    /* Override number of written bytes.*/
    *size = (uint32_t)read;

    return COLL_OK;
}

coll_err_t collection_elem_remove(coll_t    *collection,
                                  elem_id_t elem_id)
{
    COLL_CHECKIF((NULL == collection) || (NULL == elem_id))
    {
        return -COLL_ERR_INVAL;
    }

    char path[COLL_FS_FNAME_SIZE];

    coll_fs_path_build(path, collection->path, elem_id);

    return (coll_err_t)coll_f_remove(path);
}

elem_list_t * collection_elem_list_create(void)
{
    return coll_ll_create();
}

coll_err_t collection_elem_list_free(elem_list_t *list)
{
    COLL_CHECKIF(NULL == list)
    {
        return -COLL_ERR_INVAL;
    }
    coll_ll_free(list);
    return COLL_OK;
}

coll_err_t collection_elem_list_get(coll_t      *collection,
                                    elem_list_t *list)
{
    COLL_CHECKIF((NULL == collection) || (NULL == list))
    {
        return -COLL_ERR_INVAL;
    }
    return (coll_err_t)coll_f_list_get(collection->path, list);
}

coll_node_t * collection_elem_list_peek_head(elem_list_t *list)
{
    COLL_CHECKIF(NULL == list)
    {
        return NULL;
    }
    return coll_ll_peek_head(list);
}

coll_node_t * collection_elem_list_peek_next(coll_node_t *node)
{
    COLL_CHECKIF(NULL == node)
    {
        return NULL;
    }
    return coll_ll_peek_next(node);
}

int32_t collection_elem_cnt_get(coll_t *collection)
{
    COLL_CHECKIF(NULL == collection)
    {
        return -COLL_ERR_INVAL;
    }
    return (coll_err_t)coll_f_cnt_get(collection->path);
}

coll_err_t collection_elem_path_get(coll_t    *collection,
                                    elem_id_t elem_id,
                                    char      *path)
{
    COLL_CHECKIF(  (NULL == collection)
                || (NULL == elem_id)
                || (NULL == path))
    {
        return -COLL_ERR_INVAL;
    }
    coll_fs_path_build(path, collection->path, elem_id);

    return COLL_OK;
}
