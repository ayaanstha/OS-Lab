#include <stdio.h>

int main() {
    int n, i, j, temp;
    int bt[20], p[20], wt[20], tat[20];
    float wavg = 0, tatavg = 0;

    // Taking input for number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input burst times and initialize process numbers
    for (i = 0; i < n; i++) {
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1; // Storing process number
    }

    // Sorting processes by burst time (SJF)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (bt[i] > bt[j]) {
                // Swap burst times
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap process numbers
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Initialize waiting time for the first process
    wt[0] = 0;
    tat[0] = bt[0]; // Turnaround time for the first process is its burst time

    // Calculate waiting time and turnaround time for each process
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1]; // Waiting time is the sum of burst times of previous processes
        tat[i] = wt[i] + bt[i]; // Turnaround time is waiting time + burst time

        wavg += wt[i]; // Summing up the waiting times
        tatavg += tat[i]; // Summing up the turnaround times
    }

    // Calculate averages
    wavg /= n;
    tatavg /= n;

    // Output the results
    printf("\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }

    // Output averages
    printf("\nAverage Waiting Time: %.2f", wavg);
    printf("\nAverage Turnaround Time: %.2f\n", tatavg);

    return 0;
}
