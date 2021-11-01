BST_LKG int _(_stats)(BST_P p, int depth, long *ipl, long *n) {
    int h0 = 0, h1 = 0;                         /* Compute height/path length */
    if (!p) return 0;                           /* statistics */
    *ipl += depth;
    ++*n;
    if (BST_ln(p,0)) h0 = _(_stats)(BST_ln(p,0), depth + 1, ipl, n);
    if (BST_ln(p,1)) h1 = _(_stats)(BST_ln(p,1), depth + 1, ipl, n);
    return (h0 > h1 ? h0 : h1) + 1;
}
