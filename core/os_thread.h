#ifndef __OS_THREAD_H__
#define __OS_THREAD_H__

#include "os_types.h"
#include "os_cfg.h"


typedef enum{
    OS_THREAD_EXIT      = 0x00,
    OS_THREAD_WAITING   = 0x01,
    OS_THREAD_READY     = 0x02,
    OS_THREAD_RUNING    = 0x04,
}osThreadState_t;

typedef osThreadState_t (*threadFunc_t)(void *p_arg);

typedef struct osThreadDef_tag{
    struct osThreadDef_tag *next;
    threadFunc_t p_threadFunc;
    void *p_argv;
    os_uint8_t prio;
    os_uint16_t pc;
    #if OS_FEATURE_TIME_SUPPORTED
    os_time_t delay_ticks;
    #endif
}osThreadDef_t;

#define OS_THREAD_DEF(name, argv, priority)    \
    osThreadDef_t os_thread_def_##name = {    \
        .next = NULL,    \
        .p_threadFunc = name,   \
        .p_argv = argv,     \
        .prio = priority,    \
    };

#define OS_THREAD(name)        &(os_thread_def_##name)


os_uint16_t osThreadGetPC(osThreadDef_t *p_thread_def);
void osThreadSetPC(osThreadDef_t *p_thread_def, os_uint16_t pc);
void osThreadAdd(osThreadDef_t *p_thread_def);
void osThreadDel(osThreadDef_t *p_thread_def);
osThreadState_t osThreadYield(void);
void osThreadSwitch(osThreadState_t thread_state);



#endif  /*__OS_TASK_H__*/
