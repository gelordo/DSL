// dsl.h
#ifndef DSL_H
#define DSL_H
#define MAX_TOKENS 1024

// Типы токенов
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

// Структура токена
typedef struct {
    TokenType type;
    char* value;
} Token;

// Функция токенизации файла
Token* tokenize_file(const char* input, int* tokenCount);

// Функция освобождения массива токенов
void free_tokens(Token* tokens, int tokenCount);

#endif // DSL_H