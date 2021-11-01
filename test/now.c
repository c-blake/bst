#ifndef NOW_C
#define NOW_C
#include <time.h>

#ifndef NOW_CLOCK // CLOCK_MONOTONIC_COARSE is fastest but only millisec res
#   define NOW_CLOCK CLOCK_MONOTONIC
#endif /* NOW_CLOCK */

static inline double now(void) {
    struct timespec ts;
    clock_gettime(NOW_CLOCK, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}
#endif /* NOW_C */
