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

void FIFO(int pages[], int n, int frames) {
    int frame[MAX_FRAMES];
    int index = 0, pageFaults = 0;
    for(int i =0;i<frames;i++){
        frame[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        if (!isPresent(frame, frames, pages[i])) {
            frame[index] = pages[i];
            index = (index + 1) % frames;
            pageFaults++;
        }
        for(int i =0;i<frames;i++){
            printf("%d ",frame[i]);
        }
        printf("\n");
    }
    printf("FIFO Page Faults: %d\n", pageFaults);
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
    FIFO(pages, n, frames);
    return 0;
}