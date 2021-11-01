BST_LKG int _(_avl_shorter)(BST_CTX BST_P *pp, int s, int S) {
    BST_P y      = BST_ln(*pp, !s);
    BST_P bup[2] = { *pp , y };
    if (BST_bal(y) * S > 0) {                   /* DOUBLE ROTATION */
        _(_rot)(BST_ctx &BST_ln(*pp, !s), !s);
        _(_rot)(BST_ctx pp, s);
        BST_BAL(bup[ s], -(BST_bal(*pp) > 0));  /* Two kids */
        BST_BAL(bup[!s],   BST_bal(*pp) < 0 );
        BST_BAL(*pp, 0);                        /* ..and new root */
        return 1;                               /* Always shorter */
    } else {                                    /* SINGLE ROTATION */
        _(_rot)(BST_ctx pp, s);
        return !BST_BAL(bup[!s], -BST_BAL(bup[s], BST_bal(y) == 0));
    }
}

BST_LKG void _(_avl_rebalance)(BST_CTX BST_P *path[], int d, int in) {
    for (d--; d > 0; d--) {                     /* bottom-up rebalance */
        BST_P p = *path[d-1];
        int   s = (path[d] == &BST_ln(p, in));  /*Ins maybeSame; Del: maybeOpp*/
        int   S = (s << 1) - 1;                 /*s: 0,1  --> S: -1,1 */
        if (BST_bal(p) == +S) {
            if (_(_avl_shorter)(BST_ctx path[d-1], !s, -S) == in)
                break;                  /*Del: done if tallr;Ins done if shrtr*/
        } else if (BST_bal(p) == -S*in) {
            BST_BAL_INC(p, S);
            break;
        } else                                  /* BAL_INC after +S test to  */
            BST_BAL_INC(p, S);                  /* never set bal outside the */
    }                                           /* minimal range [-1,+1].    */
}
#define BST_LINKIN_REBALANCE  _(_avl_rebalance)(BST_ctx path, d, 1);
#define BST_UNLINK_REBALANCE  _(_avl_rebalance)(BST_ctx path, d, 0);
