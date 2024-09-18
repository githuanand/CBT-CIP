#include <stdio.h>
#include <ctype.h>
#include <string.h>  // Required for strcspn

// Function to count words, lines, and characters in a file
void countTextFile(const char *filename, int *wordCount, int *lineCount, int *charCount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char ch;
    int inWord = 0;  // Flag to track if we are inside a word

    *wordCount = 0;
    *lineCount = 0;
    *charCount = 0;

    while ((ch = fgetc(file)) != EOF) {
        (*charCount)++;  // Count every character read

        if (ch == '\n') {
            (*lineCount)++;  // Increment line count on newline character
        }

        if (isspace(ch)) {
            if (inWord) {
                inWord = 0;  // End of a word
                (*wordCount)++;
            }
        } else {
            inWord = 1;  // Inside a word
        }
    }

    // If the file ends with a word not followed by space, count it
    if (inWord) {
        (*wordCount)++;
    }

    // Ensure to count the last line if the file does not end with a newline
    if (*charCount > 0 && ch != '\n') {
        (*lineCount)++;
    }

    fclose(file);
}

int main() {
    char filename[256];
    int wordCount, lineCount, charCount;

    // Get the filename from the user
    printf("Enter the filename to analyze: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        perror("Error reading input");
        return 1;
    }
    filename[strcspn(filename, "\n")] = '\0';  // Remove the trailing newline character

    // Count words, lines, and characters
    countTextFile(filename, &wordCount, &lineCount, &charCount);

    // Display the results
    printf("\nFile Analysis:\n");
    printf("Total Characters: %d\n", charCount);
    printf("Total Lines: %d\n", lineCount);
    printf("Total Words: %d\n", wordCount);

    return 0;
}
