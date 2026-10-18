#include <stdio.h>
// Aim: Find both the minimum and maximum elements of an array while keeping the number of comparisons low.
typedef struct
{ // Each recursive call must return two values: the minimum and maximum of its own subarray. C functions cannot directly return two separate integers, so the structure groups them into one return value.
    int min;
    int max;
} Result;
Result findMinMax(int arr[], int low, int high)
{   Result result, left, right;
    // Only one element
    if (low == high)
    { // A single element is automatically both the minimum and the maximum of that subarray. No comparison is required.
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }
    // Two elements
    if (high == low + 1)
    { // Only one comparison is needed to decide which of the two elements is smaller and which is larger. This avoids recursively splitting such a small subarray.
        if (arr[low] < arr[high])
        {          result.min = arr[low];
            result.max = arr[high];
        }
        else
        {           result.min = arr[high];
            result.max = arr[low];
        }
        return result;
    }
    int mid = (low + high) / 2; // Splits the current subarray into two parts- DIVIDE
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high); // The recursive calls independently return the minimum and maximum of each half- CONQUER
    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;
    if (left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;
    return result;
}
int main()
{   int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    Result result = findMinMax(arr, 0, n - 1);
    printf("\nMinimum = %d\n", result.min);
    printf("Maximum = %d\n", result.max);
    return 0;
}