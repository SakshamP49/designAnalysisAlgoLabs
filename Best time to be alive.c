#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int year;
    int type;
} Event;

int compareEvents(const void *a, const void *b)
{ // comparison function for sorting events based on year and type. It takes two pointers to Event structures (a and b) as parameters. The function first casts the void pointers to Event pointers (e1 and e2). It then compares the years of the two events. If the years are different, it returns the difference between the years, ensuring that earlier years come first in the sorted order. If the years are the same, it compares the types of the events, returning the difference between the types. This ensures that death events (-1) come before birth events (+1) when they occur in the same year, allowing for correct counting of overlapping lifespans.
    Event *e1 = (Event *)a; // Cast the void pointer 'a' to an Event pointer 'e1'
    Event *e2 = (Event *)b;

    // Earlier year comes first
    if (e1->year != e2->year)
        return e1->year - e2->year; // Compare the years of the two events. If they are different, return the difference between the years. This ensures that events with earlier years come first in the sorted order.

    // Death (-1) must come before birth (+1)
    return e1->type - e2->type;
}

int main()
{
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    Event events[2 * n];

    for (int i = 0; i < n; i++)
    {
        int birth, death;

        printf("Enter birth and death year of scientist %d: ",
               i + 1);

        scanf("%d %d", &birth, &death);

        events[2 * i].year = birth; // Store the birth year of the scientist in the events array at index 2*i. Each scientist contributes two events: a birth event and a death event. The birth event is represented by a positive type (+1) to indicate that a scientist is born in that year.
        events[2 * i].type = 1;

        events[2 * i + 1].year = death;
        events[2 * i + 1].type = -1; // Store the death year of the scientist in the events array at index 2*i + 1. The death event is represented by a negative type (-1) to indicate that a scientist dies in that year. This allows for proper counting of overlapping lifespans when processing the events later.
    }

    qsort(events, 2 * n, sizeof(Event), compareEvents); // Sort the events array using the qsort function from the standard library. The array contains 2*n events (birth and death for each scientist). The size of each event is specified as sizeof(Event), and the comparison function compareEvents is provided to determine the order of events based on year and type. This sorting ensures that events are processed in chronological order, with death events coming before birth events in the same year, allowing for accurate counting of overlapping lifespans.

    int alive = 0;
    int maximum = 0;
    int bestYear = 0;

    for (int i = 0; i < 2 * n; i++)
    { // Iterate through the sorted events array to count the number of scientists alive in each year. The loop runs from 0 to 2*n - 1, processing each event in chronological order. For each event, it checks the type of the event (birth or death) and updates the count of alive scientists accordingly. If a birth event is encountered (type +1), the alive count is incremented. If a death event is encountered (type -1), the alive count is decremented. After updating the alive count, it checks if the current number of alive scientists exceeds the maximum recorded so far. If it does, it updates the maximum and records the corresponding year as bestYear. This process allows for determining the year with the highest number of overlapping lifespans among the scientists.
        if (events[i].type == -1)
        {
            alive--;
        }
        else
        {
            alive++;

            if (alive > maximum)
            {
                maximum = alive;
                bestYear = events[i].year;
            }
        }
    }

    printf("\nMaximum number of scientists alive = %d\n",
           maximum);

    printf("The maximum overlap starts in year %d.\n",
           bestYear);

    return 0;
}