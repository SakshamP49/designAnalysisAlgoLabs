#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{ // Structure to represent an edit operation. It contains three fields: type, from, and to. The type field indicates the type of operation (insertion, deletion, or substitution). The from field represents the character being replaced or deleted, and the to field represents the character being inserted or substituted. This structure is used to store the details of each edit operation performed during the calculation of the edit distance between two strings.
    char type;
    char from;
    char to;
} Operation;

void printEditOperations(char A[], char B[])
{ // function to calculate the edit distance between two strings A and B, and print the sequence of edit operations required to transform A into B. It takes two character arrays (strings) A and B as input. The function first calculates the lengths of the two strings (m and n). It then allocates a 2D array dp to store the minimum edit distances for different substrings of A and B. The dp array is filled using dynamic programming, where dp[i][j] represents the minimum edit distance between A[0..i-1] and B[0..j-1]. After filling the dp array, the function backtracks through it to construct the sequence of edit operations (insertions, deletions, substitutions) needed to transform A into B. Finally, it prints the edit distance and the sequence of operations.
    int m = strlen(A);
    int n = strlen(B);

    int *dp = malloc((m + 1) * (n + 1) * sizeof(int));

    if (dp == NULL)
        return;

    #define DP(i, j) dp[(i) * (n + 1) + (j)] // Macro to access the 2D dp array as a 1D array. It takes two indices i and j and calculates the corresponding index in the 1D dp array. This allows for efficient storage and access of the edit distance values without needing to allocate a separate 2D array. The macro simplifies the code by providing a convenient way to reference the dp array using two-dimensional indexing while actually using a one-dimensional representation in memory.

    for (int i = 0; i <= m; i++)
        DP(i, 0) = i;

    for (int j = 0; j <= n; j++)
        DP(0, j) = j;

    for (int i = 1; i <= m; i++)
    { // Fill the dp array using dynamic programming to calculate the minimum edit distances for different substrings of A and B. The outer loop iterates through each character of string A (from 1 to m), and the inner loop iterates through each character of string B (from 1 to n). For each pair of characters (A[i-1] and B[j-1]), the function checks if they are equal. If they are equal, it means that no edit operation is needed, and the value is taken from the diagonal cell (DP(i-1, j-1)). If they are not equal, the function calculates the costs for insertion, deletion, and substitution operations. It then takes the minimum of these costs and adds 1 to account for the current edit operation. This process continues until the entire dp array is filled, resulting in DP(m, n) containing the minimum edit distance between strings A and B.
        for (int j = 1; j <= n; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                DP(i, j) = DP(i - 1, j - 1);
            }
            else
            { // If the current characters of A and B are not equal, the function calculates the costs for insertion, deletion, and substitution operations. The insertCost is obtained from the left cell (DP(i, j-1)), the deleteCost is obtained from the top cell (DP(i-1, j)), and the replaceCost is obtained from the diagonal cell (DP(i-1, j-1)). The function then finds the minimum of these three costs and adds 1 to account for the current edit operation. This ensures that the dp array is filled correctly to reflect the minimum edit distances for different substrings of A and B.
                int insertCost = DP(i, j - 1);
                int deleteCost = DP(i - 1, j);
                int replaceCost = DP(i - 1, j - 1);

                int minimum = insertCost;

                if (deleteCost < minimum)
                    minimum = deleteCost;

                if (replaceCost < minimum)
                    minimum = replaceCost;

                DP(i, j) = minimum + 1;
            }
        }
    }

    printf("Edit distance = %d\n", DP(m, n));

    Operation *operations = malloc((m + n + 1) * sizeof(Operation));

    int count = 0;

    int i = m;
    int j = n;

    while (i > 0 || j > 0)
    { // Backtrack through the dp array to construct the sequence of edit operations needed to transform A into B. Starting from the bottom-right corner of the dp array (DP(m, n)), the function checks the values in the dp array to determine which operation was performed to reach the current cell. If the characters A[i-1] and B[j-1] are equal, it means no edit operation was needed, and both indices i and j are decremented. If they are not equal, the function checks if the current cell's value is equal to the diagonal cell's value plus 1, indicating a substitution operation. If so, it records a substitution operation in the operations array and decrements both indices. If the current cell's value is equal to the left cell's value plus 1, it indicates an insertion operation, and only index j is decremented. If the current cell's value is equal to the top cell's value plus 1, it indicates a deletion operation, and only index i is decremented. This process continues until either i or j reaches 0, indicating that one of the strings has been fully processed.
        if (i > 0 && j > 0 &&
            A[i - 1] == B[j - 1])
        {
            i--;
            j--;
        }
        else if (i > 0 && j > 0 &&
                 DP(i, j) == DP(i - 1, j - 1) + 1)
        {
            operations[count].type = 'S';
            operations[count].from = A[i - 1];
            operations[count].to = B[j - 1];

            count++;

            i--;
            j--;
        }
        else if (i > 0 &&
                 DP(i, j) == DP(i - 1, j) + 1)
        { // If the current cell's value is equal to the top cell's value plus 1, it indicates a deletion operation. The function records a deletion operation in the operations array, where the type is set to 'D', the from field is set to the character being deleted (A[i-1]), and the to field is set to '-' to indicate that no character is being inserted. The count of operations is incremented, and index i is decremented to move up in the dp array.
            operations[count].type = 'D';
            operations[count].from = A[i - 1];
            operations[count].to = '-';

            count++;

            i--;
        }
        else
        { // If the current cell's value is equal to the left cell's value plus 1, it indicates an insertion operation. The function records an insertion operation in the operations array, where the type is set to 'I', the from field is set to '-' to indicate that no character is being deleted, and the to field is set to the character being inserted (B[j-1]). The count of operations is incremented, and index j is decremented to move left in the dp array.
            operations[count].type = 'I';
            operations[count].from = '-';
            operations[count].to = B[j - 1];

            count++;

            j--;
        }
    }

    printf("\nTraceback:\n");

    for (int k = count - 1; k >= 0; k--)
    { // Print the sequence of edit operations in reverse order (from the last operation to the first). The loop iterates through the operations array from the last recorded operation (count - 1) down to the first operation (index 0). For each operation, it checks the type of operation (substitution, deletion, or insertion) and prints the corresponding details. For substitution operations, it prints the characters being replaced and inserted. For deletion operations, it prints the character being deleted. For insertion operations, it prints the character being inserted. This provides a clear and detailed view of how to transform string A into string B using the minimum number of edit operations.
        if (operations[k].type == 'S')
        {
            printf("Substitute %c -> %c\n",
                   operations[k].from,
                   operations[k].to);
        }
        else if (operations[k].type == 'D')
        { // If the operation type is 'D' (deletion), it prints the character being deleted from string A. The from field of the operation structure contains the character that is being removed, and it is displayed in the output to indicate which character is being deleted during the transformation process.
            printf("Delete %c\n",
                   operations[k].from);
        }
        else
        {
            printf("Insert %c\n",
                   operations[k].to);
        }
    }

    free(operations);
    free(dp);
}

int main()
{
    char A[1000];
    char B[1000];

    printf("Enter first string: ");
    scanf("%999s", A);

    printf("Enter second string: ");
    scanf("%999s", B);

    printEditOperations(A, B);

    return 0;
}