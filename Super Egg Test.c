#include <stdio.h>
#include <limits.h>
// aim of code is to find the minimum number of attempts needed in the worst case to find the critical floor from which eggs start breaking when dropped. The problem is solved using dynamic programming.
int max(int a, int b)
{ // utility function to return the maximum of two integers. It takes two integer parameters a and b, and returns the larger of the two values. This function is used in the eggDrop() function to determine the maximum number of trials needed in the worst case when dropping eggs from different floors. The max() function is a simple comparison that helps in calculating the minimum number of attempts required to find the critical floor by considering both scenarios: when an egg breaks and when it doesn't break.
    return (a > b) ? a : b;
}

int eggDrop(int eggs, int floors)
{ // function to calculate the minimum number of attempts needed in the worst case to find the critical floor from which eggs start breaking when dropped. It takes two integer parameters: eggs (the number of eggs available) and floors (the number of floors in the building). The function uses dynamic programming to build a table (dp) that stores the minimum number of trials needed for different combinations of eggs and floors. The base cases are initialized, and then the table is filled iteratively by considering all possible floors to drop an egg from. The final result is returned as dp[eggs][floors], which represents the minimum number of attempts needed for the given number of eggs and floors.
    int dp[eggs + 1][floors + 1];

    // 0 floors require 0 trials
    for (int e = 1; e <= eggs; e++)
        dp[e][0] = 0;

    // 1 floor requires 1 trial
    for (int e = 1; e <= eggs; e++)
        dp[e][1] = 1;

    // With one egg, we have to try every floor
    for (int f = 0; f <= floors; f++)
        dp[1][f] = f;

    // Fill DP table
    for (int e = 2; e <= eggs; e++)
    {
        for (int f = 2; f <= floors; f++)
        {
            dp[e][f] = INT_MAX; // Initialize to maximum value to find the minimum later

            for (int x = 1; x <= f; x++)
            { // Try dropping an egg from each floor x and calculate the number of trials needed in the worst case. The variable 'trials' stores the maximum number of trials needed between the two scenarios: when the egg breaks (dp[e - 1][x - 1]) and when it doesn't break (dp[e][f - x]). The maximum of these two values is taken to ensure we account for the worst-case scenario. The minimum number of trials across all floors is then stored in dp[e][f]. This process continues until the entire DP table is filled, allowing us to find the minimum number of attempts needed for any given number of eggs and floors.
                int trials;

                trials = 1 + max(
                    dp[e - 1][x - 1],
                    dp[e][f - x]
                );

                if (trials < dp[e][f])
                    dp[e][f] = trials;
            }
        }
    }

    return dp[eggs][floors];
}

int main()
{
    int eggs, floors;

    printf("Enter number of eggs: ");
    scanf("%d", &eggs);

    printf("Enter number of floors: ");
    scanf("%d", &floors);

    printf("Minimum number of drops = %d\n",
           eggDrop(eggs, floors));

    return 0;
}