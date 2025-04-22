#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int compare(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}

void fcfs(int requests[], int n, int head) {
    int total_seek = 0;
    printf("\nFCFS Disk Scheduling:\n");
    printf("Head movement: %d", head);
    for (int i = 0; i < n; i++) {
        total_seek += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }
    printf("\nTotal Seek Time: %d\n", total_seek);
}

void sstf(int requests[], int n, int head) {
    int total_seek = 0, completed[n];
    for (int i = 0; i < n; i++) completed[i] = 0;
    printf("\nSSTF Disk Scheduling:\n");
    printf("Head movement: %d", head);    
    for (int i = 0; i < n; i++) {
        int min_seek = INT_MAX, min_index = -1;
        for (int j = 0; j < n; j++) {
            if (!completed[j] && abs(requests[j] - head) < min_seek) {
                min_seek = abs(requests[j] - head);
                min_index = j;
            }
        }
        total_seek += min_seek;
        head = requests[min_index];
        completed[min_index] = 1;
        printf(" -> %d", head);
    }
    printf("\nTotal Seek Time: %d\n", total_seek);
}

void scan(int requests[], int n, int head, int disk_size, int direction) {
    int total_seek = 0;
    printf("\nSCAN Disk Scheduling:\n");
    printf("Head movement: %d ", head);
    int left[100], right[100], l = 0, r = 0, seek_sequence[100],x=0;
    if(direction == 1){
        right[r++] = disk_size-1; 
    }
    else {
        left[l++] = 0;
    } 
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) left[l++] = requests[i];
        else right[r++] = requests[i];
    }    
    qsort(left, l, sizeof(int), compare);
    qsort(right, r, sizeof(int), compare);
    int run = 2;
    while(run-->0){
        if (direction == 1) { 
            for(int i =0;i<r;i++){
                seek_sequence[x++] = right[i];
                total_seek += fabs(right[i] - head);
                head = right[i];
            }
            direction = 0;
        } else { 
            for(int i = l-1;i>=0;i--){
                seek_sequence[x++] = left[i];
                total_seek += fabs(left[i]-head);
                head = left[i];
            }
            direction =1;
        }
    }
    for(int i =0;i<x;i++){
        printf("%d ",seek_sequence[i]);
    }
    printf("\nTotal Seek Time: %d\n", total_seek);
}

int main() {
    int n, head, disk_size, direction;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size: ");
    scanf("%d", &disk_size);
    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &direction);   
    fcfs(requests, n, head);
    sstf(requests, n, head);
    scan(requests, n, head, disk_size, direction);
    return 0;
}