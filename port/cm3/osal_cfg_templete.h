#ifndef __OSAL_CFG_H__
#define __OSAL_CFG_H__

#include "os_types.h"

#ifndef OSAL_TASK_NAME_SUPPORTED
#define OSAL_TASK_NAME_SUPPORTED          1
#define OSAL_TASK_MAX_NAME_LEN            8
#endif

#ifndef OSAL_MAX_SUPPORTED_TASKS
#define OSAL_MAX_SUPPORTED_TASKS          16                   /*shall in [1-255]*/
#endif

#endif  /*__OSAL_CFG_H__*/
