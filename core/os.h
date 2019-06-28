#ifndef __OS_H__
#define __OS_H__

#include "os_core.h"
#include "os_thread.h"



void osInit(void);


#define OS_THREAD_YIELD()                                     \
                            osThreadSetPC(NULL, __LINE__);    \
                            osThreadYield();                  \
                            return;                           \
                            case __LINE__:                    \





#endif  /*__OS_H__*/
