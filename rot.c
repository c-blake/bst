BST_LKG void _(_rot)(BST_CTX BST_P *r, int s) { /* REPLACE r)oot WITH !s k)id */
    BST_P   k = BST_ln(*r, !s);                 /*   B            C     A     */
    BST_LN(*r, !s, BST_ln(k, s));               /* A   C ==>    B   ==>   B   */
    BST_LN( k,  s, *r);                         /*  x y  s=0  a  y  s=1  x  c */
    BST_WT(*r, BST_wt(BST_ln(*r, 0)) + BST_wt(BST_ln(*r, 1)) + 1);
    BST_WT( k, BST_wt(BST_ln( k, 0)) + BST_wt(BST_ln( k, 1)) + 1);
    BST_UP(k, BST_up(*r));                      /* fix parent links */
    BST_UP(*r, k);
    if (BST_ln(*r, !s) != BST_0)
        BST_UP(BST_ln(*r, !s), *r);             /* moved sub-tree, too */
    *r = k;
}
