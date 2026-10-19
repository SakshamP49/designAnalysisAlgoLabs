#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int parent;
    int rank;
} DSU;

int find(DSU dsu[], int x)
{ // function to find the representative (root) of the set containing element x in the Disjoint Set Union (DSU) data structure. It takes an array of DSU structures (dsu) and an integer x as input. The function first checks if x is its own parent, indicating that it is the root of its set. If so, it returns x. If not, it recursively calls itself to find the root of x's parent and updates x's parent to point directly to the root (path compression). This ensures that future queries for the same element can be answered more efficiently by reducing the height of the tree representing the disjoint sets. Finally, it returns the representative (root) of the set containing x.
    if (dsu[x].parent == x)
        return x;

    dsu[x].parent = find(dsu, dsu[x].parent);
    return dsu[x].parent;
}

void unite(DSU dsu[], int a, int b)
{ // function to unite two sets containing elements a and b in the Disjoint Set Union (DSU) data structure. It takes an array of DSU structures (dsu) and two integers a and b as input. The function first finds the representatives (roots) of the sets containing a and b using the find function. If both elements belong to the same set (same representative), it returns without making any changes. If they belong to different sets, it merges the two sets by making the root of one set point to the root of the other set. To optimize the union operation, it uses union by rank, where the tree with a smaller rank is merged into the tree with a larger rank. If both trees have the same rank, one tree is arbitrarily chosen to be merged into the other, and its rank is incremented by 1. This ensures that the height of the trees remains balanced, allowing for efficient future queries.
    int ra = find(dsu, a);
    int rb = find(dsu, b);

    if (ra == rb)
        return;

    if (dsu[ra].rank < dsu[rb].rank)
    {
        dsu[ra].parent = rb;
    }
    else if (dsu[ra].rank > dsu[rb].rank)
    { // Merge the two components by making the root of the smaller rank point to the root of the larger rank. This ensures that the height of the trees remains balanced, allowing for efficient future queries.
        dsu[rb].parent = ra;
    }
    else
    {
        dsu[rb].parent = ra;
        dsu[ra].rank++;
    }
}

int compareInt(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n, m;

    printf("Enter n: ");
    scanf("%d", &n);

    int *A = malloc(n * sizeof(int));

    printf("Enter permutation A:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("Enter number of allowed swaps: ");
    scanf("%d", &m);

    DSU *dsu = malloc(n * sizeof(DSU));

    for (int i = 0; i < n; i++)
    {
        dsu[i].parent = i;
        dsu[i].rank = 0;
    }

    printf("Enter allowed swap edges:\n");

    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        u--;
        v--;

        if (u >= 0 && u < n && v >= 0 && v < n)
        {
            unite(dsu, u, v); // Unite the two sets containing elements u and v in the Disjoint Set Union (DSU) data structure. This operation merges the connected components formed by the allowed swaps, allowing for efficient tracking of which elements can be swapped with each other. The unite function ensures that the DSU structure remains balanced and optimized for future queries regarding connected components.
        }
    }

    int **indices = malloc(n * sizeof(int *));
    int **values = malloc(n * sizeof(int *));
    int *count = calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
    { // Allocate memory for the indices and values arrays for each component. The size of each array is equal to n, which is the total number of elements in the permutation. This ensures that there is enough space to store all indices and values for each connected component formed by the allowed swaps. The indices array will hold the original positions of the elements in the permutation, while the values array will hold the corresponding values from the permutation A. The count array is used to keep track of how many elements belong to each component, allowing for efficient sorting and assignment of values later in the algorithm.
        indices[i] = malloc(n * sizeof(int));
        values[i] = malloc(n * sizeof(int));
    }

    // Collect indices and values for each component
    for (int i = 0; i < n; i++)
    { // Iterate through each element in the permutation A to collect the indices and values for each connected component formed by the allowed swaps. For each element at index i, it finds the representative (root) of the set containing i using the find function. It then stores the index i in the indices array for that component and the corresponding value A[i] in the values array for that component. The count array is incremented for that component to keep track of how many elements belong to it. This process ensures that all indices and values are grouped together based on their connected components, allowing for efficient sorting and assignment of values later in the algorithm.
        int root = find(dsu, i);

        indices[root][count[root]] = i;
        values[root][count[root]] = A[i];

        count[root]++;
    }

    // Sort indices and values within each component
    for (int i = 0; i < n; i++)
    { // Iterate through each component to sort the indices and values within that component. For each component represented by root i, it checks if there are any elements in that component (count[i] > 0). If there are elements, it uses the qsort function to sort the indices array for that component in ascending order, ensuring that the original positions of the elements are ordered. It also sorts the values array for that component in ascending order, ensuring that the smallest values are assigned to the smallest indices. This sorting step is crucial for constructing the lexicographically smallest permutation by ensuring that the smallest available values are placed in the earliest possible positions within each connected component.
        if (count[i] == 0)
            continue;

        qsort(indices[i], count[i], sizeof(int), compareInt);

        qsort(values[i], count[i], sizeof(int), compareInt);
    }

    int *answer = malloc(n * sizeof(int));

    // Assign smallest values to smallest indices
    for (int root = 0; root < n; root++)
    { // Iterate through each component to assign the smallest values to the smallest indices within that component. For each component represented by root, it checks if there are any elements in that component (count[root] > 0). If there are elements, it iterates through the sorted indices and values for that component and assigns the smallest value to the smallest index in the answer array. This ensures that the resulting permutation is lexicographically smallest by placing the smallest available values in the earliest possible positions within each connected component formed by the allowed swaps.
        for (int j = 0; j < count[root]; j++)
        {
            answer[indices[root][j]] =
                values[root][j];
        }
    }

    printf("\nLexicographically smallest permutation:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", answer[i]);

    printf("\n");

    for (int i = 0; i < n; i++)
    {
        free(indices[i]);
        free(values[i]);
    }

    free(indices);
    free(values);
    free(count);
    free(answer);
    free(A);
    free(dsu);

    return 0;
}


 

 
