#define BST_CTX
#define BST_ctx
#define BST_0       0
#define BST_NODE(p) (_(_POOL)[p])

BST_lkg _(_t) *_(_POOL);
BST_lkg BST_P  _(_POOL_head);

BST_LKG void _(_POOL_init)(size_t n, size_t sz) {
    void *memset(void *s, int c, size_t n);
    BST_P p;
    _(_POOL)      = (_(_t) *)malloc(n * sz);
    _(_POOL_head) = 1;
    memset(&BST_NODE(0), 0, sizeof(_(_t)));
    for (p = 1; p < n - 1; p++)
        BST_NODE(p).BST_LINK[0] = p + 1;
    BST_NODE(p).BST_LINK[0] = BST_0;
}

BST_LKG void _(_POOL_free)(void) { free(_(_POOL)); }

BST_LKG BST_P _(_alloc)(void) {
    BST_P p       = _(_POOL_head);
    _(_POOL_head) = BST_NODE(_(_POOL_head)).BST_LINK[0];
    return p;
}

BST_LKG void _(_free)(BST_P p) {
    _(_POOL)[p].BST_LINK[0] = _(_POOL_head);
    _(_POOL_head) = p;
}
