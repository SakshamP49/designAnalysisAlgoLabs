#include <stdio.h>
#include <stdlib.h>
// YOU HAVE TO FIRST CREATE AN INPUT FILE NAMED "input.txt" IN THE SAME DIRECTORY AS THIS PROGRAM. THE INPUT FILE SHOULD CONTAIN THE NUMBER OF ELEMENTS (given as the first input) FOLLOWED BY THE ELEMENTS THEMSELVES, EACH ON A NEW LINE. FOR EXAMPLE:
// 5
// 12
// 4
// 7    
// 1
// 9
// THIS PROGRAM WILL READ THE ELEMENTS FROM "input.txt", SORT THEM USING HEAP SORT( but before giving these six elements, you must give size of array as first input).
void swap(int *a, int *b)
{ int temp = *a;
    *a = *b;
    *b = temp;
}
void heapify(int arr[], int n, int i)
{ // The heapify() function is a recursive function that ensures the subtree rooted at index i satisfies the max-heap property. It takes three parameters: the array arr[], the size of the heap n, and the index i of the current node being heapified. The function compares the current node with its left and right children, and if either child is larger than the current node, it swaps them and recursively calls heapify() on the affected subtree to maintain the max-heap property.
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2; // The left and right child indices are calculated based on the current index i. In a zero-based array representation of a binary heap, the left child of a node at index i is located at index 2*i + 1, and the right child is located at index 2*i + 2. This allows us to easily navigate the heap structure using simple arithmetic on the indices.

    if (left < n && arr[left] > arr[largest])
       largest = left;
    if (right < n && arr[right] > arr[largest])
      largest = right;
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest); // If the largest element is not the current node, we swap the current node with the largest child and recursively call heapify() on the affected subtree. This ensures that the max-heap property is maintained throughout the heap.
    }
}
void heapSort(int arr[], int n)
{  // Build Max Heap. array is rearranged to satisfy the max-heap property, where each parent node is greater than or equal to its children. This is done by calling heapify() on all non-leaf nodes starting from the last non-leaf node down to the root node. The last non-leaf node is located at index n/2 - 1 (for zero based indexing) and we iterate backwards to the root node at index 0.
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);// The loop iterates from the last non-leaf node (n/2 - 1) down to the root node (index 0). For each node, heapify() is called to ensure that the subtree rooted at that node satisfies the max-heap property. This process effectively builds a max-heap from the unsorted array, preparing it for the sorting phase of the heap sort algorithm.
    // Extract elements from heap
    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}
int main()
{  FILE *inputFile, *outputFile;
    int n;
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL)
    {
        printf("Error opening input file!\n");
        return 1;
    }
    fscanf(inputFile, "%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
       fscanf(inputFile, "%d", &arr[i]); // Read n elements from the input file and store them in the dynamically allocated array arr. The fscanf() function is used to read each integer from the file, and the loop iterates n times to fill the array with the specified number of elements.
    fclose(inputFile);
    heapSort(arr, n);
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL)
    {
        printf("Error creating output file!\n");
        free(arr);
        return 1;
    }
    fprintf(outputFile, "Sorted elements:\n");
    for (int i = 0; i < n; i++)
         fprintf(outputFile, "%d ", arr[i]);
    
    fclose(outputFile);
    printf("Sorting completed successfully.\n");
    printf("Check output.txt for sorted elements.\n");
    free(arr);
    return 0;
}