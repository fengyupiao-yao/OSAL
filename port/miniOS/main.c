#include <stdio.h>
#include "os.h"

extern void example_thread_create(void);
void win_timer_init(void);

int main(void){
    osInit();
    win_timer_init();
    example_thread_create();
    osRun();
}
