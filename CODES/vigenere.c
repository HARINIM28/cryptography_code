#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateKey(char *str, char *key) {
    int strLen = strlen(str);
    int keyLen = strlen(key);
    int i, j;
    for (i = keyLen, j = 0; i < strLen; i++, j++) {
        key[i] = key[j % keyLen];
    }
    key[i] = '\0';
}

void vignere_encrypt(char *plaintext, char *key, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            char baseKey = isupper(key[i]) ? 'A' : 'a';
            ciphertext[i] = ((plaintext[i] - base + key[i] - baseKey) % 26) + base;
        } else {
            ciphertext[i] = plaintext[i]; // keep spaces/symbols
        }
    }
    ciphertext[i] = '\0';
}

void vignere_decrypt(char *ciphertext, char *key, char *plaintext) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char baseKey = isupper(key[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - base - (key[i] - baseKey) + 26) % 26) + base;
        } else {
            plaintext[i] = ciphertext[i]; // keep spaces/symbols
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char plaintext[100], keyword[100], key[100], ciphertext[100], decrypted[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // remove newline

    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; // remove newline

    strcpy(key, keyword);
    generateKey(plaintext, key);

    vignere_encrypt(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    vignere_decrypt(ciphertext, key, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
