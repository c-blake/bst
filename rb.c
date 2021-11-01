BST_LKG void _(_rb_rebal_ins)(BST_P *path[], int d) {
    BST_P *root = path[0];
    BST_RED(*path[d-1]);
    for (/**/; d > 2 && BST_red(*path[d-2]); d -= 2) {
        int   s = (path[d-2] == &BST_ln(*path[d-3], 0));  /* d-2 is a 0-kid */
        BST_P p = BST_ln(*path[d-3], s);
        if (p != BST_0 && BST_red(p)) {
            BST_BLK(*path[d-2]);
            BST_RED(*path[d-3]);
            BST_BLK(p);
        } else {
            if (path[d-1] == &BST_ln(*path[d-2], s))     /* d-1 is an s-kid */
                _(_rot)(BST_ctx path[d-2], !s);
            BST_BLK(*path[d-2]);
            BST_RED(*path[d-3]);
            _(_rot)(BST_ctx path[d-3], s);
            break;
        }
    }
    BST_BLK(*root);
}
#define BST_LINKIN_REBALANCE _(_rb_rebal_ins)(BST_ctx path, d);

BST_LKG void _(_rb_rebal_del)(BST_CTX BST_P *path[], int d) {
    for (/**/; d >= 2; d--) {
        int   s = (path[d-1] == &BST_ln(*path[d-2], 0));  /* s==1 if x 0-kid */
        BST_P x = BST_ln(*path[d-2], !s);
        BST_P w = BST_ln(*path[d-2],  s);
        if (x != BST_0 && BST_red(x)) {
            BST_BLK(x);
            break;
        }
        if (BST_red(w)) {
            BST_BLK(w);
            BST_RED(*path[d-2]);
            _(_rot)(BST_ctx path[d-2], !s);
            path[d-1] = &BST_ln(*path[d-2], !s);
            d++;
            w = BST_ln(*path[d-2], s);
        }
        if ((BST_ln(w,!s) == BST_0 || !BST_red(BST_ln(w,!s))) &&
            (BST_ln(w, s) == BST_0 || !BST_red(BST_ln(w, s)))) {
                BST_RED(w);
        } else {
            if (BST_ln(w, s) == BST_0 || !BST_red(BST_ln(w, s))) {
                BST_BLK(BST_ln(w, !s));
                BST_RED(w);
                _(_rot)(BST_ctx &BST_ln(*path[d-2], s), s);
                w = BST_ln(*path[d-2], s);
            }
            BST_META_CPY(w, *path[d-2]);
            BST_BLK(*path[d-2]);
            if (BST_ln(w, s)) {
                BST_BLK(BST_ln(w, s));
            }
            _(_rot)(BST_ctx path[d-2], !s);
            break;
        }
    }
}
#define BST_UNLINK_REBALANCE if (!BST_red(p)) _(_rb_rebal_del)(BST_ctx path, d);
