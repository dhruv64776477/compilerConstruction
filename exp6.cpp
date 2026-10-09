#include <cstdio>
#include <cstring>
#include <cctype>

#define MAX 500

char keywords[][10] = {"int", "if", "else", "while"};

int isKeyword(const char word[]) {
    for (int i = 0; i < 4; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isDelimiter(char ch) {
    return (ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' ||
            ch == ';' || ch == ',');
}

int isOperatorStart(char ch) {
    return (ch == '+' || ch == '-' ||
            ch == '*' || ch == '/' ||
            ch == '%' || ch == '<' ||
            ch == '>' || ch == '=' ||
            ch == '!' || ch == '&' ||
            ch == '|');
}

void lexicalAnalysis(const char input[]) {
    int i = 0;
    char token[MAX];

    std::printf("\n----- LEXICAL ANALYSIS -----\n");

    while (input[i] != '\0') {
        if (std::isspace(static_cast<unsigned char>(input[i]))) {
            i++;
            continue;
        }

        if (std::isalpha(static_cast<unsigned char>(input[i])) || input[i] == '_') {
            int j = 0;

            while (std::isalnum(static_cast<unsigned char>(input[i])) || input[i] == '_') {
                token[j++] = input[i++];
            }

            token[j] = '\0';
            if (isKeyword(token)) {
                std::printf("%-15s : KEYWORD\n", token);
            } else {
                std::printf("%-15s : IDENTIFIER\n", token);
            }
        } else if (std::isdigit(static_cast<unsigned char>(input[i]))) {
            int j = 0;

            while (std::isdigit(static_cast<unsigned char>(input[i]))) {
                token[j++] = input[i++];
            }

            token[j] = '\0';
            std::printf("%-15s : CONSTANT\n", token);
        } else if (isDelimiter(input[i])) {
            std::printf("%-15c : DELIMITER\n", input[i]);
            i++;
        } else if (isOperatorStart(input[i])) {
            char op[3] = {'\0', '\0', '\0'};

            op[0] = input[i];

            if ((input[i] == '<' || input[i] == '>' ||
                 input[i] == '=' || input[i] == '!') &&
                input[i + 1] == '=') {
                op[1] = '=';
                i += 2;
            } else if (input[i] == '&' && input[i + 1] == '&') {
                op[1] = '&';
                i += 2;
            } else if (input[i] == '|' && input[i + 1] == '|') {
                op[1] = '|';
                i += 2;
            } else {
                i++;
            }

            std::printf("%-15s : OPERATOR\n", op);
        } else {
            std::printf("%-15c : UNKNOWN SYMBOL\n", input[i]);
            i++;
        }
    }
}

void syntaxCheck(const char input[]) {
    int i = 0;
    int braces = 0;
    int parentheses = 0;
    int errors = 0;

    std::printf("\n----- SYNTAX CHECK -----\n");

    while (input[i] != '\0') {
        if (input[i] == '{') {
            braces++;
        } else if (input[i] == '}') {
            braces--;
            if (braces < 0) {
                std::printf("Error: Unexpected '}'\n");
                errors++;
                braces = 0;
            }
        } else if (input[i] == '(') {
            parentheses++;
        } else if (input[i] == ')') {
            parentheses--;
            if (parentheses < 0) {
                std::printf("Error: Unexpected ')'\n");
                errors++;
                parentheses = 0;
            }
        }

        i++;
    }

    if (braces != 0) {
        std::printf("Error: Unbalanced braces {}\n");
        errors++;
    }

    if (parentheses != 0) {
        std::printf("Error: Unbalanced parentheses ()\n");
        errors++;
    }

    if (errors == 0) {
        std::printf("Syntax structure is valid.\n");
    } else {
        std::printf("Syntax errors detected.\n");
    }
}

int main() {
    char input[MAX];
    int position = 0;
    char ch;

    std::printf("============================================\n");
    std::printf("       MINILANG IMPLEMENTATION\n");
    std::printf("============================================\n");

    std::printf("\nEnter MiniLang program.\n");
    std::printf("Enter # on a new line to finish.\n\n");

    while (position < MAX - 1) {
        ch = std::getchar();

        if (ch == '#') {
            break;
        }

        input[position++] = ch;
    }

    input[position] = '\0';

    if (position == 0) {
        std::printf("\nNo MiniLang program was entered.\n");
        std::printf("Please enter at least one valid statement.\n");
        return 0;
    }

    lexicalAnalysis(input);
    syntaxCheck(input);

    std::printf("\n============================================\n");
    std::printf("             END OF PROGRAM\n");
    std::printf("============================================\n");

    return 0;
}
