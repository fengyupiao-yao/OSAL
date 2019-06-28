#include <stdio.h>
#include "os.h"

void hello_world_1(void *argv){
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

void hello_world_2(void *argv){
    while(1){
        OS_THREAD_BEGIN();
        printf("hello world 2 start. \n");
        OS_THREAD_YIELD();
        printf("hello world 2 continue.\n");
        OS_THREAD_YIELD();
        printf("hello world 2 end.\n");
        OS_THREAD_YIELD();
        OS_THREAD_END();
    }
}

OS_THREAD_DEF(hello_world_1, NULL, 1);
OS_THREAD_DEF(hello_world_2, NULL, 0);

int main(void){
    osInit();
    osThreadAdd(OS_THREAD(hello_world_1));
    osThreadAdd(OS_THREAD(hello_world_2));
    osSched();
    osRun();
}
