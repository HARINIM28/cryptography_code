#include <stdio.h>
#include <string.h>

void caesar_encrypt(char *text, int shift) {
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] - 'a' + shift) % 26 + 'a';
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] - 'A' + shift) % 26 + 'A';
        }
    }
}

void caesar_decrypt(char *text, int shift) {
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] - 'a' - shift + 26) % 26 + 'a';
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] - 'A' - shift + 26) % 26 + 'A';
        }
    }
}

int main() {
    char text[100];
    int shift;

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter shift value: ");
    scanf("%d", &shift);

    caesar_encrypt(text, shift);
    printf("Encrypted text: %s\n", text);

    caesar_decrypt(text, shift);
    printf("Decrypted text: %s\n", text);

    return 0;
}
