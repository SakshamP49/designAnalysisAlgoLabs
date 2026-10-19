#include <stdio.h>
#include <stdlib.h>

int LIS(int arr[], int n)
{ // function to calculate the length of the longest increasing subsequence (LIS) in an array. It takes an integer array arr[] and its size n as input. The function uses dynamic programming to fill a dp[] array, where dp[i] represents the length of the longest increasing subsequence that ends with the element arr[i]. It initializes all entries of dp[] to 1, as each element is an increasing subsequence of length 1 by itself. The function then iterates through the array, comparing each element with all previous elements to find increasing subsequences. If arr[j] is less than arr[i], it updates dp[i] to be the maximum of its current value and dp[j] + 1. Finally, it returns the maximum value in the dp[] array, which represents the length of the longest increasing subsequence in arr[].
    int *dp = malloc(n * sizeof(int));

    if (dp == NULL)
        return -1;

    int maximum = 1;

    for (int i = 0; i < n; i++)
        dp[i] = 1; // Initialize all entries of dp[] to 1, as each element is an increasing subsequence of length 1 by itself.

    for (int i = 1; i < n; i++)
    { // Iterate through the array starting from the second element (index 1) to find the length of the longest increasing subsequence that ends with each element arr[i]. For each arr[i], it compares it with all previous elements arr[j] (where j < i) to check if arr[j] is less than arr[i]. If it is, it means that arr[i] can extend the increasing subsequence that ends with arr[j]. The function then updates dp[i] to be the maximum of its current value and dp[j] + 1, which represents the length of the increasing subsequence ending at arr[i]. After checking all previous elements, it updates the maximum variable if dp[i] is greater than the current maximum. This process continues until all elements have been processed, resulting in dp[] containing the lengths of the longest increasing subsequences ending at each index.
        for (int j = 0; j < i; j++)
        { // Compare arr[i] with all previous elements arr[j] (where j < i) to check if arr[j] is less than arr[i]. If it is, it means that arr[i] can extend the increasing subsequence that ends with arr[j]. The function then updates dp[i] to be the maximum of its current value and dp[j] + 1, which represents the length of the increasing subsequence ending at arr[i].
            if (arr[j] < arr[i])
            {
                if (dp[j] + 1 > dp[i])
                    dp[i] = dp[j] + 1;
            }
        }

        if (dp[i] > maximum)
            maximum = dp[i];
    }

    free(dp);

    return maximum;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int answer = LIS(arr, n);

    printf("Length of LIS = %d\n", answer);

    free(arr);

    return 0;
}