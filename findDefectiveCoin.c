#include <stdio.h>

// Helper function to sum weights in a specific range
int sum_weights(int weights[], int start, int end) {
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += weights[i];
    }
    return sum;
}

// Recursive function to find the index of the lighter (defective) coin
int find_lighter_coin(int weights[], int start, int end) {
    // Base Case: Only one coin left in the range
    if (start == end) {
        return start;
    }

    int num_coins = end - start + 1;
    
    // Divide the coins into 3 groups
    int group_size = num_coins / 3;
    if (num_coins % 3 != 0) {
        group_size += 1; // Handle remainders by skewing size slightly
    }

    // Define indices for the three groups
    int left_start = start;
    int left_end = start + group_size - 1;
    
    int right_start = left_end + 1;
    int right_end = right_start + group_size - 1;
    
    // Ensure the right group doesn't overshoot the boundary
    if (right_end > end) {
        right_end = end;
    }
    
    // The leftover coins belong to the third group
    int third_start = right_end + 1;
    int third_end = end;

    // Adjust groups if left and right don't have equal sizes to weigh fairly
    int actual_left_size = left_end - left_start + 1;
    int actual_right_size = right_end - right_start + 1;
    
    if (actual_left_size > actual_right_size) {
        // Move one element from Left to Third Group to keep Left == Right
        left_end--;
        third_start--;
    }

    // Weigh Group 1 (Left) against Group 2 (Right)
    int left_weight = sum_weights(weights, left_start, left_end);
    int right_weight = sum_weights(weights, right_start, right_end);

    if (left_weight < right_weight) {
        // The defective coin is in the Left group
        return find_lighter_coin(weights, left_start, left_end);
    } 
    else if (right_weight < left_weight) {
        // The defective coin is in the Right group
        return find_lighter_coin(weights, right_start, right_end);
    } 
    else {
        // Both sides balance: The defective coin is in the Third (unweighed) group
        return find_lighter_coin(weights, third_start, third_end);
    }
}

int main() {
    // Example: 9 coins where the coin at index 5 is lighter (defective)
    // Normal weight = 10, Defective weight = 9
    int weights[] = {10, 10, 10, 10, 10, 9, 10, 10, 10};
    int n = sizeof(weights) / sizeof(weights[0]);

    printf("Searching through %d coins...\n", n);
    int defective_index = find_lighter_coin(weights, 0, n - 1);

    printf("The defective (lighter) coin is at index: %d\n", defective_index);
    printf("Weight of the defective coin: %d\n", weights[defective_index]);

    return 0;
    
}
// int n;

//     printf("Enter number of coins: ");
//     scanf("%d", &n);

//     int coins[n];

//     printf("Enter coin weights:\n");

//     for (int i = 0; i < n; i++)
//         scanf("%d", &coins[i]);

//     /*
//        We use coin 0 as a reference good coin.
//        For this simple implementation, assume coin 0 is good
//        when searching other groups.
//     */

//     int good = 0;

//     int answer = findDefective(coins, 1, n - 1, good);

//     if (answer == -1)
//         printf("No defective coin found.\n");
//     else
//         printf("Defective coin is at position %d\n", answer + 1);

//     return 0;
// }
