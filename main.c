#include <stdio.h>
#include "at_parse.h"

#define _CRT_SECURE_NO_WARNINGS

int main(int argc, char ** argv) {

    FILE * file;
    char ch;
    char line[100];

    if(argc < 2){

        printf("Use: %s <filename>\n", argv[0]);
        return 1;

    }
    file = fopen(argv[1], "rb");
    if(file == NULL){
        perror("Can`t open file");
        return 1;
    }

    printf("File opened successfully: %s\n", argv[1]);

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("Read line: %s", line);
        for (int i = 0; i < strlen(line); ++i) {
            char ch = line[i];
            if (ch != '\n' && ch != '\r') {
                printf("Read character: %c\n", ch);
                at_parse(ch);
            }
        }
    }

    resprint();

    fclose(file);
    return 0;
}
