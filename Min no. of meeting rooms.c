#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int start;
    int end;
} Meeting;

typedef struct
{
    int heap[1000];
    int size;
} MinHeap;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push(MinHeap *h, int value)
{ // function to insert a new value into the min-heap. It takes a pointer to the MinHeap structure (h) and the value to be inserted as input. The function first adds the new value to the end of the heap's array and increments the size of the heap. It then performs a "bubble-up" operation to maintain the min-heap property. Starting from the newly added index, it compares the value at that index with its parent node. If the newly added value is less than its parent, it swaps them and continues this process until the min-heap property is restored or the root of the heap is reached. This ensures that the smallest value is always at the root of the heap, allowing for efficient extraction of minimum values during processing.
    int i = h->size++;

    h->heap[i] = value;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (h->heap[parent] <= h->heap[i])
            break;

        swap(&h->heap[parent], &h->heap[i]);

        i = parent;
    }
}

int pop(MinHeap *h)
{ // function to remove and return the minimum value from the min-heap. It takes a pointer to the MinHeap structure (h) as input. The function first stores the minimum value (the root of the heap) in a variable (result) and decrements the size of the heap. If there are still elements in the heap after removing the root, it replaces the root with the last element in the heap and performs a "bubble-down" operation to maintain the min-heap property. Starting from the root, it compares the current node with its left and right children, swapping it with the smaller child if necessary. This process continues until the min-heap property is restored or a leaf node is reached. Finally, the function returns the minimum value that was removed from the heap, allowing for efficient extraction of minimum values during processing.
    int result = h->heap[0];

    h->size--;

    if (h->size > 0)
    {
        h->heap[0] =
            h->heap[h->size];

        int i = 0;

        while (1)
        { // Bubble-down operation to maintain the min-heap property. It starts from the root (index 0) and compares the value at that index with its left and right children. If either child is less than the current value, it swaps the current value with the smaller child and continues this process until the min-heap property is restored or a leaf node is reached. This ensures that the smallest value is always at the root of the heap, allowing for efficient extraction of minimum values during processing.
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < h->size &&
                h->heap[left] < h->heap[smallest])
            {
                smallest = left;
            }

            if (right < h->size &&
                h->heap[right] < h->heap[smallest])
            {
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

int compareMeetings(const void *a, const void *b)
{ // function to compare two Meeting structures based on their start and end times. It takes two pointers (a and b) to Meeting structures as input. The function first casts the pointers to Meeting pointers (x and y) for easier access to their fields. It then compares the start times of the two meetings. If the start times are different, it returns the difference between the start times, ensuring that meetings with earlier start times come first in the sorted order. If the start times are equal, it compares the end times of the meetings and returns the difference between the end times, ensuring a consistent ordering of meetings with equal start times. This comparison function is used to sort the meetings in ascending order of their start times and end times, which is necessary for efficiently scheduling meetings in available rooms.
    Meeting *x = (Meeting *)a;
    Meeting *y = (Meeting *)b; // Compare the start times of the two meetings. If they are different, return the difference to sort by start time.

    if (x->start != y->start)
        return x->start - y->start;

    return x->end - y->end;
}

int main()
{
    int n;

    printf("Enter number of meetings: ");
    scanf("%d", &n);

    Meeting meetings[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter start and end time for meeting %d: ", i + 1);
        scanf("%d %d",
              &meetings[i].start,
              &meetings[i].end);
    }
    qsort(meetings, n,sizeof(Meeting),compareMeetings);

    MinHeap rooms;
    rooms.size = 0;
    int maximumRooms = 0;
    for (int i = 0; i < n; i++)
    { // Iterate through the sorted meetings array to determine the minimum number of meeting rooms required. The loop runs from 0 to n - 1, processing each meeting in chronological order. For each meeting, it checks if there are any meeting rooms that have become available (i.e., their end time is less than or equal to the start time of the current meeting). If so, it removes those rooms from the min-heap (rooms) using the pop function. It then adds the end time of the current meeting to the min-heap using the push function, indicating that a room is now occupied until that end time. After processing each meeting, it checks if the current size of the min-heap (the number of occupied rooms) exceeds the maximum recorded so far. If it does, it updates maximumRooms to reflect the new maximum. This process allows for determining the minimum number of meeting rooms needed to accommodate all meetings without overlap.
        while (rooms.size > 0 && rooms.heap[0] <= meetings[i].start)
        {
            pop(&rooms);
        }

        push(&rooms, meetings[i].end);
        if (rooms.size > maximumRooms)
            maximumRooms = rooms.size;
    }

    printf("Minimum number of meeting rooms = %d\n",
           maximumRooms);

    return 0;
}