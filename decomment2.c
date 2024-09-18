#include <stdio.h>

enum State {NORMAL, HALF_IN_COMMENT, IN_COMMENT, HALF_OUT_COMMENT, SPECIAL, S_STR, S_SPECIAL, D_STR, D_SPECIAL};

int main() {
    int nextChar;
    int curState = NORMAL;

    while ((nextChar = getchar()) != EOF) {
        switch (curState) {
            case NORMAL:
                if (nextChar == '/') { curState = HALF_IN_COMMENT; }
                else if (nextChar == '\\') {curState = SPECIAL; goto printchar;}
                else if (nextChar == '\'') {curState = S_STR; goto printchar;}
                else if (nextChar == '\"') {curState = D_STR; goto printchar;}
                else {goto printchar;}
                break;
            case HALF_IN_COMMENT:
                if (nextChar == '*') { curState = IN_COMMENT; }
                else {curState = NORMAL; printf("%c", '/'); goto printchar;}
                break;
            case IN_COMMENT:
                if (nextChar == '\n') {goto printchar;}
                else if (nextChar == '*') {curState = HALF_OUT_COMMENT; }
                else { /* Do nothing */ }
                break;
            case HALF_OUT_COMMENT:
                if (nextChar == '/') {curState = NORMAL; printf("%c", ' '); }
                else if (nextChar == '*') { /* Do nothing */ }
                else {curState = IN_COMMENT; }
                break;
            case D_STR:
                if (nextChar == '\"') {curState = NORMAL; goto printchar;}
                else if (nextChar == '\\') {curState = D_SPECIAL; goto printchar;}
                else {goto printchar;}
                break;
            case S_STR:
                if (nextChar == '\'') {curState = NORMAL; goto printchar;}
                else if (nextChar == '\\') {curState = S_SPECIAL; goto printchar;}
                else {goto printchar;}
                break;
            case D_SPECIAL:
                curState = D_STR; goto printchar;
                break;
            case S_SPECIAL:
                curState = S_STR; goto printchar;
                break;
            case SPECIAL:
                curState = NORMAL; goto printchar;
                break;
        }
        continue;

        printchar:
        printf("%c", nextChar);
    }

    

    


    return 0;
}
