#include <stdio.h>
#include <stdlib.h>

#define MAX 100

#define TERMINAL 0
#define INTERNAL 1
#define NONE 2

long long weight[MAX];
int state[MAX];
int root[MAX];

int leftChild[2 * MAX];
int rightChild[2 * MAX];

int nodeCount;

void buildHuTucker(long long w[], int n)
{ // function to build the Hu-Tucker tree for a given set of weights. It takes an array of weights (w) and the number of weights (n) as input. The function initializes the weight, state, and root arrays for each weight. It then iteratively finds the pair of nodes with the smallest combined weight that can be merged into a new internal node. The function checks for valid pairs by ensuring that there are no terminal nodes between the two selected nodes. Once a valid pair is found, it creates a new internal node, updates the left and right child pointers, and updates the weight and state of the merged node. This process continues until all nodes are merged into a single tree structure, resulting in an optimal alphabetic tree based on the given weights.
    for (int i = 0; i < n; i++)
    {
        weight[i] = w[i];
        state[i] = TERMINAL;
        root[i] = i;
    }

    nodeCount = n;

    for (int step = 0; step < n - 1; step++)
    { // Iterate n-1 times to merge nodes into a single tree. In each iteration, the function searches for the pair of nodes with the smallest combined weight that can be merged into a new internal node. It initializes variables to track the best sum and the indices of the best pair of nodes (bestI and bestJ). The nested loops iterate through all pairs of nodes (i, j) to find valid pairs that can be merged. A valid pair is one where there are no terminal nodes between the two selected nodes. If a valid pair is found with a smaller combined weight than the current best sum, it updates the best sum and the indices of the best pair. If multiple pairs have the same combined weight, it selects the pair with the smallest indices to ensure a consistent ordering. Once a valid pair is found, it creates a new internal node, updates the left and right child pointers, and updates the weight and state of the merged node. This process continues until all nodes are merged into a single tree structure.
        long long bestSum =
            9223372036854775807LL;

        int bestI = -1;
        int bestJ = -1;

        for (int i = 0; i < n; i++)
        {
            if (state[i] == NONE)
                continue;

            for (int j = i + 1; j < n; j++)
            {
                if (state[j] == NONE)
                    continue;

                int valid = 1;

                for (int k = i + 1; k < j; k++)
                {
                    if (state[k] == TERMINAL)
                    {
                        valid = 0;
                        break;
                    }
                }

                if (!valid)
                    continue;

                long long sum = weight[i] + weight[j];

                if (sum < bestSum)
                { // Update the best sum and the indices of the best pair of nodes (bestI and bestJ) if a valid pair with a smaller combined weight is found. This ensures that the algorithm selects the optimal pair of nodes to merge into a new internal node, contributing to the construction of an optimal alphabetic tree based on the given weights.
                    bestSum = sum;
                    bestI = i;
                    bestJ = j;
                }
                else if (sum == bestSum)
                {
                    if (bestI == -1 ||
                        i < bestI ||
                        (i == bestI && j < bestJ))
                    {
                        bestI = i;
                        bestJ = j;
                    }
                }
            }
        }

        if (bestI == -1)
            return;

        int newNode = nodeCount++;

        leftChild[newNode] = root[bestI];

        rightChild[newNode] = root[bestJ];

        root[bestI] = newNode;

        weight[bestI] += weight[bestJ];

        state[bestI] = INTERNAL;
        state[bestJ] = NONE;
    }
}

void findDepths(int node, int depth, int n,int depths[])
{// function to find the depths of each terminal node in the Hu-Tucker tree. It takes the current node index (node), the current depth (depth), the total number of terminal nodes (n), and an array to store the depths (depths) as input. The function recursively traverses the tree, starting from the root node, and updates the depth of each terminal node in the depths array. If the current node is a terminal node (node < n), it assigns the current depth to the corresponding index in the depths array. If the current node is an internal node, it recursively calls itself for the left and right child nodes, incrementing the depth by 1 for each level of recursion. This process continues until all terminal nodes have their depths calculated and stored in the depths array.
    if (node == -1)
        return;
    if (node < n)
    {
        depths[node] = depth;
        return;
    }

    findDepths(leftChild[node], depth + 1, n, depths);
    findDepths(rightChild[node], depth + 1, n, depths);
}

void printTree(int node, int n)
{ // function to print the structure of the Hu-Tucker tree in a readable format. It takes the current node index (node) and the total number of terminal nodes (n) as input. The function recursively traverses the tree, starting from the root node, and prints the structure of the tree using parentheses to indicate the hierarchy of nodes. If the current node is a terminal node (node < n), it prints the corresponding key identifier (K followed by the index + 1). If the current node is an internal node, it prints an opening parenthesis, recursively calls itself for the left and right child nodes, and prints a closing parenthesis. This process continues until all nodes in the tree have been printed, providing a clear representation of the optimal alphabetic tree based on the given weights.
    if (node < n)
    {
        printf("K%d", node + 1);
        return;
    }

    printf("(");

    printTree(leftChild[node], n);

    printf(" , ");

    printTree(rightChild[node], n);

    printf(")");
}

int main()
{
    int n;

    printf("Enter number of ordered keys: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of keys.\n");
        return 0;
    }

    long long w[n];

    printf("Enter weights:\n");

    for (int i = 0; i < n; i++)
        scanf("%lld", &w[i]);

    buildHuTucker(w, n);

    int depths[MAX];

    for (int i = 0; i < n; i++)
        depths[i] = 0;

    findDepths(root[0], 0, n, depths);

    long long minimumCost = 0;

    for (int i = 0; i < n; i++)
    {
        minimumCost +=
            w[i] * depths[i];
    }

    printf("\nMinimum weighted path length = %lld\n",
           minimumCost);

    printf("\nOptimal alphabetic tree:\n");
    printTree(root[0], n);

    printf("\n\nDepths:\n");

    for (int i = 0; i < n; i++)
    {
        printf("K%d -> depth %d\n", i + 1,
               depths[i]);
    }

    return 0;
}