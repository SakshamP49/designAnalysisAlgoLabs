#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void swap(int *a, int *b)
{   int t = *a;
    *a = *b;
    *b = t;
}
// Helper for sorting (used in Mode, Median, Remove Duplicates)
int compare(const void *a, const void *b)
 { return (*(int *)a - *(int *)b); }
// (i) Max
int findMax(int arr[], int n)
{  int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}
// (ii) First and Second Max
void findFirstSecondMax(int arr[], int n, int *max1, int *max2)
{
    *max1 = *max2 = -2147483648;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > *max1)
        {
            *max2 = *max1;
            *max1 = arr[i];
        }
        else if (arr[i] > *max2 && arr[i] != *max1)
        { // This condition checks if the current element is greater than the second maximum and not equal to the first maximum. If true, it updates the second maximum to the current element. This ensures that we correctly identify the second largest unique value in the array, even if there are duplicates of the maximum value.
            *max2 = arr[i];
        }
    }
}
// (iii) Mean
double findMean(int arr[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum / n;
}
// (iv) Median (using sort for simplicity)
double findMedian(int arr[], int n)
{
    qsort(arr, n, sizeof(int), compare);
    if (n % 2 != 0)
        return arr[n / 2];
    return (arr[(n - 1) / 2] + arr[n / 2]) / 2.0;
}
// (v) Standard Deviation
double findStdDev(int arr[], int n)
{
    double mean = findMean(arr, n);
    double varSum = 0;
    for (int i = 0; i < n; i++)
        varSum += pow(arr[i] - mean, 2);// The variance is calculated by summing the squared differences between each element and the mean. This sum is then divided by the number of elements to obtain the average squared deviation, which represents the variance. Finally, the standard deviation is obtained by taking the square root of the variance, providing a measure of how spread out the values in the array are around the mean.
    return sqrt(varSum / n);
}
// (vi) Mode
int findMode(int arr[], int n)
{
    qsort(arr, n, sizeof(int), compare);
    int max_count = 1, res = arr[0], curr_count = 1;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] == arr[i - 1])
            curr_count++;
        else
            curr_count = 1;
        if (curr_count > max_count)
        { // If the current count of a number exceeds the maximum count found so far, we update the maximum count and set the result to the current number. This ensures that we keep track of the most frequently occurring number in the array.
            max_count = curr_count;
            res = arr[i - 1];
        }
    }
    return res;
}

// (vii) Remove duplicates (returns new size)
int removeDuplicates(int arr[], int n)
{ // The removeDuplicates() function removes duplicate elements from a sorted array. It first sorts the array using qsort(), then iterates through the sorted array, comparing each element with the next one. If they are different, it copies the unique element to the front of the array. Finally, it returns the new size of the array containing only unique elements.
    qsort(arr, n, sizeof(int), compare);
    int j = 0;
    for (int i = 0; i < n - 1; i++)
        if (arr[i] != arr[i + 1])
            arr[j++] = arr[i];
    arr[j++] = arr[n - 1];
    return j;
}

// (viii) Reverse
void reverseArray(int arr[], int n)
{
    for (int i = 0; i < n / 2; i++) // The reverseArray() function reverses the elements of an array in place. It iterates from the start of the array to the midpoint, swapping each element with its corresponding element from the end of the array. This effectively reverses the order of the elements without requiring additional memory for a new array.
        swap(&arr[i], &arr[n - i - 1]);
}

// (ix) Partition ( < pivot after >= pivot )
void customPartition(int arr[], int n, int pivot)
{ // The customPartition() function rearranges the elements of an array such that all elements less than the specified pivot value are moved to the left side of the array, and all elements greater than or equal to the pivot are moved to the right side. It uses two pointers, i and j, to traverse the array from both ends. The function increments i until it finds an element greater than or equal to the pivot and decrements j until it finds an element less than the pivot. When both pointers find such elements, they are swapped, and the process continues until the pointers cross each other, ensuring that the partitioning is complete.
    int i = 0, j = n - 1;
    while (i <= j)
    {
        while (i < n && arr[i] >= pivot)
            i++;
        while (j >= 0 && arr[j] < pivot)
            j--;
        if (i < j)
        {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }
}

int main()
{
    int arr[] = {12, 3, 5, 7, 19, 3, 5, 21};
    int n = sizeof(arr) / sizeof(arr[0]);
    // Validate routines here by calling functions...
    return 0;
}