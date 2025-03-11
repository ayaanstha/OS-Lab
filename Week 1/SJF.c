#include <stdio.h>

int main() {
    int n, i, j, temp;
    int bt[20], p[20], wt[20], tat[20];
    float wavg = 0, tatavg = 0;


    printf("Enter the number of processes: ");
    scanf("%d", &n);

    
    for (i = 0; i < n; i++) {
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1; 
    }

    
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (bt[i] > bt[j]) {
                
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    
    wt[0] = 0;
    tat[0] = bt[0]; 

    
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1]; 
        tat[i] = wt[i] + bt[i]; 

        wavg += wt[i]; 
        tatavg += tat[i]; 
    }

    
    wavg /= n;
    tatavg /= n;

  
    printf("\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }

    
    printf("\nAverage Waiting Time: %.2f", wavg);
    printf("\nAverage Turnaround Time: %.2f\n", tatavg);

    return 0;
}
