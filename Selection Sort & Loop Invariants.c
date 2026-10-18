#include <stdio.h>
void selectionSort(int arr[], int n)
{    for (int i = 0; i < n - 1; i++) // The index i marks the beginning of the unsorted portion. Each iteration places the smallest remaining element at index i.
    {      int minIndex = i; // Initially, the element at i is treated as the smallest candidate. The inner loop checks whether an even smaller element exists.
        for (int j = i + 1; j < n; j++)
        {       if (arr[j] < arr[minIndex]) // checks whether a smaller element has been found.
                minIndex = j; //remembers its index, not its value
        }
        // Swap the temporary variable preserves the original value of arr[i] while the two elements are exchanged.
//After this swap, the smallest element in the unsorted portion occupies index i.
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}
void printArray(int arr[], int n)
{   for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main()
{   int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("\nBefore sorting:\n");
    printArray(arr, n);
    selectionSort(arr, n);
    printf("\nAfter sorting:\n");
    printArray(arr, n);
    return 0;
}
/*STAGE	                EXPALINATION
1.Initialization	    Before the first iteration, the sorted portion is empty. An empty portion is sorted.
2.Maintenance	        Each iteration finds the minimum of the unsorted portion and places it at index i.The sorted portion grows by                      one element and remains sorted.
3.Termination	        The loop stops after \(n-1\) iterations. The first \(n-1\) elements are sorted, and the last element is                      necessarily in the correct position.         */

// Why is the best case still O(n^2)? Even if the array is already sorted, the algorithm still scans the remaining unsorted portion on every iteration to verify which element is smallest. Worst casr also O n sq.