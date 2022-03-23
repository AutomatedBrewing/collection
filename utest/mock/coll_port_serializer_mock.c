/**
 * \file        coll_port_serializer_mock.c
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

/* Private includes ----------------------------------------------------------*/
#include <stddef.h>
#include "coll_port_serializer_mock.h"

#include "serializer_pet_encode.h"
#include "serializer_pet_decode.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function bodies ---------------------------------------------------*/
static coll_ser_err_t zcbor_err_to_coll(uint_fast8_t err)
{
    switch(err)
    {
        case ZCBOR_SUCCESS:
            return COLL_SER_OK;

        case ZCBOR_ERR_NO_BACKUP_MEM:
            return -COLL_SER_ERR_NOMEM;

        case ZCBOR_ERR_NO_PAYLOAD:
            return -COLL_SER_ERR_INVAL;
    }
    return -COLL_SER_ERR_INT;
}

static coll_ser_err_t ser_encode(void *content, void *encoded, uint32_t *size)
{
    size_t    encoded_size = 0;
    tst_pet_t *p_pet       = (tst_pet_t *)content;

    /* Reasign the working buffer. */
    *size = sizeof(p_pet->buff);

    uint_fast8_t ret = cbor_encode_Pet(encoded,
                                       *size,
                                       &p_pet->data,
                                       &encoded_size);

    *size = (uint32_t)encoded_size;

    return zcbor_err_to_coll(ret);
}

static coll_ser_err_t ser_decode(const void *encoded,
                                 uint32_t encoded_size,
                                 void *decoded)
{
    size_t       decoded_size = 0;
    tst_pet_t    *p_pet       = (tst_pet_t *)decoded;

    uint_fast8_t ret = cbor_decode_Pet(encoded,
                                       (size_t)encoded_size,
                                       &p_pet->data,
                                       &decoded_size);

    if(decoded_size != encoded_size)
    {
        return -COLL_SER_ERR_INT;
    }
    return zcbor_err_to_coll(ret);
}

static void ** get_buff(void *content)
{
    tst_pet_t *p_pet = (tst_pet_t *)content;

    return (void **)p_pet->buff;
}
/* Public function bodies ----------------------------------------------------*/
const coll_ser_t serializer =
{
    .encode   = ser_encode,
    .decode   = ser_decode,
    .get_buff = get_buff,
};
