#include <stdio.h>
#include <stdlib.h>
// it is bi directional slope greedy approach because we are traversing the array from left to right and then from right to left. In the first pass, we ensure that each child has more candies than the previous child if their rating is higher. In the second pass, we ensure that each child has more candies than the next child if their rating is higher. This two-pass approach guarantees that all children receive the minimum number of candies while satisfying the rating conditions.
int main()
{
    int n;

    printf("Enter number of children: ");
    scanf("%d", &n);

    int *rating = malloc(n * sizeof(int));
    int *candy = malloc(n * sizeof(int));

    if (rating == NULL || candy == NULL)
        return 1;

    printf("Enter ratings:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &rating[i]);

    for (int i = 0; i < n; i++)
        candy[i] = 1; // Initialize each child with at least one candy.

    for (int i = 1; i < n; i++)
    {
        if (rating[i] > rating[i - 1])
        {
            candy[i] = candy[i - 1] + 1;
        }
    }

    for (int i = n - 2; i >= 0; i--)
    { // Iterate through the array in reverse order, starting from the second-to-last element (index n-2) down to the first element (index 0). For each rating[i], it compares it with the next rating[i + 1]. If rating[i] is greater than rating[i + 1], it means that the child at index i should receive more candies than the child at index i + 1. The function then checks if candy[i] is less than candy[i + 1] + 1. If it is, it updates candy[i] to be candy[i + 1] + 1, ensuring that the child at index i receives more candies than the child at index i + 1. This process continues until all elements have been processed, resulting in the candy[] array containing the correct number of candies for each child based on their ratings.
        if (rating[i] > rating[i + 1])
        {
            if (candy[i] < candy[i + 1] + 1)
                candy[i] = candy[i + 1] + 1;
        }
    }

    long long total = 0;

    printf("\nCandies:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", candy[i]);
        total += candy[i];
    }

    printf("\n\nMinimum total candies = %lld\n",
           total);

    free(rating);
    free(candy);

    return 0;
}