#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sfl(char *word) {
    int length = strlen(word);
    if (length > 1) {
        if (word[length - 1] == '\n') {
            word[length - 1] = '\0';
            char temp = word[0];
            word[0] = word[length - 2];
            word[length - 2] = temp;
        } else {
            char temp = word[0];
            word[0] = word[length - 1];
            word[length - 1] = temp;
        }
    }
}

int main() {
    char sentence[1000];
    printf("Введите предложение: ");
    fgets(sentence, sizeof(sentence), stdin);

    char *token = strtok(sentence, " ");
    while (token != NULL) {
        sfl(token);
        printf("%s ", token);
        token = strtok(NULL, " ");
    }
    return 0;
}
