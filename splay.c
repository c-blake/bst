BST_LKG void _(_splay)(BST_CTX BST_P *path[], int d) {
    for(/**/; d > 2; d -= 2) {
        int sp = (path[d-1] == &BST_ln(*path[d-2], 0)), /* !side(parent) */
            sg = (path[d-2] == &BST_ln(*path[d-3], 0)); /* !side(grandparent) */
        if (sp == sg) {                                 /* zig-zig dbl rot */
            _(_rot)(BST_ctx path[d-3], sg);
            _(_rot)(BST_ctx path[d-3], sp);
        } else {                                        /* zig-zag dbl rot */
            _(_rot)(BST_ctx path[d-2], sp);
            _(_rot)(BST_ctx path[d-3], sg);
        }
    }
    if (d == 2)                                         /* one final rotate */
        _(_rot)(BST_ctx path[0], (path[1] == &BST_ln(*path[0], 0)));
}
#define BST_LINKIN_REBALANCE  _(_splay)(BST_ctx path, d);
#define BST_UNLINK_REBALANCE  _(_splay)(BST_ctx path, d-1);
#define BST_SPLAY
