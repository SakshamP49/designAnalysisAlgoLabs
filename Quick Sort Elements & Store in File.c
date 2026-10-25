#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b)
{ int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[], int low, int high)
{// The partition() function rearranges the elements in the subarray arr[low..high] around a pivot element. It selects the last element as the pivot and places it in its correct position in the sorted array. All elements less than or equal to the pivot are moved to its left, and all elements greater than the pivot are moved to its right. The function returns the index of the pivot after partitioning.
       int pivot = arr[high];
    int i = low - 1; // Initialize the index of the smaller element. It starts from one position before the low index, as we will increment it when we find elements less than or equal to the pivot.

    for (int j = low; j < high; j++)
    { // The loop iterates through the subarray from index low to high-1. For each element arr[j], it checks whether it is less than or equal to the pivot. If it is, the element is swapped with the element at index i, and i is incremented. This ensures that all elements less than or equal to the pivot are placed before index i.
        if (arr[j] <= pivot)
        {// If the current element arr[j] is less than or equal to the pivot, it is swapped with the element at index i+1. This effectively moves the smaller element to the left side of the pivot. The index i is then incremented to reflect the new position of the last smaller element.
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);// After the loop, the pivot is placed in its correct position by swapping it with the element at index i+1. This ensures that all elements less than or equal to the pivot are on its left, and all elements greater than the pivot are on its right.

    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);
// The quickSort() function is a recursive function that implements the Quick Sort algorithm. It takes three parameters: the array arr[], the starting index low, and the ending index high. The function partitions the array around a pivot and recursively sorts the left and right subarrays. The base case for the recursion is when low is no longer less than high, indicating that the subarray has one or zero elements and is already sorted.
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main()
{ // You have to first create an input file named "input.txt" in the same directory as this program. The input file should contain the number of elements (given as the first input) followed by the elements themselves, each on a new line.
    FILE *inputFile, *outputFile;
    int n;

    inputFile = fopen("input.txt", "r");

    if (inputFile == NULL)
    {
        printf("Error opening input file!\n");
        return 1;
    }

    fscanf(inputFile, "%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));// Dynamically allocate memory for the array based on the number of elements read from the input file. This allows the program to handle arrays of varying sizes without knowing the size at compile time.

    for (int i = 0; i < n; i++)
    {
        fscanf(inputFile, "%d", &arr[i]);
    }

    fclose(inputFile);// Close the input file after reading all the elements to free up system resources and avoid potential file access issues later in the program.

    quickSort(arr, 0, n - 1);

    outputFile = fopen("output.txt", "w");

    if (outputFile == NULL)
    {
        printf("Error creating output file!\n");
        free(arr);
        return 1;
    }

    fprintf(outputFile, "Sorted elements:\n");

    for (int i = 0; i < n; i++)
    {
        fprintf(outputFile, "%d ", arr[i]);
    }

    fclose(outputFile);

    printf("Sorting completed successfully.\n");
    printf("Check output.txt for sorted elements.\n");

    free(arr);

    return 0;
}