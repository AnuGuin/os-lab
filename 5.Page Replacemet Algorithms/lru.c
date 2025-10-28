#include <stdio.h>

void lru_page() {
    printf("\n=== LRU PAGE REPLACEMENT ===\n");
    
    int n, frames, pages[50], frame_arr[10], recent[10], page_faults = 0;
    
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
        recent[i] = -1; // Use -1 to indicate empty
    }
    
    printf("\nPage\tFrames\t\tFault\n");
    
    for(int i = 0; i < n; i++) {
        int found = 0, pos = -1;
        
        for(int j = 0; j < frames; j++) {
            if(frame_arr[j] == pages[i]) {
                found = 1;
                recent[j] = i; // Update its "last used" time
                break;
            }
        }
        
        printf("%d\t", pages[i]);
        
        if(!found) {
            // Find empty frame
            for(int j = 0; j < frames; j++) {
                if(frame_arr[j] == -1) {
                    pos = j;
                    break;
                }
            }
            
            if(pos == -1) {
                // Find LRU frame (one with smallest 'recent' value)
                int min = recent[0], min_pos = 0;
                for(int j = 1; j < frames; j++) {
                    if(recent[j] < min) {
                        min = recent[j];
                        min_pos = j;
                    }
                }
                pos = min_pos;
            }
            
            frame_arr[pos] = pages[i];
            recent[pos] = i; // Set its "last used" time
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
    lru_page();
    return 0;
}