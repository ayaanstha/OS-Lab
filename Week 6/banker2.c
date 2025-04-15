#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int p, r;
int alloc[MAX_PROCESSES][MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES], avail[MAX_RESOURCES];

void calculate_need() {
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

bool is_safe_state(int seq[]) {
    int work[MAX_RESOURCES], count = 0;
    bool finish[MAX_PROCESSES] = { false };

    for (int i = 0; i < r; i++) work[i] = avail[i];

    while (count < p) {
        bool found = false;
        for (int i = 0; i < p; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < r && canRun; j++)
                    if (need[i][j] > work[j]) canRun = false;

                if (canRun) {
                    for (int j = 0; j < r; j++) work[j] += alloc[i][j];
                    finish[i] = true;
                    seq[count++] = i;
                    printf("P%d is visited( ", i);
                    for (int j = 0; j < r; j++) printf("%d ", work[j]);
                    printf(")\n");
                    found = true;
                }
            }
        }
        if (!found) return false;
    }
    return true;
}

bool request_resources(int pid, int req[]) {
    for (int i = 0; i < r; i++) {
        if (req[i] > need[pid][i]) {
            printf("Error: Request exceeds maximum need.\n");
            return false;
        }
        if (req[i] > avail[i]) {
            printf("Resources not available. P%d must wait.\n", pid);
            return false;
        }
    }

    for (int i = 0; i < r; i++) {
        avail[i] -= req[i];
        alloc[pid][i] += req[i];
        need[pid][i] -= req[i];
    }

    int seq[MAX_PROCESSES];
    bool safe = is_safe_state(seq);

    if (!safe) {
        for (int i = 0; i < r; i++) {
            avail[i] += req[i];
            alloc[pid][i] -= req[i];
            need[pid][i] += req[i];
        }
        printf("SYSTEM IS NOT IN SAFE STATE AFTER REQUEST.\n");
    } else {
        printf("SYSTEM IS IN SAFE STATE\nSafe Sequence is -- (");
        for (int i = 0; i < p; i++) printf("P%d ", seq[i]);
        printf(")\n");
    }
    return safe;
}

void print_table() {
    printf("\n%-10s %-10s %-10s %-10s\n", "Process", "Allocation", "Max", "Need");
    for (int i = 0; i < p; i++) {
        printf("P%-9d ", i);
        for (int j = 0; j < r; j++) printf("%d ", alloc[i][j]);
        printf("    ");
        for (int j = 0; j < r; j++) printf("%d ", max[i][j]);
        printf("    ");
        for (int j = 0; j < r; j++) printf("%d ", need[i][j]);
        printf("\n");
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &p);
    printf("Enter number of resources: ");
    scanf("%d", &r);

    for (int i = 0; i < p; i++) {
        printf("Enter details for P%d\n", i);
        printf("Enter allocation: ");
        for (int j = 0; j < r; j++) scanf("%d", &alloc[i][j]);
        printf("Enter Max: ");
        for (int j = 0; j < r; j++) scanf("%d", &max[i][j]);
    }

    printf("Enter Available Resources: ");
    for (int i = 0; i < r; i++) scanf("%d", &avail[i]);

    calculate_need();
    print_table();

    int pid, req[MAX_RESOURCES];
    printf("\nEnter New Request Details --\nEnter pid: ");
    scanf("%d", &pid);
    printf("Enter Request for Resources: ");
    for (int i = 0; i < r; i++) scanf("%d", &req[i]);

    request_resources(pid, req);
    return 0;
}
