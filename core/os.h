#ifndef __OS_H__
#define __OS_H__

#include "os_cfg.h"
#include "os_core.h"
#include "os_thread.h"


#define OS_THREAD_BEGIN()    \
    switch(osThreadGetPC(NULL)){    \
        case 0:


#define OS_THREAD_END()                            \
                        osThreadSetPC(NULL, 0);    \
                        }


#define OS_THREAD_YIELD()                                     \
                            osThreadSetPC(NULL, __LINE__);    \
                            return osThreadYield();           \
                            case __LINE__:

#if OS_FEATURE_TIME_SUPPORTED
#define OS_TIME_DLY(delay_ticks)                                \
                               osThreadSetPC(NULL, __LINE__);   \
                               return osTimeDly(delay_ticks);   \
                               case __LINE__:
#else
#define OS_TIME_DLY(delay_ticks)
#endif


void osInit(void);

#endif  /*__OS_H__*/
