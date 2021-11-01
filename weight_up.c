BST_LKG void _(_weight_up)(BST_CTX BST_P *path[], int d, int dw) {
    int i;                                      /* inc or dec wt along path */
    for (i = 0; i < d; i++)
        BST_WT_INC(*path[i], dw);
}
