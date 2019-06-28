#include <stddef.h>
#include <stdlib.h>
#include "os_types.h"

/*----------------------------------------------------------------------------*/
typedef struct list_node_tag{
    struct list_node_tag *next;
}list_node_t;

typedef list_node_t* list_t;

/*----------------------------------------------------------------------------*/
void list_init(list_t *list){
    list = NULL;
}

void list_add(list_t *list, void *node){
    list_node_t *p_node;
    p_node = node;
    if(node != NULL){
        p_node->next = *list;
        *list = p_node;
    }
}

void list_add_tail(list_t *list, void *node){
    list_node_t *pre_node;
    list_node_t *p_node;
    p_node = (list_node_t *)node;
    if(*list){
        pre_node = *list;
        while(pre_node->next){
            pre_node = pre_node->next;
        }
        pre_node->next = p_node;
    }
    else{
        *list = p_node;
    }
    p_node->next = NULL;
}

void list_remove(list_t *list, void *node){
    list_node_t *pre_node = NULL;
    list_node_t *cur_node;
    list_node_t *p_node;
    p_node = (list_node_t *)node;

    if((p_node == NULL) || (*list == NULL)) return;
    cur_node = *list;
    if(cur_node == p_node){
        *list = NULL;
        return;
    }
    while(cur_node != NULL){
        if(cur_node == p_node){
            pre_node->next = cur_node->next;
        }
        pre_node = cur_node;
        cur_node = cur_node->next;
    }
}

os_uint32_t list_get_length(list_t *list){
    os_uint32_t len = 0x00;
    list_node_t *node;
    for(node = *list; node; node=node->next){
        len ++;
    }
    return len;
}

list_node_t* list_get_node(list_t *list, os_uint32_t idx){
    os_uint32_t i;
    list_node_t *node;
    node = *list;
    for(i=0x00; i<idx; i++){
        if(node == NULL) break;
        node = node->next;
    }
    return node;
}

list_node_t *list_pop(list_t *list){
    list_node_t *p_node = NULL;
    if(*list != NULL){
        p_node = *list;
        *list = (*list)->next;
    }
    return p_node;
}
