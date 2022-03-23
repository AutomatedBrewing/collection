/**
 * \file        coll_port_serializer_mock.h
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

#ifndef UTEST_MOCK_COLL_PORT_SERIALIZER_MOCK_H_
#define UTEST_MOCK_COLL_PORT_SERIALIZER_MOCK_H_

/* Private includes ----------------------------------------------------------*/
#include "collection_port_serializer.h"
#include "serializer_pet_types.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef struct
{
    uint8_t    buff[32]; /* Buffer for encoding and decoding data. */
    struct Pet data;
} tst_pet_t;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
extern const coll_ser_t serializer;

#endif /* UTEST_MOCK_COLL_PORT_SERIALIZER_MOCK_H_ */
