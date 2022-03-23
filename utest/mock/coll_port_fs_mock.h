/**
 * \file        coll_port_fs_mock.h
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

#ifndef UTEST_MOCK_COLL_PORT_FS_MOCK_H_
#define UTEST_MOCK_COLL_PORT_FS_MOCK_H_

/* Private includes ----------------------------------------------------------*/
#include <stdint.h>

/* Private define ------------------------------------------------------------*/
#define COLL_FS_MOCK_MAX_NO_OF_FILES    (16)   /* Maximum number of files supported. */
#define COLL_FS_MOCK_FSIZE_MAX          (1024) /* Maximum supported file size. */

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
void coll_fs_mock_init(void);

#endif /* UTEST_MOCK_COLL_PORT_FS_MOCK_H_ */
