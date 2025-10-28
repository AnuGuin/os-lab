#include <stdio.h>

void fifo_page() {
    printf("\n=== FIFO PAGE REPLACEMENT ===\n");
    
    int n, frames, pages[50], frame_arr[10], page_faults = 0, index = 0;
    
    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    printf("Enter page reference string: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    
    for(int i = 0; i < frames; i++) {
        frame_arr[i] = -1;
    }
    
    printf("\nPage\tFrames\t\tFault\n");
    
    for(int i = 0; i < n; i++) {
        int found = 0;
        
        for(int j = 0; j < frames; j++) {
            if(frame_arr[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        
        printf("%d\t", pages[i]);
        
        if(!found) {
            frame_arr[index] = pages[i];
            index = (index + 1) % frames; // Circular queue index
            page_faults++;
            
            for(int j = 0; j < frames; j++) {
                if(frame_arr[j] != -1) printf("%d ", frame_arr[j]);
                else printf("- ");
            }
            printf("\tYes");
        } else {
            for(int j = 0; j < frames; j++) {
                if(frame_arr[j] != -1) printf("%d ", frame_arr[j]);
                else printf("- ");
            }
            printf("\tNo");
        }
        printf("\n");
    }
    
    printf("\nTotal Page Faults: %d\n", page_faults);
    printf("Hit Ratio: %.2f%%\n", ((float)(n - page_faults) / n) * 100);
}

int main() {
    fifo_page();
    return 0;
}