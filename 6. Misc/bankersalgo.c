#include <stdio.h>

void bankersAlgorithm() {
    printf("\n=== BANKER'S ALGORITHM ===\n");
    
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    
    int allocation[n][m], max[n][m], available[m], need[n][m];
    
    printf("\nEnter Allocation Matrix (%d x %d):\n", n, m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    printf("\nEnter Max Matrix (%d x %d):\n", n, m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("\nEnter Available Resources (%d values):\n", m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
    
    // Calculate Need Matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    printf("\n=== NEED MATRIX ===\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    
    // Safety Algorithm
    int finish[n], safe_seq[n], count = 0;
    int work[m];
    
    for(int i = 0; i < m; i++) work[i] = available[i];
    for(int i = 0; i < n; i++) finish[i] = 0;
    
    while(count < n) {
        int found = 0;
        for(int i = 0; i < n; i++) {
            if(!finish[i]) {
                int can_allocate = 1;
                for(int j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }
                
                if(can_allocate) {
                    for(int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safe_seq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        
        if(!found) {
            printf("\nSystem is in UNSAFE state!\n");
            return;
        }
    }
    
    printf("\nSystem is in SAFE state!\n");
    printf("Safe Sequence: ");
    for(int i = 0; i < n; i++) {
        printf("P%d ", safe_seq[i]);
    }
    printf("\n");
}

int main() {
    bankersAlgorithm();
    return 0;  
}