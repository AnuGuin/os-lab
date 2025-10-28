#include <stdio.h>

void lfu_page() {
    printf("\n=== LFU PAGE REPLACEMENT ===\n");
    
    int n, frames, pages[50], frame_arr[10], freq[10] = {0}, recent[10] = {0}, page_faults = 0;
    
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
        int found = 0, pos = -1;
        
        for(int j = 0; j < frames; j++) {
            if(frame_arr[j] == pages[i]) {
                found = 1;
                freq[j]++;
                recent[j] = i; // Update recent use (for tie-breaking)
                break;
            }
        }
        
        printf("%d\t", pages[i]);
        
        if(!found) {
            for(int j = 0; j < frames; j++) {
                if(frame_arr[j] == -1) {
                    pos = j;
                    break;
                }
            }
            
            if(pos == -1) {
                // Find LFU frame
                int min_freq = freq[0], min_pos = 0;
                for(int j = 1; j < frames; j++) {
                    if(freq[j] < min_freq) {
                        min_freq = freq[j];
                        min_pos = j;
                    } 
                    // Tie-breaker: if frequencies are equal, use LRU
                    else if(freq[j] == min_freq && recent[j] < recent[min_pos]) {
                        min_pos = j;
                    }
                }
                pos = min_pos;
            }
            
            frame_arr[pos] = pages[i];
            freq[pos] = 1;
            recent[pos] = i;
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
    lfu_page();
    return 0;
}