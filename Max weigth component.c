#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int parent;
    int size;
    long long weight;
} DSU;

int find(DSU dsu[], int x)
{// function to find the representative (root) of the set containing element x in the Disjoint Set Union (DSU) data structure. It takes an array of DSU structures (dsu) and an integer x as input. The function first checks if x is its own parent, indicating that it is the root of its set. If so, it returns x. If not, it recursively calls itself to find the root of x's parent and updates x's parent to point directly to the root (path compression). This ensures that future queries for the same element can be answered more efficiently by reducing the height of the tree representing the disjoint sets. Finally, it returns the representative (root) of the set containing x.
    if (dsu[x].parent == x)
        return x;

    dsu[x].parent = find(dsu, dsu[x].parent);
    return dsu[x].parent;
}

void unite(DSU dsu[], int a, int b)
{ // function to unite two sets containing elements a and b in the Disjoint Set Union (DSU) data structure. It takes an array of DSU structures (dsu) and two integers a and b as input. The function first finds the representatives (roots) of the sets containing a and b using the find function. If both elements belong to the same set (same representative), it returns without making any changes. If they belong to different sets, it merges the two sets by making the root of one set point to the root of the other set. To optimize the union operation, it uses union by size, where the smaller set is merged into the larger set. The size and weight of the resulting set are updated accordingly.
    int ra = find(dsu, a);
    int rb = find(dsu, b);

    if (ra == rb)
        return;

    if (dsu[ra].size < dsu[rb].size)
    {
        int temp = ra;
        ra = rb;
        rb = temp;
    }

    dsu[rb].parent = ra;
    dsu[ra].size += dsu[rb].size;
    dsu[ra].weight += dsu[rb].weight;
}

long long getMaximumWeight(DSU dsu[], int n, int K)
{ // function to find the maximum weight of a connected component in the Disjoint Set Union (DSU) data structure that has a size less than or equal to K. It takes an array of DSU structures (dsu), the number of elements (n), and the size threshold (K) as input. The function iterates through all elements in the DSU array and checks if each element is a representative (root) of its set. If it is, and if the size of the set is less than or equal to K, it compares the weight of that set with the current maximum weight found. If the weight is greater than the current maximum, it updates the maximum weight. Finally, it returns the maximum weight found among all valid connected components.
    long long maximum = 0;

    for (int i = 0; i < n; i++)
    {
        if (dsu[i].parent == i &&
            dsu[i].size <= K)
        {
            if (dsu[i].weight > maximum)
                maximum = dsu[i].weight;
        }
    }

    return maximum;
}

int main()
{
    int V, E, K;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter size threshold K: ");
    scanf("%d", &K);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    DSU *dsu = malloc(V * sizeof(DSU));

    printf("Enter vertex weights:\n");

    for (int i = 0; i < V; i++)
    {
        long long w;
        scanf("%lld", &w);

        dsu[i].parent = i;
        dsu[i].size = 1;
        dsu[i].weight = w;
    }

    printf("Maximum valid component weight initially: %lld\n",
           getMaximumWeight(dsu, V, K));

    printf("Enter edges:\n");

    for (int i = 0; i < E; i++)
    { // Iterate through the number of edges (E) to read and process each edge. For each edge, it reads the two vertices (u and v) that the edge connects. It then checks if the vertices are valid (within the range of 0 to V-1). If they are valid, it calls the unite function to merge the sets containing u and v in the DSU structure. After processing each edge, it calculates and prints the maximum weight of a connected component that has a size less than or equal to K by calling the getMaximumWeight function. This allows for dynamic updates to the connected components as edges are added, providing real-time feedback on the maximum valid component weight.
        int u, v;
        scanf("%d %d", &u, &v);

        u--;
        v--;

        if (u >= 0 && u < V &&
            v >= 0 && v < V)
        {
            unite(dsu, u, v);
        }

        printf("Maximum valid component weight = %lld\n",
               getMaximumWeight(dsu, V, K));
    }

    free(dsu);

    return 0;
}