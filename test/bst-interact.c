#include <stdio.h>  /* printf puts fgets fputs sscanf */
#include <stdlib.h> /* getenv abs */

#define _(_x)       c ## _x             /* NAMESPACE FOR GENERATED METHODS */
#define BST_P       unsigned short      /* Bind ptr to type to our node ptr */ 
#define BST_PARENTED                    /* we want _path(p) */
#include "bst/MEMBER.h"             /* for BST_MEMBER_HOOK */

#define BST_KEY_T    int                /* Define Key Field/Node Type */
#define BST_KEY      key
typedef struct _(_s) { BST_MEMBER_HOOK; BST_KEY_T BST_KEY; } _(_t);

#include "bst/POOL.c"               /* node refs are virtual memory ptrs */
#include "bst/METHODS.c"            /* 3 simple named struct members */

#define BST_PR_INDENT   10              /* Niceties for interactive prog */
#define BST_PR_NIL      "[7m  [m"   /*   nil => A couple inverse spaces */
#if defined BST_AVL                     /* AVL mode; print -,=,+ */
# define BST_PR(n) "[7%sm%#x:%c,w%d,k%d,u%#x)[m\n", inPath ? ";1" : "", n,\
                   "-=+"[BST_bal(n)+1], BST_wt(n), BST_NODE(n).key, BST_up(n)
#elif defined BST_RB                    /* Red-Black mode: nice colors */
# define BST_PR(n) "[4%c%sm%#x:w%d,k%d,u%#x[m\n", "01"[BST_red(n)], \
                  inPath?";93;1":";97", n, BST_wt(n), BST_NODE(n).key, BST_up(n)
#else                                   /* Vanilla/Ell/Splay BST mode */
# define BST_PR(n) "[7%sm%#x:w%d,k%d,u%#x[m\n", inPath ? ";1" : "", n, \
                   BST_wt(n), BST_NODE(n).key, BST_up(n)
#endif
#include "bst/ck.c"                 /* _ck: check tree properties */
#include "bst/print.c"              /* a pretty printer */
#include "bst/stats.c"              /* and stats collector */

BST_P _(_new)(int key) {
    BST_P p = _(_alloc)();
    BST_NODE(p).key = key;
    return _(_init)(p);
}

int main(int c __attribute__((__unused__)),char**v __attribute__((__unused__))){
    BST_P *path[32] = { 0 };    /* init to make debugging easier */
    BST_P  root = 0;            /* init strictly necessary to make empty tree */
    int    d = 0, nE, s, k, Q=!!getenv("Q"), V=!!getenv("V"), ck=!!getenv("CK");
    char   buf[256], cmd[32];

    c_POOL_init(65536, sizeof(c_t));
    while (fgets(buf, sizeof buf, stdin) && sscanf(buf,"%s %d", cmd, &k) >= 1) {
      if (V) fputs(buf, stdout);
      switch (cmd[0]) {
ck:     case 'c': nE = 0; c_ck(root, &nE); if (BST_up(root) != BST_0) nE++;
                  if (nE) { c_print(root, stdout, path, abs(d), 0); return 1; }
                  break;
        case 'p': printf("--\n"); c_print(root, stdout, path, abs(d), 0); break;
        case 's': printf("%d\n", d = c_seek_key(&root, path, k));         break;
        case 'm': d = c_seek_most(&root, path, k);                        break;
        case 'P': printf("PATH:");
                  for (k = 0; k < abs(d); k++)
                      printf(" %#x", *path[k]);
                  puts(""); break;
        case 'a': d = c_seek_adj(path, d, k); break;
        case 'h': { long ipl = 0, n = 0, h = c_stats(root, 0, &ipl, &n);
                    printf("N: %ld H: %ld <depth>: %g\n", n, h, ipl/(double)n);
                    break; }
        case 'i': if ((d = c_seek_key(&root, path, k)) <= 0)
                      c_linkin(path, -d, c_new(k));
                  else if (!Q)
                      printf("%d present\n", k);
                  if (ck) goto ck;
                  break;
        case 'd': if ((d = c_seek_key(&root, path, k)) > 0)
                      c_free(c_unlink(path, d));
                  else if (!Q)
                      printf("%d not found\n", k);
                  if (ck) goto ck;
                  break;
        case '+': s = cmd[1] - '0';                     /* '0'=front,'1'=back */
                  d = c_seek_push(path, c_seek_keyS(&root, path, s, k), s);
                  c_linkin(path, d, c_new(k));
                  if (ck) goto ck;
                  break;
        case '-': s = cmd[1] - '0';                     /* '0'=front,'1'=back */
                  if ((d = c_seek_keyS(&root, path, s, k)) > 0)
                      c_free(c_unlink(path, d));
                  else if (!Q)
                      printf("%d not found\n", k);
                  if (ck) goto ck;
                  break;
#ifdef BST_WEIGHTED
        case 'r': printf("rnk: %ld\n",
                         c_rank(path, abs(d = c_seek_key(&root, path, k))));
                  break;
        case 'n': if ((d = c_seek_nth(&root, path, k)) > 0)
                      printf("%d th key: %d\n", k, BST_NODE(*path[d-1]).key);
                  else
                      printf("No %d th\n", k);
                  break;
#endif
        case '0': printf("0-rot w/root %d\n",*path[k]); c_rot(path[k],0); break;
        case '1': printf("1-rot w/root %d\n",*path[k]); c_rot(path[k],1); break;
#ifdef BST_SPLAY
        case 'S': c_splay(path, abs(d)); break; /* undef BST_WEIGHTED to test */
#endif
#ifdef BST_PARENTED
        case 'w': d = c_seek_node(&root, path, 32, k); break;
#endif
      }
    }
    return 0;
}
