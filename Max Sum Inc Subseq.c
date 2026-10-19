#include <stdio.h>
#include <stdlib.h>
int maxSumIncreasingSubsequence(int arr[], int n)
{ // function to calculate the maximum sum of an increasing subsequence in an array. It takes an integer array arr[] and its size n as input. The function uses dynamic programming to fill a dp[] array, where dp[i] represents the maximum sum of an increasing subsequence that ends with the element arr[i]. It initializes dp[i] with the value of arr[i], as each element can be considered as an increasing subsequence of length 1 by itself. The function then iterates through the array, comparing each element with all previous elements to find increasing subsequences. If arr[j] is less than arr[i], it calculates the current sum by adding arr[i] to dp[j]. If this current sum is greater than dp[i], it updates dp[i] with the current sum. Finally, it returns the maximum value in the dp[] array, which represents the maximum sum of an increasing subsequence in arr[].
    int *dp = malloc(n * sizeof(int));
    if (dp == NULL)
        return -1;
    int maximum = 0;
    for (int i = 0; i < n; i++)
     dp[i] = arr[i];
    for (int i = 1; i < n; i++)
    { // Iterate through the array starting from the second element (index 1) to find the maximum sum of an increasing subsequence that ends with each element arr[i]. For each arr[i], it compares it with all previous elements arr[j] (where j < i) to check if arr[j] is less than arr[i]. If it is, it means that arr[i] can extend the increasing subsequence that ends with arr[j]. The function then calculates the current sum by adding arr[i] to dp[j], which represents the maximum sum of the increasing subsequence ending at arr[j]. If this current sum is greater than dp[i], it updates dp[i] with the current sum. After checking all previous elements, it updates the maximum variable if dp[i] is greater than the current maximum. This process continues until all elements have been processed, resulting in dp[] containing the maximum sums of increasing subsequences ending at each index.
        for (int j = 0; j < i; j++)
        {
            if (arr[j] < arr[i])
            {
                int current = dp[j] + arr[i];

                if (current > dp[i])
                    dp[i] = current;
            }
        }

        if (dp[i] > maximum)
            maximum = dp[i];
    }

    if (n > 0 && dp[0] > maximum)
        maximum = dp[0]; // Check if the first element of the array is greater than the current maximum. If it is, update the maximum variable with the value of dp[0]. This ensures that the maximum sum of an increasing subsequence is correctly calculated, even if the first element is larger than any other increasing subsequence found in the array. This check is necessary because the initial value of maximum is set to 0, and if all elements in the array are negative or if the first element is the largest, it may not be captured in the previous iterations.

    free(dp);
    return maximum;
}

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *arr = malloc(n * sizeof(int));
    printf("Enter positive integers:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    int answer = maxSumIncreasingSubsequence(arr, n);
    printf("Maximum sum = %d\n", answer);
    free(arr);
    return 0;
}