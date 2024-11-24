#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 // Maximum number of productions and input length

typedef struct
{
    char lhs;      // Left-hand side of the production
    char rhs[MAX]; // Right-hand side of the production
} Production;

typedef struct
{
    char action[MAX][MAX];   // Action table
    int gotoTable[MAX][MAX]; // Goto table
} ParsingTable;

// Grammar definitions
// Production productions[MAX];
// int productionCount = 0;

// Function to initialize parsing table
void initializeParsingTable(ParsingTable *table)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            table->action[i][j] = ' ';   // Initialize with spaces
            table->gotoTable[i][j] = -1; // Initialize with -1
        }
    }
}

// Function to define the LR parsing table (hardcoded for this example)
void defineParsingTable(ParsingTable *table)
{
    // Action table for grammar S -> aS | b
    table->action[0]['a' - 'a'] = 's'; // state 0, input 'a' -> shift to state 2
    table->action[0]['b' - 'a'] = 's'; // state 0, input 'b' -> shift to state 1
    table->action[1]['$' - 'a'] = 'a'; // state 1, end of input -> accept
    table->action[2]['a' - 'a'] = 's'; // state 2, input 'a' -> shift to state 2
    table->action[2]['b' - 'a'] = 's'; // state 2, input 'b' -> shift to state 1

    // Goto table
    table->gotoTable[0]['S' - 'A'] = 3; // state 0, goto state 3 on S
    table->gotoTable[0]['a' - 'a'] = 2; // state 0, goto state 2 on 'a'
    table->gotoTable[0]['b' - 'a'] = 1; // state 0, goto state 1 on 'b'
    table->gotoTable[2]['S' - 'A'] = 3; // state 2, goto state 3 on S
    table->gotoTable[2]['a' - 'a'] = 2; // state 2, goto state 2 on 'a'
    table->gotoTable[2]['b' - 'a'] = 1; // state 2, goto state 1 on 'b'
}

// Function to perform LR parsing
void parseInput(const char *input, ParsingTable *table)
{
    if (strlen(input) == 0)
    {
        printf("\nEmpty string detected!\n");
        printf("Input string rejected - grammar requires at least one character\n");
        return;
    }

    int stateStack[MAX];
    int top = 0;
    stateStack[top] = 0;
    int i = 0;

    printf("\nParsing Steps:\n");
    printf("Stack\t\tInput\t\tAction\n");

    while (1)
    {
        printf("State: %d\t\t%s\t\t", stateStack[top], &input[i]);

        char currentSymbol = (input[i] != '\0') ? input[i] : '$';
        int currentState = stateStack[top];
        int symbolIndex = (currentSymbol == '$') ? ('$' - 'a') : (currentSymbol - 'a');
        char action = table->action[currentState][symbolIndex];

        if (action == 's')
        {
            stateStack[++top] = table->gotoTable[currentState][currentSymbol - 'a'];
            i++;
            printf("Shift\n");
        }
        else if (action == 'r')
        {
            top--;
            printf("Reduce\n");
            int gotoState = table->gotoTable[stateStack[top]]['S' - 'A'];
            stateStack[++top] = gotoState;
        }
        else if (action == 'a')
        {
            printf("Accept\n\nInput string accepted!\n");
            return;
        }
        else
        {
            printf("Error\n\nInput string rejected!\n");
            return;
        }

        if (i > strlen(input))
        {
            printf("Error\n\nInput string rejected! Unexpected end of input.\n");
            return;
        }
    }
}
// Function to add a production to the grammar

int main()
{
    ParsingTable table;
    initializeParsingTable(&table);
    defineParsingTable(&table);

    char input[MAX];
    printf("Enter the input string (e.g., ab): ");
    scanf("%s", input);

    parseInput(input, &table);
    return 0;
}
