#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 100

char *getBinaryForRegister(char *registerIdentifier)
{
    if (strcmp(registerIdentifier, "R0") == 0)
    {
        return "0000";
    }
    else if (strcmp(registerIdentifier, "R1") == 0)
    {
        return "0001";
    }
    else if (strcmp(registerIdentifier, "R2") == 0)
    {
        return "0010";
    }
    else if (strcmp(registerIdentifier, "R3") == 0)
    {
        return "0011";
    }
    else if (strcmp(registerIdentifier, "R4") == 0)
    {
        return "0100";
    }
    else if (strcmp(registerIdentifier, "R5") == 0)
    {
        return "0101";
    }
    else if (strcmp(registerIdentifier, "R6") == 0)
    {
        return "0110";
    }
    else if (strcmp(registerIdentifier, "R7") == 0)
    {
        return "0111";
    }
    else if (strcmp(registerIdentifier, "R8") == 0)
    {
        return "1000";
    }
    else if (strcmp(registerIdentifier, "R9") == 0)
    {
        return "1001";
    }
    else if (strncmp(registerIdentifier, "R10", 3) == 0)
    {
        return "1010";
    }
    else if (strncmp(registerIdentifier, "R11", 3) == 0)
    {
        return "1011";
    }
    else if (strncmp(registerIdentifier, "R12", 3) == 0)
    {
        return "1100";
    }
    else if (strncmp(registerIdentifier, "R13", 3) == 0)
    {
        return "1101";
    }
    else if (strncmp(registerIdentifier, "R14", 3) == 0)
    {
        return "1110";
    }
    else if (strncmp(registerIdentifier, "R15", 3) == 0)
    {
        return "1111";
    }
    else
    {
        printf("cannot identify register %s", registerIdentifier);
        return "ERROR"; // Invalid register
    }
}

char *removeCommaAtEnd(char *str)
{
    size_t len = strlen(str);
    if (len == 0)
    {
        return str;
    }
    if (str[len - 1] == ',')
    {
        str[len - 1] = '\0';
        return str;
    }
    return str;
}

char *concatenateStrings(char *str1, char *str2)
{
    // Calculate the length of the resulting string
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    // Allocate memory for the resulting string
    char *result = (char *)malloc(len1 + len2 + 1);

    // Check if memory allocation was successful
    if (result == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Copy the first string to the result
    strcpy(result, str1);

    // Concatenate the second string to the result
    strcat(result, str2);

    return result;
}

char **tokenizeString(char *inputString, short *tokenCount)
{
    char *inputCopy = strdup(inputString);
    char **tokens = NULL;
    short count = 0;

    char *token = strtok(inputCopy, " ");
    while (token != NULL)
    {
        tokens = realloc(tokens, (count + 1) * sizeof(char *));
        if (tokens == NULL)
        {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        tokens[count] = strdup(token);
        if (tokens[count] == NULL)
        {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        count++;
        token = strtok(NULL, " ");
    }

    free(inputCopy);
    *tokenCount = count;
    return tokens;
}

int main()
{
    char inputLines[MAX_LINES][MAX_LINE_LENGTH];
    char outputLines[MAX_LINES][MAX_LINE_LENGTH];
    int line_count = 0;

    // Open File
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Read file line by line into array
    while (fgets(inputLines[line_count], MAX_LINE_LENGTH, file) != NULL)
    {
        int length = strlen(inputLines[line_count]);
        line_count++;
        if (line_count >= MAX_LINES)
        {
            fprintf(stderr, "Error: Too many lines in the file\n");
            break;
        }
    }

    // Assembler
    short tokenCount;
    char *binaryOutput = "";
    for (int commandNumber = 0; commandNumber < line_count; commandNumber++)
    {
        char **tokens = tokenizeString(&inputLines[commandNumber][0], &tokenCount);

        for (int p = 0; p < tokenCount; p++)
        {
            tokens[p] = removeCommaAtEnd(tokens[p]);
        }

        char *temp;
        if (!strcmp("ADD", tokens[0]))
        {
            binaryOutput = "0000";
            binaryOutput = concatenateStrings(binaryOutput, getBinaryForRegister(tokens[1]));
            binaryOutput = concatenateStrings(binaryOutput, getBinaryForRegister(tokens[2]));
            binaryOutput = concatenateStrings(binaryOutput, getBinaryForRegister(tokens[3]));
        }
        else if (!strcmp("ADDI", tokens[0]))
        {
            binaryOutput = "0001";
        }
        else if (!strcmp("JMP", tokens[0]))
        {
            binaryOutput = "0010";
        }
        else if (!strcmp("LD", tokens[0]))
        {
            binaryOutput = "0011";
        }
        else if (!strcmp("ST", tokens[0]))
        {
            binaryOutput = "0100";
        }
        else if (!strcmp("CMP", tokens[0]))
        {
            binaryOutput = "0101";
        }
        else if (!strcmp("JE", tokens[0]))
        {
            binaryOutput = "0110";
        }
        else if (!strcmp("JA", tokens[0]))
        {
            binaryOutput = "0111";
        }
        else if (!strcmp("JB", tokens[0]))
        {
            binaryOutput = "1000";
        }
        else if (!strcmp("JAE", tokens[0]))
        {
            binaryOutput = "1001";
        }
        else if (!strcmp("JBE", tokens[0]))
        {
            binaryOutput = "1010";
        }

        printf("binary output is : %s\n", binaryOutput);

        for (int j = 0; j < tokenCount; j++)
        {
            printf("Token %d: %s\n", j + 1, tokens[j]);
        }
    }

    // output to file
    FILE *output_file = fopen("output.txt", "w");

    if (output_file == NULL)
    {
        perror("Error opening output file");
        return 1;
    }

    for (int i = 0; i < line_count; i++)
    {
        fprintf(output_file, "%s", inputLines[i]);
    }

    fclose(file);
    return 0;
}
