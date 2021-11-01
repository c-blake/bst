BST_LKG int _(_seek_most)(BST_CTX BST_P *t, BST_P *path[], int s);
BST_LKG int _(_seek_adj) (BST_CTX BST_P *path[], int d, int s);
#if defined(BST_KEY_QRY) && defined(BST_CMP)
    BST_LKG int _(_seek_key) (BST_CTX BST_P *t, BST_P *path[], BST_KEY_QRY);
    BST_LKG int _(_seek_keyS)(BST_CTX BST_P *t, BST_P *path[], int s, BST_KEY_QRY);
    BST_LKG int _(_seek_push)(BST_CTX BST_P *path[], int d, int s);
#endif
#ifdef BST_WEIGHT
    BST_LKG int    _(_seek_nth) (BST_CTX BST_P *t, BST_P *path[], size_t j);
    BST_LKG size_t _(_rank)     (BST_CTX BST_P *path[], int d);
    BST_LKG void   _(_weight_up)(BST_CTX BST_P *path[], int d, int dw);
#endif
#ifdef BST_PARENT
    BST_LKG int _(_seek_node)(BST_CTX BST_P *t, BST_P *path[], int D, BST_P p);
#endif
BST_LKG void _(_rot)(BST_CTX BST_P *r, int s);
#ifdef BST_META
#   ifdef BST_AVL
        BST_LKG int  _(_avl_shorter)  (BST_CTX BST_P *pp, int s, int S);
        BST_LKG void _(_avl_rebalance)(BST_CTX BST_P *path[], int d, int in);
#   else
        BST_LKG void _(_rb_rebal_ins)(BST_P *path[], int d);
        BST_LKG void _(_rb_rebal_del)(BST_CTX BST_P *path[], int d);
#   endif
#else
#   ifdef BST_WEIGHT
        BST_LKG void _(_ell_rebalance)(BST_CTX BST_P *path[], int d, int in);
#   else
        BST_LKG void _(_splay)(BST_CTX BST_P *path[], int d);
#   endif
#endif
BST_LKG BST_P _(_init)  (BST_CTX BST_P p);
BST_LKG void  _(_linkin)(BST_CTX BST_P *path[], int d, BST_P node);
BST_LKG BST_P _(_unlink)(BST_CTX BST_P *path[], int d);
