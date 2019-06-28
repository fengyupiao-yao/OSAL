#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdint.h>

/*----------------------------------------------------------------------------*/
//little endian format(LSB first transmit and received)
static inline uint8_t ExtractByte(uint8_t *p){
    return (*p);
}

static inline uint16_t ExtractShort(uint8_t *p){
    return ((*p) + (*(p+1) << 8));
}

static inline uint32_t ExtractWord(uint8_t *p){
    return ( (*p) + (*(p+1) << 8) + (*(p+2) << 16) + (*(p+3) << 24) );
}

static inline void AssembleByte(uint8_t *p, uint8_t value){
    *p = value;
}

static inline void AssembleShort(uint8_t *p, uint16_t value){
    *p = (value & 0xFF);
    *(p+1) = (value >> 8) & 0xFF;
}

static inline void AssembleWord(uint8_t *p, uint32_t value){
    *p = (value & 0xFF);
    *(p+1) = (value >> 8) & 0xFF;
    *(p+2) = (value >> 16) & 0xFF;
    *(p+3) = (value >> 24) & 0xFF;
}

/*----------------------------------------------------------------------------*/
#define ARRAY_SIZE(a)   ( sizeof(a) / sizeof((a)[0]) )

#define MIN(a, b)   ((a) > (b) ? (b) : (a))
#define MAX(a, b)   ((a) > (b) ? (a) : (b))

#endif  /*__UTILS_H__*/

