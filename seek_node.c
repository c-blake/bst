BST_LKG int _(_seek_node)(BST_CTX BST_P *t, BST_P *path[], int D, BST_P p) {
    void *memmove(void *dest, const void *src, size_t n);
    int   i = D - 1;                                    /* compute path to p */
    BST_P up;
    for (up = BST_up(p); up != BST_0; p = up, up = BST_up(p))
        path[i--] = &BST_ln(up, BST_ln(up, 1) == p);
    path[i] = t;
    memmove(&path[0], &path[i], (D - i) * sizeof path[0]);
    return D - i;
}
