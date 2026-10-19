#include <stdio.h>

typedef struct
{
    long long heap[1000];
    int size;
} MinHeap;

void swap(long long *a, long long *b)
{
    long long temp = *a;
    *a = *b;
    *b = temp;
}

void push(MinHeap *h, long long value)
{ // function to insert a new value into the min-heap. It takes a pointer to the MinHeap structure (h) and the value to be inserted as input. The function first adds the new value to the end of the heap's array and increments the size of the heap. It then performs a "bubble-up" operation to maintain the min-heap property. Starting from the newly added index, it compares the value at that index with its parent node. If the newly added value is less than its parent, it swaps them and continues this process until the min-heap property is restored or the root of the heap is reached. This ensures that the smallest value is always at the root of the heap, allowing for efficient extraction of minimum values during processing.
    int i = h->size++;

    h->heap[i] = value;

    while (i > 0)
    { // Bubble-up operation to maintain the min-heap property. It starts from the newly added index (i) and compares the value at that index with its parent node. If the value at index i is less than its parent, it swaps them and continues this process until the min-heap property is restored or the root of the heap is reached. This ensures that the smallest value is always at the root of the heap, allowing for efficient extraction of minimum values during processing.
        int parent = (i - 1) / 2;

        if (h->heap[parent] <= h->heap[i])
            break;

        swap(&h->heap[parent],
             &h->heap[i]);

        i = parent;
    }
}

long long pop(MinHeap *h)
{ // function to remove and return the minimum value from the min-heap. It takes a pointer to the MinHeap structure (h) as input. The function first stores the minimum value (the root of the heap) in a variable (result) and decrements the size of the heap. If there are still elements in the heap after removing the root, it replaces the root with the last element in the heap and performs a "bubble-down" operation to maintain the min-heap property. Starting from the root, it compares the current node with its left and right children, swapping it with the smaller child if necessary. This process continues until the min-heap property is restored or a leaf node is reached. Finally, the function returns the minimum value that was removed from the heap, allowing for efficient extraction of minimum values during processing.
    long long result = h->heap[0];

    h->size--;

    if (h->size > 0)
    {
        h->heap[0] =
            h->heap[h->size];

        int i = 0;

        while (1)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < h->size && h->heap[left] < h->heap[smallest])
            {
                smallest = left;
            }

            if (right < h->size && h->heap[right] < h->heap[smallest])
            { // Compare the right child with the current smallest value. If the right child is smaller than the current smallest value, update the smallest index to be the right child's index. This ensures that we are always comparing the current node with both of its children to maintain the min-heap property, where the parent node is less than or equal to its children.
                smallest = right;
            }

            if (smallest == i)
                break;

            swap(&h->heap[i], &h->heap[smallest]);

            i = smallest;
        }
    }

    return result;
}

int main()
{
    int n;

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    MinHeap heap;
    heap.size = 0;

    printf("Enter stick lengths:\n");

    for (int i = 0; i < n; i++)
    {
        long long length;
        scanf("%lld", &length);

        push(&heap, length);
    }

    long long totalCost = 0;

    while (heap.size > 1)
    {
        long long a = pop(&heap);  // Remove the smallest stick length from the min-heap and store it in variable 'a'. This represents the first stick to be connected.
        long long b = pop(&heap);

        long long sum = a + b;

        totalCost += sum;

        push(&heap, sum);
    }

    printf("Minimum total cost = %lld\n",
           totalCost);

    return 0;
}