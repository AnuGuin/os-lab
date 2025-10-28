#include <stdio.h>

void optimal_page() {
    printf("\n=== OPTIMAL PAGE REPLACEMENT ===\n");
    
    int n, frames, pages[50], frame_arr[10], page_faults = 0;
    
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
                // Find optimal victim
                int farthest = i, replace_idx = 0;
                
                for(int j = 0; j < frames; j++) {
                    int k;
                    for(k = i + 1; k < n; k++) {
                        if(frame_arr[j] == pages[k]) {
                            break;
                        }
                    }
                    
                    // If page 'k' is never used again (k == n)
                    // it's the perfect victim.
                    if(k == n) { 
                        replace_idx = j;
                        break; // Found the best victim
                    }

                    // If this page is used further in the future
                    // than the current "farthest", update it.
                    if(k > farthest) {
                        farthest = k;
                        replace_idx = j;
                    }
                }
                pos = replace_idx;
            }
            
            frame_arr[pos] = pages[i];
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
    optimal_page();
    return 0;
}