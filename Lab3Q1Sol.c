#include <stdio.h>
#include <time.h>

int binarySearch(int arr[], int n, int x)
{
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
            return mid;

        if (x < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;
}

int ternarySearch(int arr[], int n, int x)
{
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int third = (high - low) / 3;

        int mid1 = low + third;
        int mid2 = high - third;

        if (arr[mid1] == x)
            return mid1;

        if (arr[mid2] == x)
            return mid2;

        if (x < arr[mid1])
            high = mid1 - 1;

        else if (x > arr[mid2])
            low = mid2 + 1;

        else
        {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }

    return -1;
}

int main()
{
    int n, x;

    printf("Enter size: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter sorted array:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter element to search: ");
    scanf("%d", &x);

    int b = binarySearch(arr, n, x);
    int t = ternarySearch(arr, n, x);

    printf("\nBinary Search result: %d\n", b);
    printf("Ternary Search result: %d\n", t);

    printf("\nTime Complexity:\n");
    printf("Binary Search : O(log2 n)\n");
    printf("Ternary Search: O(log3 n)\n");

    printf("\nBinary search is generally better because\n");
    printf("each step requires fewer comparisons.\n");

    return 0;
}