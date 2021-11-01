#if !defined(BST_P) /* Define member hook to hold BST metadata a la BSD queue */
#   error "This instantiation helper file requires #include context to define.."
#   error "..BST_P - the pointer type to the parent object being managed, and"
#   error "..optionally define BST_BALANCED, BST_WEIGHTED, BST_LKG, BST_lkg."
#endif

#if !defined(BST_MEMBER)
#   ifdef _
#       define BST_MEMBER _(_bst)           /* users w/2 or more MEMBERs */
#   else                                    /* need to know to def _ first! */
#       define BST_MEMBER __bst             /* and lazy users need to not */
#   endif                                   /* collide with this name! */
#   define BST_MEMBER_HOOK bst_member_t BST_MEMBER
#endif
#if defined BST_META || defined BST_RB || defined BST_AVL
#   define BST_BALANCED
#endif
#if defined BST_WEIGHT
#   define BST_WEIGHTED
#endif
#if defined BST_PARENT
#   define BST_PARENTED
#endif

typedef struct {
    BST_P    ln[2];
#if defined BST_PARENTED
    BST_P    up;
#   define  BST_PARENT BST_MEMBER.up
#endif
#if defined BST_BALANCED && defined BST_WEIGHTED
    signed   meta : 2;                  /* with gcc4, Intel corei7 a bitfield */
    unsigned wt   : 30;                 /* is only a couple cycles slower. */
#   define BST_META   BST_MEMBER.meta
#   define BST_WEIGHT BST_MEMBER.wt
#elif defined BST_WEIGHTED              /* no balance data, but weight data */
    unsigned wt;
#   define BST_WEIGHT BST_MEMBER.wt
#elif defined BST_BALANCED              /* no weight data, but balance data */
    signed char meta;
#   define BST_META   BST_MEMBER.meta
#endif
} bst_member_t;

#define BST_LINK  BST_MEMBER.ln         /* name of link field for METHODS.c */

#ifndef BST_LKG
#define BST_LKG   static inline         /* default function linkage */
#endif
#ifndef BST_lkg
#define BST_lkg   static                /* default variable linkage */
#endif
