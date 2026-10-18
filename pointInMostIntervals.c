#include <stdio.h>
#include <stdlib.h>

struct Event {
    int point;
    int type;   // +1 = start, -1 = end
};

int compare(const void *a, const void *b) { // This function is used by qsort() to determine the order of elements. It takes two generic pointers (const void *a and const void *b) as input, which point to the elements being compared. Inside the function, these pointers are cast to struct Event pointers (struct Event *e1 and struct Event *e2) so that we can access the point and type fields of each event. The function first compares the point values of the two events. If they are different, it returns the difference between the point values, which determines their order in the sorted array. If the point values are equal, it returns the difference between the type values, ensuring that start events (+1) come before end events (-1) when they occur at the same point.
    struct Event *e1 = (struct Event *)a;
    struct Event *e2 = (struct Event *)b;

    if (e1->point != e2->point)
        return e1->point - e2->point;

    // Start must come before end
    return e2->type - e1->type;
}

int main() {
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Event events[2 * n];

    printf("Enter intervals:\n");

    for (int i = 0; i < n; i++) {
        int l, r;

        scanf("%d %d", &l, &r);

        events[2 * i].point = l;
        events[2 * i].type = 1; // The start event is represented by a positive type (+1), while the end event is represented by a negative type (-1). This allows us to keep track of the number of intervals that overlap at any given point by simply summing the types of events that have occurred up to that point.

        events[2 * i + 1].point = r; // The end event is represented by a negative type (-1) to indicate that an interval has ended. This allows us to keep track of the number of intervals that overlap at any given point by simply summing the types of events that have occurred up to that point.
        events[2 * i + 1].type = -1;
    }

    qsort(events, 2 * n, sizeof(struct Event), compare); // The qsort() function is used to sort the events array based on the point of each event. The compare() function is passed as a parameter to qsort() to determine the order of the events. After sorting, the events array will be in ascending order of points, allowing us to easily track the number of intervals that overlap at any given point by iterating through the sorted events and updating a counter based on the type of each event (start or end).

    int current = 0;
    int maximum = 0;
    int answerPoint = 0;

    for (int i = 0; i < 2 * n; i++) {

        current += events[i].type; // The current variable keeps track of the number of intervals that overlap at any given point. It is updated by adding the type of each event (start or end) as we iterate through the sorted events array. When a start event occurs, current is incremented by 1, and when an end event occurs, current is decremented by 1. This allows us to maintain an accurate count of the number of overlapping intervals as we process each event in order of their points.

        if (current > maximum) {
            maximum = current;
            answerPoint = events[i].point; // When the current count of overlapping intervals exceeds the previous maximum, we update the maximum and record the point at which this maximum occurs. This ensures that we capture the point with the highest number of overlapping intervals as we iterate through the events.
        }
    }

    printf("Point with maximum overlap = %d\n", answerPoint);
    printf("Maximum number of intervals = %d\n", maximum);

    return 0;
}