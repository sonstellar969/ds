#include <stdio.h>

void mst(int arr[], int n) {
    if (n <= 1)
        return;

    int mid = n / 2;
    int left[mid], right[n - mid];

    for (int i = 0; i < mid; i++)
        left[i] = arr[i];

    for (int i = mid; i < n; i++)
        right[i - mid] = arr[i];

    mst(left, mid);
    mst(right, n - mid);

    int i = 0, j = 0, k = 0;

    while (i < mid && j < n - mid) {
        if (left[i] < right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < mid)
        arr[k++] = left[i++];

    while (j < n - mid)
        arr[k++] = right[j++];
}

int main() {
    int arr[] = {50, 20, 40, 10, 30};
    int n = sizeof(arr) / sizeof(arr[0]);

    mst(arr, n);

    printf("Sorted array: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}
