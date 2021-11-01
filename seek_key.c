BST_LKG int _(_seek_key)(BST_CTX BST_P *t, BST_P *path[], BST_KEY_QRY) {
    int d = 0, cmp;                             /* path=>node w/key | ins spot*/
    for (path[d++]=t; *(t = path[d-1])!=BST_0; path[d++] = &BST_ln(*t, cmp < 0))
        if (!(cmp = BST_CMP(*t)))
            return d;
    return -d;
}
