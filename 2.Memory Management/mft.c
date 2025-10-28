#include <stdio.h>

void mft() {
    printf("\n=== MFT (Fixed Partitions) ===\n");
    
    int partitions[10], n, processes[10], m;
    int allocated[10] = {0}; 
    printf("Enter number of partitions: ");
    scanf("%d", &n);
    
    printf("Enter partition sizes: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &partitions[i]);
    }
    
    printf("Enter number of processes: ");
    scanf("%d", &m);
    
    printf("Enter process sizes: ");
    for(int i = 0; i < m; i++) {
        scanf("%d", &processes[i]);
    }
    
    printf("\nProcess\tSize\tPartition\tInternal Frag\n");
    for(int i = 0; i < m; i++) {
        int allocated_flag = 0;
        for(int j = 0; j < n; j++) {
            if(partitions[j] >= processes[i] && !allocated[j]) {
                int frag = partitions[j] - processes[i];
                printf("P%d\t%d\t%d (Size %d)\t%d\n", i+1, processes[i], j+1, partitions[j], frag);
                allocated[j] = 1; // Mark partition as allocated
                allocated_flag = 1;
                break;
            }
        }
        if(!allocated_flag) {
            printf("P%d\t%d\tNot Allocated\n", i+1, processes[i]);
        }
    }
}

int main() {
    mft();
    return 0;
}

