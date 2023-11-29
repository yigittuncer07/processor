#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 1000

int main() {

    FILE *file = fopen("input.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int line_count = 0;

    while (fgets(lines[line_count], MAX_LINE_LENGTH, file) != NULL) {
        // Remove newline character at the end of the line
        int length = strlen(lines[line_count]);

        line_count++;
        // Check if the number of lines exceeds the maximum
        if (line_count >= MAX_LINES) {
            fprintf(stderr, "Error: Too many lines in the file\n");
            break;
        }
    }

    FILE *output_file = fopen("output.txt", "w");

    if (output_file == NULL) {
        perror("Error opening output file");
        return 1; // Return an error code
    }

    for (int i = 0; i < line_count; i++) {
        fprintf(output_file, "%s", lines[i]);
    }

    fclose(file);
    return 0; 
}
