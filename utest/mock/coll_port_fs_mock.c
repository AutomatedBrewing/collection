/**
 * \file        coll_port_fs_mock.c
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

/* Private includes ----------------------------------------------------------*/
#include <stdbool.h>
#include <string.h>

#include "collection.h"
#include "collection_port_fs.h"
#include "collection_port_linked_list.h"
#include "collection_port_mem.h"

#include "coll_port_fs_mock.h"

#include "test_utils.h"
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef struct
{
    char     name[COLL_FS_FNAME_SIZE];        /* Name of the file. */
    uint8_t  content[COLL_FS_MOCK_FSIZE_MAX]; /* Content of the file. */
    uint32_t size;                            /* Size of the file. */
    bool     exists;                          /* File existance indicator. */
} coll_fs_mock_file_t;

typedef struct
{
    coll_fs_mock_file_t disk[COLL_FS_MOCK_MAX_NO_OF_FILES]; /* Disk. */
    uint32_t            file_cnt;                           /* Number of files on the disk.*/
} coll_fs_mock_cb_t;
/* Private variables ---------------------------------------------------------*/
static coll_fs_mock_cb_t cb; /* Internal control block. */

/* Private function prototypes -----------------------------------------------*/

/* Private function bodies ---------------------------------------------------*/
static coll_fs_mock_file_t * coll_fs_mock_find_by_name(const char *path)
{
    for(uint32_t file_idx = 0;
        file_idx < COLL_FS_MOCK_MAX_NO_OF_FILES;
        file_idx++)
    {
        if(0 == strncmp(cb.disk[file_idx].name, path, strlen(path)))
        {
            return &cb.disk[file_idx];
        }
    }

    return NULL;
}

static coll_fs_mock_file_t * coll_fs_mock_find_first_free(void)
{
    for(uint32_t file_idx = 0;
        file_idx < COLL_FS_MOCK_MAX_NO_OF_FILES;
        file_idx++)
    {
        if(false == cb.disk[file_idx].exists)
        {
            return &cb.disk[file_idx];
        }
    }

    return NULL;
}

/* Public function bodies ----------------------------------------------------*/
void coll_fs_mock_init(void)
{
    /* Erase whole disk.*/
    memset(&cb, 0, sizeof(cb));
}

int32_t coll_f_size_get(const char *path)
{
    coll_fs_mock_file_t *p_file = coll_fs_mock_find_by_name(path);

    if(NULL == p_file)
    {
        return -COLL_ERR_NOENT;
    }
    return (int32_t)p_file->size;
}

int32_t coll_f_cnt_get(const char *dir)
{
    uint32_t f_cnt = 0;

    for(uint32_t file_idx = 0;
        file_idx < COLL_FS_MOCK_MAX_NO_OF_FILES;
        file_idx++)
    {
        if(NULL != strstr(cb.disk[file_idx].name, dir))
        {
            f_cnt++;
        }
    }

    return (int32_t)f_cnt;
}

int32_t coll_f_read(const char *path,
                    void       *buff,
                    uint32_t   size)
{
    coll_fs_mock_file_t *p_file = coll_fs_mock_find_by_name(path);

    if(NULL == p_file)
    {
        return -COLL_ERR_NOENT;
    }
    uint32_t read_size;

    if(size > p_file->size)
    {
        read_size = p_file->size;
    }
    else
    {
        read_size = size;
    }
    memcpy(buff, p_file->content, read_size);

    return (int32_t)read_size;
}

int32_t coll_f_write(const char *path,
                     const void *buff,
                     uint32_t   size)
{
    coll_fs_mock_file_t *p_file = coll_fs_mock_find_by_name(path);

    if(NULL == p_file)
    {
        /* File does not exist. Create it now. */
        p_file = coll_fs_mock_find_first_free();

        if(NULL == p_file)
        {
            return -COLL_ERR_NOSPC;
        }
    }
    else
    {
        /* File already exist. Erase whole content. */
        return -COLL_ERR_EXIST;
    }

    if(COLL_FS_MOCK_FSIZE_MAX < size)
    {
        return -COLL_ERR_FBIG;
    }
    /* Create the file. */
    p_file->exists = true;
    strncpy(p_file->name, path, strlen(path));
    p_file->size = size;
    memcpy(p_file->content, buff, size);

    return (int32_t)size;
}

int32_t coll_f_remove(const char *path)
{
    coll_fs_mock_file_t *p_file = coll_fs_mock_find_by_name(path);

    if(NULL == p_file)
    {
        return -COLL_ERR_NOENT;
    }
    memset(p_file, 0, sizeof(coll_fs_mock_file_t));

    return COLL_OK;
}

int32_t coll_f_list_get(const char *dir, void *list)
{
    const char *p_name = NULL;

    for(uint32_t file_idx = 0;
        file_idx < COLL_FS_MOCK_MAX_NO_OF_FILES;
        file_idx++)
    {
        if(NULL != strstr(cb.disk[file_idx].name, dir))
        {
            coll_node_t *node = coll_alloc(sizeof(coll_node_t));

            if(NULL == node)
            {
                return -COLL_ERR_NOMEM;
            }
            /* Clear the node. */
            memset(node, 0, sizeof(coll_node_t));

            p_name = cb.disk[file_idx].name;
            p_name = coll_fs_strip_coll_prefix(p_name, dir);

            strncpy(node->f_name,
                    p_name,
                    strlen(p_name));

            coll_ll_append(list, node);
        }
    }

    return COLL_OK;
}
