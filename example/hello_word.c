#include <stdio.h>
#include "os.h"

osThreadState_t hello_world_1(void *argv){
    while(1){
        OS_THREAD_BEGIN();
        printf("hello world 1 start. \n");
        OS_THREAD_YIELD();
        printf("hello world 1 continue.\n");
        OS_THREAD_YIELD();
        printf("hello world 1 end.\n");
        OS_THREAD_YIELD();
        OS_THREAD_END();
    }
}

osThreadState_t hello_world_2(void *argv){
    while(1){
        OS_THREAD_BEGIN();
        printf("hello world 2 start. \n");
        OS_TIME_DLY(2);
        printf("hello world 2 continue.\n");
        OS_TIME_DLY(2);
        printf("hello world 2 end.\n");
        OS_TIME_DLY(2);
        OS_THREAD_END();
    }
}

osThreadState_t hello_world_3(void *argv){
    while(1){
        OS_THREAD_BEGIN();
        printf("hello world 3 start. \n");
        OS_THREAD_YIELD();
        printf("hello world 3 continue.\n");
        OS_THREAD_YIELD();
        printf("hello world 3 end.\n");
        OS_THREAD_YIELD();
        OS_THREAD_END();
    }
}

OS_THREAD_DEF(hello_world_1, NULL, 1);
OS_THREAD_DEF(hello_world_2, NULL, 2);
OS_THREAD_DEF(hello_world_3, NULL, 3);

void example_thread_create(void){
    osThreadAdd(OS_THREAD(hello_world_1));
    osThreadAdd(OS_THREAD(hello_world_2));
    osThreadAdd(OS_THREAD(hello_world_3));
}
