#include <stdio.h>
/* Aim: Given coins with exactly one lighter coin, locate it using : a divide-and-conquer approach & a balance scale.*/
int findDefective(int coins[], int left, int right, int good)
{
    if (left == right)
    { // only one candidate remains; compare it (let left) with the known-good reference coin.
        if (coins[left] < coins[good])
            return left;

        return -1;
    }

    if (right - left == 1)
    { //only two candidates remain, so check both.
        if (coins[left] < coins[good])
            return left;

        if (coins[right] < coins[good])
            return right;

        return -1;
    }

    int n = right - left + 1;

    int size = n / 3; // creates two equal-sized groups for the first two weighing operations.

    int l1 = left;
    int r1 = left + size - 1;

    int l2 = r1 + 1;
    int r2 = l2 + size - 1;

    int l3 = r2 + 1;
    int r3 = right;

    int weight1 = 0;
    int weight2 = 0;// simulate the weights on the two sides of the balance.

    for (int i = l1; i <= r1; i++)
        weight1 += coins[i];

    for (int i = l2; i <= r2; i++)
        weight2 += coins[i];

    if (weight1 < weight2) //the first group contains the lighter coin.
    {
        return findDefective(coins, l1, r1, good);
    }
    else if (weight2 < weight1)
    {
        return findDefective(coins, l2, r2, good);
    }
    else
    { // assuming exactly one defective coin, it must be in the unweighed third group.
        return findDefective(coins, l3, r3, good);
    }
}

int main()
{
    int n;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter coin weights:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    /*
       We use coin 0 as a reference good coin.
       For this simple implementation, assume coin 0 is good
       when searching other groups.
    */

    int good = 0;

    int answer = findDefective(coins, 1, n - 1, good);

    if (answer == -1)
        printf("No defective coin found.\n");
    else
        printf("Defective coin is at position %d\n", answer + 1);

    return 0;
}