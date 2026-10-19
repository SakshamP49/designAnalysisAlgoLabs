#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int parent;
    int rank;
    int parity;   // parity[x] = color[x] ^ color[parent[x]]
} DSU;

int find(DSU dsu[], int x)
{ // function to find the representative (root) of the set containing element x in the Disjoint Set Union (DSU) data structure. It takes an array of DSU structures (dsu) and an integer x as input. The function first checks if x is its own parent, indicating that it is the root of its set. If so, it returns x. If not, it recursively calls itself to find the root of x's parent and updates x's parent to point directly to the root (path compression). Additionally, it updates the parity of x based on the parity of its parent, ensuring that the color information is maintained correctly. Finally, it returns the representative (root) of the set containing x.
    if (dsu[x].parent == x)
        return x;

    int parent = dsu[x].parent;
    dsu[x].parent = find(dsu, parent);
    dsu[x].parity ^= dsu[parent].parity; // Update the parity of x based on the parity of its parent, ensuring that the color information is maintained correctly.

    return dsu[x].parent;
}

int addEdge(DSU dsu[], int u, int v)
{ // function to add an edge between vertices u and v in the graph while maintaining the bipartiteness property. It takes an array of DSU structures (dsu) and two integers u and v as input. The function first finds the representatives (roots) of the sets containing u and v using the find function. It also retrieves the parity (color) information for both vertices. If u and v belong to the same set (same representative), it checks if they have the same color (parity). If they do, adding the edge would violate the bipartiteness property, so it returns 0 to indicate that the edge cannot be added. If u and v belong to different sets, it merges the two sets by updating the parent and parity information accordingly, ensuring that the bipartiteness property is preserved. Finally, it returns 1 to indicate that the edge was successfully added.
    int ru = find(dsu, u);
    int pv = dsu[u].parity;

    int rv = find(dsu, v);
    int qv = dsu[v].parity;

    // Same component
    if (ru == rv)
    {
        // Edge must connect opposite colors
        if ((pv ^ qv) == 0)
            return 0;

        return 1;
    }

    // Merge the two components
    if (dsu[ru].rank < dsu[rv].rank)
    {
        dsu[ru].parent = rv;
        dsu[ru].parity = pv ^ qv ^ 1;
    }
    else if (dsu[ru].rank > dsu[rv].rank)
    { // Merge the two components by making the root of the smaller rank point to the root of the larger rank. The parity of the root of the smaller rank is updated based on the parities of u and v, ensuring that the bipartiteness property is preserved. This allows for efficient union operations while maintaining the structure of the disjoint sets.
        dsu[rv].parent = ru;
        dsu[rv].parity = pv ^ qv ^ 1;
    }
    else
    {
        dsu[rv].parent = ru;
        dsu[rv].parity = pv ^ qv ^ 1;
        dsu[ru].rank++;
    }

    return 1;
}

int main()
{
    int V, E;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    DSU *dsu = malloc(V * sizeof(DSU));

    for (int i = 0; i < V; i++)
    {
        dsu[i].parent = i;
        dsu[i].rank = 0;
        dsu[i].parity = 0;
    }

    printf("Enter edges (u v):\n");

    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        u--;
        v--;
        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            printf("Edge %d skipped: invalid vertices\n", i + 1);
            continue;
        }
        if (addEdge(dsu, u, v))
            printf("Edge (%d, %d) added: graph remains bipartite\n",u + 1, v + 1);
        else
            printf("Edge (%d, %d) rejected: violates bipartiteness\n", u + 1, v + 1);
    }

    free(dsu);

    return 0;
}