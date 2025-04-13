#include <stdio.h>
#include <string.h>

void gronsfeldEncrypt(char *text, char *key) {
    int len = strlen(text);
    int keyLen = strlen(key);

    for (int i = 0; i < len; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = 'A' + (text[i] - 'A' + (key[i % keyLen] - '0')) % 26;
        else if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = 'a' + (text[i] - 'a' + (key[i % keyLen] - '0')) % 26;
    }
}

void gronsfeldDecrypt(char *text, char *key) {
    int len = strlen(text);
    int keyLen = strlen(key);

    for (int i = 0; i < len; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = 'A' + (26 + (text[i] - 'A') - (key[i % keyLen] - '0')) % 26;
        else if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = 'a' + (26 + (text[i] - 'a') - (key[i % keyLen] - '0')) % 26;
    }
}

int main() {
    char text[100], key[10];

    printf("Enter text: ");
    gets(text);
    printf("Enter numeric key (e.g., 314): ");
    gets(key);

    gronsfeldEncrypt(text, key);
    printf("Encrypted: %s\n", text);

    gronsfeldDecrypt(text, key);
    printf("Decrypted: %s\n", text);

    return 0;
}
