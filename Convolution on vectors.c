// Aim of this code is to perform convolution of two vectors using Fast Fourier Transform (FFT) in C. The code defines functions for FFT and convolution, and demonstrates their usage in the main function.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#define PI 3.14159265358979323846
void fft(double complex *a, int n, int invert) { // The fft() function computes the Fast Fourier Transform (FFT) of a complex array a of size n. It takes an additional parameter invert, which indicates whether to perform the forward FFT (invert = 0) or the inverse FFT (invert = 1). The function recursively divides the input array into even and odd indexed elements, computes their FFTs, and combines the results using the Cooley-Tukey algorithm. If invert is set, it normalizes the output by dividing each element by n to obtain the correct inverse transform.
    if (n == 1) return;
    double complex a0[n/2], a1[n/2];
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, n/2, invert); 
    fft(a1, n/2, invert);// The function recursively calls itself on the even-indexed elements (a0) and odd-indexed elements (a1) of the input array. This divides the problem into smaller subproblems, allowing for efficient computation of the FFT. The recursion continues until the base case of n == 1 is reached, at which point the function returns without further processing.
    
    double angle = 2 * PI / n * (invert ? -1 : 1); // The angle variable is calculated based on the size of the input array n and whether the FFT is being performed in the forward or inverse direction. For the forward FFT, the angle is positive, while for the inverse FFT, it is negative. This angle is used to compute the complex roots of unity, which are essential for combining the results of the even and odd indexed FFTs.
    double complex w = 1, wn = cexp(I * angle); // The variable w is initialized to 1, representing the current complex root of unity. The variable wn is calculated as the complex exponential of the angle, which represents the primitive n-th root of unity. This value is used to iteratively compute the necessary roots of unity for combining the FFT results.
    
    for (int i = 0; 2 * i < n; i++) { // The loop iterates over the first half of the input array, combining the results of the even and odd indexed FFTs. For each index i, it computes the corresponding values in the output array by adding and subtracting the contributions from a0 and a1, scaled by the current root of unity w. If invert is set, it normalizes the output by dividing each element by n to obtain the correct inverse transform.
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

void convolve(double *A, int m, double *B, int n, double *C) { // The convolve() function computes the convolution of two real-valued arrays A and B of sizes m and n, respectively, and stores the result in the array C. It first determines the size of the output array, which is m + n - 1, and finds the next power of two greater than or equal to this size for efficient FFT computation. It then allocates complex arrays cA and cB, copies the input arrays into them, and performs FFT on both arrays. After multiplying the transformed arrays element-wise, it performs an inverse FFT on the result and extracts the real part to obtain the final convolution result in C.
    int size = 1;
    while (size < n + m - 1) size *= 2;
    
    double complex *cA = calloc(size, sizeof(double complex));
    double complex *cB = calloc(size, sizeof(double complex));
    
    for (int i = 0; i < m; i++) cA[i] = A[i];
    for (int i = 0; i < n; i++) cB[i] = B[i];
    
    fft(cA, size, 0);
    fft(cB, size, 0);
    
    for (int i = 0; i < size; i++) cA[i] *= cB[i];
    // Perform inverse FFT to get the convolution result
    fft(cA, size, 1);
    
    for (int i = 0; i < n + m - 1; i++) C[i] = creal(cA[i]);
    
    free(cA);
    free(cB);
}

int main() {
    double A[] = {1, 2, 3}; // Size m=3
    double B[] = {4, 5, 6, 7}; // Size n=4
    int m = 3, n = 4;
    double C[6] = {0}; // m+n-1 = 6
    
    convolve(A, m, B, n, C);
    
    printf("Convolution result: ");
    for(int i=0; i<m+n-1; i++) printf("%.2f ", C[i]);
    return 0;
}