#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int distance;
    int fuel;
} Station;

typedef struct
{
    int heap[1000];
    int size;
} MaxHeap;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push(MaxHeap *h, int value)
{ // function to insert a new value into the max-heap. It takes a pointer to the MaxHeap structure (h) and the value to be inserted as input. The function first adds the new value to the end of the heap's array and increments the size of the heap. It then performs a "bubble-up" operation to maintain the max-heap property. Starting from the newly added index, it compares the value at that index with its parent node. If the newly added value is greater than its parent, it swaps them and continues this process until the max-heap property is restored or the root of the heap is reached. This ensures that the largest value is always at the root of the heap, allowing for efficient extraction of maximum values during processing.
    int i = h->size++;

    h->heap[i] = value;
    while (i > 0)
    { // Bubble-up operation to maintain the max-heap property. It starts from the newly added index (i) and compares the value at that index with its parent node. If the value at index i is greater than its parent, it swaps them and continues this process until the max-heap property is restored or the root of the heap is reached. This ensures that the largest value is always at the root of the heap, allowing for efficient extraction of maximum values during processing.
        int parent = (i - 1) / 2;
        if (h->heap[parent] >= h->heap[i])
            break;
        swap(&h->heap[parent], &h->heap[i]);
        i = parent;
    }
}
int pop(MaxHeap *h)
{ // function to remove and return the maximum value from the max-heap. It takes a pointer to the MaxHeap structure (h) as input. The function first stores the maximum value (the root of the heap) in a variable (result) and decrements the size of the heap. If there are still elements in the heap after removing the root, it replaces the root with the last element in the heap and performs a "bubble-down" operation to maintain the max-heap property. Starting from the root, it compares the current node with its left and right children, swapping it with the larger child if necessary. This process continues until the max-heap property is restored or a leaf node is reached. Finally, the function returns the maximum value that was removed from the heap, allowing for efficient extraction of maximum values during processing.
    int result = h->heap[0];
    h->size--;
    h->heap[0] = h->heap[h->size];
    int i = 0;
    while (1)
    { // Bubble-down operation to maintain the max-heap property. It starts from the root (index 0) and compares the value at that index with its left and right children. If either child is greater than the current value, it swaps the current value with the larger child and continues this process until the max-heap property is restored or a leaf node is reached. This ensures that the largest value is always at the root of the heap, allowing for efficient extraction of maximum values during processing.
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if (left < h->size &&
            h->heap[left] > h->heap[largest])
        {
            largest = left;
        }

        if (right < h->size && h->heap[right] > h->heap[largest])
        {
            largest = right;
        }

        if (largest == i)
            break;

        swap(&h->heap[i], &h->heap[largest]);

        i = largest;
    }

    return result;
}

int compareStations(const void *a, const void *b)
{ // function to compare two Station structures based on their distances. It takes two pointers (a and b) to Station structures as input. The function first casts the pointers to Station pointers (x and y) for easier access to their fields. It then compares the distances of the two stations and returns the difference between them. This comparison function is used to sort the stations in ascending order of their distances from the starting point, which is necessary for processing the stations in the correct order when calculating the minimum number of refueling stops needed to reach the target distance.
    Station *x = (Station *)a;
    Station *y = (Station *)b;

    return x->distance - y->distance;
}

int main()
{
    int n;
    int D, F;

    printf("Enter target distance: ");
    scanf("%d", &D);

    printf("Enter initial fuel: ");
    scanf("%d", &F);

    printf("Enter number of stations: ");
    scanf("%d", &n);

    Station stations[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter distance and fuel for station %d: ", i + 1);

        scanf("%d %d", &stations[i].distance, &stations[i].fuel);
    }

    qsort(stations, n, sizeof(Station), compareStations);

    MaxHeap heap;
    heap.size = 0;

    int currentPosition = 0;
    int fuel = F;
    int stops = 0;

    for (int i = 0; i < n; i++)
    {
        if (stations[i].distance > D)
            break;
        int distanceNeeded = stations[i].distance - currentPosition;

        while (fuel < distanceNeeded)
        {
            if (heap.size == 0)
            {
                printf("Cannot reach the target.\n");
                return 0;
            }

            fuel += pop(&heap);
            stops++;
        }

        fuel -= distanceNeeded;
        currentPosition = stations[i].distance;

        push(&heap, stations[i].fuel); // Add the fuel from the current station to the max-heap for potential future use. The push function inserts the fuel amount of the current station into the max-heap, allowing the algorithm to keep track of available fuel sources. This enables the program to efficiently select the station with the maximum fuel when refueling is necessary, ensuring that the vehicle can reach its target distance with the minimum number of refueling stops. The &heap parameter is a pointer to the MaxHeap structure, which maintains the heap property and allows for efficient insertion and extraction of maximum values.
    }

    int distanceNeeded = D - currentPosition;

    while (fuel < distanceNeeded)
    {
        if (heap.size == 0)
        {
            printf("Cannot reach the target.\n");
            return 0;
        }

        fuel += pop(&heap);
        stops++;
    }

    printf("Minimum number of refuelling stops = %d\n",
           stops);

    return 0;
}