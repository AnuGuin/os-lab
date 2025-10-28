#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[20], at[20], bt[20], ct[20], tat[20], wt[20];
    int done[20] = {0};
    float avg_tat = 0, avg_wt = 0;

    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
    }

    int completed = 0, current_time = 0;

    while(completed < n) {
        int idx = -1, min_bt = INT_MAX;

        // Find process with smallest burst time among arrived ones
        for(int i = 0; i < n; i++) {
            if(at[i] <= current_time && done[i] == 0 && bt[i] < min_bt) {
                min_bt = bt[i];
                idx = i;
            }
        }

        if(idx != -1) {
            current_time += bt[idx];
            ct[idx] = current_time;
            done[idx] = 1;
            completed++;
        } else {
            current_time++; // CPU idle
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_tat += tat[i];
        avg_wt += wt[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", avg_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);

    return 0;
}
