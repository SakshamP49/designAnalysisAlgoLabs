#include <stdio.h>

void reverse(int arr[], int i, int j) {
    while (i < j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++; j--;
    }
}

// Swap adjacent blocks A (size m) and B (size n) starting at index 'start'
void blockSwap(int arr[], int start, int m, int n) {
    reverse(arr, start, start + m - 1);
    reverse(arr, start + m, start + m + n - 1);
    reverse(arr, start, start + m + n - 1); // The blockSwap() function swaps two adjacent blocks of an array in place using the reversal algorithm. It takes the array arr[], the starting index of the first block, and the sizes of the two blocks (m and n) as parameters. The function first reverses the first block (A), then reverses the second block (B), and finally reverses the entire combined block (A followed by B). This sequence of reversals effectively swaps the two blocks without requiring additional memory for a temporary array.
}

// Binary search to find lower bound for partitioning
int binarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

// In-place merge using reversal-based block swaps
void merge(int arr[], int left, int mid, int right) {
    if (left > mid || mid >= right) return;
    
    int L_len = mid - left + 1;
    int m_L_idx = left + L_len / 2;
    int m_L_val = arr[m_L_idx]; // The merge() function merges two sorted subarrays of arr[] in place using a reversal-based block swap technique. It takes the array arr[], the left index, the mid index, and the right index as parameters. The function first checks if the left subarray is empty or if the mid index is not less than the right index, in which case it returns without performing any operations. It then calculates the length of the left subarray (L_len) and finds the middle index (m_L_idx) and value (m_L_val) of the left subarray. The function uses binary search to find the appropriate split point in the right subarray for partitioning. It calculates the lengths of the two blocks to be swapped (L2_len and R1_len) and performs a block swap if both lengths are greater than zero. Finally, it recursively calls merge() on the two resulting subarrays to complete the merge process.
    
    int R_split = binarySearch(arr, mid + 1, right, m_L_val);
    
    int L2_len = mid - m_L_idx + 1;
    int R1_len = R_split - (mid + 1);
    
    if (L2_len > 0 && R1_len > 0) {
        blockSwap(arr, m_L_idx, L2_len, R1_len);
    }
    
    int new_mid = m_L_idx + R1_len;
    merge(arr, left, m_L_idx - 1, new_mid - 1);
    merge(arr, new_mid + 1, mid + R1_len, right);
}

// Merge Sort main function
void sortViaReversal(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        sortViaReversal(arr, left, mid);
        sortViaReversal(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() { 
    int p[] = {1, 4, 3, 2, 5};
    int n = sizeof(p)/sizeof(p[0]);
    
    sortViaReversal(p, 0, n - 1);
    
    printf("Sorted permutation: ");
    for(int i = 0; i < n; i++) printf("%d ", p[i]);
    
    return 0;
}