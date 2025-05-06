#include <stdio.h>

int main() {
    int n, i, j;
    int b[20], sb[20], t[20], c[20][20];
    int fileToDisplay;

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter number of blocks occupied by file %d: ", i + 1);
        scanf("%d", &b[i]);
        printf("Enter the starting block of file %d: ", i + 1);
        scanf("%d", &sb[i]);

        t[i] = sb[i]; // store original start block
        for (j = 0; j < b[i]; j++) {
            c[i][j] = sb[i]++;
        }
    }

    printf("\nFilename\tStart Block\tLength\n");
    for (i = 0; i < n; i++) {
        printf("File%d\t\t%d\t\t%d\n", i + 1, t[i], b[i]);
    }

    printf("\nEnter file number to view its blocks (1 to %d): ", n);
    scanf("%d", &fileToDisplay);

    if (fileToDisplay < 1 || fileToDisplay > n) {
        printf("Invalid file number.\n");
        return 1;
    }

    printf("\nFile Name: File%d", fileToDisplay);
    printf("\nLength: %d", b[fileToDisplay - 1]);
    printf("\nBlocks occupied: ");
    for (i = 0; i < b[fileToDisplay - 1]; i++) {
        printf("%d ", c[fileToDisplay - 1][i]);
    }
    printf("\n");

    return 0;
}
