#include <stdio.h>
#include <limits.h>

int dp[100][100];
int split[100][100];

void printOptimalOrder(int i, int j)
{ if (i == j)
    {
        printf("A%d", i);
        return;
    }
    printf("(");
    printOptimalOrder(i, split[i][j]); // Recursively print the optimal order for the left subchain of matrices from index i to split[i][j]. The split[i][j] value indicates the optimal split point for multiplying the matrices in the range [i, j]. This recursive call continues until it reaches a base case where i equals j, at which point it prints the matrix identifier (A followed by the index).
    printf(" x ");
    printOptimalOrder(split[i][j] + 1, j);
    printf(")");
}

int matrixChain(int p[], int n)
{ // function to calculate the minimum number of scalar multiplications needed to multiply a chain of matrices. It takes an array p[] representing the dimensions of the matrices and an integer n representing the number of matrices. The function uses dynamic programming to fill the dp[][] table, where dp[i][j] represents the minimum cost of multiplying matrices from index i to j. The split[][] table is used to store the optimal split points for reconstructing the optimal order of multiplication. The function initializes the diagonal of the dp table to 0 (cost of multiplying a single matrix) and iteratively calculates the minimum cost for increasing lengths of matrix chains. Finally, it returns the minimum cost for multiplying all matrices from index 1 to n.
    /*
       n = number of matrices
       p has n+1 dimensions
    */

    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;
    // length = number of matrices in the chain
    for (int length = 2; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {  int j = i + length - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            { // Try all possible split points k between i and j to find the minimum cost of multiplying matrices from index i to j. The variable 'cost' calculates the total number of scalar multiplications needed for the current split point k, which includes the cost of multiplying the left subchain (dp[i][k]), the right subchain (dp[k + 1][j]), and the cost of multiplying the resulting matrices together (p[i - 1] * p[k] * p[j]). If this calculated cost is less than the current minimum cost stored in dp[i][j], it updates dp[i][j] with the new minimum cost and records the split point k in split[i][j]. This process continues until all possible split points have been evaluated for the current subchain, ensuring that dp[i][j] contains the minimum cost for multiplying matrices from index i to j.
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }
    return dp[1][n];
}

int main()
{
    int n;
    printf("Enter number of matrices: ");
    scanf("%d", &n);
    int p[n + 1];
    printf("Enter %d dimensions:\n", n + 1);
    for (int i = 0; i <= n; i++)
        scanf("%d", &p[i]);
    int minimumCost = matrixChain(p, n);
    printf("\nMinimum scalar multiplications = %d\n", minimumCost);
    printf("Optimal parenthesization = ");
    printOptimalOrder(1, n);
    printf("\n");
    return 0;
}