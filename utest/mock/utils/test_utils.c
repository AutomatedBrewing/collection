/**
 * \file        test_utils.c
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

/* Private includes ----------------------------------------------------------*/
#include "test_utils.h"
#include <string.h>

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function bodies ---------------------------------------------------*/
/* Public function bodies ----------------------------------------------------*/
const char * coll_fs_strip_coll_prefix(const char *path, const char *coll)
{
    static const char *const root = "/";

    if((path == NULL) || (coll == NULL))
    {
        return path;
    }
    /* +1 becouse we want to strit '/'. I.e
     * we don't want '/kupa.txt, but 'kupa.txt'*/
    path += strlen(coll) + 1;
    return *path ? path : root;
}
