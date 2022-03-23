/**
 * \file        coll_port_mem_mock.c
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

/* Private includes ----------------------------------------------------------*/
#include <stddef.h>
#include <stdlib.h>

#include "collection_port_mem.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function bodies ---------------------------------------------------*/
/* Public function bodies ----------------------------------------------------*/
void * coll_alloc(uint32_t size)
{
    return malloc(size);
}

void coll_free(void *memory)
{
    free(memory);
}
