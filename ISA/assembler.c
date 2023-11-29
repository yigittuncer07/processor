#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 100

char* binaryToHex(char* binaryString) {
    int decimalNumber = strtol(binaryString, NULL, 2);
    char* hexString = (char*)malloc(6 * sizeof(char)); 

    if (hexString == NULL) {
        return "ERROR";
    }

    snprintf(hexString, 6, "%05X", decimalNumber);

    return hexString;
}
char *getBinaryRepresentation10(char *numberString)
{
    int number = atoi(numberString); 

    if (number < 0 || number > 1023)
    {
        return "ERROR"; 
    }

    char *binaryString = (char *)malloc(11 * sizeof(char)); 

    if (binaryString == NULL)
    {
        return "ERROR"; 
    }

    for (int i = 9; i >= 0; --i)
    {
        binaryString[i] = (number & 1) + '0'; 
        number >>= 1;
    }

    binaryString[10] = '\0'; 

    return binaryString;
}

char *getBinaryRepresentation6(char *input)
{
    int number = atoi(input);
    if (number < 0 || number > 63)
    {
        return "ERROR"; // Handle invalid input range
    }

    char *binaryString = (char *)malloc(7 * sizeof(char)); // 6 digits + '\0' terminator

    if (binaryString == NULL)
    {
        return "ERROR"; // Memory allocation failure
    }

    for (int i = 5; i >= 0; --i)
    {
        binaryString[i] = (number & 1) + '0'; // Extract the least significant bit
        number >>= 1;                         // Shift to the right
    }

    binaryString[6] = '\0'; // Null-terminate the string

    return binaryString;
}

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
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    char *result = (char *)malloc(len1 + len2 + 1);

    if (result == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    strcpy(result, str1);

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
    char *hexOutput = "";
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
            binaryOutput = concatenateStrings(binaryOutput, "00");
        }
        else if (!strcmp("ADDI", tokens[0]))
        {
            binaryOutput = "0001";
            binaryOutput = concatenateStrings(binaryOutput, getBinaryForRegister(tokens[1]));
            binaryOutput = concatenateStrings(binaryOutput, getBinaryForRegister(tokens[2]));
            binaryOutput = concatenateStrings(binaryOutput, getBinaryRepresentation6(tokens[3]));
        }
        else if (!strcmp("JMP", tokens[0]))
        {
            binaryOutput = "0010";
            binaryOutput = concatenateStrings(binaryOutput, getBinaryRepresentation10(tokens[1]));
            binaryOutput = concatenateStrings(binaryOutput, "0000");
        }
        else if (!strcmp("LD", tokens[0]))
        {
            binaryOutput = "0011";
            binaryOutput = concatenateStrings(binaryOutput, getBinaryForRegister(tokens[1]));
            binaryOutput = concatenateStrings(binaryOutput, getBinaryRepresentation10(tokens[2]));
        }
        else if (!strcmp("ST", tokens[0]))
        {
            binaryOutput = "0100";
            binaryOutput = concatenateStrings(binaryOutput, getBinaryForRegister(tokens[1]));
            binaryOutput = concatenateStrings(binaryOutput, getBinaryRepresentation10(tokens[2]));
        }
        else if (!strcmp("CMP", tokens[0]))
        {
            binaryOutput = "0101";
            binaryOutput = concatenateStrings(binaryOutput, getBinaryForRegister(tokens[1]));
            binaryOutput = concatenateStrings(binaryOutput, getBinaryForRegister(tokens[2]));
            binaryOutput = concatenateStrings(binaryOutput, "000000");
        }
        else if (!strcmp("JE", tokens[0]))
        {
            binaryOutput = "0110";
            binaryOutput = concatenateStrings(binaryOutput, getBinaryRepresentation10(tokens[1]));
            binaryOutput = concatenateStrings(binaryOutput, "0000");
        }
        else if (!strcmp("JA", tokens[0]))
        {
            binaryOutput = "0111";
            binaryOutput = concatenateStrings(binaryOutput, getBinaryRepresentation10(tokens[1]));
            binaryOutput = concatenateStrings(binaryOutput, "0000");
        }
        else if (!strcmp("JB", tokens[0]))
        {
            binaryOutput = "1000";
            binaryOutput = concatenateStrings(binaryOutput, getBinaryRepresentation10(tokens[1]));
            binaryOutput = concatenateStrings(binaryOutput, "0000");
        }
        else if (!strcmp("JAE", tokens[0]))
        {
            binaryOutput = "1001";
            binaryOutput = concatenateStrings(binaryOutput, getBinaryRepresentation10(tokens[1]));
            binaryOutput = concatenateStrings(binaryOutput, "0000");
        }
        else if (!strcmp("JBE", tokens[0]))
        {
            binaryOutput = "1010";
            binaryOutput = concatenateStrings(binaryOutput, getBinaryRepresentation10(tokens[1]));
            binaryOutput = concatenateStrings(binaryOutput, "0000");
        }
        binaryOutput = concatenateStrings("00",binaryOutput);
        hexOutput = concatenateStrings(binaryToHex(binaryOutput), " ");
        strncpy(outputLines[commandNumber], hexOutput, sizeof(outputLines[commandNumber]) - 1);
        outputLines[commandNumber][sizeof(outputLines[commandNumber]) - 1] = '\0'; // Ensure null-termination
    }

    // output to file
    FILE *output_file = fopen("output.raw", "w");
    if (output_file == NULL)
    {
        perror("Error opening output file");
        return 1;
    }
    for (int i = 0; i < line_count; i++)
    {
        fprintf(output_file, "%s", outputLines[i]);
    }
    fclose(file);
    return 0;
}
