/**
 * \file        coll_utils.c
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

/* Private includes ----------------------------------------------------------*/
#include <string.h>

#include "coll_utils.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function bodies ---------------------------------------------------*/
static void coll_fs_path_enter(char *base, const char *entering_to)
{
    strcat(base, "/");
    strcat(base, entering_to);
}

static void coll_fs_create_path(char       *buff,
                                const char *mntp,
                                const char *dir_path)
{
    memcpy(buff, mntp, strlen(mntp));
    coll_fs_path_enter(buff, dir_path);
}

/* Public function bodies ----------------------------------------------------*/

void coll_fs_path_build(char       *buffer,
                        const char *dir,
                        const char *name)
{
    memset(buffer, 0, strlen(buffer));
    coll_fs_create_path(buffer, dir, name);
}
