#include <stdlib.h>
#include <string.h>
#include "helpers.h"

int levenshtein(char *s1, char *s2, int len1, int len2, int start, int *char1Cost) {
    free(char1Cost);
    char1Cost = malloc(len2 * sizeof(*char1Cost));
    for (int i = 0; i < len2; i++) {
        char1Cost[i] = i+1;
    }

    int currentCost = 0;
    for (int i = 0; i < len1; i++) {
        int leftCharCost = i, aboveCharCost = i;
        char char1 = s1[start + i];
        for (int j = 0; j < len2; j++) {
            currentCost = leftCharCost;
            leftCharCost = char1Cost[j];
            if (s2[start + j] != char1) {
                if (aboveCharCost < currentCost) {
                    currentCost = aboveCharCost;
                }
                if (leftCharCost < currentCost) {
                    currentCost = leftCharCost;
                }
                currentCost++;
            }
            char1Cost[j] = currentCost;
            aboveCharCost = currentCost;
        }
    }
    return currentCost;
}

int levenshtein_max(char *s1, char *s2, int len1, int len2, int start, int *char1Cost, int maxDistance) {
    free(char1Cost);
    char1Cost = malloc(len2 * sizeof(*char1Cost));

    for (int i = 0; i < len2; i++) {
        if (i < maxDistance) {
            char1Cost[i] = i + 1;
        }
        else {
            char1Cost[i] = maxDistance + 1;
        }
    }

    int lenDiff = len2 - len1;
    int jStartOffset = maxDistance - lenDiff;
    int jStart = 0, jEnd = maxDistance;
    int currentCost = 0;

    for (int i = 0; i < len1; i++) {
        char char1 = s1[start + i];
        int prevChar1Cost = i, aboveCharCost = i;
        if (i > jStartOffset)
            jStart +=1;
        if (jEnd < len2)
            jEnd += 1;
        for (int j = jStart; j < jEnd; j++) {
            currentCost = prevChar1Cost;
            prevChar1Cost = char1Cost[j];
            if (s2[start + j] != char1) {
                if (aboveCharCost < currentCost)
                    currentCost = aboveCharCost;
                if (prevChar1Cost < currentCost)
                    currentCost = prevChar1Cost;
                currentCost++;
            }
            char1Cost[j] = currentCost;
            aboveCharCost = currentCost;
        }
    }

    if (currentCost > maxDistance)
        currentCost = -1;
    return currentCost;
}

int distance(char *s1, char *s2, int *baseChar1Cost, int baseChar1CostArrLength, int maxDistance) {
    unsigned int s1len = strlen(s1);
    unsigned int s2len = strlen(s2);

    if (s1len == 0  || s2len == 0) {
        return (int)nullDistanceResults(s1, s2, maxDistance);
    }
    if (maxDistance <= 0) {
        return -1;
    }

    if (s1len >= s2len) {
        char *temp;
        temp = s1;
        s1 = s2;
        s2 = temp;
    }
    if (s2len - s1len > maxDistance) {
        return -1;
    }

    int end1, end2, start;
    prefixSuffixPrep(s1, s2, &end1, &end2, &start);

    if (end1 == 0) {
      return -1;
    }

    // TODO: remember to free malloc
    if (end2 < baseChar1CostArrLength) {
        free(baseChar1Cost);
        baseChar1Cost = malloc(sizeof(*baseChar1Cost) * end2);
        for (int i = 0; i < end2; i++) {
            baseChar1Cost[i] = 0;
        }
    }

    if (maxDistance <= 2) {
        printf("checkmax\n");

        return levenshtein_max(s1, s2, end1, end2, start, baseChar1Cost, maxDistance);
    }

    return levenshtein(s1, s2, end1, end2, start, baseChar1Cost);
}

