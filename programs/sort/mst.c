
#include <stdio.h>

void mst(int arr[], int n) {

    if (n <= 1) {
        return;
    }

    int mid = n / 2;

    int left[mid], right[n - mid];

    // Copy elements into left array
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }

    // Copy elements into right array
    for (int i = mid; i < n; i++) {
        right[i - mid] = arr[i];
    }

    // Recursively sort left and right arrays
    mst(left, mid);
    mst(right, n - mid);

    int i = 0, j = 0, k = 0;

    // Merge both sorted arrays
    while (i < mid && j < n - mid) {

        if (left[i] < right[j]) {
            arr[k++] = left[i++];
        }
        else {
            arr[k++] = right[j++];
        }
    }

    // Copy remaining elements from left array
    while (i < mid) {
        arr[k++] = left[i++];
    }

    // Copy remaining elements from right array
    while (j < n - mid) {
        arr[k++] = right[j++];
    }
}

int main() {

    int n;

    printf("Enter the number of elements: ");

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size!\n");
        return 1;
    }

    int arr[n];

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Perform Merge Sort
    mst(arr, n);

    // Display sorted array
    printf("Sorted array: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}
