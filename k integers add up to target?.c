#include <stdio.h>
#include <stdlib.h>
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
int binarySearch(int arr[], int n, int target) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target)
            return 1;
        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return 0;
}
int kSum(int arr[], int n, int k, int target, int start, long long sum) {

    // We have selected k-1 elements.
    // Find the last element using binary search.
    if (k == 1) { // k == 1 means that we only need one more element to complete the combination.
//The sum of the selected elements is already stored in sum. Therefore, the missing element must be:target-sum
        return binarySearch(arr + start, n - start, target - sum); // arr + start: This is a pointer to the first element of the subarray starting at index start. n - start: This is the size of the subarray. target - sum: This is the value we are searching for in the subarray.
    }
    for (int i = start; i < n; i++) {
        if (kSum(arr, n, k - 1, target, i + 1, sum + arr[i])) // We select arr[i] as one of the k elements. Then we recursively search for the remaining k-1 elements in the subarray starting from index i+1. The sum of the selected elements is updated to sum + arr[i].
            return 1;
        
    }
    return 0;
}
int main() {
    int n, k, T;
    printf("Enter n: ");
    scanf("%d", &n);
    int S[n];
    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S[i]);
    printf("Enter k: ");
    scanf("%d", &k);
    printf("Enter target T: ");
    scanf("%d", &T);
    qsort(S, n, sizeof(int), compare);
    if (kSum(S, n, k, T, 0, 0))
        printf("YES: k elements with sum %d exist.\n", T);
    else
        printf("NO: such k elements do not exist.\n");
    return 0;
}