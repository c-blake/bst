BST_LKG int _(_seek_nth)(BST_CTX BST_P *t, BST_P *path[], size_t j) {
    int d = 0, tmp, i = j + 1;                  /* i=j+1 for 0-origin ranks */
    for (path[d++]=t; *(t=path[d-1])!=BST_0; path[d++] = &BST_ln(*t,tmp > 0)) {
        if (!(tmp = i - BST_wt(BST_ln(*t, 0)) - 1))
            return d;
        if (tmp > 0)
            i = tmp;
    }
    return -d;
}
