#include <stddef.h>
#include "timer.h"
#include "list.h"
#include "mem.h"
#include "errcode.h"
#include "bluestack.h"

#undef __BLUESTACK_FILE__
#define __BLUESTACK_FILE__    "timer.c"
#ifndef BLUESTACK_PRINT_DEBUG
#define BLUESTACK_PRINT_DEBUG     0
#endif
#include "log.h"

/*----------------------------------------------------------------------------*/
timer_t *timer_list = NULL;

/*----------------------------------------------------------------------------*/
void timer_init(void){
    list_init((list_t *)&timer_list);
}

void timer_add(timer_t *timer){
    list_add_tail((list_t *)(&timer_list), (list_node_t *) timer);
}

timer_t *timer_register(timer_times_t times, uint32_t period, timer_callback_t timer_cb, void * cb_param){
    timer_t *p_timer;

    MEM_MALLOC(p_timer, sizeof(timer_t));
    if(p_timer == NULL){
        return NULL;
    }
    p_timer->next = NULL;
    p_timer->period = period;
    p_timer->delay = period;
    p_timer->times = times;
    p_timer->run_me = 0;
    p_timer->timer_process = timer_cb;
    p_timer->cb_param = cb_param;
    p_timer->dynamic = 1;
    timer_add(p_timer);

    return p_timer;
}

void timer_update(void){
    timer_t *p_timer;

    p_timer = timer_list;
    while(p_timer){
        if(p_timer->delay){
            p_timer->delay --;
        }
        if(p_timer->delay == 0){
            p_timer->run_me ++;
            p_timer->delay = p_timer->period;
        }
        p_timer = p_timer->next;
    }
}

void timer_sch(void){
    timer_t *pre_timer;
    timer_t *cur_timer;
    timer_t *next_timer;

    if(timer_list == NULL) return;
    cur_timer = timer_list;
    pre_timer = NULL;

    while(cur_timer){
        while(cur_timer->run_me){
            if(cur_timer->timer_process){
                cur_timer->timer_process(cur_timer->cb_param);
            }
            cur_timer->run_me --;
            if(cur_timer->times != TIMER_TIMES_PERIOD){    //timer run times
                cur_timer->times --;
                if(cur_timer->times == TIMER_TIMES_ZERO_TIMES){    //remove the timer
                    next_timer = cur_timer->next;
                    if(pre_timer){
                        pre_timer->next = next_timer;
                    }else{
                        timer_list = next_timer;
                    }
                    if(cur_timer->dynamic){
                        MEM_FREE(cur_timer);
                        cur_timer = next_timer;
                        if(cur_timer == NULL) return;
                    }
                    continue;
                }
            }
        }
        pre_timer = cur_timer;
        cur_timer = cur_timer->next;
    }
}

void timer_delete(timer_t *timer){
    list_remove((list_t *)&timer_list, (list_node_t *)timer);
    timer = NULL;
}
