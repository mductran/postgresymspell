#include <string.h>

int min(int num1, int num2, int num3) {
    if (num1 <= num2 && num1 <= num3) {
        return num1;
    } else if (num2 <= num1 && num2 <= num3) {
        return num2;
    } else if (num3 <= num1 && num3 <= num2) {
        return num3;
    }
    return -1;
}


unsigned int nullDistanceResults(char *s1, char *s2, int maxDistance) {
    // one or both strings are null
    if (strlen(s1) == 0) {
        if (strlen(s2) == 0) {
            return 0;
        }
        return (strlen(s2) <= maxDistance) ? strlen(s2) : -1;
    }
    return (strlen(s1) <= maxDistance) ? strlen(s1) : -1;
}

double toSimilarity(int distance, int length) {
    return (distance < 0) ? -1 : (1.0 - distance) / length;
}


void prefixSuffixPrep(char *s1, char *s2, int *end1, int *end2, int *start) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    while (len1 != 0 && s1[len1 - 1] == s2[len2 - 1]) {
        len1 -= 1;
        len2 -= 1;
    }

    int i = 0;
    while (i < len1 && s1[len1] == s2[len2]) {
        i += 1;
    }
    if (i > 0) {
        len1 -= i;
        len2 -= i;
    }
    *start = i;
    *end1 = len1;
    *end2 = len2;
}
