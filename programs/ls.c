#include <stdio.h>

int ls(int arr[], int n, int target) {
    for (int i=0; i<n; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

int main() {
    int arr[] = {12,44,5,6,13,546};
    int n = sizeof(arr)/sizeof(arr[0]);

    int result = ls(arr, n, 546);
    if (result != -1)
        printf("Found at index %d\n", result);
    else
        printf("Not found\n");
    return 0;
}