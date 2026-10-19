#include <stdio.h>
#include <string.h>

#define MAX 1000
#define CHARSET 256

typedef struct
{
    unsigned char ch;
    int count;
} HeapNode;

typedef struct
{
    unsigned char ch;
    int count;
    int readyPosition;
} CooldownNode;

HeapNode heap[CHARSET];
int heapSize = 0;

void swap(HeapNode *a, HeapNode *b)
{
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void push(HeapNode node)
{ // function to insert a new node into the max-heap. It takes a HeapNode structure (node) as input. The function first adds the new node to the end of the heap's array and increments the size of the heap. It then performs a "bubble-up" operation to maintain the max-heap property. Starting from the newly added index, it compares the node at that index with its parent node. If the newly added node has a larger count (or character in case of equal counts) than its parent, it swaps them and continues this process until the max-heap property is restored or the root of the heap is reached. This ensures that the largest count node is always at the root of the heap, allowing for efficient extraction of nodes during processing.
    int i = heapSize++;

    heap[i] = node;

    while (i > 0)
    { // Bubble-up operation to maintain the max-heap property. It starts from the newly added index (i) and compares the node at that index with its parent node. If the node at index i has a larger count (or character in case of equal counts) than its parent, it swaps them and continues this process until the max-heap property is restored or the root of the heap is reached. This ensures that the largest count node is always at the root of the heap, allowing for efficient extraction of nodes during processing.
        int parent = (i - 1) / 2;

        if (heap[parent].count > heap[i].count)
            break;

        if (heap[parent].count == heap[i].count &&
            heap[parent].ch < heap[i].ch)
            break;

        swap(&heap[parent], &heap[i]);

        i = parent;
    }
}

HeapNode pop()
{ // function to remove and return the node with the largest count from the max-heap. It takes no input and returns a HeapNode structure. The function first stores the node at the root of the heap (the node with the largest count) in a variable (result) and decrements the size of the heap. If there are still elements in the heap after removing the root, it replaces the root with the last element in the heap and performs a "bubble-down" operation to maintain the max-heap property. Starting from the root, it compares the current node with its left and right children, swapping it with the larger child if necessary. This process continues until the max-heap property is restored or a leaf node is reached. Finally, the function returns the node that was removed from the heap, allowing for efficient extraction of nodes during processing.
    HeapNode result = heap[0];

    heapSize--;

    if (heapSize > 0)
    {
        heap[0] = heap[heapSize];

        int i = 0;

        while (1)
        { // Bubble-down operation to maintain the max-heap property. It starts from the root (index 0) and compares the node at that index with its left and right children. If either child has a larger count (or character in case of equal counts) than the current node, it swaps the current node with the larger child and continues this process until the max-heap property is restored or a leaf node is reached. This ensures that the node with the largest count is always at the root of the heap, allowing for efficient extraction of nodes during processing.
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;

            if (left < heapSize)
            {
                if (heap[left].count > heap[largest].count || (heap[left].count == heap[largest].count && heap[left].ch > heap[largest].ch)) // Compare the left child with the current largest value. If the left child has a larger count (or character in case of equal counts) than the current largest value, update the largest index to be the left child's index. This ensures that we are always comparing the current node with both of its children to maintain the max-heap property, where the parent node is greater than or equal to its children.
                {
                    largest = left;
                }
            }

            if (right < heapSize)
            {
                if (heap[right].count > heap[largest].count ||
                    (heap[right].count == heap[largest].count &&
                     heap[right].ch > heap[largest].ch))
                {
                    largest = right;
                }
            }

            if (largest == i)
                break;

            swap(&heap[i], &heap[largest]);

            i = largest;
        }
    }

    return result;
}

int main()
{
    char S[MAX];
    int K;

    printf("Enter string: ");
    scanf("%999s", S);

    printf("Enter K: ");
    scanf("%d", &K);

    if (K <= 1)
    {
        printf("Reorganised string = %s\n", S);
        return 0;
    }

    int frequency[CHARSET] = {0};

    int length = strlen(S);

    for (int i = 0; i < length; i++)
        frequency[(unsigned char)S[i]]++;

    heapSize = 0;

    for (int i = 0; i < CHARSET; i++)
    {
        if (frequency[i] > 0)
        {
            HeapNode node;

            node.ch = i;
            node.count = frequency[i];

            push(node);
        }
    }

    CooldownNode queue[MAX];
    int front = 0;
    int rear = 0;

    char result[MAX];
    int resultIndex = 0;

    for (int position = 0;
         position < length;
         position++)
    {
        while (front < rear &&
               queue[front].readyPosition <= position)
        {
            HeapNode node;

            node.ch = queue[front].ch; // Create a new HeapNode structure to hold the character and its count from the cooldown queue. The node's character (ch) is set to the character stored in the front of the queue, and its count is set to the count of that character. This allows the program to reinsert characters back into the max-heap after their cooldown period has expired, ensuring that they can be used again in the reorganized string while maintaining the K-distance constraint.
            node.count = queue[front].count;

            push(node);

            front++;
        }

        if (heapSize == 0)
        {
            printf("Reorganised string = \n");
            return 0;
        }

        HeapNode current = pop();

        result[resultIndex++] = current.ch;
        current.count--;

        if (current.count > 0)
        {
            queue[rear].ch = current.ch;
            queue[rear].count = current.count;
            queue[rear].readyPosition = position + K;

            rear++;
        }
    }

    result[resultIndex] = '\0';

    printf("Reorganised string = %s\n",
           result);

    return 0;
}