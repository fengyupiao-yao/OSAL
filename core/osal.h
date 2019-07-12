#ifndef __OSAL_H__
#define __OSAL_H__


#include "osal_types.h"
#include "osal_task.h" 


#define OSAL_TASK_BEGIN()    \
    switch(GET_CURR_TASK_PC()){   \
        case 0:

#define OSAL_TASK_END()    \
    SET_CURR_TASK_PC(0x00);   \
    }


#define OSAL_YIELD()    \
    SET_CURR_TASK_PC(__LINE__);    \
    return;    \
    case __LINE__:

//event
#define osalEventSetAsync(task_id, event_flag)    osalEventSet(task_id, event_flag)

#define osalEventSetSync(task_id, event_flag)    \
    osalEventSet(task_id, event_flag);    \
    OSAL_YIELD();

#define osalEventWait()    \
    SET_CURR_TASK_PC(__LINE__);    \
    if(!osalEventGet(os_curr_taskID)){    \
        SET_CURR_TASK_STATE(OS_TASK_W4_EVENT);    \
        return;    \
    }   \
    case __LINE__:   \


#endif  /*__OSAL_H__*/
