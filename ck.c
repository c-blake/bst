#ifdef BST_ELL_LESS
#   include "test/floorLg.c"
#endif
#define BST_E(...) printf("[34;7m0x%lx: [m",(long)p),printf(__VA_ARGS__),\
                   puts(""), ++*nE      /* auto-newline and error bump */

BST_LKG int _(_ck)(BST_P p, int *nE) {  /** VERIFY TREE PROPERTIES **/
    int h0 = 0, h1 = 0;
    if (!p)
        return 0;                       /* null tree always correct, height 0 */
    if (BST_wt(p) != BST_wt(BST_ln(p,0)) + BST_wt(BST_ln(p,1)) + 1)
        BST_E("wt %d != %d + %d + 1", BST_wt(p),
              BST_wt(BST_ln(p,0)), BST_wt(BST_ln(p,1)));
    /* NOTE: assume native struct field access to 'key' and that '>' works */
    if (BST_ln(p, 0) != BST_0) {
        if (BST_NODE(BST_ln(p, 0)).key > BST_NODE(p).key)   /* check 0-order */
            BST_E("%d > %d", BST_NODE(BST_ln(p, 0)).key, BST_NODE(p).key);
        h0 = _(_ck)(BST_ln(p, 0), nE);                      /* check 0-kid */
#ifdef BST_PARENT
        if (BST_up(BST_ln(p, 0)) != p)
            BST_E("up[kid0] == 0x%lx", (long)BST_up(BST_ln(p, 0)));
#endif
    }
    if (BST_ln(p, 1) != BST_0) {
        if (BST_NODE(BST_ln(p, 1)).key < BST_NODE(p).key)   /* check 1-order */
            BST_E("%d < %d", BST_NODE(BST_ln(p, 1)).key, BST_NODE(p).key);
        h1 = _(_ck)(BST_ln(p, 1), nE);                      /* check 1-kid */
#ifdef BST_PARENT
        if (BST_up(BST_ln(p, 1)) != p)
            BST_E("up[kid1] == 0x%lx", (long)BST_up(BST_ln(p, 1)));
#endif
    }
#if    defined BST_AVL                              /* AVL properties */
    if (abs(h0 - h1) > 1)
        BST_E("|%d - %d| > 1", h0, h1);
    if (BST_bal(p) != h1 - h0)
        BST_E("bal != %d", h1 - h0);
    return (h0 > h1 ? h0 : h1) + 1;                 /* accum height going up */
#elif  defined BST_RB                               /* Red-Black properties */
    if (h0 != h1)
        BST_E("BlackHeight %d != %d", h0, h1);
    if (BST_red(p)) {
        if (BST_ln(p, 0) != BST_0 && BST_red(BST_ln(p, 0)))
            BST_E("Red Node Has Red 0-Kid");
        if (BST_ln(p, 1) != BST_0 && BST_red(BST_ln(p, 1)))
            BST_E("Red Node Has Red 1-Kid");
    }
    return h0 + !BST_red(p);                        /* black height going up */
#else
#ifdef BST_ELL_LESS                                 /* ELL-balance properties */
    if (abs(floorLg(BST_wt(BST_ln(p, 0))) - floorLg(BST_wt(BST_ln(p, 1)))) > 1)
        BST_E("|%d - %d| > 1",
              floorLg(BST_wt(BST_ln(p,0))), floorLg(BST_wt(BST_ln(p,1))));
#endif
    return 0;
#endif
}
