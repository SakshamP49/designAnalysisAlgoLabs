#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int parent;
    int size;
    long long sum;
} DSU;

int find(DSU dsu[], int x)
{ // function to find the representative (root) of the set containing element x in the Disjoint Set Union (DSU) data structure. It takes an array of DSU structures (dsu) and an integer x as input. The function first checks if x is its own parent, indicating that it is the root of its set. If so, it returns x. If not, it recursively calls itself to find the root of x's parent and updates x's parent to point directly to the root (path compression). This ensures that future queries for the same element can be answered more efficiently by reducing the height of the tree representing the disjoint sets. Finally, it returns the representative (root) of the set containing x.
    if (dsu[x].parent == x)
        return x;

    dsu[x].parent = find(dsu, dsu[x].parent);
    return dsu[x].parent;
}

void unite(DSU dsu[], int a, int b, long long *maximum)
{ // function to unite two sets containing elements a and b in the Disjoint Set Union (DSU) data structure. It takes an array of DSU structures (dsu), two integers a and b, and a pointer to a long long variable (maximum) as input. The function first finds the representatives (roots) of the sets containing a and b using the find function. If both elements belong to the same set (same representative), it returns without making any changes. If they belong to different sets, it merges the two sets by making the root of one set point to the root of the other set. To optimize the union operation, it uses union by size, where the smaller set is merged into the larger set. The size and sum of the resulting set are updated accordingly. Additionally, if the sum of the newly formed set exceeds the current maximum value pointed to by maximum, it updates maximum to reflect this new maximum sum. This allows for efficient tracking of the maximum sum of connected components during processing.
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
    dsu[ra].size += dsu[rb].size;// Update the size of the resulting set by adding the sizes of the two merged sets. This ensures that the size information remains accurate for future union operations and queries regarding the connected components in the DSU structure.
    dsu[ra].sum += dsu[rb].sum;

    if (dsu[ra].sum > *maximum)
        *maximum = dsu[ra].sum;
}

int main()
{
    int V;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    int *weight = malloc(V * sizeof(int));

    printf("Enter vertex weights:\n");

    for (int i = 0; i < V; i++)
        scanf("%d", &weight[i]);

    int **adj = malloc(V * sizeof(int *));

    for (int i = 0; i < V; i++)
        adj[i] = calloc(V, sizeof(int));

    int E;

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges:\n");

    for (int i = 0; i < E; i++)
    { // Iterate through the number of edges (E) to read and process each edge. For each edge, it reads the two vertices (u and v) that the edge connects. It then checks if the vertices are valid (within the range of 0 to V-1). If they are valid, it updates the adjacency matrix (adj) to indicate that there is an edge between u and v by setting adj[u][v] and adj[v][u] to 1. This creates an undirected graph representation in the form of an adjacency matrix, allowing for efficient lookups of connections between vertices during processing.
        int u, v;
        scanf("%d %d", &u, &v);

        u--;
        v--;

        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    int *order = malloc(V * sizeof(int));

    printf("Enter deletion order:\n");

    for (int i = 0; i < V; i++)
    { // Iterate through the number of vertices (V) to read the order in which vertices will be deleted. For each vertex, it reads an integer representing the vertex index and stores it in the order array. The input is adjusted by decrementing the value by 1 to convert from 1-based indexing (common in user input) to 0-based indexing (used in the program). This order array will be used later to simulate the deletion of vertices and track the maximum component sum after each deletion.
        scanf("%d", &order[i]);
        order[i]--;
    }

    DSU *dsu = malloc(V * sizeof(DSU));
    int *active = calloc(V, sizeof(int)); // Allocate memory for the active array, which will be used to track the status of each vertex (active or deleted) during the simulation of vertex deletions. The size of the array is equal to the number of vertices (V), and it is initialized to 0 (indicating that all vertices are initially inactive). As vertices are processed in the specified deletion order, their corresponding entries in the active array will be updated to reflect their active status, allowing for efficient checks of connectivity and component sums during the simulation.
    long long *answer = malloc((V + 1) * sizeof(long long));

    for (int i = 0; i < V; i++)
    {
        dsu[i].parent = i;
        dsu[i].size = 1;
        dsu[i].sum = weight[i];
    }

    long long maximum = 0;

    answer[V] = 0;

    for (int i = V - 1; i >= 0; i--)
    { // Iterate through the vertices in reverse order of deletion (from the last vertex to be deleted to the first). For each vertex, it retrieves the vertex index from the order array and marks it as active in the active array. It initializes the DSU structure for that vertex by setting its parent to itself, size to 1, and sum to its weight. If the weight of the vertex exceeds the current maximum sum, it updates the maximum value. The algorithm then checks all other vertices to see if they are adjacent to the current vertex and are also active. If both conditions are met, it calls the unite function to merge their sets in the DSU structure and update the maximum sum accordingly. Finally, it stores the current maximum sum in the answer array at index i, which represents the maximum component sum after deleting vertices up to that point.
        int v = order[i];

        active[v] = 1;

        dsu[v].parent = v;
        dsu[v].size = 1;
        dsu[v].sum = weight[v];

        if (weight[v] > maximum)
            maximum = weight[v];

        for (int u = 0; u < V; u++)
        { // Iterate through all vertices (u) to check for adjacency and active status with the current vertex (v). For each vertex u, it checks if there is an edge between v and u in the adjacency matrix (adj[v][u]) and if u is marked as active in the active array. If both conditions are satisfied, it calls the unite function to merge the sets containing v and u in the DSU structure. This process ensures that all connected components involving the newly activated vertex are properly merged, and the maximum component sum is updated accordingly.
            if (adj[v][u] && active[u])
                unite(dsu, v, u, &maximum);
        }

        answer[i] = maximum;
    }

    printf("\nMaximum component sum after each deletion:\n");

    for (int i = 1; i <= V; i++)
        printf("After deleting %d: %lld\n",
               order[i - 1] + 1,
               answer[i]);

    free(weight);
    free(order);
    free(active);
    free(answer);
    free(dsu);

    for (int i = 0; i < V; i++)
        free(adj[i]);

    free(adj);

    return 0;
}