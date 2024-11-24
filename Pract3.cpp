#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum { ID, NUM, OP, PUNCT, UNK } TokenType;

typedef struct {
    TokenType type;
    char value[100];
} Token;

int tokenize(const char* input, Token tokens[], int max) {
    int i = 0, count = 0;
    char current[100];
    int j = 0;

    while (input[i] && count < max) {
        if (isalnum(input[i]) || input[i] == '_') {
            current[j++] = input[i++];
        } else {
            if (j > 0) {
                current[j] = '\0';
                strcpy(tokens[count].value, current);
                tokens[count].type = isalpha(current[0]) ? ID : NUM;
                count++;
                j = 0;
            }
            if (!isspace(input[i])) {
                tokens[count].value[0] = input[i];
                tokens[count].value[1] = '\0';
                tokens[count].type = strchr("=+-*/;", input[i]) ? OP : 
                                     (ispunct(input[i]) ? PUNCT : UNK);
                count++;
            }
            i++;
        }
    }

    if (j > 0) {
        current[j] = '\0';
        strcpy(tokens[count].value, current);
        tokens[count].type = isalpha(current[0]) ? ID : NUM;
        count++;
    }

    return count;
}

void printTokens(Token tokens[], int count) {
    const char* types[] = {"ID", "NUM", "OP", "PUNCT", "UNK"};
    for (int i = 0; i < count; i++) {
        printf("Type: %s, Value: %s\n", types[tokens[i].type], tokens[i].value);
    }
}

int main() {
    char input[100];
    Token tokens[100];
    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    int count = tokenize(input, tokens, 100);
    printTokens(tokens, count);
    return 0;
}