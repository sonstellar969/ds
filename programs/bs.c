#include <stdio.h>

int bs(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + high / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main() {
    int arr[] = {1, 5, 10, 15, 20, 30, 40, 45};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = bs(arr, n, 99);
    if (result != -1)
        printf("Found at index %d\n", result);
    else
        printf("Not found\n");
    return 0;
}