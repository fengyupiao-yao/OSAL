#ifndef __OSAL_CFG_H__
#define __OSAL_CFG_H__

#include "osal_types.h"

#ifndef OSAL_TASK_NAME_SUPPORTED
#define OSAL_TASK_NAME_SUPPORTED          1
#define OSAL_TASK_MAX_NAME_LEN            8
#endif

#ifndef OSAL_MAX_SUPPORTED_TASKS
#define OSAL_MAX_SUPPORTED_TASKS          16     /*shall in [1-255]*/
#endif

#ifdef OSAL_USE_IDLE_TASK_HOOK
#define OSAL_USE_IDLE_TASK_HOOK           0
#endif


#define ENTER_CRITICAL_SECTION(x)     {}
#define EXIT_CRITICAL_SECTION(x)      {}

#endif  /*__OSAL_CFG_H__*/
