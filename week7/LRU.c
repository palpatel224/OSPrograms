#include <stdio.h>
#include <limits.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

int isPresent(int frame[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frame[i] == page) return 1;
    }
    return 0;
}

void LRU(int pages[], int n, int frames) {
    int frame[MAX_FRAMES]; 
    int recent[MAX_FRAMES]; 
    int pageFaults = 0;
    for(int i = 0;i<frames;i++){
        frame[i] = -1;
        recent[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (!isPresent(frame, frames, pages[i])) {
            if (i < frames) {
                frame[i] = pages[i];
                recent[i] = i;
            } else {
                int minIndex = 0;
                for (int j = 1; j < frames; j++) {
                    if (recent[j] < recent[minIndex]) 
                        minIndex = j;
                }
                frame[minIndex] = pages[i];
                recent[minIndex] = i;
            }
            pageFaults++;
        } else {
            for (int j = 0; j < frames; j++) {
                if (frame[j] == pages[i]) {
                    recent[j] = i;
                    break;
                }
            }
        }
        for(int i =0;i<frames;i++)
            printf("%d ",frame[i]);
        printf("\n");
    }
    printf("LRU Page Faults: %d\n", pageFaults);
}


int main() {
    int n, frames;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    LRU(pages, n, frames);
    return 0;
}