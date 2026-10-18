#include <stdio.h>
#include <stdlib.h>
struct Interval {
    int start;
    int end;
};
int compare(const void *a, const void *b) {
    struct Interval *i1 = (struct Interval *)a;
    struct Interval *i2 = (struct Interval *)b; // The compare() function is used by qsort() to determine the order of elements. It takes two generic pointers (const void *a and const void *b) as input, which point to the elements being compared. Inside the function, these pointers are cast to struct Interval pointers (struct Interval *i1 and struct Interval *i2) so that we can access the start field of each interval. The function then returns the difference between the start values of the two intervals, which determines their order in the sorted array.

    return i1->start - i2->start; // The function returns a negative value if the first interval starts earlier, a positive value if the first interval starts later, and zero if they start at the same time. This tells qsort() how to order the intervals. If the result is negative, the first interval should come before the second. If the result is positive, the first interval should come after the second. If the result is zero, they are equal.
}
int main() {
    int n;
    printf("Enter number of intervals: ");
    scanf("%d", &n);
    struct Interval arr[n]; // Each interval has a start and an end time. The array arr[] is used to store all the intervals entered by the user.
    printf("Enter intervals:\n");
    for (int i = 0; i < n; i++)
        scanf("%d %d", &arr[i].start, &arr[i].end);
    qsort(arr, n, sizeof(struct Interval), compare); // The qsort() function is used to sort the arr[] array based on the start time of each interval. The compare() function is passed as a parameter to qsort() to determine the order of the intervals. After sorting, the arr[] array will be in ascending order of start times, allowing us to easily merge overlapping intervals by iterating through the sorted array and checking for overlaps.
    printf("Merged intervals:\n");
    int currentStart = arr[0].start;
    int currentEnd = arr[0].end;
    for (int i = 1; i < n; i++) {
// The loop iterates through the sorted intervals starting from the second interval (index 1). For each interval, it checks whether it overlaps with the current merged interval (defined by currentStart and currentEnd). If there is an overlap, it updates currentEnd to the maximum end time of the overlapping intervals. If there is no overlap, it prints the current merged interval and updates currentStart and currentEnd to the start and end of the new interval. This process continues until all intervals have been processed, resulting in a list of merged intervals that do not overlap.
        if (arr[i].start <= currentEnd) {
            // Intervals overlap
            if (arr[i].end > currentEnd)
                currentEnd = arr[i].end;
        }
        else {
            // No overlap
            printf("(%d, %d) ",currentStart, currentEnd);
            currentStart = arr[i].start;
            currentEnd = arr[i].end;
        }
    }
    // Print the last interval
    printf("(%d, %d)\n",
           currentStart, currentEnd);
    return 0;
}