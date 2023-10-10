#include <stdio.h>
#include "editDistance.h"

void swap(char *s1, char *s2) {
    char *temp = s1;
    s1 = s2;
    s2 = temp;
}

int main() {
    char *s1 = "hello world";
    char *s2 = "hi worl";

    swap(s1, s2);

    int *baseChar1Cost = NULL;

    printf("%s\t%s\n", s1, s2);
    int editDistance = distance(s1, s2, baseChar1Cost, 0, 5);
    printf("edit distance: %d\n", editDistance);

    return 0;
}