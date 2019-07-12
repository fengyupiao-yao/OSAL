#ifndef __OSAL_TYPES_H__
#define __OSAL_TYPES_H__

#include <stdint.h>

typedef uint32_t osal_uint32_t;
typedef int32_t osal_int32_t;
typedef uint16_t osal_uint16_t;
typedef int16_t osal_int16_t;
typedef uint8_t osal_uint8_t;
typedef int8_t osal_int8_t;


//error code
typedef enum{
    OSAL_ERR_NO_ERROR           = 0x00,
    OSAL_ERR_MEM_CAP            = 0x01,
    //TODO
}osal_errcode_t;



#endif  /*__OSAL_TYPES_H__*/