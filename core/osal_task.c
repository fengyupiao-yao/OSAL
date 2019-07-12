#include <stddef.h>

#include "osal_cfg.h"
#include "osal_types.h"
#include "osal_task.h"

osalTaskDef_t osal_task[OSAL_MAX_SUPPORTED_TASKS];
osal_uint8_t os_curr_taskID;

void osalTaskDel(osal_base_t task_id){
    osal_task[task_id].p_taskFunc = NULL;
    osal_task[task_id].pc = 0x00;
    osal_task[task_id].prio = 0x00;
    osal_task[task_id].state = OS_TASK_EXIT;
    osal_task[task_id].event = 0x00;
}

void osalTaskInit(void){
    osal_base_t i;
    os_curr_taskID = 0x00;
    for(i=0x00; i<OSAL_MAX_SUPPORTED_TASKS; i++){
        osalTaskDel(i);
    }
}

/**
 * @ingroup osal_task
 * osTaskAdd: add task
 *
 * @param name: task name
 * @param p_task_func: task process function address
 * @param p_argv: task function argument
 * @param priority: task priority, select 0-255
 */
osal_base_t osalTaskAdd(const char * const name, taskFunc_t p_task_func, osal_uint8_t priority){
    osal_base_t i, j;
    for(i=0x00; i<OSAL_MAX_SUPPORTED_TASKS; i++){
        if(osal_task[i].state == OS_TASK_EXIT){
            osal_task[i].p_taskFunc = p_task_func;
            osal_task[i].prio = priority;
            osal_task[i].pc = 0;
            osal_task[i].state = OS_TASK_READY;
            #if OSAL_TASK_NAME_SUPPORTED
            for(j=0x00; j<OSAL_TASK_MAX_NAME_LEN; j++){
                osal_task[i].name[j] = name[j];
                if(name[j] == '\0') break;
            }
            #endif
            return i;
        }
    }
    return OSAL_MAX_SUPPORTED_TASKS;
}

void osalTaskSchedu(void){
    osal_base_t curr_task_idx, task_idx;
    osal_base_t i;

    curr_task_idx = os_curr_taskID;
    for(i=0x00; i<OSAL_MAX_SUPPORTED_TASKS; i++){
        task_idx = (i + os_curr_taskID) % OSAL_MAX_SUPPORTED_TASKS;
        if(osal_task[task_idx].state == OS_TASK_READY){
            if(osal_task[curr_task_idx].prio <= osal_task[task_idx].prio){
                curr_task_idx = task_idx;
            }
        }
    }
    os_curr_taskID = curr_task_idx;
}

void osalTaskStart(void){
    while(1){
        osalTaskSchedu();
        if(os_curr_taskID < OSAL_MAX_SUPPORTED_TASKS){
            osal_task[os_curr_taskID].p_taskFunc();
        }else{
            #if OSAL_USE_IDLE_TASK_HOOK
            extern idleTaskHook(void);
            idleTaskHook();
            #endif
        }
    }
}

void osalEventSet(osal_base_t task_id, osal_event_t event_flag){
    osal_base_t int_state;
    ENTER_CRITICAL_SECTION(int_state);    // Hold off interrupts
    osal_task[task_id].event |= event_flag;     // Stuff the event bit(s)
    if(osal_task[task_id].state == OS_TASK_W4_EVENT){
       osal_task[task_id].state = OS_TASK_READY;
    }
    EXIT_CRITICAL_SECTION(int_state);     // Release interrupts
}

void osalEventClear(osal_base_t task_id, osal_event_t event_flag){
    osal_base_t int_state;
    ENTER_CRITICAL_SECTION(int_state);       // Hold off interrupts
    osal_task[task_id].event &= ~(event_flag);   // Clear the event bit(s)
    EXIT_CRITICAL_SECTION(int_state);        // Release interrupts
}

osal_event_t osalEventGet(osal_base_t task_id){
    osal_event_t event;
    osal_base_t int_state;
    ENTER_CRITICAL_SECTION(int_state);       // Hold off interrupts
    event = osal_task[task_id].event;
    EXIT_CRITICAL_SECTION(int_state);        // Release interrupts
    return event;
}

osal_event_t osalEventGetClear(osal_base_t task_id){
    osal_event_t event;
    osal_base_t int_state;
    ENTER_CRITICAL_SECTION(int_state);       // Hold off interrupts
    event = osal_task[task_id].event;
    osal_task[task_id].event = 0x00;
    EXIT_CRITICAL_SECTION(int_state);        // Release interrupts
    return event;
}
