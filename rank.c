//XXX This does not work for many cases
BST_LKG size_t _(_rank)(BST_CTX BST_P *path[], int d) {
    size_t r = *path[d-1] != BST_0 ? BST_wt(BST_ln(*path[d-1], 0)) : 0;
    for (d--; d > 0; d--)                       /* compute the rank of a path */
        if (path[d] != &(BST_ln(*path[d-1], 0)))    /* sum(0-kids of par) */
            r += BST_wt(BST_ln(*path[d-1], 0));     /* not on the path */
    return r;
}
