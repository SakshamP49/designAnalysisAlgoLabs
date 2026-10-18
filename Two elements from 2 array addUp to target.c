#include <stdio.h>
// You are given two sets of numbers, S1 and S2, each containing n numbers, and a target number x. You must determine whether one number from S1 and one number from S2 add up to x.
#include <stdlib.h>
int compare(const void *a, const void *b) { // This function tells qsort() how to arrange numbers. const void *: This is a pointer to an element being compared. void * means a generic pointer: it can point to different types of data. Here, it points to an integer because we are sorting integers.
    return (*(int *)a - *(int *)b); // The function returns a negative value if the first number is smaller, a positive value if the first number is larger, and zero if they are equal. This tells qsort() how to order the numbers.If the result is negative, the first number should come before the second. If the result is positive, the first number should come after the second. If the result is zero, they are equal.
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
int main() {
    int n, x;
    printf("Enter n: ");
    scanf("%d", &n);
    int S1[n], S2[n];
    printf("Enter S1:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S1[i]);
    printf("Enter S2:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S2[i]);
    printf("Enter x: ");
    scanf("%d", &x);
    qsort(S1, n, sizeof(int), compare);
    qsort(S2, n, sizeof(int), compare);
    for (int i = 0; i < n; i++) {
        int required = x - S1[i];
        if (binarySearch(S2, n, required)) {
            printf("YES\n");
            printf("Pair: %d + %d = %d\n",
                   S1[i], required, x);
            return 0;
        }
    }
    printf("NO\n");
    return 0;
}// 3. Why is the time complexity \(O(n\log n)\)?
/* Operation   	                                                  Time
    Sort S1	                                                    O(n log n)
    Sort S2                                                     O (nlog n))
Check each number in S1 using binary search in S2	             O(nlog n)
The total is O(n log n)
The key lesson: For each number in S1, subtract it from the target to find the required partner. Then use binary search to look for that partner in S2. */