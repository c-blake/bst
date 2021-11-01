#include <stdlib.h>
#include <stdio.h>
#include "now.c"

#define BST_P        unsigned short /* OR "struct t*" with BST_VMEM.c */
#include "bst/MEMBER.h"         /* this defines bst_member_t/HOOK */
#define BST_KEY_T    float
#define BST_KEY      x
typedef struct t_s { BST_MEMBER_HOOK; BST_KEY_T BST_KEY; } t_t; /* ~12 bytes */

#define _(_x)        t ## _x
#include "bst/POOL.c"           /* or VMEM.c */
#include "bst/METHODS.c"        /* MEMBER.h sets up separate accessors */

BST_P t_new(float x) {
    BST_P p = t_alloc();
    BST_NODE(p).x = x;              /* This relies on struct member property */
    return t_init(p);
}

int main(int c, char **v) {
    BST_P  t = 0, *p[1024];
    int    i; /*, d */
    float *x = (float*)malloc(c * sizeof *x);

    t_POOL_init(65536, sizeof(t_t));
    if (c < 2)
        return printf("%s float ... inserts floats; dumps in-order\n", v[0]);
    for (i = 1; i < c; i++)
        x[i] = atof(v[i]);
    double t0 = now();
    for (i = 1; i < c; i++)         /* this is a very competitive stable sort */
        t_linkin(p, t_seek_push(p, t_seek_keyS(&t, p, 1, x[i]), 1), t_new(x[i]));
    double dt = now() - t0;
    printf("%g us\n", 1e6 * dt);
/*  for (i = 1, d = t_seek_most(&t, p, 0); d; d = t_seek_adj(p, d, 1))
        printf("%d\n", BST_NODE(*p[d-1]).x); */     /* check correctness */
    return 0;
}
