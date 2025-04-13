#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int determinant(int key[2][2]) {
    return (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
}

int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a, int m) {
    a = ((a % m) + m) % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;  
}

int isValidKey(int key[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (key[i][j] < 0 || key[i][j] >= 26) return 0;
        }
    }
    
    int det = determinant(key);
    return gcd(det, 26) == 1;
}

void adjugate(int key[2][2], int adj[2][2]) {
    adj[0][0] = key[1][1];
    adj[1][1] = key[0][0];
    adj[0][1] = (-key[0][1] + 26) % 26;
    adj[1][0] = (-key[1][0] + 26) % 26;
}

void encrypt(char* text, int key[2][2], char* result) {
    int len = strlen(text);
    char cleaned[len + 1];
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            cleaned[j++] = toupper(text[i]);
        }
    }
    cleaned[j] = '\0';

    if (strlen(cleaned) % 2 != 0) {
        cleaned[strlen(cleaned)] = 'X';
        cleaned[strlen(cleaned) + 1] = '\0';
    }

    int index = 0;
    for (int i = 0; i < strlen(cleaned); i += 2) {
        int p1 = cleaned[i] - 'A';
        int p2 = cleaned[i + 1] - 'A';

        int e1 = ((key[0][0] * p1 + key[0][1] * p2) % 26 + 26) % 26;
        int e2 = ((key[1][0] * p1 + key[1][1] * p2) % 26 + 26) % 26;

        result[index++] = e1 + 'A';
        result[index++] = e2 + 'A';
    }
    result[index] = '\0';
}

void decrypt(char* text, int key[2][2], char* result) {
    int det = determinant(key);
    int detInv = modInverse(det, 26);

    if (detInv == -1) {
        printf("Invalid key matrix! No modular multiplicative inverse exists.\n");
        return;
    }

    int adj[2][2];
    adjugate(key, adj);

    int invKey[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            invKey[i][j] = (adj[i][j] * detInv % 26 + 26) % 26;
        }
    }

    encrypt(text, invKey, result);
}

int main() {
    char text[100], encrypted[100], decrypted[100];
    int key[2][2];

    printf("Enter text to encrypt (letters only): ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';  

    printf("Enter 2x2 key matrix (4 numbers between 0-25):\n");
    printf("Note: Determinant must be coprime with 26\n");

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            while (1) {
                scanf("%d", &key[i][j]);
                if (key[i][j] >= 0 && key[i][j] < 26) break;
                printf("Please enter a number between 0 and 25: ");
            }
        }
    }

    if (!isValidKey(key)) {
        printf("Invalid key matrix! Determinant must be coprime with 26.\n");
        return 1;
    }

    encrypt(text, key, encrypted);
    decrypt(encrypted, key, decrypted);

    printf("\nOriginal text:  %s\n", text);
    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
