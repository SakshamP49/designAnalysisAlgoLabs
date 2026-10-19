#include <stdio.h>
#include <limits.h>

long long dp[100];
int split[100];

void hanoi3(int n, char source, char destination, char auxiliary)
{ // function to solve the Tower of Hanoi problem with 3 pegs. It takes the number of disks n, the source peg, the destination peg, and the auxiliary peg as parameters. The function uses recursion to move n disks from the source peg to the destination peg using the auxiliary peg. The base case is when n is 0, in which case the function returns without making any moves. For n greater than 0, it first moves n-1 disks from the source peg to the auxiliary peg, then moves the nth disk from the source peg to the destination peg, and finally moves the n-1 disks from the auxiliary peg to the destination peg.
    if (n == 0)
        return;

    hanoi3(n - 1, source, auxiliary, destination); // Move n-1 disks from source to auxiliary peg

    printf("Move disk %d from %c to %c\n",
           n, source, destination);

    hanoi3(n - 1, auxiliary, destination, source);
}

void computeDP(int n)
{ // function to compute the minimum number of moves required to solve the Reve's puzzle for n disks. It uses dynamic programming to fill the dp[] array, where dp[i] represents the minimum number of moves required for i disks. The split[] array is used to store the optimal split point for each number of disks. The function initializes the base cases for 0 and 1 disks, and then iteratively calculates the minimum moves for each number of disks from 2 to n by considering all possible split points k. For each split point, it calculates the total moves required using the formula: 2 * dp[k] + (2^(i - k) - 1), which accounts for moving k smaller disks to an auxiliary peg, moving the remaining disks using 3 pegs, and then moving the k disks from the auxiliary peg to the destination peg.
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = LLONG_MAX;

        for (int k = 1; k < i; k++)
        {
            long long moves =
                2 * dp[k] +
                ((1LL << (i - k)) - 1);

            if (moves < dp[i])
            {
                dp[i] = moves;
                split[i] = k;
            }
        }
    }
}

void reve(int n, char source, char destination,
          char aux1, char aux2)
{ // function to solve the Reve's puzzle for n disks using 4 pegs. It takes the number of disks n, the source peg, the destination peg, and two auxiliary pegs as parameters. The function first checks if n is 0, in which case it returns without making any moves. If n is 1, it simply moves the disk from the source peg to the destination peg. For n greater than 1, it retrieves the optimal split point k from the split[] array. It then recursively moves k smaller disks to one of the auxiliary pegs, moves the remaining disks using the standard 3-peg Tower of Hanoi solution (hanoi3), and finally moves the k disks from the auxiliary peg to the destination peg.
    if (n == 0)
        return;

    if (n == 1)
    {
        printf("Move disk 1 from %c to %c\n",
               source, destination);
        return;
    }

    int k = split[n];

    // Move k smaller disks to auxiliary peg
    reve(k, source, aux1, destination, aux2);

    // Move remaining disks using 3 pegs
    hanoi3(n - k, source, destination, aux2);

    // Move k disks from auxiliary peg to destination
    reve(k, aux1, destination, source, aux2);
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    computeDP(n);

    printf("\nMinimum number of moves = %lld\n\n",
           dp[n]);

    printf("Sequence of moves:\n");

    reve(n, 'A', 'D', 'B', 'C'); // Call the reve() function to solve the Reve's puzzle for n disks, moving them from peg 'A' (source) to peg 'D' (destination) using pegs 'B' and 'C' as auxiliary pegs. The function will print the sequence of moves required to achieve this.

    return 0;
}