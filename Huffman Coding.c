#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 256 // Maximum number of unique symbols (ASCII characters)
#define MAX_NODES 512 // Maximum number of nodes in the Huffman tree (2 * MAX_SYMBOLS - 1)
#define MAX_CODE_LEN 512 // Maximum code length for a symbol

typedef struct
{ // structure to represent a node in the Huffman tree. Each node contains a symbol (character), its frequency (long long), and indices of its left and right children in the nodes array. The left and right indices are initialized to -1 for leaf nodes, indicating that they do not have children. This structure is used to build the Huffman tree based on the frequencies of symbols, allowing for efficient encoding of data.
    char symbol;
    long long freq;
    int left;
    int right;
} Node;

typedef struct
{ // structure to represent a min-heap data structure. It contains an array of integers (data) that stores the indices of nodes in the nodes array, and an integer (size) that keeps track of the current number of elements in the heap. The min-heap is used to efficiently extract the two nodes with the smallest frequencies during the construction of the Huffman tree, ensuring that the tree is built optimally for encoding symbols based on their frequencies.
    int data[MAX_NODES];
    int size;
} MinHeap;

typedef struct
{ // structure to store information about each symbol, including its character (symbol), frequency (freq), length of its Huffman code (length), and the actual Huffman code (code). The code is stored as a string of '0's and '1's, with a maximum length defined by MAX_CODE_LEN. This structure is used to keep track of the encoding information for each symbol after the Huffman tree has been constructed, allowing for efficient encoding and decoding of data.
    char symbol;
    long long freq;
    int length;
    char code[MAX_CODE_LEN];
} SymbolInfo;
Node nodes[MAX_NODES];
int nodeCount = 0;
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int compareNodes(int a, int b)
{ // function to compare two nodes in the Huffman tree based on their frequencies and symbols. It takes two indices (a and b) of nodes in the nodes array as input. The function first compares the frequencies of the two nodes. If the frequencies are different, it returns 1 if the frequency of node a is less than that of node b, indicating that node a should come before node b in the min-heap. If the frequencies are equal, it compares the symbols of the two nodes and returns 1 if the symbol of node a is less than that of node b, ensuring a consistent ordering of nodes with equal frequencies. This comparison function is used to maintain the min-heap property during the construction of the Huffman tree.
    if (nodes[a].freq != nodes[b].freq)
        return nodes[a].freq < nodes[b].freq;
    return nodes[a].symbol < nodes[b].symbol;
}
void push(MinHeap *heap, int index)
{ // function to insert a new node index into the min-heap. It takes a pointer to the MinHeap structure (heap) and the index of the node to be inserted (index) as input. The function first adds the new index to the end of the heap's data array and increments the size of the heap. It then performs a "bubble-up" operation to maintain the min-heap property. Starting from the newly added index, it compares the node at that index with its parent node. If the newly added node has a smaller frequency (or symbol in case of equal frequencies) than its parent, it swaps them and continues this process until the min-heap property is restored or the root of the heap is reached. This ensures that the smallest frequency node is always at the root of the heap, allowing for efficient extraction of nodes during Huffman tree construction.
    int i = heap->size++;

    heap->data[i] = index;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (compareNodes(heap->data[parent], heap->data[i])) // If the parent node has a smaller frequency (or symbol) than the current node, the min-heap property is satisfied, and we can break out of the loop. This means that the newly added node is in the correct position in the heap, and no further swaps are needed to maintain the min-heap structure.
            break;

        swap(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

int pop(MinHeap *heap)
{ // function to remove and return the index of the node with the smallest frequency from the min-heap. It takes a pointer to the MinHeap structure (heap) as input. The function first stores the index of the root node (the smallest frequency node) in a variable (result) and decrements the size of the heap. If there are still elements in the heap after removing the root, it replaces the root with the last element in the heap and performs a "bubble-down" operation to maintain the min-heap property. Starting from the root, it compares the current node with its left and right children, swapping it with the smaller child if necessary. This process continues until the min-heap property is restored or a leaf node is reached. Finally, the function returns the index of the removed node, allowing for efficient extraction of nodes during Huffman tree construction.
    int result = heap->data[0];

    heap->size--;

    if (heap->size > 0)
    {
        heap->data[0] = heap->data[heap->size];
        int i = 0;
        while (1)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;
            if (left < heap->size &&
                compareNodes(heap->data[left], heap->data[smallest]))
            {
                smallest = left;
            }
            if (right < heap->size &&
                compareNodes(heap->data[right], heap->data[smallest]))
            {
                smallest = right;
            }

            if (smallest == i)
                break;

            swap(&heap->data[i], &heap->data[smallest]); // Swap the current node with the smallest child to maintain the min-heap property. This ensures that the node with the smallest frequency (or symbol in case of equal frequencies) is always at the root of the heap, allowing for efficient extraction of nodes during Huffman tree construction.

            i = smallest;
        }
    }

    return result;
}
void findLengths(int root, int depth, SymbolInfo info[])
{
    if (root == -1)
        return;

    if (nodes[root].left == -1 && nodes[root].right == -1)
    { // If the current node is a leaf node (both left and right children are -1), it means that we have reached a symbol in the Huffman tree. The function then calculates the index of the symbol in the info array using its ASCII value (unsigned char) and stores the symbol, its frequency, and the length of its Huffman code (depth) in the corresponding entry of the info array. If the depth is 0 (indicating that this is the only symbol in the tree), it sets the length to 1 to ensure that there is at least one bit in the code. This process allows us to traverse the Huffman tree and record the lengths of the codes for each symbol, which will be used later to generate the canonical Huffman codes.
        int index = (unsigned char)nodes[root].symbol;
        info[index].symbol = nodes[root].symbol;
        info[index].freq = nodes[root].freq;
        info[index].length = (depth == 0) ? 1 : depth;

        return;
    }

    findLengths(nodes[root].left, depth + 1, info);
    findLengths(nodes[root].right, depth + 1, info);
}

int compareSymbols(const void *a, const void *b)
{ // function to compare two SymbolInfo structures based on their lengths and symbols. It takes two pointers (a and b) to SymbolInfo structures as input. The function first casts the pointers to const SymbolInfo pointers (x and y) for easier access to their fields. It then compares the lengths of the two symbols. If the lengths are different, it returns the difference between the lengths, ensuring that symbols with shorter codes come first in the sorted order. If the lengths are equal, it compares the symbols themselves (as unsigned characters) and returns the difference between their ASCII values, ensuring a consistent ordering of symbols with equal code lengths. This comparison function is used to sort the symbols in ascending order of their code lengths and symbols, which is necessary for generating canonical Huffman codes.
    const SymbolInfo *x = a;
    const SymbolInfo *y = b;

    if (x->length != y->length)
        return x->length - y->length;

    return (unsigned char)x->symbol - (unsigned char)y->symbol; // Compare the symbols as unsigned characters to ensure correct ordering based on their ASCII values. This is important for maintaining a consistent order of symbols with equal code lengths when generating canonical Huffman codes.
}

void setZeros(char code[], int length)
{ // function to initialize a binary code string with '0's. It takes a character array (code) and an integer (length) as input. The function iterates through the first length characters of the code array and sets each character to '0', effectively creating a binary string of the specified length filled with '0's. After filling the specified length, it appends a null terminator ('\0') at the end of the code array to mark the end of the string. This function is used to create an initial binary code representation for symbols when generating canonical Huffman codes, ensuring that all codes start with a consistent format before being incremented to generate unique codes for each symbol.
    for (int i = 0; i < length; i++)
        code[i] = '0';

    code[length] = '\0';
}

void incrementBinary(char code[], int length)
{ // function to increment a binary code string by 1. It takes a character array (code) representing a binary number and an integer (length) indicating the length of the binary code as input. The function starts from the least significant bit (the rightmost character) and iterates backwards through the code array. If it encounters a '1', it changes it to '0' and continues to the next bit to the left, effectively carrying over the increment. If it encounters a '0', it changes it to '1' and stops, as the increment is complete. This process simulates binary addition, allowing for the generation of unique binary codes for symbols when creating canonical Huffman codes.
    int i = length - 1;

    while (i >= 0 && code[i] == '1')
    {
        code[i] = '0';
        i--;
    }

    if (i >= 0)
        code[i] = '1';
}

int main()
{
    int n;

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    MinHeap heap;
    heap.size = 0;

    SymbolInfo info[MAX_SYMBOLS];

    for (int i = 0; i < MAX_SYMBOLS; i++)
    {
        info[i].symbol = 0;
        info[i].freq = 0;
        info[i].length = 0;
        info[i].code[0] = '\0';
    }

    for (int i = 0; i < n; i++)
    {
        char symbol;
        long long freq;

        printf("Enter symbol and frequency: ");
        scanf(" %c %lld", &symbol, &freq);

        nodes[nodeCount].symbol = symbol;
        nodes[nodeCount].freq = freq;
        nodes[nodeCount].left = -1;
        nodes[nodeCount].right = -1;

        push(&heap, nodeCount);

        nodeCount++;
    }

    if (n == 0)
        return 0;

    while (heap.size > 1)
    {
        int a = pop(&heap);
        int b = pop(&heap);

        nodes[nodeCount].symbol = (nodes[a].symbol < nodes[b].symbol) ? nodes[a].symbol : nodes[b].symbol;

        nodes[nodeCount].freq = nodes[a].freq + nodes[b].freq;

        nodes[nodeCount].left = a;
        nodes[nodeCount].right = b;

        push(&heap, nodeCount);
        nodeCount++;
    }

    int root = pop(&heap);
    findLengths(root, 0, info);
    SymbolInfo list[MAX_SYMBOLS];
    int count = 0;
    for (int i = 0; i < MAX_SYMBOLS; i++)
    {
        if (info[i].length > 0)
        {
            list[count++] = info[i];
        }
    }
    qsort(list, count, sizeof(SymbolInfo), compareSymbols);// Sort the symbols based on their lengths and symbols to prepare for generating canonical Huffman codes. The qsort function is used to sort the list of SymbolInfo structures in ascending order of their code lengths and symbols, ensuring that symbols with shorter codes come first and that symbols with equal code lengths are ordered consistently based on their ASCII values. This sorted order is essential for generating canonical Huffman codes, as it allows for a systematic assignment of binary codes to symbols while maintaining the prefix property of the codes.

    char currentCode[MAX_CODE_LEN];
    currentCode[0] = '\0';

    int previousLength = 0;

    for (int i = 0; i < count; i++)
    {
        int len = list[i].length;

        if (i == 0)
        {
            setZeros(currentCode, len);
        }
        else
        {
            incrementBinary(currentCode, previousLength);
            int currentLength = strlen(currentCode);
            while (currentLength < len)
            {
                currentCode[currentLength] = '0';
                currentLength++;
                currentCode[currentLength] = '\0';
            }
        }

        strcpy(list[i].code, currentCode);
        previousLength = len;
    }

    printf("\nCanonical Huffman Codebook:\n");

    for (int i = 0; i < count; i++)
    {
        printf("%c  Frequency=%lld  Code=%s\n",
               list[i].symbol,
               list[i].freq,
               list[i].code);
    }

    return 0;
}