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

// 1a) FCFS (First Come First Serve)
void fcfs(Process p[], int n) {
    printf("\n=== FCFS SCHEDULING ===\n");
    
    // Sort by arrival time
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(p[j].at > p[j+1].at) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    
    int current_time = 0;
    for(int i = 0; i < n; i++) {
        if(current_time < p[i].at)
            current_time = p[i].at;
        
        current_time += p[i].bt;
        p[i].ct = current_time;
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

    fcfs(p, n);

    free(p);
    return 0;
}

