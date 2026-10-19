#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#define MAX 100

double e[MAX + 2][MAX + 1];
double w[MAX + 2][MAX + 1];
int root[MAX + 1][MAX + 1];
void optimalBST(double p[], double q[], int n)
{
    /*
        p[1..n] = probabilities of successful searches
        q[0..n] = probabilities of unsuccessful searches

        e[i][j] = minimum expected search cost
                  for keys Ki ... Kj

        w[i][j] = total probability of keys Ki...Kj
                  and dummy keys Di-1...Dj

        root[i][j] = root of optimal subtree Ki...Kj
    */

    for (int i = 1; i <= n + 1; i++)
    { // Initialize the expected search cost and total probability for empty subtrees (where i > j). For each index i from 1 to n+1, set e[i][i-1] to q[i-1], which represents the expected search cost for an empty subtree (no keys) and is equal to the probability of an unsuccessful search for the dummy key Di-1. Similarly, set w[i][i-1] to q[i-1], which represents the total probability of an empty subtree and is also equal to the probability of an unsuccessful search for the dummy key Di-1. This initialization is crucial for the dynamic programming algorithm, as it provides the base case for calculating the expected search costs and probabilities for larger subtrees.
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int length = 1; length <= n; length++)
    { // Iterate through all possible lengths of subtrees from 1 to n. For each length, the algorithm will calculate the minimum expected search cost and total probability for all subtrees of that length. The outer loop variable 'length' represents the number of keys in the current subtree being considered. The inner loops will iterate through all possible starting indices 'i' for subtrees of the current length, calculating the corresponding ending index 'j' and updating the expected search costs, total probabilities, and optimal roots for each subtree.
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            e[i][j] = DBL_MAX;

            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; r++)
            { // Iterate through all possible roots 'r' for the current subtree defined by indices 'i' and 'j'. For each root 'r', calculate the expected search cost of the subtree by summing the expected search costs of the left and right subtrees (e[i][r-1] and e[r+1][j]) and adding the total probability of the current subtree (w[i][j]). This represents the expected cost of searching in a binary search tree where 'r' is the root, and the left and right subtrees are optimally constructed. If this calculated cost is less than the current minimum expected search cost stored in e[i][j], update e[i][j] with the new minimum cost and record 'r' as the optimal root for this subtree in root[i][j]. This process ensures that for each subtree, we find the optimal root that minimizes the expected search cost.
                double cost = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (cost < e[i][j])
                {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }
}

void printTree(int i, int j, int parent, char side[])
{ // function to print the structure of the optimal binary search tree (OBST) based on the calculated root indices. It takes the starting index 'i', ending index 'j', the parent node index, and a string indicating whether the current node is a left or right child. The function first checks if the current subtree is empty (i > j). If it is, it prints that the dummy key Dj is the left or right child of the parent node, depending on the 'side' parameter. If the subtree is not empty, it retrieves the root index 'r' for the current subtree from the root array. It then prints whether K[r] is the root of the current subtree or a left/right child of its parent. The function recursively calls itself to print the left and right subtrees of K[r], passing the appropriate indices and updating the parent and side parameters accordingly. This recursive process continues until all nodes in the OBST have been printed, providing a clear representation of the tree structure.
    if (i > j)
    {
        printf("d%d is the %s child of K%d\n", j, side, parent);
        return;
    }

    int r = root[i][j];
    if (parent == 0)
    {
        printf("K%d is the root\n", r);
    }
    else
    {
        printf("K%d is the %s child of K%d\n", r, side, parent);
    }

    printTree(i, r - 1, r, "left");
    printTree(r + 1, j, r, "right");
}

int main()
{
    int n;
    double p[MAX + 1];
    double q[MAX + 1];
    printf("Enter number of keys: ");
    scanf("%d", &n);
    printf("Enter probabilities p1 to p%d:\n", n);
    for (int i = 1; i <= n; i++)
     scanf("%lf", &p[i]);
    printf("Enter probabilities q0 to q%d:\n", n);
    for (int i = 0; i <= n; i++)
        scanf("%lf", &q[i]);
    optimalBST(p, q, n);
    printf("\nMinimum expected search cost = %.6lf\n", e[1][n]);
    printf("\nOptimal Binary Search Tree:\n");
    printTree(1, n, 0, "");
    return 0;
}