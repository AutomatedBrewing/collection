/**
 * \file        collection_port_serializer.h
 *
 *              File description.
 *
 * \author      Kamil Lazowski
 *
 */

#ifndef SRC_PORT_COLLECTION_PORT_SERIALIZER_H_
#define SRC_PORT_COLLECTION_PORT_SERIALIZER_H_

/* Private includes ----------------------------------------------------------*/
#include <stdint.h>

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef enum
{
    COLL_SER_OK,                      /* Operation succesful.*/
    COLL_SER_ERR_INVAL,               /* Invalid parameter */
    COLL_SER_ERR_NOMEM,               /* No more memory available */
    COLL_SER_ERR_INT,                 /* Internal error. */
} coll_ser_err_t;

/**
 * @brief Function used to encode data stored in @ref content to the @ref buff.
 *        Size of encoded data is stored in @ref size.
 *
 * @param content Content to encode.
 * @param buff    Buffer used to stre the encoded content.
 * @param size    Number of bytes to allocate. It is IN/OUT param. On input
 *                user must pass size of the @ref buff to avoid out of the
 *                buffer operations.
 *                If size is sufficient, data will be written to the buffer.
 *
 * @retval COLL_SER_OK         in case of success
 *         -COLL_SER_ERR_NOMEM Destination buffer is too small.
 *         -COLL_SER_ERR_INVAL Null pointers provided.
 */
typedef coll_ser_err_t (*encode_t)(void *content,
                                   void *encoded,
                                   uint32_t *size);

/**
 * @brief Function used to decode data stored in @ref encoded to the @ref decoded.
 *        Size of encoded data is stored in @ref size.
 *
 * @param encoded         Content to decode.
 * @param encoded_size    Size of the data to decode.
 * @param decoded         Decoded data.
 *
 * @retval COLL_SER_OK         in case of success
 *         -COLL_SER_ERR_NOMEM Destination buffer is too small.
 *         -COLL_SER_ERR_INVAL Null pointers provided.
 */
typedef coll_ser_err_t (*decode_t)(const void *encoded,
                                   uint32_t encoded_size,
                                   void *decoded);

/**
 * @brief Function used to return buffer for serialization operation.
 *        It is up to the implementation to provide this buffer
 *        baased on the content that user has provided.
 *
 * @param content         Content that will be used to obtain buffer.
 *
 * @retval Pointer to the buffer.
 */
typedef void ** (*get_buff_t)(void *content);

/**
 * @brief Structure that describes the serializer.
 *
 * @param encode Method used to encode the data.
 * @param decode Method used to decode the data.
 *
 */
typedef struct
{
    encode_t   encode;
    decode_t   decode;
    get_buff_t get_buff;
} coll_ser_t;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/

#endif /* SRC_PORT_COLLECTION_PORT_SERIALIZER_H_ */
