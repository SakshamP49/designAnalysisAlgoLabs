#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];// The pivot is chosen as the last element of the current subarray. This choice is arbitrary; other strategies (like choosing a random pivot) can also be used to improve performance in certain cases.
    int i = low;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }

    swap(&arr[i], &arr[high]); // After the loop, the pivot is placed in its correct position by swapping it with the element at index i. This ensures that all elements less than or equal to the pivot are on its left, and all elements greater than the pivot are on its right.

    return i;
}

int quickSelect(int arr[], int low, int high, int k) // The quickSelect() function is a recursive function that implements the Quickselect algorithm to find the k-th smallest element in an unsorted array. It takes four parameters: the array arr[], the starting index low, the ending index high, and the index k of the desired element (0-based). The function partitions the array around a pivot and recursively narrows down the search to either the left or right subarray based on the position of the pivot relative to k. If the pivot's index matches k, it returns the pivot value as the k-th smallest element.
{
    if (low == high)
        return arr[low];

    int pivotIndex = partition(arr, low, high); // The partition() function is called to rearrange the elements in the subarray arr[low..high] around a pivot. It returns the index of the pivot after partitioning, which helps determine whether to search in the left or right subarray for the k-th smallest element.

    if (pivotIndex == k)
        return arr[pivotIndex];
    else if (pivotIndex > k)
        return quickSelect(arr, low, pivotIndex - 1, k); // If the pivot's index is greater than k, it means the k-th smallest element lies in the left subarray. The function recursively calls itself with the left subarray (from low to pivotIndex - 1) to continue the search.
    else
        return quickSelect(arr, pivotIndex + 1, high, k);
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter the elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    if (n % 2 == 1)
    {
        float median = quickSelect(arr, 0, n - 1, n / 2);
        printf("Median = %.2f\n", median);
    }
    else
    {
        int *copy = (int *)malloc(n * sizeof(int)); // A copy of the original array is created to find the second middle element without altering the original array. This is necessary because quickSelect modifies the array during its execution, and we need to find both middle elements for an even-sized array.

        for (int i = 0; i < n; i++)
            copy[i] = arr[i];

        int middle1 = quickSelect(arr, 0, n - 1, n / 2 - 1); // The first middle element is found using quickSelect on the original array. For an even-sized array, the two middle elements are at indices n/2 - 1 and n/2. The first middle element is obtained by calling quickSelect with k = n/2 - 1.
        int middle2 = quickSelect(copy, 0, n - 1, n / 2);

        float median = (middle1 + middle2) / 2.0;

        printf("Median = %.2f\n", median);

        free(copy);
    }

    free(arr);

    return 0;
}// complexity of quickselect is O(n) on average, but O(n^2) in the worst case. The worst case occurs when the pivot chosen is always the smallest or largest element, leading to unbalanced partitions. However, with a good pivot selection strategy (like choosing a random pivot), the average case can be achieved consistently.