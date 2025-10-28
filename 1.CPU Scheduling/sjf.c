#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a process
typedef struct {
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int priority;   // Priority (lower value = higher priority)
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
    int remaining;  // Remaining burst time (for RR)
} Process;

// Function to calculate and display results
void displayResults(Process p[], int n) {
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    float total_tat = 0, total_wt = 0;
    
    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    
    printf("\nAverage Turnaround Time: %.2f", total_tat/n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt/n);
}

void sjf(Process p[], int n) {
    printf("\n=== SJF SCHEDULING ===\n");
    
    int completed = 0, current_time = 0;
    int is_completed[n];
    for(int i = 0; i < n; i++) is_completed[i] = 0;
    
    while(completed != n) {
        int idx = -1, min_bt = INT_MAX;
        
        // Find process with minimum burst time that has arrived
        for(int i = 0; i < n; i++) {
            if(p[i].at <= current_time && !is_completed[i]) {
                if(p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }
        
        if(idx != -1) {
            current_time += p[idx].bt;
            p[idx].ct = current_time;
            is_completed[idx] = 1;
            completed++;
        } else {
            current_time++;
        }
    }
    
    displayResults(p, n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    if(scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    Process *p = (Process *)malloc(sizeof(Process) * n);
    if(!p) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", p[i].pid);
        if(scanf("%d %d", &p[i].at, &p[i].bt) != 2) {
            printf("Invalid input.\n");
            free(p);
            return 1;
        }
        p[i].priority = 0;
        p[i].ct = 0;
        p[i].tat = 0;
        p[i].wt = 0;
        p[i].remaining = p[i].bt;
    }

    sjf(p, n);

    free(p);
    return 0;
}