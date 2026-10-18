#include <stdio.h>
#include <stdlib.h>

struct Event {
    int time;
    int type;   // +1 = entry, -1 = exit
};

int compare(const void *a, const void *b) {
    struct Event *e1 = (struct Event *)a; // The function compare() is used by qsort() to determine the order of elements. It takes two generic pointers (const void *a and const void *b) as input, which point to the elements being compared. Inside the function, these pointers are cast to struct Event pointers (struct Event *e1 and struct Event *e2) so that we can access the time field of each event. The function then returns the difference between the time values of the two events, which determines their order in the sorted array.
    struct Event *e2 = (struct Event *)b;

    return e1->time - e2->time;
}

int main() {
    int n;

    printf("Enter number of people: ");
    scanf("%d", &n);

    struct Event events[2 * n];

    printf("Enter entry and exit times:\n");

    for (int i = 0; i < n; i++) {
        int a, b;

        scanf("%d %d", &a, &b);

        events[2 * i].time = a; // Each person contributes two events: one for entry and one for exit. The entry event is represented by a positive type (+1), while the exit event is represented by a negative type (-1). This allows us to keep track of the number of people present at any given time by simply summing the types of events that have occurred up to that point.
        events[2 * i].type = 1;

        events[2 * i + 1].time = b;
        events[2 * i + 1].type = -1;// The exit event is represented by a negative type (-1) to indicate that a person has left the party. This allows us to keep track of the number of people present at any given time by simply summing the types of events that have occurred up to that point.
    }

    qsort(events, 2 * n, sizeof(struct Event), compare); // The qsort() function is used to sort the events array based on the time of each event. The compare() function is passed as a parameter to qsort() to determine the order of the events. After sorting, the events array will be in chronological order, allowing us to easily track the number of people present at any given time by iterating through the sorted events and updating a counter based on the type of each event (entry or exit).

    int current = 0;
    int maximum = 0;
    int maxTime = 0;

    for (int i = 0; i < 2 * n; i++) {
        current += events[i].type; // The current variable keeps track of the number of people present at the party at any given time. It is updated by adding the type of each event (entry or exit) as we iterate through the sorted events array. When an entry event occurs, current is incremented by 1, and when an exit event occurs, current is decremented by 1. This allows us to maintain an accurate count of the number of people present at the party as we process each event in chronological order.

        if (current > maximum) {
            maximum = current;
            maxTime = events[i].time;
        }
    }

    printf("Maximum number of people = %d\n", maximum);
    printf("Time = %d\n", maxTime);

    return 0;
}