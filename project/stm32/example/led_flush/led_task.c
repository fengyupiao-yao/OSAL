#include "osal.h"
#include "stm32f1xx.h"

extern osal_uint8_t led0_task, led1_task, led2_task, led3_task;
    
void led_event_flush(void){

    while(1){
        OSAL_TASK_BEGIN();
        osalEventSetSync(led0_task, 0x01);
        osalEventSetSync(led1_task, 0x01);
        osalEventSetSync(led2_task, 0x01);
        osalEventSetSync(led3_task, 0x01);
        HAL_Delay(1000);
        OSAL_TASK_END();
    }
}

void led0_flush(void){
    while(1){
        OSAL_TASK_BEGIN();
        osalEventWait();
        osalEventClear(os_curr_taskID, 0x01);
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_8);
        OSAL_TASK_END();
    }
}

void led1_flush(void){
    while(1){
        OSAL_TASK_BEGIN();
        osalEventWait();
        osalEventClear(os_curr_taskID, 0x01);
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_9);
        OSAL_TASK_END();
    }
}

void led2_flush(void){

    while(1){
        OSAL_TASK_BEGIN();
        osalEventWait();
        osalEventClear(os_curr_taskID, 0x01);
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_10);
        OSAL_TASK_END();
    }
}

void led3_flush(void){
    while(1){
        OSAL_TASK_BEGIN();
        osalEventWait();
        osalEventClear(os_curr_taskID, 0x01);
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_11);
        OSAL_TASK_END();
    }
}
