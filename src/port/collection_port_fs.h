/**
 * \file        collection_port_fs.h
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

#ifndef SRC_PORT_COLLECTION_PORT_FS_H_
#define SRC_PORT_COLLECTION_PORT_FS_H_

/* Private includes ----------------------------------------------------------*/
#include <stdint.h>

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Function used to get size of the file in bytes.
 *
 * @param path Absolute path to the file in the file system.
 *
 * @retval Number of bytes occupied by file.
 *         Negative number in case of error.
 */
int32_t coll_f_size_get(const char *path);

/**
 * @brief Function used to get number of files in the collection.
 *
 * @param dir  Absolute path to the dir in the file system.
 *
 * @retval 0 on success;
 * @retval -COLL_FS_ERR_INVAL when a bad file name is given;
 * @retval <0 an other negative errno code on error.
 */
int32_t coll_f_cnt_get(const char *dir);

/**
 * @brief Function used to read @ref size number of bytes from
 *        the file to the buffer.
 *
 * @param path Absolute path to the file in the file system.
 * @param buff Pointer to the buffer.
 * @param size Amount of bytes to read.
 *
 * @retval >=0 a number of bytes read, on success;
 * @retval -COLL_FS_ERR_BADF when invoked on zfp that represents
 *          unopened/closed file;
 * @retval -COLL_FS_ERR_NOTSUP when not implemented by underlying
 *          file system driver;
 * @retval <0 a negative errno code on error.
 */
int32_t coll_f_read(const char *path, void *buff, uint32_t size);

/**
 * @brief Function used to write @ref size number of bytes to
 *        the file from the buffer.
 *
 * @param path Absolute path to the file in the file system.
 * @param buff Pointer to the buffer.
 * @param size Amount of bytes to write.
 *
 * @retval >=0 a number of bytes written, on success;
 * @retval -COLL_FS_ERR_BADF when invoked on zfp that represents
 *          unopened/closed file;
 * @retval -COLL_FS_ERR_NOTSUP when not implemented by underlying
 *          file system driver;
 * @retval <0 an other negative errno code on error.
 */
int32_t coll_f_write(const char *path, const void *buff, uint32_t size);

/**
 * @brief Function used to remove file.
 *
 * @param path Absolute path to the file in the file system.
 *
 * @retval 0 on success;
 * @retval -COLL_FS_ERR_INVAL when a bad file name is given;
 * @retval -COLL_FS_ERR_ROFS if file is read-only, or when file system
 *          has been mounted with the FS_MOUNT_FLAG_READ_ONLY flag;
 * @retval -COLL_FS_ERR_NOTSUP when not implemented by underlying
 *          file system driver;
 * @retval <0 an other negative errno code on error.
 */
int32_t coll_f_remove(const char *path);

/**
 * @brief Function used to retrieve list of the files in desired dir.
 *        This function can dynamically allocate memory.
 *        Every list has to be freed by calling @ref coll_f_list_free
 *        when it is not needed anymore.
 * @info  This implementation does not provide functions to peek nodes.
 *        User must provide them.
 *        This implementation provides methods for creating and freeing
 *        the lists.
 *
 * @param dir  Absolute path to the dir in the file system.
 * @param list Pointer to the list of the files.
 *
 * @retval 0 on success;
 * @retval -COLL_FS_ERR_INVAL when a bad file name is given;
 * @retval <0 an other negative errno code on error.
 */
int32_t coll_f_list_get(const char *dir, void *list);

#endif /* SRC_PORT_COLLECTION_PORT_FS_H_ */
