#ifndef __OS_THREAD_H__
#define __OS_THREAD_H__

#include "osal_types.h"
#include "osal_cfg.h"


enum{
    OS_TASK_EXIT      = 0x00,
    OS_TASK_READY     = 0x01,
    //OS_TASK_WAITING   = 0x02,
    OS_TASK_W4_EVENT  = 0x02,

    //OS_TASK_RUNING    = 0x04,
};
typedef osal_uint8_t osTaskState_t;

typedef void (*taskFunc_t)(void);

typedef struct osThreadDef_tag{
    #if OSAL_TASK_NAME_SUPPORTED
    osal_uint8_t name[OSAL_TASK_MAX_NAME_LEN];
    #endif
    taskFunc_t p_taskFunc;
    osal_uint16_t pc;
    osal_uint8_t prio;
    osTaskState_t state;
    osal_event_t event;
}osalTaskDef_t;


extern osal_uint8_t os_curr_taskID;
extern osalTaskDef_t osal_task[OSAL_MAX_SUPPORTED_TASKS];


#define GET_CURR_TASK_PC()          osal_task[os_curr_taskID].pc
#define SET_CURR_TASK_PC(_pc)       osal_task[os_curr_taskID].pc = (_pc)
#define SET_CURR_TASK_STATE(_state) osal_task[os_curr_taskID].state = _state

void osalTaskDel(osal_base_t task_id);
void osalTaskInit(void);
osal_base_t osalTaskAdd(const char * const name, taskFunc_t p_task_func, osal_uint8_t priority);
void osalTaskSchedu(void);
void osalTaskStart(void);

void osalEventSet(osal_base_t task_id, osal_event_t event_flag);
void osalEventClear(osal_base_t task_id, osal_event_t event_flag);
osal_event_t osalEventGet(osal_base_t task_id);
osal_event_t osalEventGetClear(osal_base_t task_id);

#endif  /*__OSAL_TASK_H__*/
