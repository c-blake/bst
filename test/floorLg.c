#ifndef FLOORLG_C
#define FLOORLG_C
#include <endian.h>

#if BYTE_ORDER == BIG_ENDIAN
#include "f8.h"
static inline int floorLg(const unsigned long x) {
    f8_u   u;
    if (x < 2)
        return 0;
    u.fp = x;
    return u.field.exp - 1023;
}
#else /* LITTLE ENDIAN IEEE-754 doubles */
static inline int floorLg(const unsigned long x) {
    union { double d; unsigned long long i; } u;
    if (x < 2)
        return 0;
    u.d = x;
    return (u.i >> 52) - 1023;
}
#endif /* BIG_ENDIAN */
#endif /* FLOORLG_C */
