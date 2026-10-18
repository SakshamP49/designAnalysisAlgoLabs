#include <stdio.h>
#define MAX 100
// When a matrix is split into four equal blocks, the code uses these names: A= A11, a12,... each block having k*k elements, k being n/2. A11 takes the top-left block. A12 takes the top-right block. A21 takes the bottom-left block. A22 takes the bottom-right block.Similarly we do the four blocks of matrix B.
void add(int A[MAX][MAX], int B[MAX][MAX],
         int C[MAX][MAX], int n)
{    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}
void subtract(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n)
{    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}
void strassen(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n)
{  if (n == 1) // When each matrix contains just one element, ordinary integer multiplication finishes the problem. The return prevents any further recursive calls.
    {        C[0][0] = A[0][0] * B[0][0]; return;
    }
   int k = n / 2;
    int A11[MAX][MAX], A12[MAX][MAX];
    int A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX];
    int B21[MAX][MAX], B22[MAX][MAX];
    int M1[MAX][MAX], M2[MAX][MAX], M3[MAX][MAX];
    int M4[MAX][MAX], M5[MAX][MAX], M6[MAX][MAX], M7[MAX][MAX];
    int T1[MAX][MAX], T2[MAX][MAX];
    // Divide matrices
    for (int i = 0; i < k; i++)
    {    for (int j = 0; j < k; j++)
        {       A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }
    // M1 = (A11 + A22)(B11 + B22)
    add(A11, A22, T1, k);
    add(B11, B22, T2, k);
    strassen(T1, T2, M1, k);
    // M2 = (A21 + A22)B11
    add(A21, A22, T1, k);
    strassen(T1, B11, M2, k);
    // M3 = A11(B12 - B22)
    subtract(B12, B22, T2, k);
    strassen(A11, T2, M3, k);
    // M4 = A22(B21 - B11)
    subtract(B21, B11, T2, k);
    strassen(A22, T2, M4, k);
    // M5 = (A11 + A12)B22
    add(A11, A12, T1, k);
    strassen(T1, B22, M5, k);
    // M6 = (A21 - A11)(B11 + B12)
    subtract(A21, A11, T1, k);
    add(B11, B12, T2, k);
    strassen(T1, T2, M6, k);
    // M7 = (A12 - A22)(B21 + B22)
    subtract(A12, A22, T1, k);
    add(B21, B22, T2, k);
    strassen(T1, T2, M7, k);
    // C11 = M1 + M4 - M5 + M7
    // The purpose of the additions and subtractions was to compute the required result using seven recursive multiplications rather than eight.
    for (int i = 0; i < k; i++)
    {       for (int j = 0; j < k; j++)
        {
            C[i][j] =M1[i][j] + M4[i][j]- M5[i][j] + M7[i][j];
            C[i][j + k] =M3[i][j] + M5[i][j];
            C[i + k][j] =M2[i][j] + M4[i][j];
            C[i + k][j + k] =M1[i][j] - M2[i][j]+ M3[i][j] + M6[i][j];
        }
    }
}
int main()
{   int n;
 printf("Enter matrix size (power of 2): ");
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
    strassen(A, B, C, n);
    printf("\nResult Matrix:\n");
    for (int i = 0; i < n; i++)
    {      for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }
    return 0;
}// Time:  O(n to power 2.8), compared with (O(n^3)) for conventional matrix multiplication.