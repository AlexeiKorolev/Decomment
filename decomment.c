
#include <stdio.h>

#define OUTSIDE_COMMENT 0
#define HALF_INSIDE_COMMENT 1
#define INSIDE_COMMENT 2
#define HALF_OUTSIDE_COMMENT 3
#define INSIDE_STRING 4

int main() {
    int nextChar;
    nextChar = getchar();
    short curState = 0;
    /* 
    Possible States:
    0: outside of comment
    1: half-inside of comment
    2: inside of comment
    3: half-outside of comment
    4: inside of string
    */

    while (nextChar != EOF) {
        if (curState == OUTSIDE_COMMENT && nextChar == '/') {
            curState = HALF_OUTSIDE_COMMENT;
            goto next_def;
        }
        else if (curState == OUTSIDE_COMMENT && nextChar == '\"') {
            curState = INSIDE_STRING;
            printf("%c", nextChar);
            goto next_def;
        }else if (curState == OUTSIDE_COMMENT) {
            printf("%c", nextChar);
            goto next_def;
        }

        if (curState == HALF_INSIDE_COMMENT && nextChar == '*') {
            curState = INSIDE_COMMENT;
            goto next_def;
        }
        else if (curState == HALF_INSIDE_COMMENT) {
            curState = OUTSIDE_COMMENT;
            printf("/");
            printf("%c", nextChar);
            goto next_def;
        }

        if (curState == INSIDE_COMMENT && nextChar == '*') {
            curState = HALF_OUTSIDE_COMMENT;
            goto next_def;
        }
        else if (curState == INSIDE_COMMENT) {
            goto next_def;
        }

        if (curState == HALF_OUTSIDE_COMMENT && nextChar == '/') {
            curState = OUTSIDE_COMMENT;
            goto next_def;
        }
        else if (curState == HALF_INSIDE_COMMENT) {
            curState = INSIDE_COMMENT;
        }

        if (curState == INSIDE_STRING && nextChar == '\"') {
            printf("%c", nextChar);
            curState = OUTSIDE_COMMENT;
            goto next_def;
        }
        else if (curState == INSIDE_STRING) {
            printf("%c", nextChar);
            goto next_def;
        }

    next_def:
        nextChar = getchar();
    }
    if (curState == OUTSIDE_COMMENT) {
        return 0;
    }
    return -1;
}
