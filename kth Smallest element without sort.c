#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[], int low, int high) // The partition() function rearranges the elements in the subarray arr[low..high] around a pivot element. It selects the last element as the pivot and places it in its correct position in the sorted array. All elements less than or equal to the pivot are moved to its left, and all elements greater than the pivot are moved to its right. The function returns the index of the pivot after partitioning.
{   int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++)
    {// The loop iterates through the subarray from index low to high-1. For each element arr[j], it checks whether it is less than or equal to the pivot. If it is, the element is swapped with the element at index i, and i is incremented. This ensures that all elements less than or equal to the pivot are placed before index i.
        if (arr[j] <= pivot)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[high]);
// After the loop, the pivot is placed in its correct position by swapping it with the element at index i. This ensures that all elements less than or equal to the pivot are on its left, and all elements greater than the pivot are on its right.
    return i;
}
int quickSelect(int arr[], int low, int high, int k)
{// The quickSelect() function is a recursive function that implements the Quickselect algorithm to find the k-th smallest element in an unsorted array. It takes four parameters: the array arr[], the starting index low, the ending index high, and the index k of the desired element (0-based). The function partitions the array around a pivot and recursively narrows down the search to either the left or right subarray based on the position of the pivot relative to k. If the pivot's index matches k, it returns the pivot value as the k-th smallest element.
    if (low <= high)
    {      int pivotIndex = partition(arr, low, high);
        if (pivotIndex == k)
            return arr[pivotIndex];
        else if (pivotIndex > k)
            return quickSelect(arr, low, pivotIndex - 1, k);// If the pivot's index is greater than k, it means the k-th smallest element lies in the left subarray. The function recursively calls itself with the left subarray (from low to pivotIndex - 1) to continue the search.
        else
            return quickSelect(arr, pivotIndex + 1, high, k);
    }
    return -1;
}
int main()
{  int n, k;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Enter K: ");
    scanf("%d", &k);
    if (k < 1 || k > n)
          printf("Invalid value of K\n");
    else
    { 
        int result = quickSelect(arr, 0, n - 1, k - 1);
        printf("%dth smallest element = %d\n", k, result);
    }
    free(arr);// The dynamically allocated memory for the array arr is freed to prevent memory leaks. This is important in C programming, as failing to free allocated memory can lead to increased memory usage and potential crashes in long-running programs.
    return 0;
}// time complexity of quickselect is O(n) on average, but O(n^2) in the worst case. The worst case occurs when the pivot chosen is always the smallest or largest element, leading to unbalanced partitions. However, with a good pivot selection strategy (like choosing a random pivot), the average case can be achieved consistently.