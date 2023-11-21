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

Token* tokenize_file(const char* filename) {
    // Открытие файла для чтения
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    Token* tokens = malloc(MAX_TOKENS * sizeof(Token));
    int tokenCount = 0;

    // Чтение файла и токенизация
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        // Ваша логика токенизации для строки 'buffer'
        // ...
    }    // Закрытие файла
    fclose(file);

    // Возвращение массива токенов
    return tokens;
	
	//LOLOLOLLOLOLOLOLOLO
}