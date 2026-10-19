#include <stdio.h>
#include <stdlib.h>

long long rodCutting(int price[], int n, int cut[])
{ // function to calculate the maximum revenue obtainable by cutting a rod of length n into pieces and selling them based on the given prices. It takes an integer array price[] representing the prices for each length, an integer n representing the length of the rod, and an integer array cut[] to store the optimal cuts for each length. The function uses dynamic programming to fill a dp[] array, where dp[length] represents the maximum revenue obtainable for a rod of that length. It initializes dp[0] to 0 (no revenue for a rod of length 0) and iterates through each possible rod length from 1 to n. For each length, it considers all possible first cuts (from 1 to length-1) and calculates the current revenue by adding the price of the first piece and the maximum revenue for the remaining length. If this current revenue is greater than the existing maximum revenue for that length, it updates dp[length] and records the cut position in cut[length]. Finally, it returns the maximum revenue obtainable for a rod of length n.
    long long *dp = malloc((n + 1) * sizeof(long long));

    if (dp == NULL)
        return -1;

    dp[0] = 0;

    cut[0] = 0; // Initialize the cut array for length 0 to indicate that no cuts are needed for a rod of length 0.

    for (int length = 1; length <= n; length++)
    { // Iterate through each possible rod length from 1 to n to calculate the maximum revenue obtainable for that length. For each length, it initializes dp[length] with the price of the entire rod (price[length - 1]) and sets cut[length] to the current length, indicating that no cuts are made initially. It then considers all possible first cuts (from 1 to length-1) and calculates the current revenue by adding the price of the first piece (price[firstPiece - 1]) and the maximum revenue for the remaining length (dp[length - firstPiece]). If this current revenue is greater than the existing maximum revenue for that length (dp[length]), it updates dp[length] with the new maximum revenue and records the cut position in cut[length]. This process continues until all lengths have been evaluated, resulting in dp[n] containing the maximum revenue obtainable for a rod of length n.
        dp[length] = price[length - 1];
        cut[length] = length;

        for (int firstPiece = 1;
             firstPiece < length;
             firstPiece++)
        {
            long long current = price[firstPiece - 1] + dp[length - firstPiece];

            if (current > dp[length])
            { // If the current revenue obtained by making a cut at firstPiece is greater than the existing maximum revenue for the current length, update dp[length] with the new maximum revenue and record the cut position in cut[length]. This ensures that the optimal cuts for each length are stored in the cut array, allowing for reconstruction of the optimal cutting strategy after calculating the maximum revenue.
                dp[length] = current;
                cut[length] = firstPiece;
            }
        }
    }

    long long answer = dp[n];

    free(dp);

    return answer;
}

int main()
{
    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    int *price = malloc(n * sizeof(int));
    int *cut = malloc((n + 1) * sizeof(int));

    if (price == NULL || cut == NULL)
        return 1;

    printf("Enter prices for lengths 1 to %d:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &price[i]);

    long long maximumRevenue = rodCutting(price, n, cut);

    printf("\nMaximum revenue = %lld\n",
           maximumRevenue);

    printf("Optimal pieces = ");

    int remaining = n;

    while (remaining > 0)
    {
        printf("%d ", cut[remaining]);

        remaining -= cut[remaining];
    }

    printf("\n");

    free(price);
    free(cut);

    return 0;
}