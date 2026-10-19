#include <stdio.h>
#include <stdlib.h>

int minCoins(int coins[], int n, int V)
{ // function to calculate the minimum number of coins needed to make a target amount V using given coin denominations. It takes an array coins[] representing the coin denominations, an integer n representing the number of denominations, and an integer V representing the target amount. The function uses dynamic programming to fill a dp[] array, where dp[i] represents the minimum number of coins needed to make amount i. It initializes dp[0] to 0 (no coins needed for amount 0) and sets all other entries to V + 1 (an impossible value). It then iterates through each amount from 1 to V and checks each coin denomination. If the coin can be used (i.e., it is less than or equal to the current amount), it updates dp[amount] with the minimum value between its current value and the value obtained by using that coin (dp[amount - coins[i]] + 1). Finally, it returns the minimum number of coins needed for amount V, or -1 if it is not possible to make that amount with the given denominations.
    int *dp = malloc((V + 1) * sizeof(int));

    if (dp == NULL)
        return -1;

    dp[0] = 0;

    for (int i = 1; i <= V; i++)
        dp[i] = V + 1; // Initialize all other entries to V + 1, which is an impossible value representing that the amount cannot be made with the given denominations. This serves as a placeholder for amounts that have not yet been computed, allowing the algorithm to find the minimum number of coins needed for each amount iteratively.

    for (int amount = 1; amount <= V; amount++)
    { // Iterate through each amount from 1 to V to compute the minimum number of coins needed for that amount. For each amount, the algorithm checks all available coin denominations to see if they can be used to make up that amount. If a coin denomination is less than or equal to the current amount, it calculates the number of coins needed by using that coin and updates the dp[amount] entry with the minimum value found so far. This process continues until all amounts up to V have been evaluated, resulting in dp[V] containing the minimum number of coins needed for the target amount V.
        for (int i = 0; i < n; i++)
        {
            if (coins[i] <= amount &&
                dp[amount - coins[i]] != V + 1)
            {
                int current = dp[amount - coins[i]] + 1;
                if (current < dp[amount]) 
                dp[amount] = current;
            }
        }
    }

    int answer;

    if (dp[V] == V + 1)
        answer = -1; // If dp[V] is still equal to V + 1, it means that it is not possible to make the target amount V with the given coin denominations. In this case, the function sets the answer to -1 to indicate that no solution exists.
    else
        answer = dp[V];

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

    int answer = minCoins(coins, n, V);

    printf("Minimum number of coins = %d\n", answer);

    free(coins);

    return 0;
}