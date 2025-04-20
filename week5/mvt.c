#include<stdio.h>
#include<stdlib.h>

int main() {
    int ms, mp[10], i, temp, n = 0;
    char ch = 'y';

    printf("\nEnter the total memory available (in Bytes)-- ");
    scanf("%d", &ms);
    temp = ms;

    for(i = 0; ch == 'y'; i++, n++) {
        printf("\nEnter memory required for process %d (in Bytes) -- ", i + 1);
        int mem_req;
        scanf("%d", &mem_req);
         
        if (mem_req < 0) {
            printf("Memory request cannot be negative. Please enter a valid value.\n");
            i--;  
            continue;
        }

        if(mem_req <= temp) {
            printf("\nMemory is allocated for Process %d ", i + 1);
            mp[i] = mem_req;  
            temp -= mem_req;  
            printf("\nCurrent available memory: %d", temp);
        } else {
            printf("\nMemory is Full");
            break;
        }

        printf("\nDo you want to continue(y/n) -- ");
        scanf(" %c", &ch);
    }

    printf("\n\nTotal Memory Available -- %d", ms);
    printf("\n\n\tPROCESS\t\t MEMORY ALLOCATED ");
    for(i = 0; i < n; i++)
        printf("\n \t%d\t\t%d", i + 1, mp[i]);
    
    printf("\n\nTotal Memory Allocated is %d", ms - temp);
    printf("\nTotal External Fragmentation is %d", temp);
}
