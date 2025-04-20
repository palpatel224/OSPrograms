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
void Optimal(int pages[], int n, int frames) {
    int frame[MAX_FRAMES]; 
    int pageFaults = 0;
    for(int i=0;i<frames;i++){
        frame[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        if (!isPresent(frame, frames, pages[i])) { 
            if (i < frames) {
                frame[i] = pages[i];
            } else {
                int farthest = -1;
                int replaceIndex = -1;
                for (int j = 0; j < frames; j++) {
                    int nextUse = INT_MAX; 
                    for (int k = i + 1; k < n; k++) {
                        if (frame[j] == pages[k]) {
                            nextUse = k;
                            break;
                        }
                    }
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIndex = j;
                    }
                }
                frame[replaceIndex] = pages[i];
            }
            for(int i =0;i<frames;i++){
                printf("%d ",frame[i]);
            }
            printf("\n");
            pageFaults++;
        }
    }
    printf("Optimal Page Faults: %d\n", pageFaults);
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
    Optimal(pages, n, frames);
    return 0;
}
