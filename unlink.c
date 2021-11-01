BST_LKG BST_P _(_unlink)(BST_CTX BST_P *path[], int d) {
    BST_P p = *path[d - 1];
    BST_P q;
    if (BST_ln(p, 0)==BST_0 || BST_ln(p, 1)==BST_0) {  /* External: Just hop */
        *path[d - 1] = BST_ln(p, (BST_ln(p, 0)==BST_0));
        BST_UP(BST_ln(p, (BST_ln(p, 0)==BST_0)), d > 1 ? *path[d - 2] : BST_0);
    } else {                                    /* Cannot hop internal nodes */
        int d0 = d;                             /* SWAP path[d0-1],path[d-1] */
        d += _(_seek_most)(BST_ctx &BST_ln(p, 1), path + d, 0); /* find 0most */
        *path[d0 - 1] = q = *path[d - 1];       /* swap: par(p) => par(q) */
        BST_UP(q, BST_up(p));                   /*   and up links */
        BST_META_SWP(q, p);                     /* swap non-(ln,augment) data */
        BST_WT(q,    BST_wt(p)   );             /* augmentation metadata */
        BST_LN(q, 0, BST_ln(p, 0));             /* 0-kid */
        BST_UP(BST_ln(p, 0), q);                /*   and up link */
        if (q != BST_ln(p, 1)) {                /* leaf is NOT very next link:*/
            BST_UP(BST_ln(q, 1), d > 1 ? *path[d - 2] : BST_0);
            BST_UP(BST_ln(p, 1), q);                /* both up links */
            BST_LN(*path[d - 2], 0, BST_ln(q, 1));  /* hop moved leaf */
            BST_LN(q, 1           , BST_ln(p, 1));  /* move 1-kid(0-leaf) */
        }
        path[d0] = &BST_ln(q, 1);               /* q has now replaced p */
    }
    BST_WT_UPDATE(BST_ctx path, d - 1, -1);     /* update weight along path */
    BST_UNLINK_REBALANCE                        /* engage any rebalancing */
    return p;
}
