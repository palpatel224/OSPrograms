#include <stdio.h>
#include <limits.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    
    for (int i = 0; i < processes; i++)
        allocation[i] = -1;  

    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nFirst-Fit Allocation:");
    for (int i = 0; i < processes; i++)
        printf("\nProcess %d (%d KB) -> Block %d", i+1, processSize[i], (allocation[i] != -1) ? allocation[i]+1 : -1);
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];

    for (int i = 0; i < processes; i++)
        allocation[i] = -1;

    for (int i = 0; i < processes; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nBest-Fit Allocation:");
    for (int i = 0; i < processes; i++)
        printf("\nProcess %d (%d KB) -> Block %d", i+1, processSize[i], (allocation[i] != -1) ? allocation[i]+1 : -1);
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];

    for (int i = 0; i < processes; i++)
        allocation[i] = -1;

    for (int i = 0; i < processes; i++) {
        int worstIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("\nWorst-Fit Allocation:");
    for (int i = 0; i < processes; i++)
        printf("\nProcess %d (%d KB) -> Block %d", i+1, processSize[i], (allocation[i] != -1) ? allocation[i]+1 : -1);
}

void nextFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    int lastAllocated = 0;

    for (int i = 0; i < processes; i++)
        allocation[i] = -1;

    for (int i = 0; i < processes; i++) {
        int j = lastAllocated;
        int count = 0;

        while (count < blocks) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                lastAllocated = j;
                break;
            }
            j = (j + 1) % blocks;
            count++;
        }
    }

    printf("\nNext-Fit Allocation:");
    for (int i = 0; i < processes; i++)
        printf("\nProcess %d (%d KB) -> Block %d", i+1, processSize[i], (allocation[i] != -1) ? allocation[i]+1 : -1);
}

int main() {
    int blocks, processes;
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);
    printf("Enter sizes of %d memory blocks: ", blocks);
    for (int i = 0; i < blocks; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter sizes of %d processes: ", processes);
    for (int i = 0; i < processes; i++)
        scanf("%d", &processSize[i]);

    int blockCopy1[MAX_BLOCKS], blockCopy2[MAX_BLOCKS], blockCopy3[MAX_BLOCKS], blockCopy4[MAX_BLOCKS];
    for (int i = 0; i < blocks; i++) {
        blockCopy1[i] = blockCopy2[i] = blockCopy3[i] = blockCopy4[i] = blockSize[i];
    }

    firstFit(blockCopy1, blocks, processSize, processes);
    bestFit(blockCopy2, blocks, processSize, processes);
    worstFit(blockCopy3, blocks, processSize, processes);
    nextFit(blockCopy4, blocks, processSize, processes);

    return 0;
}