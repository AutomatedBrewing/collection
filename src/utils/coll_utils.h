/**
 * \file        coll_utils.h
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

#ifndef SRC_UTILS_COLL_UTILS_H_
#define SRC_UTILS_COLL_UTILS_H_

/* Private includes ----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/**
 * @brief This macro is used for runtime check of some value.
 *        Can be controlled by @ref COLLECTION_CONFIG_RUNTIME_CHECKS_ENABLED.
 */
#if defined (COLLECTION_CONFIG_RUNTIME_CHECKS_ENABLED)
#define COLL_CHECKIF(expr) \
    if(expr)
#else
#define COLL_CHECKIF(...) \
    if(0)
#endif /* COLLECTION_CONFIG_RUNTIME_CHECKS_ENABLED */
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
void coll_fs_path_build(char *buffer, const char *dir, const char *name);

#endif /* SRC_UTILS_COLL_UTILS_H_ */
