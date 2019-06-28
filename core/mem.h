#ifndef __MEM_H__
#define __MEM_H__

#include <stdint.h>

/*----------------------------------------------------------------------------*/
#ifndef MEM_SIZE
#define MEM_SIZE (1024*10)
#endif

#ifndef MEM_DEBUG
#define MEM_DEBUG    0
#endif

/*----------------------------------------------------------------------------*/
void mem_init(void);
void *mem_malloc(uint32_t size);
void mem_free(void* ptr);

#if MEM_DEBUG
    #define MEM_MALLOC(ptr, size)   do{    \
    ptr = mem_malloc(size);    \
    log("malloc at %s:%d, ptr = 0x%x\n", __BLUESTACK_FILE__, __LINE__, (uint32_t)ptr);    \
    }while(0)

    #define MEM_FREE(ptr)    do{    \
        log("%s:%d, ptr = 0x%x\n", __BLUESTACK_FILE__, __LINE__, (uint32_t)ptr);    \
        mem_free(ptr);    \
    }while(0)

#else
  #define MEM_MALLOC(ptr, size)     \
    do{     \
       ptr = mem_malloc(size);    \
    }while(0)

  #define MEM_FREE(ptr)    mem_free(ptr)
#endif

#endif  /*__MEM_H__*/
