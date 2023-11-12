#include <stdio.h>
#include "at_parse.h"

    char char_buffer[BUFFER_SIZE];
    int buffer_index = 0;
    int line_count = 1;

typedef struct {
    int isOK;


} Result;

    Result res;



int state = 0;

void init() {

    state = 0;

}

int increase_line_count(void) {

    return ++line_count;

};

void resprint() {
    if (res.isOK) {
        printf("Result: OK\n");
    } else {
        printf("Result: ERROR\n");
    }
}

int end_of_string(void) {
    buffer_index = '\0';
    increase_line_count();
    return 0;
};

int save_char(char ch) {

    if (buffer_index < BUFFER_SIZE) {

        char_buffer[buffer_index++] = ch;
        return 0;
    } else {
       return 1;
    }

};

int at_parse(char ch) {

    switch (state) {
    case 0: {
        if (ch == CARRIAGE_RETURN) {
            state = 1;
            init();
            return 0;
        } else return 1;
    }
    case 1: {
    if (ch == LINE_FEED || ch == CARRIAGE_RETURN) {
        state = 2;
        return 0;
    } else return 1;
}
    case 2: {
    if (ch == '+') {
        printf("Recognized '+', transitioning to state 30\n");
        state = 30;
        return increase_line_count();
    } else if (ch == 'O') {
        printf("Recognized 'O', transitioning to state 4\n");
        state = 4;
        return 0;
    } else if (ch == 'E') {
        printf("Recognized 'E', transitioning to state 50\n");
        state = 50;
        return 0;
    } else {
        printf("Unexpected character in state 2: %c\n", ch);
        return 1;
    }
}
case 30: {
    if (ch == CARRIAGE_RETURN) {
        state = 32;
        return end_of_string();
    } else {
        state = 31;
        printf("Recognized character in state 30: %c\n", ch);
        return save_char(ch);
    }
}
    case 32: {
        if (ch == LINE_FEED) {
            state = 33;
            return 0;
        } else return 1;
    }
    case 33: {
        if (ch == '+') {
            state = 30;
            return increase_line_count();
        } else if (ch == CARRIAGE_RETURN) {
            state = 34;
            return 0;
        } else return 1;
    }
    case 34: {
        if (ch == LINE_FEED) {
            state = 35;
            return 0;
        } else return 1;
    }
    case 35: {
        if (ch == 'O') {
            state = 4;
            return 0;
        } else if (ch == 'E') {
            state = 50;
            return 0;
        } else return 1;
    }
    case 4: {
    if (ch == 'O') {
        printf("Recognized 'O', transitioning to state 5\n");
        state = 5;
        return 0;
    } else {
        printf("Unexpected character in state 4: %c\n", ch);
        return 1;
    }
}
case 5: {
    if (ch == 'K') {
        printf("Recognized 'K', transitioning to state 6\n");
        state = 6;
        res.isOK = 1;
        return 0;
    } else {
        printf("Unexpected character in state 5: %c\n", ch);
        return 1;
    }
}
    case 50: {
    if (ch == 'R') {
        state = 51;
        return 0;
    } else {

        return 1;
    }
}
case 51: {
    if (ch == 'R') {
        state = 52;
        return 0;
    } else {

        return 1;
    }
}
case 52: {
    if (ch == 'O') {
        state = 53;
        return 0;
    } else {

        return 1;
    }
}
case 53: {
    if (ch == 'R') {
        state = 6;
        res.isOK = 0;
        return 0;
    } else {

        return 1;
    }
}
    case 6: {
    if (ch == CARRIAGE_RETURN) {
        printf("Recognized CARRIAGE_RETURN in state 6\n");
        state = 7;
        return 0;
    } else {
        printf("Unexpected character in state 6: %c\n", ch);
        return 1;
    }
}

case 7: {
    if (ch == LINE_FEED) {
        printf("Recognized LINE_FEED in state 7\n");
        state = 0;
        if (res.isOK) {
            printf("Result: OK\n");
        } else {
            printf("Result: ERROR\n");
        }
        return 0;
    } else if (ch == CARRIAGE_RETURN) {

        return 0;
    } else {
        printf("Unexpected character in state 7: %c\n", ch);
        return 1;
    }
}

    default: {
            printf("Unexpected state: %d\n", state);
            return 1;
        }
}
    printf("Unexpected error! Possible unhandled state!\n");
    return 1;
}
