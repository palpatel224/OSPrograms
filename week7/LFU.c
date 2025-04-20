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

void LFU(int pages[], int n, int frames) {
    int frame[MAX_FRAMES];
    int count[MAX_FRAMES];
    int pageFaults = 0;
    for(int i =0;i<frames;i++){
        frame[i] = -1;
        count[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (!isPresent(frame, frames, pages[i])) {
            int minIndex = 0;
            int minCount = INT_MAX;
            for (int j = 0; j < frames; j++) {
                if(frame[j] == -1){
                    minIndex = j;
                    break;
                }
                if (count[j] < count[minIndex])
                    minIndex = j;
            }
            frame[minIndex] = pages[i];
            count[minIndex] = 1;
            pageFaults++;
        } else {
            for (int j = 0; j < frames; j++) {
                if (frame[j] == pages[i]) {
                    count[j]++;
                    break;
                }
            }
        }
        for(int i= 0;i<frames;i++){
            printf("%d ",frame[i]);
        }
        printf("\n");
    }
    printf("LFU Page Faults: %d\n", pageFaults);
}

int main() {
    int  n, frames;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    LFU(pages, n, frames);
    return 0;
}