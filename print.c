BST_LKG void _(_print)(BST_P n, FILE *f, BST_P *path[], int d, int depth) {
    int i, inPath = 0;                          /* print the tree (for fun!) */
    if (n == BST_0)                             /* fringe; done */
        return (void)fprintf(f, "%*s%s\n", BST_PR_INDENT*depth,"", BST_PR_NIL);
    _(_print)(BST_ln(n, 0), f, path, d, depth + 1);
    for (i = 0; i < d; i++)                     /* set path markup flag */
        if (*path[i] == n) inPath = 1;
    fprintf(f, "%*s", BST_PR_INDENT*depth, ""); /* indent prop.to depth */
    fprintf(f, BST_PR(n));                      /* user node fmt,data */
    _(_print)(BST_ln(n, 1), f, path, d, depth + 1);
}
