#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>
#include <stddef.h>

/*----------------------------------------------------------------------------*/
//period
#define TIMER_TIMES_PERIOD          0x00
#define TIMER_TIMES_ZERO_TIMES      0x00
#define TIMER_TIMES_ONE_TIMES       0x01
#define TIMER_TIMES_N_TIMES(n)      (n)
typedef uint8_t timer_times_t;

/*----------------------------------------------------------------------------*/
typedef void(*timer_callback_t)(void *param);

typedef struct timer_tag{
    struct timer_tag *next;
    uint32_t period;
    uint32_t delay;
    timer_times_t times;
    uint8_t run_me;
    timer_callback_t timer_process;
    void *cb_param;
    uint8_t dynamic;
}timer_t;

#define TIMER_DEFINE(tm_name, tm_times, tm_period, tm_cb, tm_cb_param) \
    static timer_t tm_name = {    \
        .period = tm_period,  \
        .delay = tm_period,    \
        .next = NULL,    \
        .times = tm_times,    \
        .run_me = 0,    \
        .timer_process = (timer_callback_t)tm_cb,    \
        .cb_param = (void*)tm_cb_param,    \
        .dynamic = 0,    \
    }  \

void timer_init(void);
void timer_add(timer_t *timer);
timer_t *timer_register(timer_times_t times, uint32_t period, timer_callback_t timer_cb, void * cb_param);
void timer_update(void);
void timer_sch(void);
void timer_delete(timer_t *timer);

#endif  /*__TIMER_H__*/
