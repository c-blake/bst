BST_LKG int _(_seek_adj)(BST_CTX BST_P *path[], int d, int s) {
    if (BST_ln(*path[d-1], s) != BST_0)         /* path =>s-cessor(path[d-1]) */
        return d + _(_seek_most)(BST_ctx &BST_ln(*path[d-1], s), path + d, !s);
    for (d--; d > 0; d--)
        if (path[d] == &BST_ln(*path[d-1], !s))
            return d;
    return d;
}
