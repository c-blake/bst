#include <stdio.h>          /* Use weighted, balanced binary search trees to */
#include <stdlib.h>         /* compute a moving median over numbers from argv */
#include "now.c"

#define _(_x)      bst ## _x    /* STEP 1: Configure Namespace */
#define BST_LKG    static inline/* STEP 2: Define Linkage & Bind Members */
#define BST_LINK   ln               /* NAME separate struct members of tree */
#define BST_WEIGHT wt               /* metadata for _POOL.c,_METHODS.c below. */
#define BST_WEIGHTED                /* also needed for METHODS.c below */
#ifdef POOL                     /* STEP 3: Define Node Type & Alloc Style */
#define BST_lkg    static       /*         POOL only -- decls global vars */
typedef struct {
    unsigned short ln[2], wt;   /* binary tree links & weight */
#if defined(BST_RB) || defined(BST_AVL)
#   define BST_META meta
    short           meta;       /* balance meta data; signed needed for AVL */
#endif
    float           key;        /* floating point key */
} _(_t);                        /* should be 8 bytes/object total */
#  define BST_P  unsigned short
#  include "bst/POOL.c"     /* Custom pool allocator: (CAPS=>Global) Pool */
#else                           /* STEP 3 Alternate: System malloc/free Nodes */
typedef struct  _(_s) {
    struct _(_s)  *ln[2];       /* binary tree links */
#if defined(BST_RB) || defined(BST_AVL)
#   define BST_META meta
    signed         meta :  2;   /* balance meta data; signed needed for AVL */
    unsigned       wt   : 30;   /* binary tree weight; max 1 GigaNodes */
#else
    unsigned       wt;          /* binary tree weight; max 4 GigaNodes */
#endif
    float          key;         /* floating point key */
} _(_t), *_(_tp);               /* 16|24B on 32|64-bit arch; (+ malloc ovrhd) */
#  define BST_P  _(_tp)
#  include "bst/VMEM.c"     /* use system malloc/free */
#endif

#define BST_KEY_QRY float qry               /* STEP 4: Define seek_key Args */
#define BST_CMP(n)  (BST_NODE(n).key - qry) /*           And Comparison Op */

#include "bst/METHODS.c"    /* STEP 5: Instantiate Methods */
#include "bst/stats.c"

BST_P bst_new(float k) {        /* define a convenience object constructor */
    BST_P p = bst_alloc();
    if (p == BST_0)
        exit(1);                /* POOL needs to grow a realloc method.. */
    BST_NODE(p).key = k;
    return bst_init(p);         /* Must init metadata */
}

int main(int argc, char **argv) {
    int    i, d, w = argc > 1 ? atoi(argv[1]) : 10, n = argc - 2;
    float *x = (float*)malloc(n * sizeof *x), mean_mmed = 0, med = 0;
    BST_P  t = 0, *path[32];

#ifdef POOL
    bst_POOL_init(65536, sizeof(bst_t));
#endif
    if (n < 1)
        return printf("%s <nWin> float float ...\n", argv[0]);
    for (i = 0; i < n; i++)         /* Pre-compute x[] so we do not time the */
        x[i] = atof(argv[i + 2]);   /* sometimes slow ascii => FP conversion. */
    double t0 = now();
    for (i = 0; i < n; i++) {
        if (i >= w && (d = bst_seek_keyS(&t, path, 0, x[i - w])) > 0)
            bst_free(bst_unlink(path, d));                      /* pop_front */
        d = bst_seek_push(path, bst_seek_keyS(&t, path, 1, x[i]), 1);
        bst_linkin(path, d, bst_new(x[i]));                     /* push_back */
        if ((d = bst_seek_nth(&t, path, BST_NODE(t).wt / 2)) > 0)
            med = BST_NODE(*path[d-1]).key;                     /* median qry */
#if 0
        { int j; printf("med: %g data:", med);
        for (j = i-w+1 < 0 ? 0 : i-w+1; j <= i; j++) printf(" %g", x[j]);
        printf("\n"); }
#endif
        if (i >= w - 1)
            mean_mmed += med;       /* block compilers from eliding whole calc*/
    }
    double dt = (now() - t0) * 1e6 / (n - w / 3);
    long ipl = 0, N = 0, h = bst_stats(t, 0, &ipl, &N);
    printf("n: %d us/no: %g N: %d <mmed>: %.11g h: %ld ipl: %ld\n",
           n, dt, BST_NODE(t).wt, mean_mmed / (n - w + 1), h, ipl);
    return 0;
}
