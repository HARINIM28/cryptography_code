#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to remove non-letter characters and convert to uppercase
void preprocessText(char *text) {
    int i, j = 0;
    for (i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            text[j++] = toupper(text[i]);
        }
    }
    text[j] = '\0';
}

// Function to assign numbers to the key based on alphabetical order
void assignKeyOrder(const char *key, int *order) {
    int len = strlen(key);
    char tempKey[len + 1];
    strcpy(tempKey, key);
    
    // Convert to uppercase
    for (int i = 0; i < len; i++) {
        tempKey[i] = toupper(tempKey[i]);
    }

    int idx = 0;
    int used[len];
    for (int i = 0; i < len; i++) {
        used[i] = 0;
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        for (int i = 0; i < len; i++) {
            if (tempKey[i] == ch && !used[i]) {
                order[i] = ch - 'A';
                used[i] = 1;
                idx++;
            }
        }
    }
}

// Encryption function
void encrypt(const char *plaintext, const char *key, char *ciphertext) {
    int ptLen = strlen(plaintext);
    int kLen = strlen(key);
    int rows = (ptLen + kLen - 1) / kLen;

    char matrix[rows][kLen];
    memset(matrix, 'X', sizeof(matrix));  // Fill with padding character 'X'

    // Fill matrix row-wise
    int index = 0;
    for (int r = 0; r < rows && index < ptLen; r++) {
        for (int c = 0; c < kLen && index < ptLen; c++) {
            matrix[r][c] = plaintext[index++];
        }
    }

    int order[kLen];
    assignKeyOrder(key, order);

    // Output ciphertext column-wise based on key order
    int pos = 0;
    for (int ch = 0; ch < 26; ch++) {
        for (int c = 0; c < kLen; c++) {
            if (order[c] == ch) {
                for (int r = 0; r < rows; r++) {
                    ciphertext[pos++] = matrix[r][c];
                }
            }
        }
    }
    ciphertext[pos] = '\0';
}

// Decryption function
void decrypt(const char *ciphertext, const char *key, char *plaintext) {
    int ctLen = strlen(ciphertext);
    int kLen = strlen(key);
    int rows = (ctLen + kLen - 1) / kLen;

    char matrix[rows][kLen];
    memset(matrix, 'X', sizeof(matrix));

    int order[kLen];
    assignKeyOrder(key, order);

    // Fill matrix column-wise based on key order
    int pos = 0;
    for (int ch = 0; ch < 26; ch++) {
        for (int c = 0; c < kLen; c++) {
            if (order[c] == ch) {
                for (int r = 0; r < rows; r++) {
                    if (pos < ctLen) {
                        matrix[r][c] = ciphertext[pos++];
                    }
                }
            }
        }
    }

    // Read matrix row-wise to recover plaintext
    pos = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < kLen; c++) {
            plaintext[pos++] = matrix[r][c];
        }
    }
    plaintext[ctLen] = '\0';
}

int main() {
    char text[1000], key[100], encrypted[1000], decrypted[1000];

    printf("Enter text to encrypt (letters only): ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // remove newline

    printf("Enter key (letters only): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    preprocessText(text);
    preprocessText(key);

    encrypt(text, key, encrypted);
    decrypt(encrypted, key, decrypted);

    printf("\nOriginal Text   : %s", text);
    printf("\nKey             : %s", key);
    printf("\nEncrypted Text  : %s", encrypted);
    printf("\nDecrypted Text  : %s\n", decrypted);

    return 0;
}
