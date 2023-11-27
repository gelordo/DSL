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
    TOKEN_EQUAL,
    TOKEN_NOT,
    TOKEN_SAME,
    TOKEN_NOT_SAME,
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
    char* value;
    size_t length;

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
            if (strncmp(current, "==", 2) == 0) {
            tokens[(*tokenCount)++] = (Token){TOKEN_SAME, NULL};
            current += 2;
        } else if (strncmp(current, "!=", 2) == 0) {
            tokens[(*tokenCount)++] = (Token){TOKEN_NOT_SAME, NULL};
            current += 2;
        } else if (strncmp(current, ">=", 2) == 0) {
            tokens[(*tokenCount)++] = (Token){TOKEN_GREATER_EQ, NULL};
            current += 2;
        } else if (strncmp(current, "<=", 2) == 0) {
            tokens[(*tokenCount)++] = (Token){TOKEN_LESS_EQ, NULL};
            current += 2;
        } else if{
            switch (*current) {
                case '+':
                    tokens[(*tokenCount)++] = (Token){TOKEN_ADDITION, NULL};
                    current++;
                    break;
                case '-':
                    tokens[(*tokenCount)++] = (Token){TOKEN_SUBTRACTION, NULL};
                    current++;
                    break;
                case '*':
                    tokens[(*tokenCount)++] = (Token){TOKEN_MULTIPLICATION, NULL};
                    current++;
                    break;
                case '/':
                    tokens[(*tokenCount)++] = (Token){TOKEN_DIVISION, NULL};
                    current++;
                    break;
                case '(':
                    tokens[(*tokenCount)++] = (Token){TOKEN_L_PAREN, NULL};
                    current++;
                    break;
                case ')':
                    tokens[(*tokenCount)++] = (Token){TOKEN_R_PAREN, NULL};
                    current++;
                    break;
                case ';':
                    tokens[(*tokenCount)++] = (Token){TOKEN_END_LINE, NULL};
                    current++;
                    break;
                case '{':
                    tokens[(*tokenCount)++] = (Token){TOKEN_L_BRACE, NULL};
                    current++;
                    break;
                case '}':
                    tokens[(*tokenCount)++] = (Token){TOKEN_R_BRACE, NULL};
                    current++;
                    break;
                case '>':
                    tokens[(*tokenCount)++] = (Token){TOKEN_GREATER, NULL};
                    current++;
                    break;
                case '<':
                    tokens[(*tokenCount)++] = (Token){TOKEN_LESS, NULL};
                    current++;
                    break;
                case '=':
                    tokens[(*tokenCount)++] = (Token){TOKEN_EQUAL, NULL};
                    current++;
                    break;
                case '!':
                    tokens[(*tokenCount)++] = (Token){TOKEN_NOT, NULL};
                    current++;
                    break;
                // Другие символы...
                default:
                    if (isdigit(*current)) {
                        const char* start_nm = current;
                        while (isdigit(*current)) { // Собрать целую часть
                            current++;
                        }
                        if (*current == '.' && isdigit(*(current + 1))) { // Проверка на вещественное число
                            // Включить точку и одну цифру после неё
                            length = current - start_nm + 2;
                            current += 2; // Пропуск точки и цифры после неё
                        } else { // Целое число
                            length = current - start_nm;
                        }
                        value = (char*)malloc(length + 1);
                        strncpy(value, start_nm, length);
                        value[length] = '\0';
                        tokens[(*tokenCount)++] = (Token){
                            (*current == '.' && isdigit(*(current - 1))) ? TOKEN_FLOAT : TOKEN_INT, value
                        length = 0;
                        };
                    } else if (isalpha(*current) || *current == '_') {
                        if (strncmp(current, "add", 3) == 0) {
                        tokens[(*tokenCount)++] = (Token){TOKEN_ADDITION, NULL};
                        current += 3;
                        } else if (strncmp(current, "sub", 3) == 0) {
                        tokens[(*tokenCount)++] = (Token){TOKEN_SUBTRACTION, NULL};
                        current += 3;
                        } else if (strncmp(current, "mult", 4) == 0) {
                        tokens[(*tokenCount)++] = (Token){TOKEN_MULTIPLICATION, NULL};
                        current += 4;
                        } else if (strncmp(current, "div", 3) == 0) {
                        tokens[(*tokenCount)++] = (Token){TOKEN_DIVISION, NULL};
                        current += 3;
                        } else if (strncmp(current, "if", 2) == 0) {
                        tokens[(*tokenCount)++] = (Token){TOKEN_IF, NULL};
                        current += 2;
                        } else if (strncmp(current, "for", 3) == 0) {
                        tokens[(*tokenCount)++] = (Token){TOKEN_FOR, NULL};
                        current += 3;
                        } else if (strncmp(current, "to", 2) == 0) {
                        tokens[(*tokenCount)++] = (Token){TOKEN_FOR_INCREASE, NULL};
                        current += 2;
                        } else if (strncmp(current, "downto", 6) == 0) {
                        tokens[(*tokenCount)++] = (Token){TOKEN_FOR_DECREASE, NULL};
                        current += 6;
                        } else if (strncmp(current, "while", 5) == 0) {
                        tokens[(*tokenCount)++] = (Token){TOKEN_WHILE, NULL};
                        current += 5;
                        } else {
                            const char* start_id = current;
                            while (isalpha(*current) || isdigit(*current) || *current == '_') {
                                current++;
                            }
                            length = current - start_id;
                            value = (char*)malloc(length + 1);
                            strncpy(value, start_id, length);
                            value[length] = '\0';
                            tokens[(*tokenCount)++] = (Token){TOKEN_IDENTIFIER, value};
                            length = 0;
                        }
                      } else if (isspace(*current)) {
                        tokens[(*tokenCount)++] = (Token){TOKEN_SPACE, NULL};
                        // Пропускаем пробельные символы
                        current++;
                    } else {
                        // Обработка ошибок: нераспознанный символ
                    }
                    break;}
        } else {
        // Игнорируем символы до "START" или после "END"
        }
    
        }
    }
}