#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[20], bt[20], ct[20], tat[20], wt[20];
    int pid[20];
    float avg_tat = 0, avg_wt = 0;

    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
    }

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(at[j] > at[j + 1]) {
                int temp;
                temp = at[j]; at[j] = at[j + 1]; at[j + 1] = temp;
                temp = bt[j]; bt[j] = bt[j + 1]; bt[j + 1] = temp;
                temp = pid[j]; pid[j] = pid[j + 1]; pid[j + 1] = temp;
            }
        }
    }

    // FCFS logic
    int current_time = 0;
    for(int i = 0; i < n; i++) {
        if(current_time < at[i])
            current_time = at[i];
        current_time += bt[i];
        ct[i] = current_time;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    // Display results
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", avg_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);

    return 0;
}
