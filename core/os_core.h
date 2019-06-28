#ifndef __OS_CORE_H__
#define __OS_CORE_H__

#include <stddef.h>
#include "os_types.h"
#include "os_thread.h"


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

#if OS_FEATURE_TIME_SUPPORTED
osThreadState_t osTimeDly(os_time_t delay_ticks);
void osTimeUpdate(void);
#endif

#endif  /*__OS_CORE_H__*/
