#include <stddef.h>
#include "os_types.h"
#include "os_thread.h"
#include "os_core.h"

os_uint16_t osThreadGetPC(osThreadDef_t *p_thread_def){
    if(p_thread_def){
        return p_thread_def->pc;
    }else{
        return os_info.p_thread_curr->pc;
    }
}

void osThreadSetPC(osThreadDef_t *p_thread_def, os_uint16_t pc){
    if(p_thread_def){
        p_thread_def->pc = pc;
    }else{
        os_info.p_thread_curr->pc = pc;
    }
}

void osThreadAdd(osThreadDef_t *p_thread_def){
    osThreadDef_t **p_pre, **p_cur;
    p_pre = NULL;
    p_cur = &(os_info.p_thread_ready);
    p_thread_def->next = NULL;
    while(1){
        if(*p_cur == NULL){
            *p_cur = p_thread_def;
            break;
        }
        if((*p_cur)->prio < p_thread_def->prio){
            p_pre = p_cur;
            p_cur = &((*p_cur)->next);
        }else{
            p_thread_def->next = *p_cur;
            if(p_pre == NULL){
                os_info.p_thread_ready = p_thread_def;
            }else{
                (*p_pre)->next = p_thread_def;
            }
            break;
        }
    }
}

void osThreadDel(osThreadDef_t *p_thread_def){
    //list_remove(&(os_info.p_thread_active), p_thread_def);
}

osThreadDef_t *osThreadGetHighPrio(void){
    return os_info.p_thread_ready;
}

osThreadState_t osThreadYield(void){
    return OS_THREAD_READY;
}

void osThreadSwitch(osThreadState_t thread_state){
    osThreadDef_t *p_thread;
    switch(thread_state){
        case OS_THREAD_READY:
            p_thread = os_info.p_thread_curr;
            os_info.p_thread_curr = os_info.p_thread_ready;       //get from ready list
            os_info.p_thread_ready = os_info.p_thread_ready->next;
            osThreadAdd(p_thread);    //add to ready as priority
        break;
        case OS_THREAD_RUNING:
        break;
        case OS_THREAD_WAITING:
            os_info.p_thread_curr->next = os_info.p_thread_active;    //put into active list
            os_info.p_thread_active = os_info.p_thread_curr;
            os_info.p_thread_curr = os_info.p_thread_ready;           //get from ready list
            if(os_info.p_thread_ready){
                os_info.p_thread_ready = os_info.p_thread_ready->next;
            }
        break;
        case OS_THREAD_EXIT:
        break;
        default:break;
    }
}

