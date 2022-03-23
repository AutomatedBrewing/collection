/**
 * \file        collection_port_mem.h
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

#ifndef SRC_PORT_COLLECTION_PORT_MEM_H_
#define SRC_PORT_COLLECTION_PORT_MEM_H_

/* Private includes ----------------------------------------------------------*/
#include <stdint.h>

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Function used to allocate @size bytes of memory.
 *        This memory must be freed later using @ref coll_free().
 *
 * @param size Number of bytes to allocate.
 *
 * @retval Pointer to the allocated data.
 *         NULL in case of failure.
 */
void * coll_alloc(uint32_t size);

/**
 * @brief Function used to free memory freviously allocated by calling
 *        @ref coll_alloc().
 *
 * @param memory Pointer to previously allocated memory.
 *
 * @retval None.
 */
void coll_free(void *memory);

#endif /* SRC_PORT_COLLECTION_PORT_MEM_H_ */
