#include <stdio.h>
// in short, this program implements the Fractional Knapsack problem with deterioration. It allows the user to input the number of items, their values, weights, and decay rates (lambda), as well as the knapsack capacity. The program then calculates the maximum value that can be obtained by selecting fractions of items based on their effective density, which takes into account both their value-to-weight ratio and their decay rate over time. The selected items and their fractions are printed along with the maximum obtained value.
typedef struct
{
    int id;
    double value;
    double weight;
    double lambda;
    double fraction;
    double density;
} Item;

int main()
{
    int n;
    double W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item items[n];

    for (int i = 0; i < n; i++)
    { // Loop through each item to input its value, weight, and decay rate (lambda). The loop iterates from 0 to n-1, where n is the total number of items. For each iteration, it assigns a unique ID to the item (i + 1), initializes the fraction of the item taken to 0.0, and prompts the user to enter the value, weight, and decay rate for that specific item. The input values are read using scanf and stored in the corresponding fields of the items array.
        items[i].id = i + 1; // Assign a unique ID to the item, starting from 1 for the first item and incrementing by 1 for each subsequent item.
        items[i].fraction = 0.0;

        printf("Enter value, weight and decay rate for item %d: ", i + 1);

        scanf("%lf %lf %lf",
              &items[i].value,
              &items[i].weight,
              &items[i].lambda);
    }

    printf("Enter knapsack capacity: ");
    scanf("%lf", &W);

    double remaining = W;
    double totalValue = 0.0;
    int time = 0;

    printf("\nSelected items:\n");

    while (remaining > 0)
    { // While there is still remaining capacity in the knapsack, the loop continues to select items based on their effective density. The loop iterates until the remaining capacity is greater than 0. In each iteration, it finds the item with the highest effective density that has not been fully taken (fraction < 1.0). The effective density is calculated as the value-to-weight ratio of the item minus its decay rate multiplied by the current time. If no suitable item is found or if the best effective density is less than or equal to 0, the loop breaks, indicating that no more items can be added to the knapsack. Otherwise, it calculates how much of the selected item can be taken (up to its weight or the remaining capacity), updates its fraction and density, adds its contribution to the total value, and decreases the remaining capacity accordingly. The selected item's details are printed for each time step.
        int best = -1;
        double bestDensity = -1e100;

        for (int i = 0; i < n; i++)
        { // Iterate through each item to find the one with the highest effective density that has not been fully taken. The loop iterates from 0 to n-1, where n is the total number of items. For each item, it checks if the fraction of the item taken is less than 1.0 (indicating that there is still some portion of the item available). If the item is fully taken (fraction == 1.0), it skips to the next item. Otherwise, it calculates the current effective density of the item by taking its value-to-weight ratio and subtracting its decay rate multiplied by the current time. If this effective density is greater than the best density found so far, it updates bestDensity and records the index of the best item found.
            if (items[i].fraction == 1.0)
                continue;

            double currentDensity = (items[i].value / items[i].weight) - items[i].lambda * time;
            if (currentDensity > bestDensity)
            { // If the current effective density of the item is greater than the best density found so far, update bestDensity and record the index of the best item found. This ensures that at the end of the loop, bestDensity holds the highest effective density among all available items, and best holds the index of that item in the items array.
                bestDensity = currentDensity;
                best = i;
            }
        }
        if (best == -1 || bestDensity <= 0) // If no suitable item is found or if the best effective density is less than or equal to 0, break the loop, indicating that no more items can be added to the knapsack. This condition checks if best is still -1 (meaning no item was selected) or if the best effective density is non-positive, which implies that adding any more items would not contribute positively to the total value. In either case, the loop terminates, and the program proceeds to print the final results.
            break;
        double take = items[best].weight;
        if (take > remaining)
            take = remaining;
        items[best].fraction = take / items[best].weight;
        items[best].density = bestDensity;
        totalValue += take * bestDensity;
        remaining -= take;
        printf("Time %d: Item %d, fraction = %.4f, " "effective density = %.4f\n", time, items[best].id, items[best].fraction,bestDensity);
        time++;
    }
    printf("\nMaximum obtained value = %.4lf\n", totalValue);
    return 0;
}