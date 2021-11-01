#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av) {
    int   i, w = ac > 1 ? atoi(av[1]) : 10, n = ac - 2;
    float x[n];

    if (n < 1)
        return printf("%s <nWin> num num ...\n", av[0]);
    for (i = 0; i < n; i++)
        x[i] = atof(av[i + 2]);
    for (i = 0; i < n; i++) {
        if (i >= w)
            printf("-%g\n", x[i - w]);
        printf("+%g\n", x[i]);
    }
    return 0;
}
