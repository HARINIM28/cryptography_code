#include <stdio.h>
#include <string.h>

void beaufortCipher(char *text, char *key, char *result) {
    int len = strlen(text);
    int keyLen = strlen(key);

    for (int i = 0; i < len; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            result[i] = 'A' + (26 + (key[i % keyLen] - 'A') - (text[i] - 'A')) % 26;
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            result[i] = 'a' + (26 + (key[i % keyLen] - 'a') - (text[i] - 'a')) % 26;
        } else {
            result[i] = text[i];
        }
    }
    result[len] = '\0';
}

int main() {
    char text[100], key[100], encrypted[100];

    printf("Enter text: ");
    gets(text);
    printf("Enter key: ");
    gets(key);

    beaufortCipher(text, key, encrypted);
    printf("Encrypted: %s\n", encrypted);

    beaufortCipher(encrypted, key, text);  // Decrypting with same function
    printf("Decrypted: %s\n", text);

    return 0;
}
