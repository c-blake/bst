BST_LKG BST_P _(_init)(BST_CTX BST_P p) {       /* Init a BST node's metadata */
    if (p == BST_0)
        return p;
    BST_LN(p, 0, BST_0);                        /* Links */
    BST_LN(p, 1, BST_0);
    BST_WT(p,    0);                            /* Augmentation */
    BST_META_INIT(p);                           /* Balance MetaData */
    return p;
}
