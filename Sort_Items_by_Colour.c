#include <stdio.h>
/* The question gives us several items. Every item has two things:
- A number, such as 25, 10, or 40.
- A colour: red (R), blue (B), or yellow (Y).
We must rearrange the items so that all red items come first, all blue items come next, and all yellow items come last.
Before sorting, you give the items in this format:
25B   10Y   40R   30R   15B
After sorting by colour, you see:
(10, R)   (40, R)  (30,R)  (15, B)  (10, Y)   Notice that the number and its colour must stay together. We cannot separate 25 from its colour B.    */
struct Item { // A struct lets us keep related information together. Here, each item has a number and a colour.
    int number;
    char color;
};
int main() {
    int n;
    printf("Enter number of items: ");
    scanf("%d", &n); // Think of & here as giving the variable's memory address.

    struct Item red[n], blue[n], yellow[n]; // Each array can hold up to n items. That is enough because there cannot be more than n items of any one colour.
    int r = 0, b = 0, y = 0; /* creates three counters:
- r = 0: no red items have been stored yet.
- b = 0: no blue items have been stored yet.
- y = 0: no yellow items have been stored yet*/

    printf("Enter number and color (R/B/Y) as: <Number><Colour>:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %c", &red[0].number, &red[0].color); // %c reads a character and stores it in red[0].colour.

        if (red[0].color == 'R' || red[0].color == 'r') {
            red[r++] = red[0]; // uses red[0] as the destination and then changes r to 1. When r = 1, the next red item is stored at red[1], and r becomes 2. In simple words: Store the red item in the next available red position, then increase the red counter.
        }
        else if (red[0].color == 'B' || red[0].color == 'b') {
            blue[b].number = red[0].number;
            blue[b].color = red[0].color;
            b++;
        }
        else if (red[0].color == 'Y' || red[0].color == 'y') {
            yellow[y].number = red[0].number; // red[0] is used as a temporary variable to hold the current item. The item is then copied to the appropriate colour array.
            yellow[y].color = red[0].color;
            y++;
        }
    }
    printf("\nSorted by colour:\n");
    for (int i = 0; i < r; i++)
        printf("(%d, R) ", red[i].number);
    for (int i = 0; i < b; i++)
        printf("(%d, B) ", blue[i].number);
    for (int i = 0; i < y; i++)
        printf("(%d, Y) ", yellow[i].number);
    printf("\n");
    return 0;
}