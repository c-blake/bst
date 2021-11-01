BST_LKG int _(_seek_most)(BST_CTX BST_P *t, BST_P *path[], int s) {
    int d = 0;                                  /* path => s-most node */
    for (path[d++] = t; *(t = path[d-1]) != BST_0; path[d++] = &BST_ln(*t, s))
        /**/;
    return d-1;
}
