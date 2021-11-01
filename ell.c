#define BST_ELL_LESS(a, b)   ((a) < (b) ? ((a) & (b)) << 1  <  (b) : 0)

BST_LKG void _(_ell_rebalance)(BST_CTX BST_P *path[], int d, int in) {
    for (d--; d > 0; d--) {                     /* bottom-up rebalance */
        BST_P *p = path[d-1];
        int    s = path[d] == &BST_ln(*p, in);  /*Ins maybeSame; Del: maybeOpp*/
        if (BST_ELL_LESS(BST_wt(BST_ln(*p, !s)), BST_wt(BST_ln(*p, s)) >> 1)) {
            BST_P y = BST_ln(*p, s);
            if (BST_ELL_LESS(BST_wt(BST_ln(y, s)), BST_wt(BST_ln(y, !s))))
                _(_rot)(BST_ctx &BST_ln(*p, s), s);
            _(_rot)(BST_ctx p, !s);
        }
    }
}
#define BST_LINKIN_REBALANCE  _(_ell_rebalance)(BST_ctx path, d, 1);
#define BST_UNLINK_REBALANCE  _(_ell_rebalance)(BST_ctx path, d, 0);
