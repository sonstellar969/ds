#include <stdio.h>
#include <stdlib.h>                     // malloc / free

void swap(int *a, int *b) {             // swap via pointers
    int t = *a;
    *a = *b;
    *b = t;
}

int part(int a[], int lo, int hi) {     // put pivot in place, return index
    int p = a[hi];                      // last element is pivot
    int i = lo - 1;                     // end of smaller-than-pivot section

    for (int j = lo; j < hi; j++) {     // scan everything except pivot
        if (a[j] < p) {                 // belongs left of pivot
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[hi]);            // place pivot after smaller section
    return i + 1;
}

void qs(int a[], int lo, int hi) {      // sort range [lo..hi]
    if (lo < hi) {                      // stop if 0 or 1 element
        int pi = part(a, lo, hi);       // pivot now fixed
        qs(a, lo, pi - 1);              // sort left
        qs(a, pi + 1, hi);              // sort right
    }
}

void print(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Invalid\n");
        return 0;
    }

    int *a = (int *)malloc(n * sizeof(int));   // size decided at runtime
    if (a == NULL) {
        printf("Malloc failed\n");
        return 0;
    }

    printf("Enter %d nums: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    printf("Before: ");
    print(a, n);

    qs(a, 0, n - 1);

    printf("After: ");
    print(a, n);

    free(a);                            // give memory back
    return 0;
}
