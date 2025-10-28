#include <stdio.h>

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int pid[20], at[20], bt[20], rt[20], ct[20], tat[20], wt[20];
    float avg_tat = 0, avg_wt = 0;

    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];  // remaining time
    }

    int completed = 0, current_time = 0;
    int done[20] = {0};

    // Continue until all processes complete
    while(completed < n) {
        int all_idle = 1;
        for(int i = 0; i < n; i++) {
            if(rt[i] > 0 && at[i] <= current_time) {
                all_idle = 0;

                if(rt[i] <= quantum) {
                    current_time += rt[i];
                    rt[i] = 0;
                    ct[i] = current_time;
                    completed++;
                } else {
                    rt[i] -= quantum;
                    current_time += quantum;
                }

                // Check for new arrivals before continuing
                for(int j = 0; j < n; j++) {
                    if(at[j] <= current_time && rt[j] > 0) {
                        done[j] = 0;
                    }
                }
            }
        }

        if(all_idle) current_time++;  // CPU idle if nothing has arrived yet
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
