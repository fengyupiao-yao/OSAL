#include <stddef.h>
#include "mem.h"

/*----------------------------------------------------------------------------*/
typedef struct block_tag{
    struct block_tag *next;
    uint32_t size;
}mem_block_t;

typedef struct{
    uint32_t size;
}mem_using_t;

/*----------------------------------------------------------------------------*/
static uint8_t m_mem[MEM_SIZE];

/*----------------------------------------------------------------------------*/
void mem_init(void){
    mem_block_t *first_block;
    first_block = (mem_block_t *)m_mem;
    first_block->next = NULL;
    first_block->size = MEM_SIZE;
}

void *mem_malloc(uint32_t size){
    mem_using_t *mem = NULL;
    mem_block_t *block = NULL;
    mem_block_t *found = NULL;    //found best block

    block = (mem_block_t *)m_mem;
    size = (size + 3) & (~3);    //align to 4 Byte
    size += sizeof(mem_using_t);

    if(size < sizeof(mem_block_t))
        size = sizeof(mem_block_t);

    while(block){
        if(block->size >= size + sizeof(mem_block_t)){
            if((found == NULL) || (found->size > block->size)){    //found best match
                found = block;
            }
        }
        block = block->next;
    }

    if (found != NULL){
        found->size -= size;
        mem = (mem_using_t *)((uint32_t)found + found->size);
        mem->size = size;
        mem ++;
    }
    return (void *)mem;
}

void mem_free(void* ptr){
    mem_block_t *pre_block = NULL;
    mem_block_t *cur_block = NULL;

    if(ptr == NULL) return;
   
    mem_using_t *free_block = ((mem_using_t*)ptr) - 1;
    uint32_t size = free_block->size;

    cur_block = (mem_block_t *)m_mem;

    //found located block
    while(cur_block){
        if((uint32_t)free_block < (uint32_t)cur_block)
            break;
        pre_block = cur_block;
        cur_block = cur_block->next;
    }

    //free and merge
    if( ((uint32_t)pre_block + pre_block->size) == (uint32_t)free_block){
        pre_block->size += size;
        if( ((uint32_t)pre_block + pre_block->size) == (uint32_t)pre_block->next){  //merge
            pre_block->size += pre_block->next->size;
            pre_block->next = pre_block->next->next;
        }
    }else{    //generate new block
            mem_block_t *new_block = (mem_block_t *)free_block;
            new_block->size = size;
            if( ((uint32_t)new_block + size) == (uint32_t)pre_block->next){  //merge
                new_block->size = size + pre_block->next->size;
                new_block->next = pre_block->next->next;
            }else{
                new_block->next = pre_block->next;
            }
            pre_block->next = new_block;
    }
}
