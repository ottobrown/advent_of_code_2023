#include <stdio.h>
#include <ctype.h>

int main() {
    FILE* input_file = fopen("input/1.txt", "r");

    char current;
    int first_digit = -1;
    int last_digit;

    unsigned long total = 0;

    while((current = getc(input_file)) != EOF){
        if (current == '\n') {
            total += (unsigned long) first_digit * 10 + last_digit;
            first_digit = -1;
        } else if (isdigit(current)) {
            if (first_digit == -1) first_digit = current - '0';
            last_digit = current - '0';
        }
    }

    printf("%lu\n", total);

    fclose(input_file);
    return 0;
}
