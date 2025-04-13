#include <stdio.h>
#include <string.h>

void august_encrypt(char *text) {
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] - 'a' + 1) % 26 + 'a';
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] - 'A' + 1) % 26 + 'A';
        }
    }
}

void august_decrypt(char *text) {
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] - 'a' - 1 + 26) % 26 + 'a';
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] - 'A' - 1 + 26) % 26 + 'A';
        }
    }
}

int main() {
    char text[100];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);

    august_encrypt(text);
    printf("Encrypted text: %s\n", text);

    august_decrypt(text);
    printf("Decrypted text: %s\n", text);

    return 0;
}
