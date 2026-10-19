#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printLCS(char X[], char Y[])
{ // function to find and print the longest common subsequence (LCS) of two sequences X and Y. It takes two character arrays (strings) X and Y as input. The function first calculates the lengths of the two sequences (m and n). It then allocates a 2D array dp to store the lengths of LCS for different substrings of X and Y. The dp array is filled using dynamic programming, where dp[i][j] represents the length of LCS of X[0..i-1] and Y[0..j-1]. After filling the dp array, the function backtracks through it to construct the LCS string. Finally, it prints the length of the LCS and the LCS itself.
    int m = strlen(X);
    int n = strlen(Y);

    int *dp = malloc((m + 1) * (n + 1) * sizeof(int));

    if (dp == NULL)
        return;

    #define DP(i, j) dp[(i) * (n + 1) + (j)] // Macro to access the 2D dp array as a 1D array

    for (int i = 0; i <= m; i++)
        DP(i, 0) = 0;

    for (int j = 0; j <= n; j++)
        DP(0, j) = 0;

    for (int i = 1; i <= m; i++)
    { // Fill the dp array using dynamic programming to calculate the lengths of LCS for different substrings of X and Y. The outer loop iterates through each character of sequence X (from 1 to m), and the inner loop iterates through each character of sequence Y (from 1 to n). For each pair of characters (X[i-1] and Y[j-1]), the function checks if they are equal. If they are equal, it means that the current characters contribute to the LCS, and the length is incremented by 1 from the previous diagonal value (DP(i-1, j-1)). If they are not equal, the function takes the maximum value from either the left cell (DP(i, j-1)) or the top cell (DP(i-1, j)), which represents the longest LCS found so far without including the current characters. This process continues until the entire dp array is filled, resulting in DP(m, n) containing the length of the longest common subsequence of X and Y.
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                DP(i, j) = DP(i - 1, j - 1) + 1;
            }
            else
            { // If the current characters of X and Y are not equal, the function takes the maximum value from either the left cell (DP(i, j-1)) or the top cell (DP(i-1, j)), which represents the longest LCS found so far without including the current characters. This ensures that the dp array is filled correctly to reflect the lengths of LCS for different substrings of X and Y.
                if (DP(i - 1, j) > DP(i, j - 1))
                    DP(i, j) = DP(i - 1, j);
                else
                    DP(i, j) = DP(i, j - 1);
            }
        }
    }

    int lcsLength = DP(m, n);

    char *lcs = malloc((lcsLength + 1) * sizeof(char));

    if (lcs == NULL)
    {
        free(dp);
        return;
    }

    lcs[lcsLength] = '\0';

    int i = m;
    int j = n;
    int index = lcsLength - 1;

    while (i > 0 && j > 0)
    { // Backtrack through the dp array to construct the LCS string. Starting from the bottom-right corner of the dp array (DP(m, n)), the function checks if the characters X[i-1] and Y[j-1] are equal. If they are equal, it means that the current characters contribute to the LCS, and they are added to the lcs string at the current index. The indices i, j, and index are then decremented to move diagonally up-left in the dp array. If the characters are not equal, the function checks whether to move left (decrement j) or up (decrement i) based on which cell has a greater value in the dp array. This process continues until either i or j reaches 0, indicating that one of the sequences has been fully traversed. The resulting lcs string contains the longest common subsequence of X and Y.
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index] = X[i - 1];
            index--;
            i--;
            j--;
        }
        else if (DP(i - 1, j) >= DP(i, j - 1))
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("LCS length = %d\n", lcsLength);
    printf("LCS = %s\n", lcs);

    free(lcs);
    free(dp);
}

int main()
{
    char X[1000];
    char Y[1000];

    printf("Enter first sequence: ");
    scanf("%999s", X);

    printf("Enter second sequence: ");
    scanf("%999s", Y); // Read the first and second sequences from the user input. The scanf function is used to read strings into the character arrays X and Y, with a maximum length of 999 characters to prevent buffer overflow. The user is prompted to enter the first sequence, which is stored in X, and then prompted to enter the second sequence, which is stored in Y. These sequences will be used as input for the printLCS function to find and print their longest common subsequence. the "%999s" format specifier ensures that at most 999 characters are read, leaving space for the null terminator at the end of the string.

    printLCS(X, Y);

    return 0;
}