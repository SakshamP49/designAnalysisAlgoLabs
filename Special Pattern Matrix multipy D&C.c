#include <stdio.h>
#define MAX 64
void add(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}
void subtract(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n)
{    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}
void multiplySpecial(int A[MAX][MAX], int B[MAX][MAX],int C[MAX][MAX], int n)
{    if (n == 1)
    {      C[0][0] = A[0][0] * B[0][0];
        return;
    }
    int k = n / 2;
    int A11[MAX][MAX], A12[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX];
    int S1[MAX][MAX], S2[MAX][MAX];
    int P[MAX][MAX];
    int Q[MAX][MAX];
    int R[MAX][MAX];
    int temp1[MAX][MAX];
    int temp2[MAX][MAX];
    // Extract the unique blocks
    for (int i = 0; i < k; i++)
    {       for (int j = 0; j < k; j++)
        {       A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
        }
    }
    /*       P = A11 * B11
        Q = A12 * B12
        R = (A11 + A12)(B11 + B12)   */
    multiplySpecial(A11, B11, P, k);
    multiplySpecial(A12, B12, Q, k);
    add(A11, A12, S1, k);
    add(B11, B12, S2, k);
    multiplySpecial(S1, S2, R, k);
    // Calculate:
    // X = P + Q
    // Y = R - P - Q
    add(P, Q, temp1, k);
    subtract(R, temp1, temp2, k);
    // Construct result
    for (int i = 0; i < k; i++)
    {        for (int j = 0; j < k; j++)
        {          C[i][j] = temp1[i][j];
            C[i][j + k] = temp2[i][j];
            C[i + k][j] = temp2[i][j];
            C[i + k][j + k] = temp1[i][j];
        }
    }
}
int main()
{    int n;
    printf("Enter n (power of 2): ");
    scanf("%d", &n);
    int A[MAX][MAX];
    int B[MAX][MAX];
    int C[MAX][MAX];
    printf("Enter Matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    printf("Enter Matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);
    multiplySpecial(A, B, C, n);
    printf("\nResult Matrix:\n");
    for (int i = 0; i < n; i++)
    {       for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }
    return 0;
}// O(n square)