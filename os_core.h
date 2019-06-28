#ifndef __OS_CORE_H__
#define __OS_CORE_H__

#include <stddef.h>
#include "os_types.h"
#include "os_thread.h"

#define PC_INIT(p_pc)    *p_pc = 0
#define PC_SET(p_pc)     *p_pc = __LINE__;    \
                          case __LINE__:


#define OS_THREAD_BEGIN()    \
    switch(osThreadGetPC(NULL)){    \
        case 0:


#define OS_THREAD_END()                            \
                        osThreadSetPC(NULL, 0);    \
                        }



typedef struct{
    osThreadDef_t *p_thread_active;
    osThreadDef_t *p_thread_ready;
    osThreadDef_t *p_thread_curr;
    os_uint8_t schLock;
}os_info_t;

extern os_info_t os_info;

void osCoreInit(void);
void osSched(void);
void osRun(void);


#endif  /*__OS_CORE_H__*/
