#include <stdio.h>
#include <stdlib.h>

void paging() {
    printf("\n=== PAGING SIMULATION ===\n");
    
    int pages, page_size, frames;
    printf("Enter total logical memory size (e.g., 8192): ");
    int mem_size;
    scanf("%d", &mem_size);
    printf("Enter page size (bytes) (e.g., 1024): ");
    scanf("%d", &page_size);
    
    pages = mem_size / page_size;
    printf("Total number of pages: %d\n", pages);
    
    int page_table[pages];
    printf("\nEnter frame number for each page (e.g., 'Page 0 -> Frame 5'):\n");
    for(int i = 0; i < pages; i++) {
        printf("Page %d -> Frame: ", i);
        scanf("%d", &page_table[i]);
    }
    
    printf("\n=== PAGE TABLE ===\n");
    printf("Page\tFrame\n");
    for(int i = 0; i < pages; i++) {
        printf("%d\t%d\n", i, page_table[i]);
    }
    
    // Address translation example
    int logical_addr;
    printf("\nEnter logical address to translate: ");
    scanf("%d", &logical_addr);
    
    int page_num = logical_addr / page_size;
    int offset = logical_addr % page_size;
    
    if(page_num >= pages) {
        printf("Error: Logical address exceeds process size.\n");
        return;
    }

    int frame_num = page_table[page_num];
    int physical_addr = frame_num * page_size + offset;
    
    printf("\nLogical Address: %d\n", logical_addr);
    printf("Page Number: %d\n", page_num);
    printf("Offset: %d\n", offset);
    printf("Frame Number: %d\n", frame_num);
    printf("Physical Address: %d * %d + %d = %d\n", frame_num, page_size, offset, physical_addr);
}

int main() {
    paging();
    return 0;
}