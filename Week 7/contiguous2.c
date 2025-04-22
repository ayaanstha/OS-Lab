#include <stdio.h>

void allocateMemory(char *strategy, int blockSize[], int m, int processSize[], int n) {
    int allocation[n], blocks[m];

    // Copy block sizes to preserve original
    for (int i = 0; i < m; i++) blocks[i] = blockSize[i];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int chosen = -1;
        for (int j = 0; j < m; j++) {
            if (blocks[j] >= processSize[i]) {
                if (strategy == "First" && chosen == -1)
                    chosen = j;
                else if (strategy == "Best" && (chosen == -1 || blocks[j] < blocks[chosen]))
                    chosen = j;
                else if (strategy == "Worst" && (chosen == -1 || blocks[j] > blocks[chosen]))
                    chosen = j;
            }
        }
        if (chosen != -1) {
            allocation[i] = chosen;
            blocks[chosen] -= processSize[i];
        }
    }

    printf("\n%s Fit Allocation:\n", strategy);
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }
}

int main() {
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int blockSize[m], processSize[n];

    printf("Enter sizes of memory blocks:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter sizes of processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    allocateMemory("Worst", blockSize, m, processSize, n);
    allocateMemory("Best", blockSize, m, processSize, n);
    allocateMemory("First", blockSize, m, processSize, n);

    return 0;
}
