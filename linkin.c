BST_LKG void _(_linkin)(BST_CTX BST_P *path[], int d, BST_P node) {
    *path[d - 1] = node;                        /* link it in */
    BST_UP(node, d > 1 ? *path[d - 2] : BST_0); /* assign parent */
    BST_WT_UPDATE(BST_ctx path, d, +1);         /* update weight along path */
    BST_LINKIN_REBALANCE                        /* optionally rebalance */
}
