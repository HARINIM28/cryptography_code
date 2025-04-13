#include <stdio.h>
#include <string.h>

void railFenceEncrypt(char *text, int rails, char *cipher) {
    int len = strlen(text);
    char rail[rails][len];
    int dir_down = 0, row = 0, col = 0;

    // initialize the rail matrix
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    for (int i = 0; i < len; i++) {
        rail[row][col++] = text[i];

        if (row == 0 || row == rails - 1)
            dir_down = !dir_down;

        row += dir_down ? 1 : -1;
    }

    int index = 0;
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] != '\n')
                cipher[index++] = rail[i][j];

    cipher[index] = '\0';
}

void railFenceDecrypt(char *cipher, int rails, char *result) {
    int len = strlen(cipher);
    char rail[rails][len];

    // initialize the rail matrix
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    int dir_down, row = 0, col = 0;

    for (int i = 0; i < len; i++) {
        if (row == 0)
            dir_down = 1;
        if (row == rails - 1)
            dir_down = 0;

        rail[row][col++] = '*';

        row += dir_down ? 1 : -1;
    }

    int index = 0;
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] == '*')
                rail[i][j] = cipher[index++];

    row = 0, col = 0;
    for (int i = 0; i < len; i++) {
        if (row == 0)
            dir_down = 1;
        if (row == rails - 1)
            dir_down = 0;

        result[i] = rail[row][col++];
        row += dir_down ? 1 : -1;
    }

    result[len] = '\0';
}

int main() {
    char text[100], encrypted[100], decrypted[100];
    int rails;

    printf("Enter text: ");
    gets(text);
    printf("Enter number of rails: ");
    scanf("%d", &rails);
    getchar();

    railFenceEncrypt(text, rails, encrypted);
    printf("Encrypted: %s\n", encrypted);

    railFenceDecrypt(encrypted, rails, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
