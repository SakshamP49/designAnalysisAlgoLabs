#include <stdio.h>

int minimumMoves(int n)
{ // logic to calculate the minimum number of moves required to invert a coin triangle with n rows. The total number of coins in a triangle with n rows is given by the formula n(n + 1)/2. To invert the triangle, we need to move one-third of the total coins, which is calculated as totalCoins / 3. The function returns the minimum number of moves required to invert the triangle.
    int totalCoins;
    int moves;

    // Total number of coins in n rows
    totalCoins = n * (n + 1) / 2; // The formula for the sum of the first n natural numbers is n(n + 1)/2.
    // Minimum number of coins to move
    moves = totalCoins / 3;

    return moves;
}

int main()
{
    int n;

    printf("Enter number of rows: ");
    scanf("%d", &n);

    int totalCoins = n * (n + 1) / 2; // The formula for the sum of the first n natural numbers is n(n + 1)/2.

    printf("Total coins = %d\n", totalCoins);

    printf("Minimum moves = %d\n", minimumMoves(n));

    return 0;
}