#include <stdio.h>
#include <string.h>

void autokeyEncrypt(char *text, char *key, char *encrypted) {
    int len = strlen(text);
    char fullKey[200];
    strcpy(fullKey, key);
    strncat(fullKey, text, len - strlen(key));

    for (int i = 0; i < len; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z')
            encrypted[i] = 'A' + (text[i] - 'A' + fullKey[i] - 'A') % 26;
        else if (text[i] >= 'a' && text[i] <= 'z')
            encrypted[i] = 'a' + (text[i] - 'a' + fullKey[i] - 'a') % 26;
        else
            encrypted[i] = text[i];
    }
    encrypted[len] = '\0';
}

void autokeyDecrypt(char *text, char *key, char *decrypted) {
    int len = strlen(text);
    char fullKey[200];
    strcpy(fullKey, key);

    for (int i = 0; i < len; i++) {
        int shift = (fullKey[i] >= 'A' && fullKey[i] <= 'Z') ? fullKey[i] - 'A' : fullKey[i] - 'a';
        if (text[i] >= 'A' && text[i] <= 'Z') {
            decrypted[i] = 'A' + (26 + text[i] - 'A' - shift) % 26;
            fullKey[i + strlen(key)] = decrypted[i];
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            decrypted[i] = 'a' + (26 + text[i] - 'a' - shift) % 26;
            fullKey[i + strlen(key)] = decrypted[i];
        } else {
            decrypted[i] = text[i];
        }
    }
    decrypted[len] = '\0';
}

int main() {
    char text[100], key[100], encrypted[100], decrypted[100];

    printf("Enter plaintext: ");
    gets(text);
    printf("Enter key: ");
    gets(key);

    autokeyEncrypt(text, key, encrypted);
    printf("Encrypted: %s\n", encrypted);

    autokeyDecrypt(encrypted, key, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
