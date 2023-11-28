#include "dsl.h"
#include "cJSON.h"
#include <stdlib.h>
#include <stdio.h>
char* serialize_tokens_to_json(Token* tokens, int tokenCount) {
    cJSON* json_array = cJSON_CreateArray();
    for (int i = 0; i < tokenCount; ++i) {
        cJSON* json_token = cJSON_CreateObject();
        cJSON_AddStringToObject(json_token, "type", token_type_to_string(tokens[i].type));
        cJSON_AddStringToObject(json_token, "value", tokens[i].value ? tokens[i].value : "");
        cJSON_AddItemToArray(json_array, json_token);
    }
    char* json_string = cJSON_Print(json_array);
    cJSON_Delete(json_array);
    return json_string;
}

void save_json_to_file(const char* json_string, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Unable to open file for writing JSON");
        return;
    }
    fprintf(file, "%s", json_string);
    fclose(file);
}

int main() {
    const char* filename = "input.dsl"; // Имя файла с вашим DSL кодом
    int tokenCount = 0;
    Token* tokens = tokenize_file(filename, &tokenCount);

    char* json_string = serialize_tokens_to_json(tokens, tokenCount);
    save_json_to_file(json_string, "output.json");

    // Очистка
    free(json_string);
    free_tokens(tokens, tokenCount);

    return 0;
}
