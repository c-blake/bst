BST_LKG int _(_seek_keyS)(BST_CTX BST_P *t, BST_P *path[], int s, BST_KEY_QRY) {
    int d = 0, cmp, d_ret = 0;                  /* path=>node w/key | ins spot*/
    if (s) {                                            /*s=1: bias-0-ward */
      for (path[d++]=t; *(t=path[d-1])!=BST_0; path[d++]=&BST_ln(*t, cmp<=0))
        if (!(cmp = BST_CMP(*t)))
          d_ret = d;
    } else                                              /*s=0: bias-1-ward */
      for (path[d++]=t; *(t=path[d-1])!=BST_0; path[d++]=&BST_ln(*t, cmp< 0))
        if (!(cmp = BST_CMP(*t)))
          d_ret = d;
    return d_ret ? d_ret : -d;      /* seek_keyS+unlink=pop(0:front,1:back) */
}

BST_LKG int _(_seek_push)(BST_CTX BST_P *path[], int d, int s) {
    if (d <= 0)                                 /* NOTE: push(keyS(s),s) =>   */
        return -d;                              /*       push(0:front,1:back) */
    if (BST_ln(*path[d-1], s) != BST_0) {       /* BUT 1,0 or 0,1 do not      */
        d = _(_seek_adj)(BST_ctx path, d, s);   /* do anything very useful    */
        path[d] = &BST_ln(*path[d-1], !s);
    } else
        path[d] = &BST_ln(*path[d-1],  s);
    return d + 1;
}
