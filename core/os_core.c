#include <stddef.h>
#include "os_core.h"

os_info_t os_info;

void osCoreInit(void){
    os_info.p_thread_active = NULL;
    os_info.p_thread_ready = NULL;
    os_info.p_thread_curr = NULL;
    os_info.schLock = 0;
}

//FIXME
void osSched(void){
    if(os_info.schLock){
        return;
    }
    os_info.p_thread_curr = os_info.p_thread_ready;
    if(os_info.p_thread_ready){
        os_info.p_thread_ready = os_info.p_thread_ready->next;
    }
}

void osRun(void){
    osThreadState_t thread_state;
    osSched();
    while(1){
        if(os_info.p_thread_curr){
            thread_state = os_info.p_thread_curr->p_threadFunc(os_info.p_thread_curr->p_argv);
            osThreadSwitch(thread_state);
        }else{
            //sleep
            //WFI
            win_wfi();
            osSched();
        }
    }
}

#if OS_FEATURE_TIME_SUPPORTED
osThreadState_t osTimeDly(os_time_t delay_ticks){
    os_info.p_thread_curr->delay_ticks = delay_ticks;
    if(delay_ticks){
        return OS_THREAD_WAITING;
    }else{
        return OS_THREAD_RUNING;
    }
}

osThreadState_t osTimeDlyResume(osThreadDef_t *p_thread){
    p_thread->delay_ticks = 0;
    //ready;
}

void osTimeUpdate(void){
    osThreadDef_t *p_thread;
    osThreadDef_t *p_pre_thread;

    p_pre_thread = NULL;
    p_thread = os_info.p_thread_active;
    while(p_thread){
        if(p_thread->delay_ticks){
            p_thread->delay_ticks--;
            if(p_thread->delay_ticks == 0){
                if(p_pre_thread){
                    p_pre_thread->next = p_thread->next;
                }else{
                    os_info.p_thread_active = p_thread->next;
                }
                osThreadAdd(p_thread);
                if(p_pre_thread){
                    p_thread = p_pre_thread->next;
                }else{
                    p_thread = os_info.p_thread_active;
                }
                continue;
            }
        }
        p_pre_thread = p_thread;
        p_thread = p_thread->next;
    }
}

#endif
