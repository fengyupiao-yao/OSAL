#ifndef __OS_THREAD_H__
#define __OS_THREAD_H__

#include "os_types.h"

typedef void (*threadFunc_t)(void *p_arg);

typedef struct osThreadDef_tag{
    struct osThreadDef_tag *next;
    threadFunc_t p_threadFunc;
    void *p_argv;
    os_uint8_t prio;
    os_uint16_t pc;
}osThreadDef_t;

#define OS_THREAD_DEF(name, argv, priority)    \
    osThreadDef_t os_thread_def_##name = {    \
        .next = NULL,    \
        .p_threadFunc = name,   \
        .p_argv = argv,     \
        .prio = priority,    \
        .pc = 0,    \
    };

#define OS_THREAD(name)        &(os_thread_def_##name)




os_uint16_t osThreadGetPC(osThreadDef_t *p_thread_def);
void osThreadSetPC(osThreadDef_t *p_thread_def, os_uint16_t pc);
void osThreadAdd(osThreadDef_t *p_thread_def);
void osThreadDel(osThreadDef_t *p_thread_def);
void osThreadYield(void);

#endif  /*__OS_TASK_H__*/
