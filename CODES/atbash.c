#include <stdio.h>
#include <string.h>

void atbash(char *text) {
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = 'z' - (text[i] - 'a');
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = 'Z' - (text[i] - 'A');
        }
    }
}

int main() {
    char text[100];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);

    atbash(text);
    printf("Encrypted text: %s\n", text);

    return 0;
}
