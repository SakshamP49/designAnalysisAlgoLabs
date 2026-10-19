#include <stdio.h>
#include <stdlib.h>

int isLegal(int state, int n, int pos)
{ // function to check if toggling the switch at position 'pos' is legal based on the current state of switches. It takes three parameters: state (an integer representing the current state of switches, where each bit corresponds to a switch), n (the total number of switches), and pos (the position of the switch to be toggled). The function checks if the rightmost switch can always be toggled, if the immediate right switch is ON, and if all switches further right are OFF. If all conditions are satisfied, it returns 1 (legal); otherwise, it returns 0 (illegal).
    // Rightmost switch can always be toggled
    if (pos == n - 1)
        return 1;

    // Immediate right switch must be ON
    if ((state & (1 << (pos + 1))) == 0)
        return 0;

    // Every switch further right must be OFF
    for (int j = pos + 2; j < n; j++)
    {
        if (state & (1 << j))
            return 0;
    }

    return 1;
}

void printState(int state, int n)
{ // function to print the current state of switches. It takes two parameters: state (an integer representing the current state of switches, where each bit corresponds to a switch) and n (the total number of switches). The function iterates through each switch position from 0 to n-1 and checks if the corresponding bit in the state is set (ON) or not set (OFF). It prints "1" for ON and "0" for OFF, followed by a space. After printing all switch states, it prints a newline character.
    printf("Current state: ");
    for (int i = 0; i < n; i++)
    {
        if (state & (1 << i))
            printf("1 ");
        else
            printf("0 ");
    }

    printf("\n");
}

int main()
{
    int n;

    printf("Enter number of switches (<= 20): ");
    scanf("%d", &n);

    int totalStates = 1 << n;
    int start = totalStates - 1;
    int goal = 0;

    int *distance = malloc(totalStates * sizeof(int)); // Allocate memory for the distance array, which will store the minimum number of moves required to reach each state from the starting state. The size of the array is equal to the total number of possible states (2^n), where n is the number of switches. Each index in the array corresponds to a specific state, and the value at that index represents the minimum number of moves needed to reach that state from the starting state. Initially, all values are set to -1 (unreachable) except for the starting state, which is set to 0 (no moves needed).
    int *parent = malloc(totalStates * sizeof(int)); // Allocate memory for the parent array, which will store the parent state for each state in the BFS traversal. The size of the array is equal to the total number of possible states (2^n), where n is the number of switches. Each index in the array corresponds to a specific state, and the value at that index represents the parent state from which it was reached during the BFS traversal. This information is used to reconstruct the path from the starting state to the goal state after the BFS is complete. Initially, all values are set to -1 (no parent) except for the starting state, which has no parent.
    int *moveUsed = malloc(totalStates * sizeof(int)); // Allocate memory for the moveUsed array, which will store the switch position that was toggled to reach each state in the BFS traversal. The size of the array is equal to the total number of possible states (2^n), where n is the number of switches. Each index in the array corresponds to a specific state, and the value at that index represents the switch position that was toggled to reach that state from its parent state during the BFS traversal. This information is used to reconstruct the sequence of moves from the starting state to the goal state after the BFS is complete. Initially, all values are set to -1 (no move) except for the starting state, which has no move.
    int *queue = malloc(totalStates * sizeof(int)); // Allocate memory for the queue array, which will be used to implement the BFS traversal. The size of the array is equal to the total number of possible states (2^n), where n is the number of switches. The queue will store the states to be explored during the BFS traversal, allowing us to systematically explore all reachable states from the starting state. The front and rear indices will be used to manage the queue operations (enqueue and dequeue) during the BFS process.

    for (int i = 0; i < totalStates; i++)
    { // Initialize the distance, parent, and moveUsed arrays for all possible states. The loop iterates through each state index from 0 to totalStates - 1 (where totalStates is 2^n, representing all possible combinations of switch states). For each state index i, the distance[i] is set to -1 (indicating that the state is initially unreachable), the parent[i] is set to -1 (indicating that there is no parent state yet), and the moveUsed[i] is set to -1 (indicating that no switch has been toggled to reach this state). This initialization ensures that all states are marked as unvisited before starting the BFS traversal.
        distance[i] = -1;
        parent[i] = -1;
        moveUsed[i] = -1;
    }

    int front = 0;
    int rear = 0;

    queue[rear++] = start; // Enqueue the starting state into the queue for BFS traversal. The rear index is incremented after adding the start state to the queue, indicating that there is now one state in the queue to be explored. This marks the beginning of the BFS process, where we will explore all reachable states from the starting configuration of switches.
    distance[start] = 0;

    while (front < rear)
    { // Perform BFS traversal to explore all reachable states from the starting state. The loop continues as long as there are states in the queue to be explored (i.e., front index is less than rear index). In each iteration, the current state is dequeued from the front of the queue, and if it matches the goal state, the loop breaks (indicating that we have found the minimum number of moves to reach the goal). For each switch position, the function checks if toggling that switch is legal based on the current state. If it is legal, a new state is generated by toggling the switch, and if that new state has not been visited yet (distance[nextState] == -1), it is enqueued into the queue for further exploration. The distance, parent, and moveUsed arrays are updated accordingly to keep track of the number of moves taken to reach each state, the parent state from which it was reached, and the switch position that was toggled to reach that state.
        int state = queue[front++];

        if (state == goal)
            break;

        for (int pos = 0; pos < n; pos++)
        {
            if (!isLegal(state, n, pos))
                continue;

            int nextState = state ^ (1 << pos);
// Generate the next state by toggling the switch at position 'pos' using the XOR operation. The expression (1 << pos) creates a bitmask with a 1 at the position corresponding to the switch being toggled, and XORing it with the current state flips the bit at that position, effectively toggling the switch. This new state represents the configuration of switches after performing the toggle operation.
            if (distance[nextState] == -1)
            {
                distance[nextState] =
                    distance[state] + 1;

                parent[nextState] = state;
                moveUsed[nextState] = pos;

                queue[rear++] = nextState;
            }
        }
    }

    printf("\nMinimum number of moves = %d\n",
           distance[goal]);

    printf("\nMinimum sequence:\n");

    int pathSize = distance[goal];
    int *path = malloc(pathSize * sizeof(int));

    int current = goal;

    for (int i = pathSize - 1; i >= 0; i--)
    {
        path[i] = moveUsed[current];
        current = parent[current];
    }

    current = start;

    printState(current, n);

    for (int i = 0; i < pathSize; i++)
    {
        printf("Toggle switch %d\n", path[i] + 1);
// Toggle the switch at position path[i] by flipping the corresponding bit in the current state using the XOR operation. The expression (1 << path[i]) creates a bitmask with a 1 at the position of the switch being toggled, and XORing it with the current state flips that bit, effectively toggling the switch. This updates the current state to reflect the new configuration of switches after performing the toggle operation.
        current ^= (1 << path[i]);

        printState(current, n);
    }

    free(distance);
    free(parent);
    free(moveUsed);
    free(queue);
    free(path);

    return 0;
}