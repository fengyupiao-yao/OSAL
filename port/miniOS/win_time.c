#include <windows.h>
#include <stdint.h>
#include "os.h"

HANDLE htimer = NULL;
uint32_t m_win_time=0x00;
uint8_t m_time_int = 0x00;

/*----------------------------------------------------------------------------*/
//timer isr process
DWORD WINAPI thread_win_timer(LPVOID lpParameter){
    while(1){
        Sleep(10);
        m_win_time ++;
        osTimeUpdate();
        m_time_int = 1;
    }
}

void win_timer_init(void){
    m_win_time = 0x00;
    m_time_int = 0x00;
    htimer = CreateThread(NULL, 0, thread_win_timer, NULL, 0, NULL);
}

void win_timer_close(void){
    if(htimer){
        CloseHandle(htimer);
    }
}

void delay_ms(uint32_t ms){
    DWORD start = GetTickCount();
    DWORD elapse;
    do{
        elapse = GetTickCount() - start;
    }while(elapse < ms);
}

uint32_t win_get_cur_time(void){
    return m_win_time;
}

void win_wfi(void){
    m_time_int = 0x00;
    while(!m_time_int);
}
