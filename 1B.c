#include <stdio.h>
#include <ctype.h>
#include <string.h>

int spelled_digit(char buffer[5]);
void add_char(char buffer[5], char c);

int main() {
    FILE* input_file = fopen("input/1.txt", "r");

    char current;
    int first_digit = -1;
    int last_digit;

    // stores the last 5 characters read
    char buffer[5];

    unsigned long total = 0;

    while((current = getc(input_file)) != EOF){
        add_char(buffer, current);

        if (current == '\n') {
            total += (unsigned long) first_digit * 10 + last_digit;
            first_digit = -1;
            continue;
        } 

        int spelled = spelled_digit(buffer);
        if (spelled) {
            if (first_digit == -1) first_digit = spelled;
            last_digit = spelled;
            continue;
        }

        if (isdigit(current)) {
            if (first_digit == -1) first_digit = current - '0';
            last_digit = current - '0';
        }
    }

    printf("%lu\n", total);

    fclose(input_file);
    return 0;
}

/// if the buffer ends with the name of a digit (i.e. "one").
/// return that digit (i.e. 1). If not, return 0
int spelled_digit(char buffer[5]) {
    if (strncmp("one", buffer+2, 3) == 0) return 1;
    if (strncmp("two", buffer+2, 3) == 0) return 2;
    if (strncmp("three", buffer, 5) == 0) return 3;
    if (strncmp("four", buffer+1, 4) == 0) return 4;
    if (strncmp("five", buffer+1, 4) == 0) return 5;
    if (strncmp("six", buffer+2, 3) == 0) return 6;
    if (strncmp("seven", buffer, 5) == 0) return 7;
    if (strncmp("eight", buffer, 5) == 0) return 8;
    if (strncmp("nine", buffer+1, 4) == 0) return 9;

    return 0;
}

void add_char(char buffer[5], char c) {
    for(int i=1; i<5; i++) {
        buffer[i-1] = buffer[i];
    }

    buffer[4] = c;
}
