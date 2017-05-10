#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int **a = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        a[i] = (int *) malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = (i + 1) * (j + 1);
        }
    }
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    while (x1 != 0) {
        if (x1 < 1 || x1 > n || y1 < 1 || y1 > n || x2 < 1 || x2 > n || y2 < 1 || y2 > n) {
            printf("Your requirements are wrong");
        }
        for (int i = x1-1; i < x2; i++) {
            for (int j = y1-1; j < y2; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    }
    for (int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
    return 0;
}