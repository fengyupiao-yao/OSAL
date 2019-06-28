#ifndef __OS_TYPES_H__
#define __OS_TYPES_H__

#include <stdint.h>

typedef uint32_t os_uint32_t;
typedef int32_t os_int32_t;
typedef uint16_t os_uint16_t;
typedef int16_t os_int16_t;
typedef uint8_t os_uint8_t;
typedef int8_t os_int8_t;


//error code
typedef enum{
    OS_ERR_NO_ERROR           = 0x00,
    OS_ERR_MEM_CAP            = 0x01,
    //TODO
}os_errcode_t;



#endif  /*__OS_TYPES_H__*/