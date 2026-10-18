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
}