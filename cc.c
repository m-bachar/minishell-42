#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ENV_VAR_LENGTH 100

char* expandEnvironmentVariables(const char* input) {
    char* result = (char*)malloc(strlen(input) * sizeof(char));
    char envVar[MAX_ENV_VAR_LENGTH];
    const char* p = input;
    char* q = result;
    size_t len = 0;
    int envVarLength = 0;
    
    while (*p) {
        if (*p == '$') {
            p++; // Move past the '$' character
            envVarLength = 0;

            // Collect the characters following '$' until a non-alphanumeric character is encountered
            while (*p && isalnum(*p) && envVarLength < MAX_ENV_VAR_LENGTH - 1) {
                envVar[envVarLength] = *p;
                envVarLength++;
                p++;
            }

            envVar[envVarLength] = '\0'; // Null-terminate the environment variable string

            // Fetch the value of the environment variable
            const char* envValue = getenv(envVar);

            if (envValue) {
                // Copy the environment variable's value to the result string
                while (*envValue && len < MAX_ENV_VAR_LENGTH - 1) {
                    *q++ = *envValue++;
                    len++;
                }
            }
        } else {
            *q++ = *p++;
            len++;
        }
    }

    *q = '\0'; // Null-terminate the result string

    return result;
}

int main() {
    const char* input = "Hello '$DAWDAW'! Your home directory is $HOME.";

    char* expanded = expandEnvironmentVariables(input);
    printf("%s\n", expanded);

    free(expanded);
    return 0;
}
