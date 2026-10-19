#include <stdio.h>
// this is a 2 way greedy approach because we are using a max heap to get the maximum element and then we are dividing it by 2 and pushing it back to the heap. We are also keeping track of the minimum element and updating it whenever we get a new minimum element. The deviation is calculated as the difference between the maximum and minimum elements in the heap. We keep doing this until we get an odd number as the maximum element in the heap.
typedef struct
{
    long long heap[1000];
    int size;
} MaxHeap;

void swap(long long *a, long long *b)
{
    long long temp = *a;
    *a = *b;
    *b = temp;
}

void push(MaxHeap *h, long long value)
{ // function to insert a new value into the max-heap. It takes a pointer to the MaxHeap structure (h) and the value to be inserted as input. The function first adds the new value to the end of the heap's array and increments the size of the heap. It then performs a "bubble-up" operation to maintain the max-heap property. Starting from the newly added index, it compares the value at that index with its parent node. If the newly added value is greater than its parent, it swaps them and continues this process until the max-heap property is restored or the root of the heap is reached. This ensures that the largest value is always at the root of the heap, allowing for efficient extraction of maximum values during processing.
    int i = h->size++;

    h->heap[i] = value;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (h->heap[parent] >= h->heap[i])
            break;

        swap(&h->heap[parent],
             &h->heap[i]);

        i = parent;
    }
}

long long pop(MaxHeap *h)
{ // function to remove and return the maximum value from the max-heap. It takes a pointer to the MaxHeap structure (h) as input. The function first stores the maximum value (the root of the heap) in a variable (result) and decrements the size of the heap. If there are still elements in the heap after removing the root, it replaces the root with the last element in the heap and performs a "bubble-down" operation to maintain the max-heap property. Starting from the root, it compares the current node with its left and right children, swapping it with the larger child if necessary. This process continues until the max-heap property is restored or a leaf node is reached. Finally, the function returns the maximum value that was removed from the heap, allowing for efficient extraction of maximum values during processing.
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
            int largest = i;

            if (left < h->size && h->heap[left] > h->heap[largest])
            {
                largest = left;
            }

            if (right < h->size &&
                h->heap[right] > h->heap[largest])
            {
                largest = right;
            }

            if (largest == i)
                break;

            swap(&h->heap[i], &h->heap[largest]);

            i = largest;
        }
    }

    return result;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    MaxHeap heap;
    heap.size = 0;

    long long minimum = 1000000000000000000LL;

    printf("Enter array elements:\n");

    for (int i = 0; i < n; i++)
    {
        long long x;
        scanf("%lld", &x);

        if (x % 2 == 1)
            x *= 2;

        if (x < minimum)
            minimum = x;

        push(&heap, x);
    }

    long long answer =
        heap.heap[0] - minimum;

    while (heap.size > 0)
    {
        long long maximum = heap.heap[0];

        if (maximum % 2 == 1)
            break;

        pop(&heap);

        maximum /= 2;

        if (maximum < minimum)
            minimum = maximum;

        push(&heap, maximum);

        long long currentDeviation =
            heap.heap[0] - minimum;

        if (currentDeviation < answer)
            answer = currentDeviation;
    }

    printf("Minimum deviation = %lld\n",
           answer);

    return 0;
}