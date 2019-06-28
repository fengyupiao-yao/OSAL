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
    os_info.p_thread_ready = os_info.p_thread_ready->next;
}

void osRun(void){
    while(1){
        if(os_info.p_thread_curr){
            os_info.p_thread_curr->p_threadFunc(os_info.p_thread_curr->p_argv);
        }else{
            //sleep
            //WFI
        }
    }
}




