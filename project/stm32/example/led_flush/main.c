
/* Standard includes. */
#include <stdio.h>
#include "osal.h"

/* Library includes. */
#include "stm32f1xx.h"
#include "board.h"

/*-----------------------------------------------------------*/
extern void led0_flush(void);
extern void led1_flush(void);
extern void led2_flush(void);
extern void led3_flush(void);
extern void led_event_flush(void);

/*-----------------------------------------------------------*/
osal_uint8_t led0_task, led1_task, led2_task, led3_task, ledx_task;

int main( void ){

    MX_Board_Init();
    osalTaskInit();
    led0_task = osalTaskAdd("led0", led0_flush, 0x00);
    led1_task = osalTaskAdd("led1", led1_flush, 0x00);
    led2_task = osalTaskAdd("led2", led2_flush, 0x00);
    led3_task = osalTaskAdd("led3", led3_flush, 0x00);
    ledx_task = osalTaskAdd("ledx", led_event_flush, 0x00);
    osalTaskStart();
}
/*-----------------------------------------------------------*/
