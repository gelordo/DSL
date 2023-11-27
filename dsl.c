#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_END_LINE,
    TOKEN_START,
    TOKEN_END,
    TOKEN_SPACE,
    TOKEN_ADDITION,
    TOKEN_SUBTRACTION,
    TOKEN_MULTIPLICATION,
    TOKEN_DIVISION,
    TOKEN_L_PAREN,
    TOKEN_R_PAREN,
    TOKEN_L_BRACE,
    TOKEN_R_BRACE,
    TOKEN_INPUT,
    TOKEN_EQUAL,
    TOKEN_NOT,
    TOKEN_SAME,
    TOKEN_GREATER,
    TOKEN_LESS,
    TOKEN_GREATER_EQ,
    TOKEN_LESS_EQ,
    TOKEN_IF,
    TOKEN_FOR,
    TOKEN_FOR_INCREASE,
    TOKEN_FOR_DECREASE,
    TOKEN_WHILE,
} TokenType;

void tokenize_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    int inProgram = 0; // Флаг, указывающий на то, что мы внутри блока START ... END
    int line_number = 0; // Счётчик строк для сообщений об ошибках

    // Массив токенов и счётчик токенов
    Token* tokens = malloc(MAX_TOKENS * sizeof(Token));
    int tokenCount = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        tokenize_line(line, tokens, &tokenCount, &inProgram);
        // Если мы вышли за END, можно прервать чтение файла
        if (!inProgram) break;
    }

    fclose(file);

    // Далее идет код для обработки токенов, а также для очистки памяти

    free(tokens);
}

void tokenize_line(const char* line, Token* tokens, int* tokenCount, int* inProgram) {
    const char* current = line;

    while (*current) {
        if (strncmp(current, "START", 5) == 0 && !(*inProgram)) {
            tokens[(*tokenCount)++] = (Token){TOKEN_START, NULL};
            current += 5; // Перемещение указателя за "START"
            *inProgram = 1; // Установка флага, что мы внутри программы
        } else if (strncmp(current, "END", 3) == 0 && *inProgram) {
            tokens[(*tokenCount)++] = (Token){TOKEN_END, NULL};
            current += 3; // Перемещение указателя за "END"
            *inProgram = 0; // Сброс флага, т.к. мы достигли конца программы
        } else if (*inProgram) {
            while (*current) {
        switch (*current) {
            case '+':
                tokens[(*tokenCount)++] = (Token){TOKEN_ADDITION, NULL};
                current++;
                break;
            case '-':
                tokens[(*tokenCount)++] = (Token){TOKEN_SUBTRACTION, NULL};
                current++;
                break;
            // Другие символы...
            default:
                if (isdigit(*current)) {
                    // Здесь должна быть логика для обработки чисел
                } else if (isalpha(*current)) {
                    // Здесь должна быть логика для обработки идентификаторов и ключевых слов
                } else if (isspace(*current)) {
                    // Пропускаем пробельные символы
                    current++;
                } else {
                    // Обработка ошибок: нераспознанный символ
                }
                break;
        }
    }.
        } else {
            // Игнорируем символы до "START" или после "END"
        }
    }
}
