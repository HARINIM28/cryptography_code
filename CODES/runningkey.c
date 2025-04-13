#include <stdio.h>
#include <string.h>

void runningKeyEncrypt(char *plaintext, char *key, char *ciphertext) {
    int len = strlen(plaintext);

    for (int i = 0; i < len; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
            ciphertext[i] = 'a' + (plaintext[i] - 'a' + key[i] - 'a') % 26;
        else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
            ciphertext[i] = 'A' + (plaintext[i] - 'A' + key[i] - 'A') % 26;
        else
            ciphertext[i] = plaintext[i];
    }
    ciphertext[len] = '\0';
}

void runningKeyDecrypt(char *ciphertext, char *key, char *plaintext) {
    int len = strlen(ciphertext);

    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
            plaintext[i] = 'a' + (26 + (ciphertext[i] - 'a') - (key[i] - 'a')) % 26;
        else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')
            plaintext[i] = 'A' + (26 + (ciphertext[i] - 'A') - (key[i] - 'A')) % 26;
        else
            plaintext[i] = ciphertext[i];
    }
    plaintext[len] = '\0';
}

int main() {
    char plaintext[200], key[200], ciphertext[200], decrypted[200];

    printf("Enter plaintext: ");
    gets(plaintext);
    printf("Enter long key (at least as long as plaintext): ");
    gets(key);

    runningKeyEncrypt(plaintext, key, ciphertext);
    printf("Encrypted: %s\n", ciphertext);

    runningKeyDecrypt(ciphertext, key, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
