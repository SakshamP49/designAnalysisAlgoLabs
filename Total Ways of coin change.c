#include <stdio.h>
#include <stdlib.h>

long long countWays(int coins[], int n, int V)
{ // function to calculate the total number of ways to make a target amount V using given coin denominations. It takes an array coins[] representing the coin denominations, an integer n representing the number of denominations, and an integer V representing the target amount. The function uses dynamic programming to fill a dp[] array, where dp[i] represents the total number of ways to make amount i. It initializes dp[0] to 1 (one way to make amount 0) and sets all other entries to 0. It then iterates through each coin denomination and updates the dp[] array for each amount from the coin value up to V. For each amount, it adds the number of ways to make that amount by including the current coin (dp[amount - coins[i]]) to the existing number of ways (dp[amount]). Finally, it returns the total number of ways to make amount V.
    long long *dp = malloc((V + 1) * sizeof(long long)); // Allocate memory for the dp array, which will store the total number of ways to make each amount from 0 to V. The size of the array is V + 1 to accommodate all amounts, including 0. Each index in the array corresponds to a specific amount, and the value at that index represents the total number of ways to make that amount using the given coin denominations. Initially, all values are set to 0 except for dp[0], which is set to 1 (one way to make amount 0).

    if (dp == NULL)
        return -1;

    for (int i = 0; i <= V; i++)
        dp[i] = 0;

    dp[0] = 1;

    for (int i = 0; i < n; i++)
    { // Iterate through each coin denomination to update the dp array for all amounts from the coin value up to V. For each coin, the algorithm checks all amounts starting from the coin's value (coins[i]) up to the target amount V. For each amount, it adds the number of ways to make that amount by including the current coin (dp[amount - coins[i]]) to the existing number of ways (dp[amount]). This process ensures that all combinations of coins are considered, allowing the algorithm to calculate the total number of ways to make each amount using the available denominations.
        for (int amount = coins[i]; amount <= V; amount++)
        {
            dp[amount] = dp[amount] + dp[amount - coins[i]];
        }
    }

    long long answer = dp[V];

    free(dp);

    return answer;
}

int main()
{
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int *coins = malloc(n * sizeof(int));

    printf("Enter coin denominations:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter target amount: ");
    scanf("%d", &V);

    long long answer = countWays(coins, n, V);

    printf("Total number of ways = %lld\n", answer);

    free(coins);

    return 0;
}