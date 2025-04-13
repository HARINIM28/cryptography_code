#include <stdio.h>
#include <string.h>

int mod_inverse(int a, int m) {
    for (int i = 1; i < m; i++) {
        if ((a * i) % m == 1) {
            return i;
        }
    }
    return -1;
}

void affine_encrypt(char *text, int a, int b) {
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (a * (text[i] - 'a') + b) % 26 + 'a';
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (a * (text[i] - 'A') + b) % 26 + 'A';
        }
    }
}

void affine_decrypt(char *text, int a, int b) {
    int a_inv = mod_inverse(a, 26);
    if (a_inv == -1) {
        printf("No modular inverse exists for 'a'\n");
        return;
    }

    for (int i = 0; i < strlen(text); i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (a_inv * (text[i] - 'a' - b + 26)) % 26 + 'a';
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (a_inv * (text[i] - 'A' - b + 26)) % 26 + 'A';
        }
    }
}

int main() {
    char text[100];
    int a, b;

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter 'a' and 'b' for affine cipher: ");
    scanf("%d %d", &a, &b);

    affine_encrypt(text, a, b);
    printf("Encrypted text: %s\n", text);

    affine_decrypt(text, a, b);
    printf("Decrypted text: %s\n", text);

    return 0;
}
