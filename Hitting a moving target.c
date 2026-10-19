
#include <stdio.h>

void printStrategy(int n)
{ // function to print the guaranteed shooting sequence for hitting a moving target with n hiding spots. The function takes an integer parameter n, which represents the number of hiding spots. It first checks if n is equal to 2, in which case it prints "1 1" as the guaranteed shooting sequence. For n greater than 2, it performs a forward sweep by printing numbers from 2 to n-1, followed by a reverse sweep by printing numbers from n-1 back down to 2. This sequence ensures that all hiding spots are covered in a way that guarantees hitting the moving target.
    if (n == 2)
    {
        printf("1 1\n");
        return;
    }

    // Forward sweep
    for (int i = 2; i <= n - 1; i++)
        printf("%d ", i);
// The forward sweep loop iterates from 2 to n-1, printing each number in this range. This represents the first part of the guaranteed shooting sequence, where the shooter targets each hiding spot in ascending order, starting from the second hiding spot up to the second-to-last hiding spot. The numbers are printed with a space in between to separate them visually.
    // Reverse sweep
    for (int i = n - 1; i >= 2; i--)
        printf("%d ", i);

    printf("\n");
}

int main()
{
    int n;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1)
    {
        printf("n must be greater than 1.\n");
        return 0;
    }

    printf("\nGuaranteed shooting sequence:\n");

    printStrategy(n);

    if (n == 2)
        printf("Number of shots = 2\n");
    else
        printf("Number of shots = %d\n",
               2 * (n - 2));

    return 0;
}