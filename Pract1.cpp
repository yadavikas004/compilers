#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

enum TokenType { ID, NUM, OP, PUNCT, UNK };

struct Token {
    TokenType type;
    string value;
};

vector<Token> tokenize(const string &input) {
    vector<Token> tokens;
    string current;
    
    for (char c : input) {
        if (isalpha(c) || isdigit(c)) {
            current += c;
        } else {
            if (!current.empty()) {
                tokens.push_back({isalpha(current[0]) ? ID : NUM, current});
                current.clear();
            }
            if (!isspace(c)) {
                tokens.push_back({ispunct(c) ? OP : UNK, string(1, c)});
            }
        }
    }
    
    if (!current.empty()) {
        tokens.push_back({isalpha(current[0]) ? ID : NUM, current});
    }
    
    return tokens;
}

void printTokens(const vector<Token> &tokens) {
    const char* types[] = {"ID", "NUM", "OP", "PUNCT", "UNK"};
    for (const auto &t : tokens) {
        cout << "Type: " << types[t.type] << ", Value: " << t.value << endl;
    }
}

int main() {
    string input;
    cout << "Enter a lexeme: ";
    getline(cin, input);
    printTokens(tokenize(input));
    return 0;
}