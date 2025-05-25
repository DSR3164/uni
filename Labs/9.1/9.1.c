#include <stdio.h>
#include <string.h>

void swapFirstLast(char *word) 
{
    int length = strlen(word);
    if (length > 1) 
    {
        char temp = word[0];
        word[0] = word[length - 1];
        word[length - 1] = temp;
    }
}
int main() {
    char sentence[1000];
    printf("Input: ");
    fgets(sentence, sizeof(sentence), stdin);
    int length = strlen(sentence);
    char *current = sentence;
    printf("Output: ");
    for (int i = 0; i < length; i++) 
    {
        if (sentence[i] == ' ' || sentence[i] == '\n') 
        {
            sentence[i] = '\0';
            swapFirstLast(current);
            printf("%s ", current);
            current = sentence + i + 1;
        }
    }
    return 0;
}



