#include <stdio.h>

#define MAX 100

// Quick Sort function
void qs(int arr[], int low, int high) {

    // Check if the array has more than one element
    if (low < high) {

        // Select the last element as pivot
        int pivot = arr[high];

        // Initialize i to track smaller elements
        int i = low - 1;

        // Traverse the array from low to high-1
        for (int j = low; j < high; j++) {

            // Check if current element is smaller than pivot
            if (arr[j] < pivot) {
                i++;

                // Swap current element with the next smaller position
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        // Place pivot in its correct sorted position
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        // Store the final position of pivot
        int pi = i + 1;

        // Sort the left part of the pivot
        qs(arr, low, pi - 1);

        // Sort the right part of the pivot
        qs(arr, pi + 1, high);
    }
}

int main() {
    int n;

    // Get the number of elements
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Check for invalid array size
    if (n <= 0 || n > MAX) {
        printf("Invalid array size!\n");
        return 1;
    }

    // Declare a fixed-size array
    int arr[MAX];

    // Get array elements from the user
    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Call Quick Sort to sort the entire array
    qs(arr, 0, n - 1);

    // Display the sorted array
    printf("Sorted array: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}
