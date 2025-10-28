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

void roundRobin(Process p[], int n, int quantum) {
    printf("\n=== ROUND ROBIN SCHEDULING (Quantum=%d) ===\n", quantum);
    
    int current_time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;
    int visited[n];
    
    for(int i = 0; i < n; i++) {
        p[i].remaining = p[i].bt;
        visited[i] = 0;
    }
    
    // Add first process to queue (assuming at least one process at time 0 or sorting)
    // A more robust way would be to sort by AT first, or find the first arriving process
    // This implementation assumes P[0] is the first to check.
    
    // Let's find the first process to arrive to start the queue
    int first_idx = 0;
    for(int i = 1; i < n; i++) {
        if(p[i].at < p[first_idx].at) {
            first_idx = i;
        }
    }
    current_time = p[first_idx].at;
    queue[rear++] = first_idx;
    visited[first_idx] = 1;


    while(completed != n) {
        if(front == rear) {
            // Queue is empty, check for new arrivals
            int all_done = 1;
            for(int i=0; i<n; i++) {
                if(p[i].remaining > 0) all_done = 0;
            }
            if(all_done) break;

            current_time++;
            for(int i = 0; i < n; i++) {
                if(p[i].at <= current_time && !visited[i] && p[i].remaining > 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }
        
        int idx = queue[front++];
        
        if(p[idx].remaining <= quantum) {
            current_time += p[idx].remaining;
            p[idx].remaining = 0;
            p[idx].ct = current_time;
            completed++;
        } else {
            current_time += quantum;
            p[idx].remaining -= quantum;
        }
        
        // Add newly arrived processes to queue
        for(int i = 0; i < n; i++) {
            if(p[i].at <= current_time && !visited[i] && p[i].remaining > 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
        
        // Re-add current process if not completed
        if(p[idx].remaining > 0) {
            queue[rear++] = idx;
        }
    }
    
    displayResults(p, n);
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    if(scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    printf("Enter time quantum: ");
    if(scanf("%d", &quantum) != 1 || quantum <= 0) {
        printf("Invalid time quantum.\n");
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

    roundRobin(p, n, quantum);

    free(p);
    return 0;
}

