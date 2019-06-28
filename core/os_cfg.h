#ifndef __OS_CFG_H__
#define __OS_CFG_H__

#include "os_types.h"

#ifndef OS_FEATURE_TIME_SUPPORTED
#define OS_FEATURE_TIME_SUPPORTED         1
#endif

#if OS_FEATURE_TIME_SUPPORTED
typedef os_uint32_t os_time_t;
#endif

#endif  /*__OS_CFG_H__*/
