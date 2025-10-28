#include <stdio.h>

void bestFit(int holes[], int m, int process[], int n) {
    printf("\n=== BEST FIT ===\n");
    int allocation[n];
    
    for(int i = 0; i < n; i++) allocation[i] = -1;
    
    for(int i = 0; i < n; i++) {
        int best_idx = -1;
        for(int j = 0; j < m; j++) {
            if(holes[j] >= process[i]) {
                if(best_idx == -1 || holes[j] < holes[best_idx]) {
                    best_idx = j;
                }
            }
        }
        
        if(best_idx != -1) {
            allocation[i] = best_idx;
            holes[best_idx] -= process[i];
        }
    }
    
    printf("\nProcess\tSize\tHole\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t", i+1, process[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i]+1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int m, n;
    printf("Enter number of holes: ");
    scanf("%d", &m);
    int holes[m];
    printf("Enter hole sizes: ");
    for(int i = 0; i < m; i++) {
        scanf("%d", &holes[i]);
    }
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int process[n];
    printf("Enter process sizes: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &process[i]);
    }
    bestFit(holes, m, process, n);
    return 0;
}