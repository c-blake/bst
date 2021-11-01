#include <stdlib.h>
#include <stdio.h>
#include "now.c"

#define BST_P        unsigned short /* OR "struct bst*" if VMEM.c below */
#include "bst/MEMBER.h"         /* this defines bst_member_t/HOOK */
#define BST_KEY_T    unsigned short
#define BST_KEY      x
typedef struct bst { BST_MEMBER_HOOK; BST_KEY_T BST_KEY; } bst_t;
#define _(_x)        bst ## _x
#include "bst/POOL.c"           /* OR VMEM.c */
#include "bst/METHODS.c"        /* member.h sets up separate accessors */

BST_P bst_new(unsigned short x) {
    BST_P p = bst_alloc();
    BST_NODE(p).BST_KEY = x;        /* This relies on struct member property */
    return bst_init(p);
}

int main(int argc, char **argv) {
    BST_P  t = BST_0;
    BST_P *path[1024];              /* giant to be splay tree friendly */
    int    i, *x = (int*)malloc(argc * sizeof *x), d;

    bst_POOL_init(65536, sizeof(bst_t));
    if (argc < 2)
        return printf("%s int -int ... inserts int, deletes -int\n", argv[0]);
    for (i = 1; i < argc; i++)
        x[i] = atoi(argv[i]);
    double t0 = now();
    for (i = 1; i < argc; i++)
        if (*argv[i] == '-') {
            if ((d = bst_seek_key(&t, path, -x[i])) > 0)
                bst_free(bst_unlink(path, d));
        } else
            if ((d = bst_seek_key(&t, path,  x[i])) <= 0)
                bst_linkin(path, -d, bst_new(x[i]));
    double dt = now() - t0;
    printf("%g us/op\n", 1e6 * dt / (argc - 1));
    return 0;
}
