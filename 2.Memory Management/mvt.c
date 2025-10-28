#include <stdio.h>

void mvt() {
    printf("\n=== MVT (Variable Partitions) ===\n");
    
    int memory, n, processes[10];
    printf("Enter total memory size: ");
    scanf("%d", &memory);
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter process sizes: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &processes[i]);
    }
    
    int remaining = memory;
    printf("\nProcess\tSize\tAllocated\tRemaining\n");
    for(int i = 0; i < n; i++) {
        if(remaining >= processes[i]) {
            printf("P%d\t%d\tYes\t\t%d\n", i+1, processes[i], remaining - processes[i]);
            remaining -= processes[i];
        } else {
            printf("P%d\t%d\tNo\t\t%d\n", i+1, processes[i], remaining);
        }
    }
    
    printf("\nExternal Fragmentation (Total Remaining): %d KB\n", remaining);
}


int main() {
    mvt();
    return 0;
}

