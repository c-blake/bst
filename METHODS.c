#if !defined(BST_LINK) /* Helper header for when BST_NODE(ptr).MEMBERS works */
#   error "This instantiation helper file requires #include context to define.."
#   error "..BST_LINK[, BST_META, BST_WEIGHT] - names of native struct fields."
#endif

#define BST_LN(n, i, v) (BST_NODE(n).BST_LINK[(i)] = (v))
#define BST_ln(n, i)    (BST_NODE(n).BST_LINK[(i)])

#ifdef BST_PARENT                   /* parent access if user tells us how */
#   define BST_UP(n, v)     (BST_NODE(n).BST_PARENT = (v))
#   define BST_up(n)        ((n) == BST_0 ? 0 : BST_NODE(n).BST_PARENT)
#   include "seek_node.c"               /* structural query */
#else  /* BST_PARENT */                 /* No PARENT member; provide dummies */
#   define BST_UP(n, v)     ((void)0)   /* for augmentation maintenance that */
#   define BST_up(n)        (0)         /* (hopefully!) compile to nothing. */
#endif /* BST_PARENT */

#include "seek_most.c"              /* purely structural seekers: extreme.. */
#include "seek_adj.c"               /*                      ..and adjacent. */

#if defined BST_KEY_T && defined BST_KEY && !defined BST_KEY_QRY && !defined BST_CMP
#   define BST_KEY_QRY  BST_KEY_T qry
#   define BST_CMP(n)   (BST_NODE(n).BST_KEY - qry)
#endif
#if defined(BST_KEY_QRY) && defined(BST_CMP)
#   include "seek_key.c"            /* keyed access if user tells us how */
#   include "seek_keyS.c"           /* seek_keyS+push = dup key support */
#endif /* BST_KEY_QRY & BST_CMP */

#ifdef BST_WEIGHT                   /* ranked access if user tells us how */
#   define BST_WT(n, W)     (BST_NODE(n).BST_WEIGHT = (W))
#   define BST_WT_INC(n,dw) (BST_NODE(n).BST_WEIGHT += (dw))
#   define BST_wt(n)        ((n) == BST_0 ? 0 : BST_NODE(n).BST_WEIGHT)
#   include "seek_nth.c"            /* ranked access */
#   include "rank.c"                /* augmentation structural query */
#   include "weight_up.c"           /* augmentation maintenance */
#   define  BST_WT_UPDATE   _(_weight_up)
#else  /* BST_WEIGHT */                 /* No WEIGHT member; provide dummies */
#   define BST_WT(n, W)     ((void)0)   /* for augmentation maintenance that */
#   define BST_WT_INC(n,dw) ((void)0)   /* (hopefully!) compile to nothing. */
#   define BST_wt(n)        (0)
#   define BST_WT_UPDATE    (void)      /*XXX -Wno-unused-value; VA_ARGS? */
#endif /* BST_WEIGHT */

#include "rot.c"                    /* Re-balancing primitive */
#ifdef BST_META                     /* DEF OF META TRIGGERS REBALANCE CODE */
#   define BST_META_CPY(p,q)   (BST_NODE(p).BST_META  = BST_NODE(q).BST_META)
#   define BST_META_SWP(p,q)   { unsigned char      t = BST_NODE(p).BST_META; \
                                 BST_NODE(p).BST_META = BST_NODE(q).BST_META; \
                                 BST_NODE(q).BST_META = t; }
#   ifdef BST_AVL                  /* AVL mode; meta is balance */
#       define BST_BAL(n, B)    (BST_NODE(n).BST_META  = (B))
#       define BST_BAL_INC(n,db)(BST_NODE(n).BST_META += (db))
#       define BST_bal(n)       (BST_NODE(n).BST_META)
#       define BST_META_INIT(n) BST_BAL(n, 0)       /*calloc/memset? */
#       include "avl.c"
#   else                           /* Red-Black mode; meta is redness */
#       define BST_red(n)       (BST_NODE(n).BST_META ==1) /*Can flip sense so*/
#       define BST_RED(n)       (BST_NODE(n).BST_META = 1) /*calloc is enough.*/
#       define BST_BLK(n)       (BST_NODE(n).BST_META = 0)
#       define BST_META_INIT(n) BST_RED(n)          /* see calloc note above */
#       include "rb.c"
#   endif
#else
#   define BST_META_CPY(p,q)    (void)0
#   define BST_META_SWP(p,q)    (void)0
#   define BST_META_INIT(n)     (void)0
#   ifdef BST_WEIGHTED
#       include "ell.c"
#   else
#       include "splay.c"
#   endif
#endif
#include "init.c"               /* Down here since it uses META_INIT. */
#include "linkin.c"             /* These use REBALANCE macros defined in */
#include "unlink.c"             /* _avl/_rb above.  So, they come last.  */
