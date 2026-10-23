#include <stdio.h>

// Helper function to sum weights in a specific range
int sum_weights(int weights[], int start, int end) {
    int sum = 0;
    for (int i = start; i <= end; i++) 
        sum += weights[i];
    return sum;
}

// Recursive function to find the index of the lighter (defective) coin
int find_lighter_coin(int weights[], int start, int end) {
    // Base Case: Only one coin left
    if (start == end) 
        return start;

    int num_coins = end - start + 1; 
    // Divide into 3 groups accurately using integer division
    int group_size = num_coins / 3;
    // Define standard ranges for Group 1 and Group 2
    int left_start = start;
    int left_end = start + group_size - 1; 
    int right_start = left_end + 1;
    int right_end = right_start + group_size - 1; 
    // Group 3 automatically takes any remainder coins
    int third_start = right_end + 1;
    int third_end = end;
    // If total coins are not perfectly divisible by 3 (e.g., 2 coins left)
    // and group_size becomes 0, we must weigh 1 vs 1 directly.
    if (group_size == 0)
     {  left_end = start;
        right_start = start + 1;
        right_end = start + 1;
        third_start = start + 2; // out of bounds, but won't be called
     }

    // Weigh Group 1 (Left) against Group 2 (Right)
    int left_weight = sum_weights(weights, left_start, left_end);
    int right_weight = sum_weights(weights, right_start, right_end);

    if (left_weight < right_weight) 
        return find_lighter_coin(weights, left_start, left_end);
    else if (right_weight < left_weight)
        return find_lighter_coin(weights, right_start, right_end);
    else 
        return find_lighter_coin(weights, third_start, third_end);
}

int main() {
    int n; 
    
    printf("Enter total number of coins: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    int individuals[n];
    printf("Enter all weights, ensuring one is lighter than the rest and others are equal:\n");
    for(int i = 0; i < n; i++) {
        if (scanf("%d", &individuals[i]) != 1) return 1;
    }

    printf("Searching through %d coins...\n", n);
    int defective_index = find_lighter_coin(individuals, 0, n - 1);

    printf("The defective (lighter) coin is at index: %d\n", defective_index);
    printf("Weight of the defective coin: %d\n", individuals[defective_index]);

    return 0;
}
