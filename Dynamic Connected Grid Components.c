#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int parent;
    int size;
} DSU;

int find(DSU dsu[], int x)
{ // function to find the representative (root) of the set containing element x in the Disjoint Set Union (DSU) data structure. It takes an array of DSU structures (dsu) and an integer x as input. The function first checks if x is its own parent, indicating that it is the root of its set. If so, it returns x. If not, it recursively calls itself to find the root of x's parent and updates x's parent to point directly to the root (path compression). This ensures that future queries for the same element can be answered more efficiently by reducing the height of the tree representing the disjoint sets. Finally, it returns the representative (root) of the set containing x.
    if (dsu[x].parent == x)
        return x;

    dsu[x].parent = find(dsu, dsu[x].parent);
    return dsu[x].parent;
}

int unite(DSU dsu[], int a, int b)
{ // function to unite two sets containing elements a and b in the Disjoint Set Union (DSU) data structure. It takes an array of DSU structures (dsu) and two integers a and b as input. The function first finds the representatives (roots) of the sets containing a and b using the find function. If both elements belong to the same set (same representative), it returns 0 to indicate that they are already united. If they belong to different sets, it merges the two sets by making the root of one set point to the root of the other set. To optimize the union operation, it uses union by size, where the smaller set is merged into the larger set. The size of the resulting set is updated accordingly. Finally, it returns 1 to indicate that the sets were successfully united.
    int ra = find(dsu, a);
    int rb = find(dsu, b);

    if (ra == rb)
        return 0;

    if (dsu[ra].size < dsu[rb].size)
    {
        int temp = ra;
        ra = rb;
        rb = temp;
    }

    dsu[rb].parent = ra;
    dsu[ra].size += dsu[rb].size;

    return 1;
}

int main()
{
    int R, C, K;

    printf("Enter rows and columns: ");
    scanf("%d %d", &R, &C);

    printf("Enter number of land additions: ");
    scanf("%d", &K);

    int total = R * C;

    DSU *dsu = malloc(total * sizeof(DSU));
    int *land = calloc(total, sizeof(int));

    for (int i = 0; i < total; i++)
    {
        dsu[i].parent = i;
        dsu[i].size = 1;
    }

    int components = 0;

    int dr[] = {-1, 1, 0, 0}; // dr[] and dc[] arrays represent the row and column offsets for the four possible directions (up, down, left, right) when checking neighboring cells in the grid. These offsets are used to calculate the coordinates of neighboring cells relative to the current cell being processed. By iterating through these offsets, the algorithm can efficiently check all adjacent cells to determine if they are part of the same connected component of land.
    int dc[] = {0, 0, -1, 1};

    printf("Enter land positions (row column):\n");

    for (int op = 0; op < K; op++)
    {
        int r, c;
        scanf("%d %d", &r, &c);

        if (r < 0 || r >= R || c < 0 || c >= C)
        {
            printf("Invalid position -> %d\n", components);
            continue;
        }

        int id = r * C + c;

        if (land[id])
        {
            printf("%d\n", components);
            continue;
        }

        land[id] = 1;
        components++;

        for (int d = 0; d < 4; d++)
        { // Iterate through the four possible directions (up, down, left, right) to check neighboring cells of the newly added land cell. For each direction, it calculates the coordinates of the neighboring cell using the dr[] and dc[] offsets. If the neighboring cell is within the grid boundaries and is also land (land[neighbor] is true), it attempts to unite the current land cell with the neighboring land cell using the unite function. If the union is successful (the two cells were previously in different components), it decrements the components count, as two separate components have now been merged into one. This process ensures that the algorithm accurately tracks the number of connected components of land in the grid after each addition.
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr < 0 || nr >= R ||
                nc < 0 || nc >= C)
                continue;

            int neighbor = nr * C + nc;

            if (land[neighbor])
            { // Check if the neighboring cell is land. If it is, attempt to unite the current land cell with the neighboring land cell using the unite function. If the union is successful (the two cells were previously in different components), decrement the components count, as two separate components have now been merged into one.
                if (unite(dsu, id, neighbor))
                    components--;
            }
        }

        printf("%d\n", components);
    }

    free(dsu);
    free(land);

    return 0;
}