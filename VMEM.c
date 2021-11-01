#define BST_CTX             /*FunArg recv ctxt by which prog interprets links */
#define BST_ctx             /*FunArg recv ctxt by which prog interprets links */
#define BST_NODE(n)         (*(n))  /* n => tokens compiler can apply '.' to */
#define BST_0               NULL
BST_LKG BST_P _(_alloc)(void) { BST_P p; return (BST_P)malloc(sizeof *p); }
BST_LKG void  _(_free)(BST_P p) { free((void*)p); }
