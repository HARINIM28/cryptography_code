#include <stdio.h>
#include <string.h>
#include <math.h>

void fillMatrix(char mat[10][10], char *text, int rows, int cols) {
    int k = 0;
    for (int i = 0; i < rows && k < strlen(text); i++)
        for (int j = 0; j < cols && k < strlen(text); j++)
            mat[i][j] = text[k++];
}

void routeCipherEncrypt(char *text, int rows, int cols, char *cipher) {
    char mat[10][10];
    fillMatrix(mat, text, rows, cols);

    int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
    int k = 0;

    while (top <= bottom && left <= right) {
        for (int i = top; i <= bottom; i++) cipher[k++] = mat[i][left];
        left++;

        for (int i = left; i <= right; i++) cipher[k++] = mat[bottom][i];
        bottom--;

        if (left <= right) {
            for (int i = bottom; i >= top; i--) cipher[k++] = mat[i][right];
            right--;
        }

        if (top <= bottom) {
            for (int i = right; i >= left; i--) cipher[k++] = mat[top][i];
            top++;
        }
    }

    cipher[k] = '\0';
}

void routeCipherDecrypt(char *cipher, int rows, int cols, char *plain) {
    char mat[10][10];
    int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
    int k = 0;

    while (top <= bottom && left <= right) {
        for (int i = top; i <= bottom; i++) mat[i][left] = cipher[k++];
        left++;

        for (int i = left; i <= right; i++) mat[bottom][i] = cipher[k++];
        bottom--;

        if (left <= right) {
            for (int i = bottom; i >= top; i--) mat[i][right] = cipher[k++];
            right--;
        }

        if (top <= bottom) {
            for (int i = right; i >= left; i--) mat[top][i] = cipher[k++];
            top++;
        }
    }

    k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            plain[k++] = mat[i][j];
    plain[k] = '\0';
}

int main() {
    char text[100], encrypted[100], decrypted[100];
    int rows, cols;

    printf("Enter text: ");
    gets(text);
    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);
    getchar();

    routeCipherEncrypt(text, rows, cols, encrypted);
    printf("Encrypted: %s\n", encrypted);

    routeCipherDecrypt(encrypted, rows, cols, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
