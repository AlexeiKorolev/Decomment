#include <stdio.h>

enum State {NORMAL, HALF_IN_COMMENT, IN_COMMENT, HALF_OUT_COMMENT,
   SPECIAL, S_STR, S_SPECIAL, D_STR, D_SPECIAL};


/* Input is an int c that represents the next character
   read. Prints the character, returns void */
void printCharacter(int c) {
   printf("%c", c);
}


/* Input: int c -> the current character
   Output: enum State -> the next state*/
enum State handleNormal(int c, int* lineNum) {
   if (c == '/') { return HALF_IN_COMMENT; }
   /* else if (c == '\n') {printCharacter(c); lineNum++; return NORMAL;} */
   else if (c == '\'') {printCharacter(c); return S_STR;}
   else if (c == '\"') {printCharacter(c); return D_STR;}
   else {printCharacter(c); return NORMAL; } /* WILL ALSO NEED TO ADD COUNTING
                                               FOR NEWLINES HERE*/
}

/* Input: an int c -> the current character
   Returns enum State of the next logical state */
enum State handleHalfIn(int c, int* lineNum) {
   if (c == '*') {printCharacter(' '); return IN_COMMENT; }
   else if (c == '\"') {printCharacter('/'); printCharacter('\"'); return D_STR;}
   else if (c == '\'') {printCharacter('/'); printCharacter('\''); return S_STR; }
   /* else if (c == '\n') {printCharacter('/'); printCharacter('\n'); 
      lineNum++; return NORMAL; } */
   else if (c == '/') { printCharacter(c); return HALF_IN_COMMENT; }
   else {printCharacter('/'); printCharacter(c); return NORMAL; }
}

enum State handleInComment(int c, int* lineNum) {
   /* ADD LINE COUNTING */ 
   if (c == '\n') {printCharacter('\n'); return IN_COMMENT;} 
   else if (c == '*') {return HALF_OUT_COMMENT; }
   else { return IN_COMMENT; }
}

enum State handleHalfOut(int c, int* lineNum) {
   if (c == '/') { return NORMAL; }
   else if (c == '*') { return HALF_OUT_COMMENT; }
   /*else if (c == '\n') { lineNum++; return IN_COMMENT; } */
   else { return IN_COMMENT; }
}

enum State handleDSTR(int c, int* lineNum) {
   if (c == '\"') {printCharacter(c); return NORMAL; }
   else if (c == '\\') {printCharacter(c); return D_SPECIAL; }
   else {printCharacter(c); return D_STR; }
}

enum State handleSSTR(int c, int* lineNum) {
   if (c == '\'') {printCharacter(c); return NORMAL; }
   else if (c == '\\') {printCharacter(c); return S_SPECIAL; }
   else {printCharacter(c); return S_STR; }
}

enum State handleDSpecial(int c, int* lineNum) {
   printCharacter(c);
   return D_STR;
}

enum State handleSSpecial(int c, int* lineNum) {
   printCharacter(c);
   return S_STR;
}

enum State handleSpecial(int c, int* lineNum) {
   printCharacter(c);
   return NORMAL;
}
 
int main() {
    int nextChar;
    int curState = NORMAL;
    int lineNum = 1;
    int lastLineInComment = 1;

    while ((nextChar = getchar()) != EOF) {
       if (nextChar == '\n') {lineNum++;}
       switch (curState) {
           case NORMAL:
              curState = handleNormal(nextChar, &lineNum);
              break;
          case HALF_IN_COMMENT:
             curState = handleHalfIn(nextChar, &lineNum);
             if (curState == IN_COMMENT) {lastLineInComment = lineNum;}
              break;
          case IN_COMMENT:
              curState = handleInComment(nextChar, &lineNum);
              break;
          case HALF_OUT_COMMENT:
              curState = handleHalfOut(nextChar, &lineNum);
              break;
          case D_STR:
              curState = handleDSTR(nextChar, &lineNum);
              break;
          case S_STR:
             curState = handleSSTR(nextChar, &lineNum);
             break;
          case SPECIAL:
             curState = handleSpecial(nextChar, &lineNum);
             break;
          case S_SPECIAL:
             curState = handleSSpecial(nextChar, &lineNum);
             break;
          case D_SPECIAL:
             curState = handleDSpecial(nextChar, &lineNum);
             break;
          default:
             break;
       }
    }
    if (curState == HALF_IN_COMMENT) {printCharacter('/');}
    if (curState == IN_COMMENT || curState == HALF_OUT_COMMENT) {
       fprintf(stderr, "Error: line %d: unterminated comment\n", lastLineInComment);
       return 1;
    }
    
    return 0;
}
