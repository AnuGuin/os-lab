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

void multiLevelQueue(Process system[], int n1, Process user[], int n2) {
    printf("\n=== MULTI-LEVEL QUEUE SCHEDULING ===\n");
    
    printf("\n--- SYSTEM PROCESSES (Higher Priority - FCFS) ---\n");
    fcfs(system, n1);
    
    int last_system_ct = 0;
    for(int i=0; i<n1; i++) {
        if(system[i].ct > last_system_ct) {
            last_system_ct = system[i].ct;
        }
    }

    printf("\n--- USER PROCESSES (Lower Priority - FCFS) ---\n");

    for(int i = 0; i < n2; i++) {
        if(user[i].at < last_system_ct) {
            user[i].at = last_system_ct;
        }
    }
    
    fcfs(user, n2);
}

int main() {
    int n1, n2;
    printf("Enter number of system processes: ");
    if(scanf("%d", &n1) != 1 || n1 < 0) {
        printf("Invalid number of system processes.\n");
        return 1;
    }
    printf("Enter number of user processes: ");
    if(scanf("%d", &n2) != 1 || n2 < 0) {
        printf("Invalid number of user processes.\n");
        return 1;
    }

    Process *system = (Process *)malloc(sizeof(Process) * n1);
    if(!system && n1 > 0) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    Process *user = (Process *)malloc(sizeof(Process) * n2);
    if(!user && n2 > 0) {
        printf("Memory allocation failed.\n");
        free(system);
        return 1;
    }

    for(int i = 0; i < n1; i++) {
        system[i].pid = i + 1;
        printf("Enter arrival time and burst time for system process %d: ", system[i].pid);
        if(scanf("%d %d", &system[i].at, &system[i].bt) != 2) {
            printf("Invalid input.\n");
            free(system);
            free(user);
            return 1;
        }
        system[i].priority = 1; // Higher priority
        system[i].ct = 0;
        system[i].tat = 0;
        system[i].wt = 0;
        system[i].remaining = system[i].bt;
    }

    for(int i = 0; i < n2; i++) {
        user[i].pid = n1 + i + 1;
        printf("Enter arrival time and burst time for user process %d: ", user[i].pid);
        if(scanf("%d %d", &user[i].at, &user[i].bt) != 2) {
            printf("Invalid input.\n");
            free(system);
            free(user);
            return 1;
        }
        user[i].priority = 2; // Lower priority
        user[i].ct = 0;
        user[i].tat = 0;
        user[i].wt = 0;
        user[i].remaining = user[i].bt;
    }

    multiLevelQueue(system, n1, user, n2);

    free(system);
    free(user);
    return 0;
}